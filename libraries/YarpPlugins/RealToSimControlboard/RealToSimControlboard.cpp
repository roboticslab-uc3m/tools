// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <sstream>

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

FileLUTTransformation::FileLUTTransformation(yarp::os::Searchable* parameters)
{
}

// -----------------------------------------------------------------------------

double FileLUTTransformation::transform(const double& value)
{
    return value;
}

// -----------------------------------------------------------------------------

ExposedJointControlledDevice::ExposedJointControlledDevice(std::string name, yarp::dev::PolyDriver *device) : name(name)
{
    CD_DEBUG("** %s\n", name.c_str());
    if(! device->view(iPositionControl) )
    {
        CD_DEBUG("** NO view IPositionControl\n");
        iPositionControl = nullptr;
    }
    else
        CD_DEBUG("** view IPositionControl\n");
}

// -----------------------------------------------------------------------------

ExposedJointControlledDevice::~ExposedJointControlledDevice()
{
    for(size_t i=0;i<transformations.size();i++)
    {
        delete transformations[i];
        transformations[i] = 0;
    }
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::addControlledDeviceJoint(yarp::os::Searchable* parameters)
{
    if(!parameters->check("joint"))
    {
        CD_ERROR("*** \"joint\" (index) for joint NOT found\n");
        return false;
    }
    CD_DEBUG("*** \"joint\" (index) for joint found\n");
    int jointIdx = parameters->find("joint").asInt();
    controlledDeviceJoints.push_back(jointIdx);
    axes = controlledDeviceJoints.size();

    if(!parameters->check("transformation"))
    {
        CD_ERROR("*** \"transformation\" for joint NOT found\n");
        return false;
    }
    CD_DEBUG("*** \"transformation\" for joint found\n");
    std::string transformation = parameters->find("transformation").asString();

    if(transformation == "linear")
    {
        CD_DEBUG("*** transformation of type \"%s\" set\n", transformation.c_str());
        Transformation* transformation = new LinearTransformation(parameters);
        transformations.push_back(transformation);
        return true;
    }
    CD_ERROR("*** transformation of type \"%s\" NOT implemented \n",transformation.c_str());
    return false;
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::positionMove(double ref)
{
    CD_INFO("* %s: %f\n",name.c_str(), ref);
    if(iPositionControl == nullptr)
    {
        CD_DEBUG("%s: NO view IPositionControl\n", name.c_str());
        return true;
    }

    std::vector<double> refs(axes);
    for(size_t i=0; i<axes; i++)
        refs[i] = transformations[i]->transform(ref);

    return iPositionControl->positionMove(axes, controlledDeviceJoints.data(), refs.data());
}

// -----------------------------------------------------------------------------

ExposedJoint::ExposedJoint(std::string name) : name(name)
{
}

// -----------------------------------------------------------------------------

ExposedJoint::~ExposedJoint()
{
    for(size_t i=0;i<exposedJointControlledDevices.size();i++)
    {
        delete exposedJointControlledDevices[i];
        exposedJointControlledDevices[i] = 0;
    }
}

// -----------------------------------------------------------------------------

void ExposedJoint::addExposedJointControlledDevice(ExposedJointControlledDevice* exposedJointControlledDevice)
{
    exposedJointControlledDevices.push_back(exposedJointControlledDevice);
}

// -----------------------------------------------------------------------------

bool ExposedJoint::positionMove(double ref)
{
    CD_INFO("%s: %f\n",name.c_str(), ref);
    bool ok = true;
    for(size_t i=0; i<exposedJointControlledDevices.size();i++)
        ok &= exposedJointControlledDevices[i]->positionMove(ref);
    return true;
}

// -----------------------------------------------------------------------------

}  // namespace roboticslab
