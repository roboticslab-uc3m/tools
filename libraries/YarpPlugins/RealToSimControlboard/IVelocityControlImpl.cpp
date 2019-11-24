// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

// ------------------ IVelocityControl Related ----------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(int j, double sp) {  // velExposed = sp;

    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(const double *sp) {
    CD_INFO("\n");
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= velocityMove(i,sp[i]);
    return ok;
}

// ----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::velocityMove(const int n_joint, const int *joints, const double *spds)
{
    CD_INFO("\n");
    bool ok = true;
    for(int i=0;i<n_joint;i++)
        ok &= velocityMove(joints[i],spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocity(const int joint, double *vel)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocities(double *vels)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefVelocities(const int n_joint, const int *joints, double *vels)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setVelPid(int j, const yarp::dev::Pid &pid)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setVelPids(const yarp::dev::Pid *pids)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getVelPid(int j, yarp::dev::Pid *pid)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getVelPids(yarp::dev::Pid *pids)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------
