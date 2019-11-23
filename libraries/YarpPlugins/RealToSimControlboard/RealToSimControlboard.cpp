// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

namespace roboticslab
{

// -----------------------------------------------------------------------------

ExposedJointControlledDevice::ExposedJointControlledDevice(std::string name, yarp::dev::PolyDriver *device) : name(name)
{
    if(! device->view(iPositionControl) )
    {
        CD_DEBUG("%s: NO view IPositionControl\n", name.c_str());
        iPositionControl = nullptr;
    }
    else
        CD_DEBUG("%s: view IPositionControl\n", name.c_str());
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::addControlledDeviceJoint(int idx)
{
    controlledDeviceJoints.push_back(idx);
    axes = controlledDeviceJoints.size();
    return true;
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::addTransformation(const std::string& transformation)
{
    return true;
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
        refs[i] = ref * 1 + 0;

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
