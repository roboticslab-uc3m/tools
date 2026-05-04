// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/ResourceFinder.h>

#include "LogComponent.hpp"

// ------------------- DeviceDriver Related ------------------------------------

bool BasicJointCoupling::open(yarp::os::Searchable & config)
{
    if (!parseParams(config))
    {
        yCError(BJC) << "Failed to parse parameters";
        return false;
    }

    yarp::os::ResourceFinder rf;
    rf.setDefaultContext("BasicJointCoupling");

    std::string configFileFullPath = rf.findFileByName(m_configFile);

    if (configFileFullPath.empty())
    {
        yCError(BJC) << "Configuration file not found:" << m_configFile;
        return false;
    }

    yCInfo(BJC) << "Using config file:" << configFileFullPath;

    yarp::os::Property fullConfig;

    if (!fullConfig.fromConfigFile(configFileFullPath))
    {
        yCError(BJC) << "Failed to read configuration file:" << m_configFile;
        return false;
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
        const auto actuatedAxisName = actuatedAxes->get(i).asString();
        actuatedAxesNames.push_back(actuatedAxisName);

        const auto group = fullConfig.findGroup(actuatedAxisName).tail();

        if (group.isNull() || group.size() == 0)
        {
            yCError(BJC) << "Missing or empty section for actuated axis" << actuatedAxisName;
            return false;
        }

        yCInfo(BJC) << "Actuated axis" << actuatedAxisName << "is coupled with:" << group.toString();
    }

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        physicalJointsNames.push_back(physicalJoints->get(i).asString());
        this->physicalJointLimitsMins.push_back(physicalJointLimitsMins->get(i).asFloat64());
        this->physicalJointLimitsMaxs.push_back(physicalJointLimitsMaxs->get(i).asFloat64());
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::close()
{
    return true;
}

// -----------------------------------------------------------------------------
