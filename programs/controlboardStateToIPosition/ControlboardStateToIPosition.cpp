#include "ControlboardStateToIPosition.hpp"
#include "ColorDebug.hpp"

namespace roboticslab
{

bool ControlboardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    std::string inStr = rf.check("in",yarp::os::Value(DEFAULT_IN),"in").asString();
    std::string outStr = rf.check("out",yarp::os::Value(DEFAULT_OUT),"out").asString();

    //-- inRobotDevice
    yarp::os::Property inOptions;
    inOptions.put("device","remote_controlboard");
    inOptions.put("remote",inStr);
    inOptions.put("local","/in");

    if( ! inRobotDevice.open(inOptions) )
    {
        CD_ERROR("Could not open() input robot device: %s\n", inStr.c_str());
        inRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }

    if( ! inRobotDevice.view(iEncodersIn) )
    {
        CD_ERROR("Could not view iEncodersIn in: %s.\n", inStr.c_str());
        return false;
    }

    //-- outRobotDevice
    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",outStr);
    options.put("local","/out");

    if( ! outRobotDevice.open(options) )
    {
        CD_ERROR("Could not open() output robot device: %s\n", inStr.c_str());
        outRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }

    if( ! outRobotDevice.view(iPositionDirectOut) )
    {
        CD_ERROR("Could not view iPositionDirectOut in: %s.\n", outStr.c_str());
        return false;
    }

    //-- Resize encPoss
    int axes;

    if( ! iEncodersIn->getAxes(&axes) )
    {
        CD_ERROR("Failed to getAxes.\n");
    }
    CD_SUCCESS("iEncodersIn->getAxes got %d axes.\n",axes);

    encPoss.resize(axes);

    //-- Start RateThread
    if( ! this->start() )
    {
        CD_ERROR("Could not start thread.\n");
    }
    CD_SUCCESS("Started thread.\n");

    return true;
}

bool ControlboardStateToIPosition::close()
{
    inRobotDevice.close();
    outRobotDevice.close();

    return true;
}

bool ControlboardStateToIPosition::updateModule()
{
    CD_INFO("Alive...\n");
    return true;
}

void ControlboardStateToIPosition::run()
{
    iEncodersIn->getEncoders( encPoss.data() );

    CD_DEBUG("\n");
    return;
}

}  // namespace
