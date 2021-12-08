// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

constexpr auto DEFAULT_FILE_NAME = "test.txt";
constexpr auto DEFAULT_TIME_IDX = 0;
constexpr auto DEFAULT_TIME_SCALE = 1.0;

// -----------------------------------------------------------------------------

bool PlaybackThread::open(yarp::os::Searchable & config)
{
    std::string fileName = config.check("file", yarp::os::Value(DEFAULT_FILE_NAME), "file name").asString();
    timeIdx = config.check("timeIdx", yarp::os::Value(DEFAULT_TIME_IDX), "index of timestamp").asInt32();
    timeScale = config.check("timeScale", yarp::os::Value(DEFAULT_TIME_SCALE), "time scaling of timestamp").asFloat64();
    mask = config.findGroup("mask", "filter to apply to each item in a row ('1': process, '0': ignore)").tail();

    yCInfo(PBT, "file: %s [%s]", fileName.c_str(), DEFAULT_FILE_NAME);
    yCInfo(PBT, "timeIdx: %d [%d]", timeIdx, DEFAULT_TIME_IDX);
    yCInfo(PBT, "timeScale: %f [%f]", timeScale, DEFAULT_TIME_SCALE);
    yCInfo(PBT, "mask: %s (%zu)", mask.toString().c_str(), mask.size());

    return fromFile(fileName) && yarp::os::Thread::start();
}

// -----------------------------------------------------------------------------

bool PlaybackThread::close()
{
    return yarp::os::Thread::stop();
}

// -----------------------------------------------------------------------------
