// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <map>
#include <sstream>

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

constexpr auto DEFAULT_MODE_POS_VEL = 0; // 0=Position, 1=Velocity.

using namespace roboticslab;

// ------------------- DeviceDriver Related ------------------------------------

bool RealToSimControlboard::open(yarp::os::Searchable& config)
{
    int modePosVelInt = config.check("modePosVel", yarp::os::Value(DEFAULT_MODE_POS_VEL), "0:pos, 1:vel").asInt32();

    switch (modePosVelInt)
    {
    case 0:
        controlMode = POSITION_MODE;
        break;
    case 1:
        controlMode = VELOCITY_MODE;
        break;
    default:
        yCError(R2SCB) << "Unrecognized mode identifier:" << modePosVelInt << "(0:pos, 1:vel)";
        return false;
    }

    if(!config.check("remotes", "list of remotes to which this device connects"))
    {
        yCError(R2SCB) << "Required \"remotes\" list";
        return false;
    }
    yarp::os::Bottle* controlledDeviceList = config.find("remotes").asList();
    if (!controlledDeviceList)
    {
        yCError(R2SCB) << "Error parsing parameters: \"remotes\" should be followed by a list";
        return false;
    }
    yCDebug(R2SCB) << controlledDeviceList->toString();

    std::string remotePrefix;
    if(config.check("remotePrefix", "global prefix to remote ports"))
    {
        remotePrefix = config.find("remotePrefix").asString();
    }

    std::map<std::string,int> controlledDeviceNameToIdx;
    for(size_t controlledDeviceIdx=0; controlledDeviceIdx< controlledDeviceList->size(); controlledDeviceIdx++)
    {
        std::string controlledDeviceName = controlledDeviceList->get(controlledDeviceIdx).asString();
        if(!config.check(controlledDeviceName))
        {
            yCError(R2SCB, "\"%s\" group not found!", controlledDeviceName.c_str());
            return false;
        }
        yCInfo(R2SCB, "\"%s\" group found!", controlledDeviceName.c_str());
        yarp::os::Bottle controlledDeviceGroup = config.findGroup(controlledDeviceName);
        yCInfo(R2SCB) << controlledDeviceGroup.toString();
        yarp::os::Property controlledDeviceOptions;
        controlledDeviceOptions.fromString(controlledDeviceGroup.toString());

        if(controlledDeviceOptions.check("remoteSuffix", "suffix used for local and remote of each remote_controlboard"))
        {
            std::string remote(remotePrefix);
            remote += controlledDeviceOptions.find("remoteSuffix").asString();
            controlledDeviceOptions.unput("remoteSuffix");
            controlledDeviceOptions.put("remote",remote);

            std::string local(remotePrefix);
            local += controlledDeviceOptions.find("localSuffix").asString();
            controlledDeviceOptions.unput("localSuffix");
            controlledDeviceOptions.put("local",local);
        }

        yarp::dev::PolyDriver* controlledDevice = new yarp::dev::PolyDriver(controlledDeviceOptions);
        if( ! controlledDevice->isValid() )
        {
            yCError(R2SCB, "\"%s\" group did not create a valid yarp device!", controlledDeviceName.c_str());
            return false;
        }
        yCInfo(R2SCB, "\"%s\" group created a valid yarp device!", controlledDeviceName.c_str());

        controlledDeviceNameToIdx[controlledDeviceName] = controlledDeviceIdx;
        controlledDevices.push_back(controlledDevice);
    }

    int idx = 0;
    while(true)
    {
        std::ostringstream exposedJointNameStream("exposed_joint_", std::ios_base::app);
        exposedJointNameStream << idx;
        std::string exposedJointName(exposedJointNameStream.str());
        if(!config.check(exposedJointName))
        {
            axes = idx;
            storedPositions.resize(axes);
            yCInfo(R2SCB, "Could not find \"%s\" group, setting number of exposed joints to %d",exposedJointName.c_str(), axes);
            break;
        }
        yCInfo(R2SCB, "* %s group found!", exposedJointName.c_str());

        ExposedJoint* exposedJoint = new ExposedJoint(exposedJointName);
        exposedJoints.push_back(exposedJoint);

        yarp::os::Bottle exposedJointGroup = config.findGroup(exposedJointName);
        yCDebug(R2SCB, "* %s", exposedJointGroup.toString().c_str());
        for(size_t exposedJointControlledDeviceIdx=1; exposedJointControlledDeviceIdx<exposedJointGroup.size(); exposedJointControlledDeviceIdx++)
        {
            yarp::os::Bottle* exposedJointControlledDeviceGroup = exposedJointGroup.get(exposedJointControlledDeviceIdx).asList();
            yCDebug(R2SCB, "** %s", exposedJointControlledDeviceGroup->toString().c_str());
            std::string exposedJointControlledDeviceName = exposedJointControlledDeviceGroup->get(0).asString();
            int idx = controlledDeviceNameToIdx[exposedJointControlledDeviceName];
            yCDebug(R2SCB, "** %s [%d]", exposedJointControlledDeviceName.c_str(), idx);

            ExposedJointControlledDevice* exposedJointControlledDevice =
                new ExposedJointControlledDevice(exposedJointControlledDeviceName, controlledDevices[idx]);
            exposedJoint->addExposedJointControlledDevice(exposedJointControlledDevice);

            for(size_t exposedJointControlledDeviceJointIdx=1; exposedJointControlledDeviceJointIdx<exposedJointControlledDeviceGroup->size(); exposedJointControlledDeviceJointIdx++)
            {
                yarp::os::Bottle* exposedJointControlledDeviceJointGroup = exposedJointControlledDeviceGroup->get(exposedJointControlledDeviceJointIdx).asList();
                yCDebug(R2SCB, "*** %s", exposedJointControlledDeviceJointGroup->toString().c_str());

                if(!exposedJointControlledDevice->addControlledDeviceJoint(exposedJointControlledDeviceJointGroup))
                    return false;
            }
        }

        idx++;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::close()
{
    for(size_t i=0;i<controlledDevices.size();i++)
    {
        controlledDevices[i]->close();
        delete controlledDevices[i];
        controlledDevices[i] = 0;
    }
    for(size_t i=0;i<exposedJoints.size();i++)
    {
        delete exposedJoints[i];
        exposedJoints[i] = 0;
    }
    return true;
}

// -----------------------------------------------------------------------------
