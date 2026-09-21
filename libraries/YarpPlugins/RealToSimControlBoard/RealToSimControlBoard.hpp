// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __REAL_TO_SIM_CONTROL_BOARD_HPP__
#define __REAL_TO_SIM_CONTROL_BOARD_HPP__

#include <vector>

#include <yarp/conf/version.h>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IControlMode.h>
#include <yarp/dev/IEncodersTimed.h>
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IVelocityControl.h>

#include "Transformation.hpp"
#include "RealToSimControlBoard_ParamsParser.h"

namespace roboticslab
{

class ExposedJointControlledDevice
{
public:
    ExposedJointControlledDevice(const std::string & name, yarp::dev::PolyDriver * device);
    ~ExposedJointControlledDevice();
    bool addControlledDeviceJoint(yarp::os::Searchable * parameters);
    bool positionMove(double ref);
private:
    std::string name;
    size_t axes {0}; // same as controlledDeviceJoints.size()
    std::vector<int> controlledDeviceJoints;
    std::vector<Transformation *> transformations;
    yarp::dev::IPositionControl * iPositionControl {nullptr};
};

class ExposedJoint
{
public:
    ExposedJoint(const std::string & name);
    ~ExposedJoint();
    void addExposedJointControlledDevice(ExposedJointControlledDevice * exposedJointControlledDevice);
    bool positionMove(double ref);
private:
    std::vector<ExposedJointControlledDevice *> exposedJointControlledDevices;
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

    bool open(yarp::os::Searchable & config) override;
    bool close() override;

    //  --------- IControlMode declarations. Implementation in IControlModeImpl.cpp ---------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    yarp::dev::ReturnValue getAvailableControlModes(int j, std::vector<yarp::dev::SelectableControlModeEnum> & avail) override;
    yarp::dev::ReturnValue getControlMode(int j, yarp::dev::ControlModeEnum & mode) override;
    yarp::dev::ReturnValue getControlModes(std::vector<yarp::dev::ControlModeEnum> & modes) override;
    yarp::dev::ReturnValue getControlModes(const std::vector<int> & joints, std::vector<yarp::dev::ControlModeEnum> & modes) override;
    yarp::dev::ReturnValue setControlMode(int j, yarp::dev::SelectableControlModeEnum mode) override;
    yarp::dev::ReturnValue setControlModes(const std::vector<yarp::dev::SelectableControlModeEnum> & modes) override;
    yarp::dev::ReturnValue setControlModes(const std::vector<int> & joints, const std::vector<yarp::dev::SelectableControlModeEnum> & modes) override;
#else
    bool getControlMode(int j, int * mode) override;
    bool getControlModes(int * modes) override;
    bool getControlModes(int n_joint, const int * joints, int * modes) override;
    bool setControlMode(int j, int mode) override;
    bool setControlModes(int n_joint, const int * joints, int * modes) override;
    bool setControlModes(int * modes) override;
#endif

    //  ---------- IEncodersTimed Declarations. Implementation in IEncodersTimedImpl.cpp ----------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    yarp::dev::ReturnValue getEncodersTimed(double * encs, double * time) override;
    yarp::dev::ReturnValue getEncoderTimed(int j, double * encs, double * time) override;
    yarp::dev::ReturnValue resetEncoder(int j) override;
    yarp::dev::ReturnValue resetEncoders() override;
    yarp::dev::ReturnValue setEncoder(int j, double val) override;
    yarp::dev::ReturnValue setEncoders(const double * vals) override;
    yarp::dev::ReturnValue getEncoder(int j, double * v) override;
    yarp::dev::ReturnValue getEncoders(double * encs) override;
    yarp::dev::ReturnValue getEncoderSpeed(int j, double * sp) override;
    yarp::dev::ReturnValue getEncoderSpeeds(double * spds) override;
    yarp::dev::ReturnValue getEncoderAcceleration(int j, double * spds) override;
    yarp::dev::ReturnValue getEncoderAccelerations(double * accs) override;
#else
    bool getEncodersTimed(double * encs, double * time) override;
    bool getEncoderTimed(int j, double * encs, double * time) override;
    bool resetEncoder(int j) override;
    bool resetEncoders() override;
    bool setEncoder(int j, double val) override;
    bool setEncoders(const double * vals) override;
    bool getEncoder(int j, double * v) override;
    bool getEncoders(double * encs) override;
    bool getEncoderSpeed(int j, double * sp) override;
    bool getEncoderSpeeds(double * spds) override;
    bool getEncoderAcceleration(int j, double * spds) override;
    bool getEncoderAccelerations(double * accs) override;
#endif

