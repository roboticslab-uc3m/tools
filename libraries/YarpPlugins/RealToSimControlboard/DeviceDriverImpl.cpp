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
    yarp::os::Bottle* remotesList = config.find("remotes").asList();
    if (!remotesList)
    {
        CD_ERROR("Error parsing parameters: \"remotes\" should be followed by a list\n");
        return false;
    }
    CD_DEBUG("%s\n", remotesList->toString().c_str());

    std::map<std::string,int> remoteNameToIdx;
    for(size_t i=0; i< remotesList->size(); i++)
    {
        std::string remoteGroupName = remotesList->get(i).asString();
        if(!config.check(remoteGroupName))
        {
            CD_ERROR("\"%s\" group not found!\n", remoteGroupName.c_str());
            return false;
        }
        CD_SUCCESS("\"%s\" group found!\n", remoteGroupName.c_str());
        yarp::os::Bottle remoteGroup = config.findGroup(remoteGroupName);
        CD_INFO("%s\n", remoteGroup.toString().c_str());
        yarp::os::Property options;
        options.fromString(remoteGroup.toString());

        yarp::dev::PolyDriver* remoteControlboard = new yarp::dev::PolyDriver(options);
        if( ! remoteControlboard->isValid() )
        {
            CD_ERROR("\"%s\" group did not create a valid yarp plugin!\n", remoteGroupName.c_str());
            return false;
        }
        CD_SUCCESS("\"%s\" group created a valid yarp plugin!\n", remoteGroupName.c_str());

        remoteNameToIdx[remoteGroupName] = i;
        remoteControlboards.push_back(remoteControlboard);
    }

    int idx = 0;
    while(true)
    {
        std::ostringstream exposedGroupName("exposed_joint_", std::ios_base::app);
        exposedGroupName << idx;
        if(!config.check(exposedGroupName.str()))
        {
            axes = idx;
            CD_INFO("Could not find \"%s\" group, setting number of exposed joints to %d.\n",exposedGroupName.str().c_str(), axes);
            break;
        }
        CD_SUCCESS("\"%s\" group found!\n", exposedGroupName.str().c_str());
        ExposedJoint* exposedJoint = new ExposedJoint(exposedGroupName.str());
        exposedJoints.push_back(exposedJoint);;
        yarp::os::Bottle exposedGroup = config.findGroup(exposedGroupName.str());
        CD_INFO("%s\n", exposedGroup.toString().c_str());
        for(size_t remoteGroupIdx=1; remoteGroupIdx< exposedGroup.size(); remoteGroupIdx++)
        {
            yarp::os::Bottle* remoteGroup = exposedGroup.get(remoteGroupIdx).asList();
            CD_DEBUG("%s\n", remoteGroup->toString().c_str());
            std::string remoteName = remoteGroup->get(0).asString();
            CD_DEBUG("* %s [%d]\n", remoteName.c_str(), remoteNameToIdx[remoteName]);
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
    for(size_t i=0;i<remoteControlboards.size();i++)
    {
        remoteControlboards[i]->close();
        delete remoteControlboards[i];
        remoteControlboards[i] = 0;
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
