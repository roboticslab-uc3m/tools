#include "gtest/gtest.h" // -- We load the librarie of GoogleTest

#include <string>

// -- We load the rest of libraries that we will use to call the functions of our code
#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#include <ColorDebug.h>

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
* @brief Tests \ref Playback
*/
class PlaybackThreadTest : public testing::Test // -- inherit the Test class (gtest.h)
{

public:

    virtual void SetUp()
    {
        // -- code here will execute just before the test ensues

        yarp::os::ResourceFinder rf;
        rf.setVerbose(true);
        rf.setDefaultContext("Playback");
        std::string path = rf.findFileByName("txt/testPlayback.txt");

        yarp::os::Property playbackThreadConf;
        playbackThreadConf.put("device","PlaybackThread");
        playbackThreadConf.put("file",path);
        playbackThreadConf.put("timeIdx",0);
        playbackThreadConf.fromString("(mask 0 1 0 1)",false);
        bool ok = true;
        ok &= playbackDevice.open(playbackThreadConf);
        ok &= playbackDevice.view(iPlaybackThread);
        if(ok)
        {
            CD_SUCCESS("Configuration successful :)\n");
        }
        else
        {
            CD_ERROR("Bad Configuration\n");
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
    CD_INFO("Play 2 seconds.\n");
    iPlaybackThread->play();
    yarp::os::Time::delay(0.5);
    iPlaybackThread->pause();
    CD_INFO("Pause 7 seconds (normal for one to pass).\n");
    yarp::os::Time::delay(7);
    CD_INFO("Play untill end.\n");
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
}

TEST_F( PlaybackThreadTest, PlaybackThreadTestTimeScale )
{
    CD_INFO("Play x2 slower.\n");
    iPlaybackThread->setTimeScale(2);
    iPlaybackThread->play();
    while( iPlaybackThread->isPlaying() );
    CD_INFO("Play x10 faster.\n");
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
