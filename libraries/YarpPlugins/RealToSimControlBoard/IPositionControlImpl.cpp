// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------- IPositionControl Related --------------------------------

bool RealToSimControlBoard::getAxes(int * ax)
{
    *ax = axes;
    return true;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(int j, double ref)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    storedPositions[j] = ref;
    return exposedJoints[j]->positionMove(ref);
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(const double * refs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= positionMove(i, refs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(int j, double delta)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "relativeMove() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(const double * deltas)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= relativeMove(i, deltas[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(int j, bool * flag)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "checkMotionDone() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(bool * flag)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= checkMotionDone(i, &flag[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeed(int j, double sp)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "setRefSpeed() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeeds(const double * spds)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= setRefSpeed(i, spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAcceleration(int j, double acc)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "setRefAcceleration() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAccelerations(const double * accs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= setRefAcceleration(i, accs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeed(int j, double * ref)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "getRefSpeed() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeeds(double * spds)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getRefSpeed(i, &spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAcceleration(int j, double * acc)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "getRefAcceleration() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAccelerations(double * accs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getRefAcceleration(i, &accs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop(int j)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "stop() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop()
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= stop(i);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::positionMove(int n_joint, const int * joints, const double * refs)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= positionMove(joints[i], refs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::relativeMove(int n_joint, const int * joints, const double * deltas)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= relativeMove(joints[i], deltas[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::checkMotionDone(int n_joint, const int * joints, bool * flags)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= checkMotionDone(joints[i], &flags[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefSpeeds(int n_joint, const int * joints, const double * spds)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= setRefSpeed(joints[i], spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::setRefAccelerations(int n_joint, const int * joints, const double * accs)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= setRefAcceleration(joints[i], accs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefSpeeds(int n_joint, const int * joints, double * spds)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getRefSpeed(joints[i], &spds[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getRefAccelerations(int n_joint, const int * joints, double * accs)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getRefAcceleration(joints[i], &accs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::stop(int n_joint, const int * joints)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= stop(joints[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPosition(int j, double * ref)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return false;
    }

    yCError(R2SCB) << "getTargetPosition() not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPositions(double * refs)
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getTargetPosition(i, &refs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------

bool RealToSimControlBoard::getTargetPositions(int n_joint, const int * joints, double * refs)
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getTargetPosition(joints[i], &refs[i]);
    }

    return ok;
}

// -----------------------------------------------------------------------------
