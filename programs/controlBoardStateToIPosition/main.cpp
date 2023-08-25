#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>

#include "ControlBoardStateToIPosition.hpp"

/**
 *
 * @ingroup roboticslab-tools-programs
 *
 * \defgroup controlBoardStateToIPosition controlBoardStateToIPosition
 *
 * @brief Creates an instance of roboticslab::ControlBoardStateToIPosition.
 *
 */

int main(int argc, char *argv[])
{
    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("controlBoardStateToIPosition");
    rf.setDefaultConfigFile("controlBoardStateToIPosition.ini");
    rf.configure(argc,argv);

    roboticslab::ControlBoardStateToIPosition mod;
    if (rf.check("help"))
    {
        return mod.runModule(rf);
    }

    yInfo() << "Run \"controlBoardStateToIPosition --help\" for options";
    yInfo() << "Checking for yarp network...";
    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        yError() << "Found no yarp network (try running \"yarpserver &\"), bye!";
        return 1;
    }

    return mod.runModule(rf);
}
