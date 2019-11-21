// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <sstream>

namespace roboticslab
{

// ------------------- DeviceDriver Related ------------------------------------

bool RealToSimControlboard::open(yarp::os::Searchable& config)
{
    CD_DEBUG("config: %s\n",config.toString().c_str());

    if(!config.check("remotes", "list of remotes to which this device connects"))
    {
        CD_ERROR("Required \"remotes\" list\n");
        return false;
    }
    yarp::os::Bottle* controlledDeviceList = config.find("remotes").asList();
    if (!controlledDeviceList)
    {
        CD_ERROR("Error parsing parameters: \"remotes\" should be followed by a list\n");
        return false;
    }
    CD_DEBUG("%s\n", controlledDeviceList->toString().c_str());

    std::map<std::string,int> controlledDeviceNameToIdx;
    for(size_t controlledDeviceIdx=0; controlledDeviceIdx< controlledDeviceList->size(); controlledDeviceIdx++)
    {
        std::string controlledDeviceName = controlledDeviceList->get(controlledDeviceIdx).asString();
        if(!config.check(controlledDeviceName))
        {
            CD_ERROR("\"%s\" group not found!\n", controlledDeviceName.c_str());
            return false;
        }
        CD_SUCCESS("\"%s\" group found!\n", controlledDeviceName.c_str());
        yarp::os::Bottle controlledDeviceGroup = config.findGroup(controlledDeviceName);
        CD_INFO("%s\n", controlledDeviceGroup.toString().c_str());
        yarp::os::Property controlledDeviceOptions;
        controlledDeviceOptions.fromString(controlledDeviceGroup.toString());

        yarp::dev::PolyDriver* controlledDevice = new yarp::dev::PolyDriver(controlledDeviceOptions);
        if( ! controlledDevice->isValid() )
        {
            CD_ERROR("\"%s\" group did not create a valid yarp device!\n", controlledDeviceName.c_str());
            return false;
        }
        CD_SUCCESS("\"%s\" group created a valid yarp device!\n", controlledDeviceName.c_str());

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
            CD_INFO("Could not find \"%s\" group, setting number of exposed joints to %d.\n",exposedJointName.c_str(), axes);
            break;
        }
        CD_SUCCESS("\"%s\" group found!\n", exposedJointName.c_str());
        ExposedJoint* exposedJoint = new ExposedJoint(exposedJointName);
        exposedJoints.push_back(exposedJoint);;
        yarp::os::Bottle exposedGroup = config.findGroup(exposedJointName);
        CD_INFO("%s\n", exposedGroup.toString().c_str());
        for(size_t remoteGroupIdx=1; remoteGroupIdx< exposedGroup.size(); remoteGroupIdx++)
        {
            yarp::os::Bottle* remoteGroup = exposedGroup.get(remoteGroupIdx).asList();
            CD_DEBUG("%s\n", remoteGroup->toString().c_str());
            std::string remoteName = remoteGroup->get(0).asString();
            CD_DEBUG("* %s [%d]\n", remoteName.c_str(), controlledDeviceNameToIdx[remoteName]);
            for(size_t remoteJointIdx=1; remoteJointIdx< remoteGroup->size(); remoteJointIdx++)
            {
                yarp::os::Bottle* b = remoteGroup->get(remoteJointIdx).asList();
                CD_DEBUG("* %s\n", b->toString().c_str());
            }
        }

        idx++;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::close()
{
    CD_INFO("\n");
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

}  // namespace roboticslab
