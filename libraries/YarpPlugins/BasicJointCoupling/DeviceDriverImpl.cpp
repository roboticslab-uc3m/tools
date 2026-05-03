// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

// ------------------- DeviceDriver Related ------------------------------------

bool BasicJointCoupling::open(yarp::os::Searchable & config)
{
    if (!parseParams(config))
    {
        yCError(BJC) << "Failed to parse parameters";
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
