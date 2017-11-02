#include "ControlboardStateToIPosition.hpp"
#include "ColorDebug.hpp"

namespace roboticslab
{

bool ControlboardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    std::string remoteStr = rf.check("remote",yarp::os::Value(DEFAULT_REMOTE),"remote out").asString();

    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",remoteStr);
    options.put("local","/local");

    robotDevice.open(options);
    if( ! robotDevice.isValid() )
    {
        CD_ERROR("Device not valid.\n");
        robotDevice.close();
        yarp::os::Network::fini();
        return false;
    }
    if( ! robotDevice.view(iPositionControl) )
    {
        CD_ERROR("Could not view iPositionControl in: %s.\n", remoteStr.c_str());
        return false;
    }

    return true;
}


bool ControlboardStateToIPosition::updateModule()
{
    CD_INFO("Alive...\n");
    return true;
}

}
