// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

// ------------------- IJointCoupling Related ------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsPos(const yarp::sig::Vector & actAxesPos, yarp::sig::Vector & physJointsPos)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getNrOfPhysicalJoints(std::size_t & nrOfPhysicalJoints)
{
    nrOfPhysicalJoints = numberOfPhysicalJoints;
    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getNrOfActuatedAxes(std::size_t & nrOfActuatedAxes)
{
    nrOfActuatedAxes = numberOfActuatedAxes;
    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getCoupledPhysicalJoints(yarp::sig::VectorOf<std::size_t> & coupPhysJointsIndexes)
{
    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes)
{
    yCError(BJC) << "Method not implemented yet";
    return false;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getActuatedAxisName(std::size_t actuatedAxisIndex, std::string & actuatedAxisName)
{
    if (actuatedAxisIndex < 0 || actuatedAxisIndex >= numberOfActuatedAxes)
    {
        yCError(BJC) << "Invalid actuated axis index:" << actuatedAxisIndex;
        return false;
    }

    actuatedAxisName = actuatedAxesNames[actuatedAxisIndex];
    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getPhysicalJointName(std::size_t physicalJointIndex, std::string & physicalJointName)
{
    if (physicalJointIndex < 0 || physicalJointIndex >= numberOfPhysicalJoints)
    {
        yCError(BJC) << "Invalid physical joint index:" << physicalJointIndex;
        return false;
    }

    physicalJointName = physicalJointsNames[physicalJointIndex];
    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getPhysicalJointLimits(std::size_t physicalJointIndex, double & min, double & max)
{
    if (physicalJointIndex < 0 || physicalJointIndex >= numberOfPhysicalJoints)
    {
        yCError(BJC) << "Invalid physical joint index:" << physicalJointIndex;
        return false;
    }

    min = physicalJointLimitsMins[physicalJointIndex];
    max = physicalJointLimitsMaxs[physicalJointIndex];
    return true;
}

// -----------------------------------------------------------------------------
