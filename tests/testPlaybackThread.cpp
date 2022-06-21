#include "gtest/gtest.h"

#include <string>

#include <yarp/os/LogStream.h>
#include <yarp/os/SystemClock.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/conf/filesystem.h>

#include "IPlaybackThread.h"

namespace roboticslab::test
{

class MockRunnable : public IRunnable
{
    bool run(const std::vector<double> & v) override
    {
        yInfo() << "MockRunnable:" << v;
        return true;
    }
};

/**
 * @ingroup roboticslab-tools-tests
 * @brief Tests \ref Playback
 */
class PlaybackThreadTest : public testing::Test
{
public:
    void SetUp() override
    {
        // -- code here will execute just before the test ensues
        std::string fileName("resources");
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testPlayback.txt";

        yarp::os::Property playbackThreadConf {
            {"device", yarp::os::Value("PlaybackThread")},
            {"file", yarp::os::Value(fileName)},
            {"timeIdx", yarp::os::Value(0)}
        };

        playbackThreadConf.fromString("(mask 0 1 0 1)", false);

        if (!playbackDevice.open(playbackThreadConf) || !playbackDevice.view(iPlaybackThread))
        {
            yFatal() << "Bad Configuration";
        }

        yInfo() << "Configuration successful";
    }

    void TearDown() override
    {
        playbackDevice.close();
    }

protected:
    yarp::dev::PolyDriver playbackDevice;
    roboticslab::IPlaybackThread * iPlaybackThread;
};

TEST_F(PlaybackThreadTest, PlaybackThreadTestPlayQuick)
{
    iPlaybackThread->play();
}

TEST_F(PlaybackThreadTest, PlaybackThreadTestPlayFull)
{
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}
}

TEST_F(PlaybackThreadTest, PlaybackThreadTestPlayReplay)
{
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}

    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}
}

TEST_F(PlaybackThreadTest, PlaybackThreadTestPause)
{
    yInfo() << "Play 2 seconds";
    iPlaybackThread->play();
    yarp::os::SystemClock::delaySystem(0.5);
    iPlaybackThread->pause();

    yInfo() << "Pause 7 seconds (normal for one to pass)";
    yarp::os::SystemClock::delaySystem(7.0);

    yInfo() << "Play until end";
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}
}

TEST_F(PlaybackThreadTest, PlaybackThreadTestTimeScale)
{
    yInfo() << "Play x2 slower";
    iPlaybackThread->setTimeScale(2.0);
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}

    yInfo() << "Play x10 faster";
    iPlaybackThread->setTimeScale(0.1);
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}
    iPlaybackThread->setTimeScale(1.0);
}

TEST_F(PlaybackThreadTest, PlaybackThreadTestRunnable)
{
    MockRunnable runnable;
    iPlaybackThread->setIRunnable(&runnable);
    iPlaybackThread->play();
    while (iPlaybackThread->isPlaying()) {}
}

} // namespace roboticslab::test
