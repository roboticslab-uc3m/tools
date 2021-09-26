// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <string>

#include <yarp/conf/filesystem.h>

#include <yarp/os/LogStream.h>
#include <yarp/os/Network.h>
#include <yarp/os/Property.h>
#include <yarp/os/ResourceFinder.h>

#include <yarp/dev/IControlMode.h>
#include <yarp/dev/IPositionDirect.h>
#include <yarp/dev/PolyDriver.h>

#include <IPlaybackThread.h>
#include <IRunnable.h>

class Runnable : public roboticslab::IRunnable
{
public:
    bool run(const std::vector<double> & v) override
    {
        return iPositionDirect->setPositions(v.data());
    }

    yarp::dev::IPositionDirect * iPositionDirect;
};

int main(int argc, char * argv[])
{
    yarp::os::ResourceFinder rf;
    rf.configure(argc, argv);

    yarp::os::Property options(rf.toString().c_str());

#ifdef SAMPLE_CONFIG
    std::string sampleConfigFile = SAMPLE_CONFIG;
    options.fromConfigFile(sampleConfigFile, false);
#endif

    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        yError() << "Please start a yarp name server first";
        return 1;
    }

    yarp::dev::PolyDriver playbackThreadDevice;
    roboticslab::IPlaybackThread * iPlaybackThread;

    yarp::dev::PolyDriver robotDevice;
    Runnable runnable;

    //-- playbackThreadDevice and interface
    yarp::os::Property playbackThreadOptions(options.findGroup("PLAYBACK").toString().c_str());

    if (!playbackThreadDevice.open(playbackThreadOptions))
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
    yarp::os::Property robotOptions(options.findGroup("ROBOT").toString().c_str());

    if (!robotDevice.open(robotOptions))
    {
        yError() << "robotDevice not available";
        return 1;
    }

    yarp::dev::IControlMode * mode;

    if (!robotDevice.view(mode) || !robotDevice.view(runnable.iPositionDirect))
    {
        yError() << "Unable to acquire interfaces";
        return 1;
    }

    if (!mode->setControlModes(std::vector<int>(6, VOCAB_CM_POSITION_DIRECT).data()))
    {
        yError() << "Unable to switch to position direct mode";
        return 1;
    }

    iPlaybackThread->setIRunnable(&runnable);

    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}

    return 0;
}
