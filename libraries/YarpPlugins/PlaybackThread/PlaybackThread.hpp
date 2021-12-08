// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK_THREAD_HPP__
#define __PLAYBACK_THREAD_HPP__

#include <atomic>

#include <yarp/os/Bottle.h>
#include <yarp/os/Thread.h>
#include <yarp/dev/DeviceDriver.h>

#include "Playback.hpp"
#include "IPlaybackThread.h"

namespace roboticslab
{

/**
 * @ingroup YarpPlugins
 * @defgroup PlaybackThread
 * @brief Contains roboticslab::PlaybackThread.
 */

 /**
 * @ingroup PlaybackThread
 * @brief Implementation for the PlaybackThread.
 */
class PlaybackThread : public yarp::dev::DeviceDriver,
                       public IPlaybackThread,
                       public yarp::os::Thread,
                       private Playback
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
    void setIRunnable(IRunnable * iRunnable) override;

    // --------- Thread Declarations. Implementation in ThreadImpl.cpp ---------
    void run() override;
    void onStop() override;

private:
    enum class state { NOT_PLAYING, PLAYING };

    int timeIdx {0};
    double timeScale {0.0};

    yarp::os::Bottle mask;
    IRunnable * _iRunnable {nullptr};
    std::atomic<state> _state {state::NOT_PLAYING};
};

} // namespace roboticslab

#endif // __PLAYBACK_THREAD_HPP__
