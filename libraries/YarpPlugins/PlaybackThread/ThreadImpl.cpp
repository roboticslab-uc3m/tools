// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

#include <iostream>

#include <yarp/os/LogStream.h>
#include <yarp/os/SystemClock.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

void PlaybackThread::run()
{
    std::vector<double> row, maskedRow;
    double initTime = 0.0;
    double initRow = 0.0;

    while (!yarp::os::Thread::isStopping())
    {
        if (_state != state::PLAYING)
        {
            yarp::os::SystemClock::delaySystem(0.1);
            initTime = 0.0;
            continue;
        }

        if (!getNext(row))
        {
            stopPlay();
            yCInfo(PBT) << "End of rows, auto stopPlay()";
            continue;
        }

        if (initTime == 0.0)
        {
            initTime = yarp::os::SystemClock::nowSystem();
            initRow = row[timeIdx];
        }
        else
        {
            yarp::os::SystemClock::delaySystem(initTime + (row[timeIdx] - initRow) * timeScale - yarp::os::SystemClock::nowSystem());
        }

        if (mask.size() == 0)
        {
            maskedRow = row;
        }
        else
        {
            maskedRow.clear();
            maskedRow.reserve(mask.size());

            for (int i = 0; i < mask.size(); i++)
            {
                if (mask.get(i).asInt32() == 1)
                {
                    maskedRow.push_back(row[i]);
                }
            }
        }

        std::cout << "Row[" << getIter() << "]: ";

        for (auto column : row)
        {
            std::cout << column << " ";
        }

        std::cout << std::endl;

        if (_iRunnable)
        {
            _iRunnable->run(maskedRow);
        }
    }
}

// -----------------------------------------------------------------------------

void PlaybackThread::onStop()
{
    _state = state::NOT_PLAYING;
}

// -----------------------------------------------------------------------------
