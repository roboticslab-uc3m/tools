// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

#include <sstream>

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace roboticslab;

// -----------------------------------------------------------------------------

ExposedJointControlledDevice::ExposedJointControlledDevice(std::string name, yarp::dev::PolyDriver *device) : name(name)
{
    yCDebug(R2SCB, "** %s", name.c_str());
    if(! device->view(iPositionControl) )
    {
        yCDebug(R2SCB) << "** NO view IPositionControl";
        iPositionControl = nullptr;
    }
    else
        yCDebug(R2SCB) << "** view IPositionControl";
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
        yCError(R2SCB) << "*** \"joint\" (index) for joint NOT found";
        return false;
    }
    yCDebug(R2SCB) << "*** \"joint\" (index) for joint found";
    int jointIdx = parameters->find("joint").asInt32();
    controlledDeviceJoints.push_back(jointIdx);
    axes = controlledDeviceJoints.size();

    if(!parameters->check("transformation"))
    {
        yCError(R2SCB) << "*** \"transformation\" for joint NOT found";
        return false;
    }
    yCDebug(R2SCB) << "*** \"transformation\" for joint found";
    std::string transformation = parameters->find("transformation").asString();

    if(transformation == "linear")
    {
        yCDebug(R2SCB, "*** transformation of type \"%s\" set", transformation.c_str());
        Transformation* transformation = new LinearTransformation(parameters);
        if(!transformation->isValid())
            return false;
        transformations.push_back(transformation);
        return true;
    }
    else if(transformation == "piecewiseLinear")
    {
        yCDebug(R2SCB, "*** transformation of type \"%s\" set", transformation.c_str());
        Transformation* transformation = new PiecewiseLinearTransformation(parameters);
        if(!transformation->isValid())
            return false;
        transformations.push_back(transformation);
        return true;
    }
    yCError(R2SCB, "*** transformation of type \"%s\" NOT implemented",transformation.c_str());
    return false;
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::positionMove(double ref)
{
    yCInfo(R2SCB, "* %s: %f",name.c_str(), ref);
    if(iPositionControl == nullptr)
    {
        yCDebug(R2SCB, "%s: NO view IPositionControl", name.c_str());
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
    yCInfo(R2SCB, "%s: %f",name.c_str(), ref);
    bool ok = true;
    for(size_t i=0; i<exposedJointControlledDevices.size();i++)
        ok &= exposedJointControlledDevices[i]->positionMove(ref);
    return true;
}

// -----------------------------------------------------------------------------
