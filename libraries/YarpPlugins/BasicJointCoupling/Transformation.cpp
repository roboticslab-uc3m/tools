// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Transformation.hpp"

#include <fstream>

#include <yarp/os/LogStream.h>
#include <yarp/os/ResourceFinder.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

Transformation::Transformation(int actAxisIndex, int physJointIndex)
    : actAxisIndex(actAxisIndex),
      physJointIndex(physJointIndex)
{}

// -----------------------------------------------------------------------------

bool LinearTransformation::configure(const yarp::os::Searchable & parameters)
{
    if (!parameters.check("m"))
    {
        yCError(BJC) << R"("m" parameter for LinearTransformation not found)";
        return false;
    }

    m = parameters.find("m").asFloat64();

    if (!parameters.check("b"))
    {
        yCError(BJC) << R"("b" parameter for LinearTransformation not found)";
        return false;
    }

    b = parameters.find("b").asFloat64();

    return true;
}

// -----------------------------------------------------------------------------

double LinearTransformation::transform(const double value)
{
    return value * m + b;
}

// -----------------------------------------------------------------------------

bool PiecewiseLinearTransformation::configure(const yarp::os::Searchable & parameters)
{
    if (!parameters.check("csvFile"))
    {
        yCError(BJC) << R"("csvFile" parameter for PiecewiseLinearTransformation not found)";
        return false;
    }

    std::string csvFileName = parameters.find("csvFile").asString();

    if (!parameters.check("context"))
    {
        yCError(BJC) << R"("context" parameter for PiecewiseLinearTransformation not found)";
        return false;
    }

    std::string context = parameters.find("context").asString();

    if (!parameters.check("inColumn"))
    {
        yCError(BJC) << R"("inColumn" parameter for PiecewiseLinearTransformation not found)";
        return false;
    }

    int inColumn = parameters.find("inColumn").asInt32();

    if (!parameters.check("outColumn"))
    {
        yCError(BJC) << R"("outColumn" parameter for PiecewiseLinearTransformation not found)";
        return false;
    }

    int outColumn = parameters.find("outColumn").asInt32();

    yarp::os::ResourceFinder rf;
    rf.setDefaultContext(context);

    std::string csvFileFullName = rf.findFileByName(csvFileName);

    if (csvFileFullName.empty())
    {
        yCError(BJC) << "Full path for file not found:" << csvFileName;
        return false;
    }

    std::ifstream csvFile(csvFileFullName);

    if (!csvFile.is_open())
    {
        yCError(BJC) << "Unable to open CSV file:" << csvFileFullName;
        return false;
    }

    std::string line;

    while (std::getline(csvFile, line))
    {
        std::stringstream lineSS(line);
        std::string token;
        int idx = 0;

        while (std::getline(lineSS, token, ','))
        {
            std::stringstream tokenSS(token);
            double d;
            tokenSS >> d;

            if (inColumn == idx)
            {
                inData.push_back(d);
            }

            if (outColumn == idx)
            {
                outData.push_back(d);
            }

            idx++;
        }

        yCDebug(BJC, "[%f, %f] from %s", inData[inData.size() - 1], outData[outData.size() - 1], line.c_str());
    }

    csvFile.close();

    return true;
}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::transform(const double value)
{
    // <http://www.cplusplus.com/forum/general/216928/> "lastchance" on May 31, 2017 at 5:55pm

    bool extrapolate = true; // determines behaviour beyond ends of array (if needed)
    int size = inData.size();
    int i = 0; // find left end of interval for interpolation

    if (value >= inData[size - 2]) // special case: beyond right end
    {
        i = size - 2;
    }
    else
    {
        while (value > inData[i + 1])
        {
            i++;
        }
    }

    // points on either side (unless beyond ends)
    double xL = inData[i];
    double yL = outData[i];
    double xR = inData[i + 1];
    double yR = outData[i + 1];

    if (!extrapolate) // if beyond ends of array and not extrapolating
    {
        if (value < xL)
        {
            yR = yL;
        }

        if (value > xR)
        {
            yL = yR;
        }
    }

    double dydx = (yR - yL) / (xR - xL); // gradient

    yCDebug(BJC) << "Ret:" << yL + dydx * (value - xL);
    return yL + dydx * (value - xL); // linear interpolation
}

// -----------------------------------------------------------------------------
