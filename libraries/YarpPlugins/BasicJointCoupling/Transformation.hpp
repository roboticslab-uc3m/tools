// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include <yarp/os/Searchable.h>

#include <vector>

namespace roboticslab
{

class Transformation
{
public:
    Transformation(int actAxisIndex, int physJointIndex);
    virtual ~Transformation() = default;
    virtual bool configure(const yarp::os::Searchable & parameters) = 0;
    virtual double transform(double value) = 0;
    int getActuatedAxisIndex() const { return actAxisIndex; }
    int getPhysicalJointIndex() const { return physJointIndex; }
private:
    const int actAxisIndex;
    const int physJointIndex;
};

class LinearTransformation : public Transformation
{
public:
    using Transformation::Transformation;
    bool configure(const yarp::os::Searchable & parameters) override;
    double transform(double value) override;
private:
    double m {0.0};
    double b {0.0};
};

class PiecewiseLinearTransformation : public Transformation
{
public:
    using Transformation::Transformation;
    bool configure(const yarp::os::Searchable & parameters) override;
    double transform(double value) override;
private:
    std::vector<double> inData;
    std::vector<double> outData;
};

} // namespace roboticslab

#endif // __TRANSFORMATION_HPP__
