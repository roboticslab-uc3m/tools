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
        CD_ERROR("Could not open() input robot device.\n");
        inRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }

    //-- outRobotDevice
    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",outStr);
    options.put("local","/out");

    if( ! outRobotDevice.open(options) )
    {
        CD_ERROR("Could not open() output robot device.\n");
        outRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }
    /*if( ! outRobotDevice.view(inStreamPort.iPositionDirect) )
    {
        CD_ERROR("Could not view iPositionControl in: %s.\n", remoteStr.c_str());
        return false;
    }*/


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

}
