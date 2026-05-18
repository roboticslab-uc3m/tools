// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <algorithm> // std::find

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/ResourceFinder.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------- DeviceDriver Related ------------------------------------

bool BasicJointCoupling::open(yarp::os::Searchable & config)
{
    yarp::os::Property fullConfig;

    if (const auto & couplingGroup = config.findGroup("COUPLING"); !couplingGroup.isNull())
    {
        fullConfig.fromString(couplingGroup.toString(), false);
    }

    // allow override of config file parameters with command line parameters
    fullConfig.fromString(config.toString(), false);

    if (!parseParams(fullConfig))
    {
        yCError(BJC) << "Failed to parse parameters";
        return false;
    }

    if (!m_configFile.empty())
    {
        yarp::os::ResourceFinder rf;
        rf.setDefaultContext("coupling");

        std::string configFileFullPath = rf.findFileByName(m_configFile);

        if (!configFileFullPath.empty() && fullConfig.fromConfigFile(configFileFullPath, false))
        {
            yCInfo(BJC) << "Using config file:" << configFileFullPath;
        }
        else
        {
            yCWarning(BJC) << "Failed to read configuration file:" << m_configFile;
        }
    }

    const auto * actuatedAxes = fullConfig.find("actuatedAxes").asList();
    const auto * physicalJoints = fullConfig.find("physicalJoints").asList();
    const auto * physicalJointLimitsMins = fullConfig.find("mins").asList();
    const auto * physicalJointLimitsMaxs = fullConfig.find("maxs").asList();

    if (!actuatedAxes || actuatedAxes->size() == 0)
    {
        yCError(BJC) << "Missing or empty 'actuatedAxes' property or not a list";
        return false;
    }

    if (!physicalJoints || physicalJoints->size() == 0)
    {
        yCError(BJC) << "Missing or empty 'physicalJoints' property or not a list";
        return false;
    }

    if (!physicalJointLimitsMins || physicalJointLimitsMins->size() != physicalJoints->size())
    {
        yCError(BJC) << "Missing or empty 'mins' property, not a list, or its size does not match the number of physical joints";
        return false;
    }

    if (!physicalJointLimitsMaxs || physicalJointLimitsMaxs->size() != physicalJoints->size())
    {
        yCError(BJC) << "Missing or empty 'maxs' property, not a list, or its size does not match the number of physical joints";
        return false;
    }

    yCInfo(BJC) << "Actuated axes:" << actuatedAxes->toString();
    yCInfo(BJC) << "Physical joints:" << physicalJoints->toString();
    yCInfo(BJC) << "Physical joint limits mins:" << physicalJointLimitsMins->toString();
    yCInfo(BJC) << "Physical joint limits maxs:" << physicalJointLimitsMaxs->toString();

    numberOfActuatedAxes = actuatedAxes->size();
    numberOfPhysicalJoints = physicalJoints->size();

    for (auto i = 0; i < numberOfActuatedAxes; i++)
    {
        actuatedAxesNames.push_back(actuatedAxes->get(i).asString());
    }

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        physicalJointsNames.push_back(physicalJoints->get(i).asString());
        this->physicalJointLimitsMins.push_back(physicalJointLimitsMins->get(i).asFloat64());
        this->physicalJointLimitsMaxs.push_back(physicalJointLimitsMaxs->get(i).asFloat64());
    }

    std::vector<std::string> uncoupledActuatedAxesNames;
    std::vector<std::string> uncoupledPhysicalJointsNames;

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        const auto & actuatedAxisName = actuatedAxesNames[actuatedAxisIndex];
        const auto collection = fullConfig.findGroup(actuatedAxisName).tail();

        if (collection.isNull() || collection.size() == 0)
        {
            yCError(BJC) << "Missing or empty section collection for actuated axis" << actuatedAxisName;
            return false;
        }

        yCInfo(BJC) << "Actuated axis" << actuatedAxisName << "is coupled with physical joints:" << collection.toString();

        if (collection.size() == 1)
        {
            uncoupledActuatedAxesNames.push_back(actuatedAxisName);
            uncoupledPhysicalJointsNames.push_back(collection.get(0).asString());
        }

        for (auto collectionIndex = 0; collectionIndex < collection.size(); collectionIndex++)
        {
            const auto physicalJointName = collection.get(collectionIndex).asString();

            auto it = std::find(physicalJointsNames.begin(), physicalJointsNames.end(), physicalJointName);

            if (it == physicalJointsNames.end())
            {
                yCError(BJC) << "Unrecognized physical joint" << physicalJointName << "coupled with actuated axis" << actuatedAxisName;
                return false;
            }

            int physicalJointIndex = std::distance(physicalJointsNames.begin(), it);

            if (physicalToActuated.count(physicalJointIndex) > 0) // TODO: replace with .contains() in C++20
            {
                yCError(BJC) << "Physical joint" << physicalJointName << "coupled with more than one actuated axis";
                return false;
            }

            const auto & group = fullConfig.findGroup(physicalJointName);
            yCInfo(BJC) << "Physical joint" << physicalJointName << "config:" << group.toString();

            auto * transformation = createTransformation(group);

            if (!transformation)
            {
                yCError(BJC) << "Failed to create transformation for coupling between actuated axis" << actuatedAxisName << "and physical joint" << physicalJointName;
                return false;
            }

            physicalToActuated.emplace(physicalJointIndex, std::make_pair(actuatedAxisIndex, transformation));

            auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);

            for (auto itt = range.first; itt != range.second; ++itt)
            {
                if (itt->second.first == physicalJointIndex)
                {
                    yCError(BJC) << "Physical joint" << physicalJointName << "coupled with actuated axis" << actuatedAxisName << "more than once";
                    return false;
                }
            }

            actuatedToPhysical.emplace(actuatedAxisIndex, std::make_pair(physicalJointIndex, transformation->inverse()));
        }
    }

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        if (physicalToActuated.count(i) == 0) // TODO: replace with .contains() in C++20
        {
            yCError(BJC) << "Physical joint" << physicalJointsNames[i] << "not coupled with any actuated axis";
            return false;
        }
    }

    for (auto i = 0; i < numberOfActuatedAxes; i++)
    {
        if (std::find(uncoupledActuatedAxesNames.begin(), uncoupledActuatedAxesNames.end(), actuatedAxesNames[i]) == uncoupledActuatedAxesNames.end())
        {
            coupledActuatedAxesIndexes.push_back(i);
        }
    }

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        if (std::find(uncoupledPhysicalJointsNames.begin(), uncoupledPhysicalJointsNames.end(), physicalJointsNames[i]) == uncoupledPhysicalJointsNames.end())
        {
            coupledPhysicalJointsIndexes.push_back(i);
        }
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::close()
{
    for (auto & [id, entry] : physicalToActuated)
    {
        delete entry.second;
    }

    for (auto & [id, entry] : actuatedToPhysical)
    {
        delete entry.second;
    }

    physicalToActuated.clear();
    actuatedToPhysical.clear();

    return true;
}

// -----------------------------------------------------------------------------
