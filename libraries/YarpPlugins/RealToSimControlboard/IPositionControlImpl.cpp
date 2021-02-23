// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <yarp/os/LogStream.h>

// ------------------- IPositionControl Related --------------------------------

bool roboticslab::RealToSimControlboard::getAxes(int *ax)
{
    *ax = axes;
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(int j, double ref)
{
    storedPositions[j] = ref;
    return exposedJoints[j]->positionMove(ref);
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(const double *refs)
{
    bool ok = true;
    for(unsigned int i=0; i < axes; i++)
        ok &= positionMove(i, refs[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::relativeMove(int j, double delta)
{
    yError() << "relativeMove() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::relativeMove(const double *deltas)
{
    yError() << "relativeMove() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::checkMotionDone(int j, bool *flag)
{
    yError() << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::checkMotionDone(bool *flag)
{
    yError() << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeed(int j, double sp)
{
    yError() << "setRefSpeed() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeeds(const double *spds)
{
    yError() << "setRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefAcceleration(int j, double acc)
{
    yError() << "setRefAcceleration() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefAccelerations(const double *accs)
{
    yError() << "setRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefSpeed(int j, double *ref)
{
    yError() << "getRefSpeed() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefSpeeds(double *spds)
{
    yError() << "getRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAcceleration(int j, double *acc)
{
    yError() << "getRefAcceleration() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAccelerations(double *accs)
{
    yError() << "getRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop(int j)
{
    yError() << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop()
{
    yError() << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::positionMove(const int n_joint, const int *joints, const double *refs)
{
    yTrace();
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
    yTrace();
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
    yError() << "checkMotionDone() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setRefSpeeds(const int n_joint, const int *joints, const double *spds)
{
    yTrace();
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
    yTrace();
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
    yError() << "getRefSpeeds() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getRefAccelerations(const int n_joint, const int *joints, double *accs)
{
    yError() << "getRefAccelerations() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::stop(const int n_joint, const int *joints)
{
    yError() << "stop() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPosition(const int joint, double *ref)
{
    yError() << "getTargetPosition() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPositions(double *refs)
{
    yError() << "getTargetPositions() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getTargetPositions(const int n_joint, const int *joints, double *refs)
{
    yError() << "getTargetPositions() not implemented yet";
    return true;
}

// -----------------------------------------------------------------------------
