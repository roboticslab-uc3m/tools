#include "ControlboardStateToIPosition.hpp"

#include <string>
#include <vector>

#include <yarp/os/Property.h>
#include <yarp/os/Value.h>
#include <yarp/dev/IControlMode.h> // Defines VOCAB_CM_POSITION_DIRECT.

#include <ColorDebug.hpp>

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
        CD_ERROR("Could not open() inRobotDevice: %s\n", inStr.c_str());
        CD_ERROR("Please review or set --in\n");
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
    std::string localOutStr("/ControlboardStateToIPosition");
    localOutStr += outStr;

    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",outStr);
    options.put("local",localOutStr);

    if( ! outRobotDevice.open(options) )
    {
        CD_ERROR("Could not open() outRobotDevice: %s\n", outStr.c_str());
        CD_ERROR("Please review or set --out\n");
        inRobotDevice.close();
        outRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }

    if( ! outRobotDevice.view(iControlMode2Out) )
    {
        CD_ERROR("Could not view iControlMode2Out in: %s.\n", outStr.c_str());
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
        CD_ERROR("Failed to iEncodersIn->getAxes.\n");
    }
    CD_SUCCESS("iEncodersIn->getAxes got %d axes.\n",axes);

    encPoss.resize(axes);

    //-- Set PositionDirect
    std::vector<int> modes(axes,VOCAB_CM_POSITION_DIRECT);
    if( ! iControlMode2Out->setControlModes( modes.data() ) )
    {
        CD_ERROR("Failed to iControlMode2Out->setControlModes.\n");
    }
    CD_SUCCESS("iEncodersIn->getAxes got %d axes.\n",axes);


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
    if( ! iEncodersIn->getEncoders( encPoss.data() ) )
    {
        CD_WARNING("Failed iEncodersIn->getEncoders\n");
        return;
    }

    CD_DEBUG("Got in:");
    for(size_t i=0;i<encPoss.size();i++)
        CD_DEBUG_NO_HEADER(" %f", encPoss[i]);
    CD_DEBUG_NO_HEADER("\n");

    if( ! iPositionDirectOut->setPositions( encPoss.data() ) )
    {
        CD_WARNING("Failed iPositionDirectOut->setPositions\n");
        return;
    }

    return;
}

}  // namespace roboticslab
