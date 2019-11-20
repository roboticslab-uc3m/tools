// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

namespace roboticslab
{

// ------------------- DeviceDriver Related ------------------------------------

bool RealToSimControlboard::open(yarp::os::Searchable& config)
{
    CD_DEBUG("config: %s\n",config.toString().c_str());

    yarp::dev::PolyDriver* remoteControlboard = new yarp::dev::PolyDriver;

    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("local","/realToSimControlboard/teoSim/leftLacqueyFetch/externalFinger");
    options.put("remote","/teoSim/leftLacqueyFetch/externalFinger");
    remoteControlboard->open(options);

    if( ! remoteControlboard->isValid() )
    {
        CD_ERROR("yarp plugin not valid.\n");
        return false;
    }
    CD_SUCCESS("Valid yarp plugin.\n");

    remoteControlboards.push_back(remoteControlboard);

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
