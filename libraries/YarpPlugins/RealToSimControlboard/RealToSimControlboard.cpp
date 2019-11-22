// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

namespace roboticslab
{

// -----------------------------------------------------------------------------

ExposedJointControlledDevice::ExposedJointControlledDevice(std::string name, yarp::dev::PolyDriver *device) : name(name)
{
    if(! device->view(iPositionControl) )
        CD_DEBUG("%s: NO view IPositionControl\n", name.c_str());
    else
        CD_DEBUG("%s: view IPositionControl\n", name.c_str());
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::addControlledDeviceJoint(int idx)
{
    controlledDeviceJoints.push_back(idx);
    return true;
}

// -----------------------------------------------------------------------------

bool ExposedJointControlledDevice::positionMove(double ref)
{
    CD_INFO("* %s: %f\n",name.c_str(), ref);
    //positionMove(const int n_joint, const int *joints, const double *refs)
    //iPositionControl->
    return true;
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
