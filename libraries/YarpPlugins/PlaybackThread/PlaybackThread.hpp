// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK_THREAD_HPP__
#define __PLAYBACK_THREAD_HPP__

#include <atomic>

#include <yarp/os/Thread.h>
#include <yarp/dev/DeviceDriver.h>

#include "Playback.hpp"
#include "IPlaybackThread.h"
#include "PlaybackThread_ParamsParser.h"

/**
 * @ingroup YarpPlugins
 * @defgroup PlaybackThread
 * @brief Contains PlaybackThread.
 */

 /**
 * @ingroup PlaybackThread
 * @brief Implementation for the PlaybackThread.
 */
class PlaybackThread : public yarp::dev::DeviceDriver,
                       public roboticslab::IPlaybackThread,
                       public yarp::os::Thread,
                       private roboticslab::Playback,
                       public PlaybackThread_ParamsParser
{
public:
    //  --------- DeviceDriver Declarations. Implementation in DeviceDriverImpl.cpp ---------
    bool open(yarp::os::Searchable & config) override;
    bool close() override;

    //  --------- IPlaybackThread Declarations. Implementation in IPlaybackThreadImpl.cpp ---------
    bool play() override;
    bool pause() override;
    bool stopPlay() override;
    bool isPlaying() override;
    bool setTimeScale(double timeScale) override;
    void setIRunnable(roboticslab::IRunnable * iRunnable) override;

    // --------- Thread Declarations. Implementation in ThreadImpl.cpp ---------
    void run() override;
    void onStop() override;

private:
    enum class state { NOT_PLAYING, PLAYING };

    roboticslab::IRunnable * _iRunnable {nullptr};
    std::atomic<state> _state {state::NOT_PLAYING};
};

#endif // __PLAYBACK_THREAD_HPP__
