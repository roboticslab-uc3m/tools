// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

// ------------------- IPositionControl Related --------------------------------

bool roboticslab::RealToSimControlboard::getAxes(int *ax)
{
    *ax = axes;
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(int j, double ref)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(const double *refs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::relativeMove(int j, double delta)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::relativeMove(const double *deltas)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::checkMotionDone(int j, bool *flag)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::checkMotionDone(bool *flag)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeed(int j, double sp)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeeds(const double *spds)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefAcceleration(int j, double acc)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefAccelerations(const double *accs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefSpeed(int j, double *ref)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefSpeeds(double *spds)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAcceleration(int j, double *acc)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAccelerations(double *accs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop(int j)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop()
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(const int n_joint, const int *joints, const double *refs)
{
    CD_INFO("\n");
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= positionMove(joints[i],refs[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::relativeMove(const int n_joint, const int *joints, const double *deltas)
{
    CD_INFO("\n");
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= relativeMove(joints[i],deltas[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::checkMotionDone(const int n_joint, const int *joints, bool *flags)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeeds(const int n_joint, const int *joints, const double *spds)
{
    CD_INFO("\n");
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= setRefSpeed(joints[i],spds[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefAccelerations(const int n_joint, const int *joints, const double *accs)
{
    CD_INFO("\n");
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= setRefAcceleration(joints[i],accs[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefSpeeds(const int n_joint, const int *joints, double *spds)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAccelerations(const int n_joint, const int *joints, double *accs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop(const int n_joint, const int *joints)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPosition(const int joint, double *ref)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPositions(double *refs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPositions(const int n_joint, const int *joints, double *refs)
{
    CD_ERROR("Not implemented yet.\n");
    return true;
}

// -----------------------------------------------------------------------------
