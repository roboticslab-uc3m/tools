#include "ControlboardStateToIPosition.hpp"
#include "ColorDebug.hpp"

namespace roboticslab
{

bool ControlboardStateToIPosition::configure(yarp::os::ResourceFinder &rf)
{
    return true;
}


bool ControlboardStateToIPosition::updateModule()
{
    CD_INFO("Alive...\n");
    return true;
}

}
