// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

namespace roboticslab
{

// ------------------- DeviceDriver Related ------------------------------------

bool RealToSimControlboard::open(yarp::os::Searchable& config)
{
    CD_DEBUG("config: %s\n",config.toString().c_str());

    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::close()
{
    CD_INFO("\n");
    return true;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
