// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Transformation.hpp"

#include <fstream>

namespace roboticslab
{

// -----------------------------------------------------------------------------

LinearTransformation::LinearTransformation(yarp::os::Searchable* parameters)
{
    if(!parameters->check("m"))
    {
        CD_ERROR("**** \"m\" parameter for LinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"m\" parameter for LinearTransformation found\n");
    m = parameters->find("m").asDouble();

    if(!parameters->check("b"))
    {
        CD_ERROR("**** \"b\" parameter for LinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"b\" parameter for LinearTransformation found\n");
    b = parameters->find("b").asDouble();

    valid = true;
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

double LinearTransformation::transform(const double& value)
{
    return value * m + b;
}

// -----------------------------------------------------------------------------

PiecewiseLinearTransformation::PiecewiseLinearTransformation(yarp::os::Searchable* parameters)
{
    if(!parameters->check("csvFile"))
    {
        CD_ERROR("**** \"csvFile\" parameter for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    std::string csvFileName = parameters->find("csvFile").asString();
    CD_DEBUG("**** \"csvFile\" parameter for PiecewiseLinearTransformation found: \"%s\"\n", csvFileName.c_str());

    if(!parameters->check("context"))
    {
        CD_ERROR("**** \"context\" parameter for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    std::string context = parameters->find("context").asString();
    CD_DEBUG("**** \"context\" parameter for PiecewiseLinearTransformation found: \"%s\"\n", context.c_str());

    if(!parameters->check("inColumn"))
    {
        CD_ERROR("**** \"inColumn\" parameter for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    const int inColumn = parameters->find("inColumn").asInt();
    CD_DEBUG("**** \"inColumn\" parameter for PiecewiseLinearTransformation found: \"%d\"\n", inColumn);

    if(!parameters->check("outColumn"))
    {
        CD_ERROR("**** \"outColumn\" parameter for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    const int outColumn = parameters->find("outColumn").asInt();
    CD_DEBUG("**** \"outColumn\" parameter for PiecewiseLinearTransformation found: \"%d\"\n", outColumn);

    yarp::os::ResourceFinder rf;
    rf.setVerbose(false);
    rf.setDefaultContext(context);
    std::string csvFileFullName = rf.findFileByName(csvFileName);
    if(csvFileFullName.empty())
    {
        CD_ERROR("**** full path for file NOT found\n");
        return;
    }
    CD_DEBUG("**** full path for file found: \"%s\"\n", csvFileFullName.c_str());

    std::ifstream csvFile(csvFileFullName);
    if(!csvFile.is_open())
    {
        CD_ERROR("**** \"%s\" csvFile for PiecewiseLinearTransformation NOT open\n", csvFileName.c_str());
        return;
    }
    CD_DEBUG("**** \"%s\" csvFile for PiecewiseLinearTransformation open\n", csvFileName.c_str());

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
        CD_DEBUG("***** [%f, %f] from %s\n", inData[inData.size()-1], outData[outData.size()-1], line.c_str());
    }

    csvFile.close();

    valid = true;
}

// -----------------------------------------------------------------------------

// <http://www.cplusplus.com/forum/general/216928/> "lastchance" on May 31, 2017 at 5:55pm
double PiecewiseLinearTransformation::transform(const double& value)
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

    CD_DEBUG("Ret: %f\n", yL + dydx * ( value - xL ));
    return yL + dydx * ( value - xL ); // linear interpolation
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
