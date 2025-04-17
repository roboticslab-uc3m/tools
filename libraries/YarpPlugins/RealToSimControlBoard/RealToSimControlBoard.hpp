// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __REAL_TO_SIM_CONTROL_BOARD_HPP__
#define __REAL_TO_SIM_CONTROL_BOARD_HPP__

#include <vector>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>

#include "Transformation.hpp"
#include "RealToSimControlBoard_ParamsParser.h"

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

} // namespace roboticslab

/**
 * @ingroup YarpPlugins
 * @defgroup RealToSimControlBoard
 *
 * @brief Contains RealToSimControlBoard.
 */

/**
 * @ingroup RealToSimControlBoard
 * @brief Implements the YARP_dev IPositionControl, etc.
 * interface class member functions.
 */
class RealToSimControlBoard : public yarp::dev::DeviceDriver,
                              public yarp::dev::IControlMode,
                              public yarp::dev::IEncodersTimed,
                              public yarp::dev::IPositionControl,
                              public yarp::dev::IVelocityControl,
                              public RealToSimControlBoard_ParamsParser
{
public:
    // -------- DeviceDriver declarations. Implementation in IDeviceImpl.cpp --------

    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    //  --------- IControlMode declarations. Implementation in IControlModeImpl.cpp ---------

    bool getControlMode(int j, int * mode) override;
    bool getControlModes(int * modes) override;
    bool getControlModes(int n_joint, const int * joints, int * modes) override;
    bool setControlMode(int j, const int mode) override;
    bool setControlModes(int n_joint, const int * joints, int * modes) override;
    bool setControlModes(int * modes) override;

    //  ---------- IEncodersTimed Declarations. Implementation in IEncodersTimedImpl.cpp ----------

    bool getEncodersTimed(double *encs, double *time) override;
    bool getEncoderTimed(int j, double *encs, double *time) override;
    bool resetEncoder(int j) override;
    bool resetEncoders() override;
    bool setEncoder(int j, double val) override;
    bool setEncoders(const double *vals) override;
    bool getEncoder(int j, double *v) override;
    bool getEncoders(double *encs) override;
    bool getEncoderSpeed(int j, double *sp) override;
    bool getEncoderSpeeds(double *spds) override;
    bool getEncoderAcceleration(int j, double *spds) override;
    bool getEncoderAccelerations(double *accs) override;

    // ------- IPositionControl declarations. Implementation in IPositionControlImpl.cpp -------

    bool getAxes(int *ax) override;
    bool positionMove(int j, double ref) override;
    bool positionMove(const double *refs) override;
    bool relativeMove(int j, double delta) override;
    bool relativeMove(const double *deltas) override;
    bool checkMotionDone(int j, bool *flag) override;
    bool checkMotionDone(bool *flag) override;
    bool setRefSpeed(int j, double sp) override;
    bool setRefSpeeds(const double *spds) override;
    bool setRefAcceleration(int j, double acc) override;
    bool setRefAccelerations(const double *accs) override;
    bool getRefSpeed(int j, double *ref) override;
    bool getRefSpeeds(double *spds) override;
    bool getRefAcceleration(int j, double *acc) override;
    bool getRefAccelerations(double *accs) override;
    bool stop(int j) override;
    bool stop() override;
    bool positionMove(const int n_joint, const int *joints, const double *refs) override;
    bool relativeMove(const int n_joint, const int *joints, const double *deltas) override;
    bool checkMotionDone(const int n_joint, const int *joints, bool *flags) override;
    bool setRefSpeeds(const int n_joint, const int *joints, const double *spds) override;
    bool setRefAccelerations(const int n_joint, const int *joints, const double *accs) override;
    bool getRefSpeeds(const int n_joint, const int *joints, double *spds) override;
    bool getRefAccelerations(const int n_joint, const int *joints, double *accs) override;
    bool stop(const int n_joint, const int *joints) override;
    bool getTargetPosition(const int joint, double *ref) override;
    bool getTargetPositions(double *refs) override;
    bool getTargetPositions(const int n_joint, const int *joints, double *refs) override;

    //  --------- IVelocityControl Declarations. Implementation in IVelocityControlImpl.cpp ---------

    bool velocityMove(int j, double sp) override;
    bool velocityMove(const double *sp) override;
    bool velocityMove(const int n_joint, const int *joints, const double *spds) override;
    bool getRefVelocity(const int joint, double *vel) override;
    bool getRefVelocities(double *vels) override;
    bool getRefVelocities(const int n_joint, const int *joints, double *vels) override;

private:
    enum jmc_mode { POSITION_MODE, VELOCITY_MODE, POSITION_DIRECT_MODE };

    // General Joint Motion Controller parameters //
    unsigned int axes;
    jmc_mode controlMode;

    std::vector<double> storedPositions;
    std::vector<yarp::dev::PolyDriver *> controlledDevices;
    std::vector<roboticslab::ExposedJoint *> exposedJoints;
};

#endif // __REAL_TO_SIM_CONTROL_BOARD_HPP__
