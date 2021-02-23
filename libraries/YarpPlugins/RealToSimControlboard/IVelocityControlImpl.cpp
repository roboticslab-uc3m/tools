// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <yarp/os/LogStream.h>

// ------------------ IVelocityControl Related ----------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(int j, double sp)
{
    yTrace();
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(const double *sp)
{
    yTrace();
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= velocityMove(i,sp[i]);
    return ok;
}

// ----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(const int n_joint, const int *joints, const double *spds)
{
    yTrace();
    bool ok = true;
    for(int i=0;i<n_joint;i++)
        ok &= velocityMove(joints[i],spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocity(const int joint, double *vel)
{
    yError() << "getRefVelocity() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocities(double *vels)
{
    yError() << "getRefVelocities() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocities(const int n_joint, const int *joints, double *vels)
{
    yError() << "getRefVelocities() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------
