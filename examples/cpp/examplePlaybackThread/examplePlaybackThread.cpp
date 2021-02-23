// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <string>

#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Property.h>

#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/conf/filesystem.h>

#include <IPlaybackThread.h>
#include <IRunnable.h>

class PositionMoveRunnable : public roboticslab::IRunnable
{
public:
    virtual bool run(const std::vector<double> &v)
    {
        iPositionControl->positionMove( v.data() );
        return true;
    }

    yarp::dev::IPositionControl* iPositionControl;
};

int main(int argc, char *argv[])
{
    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        yError() << "Please start a yarp name server first";
        return 1;
    }

    yarp::dev::PolyDriver playbackThreadDevice;
    roboticslab::IPlaybackThread *iPlaybackThread;

    yarp::dev::PolyDriver robotDevice;
    PositionMoveRunnable positionMoveRunnable;

    //-- playbackThreadDevice and interface
    std::string fileName("..");
    fileName += yarp::conf::filesystem::preferred_separator;
    fileName += "resources";
    fileName += yarp::conf::filesystem::preferred_separator;
    fileName += "yarpdatadumper-teo-rightArm.txt";

    yarp::os::Property playbackThreadOptions;
    playbackThreadOptions.put("device", "PlaybackThread");
    playbackThreadOptions.put("file", fileName);
    playbackThreadOptions.put("timeIdx", 1);
    playbackThreadOptions.put("timeScale", 0.000001);
    playbackThreadOptions.fromString("(mask 0 0 1 1 1 1 1 1 1)", false);
    playbackThreadDevice.open(playbackThreadOptions);

    if (!playbackThreadDevice.isValid())
    {
        yError() << "playbackThreadDevice not available";
        return 1;
    }

    if (!playbackThreadDevice.view(iPlaybackThread))
    {
        yError() << "Problems acquiring iPlaybackThread interface";
        return 1;
    }

    //-- robotDevice
    yarp::os::Property robotOptions;
    robotOptions.put("device", "remote_controlboard");
    robotOptions.put("local", "/playback");
    robotOptions.put("remote", "/teoSim/rightArm");
    robotDevice.open(robotOptions);

    if (!robotDevice.isValid())
    {
        yError() << "robotDevice not available";
        return 1;
    }

    robotDevice.view(positionMoveRunnable.iPositionControl);
    roboticslab::IRunnable* iRunnable = dynamic_cast<roboticslab::IRunnable*>(&positionMoveRunnable);
    iPlaybackThread->setIRunnable(iRunnable);

    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}

    robotDevice.close();
    playbackThreadDevice.close();

    return 0;
}
