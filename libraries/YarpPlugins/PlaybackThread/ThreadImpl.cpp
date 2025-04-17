// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/SystemClock.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

void PlaybackThread::run()
{
    std::vector<double> maskedRow;
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

        if (!hasNextRow())
        {
            stopPlay();
            yCInfo(PBT) << "End of rows, auto stopPlay()";
            continue;
        }

        const auto & row = getNextRow();

        if (initTime == 0.0)
        {
            initTime = yarp::os::SystemClock::nowSystem();
            initRow = row[m_timeIdx];
        }
        else
        {
            yarp::os::SystemClock::delaySystem(initTime + (row[m_timeIdx] - initRow) * m_timeScale - yarp::os::SystemClock::nowSystem());
        }

        if (m_mask.empty())
        {
            maskedRow = row;
        }
        else
        {
            maskedRow.clear();
            maskedRow.reserve(m_mask.size());

            for (int i = 0; i < m_mask.size(); i++)
            {
                if (m_mask[i] == 1)
                {
                    maskedRow.push_back(row[i]);
                }
            }
        }

        yCInfo(PBT) << "Row" << getCurrentRowIndex() << row;

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
