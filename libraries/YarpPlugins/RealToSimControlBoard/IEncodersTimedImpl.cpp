// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

using namespace roboticslab;

// ------------------ IEncodersTimed Related -----------------------------------------

bool RealToSimControlBoard::getEncodersTimed(double *encs, double *time)
{
    bool ok = true;
    for(unsigned int i=0; i < axes; i++)
        ok &= getEncoderTimed(i,&(encs[i]),&(time[i]));
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderTimed(int j, double *encs, double *time)
{
    getEncoder(j, encs);
    *time = yarp::os::Time::now();
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::resetEncoder(int j)
{
    if ((unsigned int)j>axes) return false;
    return setEncoder(j,0.0);
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::resetEncoders()
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= resetEncoder(i);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setEncoder(int j, double val)
{
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setEncoders(const double *vals)
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= setEncoder(i,vals[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoder(int j, double *v)
{
    *v = storedPositions[j];
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoders(double *encs)
{
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= getEncoder(i,&encs[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderSpeed(int j, double *sp)
{
    // Make it easy, give the current reference speed.
    *sp = 0;  // begins to look like we should use semaphores.
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderSpeeds(double *spds)
{
    bool ok = true;
    //for(unsigned int i=0;i<axes;i++)
    //    ok &= getEncoderSpeed(i,&spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderAcceleration(int j, double *spds)
{
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getEncoderAccelerations(double *accs)
{
    return false;
}

// -----------------------------------------------------------------------------


