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
