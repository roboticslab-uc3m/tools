// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK_THREAD_HPP__
#define __PLAYBACK_THREAD_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <sstream>

#include <limits>  // NAN

#include "Playback.hpp"

#include "IPlaybackThread.h"

namespace roboticslab
{

/**
 * @ingroup YarpPlugins
 * \defgroup PlaybackThread
 * @brief Contains roboticslab::PlaybackThread.
 */

 /**
 * @ingroup PlaybackThread
 * @brief Implementation for the PlaybackThread.
 *
 */
class PlaybackThread : public yarp::dev::DeviceDriver,
                       public IPlaybackThread,
                       public yarp::os::Thread,
                       public Playback
{
public:
    //  --------- DeviceDriver Declarations. Implementation in DeviceDriverImpl.cpp ---------
    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    //  --------- IPlaybackThread Declarations. Implementation in IPlaybackThreadImpl.cpp ---------
    bool play() override;
    bool pause() override;
    bool stopPlay() override;
    bool isPlaying() override;
    bool setTimeScale(double timeScale) override;
    void setIRunnable(IRunnable* iRunnable) override;

    // --------- Thread Declarations. Implementation in ThreadImpl.cpp ---------
    void run() override;
    void onStop() override;

private:
    int timeIdx;
    double timeScale;
    double initTime;
    double initRow;

    yarp::os::Bottle mask;

    IRunnable* _iRunnable;

    int _state;
    yarp::os::Semaphore _stateSemaphore;
    int getState();
    void setState(const int& state);

    static const int NOT_PLAYING;
    static const int PLAYING;
};

} // namespace roboticslab

#endif // __PLAYBACK_THREAD_HPP__
