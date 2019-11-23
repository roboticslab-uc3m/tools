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
                xData.push_back(d);
            if(outColumn == idx)
                yData.push_back(d);
            idx++;
        }
        CD_DEBUG("***** %s [%f, %f]\n", line.c_str(), xData[xData.size()-1], yData[yData.size()-1]);
    }

    csvFile.close();

    valid = true;
}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::transform(const double& value)
{
    return value;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
