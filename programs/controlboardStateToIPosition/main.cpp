
#include <yarp/os/all.h>

int main(int argc, char *argv[])
{
    yarp::os::Network yarp;
    if ( ! yarp::os::Network::checkNetwork() )
    {
        printf("Please start a yarp name server first\n");
        return 1;
    }
    return 0;
}

