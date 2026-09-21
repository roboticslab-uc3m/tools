// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------- IPositionControl Related --------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getAxes(std::size_t & ax)
{
    ax = axes;
    return yarp::dev::ReturnValue::return_code::return_value_ok;
}
#else
bool RealToSimControlBoard::getAxes(int * ax)
{
    *ax = axes;
    return true;
}
#endif

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::positionMove(int j, double ref)
#else
bool RealToSimControlBoard::positionMove(int j, double ref)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    storedPositions[j] = ref;

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return exposedJoints[j]->positionMove(ref)
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return exposedJoints[j]->positionMove(ref);
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::positionMove(const double * refs)
#else
bool RealToSimControlBoard::positionMove(const double * refs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= positionMove(i, refs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::positionMove(int n_joint, const int * joints, const double * refs)
#else
bool RealToSimControlBoard::positionMove(int n_joint, const int * joints, const double * refs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= positionMove(joints[i], refs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::relativeMove(int j, double delta)
#else
bool RealToSimControlBoard::relativeMove(int j, double delta)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "relativeMove() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::relativeMove(const double * deltas)
#else
bool RealToSimControlBoard::relativeMove(const double * deltas)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= relativeMove(i, deltas[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::relativeMove(int n_joint, const int * joints, const double * deltas)
#else
bool RealToSimControlBoard::relativeMove(int n_joint, const int * joints, const double * deltas)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= relativeMove(joints[i], deltas[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::checkMotionDone(int j, bool & flag)
#else
bool RealToSimControlBoard::checkMotionDone(int j, bool * flag)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "checkMotionDone() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::checkMotionDone(bool & flag)
#else
bool RealToSimControlBoard::checkMotionDone(bool * flag)
#endif
{
    bool ok = true;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    bool done = true;
#endif

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        bool local;
        ok &= checkMotionDone(i, local);
        done &= local;
#else
        ok &= checkMotionDone(i, &flag[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    flag = done;
#endif

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::checkMotionDone(const std::vector<int> & joints, bool & flag)
#else
bool RealToSimControlBoard::checkMotionDone(int n_joint, const int * joints, bool * flags)
#endif
{
    bool ok = true;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    bool done = true;
#endif

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    for (auto i = 0; i < joints.size(); i++)
    {
        bool local;
        ok &= checkMotionDone(joints[i], local);
        done &= local;
    }
#else
    for (auto i = 0; i < n_joint; i++)
    {
        ok &= checkMotionDone(joints[i], &flags[i]);
    }
#endif

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    flag = done;
#endif

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajSpeed(int j, double sp)
#else
bool RealToSimControlBoard::setRefSpeed(int j, double sp)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "setRefSpeed() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajSpeeds(const double * spds)
#else
bool RealToSimControlBoard::setRefSpeeds(const double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= setTrajSpeed(i, spds[i]);
#else
        ok &= setRefSpeed(i, spds[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajSpeeds(int n_joint, const int * joints, const double * spds)
#else
bool RealToSimControlBoard::setRefSpeeds(int n_joint, const int * joints, const double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= setTrajSpeed(joints[i], spds[i]);
#else
        ok &= setRefSpeed(joints[i], spds[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajAcceleration(int j, double acc)
#else
bool RealToSimControlBoard::setRefAcceleration(int j, double acc)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "setRefAcceleration() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajAccelerations(const double * accs)
#else
bool RealToSimControlBoard::setRefAccelerations(const double * accs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= setTrajAcceleration(i, accs[i]);
#else
        ok &= setRefAcceleration(i, accs[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setTrajAccelerations(int n_joint, const int * joints, const double * accs)
#else
bool RealToSimControlBoard::setRefAccelerations(int n_joint, const int * joints, const double * accs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= setTrajAcceleration(joints[i], accs[i]);
#else
        ok &= setRefAcceleration(joints[i], accs[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajSpeed(int j, double * ref)
#else
bool RealToSimControlBoard::getRefSpeed(int j, double * ref)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "getRefSpeed() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajSpeeds(double * spds)
#else
bool RealToSimControlBoard::getRefSpeeds(double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTrajSpeed(i, &spds[i]);
#else
        ok &= getRefSpeed(i, &spds[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajSpeeds(int n_joint, const int * joints, double * spds)
#else
bool RealToSimControlBoard::getRefSpeeds(int n_joint, const int * joints, double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTrajSpeed(joints[i], &spds[i]);
#else
        ok &= getRefSpeed(joints[i], &spds[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajAcceleration(int j, double * acc)
#else
bool RealToSimControlBoard::getRefAcceleration(int j, double * acc)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "getRefAcceleration() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajAccelerations(double * accs)
#else
bool RealToSimControlBoard::getRefAccelerations(double * accs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTrajAcceleration(i, &accs[i]);
#else
        ok &= getRefAcceleration(i, &accs[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTrajAccelerations(int n_joint, const int * joints, double * accs)
#else
bool RealToSimControlBoard::getRefAccelerations(int n_joint, const int * joints, double * accs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTrajAcceleration(joints[i], &accs[i]);
#else
        ok &= getRefAcceleration(joints[i], &accs[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::stop(int j)
#else
bool RealToSimControlBoard::stop(int j)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "stop() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::stop()
#else
bool RealToSimControlBoard::stop()
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= stop(i);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::stop(int n_joint, const int * joints)
#else
bool RealToSimControlBoard::stop(int n_joint, const int * joints)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= stop(joints[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTargetPosition(int j, double * ref)
#else
bool RealToSimControlBoard::getTargetPosition(int j, double * ref)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue::return_code::return_value_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "getTargetPosition() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTargetPositions(double * refs)
#else
bool RealToSimControlBoard::getTargetPositions(double * refs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getTargetPosition(i, &refs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTargetPositions(int n_joint, const int * joints, double * refs)
#else
bool RealToSimControlBoard::getTargetPositions(int n_joint, const int * joints, double * refs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getTargetPosition(joints[i], &refs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------
