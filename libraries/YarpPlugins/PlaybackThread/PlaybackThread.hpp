// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __PLAYBACK_THREAD__
#define __PLAYBACK_THREAD__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <sstream>

#include <limits>  // NAN

#include <ColorDebug.h>

#include "Playback.hpp"

#include "IPlaybackThread.h"

#define DEFAULT_FILE_NAME "test.txt"
#define DEFAULT_TIME_IDX 0
#define DEFAULT_TIME_SCALE 1.0

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
class PlaybackThread : public yarp::dev::DeviceDriver, public IPlaybackThread, public yarp::os::Thread, public Playback
{

    public:

        PlaybackThread() { }

        //  --------- DeviceDriver Declarations. Implementation in DeviceDriverImpl.cpp ---------
        virtual bool open(yarp::os::Searchable& config);
        virtual bool close();

        //  --------- IPlaybackThread Declarations. Implementation in IPlaybackThreadImpl.cpp ---------
        virtual bool play();
        virtual bool pause();
        virtual bool stopPlay();
        virtual bool isPlaying();
        virtual bool setTimeScale(double timeScale);
        virtual void setIRunnable(IRunnable* iRunnable);

        // --------- Thread Declarations. Implementation in ThreadImpl.cpp ---------
        virtual void run();
        virtual void onStop();

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
        void setState( const int& state);

        static const int NOT_PLAYING;
        static const int PLAYING;

};

}  // namespace roboticslab

#endif  // __PLAYBACK_THREAD__

