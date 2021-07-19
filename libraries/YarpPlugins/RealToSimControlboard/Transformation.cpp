// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Transformation.hpp"

#include <fstream>

#include <yarp/os/LogStream.h>

namespace roboticslab
{

// -----------------------------------------------------------------------------

LinearTransformation::LinearTransformation(yarp::os::Searchable* parameters)
{
    if(!parameters->check("m"))
    {
        yError() << "**** \"m\" parameter for LinearTransformation NOT found";
        return;
    }
    yDebug() << "**** \"m\" parameter for LinearTransformation found";
    m = parameters->find("m").asFloat64();

    if(!parameters->check("b"))
    {
        yError() << "**** \"b\" parameter for LinearTransformation NOT found";
        return;
    }
    yDebug() << "**** \"b\" parameter for LinearTransformation found";
    b = parameters->find("b").asFloat64();

    valid = true;
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

double LinearTransformation::transform(const double value)
{
    return value * m + b;
}

// -----------------------------------------------------------------------------

PiecewiseLinearTransformation::PiecewiseLinearTransformation(yarp::os::Searchable* parameters)
{
    if(!parameters->check("csvFile"))
    {
        yError() << "**** \"csvFile\" parameter for PiecewiseLinearTransformation NOT found";
        return;
    }
    std::string csvFileName = parameters->find("csvFile").asString();
    yDebug("**** \"csvFile\" parameter for PiecewiseLinearTransformation found: \"%s\"", csvFileName.c_str());

    if(!parameters->check("context"))
    {
        yError() << "**** \"context\" parameter for PiecewiseLinearTransformation NOT found";
        return;
    }
    std::string context = parameters->find("context").asString();
    yDebug("**** \"context\" parameter for PiecewiseLinearTransformation found: \"%s\"", context.c_str());

    if(!parameters->check("inColumn"))
    {
        yError() << "**** \"inColumn\" parameter for PiecewiseLinearTransformation NOT found";
        return;
    }
    const int inColumn = parameters->find("inColumn").asInt32();
    yDebug("**** \"inColumn\" parameter for PiecewiseLinearTransformation found: \"%d\"", inColumn);

    if(!parameters->check("outColumn"))
    {
        yError() << "**** \"outColumn\" parameter for PiecewiseLinearTransformation NOT found";
        return;
    }
    const int outColumn = parameters->find("outColumn").asInt32();
    yDebug("**** \"outColumn\" parameter for PiecewiseLinearTransformation found: \"%d\"", outColumn);

    yarp::os::ResourceFinder rf;
    rf.setVerbose(false);
    rf.setDefaultContext(context);
    std::string csvFileFullName = rf.findFileByName(csvFileName);
    if(csvFileFullName.empty())
    {
        yError() << "**** full path for file NOT found";
        return;
    }
    yDebug("**** full path for file found: \"%s\"", csvFileFullName.c_str());

    std::ifstream csvFile(csvFileFullName);
    if(!csvFile.is_open())
    {
        yError("**** \"%s\" csvFile for PiecewiseLinearTransformation NOT open", csvFileName.c_str());
        return;
    }
    yDebug("**** \"%s\" csvFile for PiecewiseLinearTransformation open", csvFileName.c_str());

    std::string line;
    while (std::getline(csvFile, line))
    {
        std::stringstream lineSS(line);
        std::string token;
        int idx = 0;
        while(std::getline(lineSS, token, ','))
        {
            std::stringstream tokenSS(token);
            double d;
            tokenSS >> d;
            if(inColumn == idx)
                inData.push_back(d);
            if(outColumn == idx)
                outData.push_back(d);
            idx++;
        }
        yDebug("***** [%f, %f] from %s", inData[inData.size()-1], outData[outData.size()-1], line.c_str());
    }

    csvFile.close();

    valid = true;
}

// -----------------------------------------------------------------------------

// <http://www.cplusplus.com/forum/general/216928/> "lastchance" on May 31, 2017 at 5:55pm
double PiecewiseLinearTransformation::transform(const double value)
{
    bool extrapolate = true; // determines behaviour beyond ends of array (if needed)

    int size = inData.size();

    int i = 0; // find left end of interval for interpolation
    if ( value >= inData[size - 2] ) // special case: beyond right end
    {
       i = size - 2;
    }
    else
    {
       while ( value > inData[i+1] ) i++;
    }
    double xL = inData[i], yL = outData[i], xR = inData[i+1], yR = outData[i+1]; // points on either side (unless beyond ends)
    if ( !extrapolate ) // if beyond ends of array and not extrapolating
    {
       if ( value < xL ) yR = yL;
       if ( value > xR ) yL = yR;
    }

    double dydx = ( yR - yL ) / ( xR - xL ); // gradient

    yDebug() << "Ret:" << yL + dydx * ( value - xL );
    return yL + dydx * ( value - xL ); // linear interpolation
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
