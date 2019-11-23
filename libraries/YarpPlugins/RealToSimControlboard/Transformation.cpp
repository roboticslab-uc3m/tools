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
}

// -----------------------------------------------------------------------------

double LinearTransformation::transform(const double& value)
{
    return value * m + b;
}

// -----------------------------------------------------------------------------

PiecewiseLinearTransformation::PiecewiseLinearTransformation(yarp::os::Searchable* parameters)
{
    if(!parameters->check("file"))
    {
        CD_ERROR("**** \"file\" for PiecewiseLinearTransformation NOT found\n");
        return;
    }
    CD_DEBUG("**** \"file\" for PiecewiseLinearTransformation found\n");
    std::string fileName = parameters->find("file").asString();

    std::ifstream file(fileName);
    if(!file.is_open())
    {
        CD_ERROR("**** file \"%s\" for PiecewiseLinearTransformation NOT open\n");
        return;
    }
    CD_ERROR("**** file \"%s\" for PiecewiseLinearTransformation NOT open\n");

}

// -----------------------------------------------------------------------------

double PiecewiseLinearTransformation::transform(const double& value)
{
    return value;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
