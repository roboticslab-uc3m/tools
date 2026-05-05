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
    virtual ~Transformation() = default;
    virtual bool configure(const yarp::os::Searchable & parameters) = 0;
    virtual double position(double q) = 0;
    virtual double velocity(double q, double qdot) = 0;
    virtual double acceleration(double q, double qdot, double qdotdot) = 0;
    virtual Transformation * inverse() { return nullptr; }
};

class LinearTransformation : public Transformation
{
public:
    bool configure(const yarp::os::Searchable & parameters) override;
    double position(double q) override;
    double velocity(double q, double qdot) override;
    double acceleration(double q, double qdot, double qdotdot) override;
private:
    double m {0.0};
    double b {0.0};
};

class PiecewiseLinearTransformation : public Transformation
{
public:
    bool configure(const yarp::os::Searchable & parameters) override;
    double position(double q) override;
    double velocity(double q, double qdot) override;
    double acceleration(double q, double qdot, double qdotdot) override;
private:
    std::vector<double> inData;
    std::vector<double> outData;
};

Transformation * createTransformation(const yarp::os::Searchable & parameters);

} // namespace roboticslab

#endif // __TRANSFORMATION_HPP__
