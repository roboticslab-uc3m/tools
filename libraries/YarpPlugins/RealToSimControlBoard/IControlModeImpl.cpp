// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlBoard.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// ------------------ IControlMode Related ----------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getAvailableControlModes(int j, std::vector<yarp::dev::SelectableControlModeEnum> & avail)
{
    if (j < 0 || static_cast<unsigned int>(j) > axes)
    {
        yCError(R2SCB) << "Illegal axis index:" << j;
        return yarp::dev::ReturnValue_error_input_out_of_bounds;
    }

    avail = {
        yarp::dev::SelectableControlModeEnum::VOCAB_CM_POSITION,
        yarp::dev::SelectableControlModeEnum::VOCAB_CM_POSITION_DIRECT,
        yarp::dev::SelectableControlModeEnum::VOCAB_CM_VELOCITY
    };

    return yarp::dev::ReturnValue_ok;
}
#endif

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getControlMode(int j, yarp::dev::ControlModeEnum & mode)
#else
bool RealToSimControlBoard::getControlMode(int j, int * mode)
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

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    mode = static_cast<yarp::dev::ControlModeEnum>(controlMode);
    return yarp::dev::ReturnValue_ok;
#else
    *mode = controlMode;
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getControlModes(std::vector<yarp::dev::ControlModeEnum> & modes)
#else
bool RealToSimControlBoard::getControlModes(int * modes)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        ok &= getControlMode(i, modes[i]);
#else
        ok &= getControlMode(i, &modes[i]);
#endif
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::getControlModes(const std::vector<int> & joints, std::vector<yarp::dev::ControlModeEnum> & modes)
#else
bool RealToSimControlBoard::getControlModes(int n_joint, const int * joints, int * modes)
#endif
{
    bool ok = true;

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    for (auto i = 0; i < joints.size(); i++)
    {
        ok &= getControlMode(joints[i], modes[i]);
    }
#else
    for (auto i = 0; i < n_joint; i++)
    {
        ok &= getControlMode(joints[i], &modes[i]);
    }
#endif

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setControlMode(int j, yarp::dev::SelectableControlModeEnum mode)
#else
bool RealToSimControlBoard::setControlMode(int j, const int mode)
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

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    controlMode = static_cast<yarp::conf::vocab32_t>(mode);
    return yarp::dev::ReturnValue_ok;
#else
    controlMode = mode;
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setControlModes(const std::vector<yarp::dev::SelectableControlModeEnum> & modes)
#else
bool RealToSimControlBoard::setControlModes(int * modes)
#endif
{
    bool ok = true;

    for (auto i = 0; i < axes; i++)
    {
        ok &= setControlMode(i, modes[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue RealToSimControlBoard::setControlModes(const std::vector<int> & joints, const std::vector<yarp::dev::SelectableControlModeEnum> & modes)
#else
bool RealToSimControlBoard::setControlModes(int n_joint, const int * joints, int * modes)
#endif
{
    bool ok = true;

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    for (auto i = 0; i < joints.size(); i++)
#else
    for (auto i = 0; i < n_joint; i++)
#endif
    {
        ok &= setControlMode(joints[i], modes[i]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return ok ? yarp::dev::ReturnValue_ok : yarp::dev::ReturnValue_error_method_failed;
#else
    return ok;
#endif
}

// -----------------------------------------------------------------------------
