// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "PlaybackThread.hpp"

#include <yarp/os/LogStream.h>

namespace roboticslab {

// -----------------------------------------------------------------------------

bool PlaybackThread::open(yarp::os::Searchable& config)
{
    std::string fileName = config.check("file",yarp::os::Value(DEFAULT_FILE_NAME),"file name").asString();
    timeIdx = config.check("timeIdx",yarp::os::Value(DEFAULT_TIME_IDX),"index of timestamp").asInt32();
    timeScale = config.check("timeScale",yarp::os::Value(DEFAULT_TIME_SCALE),"time scaling of timestamp").asFloat64();
    mask = config.findGroup("mask","filter to apply to each item in a row ('1': process, '0': ignore)").tail();

    yInfo("file: %s [%s]", fileName.c_str(), DEFAULT_FILE_NAME);
    yInfo("timeIdx: %d [%d]", timeIdx, DEFAULT_TIME_IDX);
    yInfo("timeScale: %f [%f]", timeScale, DEFAULT_TIME_SCALE);
    yInfo("mask: %s (%zu)", mask.toString().c_str(), mask.size());

    _iRunnable = NULL;

    if( ! fromFile(fileName) )
        return false;

    setState( NOT_PLAYING );
    this->start();

    return true;
}

// -----------------------------------------------------------------------------

bool PlaybackThread::close()
{
    this->stop();
    return true;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
