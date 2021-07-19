// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

using namespace roboticslab;

// ------------------ IEncodersTimed Related -----------------------------------------

bool RealToSimControlboard::getEncodersTimed(double *encs, double *time)
{
    bool ok = true;
    for(unsigned int i=0; i < axes; i++)
        ok &= getEncoderTimed(i,&(encs[i]),&(time[i]));
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoderTimed(int j, double *encs, double *time)
{
    getEncoder(j, encs);
    *time = yarp::os::Time::now();
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::resetEncoder(int j)
{
    if ((unsigned int)j>axes) return false;
    return setEncoder(j,0.0);
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::resetEncoders()
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= resetEncoder(i);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::setEncoder(int j, double val)
{
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::setEncoders(const double *vals)
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= setEncoder(i,vals[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoder(int j, double *v)
{
    *v = storedPositions[j];
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoders(double *encs)
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= getEncoder(i,&encs[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoderSpeed(int j, double *sp)
{
    // Make it easy, give the current reference speed.
    *sp = 0;  // begins to look like we should use semaphores.
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoderSpeeds(double *spds)
{
    bool ok = true;
    //for(unsigned int i=0;i<axes;i++)
    //    ok &= getEncoderSpeed(i,&spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoderAcceleration(int j, double *spds)
{
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlboard::getEncoderAccelerations(double *accs)
{
    return false;
}

// -----------------------------------------------------------------------------


