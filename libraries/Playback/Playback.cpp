// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Playback.hpp"

#include <yarp/os/LogStream.h>

namespace roboticslab
{

// -----------------------------------------------------------------------------

bool Playback::fromFile(const std::string& fileName)
{
    file.open(fileName.c_str());
    if( ! file.is_open() )
    {
        yError() << "Not able to open file:" << fileName;
        return false;
    }
    yInfo() << "Opened file:" << fileName;

    std::vector<double> doublesOnFileLine;

    while( this->parseFileLine(doublesOnFileLine) )
    {
        if ( doublesOnFileLine.size() == 0 ) continue;

        doublesOnFile.push_back( doublesOnFileLine );
    }

    file.close();

    return true;
}

// -----------------------------------------------------------------------------

int Playback::getNumRows()
{
    return doublesOnFile.size();
}

// -----------------------------------------------------------------------------

int Playback::getIter()
{
    return doublesOnFileIter;
}

// -----------------------------------------------------------------------------

bool Playback::reset()
{
    doublesOnFileIter = 0;

    return true;
}

// -----------------------------------------------------------------------------

bool Playback::getNext(std::vector<double>& row)
{
    if( doublesOnFileIter >= doublesOnFile.size() )
        return false;

    row = doublesOnFile[doublesOnFileIter];

    doublesOnFileIter++;

    return true;
}

// -----------------------------------------------------------------------------

bool Playback::parseFileLine(std::vector<double>& doublesOnFileLine)
{
    doublesOnFileLine.clear();

    if( file.eof() )
        return false;

    std::string s;
    getline(file, s);
    std::stringstream ss(s);

    double d;
    while (ss >> d)
        doublesOnFileLine.push_back(d);

    return true;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
