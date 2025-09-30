// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IEncodersTimed Related -----------------------------------------

bool RealToSimControlBoard::getEncodersTimed(double * encs, double * time)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderTimed(i, &encs[i], &time[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderTimed(int j, double * encs, double * time)
{
    bool ok = getEncoder(j, encs);
    *time = yarp::os::Time::now();
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::resetEncoder(int j)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    return setEncoder(j, 0.0);
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::resetEncoders()
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= resetEncoder(i);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setEncoder(int j, double val)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "setEncoder() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setEncoders(const double * vals)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= setEncoder(i, vals[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoder(int j, double * v)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    *v = storedPositions[j];
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoders(double * encs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoder(i, &encs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderSpeed(int j, double * sp)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    // Make it easy, give the current reference speed.
    *sp = 0; // begins to look like we should use semaphores.
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderSpeeds(double * spds)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderSpeed(i, &spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderAcceleration(int j, double * acc)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "getEncoderAcceleration not implemented";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderAccelerations(double * accs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderAcceleration(i, &accs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------
