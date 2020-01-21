// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __REAL_TO_SIM_CONTROLBOARD_HPP__
#define __REAL_TO_SIM_CONTROLBOARD_HPP__

#include <vector>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "ColorDebug.h"

#include "Transformation.hpp"

namespace roboticslab
{

class ExposedJointControlledDevice
{
public:
    ExposedJointControlledDevice(std::string name, yarp::dev::PolyDriver* device);
    ~ExposedJointControlledDevice();
    bool addControlledDeviceJoint(yarp::os::Searchable* parameters);
    bool positionMove(double ref);
private:
    std::string name;
    size_t axes; // same as controlledDeviceJoints.size()
    std::vector<int> controlledDeviceJoints;
    std::vector<Transformation*> transformations;
    yarp::dev::IPositionControl* iPositionControl;
};

class ExposedJoint
{
public:
    ExposedJoint(std::string name);
    ~ExposedJoint();
    void addExposedJointControlledDevice(ExposedJointControlledDevice* exposedJointControlledDevice);
    bool positionMove(double ref);
private:
    std::vector<ExposedJointControlledDevice*> exposedJointControlledDevices;
    std::string name;
};

/**
 * @ingroup YarpPlugins
 * \defgroup RealToSimControlboard
 *
 * @brief Contains roboticslab::RealToSimControlboard.
 */

/**
 * @ingroup RealToSimControlboard
 * @brief Implements the YARP_dev IPositionControl, etc.
 * interface class member functions.
 */
class RealToSimControlboard :
        public yarp::dev::DeviceDriver,
        public yarp::dev::IControlMode,
        public yarp::dev::IEncodersTimed,
        public yarp::dev::IPositionControl,
        public yarp::dev::IVelocityControl
{
public:

    // -------- DeviceDriver declarations. Implementation in IDeviceImpl.cpp --------

    virtual bool open(yarp::os::Searchable& config) override;
    virtual bool close() override;

    //  --------- IControlMode declarations. Implementation in IControlModeImpl.cpp ---------

    virtual bool getControlMode(int j, int * mode) override;
    virtual bool getControlModes(int * modes) override;
    virtual bool getControlModes(int n_joint, const int * joints, int * modes) override;
    virtual bool setControlMode(int j, const int mode) override;
    virtual bool setControlModes(int n_joint, const int * joints, int * modes) override;
    virtual bool setControlModes(int * modes) override;

    //  ---------- IEncodersTimed Declarations. Implementation in IEncodersTimedImpl.cpp ----------

    virtual bool getEncodersTimed(double *encs, double *time) override;
    virtual bool getEncoderTimed(int j, double *encs, double *time) override;
    virtual bool resetEncoder(int j) override;
    virtual bool resetEncoders() override;
    virtual bool setEncoder(int j, double val) override;
    virtual bool setEncoders(const double *vals) override;
    virtual bool getEncoder(int j, double *v) override;
    virtual bool getEncoders(double *encs) override;
    virtual bool getEncoderSpeed(int j, double *sp) override;
    virtual bool getEncoderSpeeds(double *spds) override;
    virtual bool getEncoderAcceleration(int j, double *spds) override;
    virtual bool getEncoderAccelerations(double *accs) override;

    // ------- IPositionControl declarations. Implementation in IPositionControlImpl.cpp -------

    virtual bool getAxes(int *ax) override;
    virtual bool positionMove(int j, double ref) override;
    virtual bool positionMove(const double *refs) override;
    virtual bool relativeMove(int j, double delta) override;
    virtual bool relativeMove(const double *deltas) override;
    virtual bool checkMotionDone(int j, bool *flag) override;
    virtual bool checkMotionDone(bool *flag) override;
    virtual bool setRefSpeed(int j, double sp) override;
    virtual bool setRefSpeeds(const double *spds) override;
    virtual bool setRefAcceleration(int j, double acc) override;
    virtual bool setRefAccelerations(const double *accs) override;
    virtual bool getRefSpeed(int j, double *ref) override;
    virtual bool getRefSpeeds(double *spds) override;
    virtual bool getRefAcceleration(int j, double *acc) override;
    virtual bool getRefAccelerations(double *accs) override;
    virtual bool stop(int j) override;
    virtual bool stop() override;
    virtual bool positionMove(const int n_joint, const int *joints, const double *refs) override;
    virtual bool relativeMove(const int n_joint, const int *joints, const double *deltas) override;
    virtual bool checkMotionDone(const int n_joint, const int *joints, bool *flags) override;
    virtual bool setRefSpeeds(const int n_joint, const int *joints, const double *spds) override;
    virtual bool setRefAccelerations(const int n_joint, const int *joints, const double *accs) override;
    virtual bool getRefSpeeds(const int n_joint, const int *joints, double *spds) override;
    virtual bool getRefAccelerations(const int n_joint, const int *joints, double *accs) override;
    virtual bool stop(const int n_joint, const int *joints) override;
    virtual bool getTargetPosition(const int joint, double *ref) override;
    virtual bool getTargetPositions(double *refs) override;
    virtual bool getTargetPositions(const int n_joint, const int *joints, double *refs) override;

    //  --------- IVelocityControl Declarations. Implementation in IVelocityControlImpl.cpp ---------

    virtual bool velocityMove(int j, double sp) override;
    virtual bool velocityMove(const double *sp) override;
    virtual bool velocityMove(const int n_joint, const int *joints, const double *spds) override;
    virtual bool getRefVelocity(const int joint, double *vel) override;
    virtual bool getRefVelocities(double *vels) override;
    virtual bool getRefVelocities(const int n_joint, const int *joints, double *vels) override;


private:

    // General Joint Motion Controller parameters //
    unsigned int axes;

    std::vector<double> storedPositions;

    //yarp::os::Network yarp; // Uncomment if required
    std::vector<yarp::dev::PolyDriver*> controlledDevices;

    std::vector<ExposedJoint*> exposedJoints;

};

}  // namespace roboticslab

#endif  // __REAL_TO_SIM_CONTROLBOARD_HPP__
