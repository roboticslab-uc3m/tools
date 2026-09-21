// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IVelocityControl Related ----------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::velocityMove(int j, double sp)
#else
bool RealToSimControlBoard::velocityMove(int j, double sp)
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

    yCError(R2SCB) << "velocityMove() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::velocityMove(const double * sp)
#else
bool RealToSimControlBoard::velocityMove(const double * sp)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= velocityMove(i, sp[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok
        ? yarp::dev::ReturnValue::return_code::return_value_ok
        : yarp::dev::ReturnValue::return_code::return_value_error_method_failed;
#else
    return ok;
#endif
}

// ----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::velocityMove(int n_joint, const int * joints, const double * spds)
#else
bool RealToSimControlBoard::velocityMove(int n_joint, const int * joints, const double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
        ok &= velocityMove(joints[i], spds[i]);
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
yarp::dev::ReturnValue RealToSimControlBoard::getTargetVelocity(int j, double * vel)
#else
bool RealToSimControlBoard::getRefVelocity(int j, double * vel)
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

    yCError(R2SCB) << "getRefVelocity() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue::return_code::return_value_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getTargetVelocities(double * vels)
#else
bool RealToSimControlBoard::getRefVelocities(double * vels)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTargetVelocity(i, &vels[i]);
#else
        ok &= getRefVelocity(i, &vels[i]);
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
yarp::dev::ReturnValue RealToSimControlBoard::getTargetVelocities(int n_joint, const int * joints, double * vels)
#else
bool RealToSimControlBoard::getRefVelocities(int n_joint, const int * joints, double * vels)
#endif
{
    bool ok = true;

    for (auto i = 0; i < n_joint; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getTargetVelocity(joints[i], &vels[i]);
#else
        ok &= getRefVelocity(joints[i], &vels[i]);
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
