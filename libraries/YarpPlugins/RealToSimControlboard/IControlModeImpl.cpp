// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <yarp/os/LogStream.h>

// ------------------ IControlMode Related ----------------------------------------

bool roboticslab::RealToSimControlboard::getControlMode(int j, int * mode)
{
    if (controlMode == POSITION_MODE)
    {
        *mode = VOCAB_CM_POSITION;
    }
    else if (controlMode == VELOCITY_MODE)
    {
        *mode = VOCAB_CM_VELOCITY;
    }
    else if (controlMode == POSITION_DIRECT_MODE)
    {
        *mode = VOCAB_CM_POSITION_DIRECT;
    }
    else
    {
        yError() << "Currently unsupported mode";
        return false;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getControlModes(int * modes)
{
    bool ok = true;

    for (unsigned int i = 0; i < axes; i++)
    {
        ok &= getControlMode(i, &modes[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getControlModes(int n_joint, const int * joints, int * modes)
{
    bool ok = true;

    for (int i = 0; i < n_joint; i++)
    {
        ok &= getControlMode(joints[i], &modes[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setControlMode(int j, const int mode)
{
    if ((unsigned int)j > axes)
    {
        yError() << "Axis index greater than number of than axes";
        return false;
    }

    switch (mode)
    {
    case VOCAB_CM_POSITION:
        controlMode = POSITION_MODE;
        return true;
    case VOCAB_CM_VELOCITY:
        controlMode = VELOCITY_MODE;
        return true;
    case VOCAB_CM_POSITION_DIRECT:
        controlMode = POSITION_DIRECT_MODE;
        return true;
    default:
        return false;
    }
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setControlModes(int n_joint, const int * joints, int * modes)
{
    bool ok = true;

    for (unsigned int i = 0; i < axes; i++)
    {
        ok &= setControlMode(i, modes[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setControlModes(int * modes)
{
    return true;
}

// -----------------------------------------------------------------------------
