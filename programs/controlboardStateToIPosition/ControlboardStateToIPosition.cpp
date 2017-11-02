#include "ControlboardStateToIPosition.hpp"
#include "ColorDebug.hpp"

namespace roboticslab
{

bool ControlboardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    std::string inputStr = rf.check("input",yarp::os::Value(DEFAULT_INPUT),"input port").asString();
    std::string remoteStr = rf.check("remote",yarp::os::Value(DEFAULT_REMOTE),"remote out").asString();

    //-- outRobotDevice
    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",remoteStr);
    options.put("local","/ControlboardStateToIPosition");

    outRobotDevice.open(options);
    if( ! outRobotDevice.isValid() )
    {
        CD_ERROR("Device not valid.\n");
        outRobotDevice.close();
        yarp::os::Network::fini();
        return false;
    }
    if( ! outRobotDevice.view(inStreamPort.iPositionControl) )
    {
        CD_ERROR("Could not view iPositionControl in: %s.\n", remoteStr.c_str());
        return false;
    }

    //-- inStreamPort
    inStreamPort.open(inputStr);
    inStreamPort.useCallback();

    return true;
}


bool ControlboardStateToIPosition::updateModule()
{
    CD_INFO("Alive...\n");
    return true;
}

}
