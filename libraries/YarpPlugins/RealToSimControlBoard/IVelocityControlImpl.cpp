// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IVelocityControl Related ----------------------------------------

bool RealToSimControlBoard::velocityMove(int j, double sp)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "velocityMove() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::velocityMove(const double * sp)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= velocityMove(i, sp[i]);
    }

    return ok;
}

// ----------------------------------------------------------------------------

bool RealToSimControlBoard::velocityMove(int n_joint, const int * joints, const double * spds)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= velocityMove(joints[i], spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocity(int j, double * vel)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "getRefVelocity() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocities(double * vels)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getRefVelocity(i, &vels[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefVelocities(int n_joint, const int * joints, double * vels)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getRefVelocity(joints[i], &vels[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------
