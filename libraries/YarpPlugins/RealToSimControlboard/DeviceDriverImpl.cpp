// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

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
            CD_ERROR("yarp plugin not valid.\n");
            return false;
        }
        CD_SUCCESS("Valid yarp plugin.\n");

        remoteControlboards.push_back(remoteControlboard);
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
    return true;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
