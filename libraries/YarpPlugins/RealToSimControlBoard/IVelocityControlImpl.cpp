// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IVelocityControl Related ----------------------------------------

bool RealToSimControlBoard::velocityMove(int j, double sp)
{
    yCTrace(R2SCB);
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::velocityMove(const double *sp)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= velocityMove(i,sp[i]);
    return ok;
}

// ----------------------------------------------------------------------------

bool RealToSimControlBoard::velocityMove(const int n_joint, const int *joints, const double *spds)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(int i=0;i<n_joint;i++)
        ok &= velocityMove(joints[i],spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocity(const int joint, double *vel)
{
    yCError(R2SCB) << "getRefVelocity() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocities(double *vels)
{
    yCError(R2SCB) << "getRefVelocities() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocities(const int n_joint, const int *joints, double *vels)
{
    yCError(R2SCB) << "getRefVelocities() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------
