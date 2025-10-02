// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __BASIC_JOINT_COUPLING_HPP__
#define __BASIC_JOINT_COUPLING_HPP__

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/IJointCoupling.h>

#include "BasicJointCoupling_ParamsParser.h"

/**
 * @ingroup YarpPlugins
 * @defgroup BasicJointCoupling
 * @brief Contains BasicJointCoupling.
 */

/**
 * @ingroup BasicJointCoupling
 * @brief Implements yarp::dev::IJointCoupling.
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
};

#endif // __BASIC_JOINT_COUPLING_HPP__
