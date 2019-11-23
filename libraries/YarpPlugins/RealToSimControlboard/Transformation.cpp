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
        CD_ERROR("**** \"m\" for LinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"m\" for LinearTransformation found\n");
    m = parameters->find("m").asDouble();

    if(!parameters->check("b"))
    {
        CD_ERROR("**** \"b\" for LinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"b\" for LinearTransformation found\n");
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
        CD_ERROR("**** \"csvFile\" for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"csvFile\" for PiecewiseLinearTransformation found\n");
    std::string csvFileName = parameters->find("csvFile").asString();

    std::ifstream csvFile(csvFileName);
    if(!csvFile.is_open())
    {
        CD_ERROR("**** csvFile \"%s\" for PiecewiseLinearTransformation NOT open\n", csvFileName.c_str());
        return;
    }
    CD_DEBUG("**** csvFile \"%s\" for PiecewiseLinearTransformation open\n", csvFileName.c_str());

    valid = true;
}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::transform(const double& value)
{
    return value;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
