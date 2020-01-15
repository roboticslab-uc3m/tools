// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <string>

#include <yarp/os/Network.h>
#include <yarp/os/Property.h>

#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IPositionDirect.h>
#include <yarp/dev/PolyDriver.h>

#include <yarp/conf/version.h>
#if YARP_VERSION_MINOR >= 3
# include <yarp/conf/filesystem.h>
#endif

#include <IPlaybackThread.h>
#include <IRunnable.h>

#include <ColorDebug.h>

class PositionMoveRunnable : public roboticslab::IRunnable
{
public:
    virtual bool run(const std::vector<double> &v)
    {
        //iPositionControl->positionMove( v.data() );
        iPositionDirect->setPositions( v.data() );
        return true;
    }

    yarp::dev::IPositionControl* iPositionControl;
    yarp::dev::IPositionDirect* iPositionDirect;
};

int main(int argc, char *argv[])
{
    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        CD_ERROR("Please start a yarp name server first\n");
        return 1;
    }

    yarp::dev::PolyDriver playbackThreadDevice;
    roboticslab::IPlaybackThread *iPlaybackThread;

    yarp::dev::PolyDriver robotDevice;
    PositionMoveRunnable positionMoveRunnable;

    if (!yarp::os::Network::checkNetwork())
    {
        CD_ERROR("Please start a yarp name server first.\n");
        return(1);
    }

    //-- playbackThreadDevice and interface
    std::string fileName("..");
    fileName += yarp::os::NetworkBase::getDirectorySeparator();
    fileName += "rightArmLFlower1344";
    fileName += yarp::os::NetworkBase::getDirectorySeparator();
    fileName += "data-awk.log";

    yarp::os::Property playbackThreadOptions;
    playbackThreadOptions.put("device", "PlaybackThread");
    playbackThreadOptions.put("file", fileName);
    playbackThreadOptions.put("timeIdx", 0);
    playbackThreadOptions.put("timeScale", 0.0025);
    playbackThreadOptions.fromString("(mask 0 0 0 1 1 1 1 1 1)", false);
    playbackThreadDevice.open(playbackThreadOptions);

    if (!playbackThreadDevice.isValid())
    {
        CD_ERROR("playbackThreadDevice not available.\n");
        return 1;
    }

    if (!playbackThreadDevice.view(iPlaybackThread))
    {
        CD_ERROR("Problems acquiring iPlaybackThread interface.\n");
        return 1;
    }

    CD_SUCCESS("Acquired iPlaybackThread interface.\n");

    //-- robotDevice
    yarp::os::Property robotOptions;
    robotOptions.put("device", "remote_controlboard");
    robotOptions.put("local", "/playback");
    robotOptions.put("remote", "/teo/rightArm");
    robotDevice.open(robotOptions);

    if (!robotDevice.isValid())
    {
        CD_ERROR("robotDevice not available.\n");
        return 1;
    }

    robotDevice.view(positionMoveRunnable.iPositionControl);
    robotDevice.view(positionMoveRunnable.iPositionDirect );
    roboticslab::IRunnable* iRunnable = dynamic_cast<roboticslab::IRunnable*>(&positionMoveRunnable);
    iPlaybackThread->setIRunnable(iRunnable);

    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}

    robotDevice.close();
    playbackThreadDevice.close();

    return 0;
}
