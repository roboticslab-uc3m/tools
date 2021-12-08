// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

void PlaybackThread::setIRunnable(IRunnable * iRunnable)
{
    _iRunnable = iRunnable;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::play()
{
    _state = state::PLAYING;
    return true;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::pause()
{
    _state = state::NOT_PLAYING;
    return true;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::stopPlay()
{
    _state = state::NOT_PLAYING;
    reset();
    return true;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::isPlaying()
{
    return _state == state::PLAYING;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::setTimeScale(double timeScale)
{
    this->timeScale = timeScale;
    return true;
}

// -----------------------------------------------------------------------------
