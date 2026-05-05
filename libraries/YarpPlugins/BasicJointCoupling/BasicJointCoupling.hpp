// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __BASIC_JOINT_COUPLING_HPP__
#define __BASIC_JOINT_COUPLING_HPP__

#include <string>
#include <unordered_map>
#include <vector>

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/IJointCoupling.h>

#include "BasicJointCoupling_ParamsParser.h"
#include "Transformation.hpp"

/**
 * @ingroup YarpPlugins
 * @defgroup BasicJointCoupling
 * @brief Contains BasicJointCoupling.
 */

/**
 * @ingroup BasicJointCoupling
 * @brief Implements yarp::dev::IJointCoupling.
 *
 * Assumes 1:N subactuated joints with no mixing across actuated axes, i.e.
 * each physical joint is coupled with exactly one actuated axis, while each
 * actuated axis can be coupled with one or more physical joints. This device
 * is best suited for tendon-like couplings supported by springs to restore the
 * initial position, e.g. the LacqueyFetch gripper or the Dextra hand. In case
 * of ambiguity in physical-to-actuated mappings, the lowest value for the
 * actuated axis is chosen across all coupled physical joints during
 * transformations.
 */
class BasicJointCoupling : public yarp::dev::DeviceDriver,
                           public yarp::dev::IJointCoupling,
                           public BasicJointCoupling_ParamsParser
{
public:
    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------
    bool open(yarp::os::Searchable & config) override;
    bool close() override;

    // -------- IJointCoupling declarations. Implementation in JointCouplingImpl.cpp --------
    bool convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos) override;
    bool convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel) override;
    bool convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc) override;
    bool convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq) override;
    bool convertFromActuatedAxesToPhysicalJointsPos(const yarp::sig::Vector & actAxesPos, yarp::sig::Vector & physJointsPos) override;
    bool convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel) override;
    bool convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc) override;
    bool convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq) override;
    bool getNrOfPhysicalJoints(std::size_t & nrOfPhysicalJoints) override;
    bool getNrOfActuatedAxes(std::size_t & nrOfActuatedAxes) override;
    bool getCoupledPhysicalJoints(yarp::sig::VectorOf<std::size_t> & coupPhysJointsIndexes) override;
    bool getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes) override;
    bool getActuatedAxisName(std::size_t actuatedAxisIndex, std::string & actuatedAxisName) override;
    bool getPhysicalJointName(std::size_t physicalJointIndex, std::string & physicalJointName) override;
    bool getPhysicalJointLimits(std::size_t physicalJointIndex, double & min, double & max) override;

private:
    int numberOfActuatedAxes {0};
    int numberOfPhysicalJoints {0};

    std::vector<std::string> actuatedAxesNames;
    std::vector<std::string> physicalJointsNames;

    std::vector<double> physicalJointLimitsMins;
    std::vector<double> physicalJointLimitsMaxs;

    std::unordered_map<int, std::pair<int, roboticslab::Transformation *>> physicalToActuated;
    std::unordered_multimap<int, std::pair<int, roboticslab::Transformation *>> actuatedToPhysical;

    std::vector<std::size_t> coupledActuatedAxesIndexes;
    std::vector<std::size_t> coupledPhysicalJointsIndexes;
};

#endif // __BASIC_JOINT_COUPLING_HPP__
