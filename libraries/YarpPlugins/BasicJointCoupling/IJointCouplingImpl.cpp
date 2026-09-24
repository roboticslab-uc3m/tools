// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "BasicJointCoupling.hpp"

#include <algorithm> // std::clamp
#include <limits>

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

// ------------------- IJointCoupling Related ------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos)
#else
bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesPos(const yarp::sig::Vector & physJointsPos, yarp::sig::Vector & actAxesPos)
#endif
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    actAxesPos.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        auto minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            auto position = physJointsPos[physicalJointIndex];
            auto minLimit = physicalJointLimitsMins[physicalJointIndex];
            auto maxLimit = physicalJointLimitsMaxs[physicalJointIndex];
            auto value = transformation->position(std::clamp(position, minLimit, maxLimit));

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesPos[actuatedAxisIndex] = minValue;
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel)
#else
bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesVel(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, yarp::sig::Vector & actAxesVel)
#endif
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (physJointsVel.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of velocity vector does not match number of physical joints:" << physJointsVel.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    actAxesVel.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        auto minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            auto value = transformation->velocity(physJointsPos[physicalJointIndex], physJointsVel[physicalJointIndex]);

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesVel[actuatedAxisIndex] = minValue;
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc)
#else
bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesAcc(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsVel, const yarp::sig::Vector & physJointsAcc, yarp::sig::Vector & actAxesAcc)
#endif
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (physJointsVel.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of velocity vector does not match number of physical joints:" << physJointsVel.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (physJointsAcc.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of acceleration vector does not match number of physical joints:" << physJointsAcc.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    actAxesAcc.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        auto minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            auto value = transformation->acceleration(physJointsPos[physicalJointIndex], physJointsVel[physicalJointIndex], physJointsAcc[physicalJointIndex]);

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesAcc[actuatedAxisIndex] = minValue;
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq)
#else
bool BasicJointCoupling::convertFromPhysicalJointsToActuatedAxesTrq(const yarp::sig::Vector & physJointsPos, const yarp::sig::Vector & physJointsTrq, yarp::sig::Vector & actAxesTrq)
#endif
{
    if (physJointsPos.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of position vector does not match number of physical joints:" << physJointsPos.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (physJointsTrq.size() != numberOfPhysicalJoints)
    {
        yCError(BJC) << "Size of torque vector does not match number of physical joints:" << physJointsTrq.size() << "!=" << numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    actAxesTrq.resize(numberOfActuatedAxes);

    for (auto actuatedAxisIndex = 0; actuatedAxisIndex < numberOfActuatedAxes; actuatedAxisIndex++)
    {
        auto range = actuatedToPhysical.equal_range(actuatedAxisIndex);
        auto minValue = std::numeric_limits<double>::max();

        for (auto it = range.first; it != range.second; ++it)
        {
            auto [physicalJointIndex, transformation] = it->second;
            auto value = physJointsTrq[physicalJointIndex];

            if (value < minValue)
            {
                minValue = value;
            }
        }

        actAxesTrq[actuatedAxisIndex] = minValue;
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsPos(const yarp::sig::Vector & actAxesPos, yarp::sig::Vector & physJointsPos)
#else
bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsPos(const yarp::sig::Vector & actAxesPos, yarp::sig::Vector & physJointsPos)
#endif
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    physJointsPos.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        auto position = transformation->position(actAxesPos[actuatedAxisIndex]);
        auto minValue = physicalJointLimitsMins[physicalJointIndex];
        auto maxValue = physicalJointLimitsMaxs[physicalJointIndex];
        physJointsPos[physicalJointIndex] = std::clamp(position, minValue, maxValue);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel)
#else
bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsVel(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, yarp::sig::Vector & physJointsVel)
#endif
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (actAxesVel.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of velocity vector does not match number of actuated axes:" << actAxesVel.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    physJointsVel.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsVel[physicalJointIndex] = transformation->velocity(actAxesPos[actuatedAxisIndex], actAxesVel[actuatedAxisIndex]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc)
#else
bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsAcc(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesVel, const yarp::sig::Vector & actAxesAcc, yarp::sig::Vector & physJointsAcc)
#endif
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (actAxesVel.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of velocity vector does not match number of actuated axes:" << actAxesVel.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (actAxesAcc.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of acceleration vector does not match number of actuated axes:" << actAxesAcc.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    physJointsAcc.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsAcc[physicalJointIndex] = transformation->acceleration(actAxesPos[actuatedAxisIndex], actAxesVel[actuatedAxisIndex], actAxesAcc[actuatedAxisIndex]);
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq)
#else
bool BasicJointCoupling::convertFromActuatedAxesToPhysicalJointsTrq(const yarp::sig::Vector & actAxesPos, const yarp::sig::Vector & actAxesTrq, yarp::sig::Vector & physJointsTrq)
#endif
{
    if (actAxesPos.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of position vector does not match number of actuated axes:" << actAxesPos.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    if (actAxesTrq.size() != numberOfActuatedAxes)
    {
        yCError(BJC) << "Size of torque vector does not match number of actuated axes:" << actAxesTrq.size() << "!=" << numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    physJointsTrq.resize(numberOfPhysicalJoints);

    for (auto physicalJointIndex = 0; physicalJointIndex < numberOfPhysicalJoints; physicalJointIndex++)
    {
        auto [actuatedAxisIndex, transformation] = physicalToActuated[physicalJointIndex];
        physJointsTrq[physicalJointIndex] = actAxesTrq[actuatedAxisIndex];
    }

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getNrOfPhysicalJoints(std::size_t & nrOfPhysicalJoints)
#else
bool BasicJointCoupling::getNrOfPhysicalJoints(std::size_t & nrOfPhysicalJoints)
#endif
{
    nrOfPhysicalJoints = numberOfPhysicalJoints;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getNrOfActuatedAxes(std::size_t & nrOfActuatedAxes)
#else
bool BasicJointCoupling::getNrOfActuatedAxes(std::size_t & nrOfActuatedAxes)
#endif
{
    nrOfActuatedAxes = numberOfActuatedAxes;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getCoupledPhysicalJoints(yarp::sig::VectorOf<std::size_t> & coupPhysJointsIndexes)
#else
bool BasicJointCoupling::getCoupledPhysicalJoints(yarp::sig::VectorOf<std::size_t> & coupPhysJointsIndexes)
#endif
{
    coupPhysJointsIndexes = yarp::sig::VectorOf<std::size_t>(coupledPhysicalJointsIndexes.size(), coupledPhysicalJointsIndexes.data());
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes)
#else
bool BasicJointCoupling::getCoupledActuatedAxes(yarp::sig::VectorOf<std::size_t> & coupActAxesIndexes)
#endif
{
    coupActAxesIndexes = yarp::sig::VectorOf<std::size_t>(coupledActuatedAxesIndexes.size(), coupledActuatedAxesIndexes.data());
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getActuatedAxisName(std::size_t actuatedAxisIndex, std::string & actuatedAxisName)
#else
bool BasicJointCoupling::getActuatedAxisName(std::size_t actuatedAxisIndex, std::string & actuatedAxisName)
#endif
{
    if (actuatedAxisIndex < 0 || actuatedAxisIndex >= numberOfActuatedAxes)
    {
        yCError(BJC) << "Invalid actuated axis index:" << actuatedAxisIndex;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    actuatedAxisName = m_prefix + actuatedAxesNames[actuatedAxisIndex];
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getPhysicalJointName(std::size_t physicalJointIndex, std::string & physicalJointName)
#else
bool BasicJointCoupling::getPhysicalJointName(std::size_t physicalJointIndex, std::string & physicalJointName)
#endif
{
    if (physicalJointIndex < 0 || physicalJointIndex >= numberOfPhysicalJoints)
    {
        yCError(BJC) << "Invalid physical joint index:" << physicalJointIndex;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    physicalJointName = m_prefix + physicalJointsNames[physicalJointIndex];
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
yarp::dev::ReturnValue BasicJointCoupling::getPhysicalJointLimits(std::size_t physicalJointIndex, double & min, double & max)
#else
bool BasicJointCoupling::getPhysicalJointLimits(std::size_t physicalJointIndex, double & min, double & max)
#endif
{
    if (physicalJointIndex < 0 || physicalJointIndex >= numberOfPhysicalJoints)
    {
        yCError(BJC) << "Invalid physical joint index:" << physicalJointIndex;
#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
        return yarp::dev::ReturnValue_error_method_failed;
#else
        return false;
#endif
    }

    min = physicalJointLimitsMins[physicalJointIndex];
    max = physicalJointLimitsMaxs[physicalJointIndex];

#if YARP_VERSION_COMPARE(>=, 4, 0, 0)
    return yarp::dev::ReturnValue_ok;
#else
    return true;
#endif
}

// -----------------------------------------------------------------------------
