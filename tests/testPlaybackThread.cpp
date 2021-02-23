#include "gtest/gtest.h"

#include <string>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/conf/filesystem.h>

#include "IPlaybackThread.h"

namespace roboticslab
{

class MockRunnable : public IRunnable
{
    virtual bool run(const std::vector<double> &v)
    {
        std::cout << "MockRunnable: ";
        for(int i=0;i<v.size();i++)
        {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;

        return true;
    }
};

/**
 * @ingroup roboticslab-tools-tests
 * @brief Tests \ref Playback
 */
class PlaybackThreadTest : public testing::Test // -- inherit the Test class (gtest.h)
{

public:

    virtual void SetUp()
    {
        // -- code here will execute just before the test ensues
        std::string fileName("resources");
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testPlayback.txt";

        yarp::os::Property playbackThreadConf;
        playbackThreadConf.put("device","PlaybackThread");
        playbackThreadConf.put("file",fileName);
        playbackThreadConf.put("timeIdx",0);
        playbackThreadConf.fromString("(mask 0 1 0 1)",false);
        bool ok = true;
        ok &= playbackDevice.open(playbackThreadConf);
        ok &= playbackDevice.view(iPlaybackThread);
        if(ok)
        {
            yInfo() << "Configuration successful";
        }
        else
        {
            yError() << "Bad Configuration";
            ::exit(1);
        }
    }

    virtual void TearDown()
    {
        // -- code here will be called just after the test completes
        // -- ok to through exceptions from here if need be
        playbackDevice.close();
    }

protected:

    /** Playback device. */
    yarp::dev::PolyDriver playbackDevice;
    roboticslab::IPlaybackThread* iPlaybackThread;
};

TEST_F( PlaybackThreadTest, PlaybackThreadTestPlayQuick )
{
    iPlaybackThread->play();
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestPlayFull )
{
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestPlayReplay )
{
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestPause )
{
    yInfo() << "Play 2 seconds";
    iPlaybackThread->play();
    yarp::os::Time::delay(0.5);
    iPlaybackThread->pause();
    yInfo() << "Pause 7 seconds (normal for one to pass)";
    yarp::os::Time::delay(7);
    yInfo() << "Play untill end";
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestTimeScale )
{
    yInfo() << "Play x2 slower";
    iPlaybackThread->setTimeScale(2);
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
    yInfo() << "Play x10 faster";
    iPlaybackThread->setTimeScale(0.1);
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
    iPlaybackThread->setTimeScale(1);
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestRunnable )
{
    IRunnable* iRunnable = new MockRunnable;
    iPlaybackThread->setIRunnable( iRunnable );
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
    delete iRunnable;
    iRunnable = NULL;
}

}
