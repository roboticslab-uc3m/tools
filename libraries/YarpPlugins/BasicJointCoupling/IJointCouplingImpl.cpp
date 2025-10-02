// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

// ------------------- IJointCoupling Related ------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsPos(const yarp::sig::Vector & actAxesPos, yarp::sig::Vector & physJointsPos)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getNrOfPhysicalJoints(std::size_t & nrOfPhysicalJoints)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getNrOfActuatedAxes(std::size_t & nrOfActuatedAxes)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getCoupledPhysicalJoints(yarp::sig::VectorOf<std::size_t> & coupPhysJointsIndexes)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getActuatedAxisName(std::size_t actuatedAxisIndex, std::string & actuatedAxisName)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getPhysicalJointName(std::size_t physicalJointIndex, std::string & physicalJointName)
{
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getPhysicalJointLimits(std::size_t physicalJointIndex, double & min, double & max)
{
    return false;
}

// -----------------------------------------------------------------------------