    // ------- IPositionControl declarations. Implementation in IPositionControlImpl.cpp -------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    yarp::dev::ReturnValue getAxes(std::size_t & ax) override;
    yarp::dev::ReturnValue positionMove(int j, double ref) override;
    yarp::dev::ReturnValue positionMove(const double * refs) override;
    yarp::dev::ReturnValue positionMove(int n_joint, const int * joints, const double * refs) override;
    yarp::dev::ReturnValue relativeMove(int j, double delta) override;
    yarp::dev::ReturnValue relativeMove(const double * deltas) override;
    yarp::dev::ReturnValue relativeMove(int n_joint, const int * joints, const double * deltas) override;
    yarp::dev::ReturnValue checkMotionDone(int j, bool & flag) override;
    yarp::dev::ReturnValue checkMotionDone(bool & flag) override;
    yarp::dev::ReturnValue checkMotionDone(const std::vector<int> & joints, bool & flag) override;
    yarp::dev::ReturnValue setTrajSpeed(int j, double sp) override;
    yarp::dev::ReturnValue setTrajSpeeds(const double * spds) override;
    yarp::dev::ReturnValue setTrajSpeeds(int n_joint, const int * joints, const double * spds) override;
    yarp::dev::ReturnValue setTrajAcceleration(int j, double acc) override;
    yarp::dev::ReturnValue setTrajAccelerations(const double * accs) override;
    yarp::dev::ReturnValue setTrajAccelerations(int n_joint, const int *joints, const double * accs) override;
    yarp::dev::ReturnValue getTrajSpeed(int j, double * ref) override;
    yarp::dev::ReturnValue getTrajSpeeds(double * spds) override;
    yarp::dev::ReturnValue getTrajSpeeds(int n_joint, const int * joints, double * spds) override;
    yarp::dev::ReturnValue getTrajAcceleration(int j, double * acc) override;
    yarp::dev::ReturnValue getTrajAccelerations(double *accs) override;
    yarp::dev::ReturnValue getTrajAccelerations(int n_joint, const int * joints, double * accs) override;
    yarp::dev::ReturnValue stop(int j) override;
    yarp::dev::ReturnValue stop() override;
    yarp::dev::ReturnValue stop(int n_joint, const int * joints) override;
    yarp::dev::ReturnValue getTargetPosition(int joint, double * ref) override;
    yarp::dev::ReturnValue getTargetPositions(double * refs) override;
    yarp::dev::ReturnValue getTargetPositions(int n_joint, const int * joints, double * refs) override;
#else
    bool getAxes(int * ax) override;
    bool positionMove(int j, double ref) override;
    bool positionMove(const double * refs) override;
    bool positionMove(int n_joint, const int * joints, const double * refs) override;
    bool relativeMove(int j, double delta) override;
    bool relativeMove(const double * deltas) override;
    bool relativeMove(int n_joint, const int * joints, const double * deltas) override;
    bool checkMotionDone(int j, bool * flag) override;
    bool checkMotionDone(bool * flag) override;
    bool checkMotionDone(int n_joint, const int * joints, bool * flags) override;
    bool setRefSpeed(int j, double sp) override;
    bool setRefSpeeds(const double * spds) override;
    bool setRefSpeeds(int n_joint, const int * joints, const double * spds) override;
    bool setRefAcceleration(int j, double acc) override;
    bool setRefAccelerations(const double * accs) override;
    bool setRefAccelerations(int n_joint, const int *joints, const double * accs) override;
    bool getRefSpeed(int j, double * ref) override;
    bool getRefSpeeds(double * spds) override;
    bool getRefSpeeds(int n_joint, const int * joints, double * spds) override;
    bool getRefAcceleration(int j, double * acc) override;
    bool getRefAccelerations(double *accs) override;
    bool getRefAccelerations(int n_joint, const int * joints, double * accs) override;
    bool stop(int j) override;
    bool stop() override;
    bool stop(int n_joint, const int * joints) override;
    bool getTargetPosition(int joint, double * ref) override;
    bool getTargetPositions(double * refs) override;
    bool getTargetPositions(int n_joint, const int * joints, double * refs) override;
#endif

    //  --------- IVelocityControl Declarations. Implementation in IVelocityControlImpl.cpp ---------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    yarp::dev::ReturnValue velocityMove(int j, double sp) override;
    yarp::dev::ReturnValue velocityMove(const double * sp) override;
    yarp::dev::ReturnValue velocityMove(int n_joint, const int * joints, const double * spds) override;
    yarp::dev::ReturnValue getTargetVelocity(int joint, double * vel) override;
    yarp::dev::ReturnValue getTargetVelocities(double * vels) override;
    yarp::dev::ReturnValue getTargetVelocities(int n_joint, const int *joints, double * vels) override;
#else
    bool velocityMove(int j, double sp) override;
    bool velocityMove(const double * sp) override;
    bool velocityMove(int n_joint, const int * joints, const double * spds) override;
    bool getRefVelocity(int joint, double * vel) override;
    bool getRefVelocities(double * vels) override;
    bool getRefVelocities(int n_joint, const int *joints, double * vels) override;
#endif

private:
    // General Joint Motion Controller parameters //
    unsigned int axes {0};
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    yarp::conf::vocab32_t controlMode {static_cast<yarp::conf::vocab32_t>(yarp::dev::ControlModeEnum::VOCAB_CM_POSITION)};
#else
    yarp::conf::vocab32_t controlMode {VOCAB_CM_POSITION};
#endif

    std::vector<double> storedPositions;
    std::vector<yarp::dev::PolyDriver *> controlledDevices;
    std::vector<roboticslab::ExposedJoint *> exposedJoints;
};

#endif // __REAL_TO_SIM_CONTROL_BOARD_HPP__
