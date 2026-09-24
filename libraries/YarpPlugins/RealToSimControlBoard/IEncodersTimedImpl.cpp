// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IEncodersTimed Related -----------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncodersTimed(double * encs, double * time)
#else
bool RealToSimControlBoard::getEncodersTimed(double * encs, double * time)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderTimed(i, &encs[i], &time[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoderTimed(int j, double * encs, double * time)
#else
bool RealToSimControlBoard::getEncoderTimed(int j, double * encs, double * time)
#endif
{
    bool ok = getEncoder(j, encs);
    *time = yarp::os::Time::now();

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::resetEncoder(int j)
#else
bool RealToSimControlBoard::resetEncoder(int j)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    return setEncoder(j, 0.0);
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::resetEncoders()
#else
bool RealToSimControlBoard::resetEncoders()
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= resetEncoder(i);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setEncoder(int j, double val)
#else
bool RealToSimControlBoard::setEncoder(int j, double val)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "setEncoder() not implemented yet";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setEncoders(const double * vals)
#else
bool RealToSimControlBoard::setEncoders(const double * vals)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= setEncoder(i, vals[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoder(int j, double * v)
#else
bool RealToSimControlBoard::getEncoder(int j, double * v)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    *v = storedPositions[j];
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoders(double * encs)
#else
bool RealToSimControlBoard::getEncoders(double * encs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoder(i, &encs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoderSpeed(int j, double * sp)
#else
bool RealToSimControlBoard::getEncoderSpeed(int j, double * sp)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    // Make it easy, give the current reference speed.
    *sp = 0; // begins to look like we should use semaphores.
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoderSpeeds(double * spds)
#else
bool RealToSimControlBoard::getEncoderSpeeds(double * spds)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderSpeed(i, &spds[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoderAcceleration(int j, double * acc)
#else
bool RealToSimControlBoard::getEncoderAcceleration(int j, double * acc)
#endif
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
#else
        return false;
#endif
    }

    yCError(R2SCB) << "getEncoderAcceleration not implemented";
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_error_not_implemented_by_device;
#else
    return false;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getEncoderAccelerations(double * accs)
#else
bool RealToSimControlBoard::getEncoderAccelerations(double * accs)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= getEncoderAcceleration(i, &accs[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------
