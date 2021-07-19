// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

using namespace roboticslab;

const int PlaybackThread::NOT_PLAYING = 0;
const int PlaybackThread::PLAYING = 1;

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
    _stateSemaphore.wait();
    _state = state;
    _stateSemaphore.post();
    return;
}

// -----------------------------------------------------------------------------
