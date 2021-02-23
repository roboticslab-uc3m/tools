#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>

#include "ControlboardStateToIPosition.hpp"

/**
 *
 * @ingroup roboticslab-tools-programs
 *
 * \defgroup controlboardStateToIPosition controlboardStateToIPosition
 *
 * @brief Creates an instance of roboticslab::ControlboardStateToIPosition.
 *
 */

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

    yInfo() << "Run \"controlboardStateToIPosition --help\" for options";
    yInfo() << "Checking for yarp network...";
    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork()) {
        yError() << "Found no yarp network (try running \"yarpserver &\"), bye!";
        return 1;
    }

    return mod.runModule(rf);
}
