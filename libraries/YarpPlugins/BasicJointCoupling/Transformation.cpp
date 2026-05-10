// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "Transformation.hpp"

#include <fstream> // std::ifstream
#include <sstream> // std::stringstream

#include <yarp/os/LogStream.h>
#include <yarp/os/ResourceFinder.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

bool LinearTransformation::configure(const yarp::os::Searchable & parameters)
{
    if (!parameters.check("m"))
    {
        yCError(BJC) << R"("m" parameter for LinearTransformation not found)";
        return false;
    }

    m = parameters.find("m").asFloat64();

    if (m == 0.0)
    {
        yCError(BJC) << R"("m" parameter for LinearTransformation cannot be zero)";
        return false;
    }

    if (!parameters.check("b"))
    {
        yCError(BJC) << R"("b" parameter for LinearTransformation not found)";
        return false;
    }

    b = parameters.find("b").asFloat64();

    return true;
}

// -----------------------------------------------------------------------------

double LinearTransformation::position(const double q)
{
    return q * m + b;
}

// -----------------------------------------------------------------------------

double LinearTransformation::velocity(const double q, const double qdot)
{
    return m;
}

// -----------------------------------------------------------------------------

double LinearTransformation::acceleration(const double q, const double qdot, const double qdotdot)
{
    return 0.0;
}

// -----------------------------------------------------------------------------

Transformation * LinearTransformation::inverse()
{
    auto * inverse = new LinearTransformation();
    inverse->m = 1.0 / m;
    inverse->b = -b / m;
    return inverse;
}

// -----------------------------------------------------------------------------

bool PiecewiseLinearTransformation::configure(const yarp::os::Searchable & parameters)
{
    if (parameters.check("csvFile"))
    {
        if (!readCsvFile(parameters))
        {
            yCError(BJC) << "CSV file for PiecewiseLinearTransformation requested, but failed to read it";
            return false;
        }
    }
    else
    {
        yCInfo(BJC) << R"("csvFile" parameter for PiecewiseLinearTransformation not found, reading from local config)";

        const auto * inDataList = parameters.find("inData").asList();
        const auto * outDataList = parameters.find("outData").asList();

        if (!inDataList || inDataList->isNull())
        {
            yCError(BJC) << R"("inData" parameter for PiecewiseLinearTransformation not found or not a list)";
            return false;
        }

        if (!outDataList || outDataList->isNull())
        {
            yCError(BJC) << R"("outData" parameter for PiecewiseLinearTransformation not found or not a list)";
            return false;
        }

        if (inDataList->size() != outDataList->size())
        {
            yCError(BJC) << R"("inData" and "outData" parameters for PiecewiseLinearTransformation must have the same size)";
            return false;
        }

        for (auto i = 0; i < inDataList->size(); i++)
        {
            double inValue = inDataList->get(i).asFloat64();
            double outValue = outDataList->get(i).asFloat64();

            inData.push_back(inValue);
            outData.push_back(outValue);

            yCDebug(BJC, "[%f, %f]", inValue, outValue);
        }
    }

    for (auto i = 1; i < inData.size(); i++)
    {
        if (inData[i] <= inData[i - 1])
        {
            yCError(BJC) << "Input data is not strictly increasing at line" << (i + 1) << "->" << inData[i] << "<=" << inData[i - 1];
            return false;
        }
    }

    for (auto i = 1; i < outData.size(); i++)
    {
        if (outData[i] <= outData[i - 1])
        {
            yCError(BJC) << "Output data is not strictly increasing at line" << (i + 1) << "->" << outData[i] << "<=" << outData[i - 1];
            return false;
        }
    }

    return true;
}

// -----------------------------------------------------------------------------

bool PiecewiseLinearTransformation::readCsvFile(const yarp::os::Searchable & parameters)
{
    auto csvFileName = parameters.find("csvFile").asString();
    auto context = parameters.find("context").asString();

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

    if (!context.empty())
    {
        rf.setDefaultContext(context);
    }

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

    yCInfo(BJC) << "Reading CSV file for PiecewiseLinearTransformation:" << csvFileFullName;

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

double PiecewiseLinearTransformation::position(const double value)
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

    return yL + dydx * (value - xL); // linear interpolation
}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::velocity(const double q, const double qdot)
{
    return 0.0; // TODO
}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::acceleration(const double q, const double qdot, const double qdotdot)
{
    return 0.0; // TODO
}

// -----------------------------------------------------------------------------

Transformation * roboticslab::createTransformation(const yarp::os::Searchable & parameters)
{
    if (!parameters.check("transformation"))
    {
        yCError(BJC) << R"("transformation" parameter for transformation not found)";
        return nullptr;
    }

    const auto type = parameters.find("transformation").asString();

    Transformation * instance;

    if (type == "linear")
    {
        instance = new LinearTransformation();
    }
    else if (type == "piecewiseLinear")
    {
        instance = new PiecewiseLinearTransformation();
    }
    else
    {
        yCError(BJC) << "Unknown transformation type:" << type;
        return nullptr;
    }

    if (!instance->configure(parameters))
    {
        yCError(BJC) << "Failed to configure transformation of type:" << type;
        delete instance;
        return nullptr;
    }

    return instance;
}

// -----------------------------------------------------------------------------

Transformation * PiecewiseLinearTransformation::inverse()
{
    auto * inverse = new PiecewiseLinearTransformation();
    inverse->inData = outData;
    inverse->outData = inData;
    return inverse;
}

// -----------------------------------------------------------------------------
