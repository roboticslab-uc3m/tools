#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>

#include <ColorDebug.hpp>

#include "ControlboardStateToIPosition.hpp"

int main(int argc, char *argv[])
{
    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("controlboardStateToIPosition");
    rf.setDefaultConfigFile("controlboardStateToIPosition.ini");
    rf.configure(argc,argv);

    roboticslab::ControlboardStateToIPosition mod;
    if(rf.check("help")) {
        return mod.runModule(rf);
    }

    CD_INFO("Run \"controlboardStateToIPosition --help\" for options.\n");
    CD_INFO("Checking for yarp network...\n");
    yarp::os::Network yarp;
    if (!yarp::os::Network::checkNetwork()) {
        CD_ERROR("Found no yarp network (try running \"yarpserver &\"), bye!\n");
        return 1;
    }
    CD_SUCCESS("Yarp network found.\n");

    return mod.runModule(rf);
}
