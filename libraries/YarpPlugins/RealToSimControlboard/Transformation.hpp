// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include <yarp/os/all.h>

#include <vector>

#include "ColorDebug.h"

namespace roboticslab
{

class Transformation
{
public:
    Transformation() : valid(false) {}
    virtual ~Transformation() {}
    bool isValid() const { return valid; }
    virtual double transform(double value) = 0;
protected:
    bool valid;
};

class LinearTransformation : public Transformation
{
public:
    LinearTransformation(yarp::os::Searchable* parameters);
    double transform(double value) override;
private:
    double m, b;
};

class PiecewiseLinearTransformation : public Transformation
{
public:
    PiecewiseLinearTransformation(yarp::os::Searchable* parameters);
    double transform(double value) override;
private:
    std::vector<double> inData;
    std::vector<double> outData;
};

}  // namespace roboticslab

#endif  // __TRANSFORMATION_HPP__
