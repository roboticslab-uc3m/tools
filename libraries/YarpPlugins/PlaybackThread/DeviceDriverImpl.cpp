// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

bool PlaybackThread::open(yarp::os::Searchable & config)
{
    if (!parseParams(config))
    {
        yCError(PBT) << "Failed to parse parameters";
        return false;
    }

    if (m_mask.empty())
    {
        yCError(PBT) << "Mask is empty";
        return false;
    }

    return fromFile(m_file) && yarp::os::Thread::start();
}

// -----------------------------------------------------------------------------

bool PlaybackThread::close()
{
    return yarp::os::Thread::stop();
}

// -----------------------------------------------------------------------------
