// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Playback.hpp"

#include <sstream>
#include <string>
#include <utility>

#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>

using namespace roboticslab;

namespace
{
    YARP_LOG_COMPONENT(PLAY, "rl.Playback")
}

// -----------------------------------------------------------------------------

bool Playback::fromFile(const std::string & fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        yCError(PLAY) << "Not able to open file:" << fileName;
        return false;
    }

    yCInfo(PLAY) << "Opened file:" << fileName;

    std::vector<double> row;

    while (!file.eof())
    {
        parseFileLine(file, row);

        if (!row.empty())
        {
            storage.push_back(std::move(row));
        }
    }

    file.close();
    reset(); // sets our iterator to the first row
    return true;
}

// -----------------------------------------------------------------------------

std::size_t Playback::getNumRows() const
{
    return storage.size();
}

// -----------------------------------------------------------------------------

std::size_t Playback::getCurrentRowIndex() const
{
    return std::distance(storage.cbegin(), iter);
}

// -----------------------------------------------------------------------------

bool Playback::hasNextRow() const
{
    return iter != storage.cend();
}

// -----------------------------------------------------------------------------

const Playback::row_t::value_type & Playback::getNextRow()
{
    return *iter++; // dereference, then increment
}

// -----------------------------------------------------------------------------

void Playback::reset()
{
    iter = storage.cbegin();
}

// -----------------------------------------------------------------------------

void Playback::parseFileLine(std::ifstream & file, std::vector<double> & row)
{
    std::string s;
    std::getline(file, s);
    std::stringstream ss(s);

    double d;

    while (ss >> d)
    {
        row.push_back(d);
    }
}

// -----------------------------------------------------------------------------
