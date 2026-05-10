// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __TRANSFORMATION_HPP__
#define __TRANSFORMATION_HPP__

#include <yarp/os/Searchable.h>

#include <vector>

namespace roboticslab
{

class Transformation
{
    friend Transformation * createTransformation(const yarp::os::Searchable & parameters);
public:
    virtual ~Transformation() = default;
    virtual double position(double q) = 0;
    virtual double velocity(double q, double qdot) = 0;
    virtual double acceleration(double q, double qdot, double qdotdot) = 0;
    virtual Transformation * inverse() = 0;
protected:
    virtual bool configure(const yarp::os::Searchable & parameters) = 0;
};

class LinearTransformation : public Transformation
{
    friend Transformation * createTransformation(const yarp::os::Searchable & parameters);
public:
    double position(double q) override;
    double velocity(double q, double qdot) override;
    double acceleration(double q, double qdot, double qdotdot) override;
    Transformation * inverse() override;
protected:
    LinearTransformation() = default;
    bool configure(const yarp::os::Searchable & parameters) override;
private:
    double m {0.0};
    double b {0.0};
};

class PiecewiseLinearTransformation : public Transformation
{
    friend Transformation * createTransformation(const yarp::os::Searchable & parameters);
public:
    double position(double q) override;
    double velocity(double q, double qdot) override;
    double acceleration(double q, double qdot, double qdotdot) override;
    Transformation * inverse() override;
protected:
    PiecewiseLinearTransformation() = default;
    bool configure(const yarp::os::Searchable & parameters) override;
private:
    bool readCsvFile(const yarp::os::Searchable & parameters);
    std::vector<double> inData;
    std::vector<double> outData;
};

Transformation * createTransformation(const yarp::os::Searchable & parameters);

} // namespace roboticslab

#endif // __TRANSFORMATION_HPP__
