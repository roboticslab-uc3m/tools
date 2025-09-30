// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <map>
#include <sstream>

#include <yarp/os/Bottle.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------- DeviceDriver Related ------------------------------------

bool RealToSimControlBoard::open(yarp::os::Searchable & config)
{
    if (!parseParams(config))
    {
        yCError(R2SCB) << "Failed to parse parameters";
        return false;
    }

    switch (m_modePosVel)
    {
    case 0:
        controlMode = POSITION_MODE;
        break;
    case 1:
        controlMode = VELOCITY_MODE;
        break;
    default:
        yCError(R2SCB) << "Unrecognized mode identifier:" << m_modePosVel;
        return false;
    }

    std::map<std::string, int> controlledDeviceNameToIdx;

    for (auto controlledDeviceIdx = 0; controlledDeviceIdx < m_remotes.size(); controlledDeviceIdx++)
    {
        std::string controlledDeviceName = m_remotes[controlledDeviceIdx];

        if (!config.check(controlledDeviceName))
        {
            yCError(R2SCB) << "Group" << controlledDeviceName << "not found";
            return false;
        }

        yCInfo(R2SCB) << "Group" << controlledDeviceName << "found";

        yarp::os::Bottle controlledDeviceGroup = config.findGroup(controlledDeviceName);
        yCInfo(R2SCB) << controlledDeviceGroup.toString();

        yarp::os::Property controlledDeviceOptions;
        controlledDeviceOptions.fromString(controlledDeviceGroup.toString());

        if (!m_remoteSuffix.empty())
        {
            std::string remote = m_remotePrefix + controlledDeviceOptions.find("remoteSuffix").asString();
            controlledDeviceOptions.unput("remoteSuffix");
            controlledDeviceOptions.put("remote", remote);
        }

        if (!m_localSuffix.empty())
        {
            std::string local = m_remotePrefix + controlledDeviceOptions.find("localSuffix").asString();
            controlledDeviceOptions.unput("localSuffix");
            controlledDeviceOptions.put("local", local);
        }

        auto * controlledDevice = new yarp::dev::PolyDriver(controlledDeviceOptions);

        if (!controlledDevice->isValid())
        {
            yCError(R2SCB) << "Group" << controlledDeviceName << "did not create a valid yarp device";
            delete controlledDevice;
            return false;
        }

        yCInfo(R2SCB) << "Group" << controlledDeviceName << "created a valid yarp device";

        controlledDeviceNameToIdx[controlledDeviceName] = controlledDeviceIdx;
        controlledDevices.push_back(controlledDevice);
    }

    int idx = 0;

    while (true)
    {
        std::ostringstream exposedJointNameStream("exposed_joint_", std::ios_base::app);
        exposedJointNameStream << idx;

        std::string exposedJointName = exposedJointNameStream.str();

        if (!config.check(exposedJointName))
        {
            axes = idx;
            storedPositions.resize(axes);
            yCInfo(R2SCB, "Could not find group %s, setting number of exposed joints to %d", exposedJointName.c_str(), axes);
            break;
        }

        yCInfo(R2SCB) << "* Group" << exposedJointName << "found";

        auto * exposedJoint = new ExposedJoint(exposedJointName);
        exposedJoints.push_back(exposedJoint);

        yarp::os::Bottle exposedJointGroup = config.findGroup(exposedJointName);
        yCDebug(R2SCB) << "*" << exposedJointGroup.toString();

        for (size_t exposedJointControlledDeviceIdx = 1; exposedJointControlledDeviceIdx < exposedJointGroup.size(); exposedJointControlledDeviceIdx++)
        {
            yarp::os::Bottle * exposedJointControlledDeviceGroup = exposedJointGroup.get(exposedJointControlledDeviceIdx).asList();
            yCDebug(R2SCB) << "**" << exposedJointControlledDeviceGroup->toString();

            std::string exposedJointControlledDeviceName = exposedJointControlledDeviceGroup->get(0).asString();
            int idx = controlledDeviceNameToIdx[exposedJointControlledDeviceName];
            yCDebug(R2SCB, "** %s [%d]", exposedJointControlledDeviceName.c_str(), idx);

            auto * exposedJointControlledDevice = new ExposedJointControlledDevice(exposedJointControlledDeviceName, controlledDevices[idx]);
            exposedJoint->addExposedJointControlledDevice(exposedJointControlledDevice);

            for (size_t exposedJointControlledDeviceJointIdx = 1; exposedJointControlledDeviceJointIdx < exposedJointControlledDeviceGroup->size(); exposedJointControlledDeviceJointIdx++)
            {
                yarp::os::Bottle * exposedJointControlledDeviceJointGroup = exposedJointControlledDeviceGroup->get(exposedJointControlledDeviceJointIdx).asList();
                yCDebug(R2SCB) << "***" << exposedJointControlledDeviceJointGroup->toString();

                if (!exposedJointControlledDevice->addControlledDeviceJoint(exposedJointControlledDeviceJointGroup))
                {
                    return false;
                }
            }
        }

        idx++;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::close()
{
    for (auto * device : controlledDevices)
    {
        device->close();
        delete device;
    }

    controlledDevices.clear();

    for (auto * joint : exposedJoints)
    {
        delete joint;
    }

    exposedJoints.clear();

    return true;
}

// -----------------------------------------------------------------------------
