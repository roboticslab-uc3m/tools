#include "ControlboardStateToIPosition.hpp"

#include <string>
#include <vector>

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/Value.h>
#include <yarp/dev/IControlMode.h> // Defines VOCAB_CM_POSITION_DIRECT.

namespace roboticslab
{

bool ControlboardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    std::string inStr = rf.check("in",yarp::os::Value(DEFAULT_IN),"in").asString();
    std::string outStr = rf.check("out",yarp::os::Value(DEFAULT_OUT),"out").asString();

    //-- inRobotDevice
    std::string localInStr("/ControlboardStateToIPosition");
    localInStr += inStr;

    yarp::os::Property inOptions;
    inOptions.put("device","remote_controlboard");
    inOptions.put("remote",inStr);
    inOptions.put("local",localInStr);

    if( ! inRobotDevice.open(inOptions) )
    {
        yError() << "Could not open() inRobotDevice:" << inStr;
        yError() << "Please review or set --in";
        return false;
    }

    if( ! inRobotDevice.view(iEncodersIn) )
    {
        yError() << "Could not view iEncodersIn in:" << inStr;
        return false;
    }

    //-- outRobotDevice
    std::string localOutStr("/ControlboardStateToIPosition");
    localOutStr += outStr;

    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",outStr);
    options.put("local",localOutStr);

    if( ! outRobotDevice.open(options) )
    {
        yError() << "Could not open() outRobotDevice:" << outStr;
        yError() << "Please review or set --out";
        return false;
    }

    if( ! outRobotDevice.view(iControlModeOut) )
    {
        yError() << "Could not view iControlModeOut in:" << outStr;
        return false;
    }
    if( ! outRobotDevice.view(iPositionDirectOut) )
    {
        yError() << "Could not view iPositionDirectOut in:" << outStr;
        return false;
    }

    //-- Resize encPoss
    int axes;

    if( ! iEncodersIn->getAxes(&axes) )
    {
        yError() << "Failed to iEncodersIn->getAxes()";
    }
    yInfo() << "iEncodersIn->getAxes() got" << axes << "axes";

    encPoss.resize(axes);

    //-- Set PositionDirect
    std::vector<int> modes(axes,VOCAB_CM_POSITION_DIRECT);
    if( ! iControlModeOut->setControlModes( modes.data() ) )
    {
        yError() << "Failed to iControlModeOut->setControlModes()";
    }

    //-- Start PeriodicThread
    if( ! this->start() )
    {
        yError() << "Could not start thread";
    }
    yInfo() << "Started thread";

    return true;
}

bool ControlboardStateToIPosition::close()
{
    this->stop();
    inRobotDevice.close();
    outRobotDevice.close();
    return true;
}

bool ControlboardStateToIPosition::updateModule()
{
    yInfo() << "Alive...";
    return true;
}

void ControlboardStateToIPosition::run()
{
    if( ! iEncodersIn->getEncoders( encPoss.data() ) )
    {
        yWarning() << "Failed iEncodersIn->getEncoders()";
        return;
    }

    yDebug() << "Got in:" << encPoss;

    if( ! iPositionDirectOut->setPositions( encPoss.data() ) )
    {
        yWarning() << "Failed iPositionDirectOut->setPositions()";
        return;
    }
}

}  // namespace roboticslab
