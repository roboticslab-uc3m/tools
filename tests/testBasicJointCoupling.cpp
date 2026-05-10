#include "gtest/gtest.h"

#include <yarp/conf/filesystem.h>

#include <yarp/os/LogStream.h>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IJointCoupling.h>

namespace roboticslab::test
{

/**
 * @ingroup roboticslab-tools-tests
 * @brief Tests @ref BasicJointCoupling
 */
class BasicJointCouplingTest : public testing::Test
{
public:
    void SetUp() override
    {
        std::string fileName = "resources";
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testBasicJointCoupling.ini";

        yarp::os::Property options {
            {"device", yarp::os::Value("BasicJointCoupling")},
            {"configFile", yarp::os::Value(fileName)}
        };

        if (device.open(options))
        {
            device.view(coupling);
        }
    }

    void TearDown() override
    {
        device.close();
    }

protected:
    static constexpr const double EPS = 1e-6;
    yarp::dev::PolyDriver device;
    yarp::dev::IJointCoupling * coupling {nullptr};
};

TEST_F(BasicJointCouplingTest, Configure)
{
    ASSERT_TRUE(device.isValid());
    ASSERT_NE(coupling, nullptr);

    std::size_t numberOfPhysicalJoints;
    std::size_t numberOfActuatedAxes;

    ASSERT_TRUE(coupling->getNrOfPhysicalJoints(numberOfPhysicalJoints));
    ASSERT_TRUE(coupling->getNrOfActuatedAxes(numberOfActuatedAxes));

    ASSERT_EQ(numberOfPhysicalJoints, 6);
    ASSERT_EQ(numberOfActuatedAxes, 3);

    yarp::sig::VectorOf<std::size_t> coupPhysJointsIndexes;
    yarp::sig::VectorOf<std::size_t> coupActAxesIndexes;

    ASSERT_TRUE(coupling->getCoupledPhysicalJoints(coupPhysJointsIndexes));
    ASSERT_TRUE(coupling->getCoupledActuatedAxes(coupActAxesIndexes));

    ASSERT_EQ(coupPhysJointsIndexes.size(), 5);
    ASSERT_EQ(coupActAxesIndexes.size(), 2);

    ASSERT_EQ(coupPhysJointsIndexes, yarp::sig::VectorOf<std::size_t>({0, 1, 3, 4, 5}));
    ASSERT_EQ(coupActAxesIndexes, yarp::sig::VectorOf<std::size_t>({0, 2}));

    std::string physicalJointName;
    std::string actuatedAxisName;

    ASSERT_TRUE(coupling->getPhysicalJointName(0, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint1");
    ASSERT_TRUE(coupling->getPhysicalJointName(1, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint2");
    ASSERT_TRUE(coupling->getPhysicalJointName(2, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint3");
    ASSERT_TRUE(coupling->getPhysicalJointName(3, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint4");
    ASSERT_TRUE(coupling->getPhysicalJointName(4, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint5");
    ASSERT_TRUE(coupling->getPhysicalJointName(5, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint6");

    ASSERT_TRUE(coupling->getActuatedAxisName(0, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor1");
    ASSERT_TRUE(coupling->getActuatedAxisName(1, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor2");
    ASSERT_TRUE(coupling->getActuatedAxisName(2, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor3");

    double min;
    double max;

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        ASSERT_TRUE(coupling->getPhysicalJointLimits(i, min, max));
        ASSERT_EQ(min, 0.0);
        ASSERT_EQ(max, 30.0);
    }
}

TEST_F(BasicJointCouplingTest, ActuatedAxesToPhysicalJoints)
{
    ASSERT_TRUE(device.isValid());
    ASSERT_NE(coupling, nullptr);

    yarp::sig::Vector physJointsPos, physJointsVel, physJointsAcc, physJointsTrq;

    yarp::sig::Vector actAxesPos {1.5, 3.0, 4.5};
    yarp::sig::Vector actAxesVel {1.5, 3.0, 4.5};
    yarp::sig::Vector actAxesAcc {1.5, 3.0, 4.5};
    yarp::sig::Vector actAxesTrq {1.5, 3.0, 4.5};

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsPos(actAxesPos, physJointsPos));
    ASSERT_EQ(physJointsPos.size(), 6);
    ASSERT_NEAR(physJointsPos[0], actAxesPos[0] * 0.5 + 0.0, EPS);
    ASSERT_NEAR(physJointsPos[1], actAxesPos[0] * 1.0 + 0.1, EPS);
    ASSERT_NEAR(physJointsPos[2], actAxesPos[1] * 2.0 + 0.5, EPS);
    ASSERT_NEAR(physJointsPos[3], actAxesPos[2] * 0.25 + 1.0, EPS);
    ASSERT_NEAR(physJointsPos[4], actAxesPos[2] * 0.5 + 0.0, EPS);
    ASSERT_NEAR(physJointsPos[5], actAxesPos[2] * 0.75 - 1.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsVel(actAxesPos, actAxesVel, physJointsVel));
    ASSERT_EQ(physJointsVel.size(), 6);
    ASSERT_NEAR(physJointsVel[0], 0.5, EPS);
    ASSERT_NEAR(physJointsVel[1], 1.0, EPS);
    ASSERT_NEAR(physJointsVel[2], 2.0, EPS);
    ASSERT_NEAR(physJointsVel[3], 0.25, EPS);
    ASSERT_NEAR(physJointsVel[4], 0.5, EPS);
    ASSERT_NEAR(physJointsVel[5], 0.75, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsAcc(actAxesPos, actAxesVel, actAxesAcc, physJointsAcc));
    ASSERT_EQ(physJointsAcc.size(), 6);
    ASSERT_NEAR(physJointsAcc[0], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[1], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[2], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[3], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[4], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[5], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsTrq(actAxesPos, actAxesTrq, physJointsTrq));
    ASSERT_EQ(physJointsTrq.size(), 6);
    ASSERT_NEAR(physJointsTrq[0], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[1], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[2], actAxesTrq[1], EPS);
    ASSERT_NEAR(physJointsTrq[3], actAxesTrq[2], EPS);
    ASSERT_NEAR(physJointsTrq[4], actAxesTrq[2], EPS);
    ASSERT_NEAR(physJointsTrq[5], actAxesTrq[2], EPS);
}

} // namespace roboticslab::test
