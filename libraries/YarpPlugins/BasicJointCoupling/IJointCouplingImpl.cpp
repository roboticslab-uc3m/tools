// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <limits>

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

// ------------------- IJointCoupling Related ------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    actAxesPos.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        double minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            double value = transformation->position(physJointsPos[physicalJointIndex]);

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesPos[actuatedAxisIndex] = minValue;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    if (physJointsVel.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of velocity vector does not match number of physical joints:" << physJointsVel.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    actAxesVel.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        double minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            double value = transformation->velocity(physJointsPos[physicalJointIndex], physJointsVel[physicalJointIndex]);

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesVel[actuatedAxisIndex] = minValue;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    if (physJointsVel.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of velocity vector does not match number of physical joints:" << physJointsVel.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    if (physJointsAcc.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of acceleration vector does not match number of physical joints:" << physJointsAcc.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    actAxesAcc.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        double minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            double value = transformation->acceleration(physJointsPos[physicalJointIndex], physJointsVel[physicalJointIndex], physJointsAcc[physicalJointIndex]);

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesAcc[actuatedAxisIndex] = minValue;
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq)
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
        return false;
    }

    if (physJointsTrq.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of torque vector does not match number of physical joints:" << physJointsTrq.size() << "!=" << numberOfPhysicalJoints;
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
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    physJointsPos.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsPos[physicalJointIndex] = transformation->position(actAxesPos[actuatedAxisIndex]);
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    if (actAxesVel.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of velocity vector does not match number of actuated axes:" << actAxesVel.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    physJointsVel.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsVel[physicalJointIndex] = transformation->velocity(actAxesPos[actuatedAxisIndex], actAxesVel[actuatedAxisIndex]);
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    if (actAxesVel.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of velocity vector does not match number of actuated axes:" << actAxesVel.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    if (actAxesAcc.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of acceleration vector does not match number of actuated axes:" << actAxesAcc.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    physJointsAcc.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsAcc[physicalJointIndex] = transformation->acceleration(actAxesPos[actuatedAxisIndex], actAxesVel[actuatedAxisIndex], actAxesAcc[actuatedAxisIndex]);
    }

    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq)
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
        return false;
    }

    if (actAxesTrq.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of torque vector does not match number of actuated axes:" << actAxesTrq.size() << "!=" << numberOfActuatedAxes;
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
    coupPhysJointsIndexes = yarp::sig::VectorOf<std::size_t>(coupledPhysicalJointsIndexes.size(), coupledPhysicalJointsIndexes.data());
    return true;
}

// -----------------------------------------------------------------------------

bool BasicJointCoupling::getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes)
{
    coupActAxesIndexes = yarp::sig::VectorOf<std::size_t>(coupledActuatedAxesIndexes.size(), coupledActuatedAxesIndexes.data());
    return true;
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
