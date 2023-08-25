// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------- IPositionControl Related --------------------------------

bool RealToSimControlBoard::getAxes(int *ax)
{
    *ax = axes;
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(int j, double ref)
{
    storedPositions[j] = ref;
    return exposedJoints[j]->positionMove(ref);
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(const double *refs)
{
    bool ok = true;
    for(unsigned int i=0; i < axes; i++)
        ok &= positionMove(i, refs[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(int j, double delta)
{
    yCError(R2SCB) << "relativeMove() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(const double *deltas)
{
    yCError(R2SCB) << "relativeMove() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(int j, bool *flag)
{
    yCError(R2SCB) << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(bool *flag)
{
    yCError(R2SCB) << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeed(int j, double sp)
{
    yCError(R2SCB) << "setRefSpeed() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeeds(const double *spds)
{
    yCError(R2SCB) << "setRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAcceleration(int j, double acc)
{
    yCError(R2SCB) << "setRefAcceleration() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAccelerations(const double *accs)
{
    yCError(R2SCB) << "setRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeed(int j, double *ref)
{
    yCError(R2SCB) << "getRefSpeed() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeeds(double *spds)
{
    yCError(R2SCB) << "getRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAcceleration(int j, double *acc)
{
    yCError(R2SCB) << "getRefAcceleration() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAccelerations(double *accs)
{
    yCError(R2SCB) << "getRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop(int j)
{
    yCError(R2SCB) << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop()
{
    yCError(R2SCB) << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(const int n_joint, const int *joints, const double *refs)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= positionMove(joints[i],refs[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(const int n_joint, const int *joints, const double *deltas)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= relativeMove(joints[i],deltas[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(const int n_joint, const int *joints, bool *flags)
{
    yCError(R2SCB) << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeeds(const int n_joint, const int *joints, const double *spds)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= setRefSpeed(joints[i],spds[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAccelerations(const int n_joint, const int *joints, const double *accs)
{
    yCTrace(R2SCB);
    bool ok = true;
    for(int i=0;i<n_joint;i++)
    {
        ok &= setRefAcceleration(joints[i],accs[i]);
    }
    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeeds(const int n_joint, const int *joints, double *spds)
{
    yCError(R2SCB) << "getRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAccelerations(const int n_joint, const int *joints, double *accs)
{
    yCError(R2SCB) << "getRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop(const int n_joint, const int *joints)
{
    yCError(R2SCB) << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPosition(const int joint, double *ref)
{
    yCError(R2SCB) << "getTargetPosition() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPositions(double *refs)
{
    yCError(R2SCB) << "getTargetPositions() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPositions(const int n_joint, const int *joints, double *refs)
{
    yCError(R2SCB) << "getTargetPositions() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------
