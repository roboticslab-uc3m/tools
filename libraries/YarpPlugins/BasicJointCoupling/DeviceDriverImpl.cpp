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

    const auto actuatedAxes = fullConfig.findGroup("actuatedAxes").tail();
    const auto physicalJoints = fullConfig.findGroup("physicalJoints").tail();

    if (actuatedAxes.isNull() || actuatedAxes.size() == 0)
    {
        yCError(BJC) << "Missing or empty \"actuatedAxes\" section collection";
        return false;
    }

    if (physicalJoints.isNull() || physicalJoints.size() == 0)
    {
        yCError(BJC) << "Missing or empty \"physicalJoints\" section collection";
        return false;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::close()
{
    return true;
}

// -----------------------------------------------------------------------------
