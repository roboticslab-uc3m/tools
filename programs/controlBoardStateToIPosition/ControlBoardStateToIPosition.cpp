#include "ControlBoardStateToIPosition.hpp"

#include <string>
#include <vector>

#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/Value.h>
#include <yarp/dev/IControlMode.h> // Defines VOCAB_CM_POSITION_DIRECT.

using namespace roboticslab;

namespace
{
    YARP_LOG_COMPONENT(CBS2P, "rl.ControlBoardStateToIPosition")
}

constexpr auto DEFAULT_IN = "/teo/rightArm";
constexpr auto DEFAULT_OUT = "/teoSim/rightArm";
constexpr auto DEFAULT_RATE_MS = 20.0;

bool ControlBoardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    std::string inStr = rf.check("in", yarp::os::Value(DEFAULT_IN), "in").asString();
    std::string outStr = rf.check("out", yarp::os::Value(DEFAULT_OUT), "out").asString();

    //-- inRobotDevice
    std::string localInStr("/ControlBoardStateToIPosition");
    localInStr += inStr;

    yarp::os::Property inOptions {
        {"device", yarp::os::Value("remote_controlboard")},
        {"remote", yarp::os::Value(inStr)},
        {"local", yarp::os::Value(localInStr)}
    };

    if (!inRobotDevice.open(inOptions))
    {
        yCError(CBS2P) << "Could not open() inRobotDevice:" << inStr;
        yCError(CBS2P) << "Please review or set --in";
        return false;
    }

    if (!inRobotDevice.view(iEncodersIn))
    {
        yCError(CBS2P) << "Could not view iEncodersIn in:" << inStr;
        return false;
    }

    //-- outRobotDevice
    std::string localOutStr("/ControlBoardStateToIPosition");
    localOutStr += outStr;

    yarp::os::Property options {
        {"device", yarp::os::Value("remote_controlboard")},
        {"remote", yarp::os::Value(outStr)},
        {"local", yarp::os::Value(localOutStr)}
    };

    if (!outRobotDevice.open(options))
    {
        yCError(CBS2P) << "Could not open() outRobotDevice:" << outStr;
        yCError(CBS2P) << "Please review or set --out";
        return false;
    }

    if (!outRobotDevice.view(iControlModeOut))
    {
        yCError(CBS2P) << "Could not view iControlModeOut in:" << outStr;
        return false;
    }

    if (!outRobotDevice.view(iPositionDirectOut))
    {
        yCError(CBS2P) << "Could not view iPositionDirectOut in:" << outStr;
        return false;
    }

    //-- Resize encPoss
    int axes;

    if (!iEncodersIn->getAxes(&axes))
    {
        yCError(CBS2P) << "Failed to iEncodersIn->getAxes()";
    }

    yCInfo(CBS2P) << "iEncodersIn->getAxes() got" << axes << "axes";

    encPoss.resize(axes);

    //-- Set PositionDirect
    std::vector<int> modes(axes, VOCAB_CM_POSITION_DIRECT);

    if (!iControlModeOut->setControlModes(modes.data()))
    {
        yCError(CBS2P) << "Failed to iControlModeOut->setControlModes()";
    }

    yarp::os::PeriodicThread::setPeriod(DEFAULT_RATE_MS * 0.001);

    //-- Start PeriodicThread
    if (!yarp::os::PeriodicThread::start())
    {
        yCError(CBS2P) << "Could not start thread";
    }

    yCInfo(CBS2P) << "Started thread";
    return true;
}

bool ControlBoardStateToIPosition::close()
{
    yarp::os::PeriodicThread::stop();
    inRobotDevice.close();
    outRobotDevice.close();
    return true;
}

bool ControlBoardStateToIPosition::updateModule()
{
    yCInfo(CBS2P) << "Alive...";
    return true;
}

void ControlBoardStateToIPosition::run()
{
    if (!iEncodersIn->getEncoders(encPoss.data()))
    {
        yCWarning(CBS2P) << "Failed iEncodersIn->getEncoders()";
        return;
    }

    yCDebug(CBS2P) << "Got in:" << encPoss;

    if (!iPositionDirectOut->setPositions(encPoss.data()))
    {
        yCWarning(CBS2P) << "Failed iPositionDirectOut->setPositions()";
        return;
    }
}
