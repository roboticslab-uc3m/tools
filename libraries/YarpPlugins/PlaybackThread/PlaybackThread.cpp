// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

const int roboticslab::PlaybackThread::NOT_PLAYING = 0;
const int roboticslab::PlaybackThread::PLAYING = 1;

namespace roboticslab {

// -----------------------------------------------------------------------------

int PlaybackThread::getState()
{
    _stateSemaphore.wait();
    int tmp = _state;
    _stateSemaphore.post();
    return tmp;
}

// -----------------------------------------------------------------------------

void PlaybackThread::setState( const int& state)
{
    //CD_DEBUG("%d\n",state);
    _stateSemaphore.wait();
    _state = state;
    _stateSemaphore.post();
    return;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
