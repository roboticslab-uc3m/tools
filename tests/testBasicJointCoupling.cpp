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
    {}

    void TearDown() override
    {
        device.close();
    }

protected:
    bool loadConfig()
    {
        std::string fileName = "resources";
        fileName += yarp::conf::filesystem::preferred_separator;
        fileName += "testBasicJointCoupling.ini";

        yarp::os::Property options {
            {"device", yarp::os::Value("BasicJointCoupling")},
            {"configFile", yarp::os::Value(fileName)}
        };

        return device.open(options) && device.view(coupling);
    }

    yarp::dev::PolyDriver device;
    yarp::dev::IJointCoupling * coupling {nullptr};

    std::size_t numberOfPhysicalJoints {0};
    std::size_t numberOfActuatedAxes {0};

    yarp::sig::VectorOf<std::size_t> coupPhysJointsIndexes;
    yarp::sig::VectorOf<std::size_t> coupActAxesIndexes;

    std::string physicalJointName;
    std::string actuatedAxisName;

    yarp::sig::Vector physJointsPos;
    yarp::sig::Vector physJointsVel;
    yarp::sig::Vector physJointsAcc;
    yarp::sig::Vector physJointsTrq;

    yarp::sig::Vector actAxesPos;
    yarp::sig::Vector actAxesVel;
    yarp::sig::Vector actAxesAcc;
    yarp::sig::Vector actAxesTrq;

    static constexpr const double EPS = 1e-6;
};

TEST_F(BasicJointCouplingTest, Configure)
{
    ASSERT_TRUE(loadConfig());
    ASSERT_TRUE(device.isValid());
    ASSERT_NE(coupling, nullptr);

    ASSERT_TRUE(coupling->getNrOfPhysicalJoints(numberOfPhysicalJoints));
    ASSERT_TRUE(coupling->getNrOfActuatedAxes(numberOfActuatedAxes));

    ASSERT_EQ(numberOfPhysicalJoints, 8);
    ASSERT_EQ(numberOfActuatedAxes, 4);

    ASSERT_TRUE(coupling->getCoupledPhysicalJoints(coupPhysJointsIndexes));
    ASSERT_TRUE(coupling->getCoupledActuatedAxes(coupActAxesIndexes));

    ASSERT_EQ(coupPhysJointsIndexes.size(), 7);
    ASSERT_EQ(coupActAxesIndexes.size(), 3);

    ASSERT_EQ(coupPhysJointsIndexes, yarp::sig::VectorOf<std::size_t>({0, 1, 3, 4, 5, 6, 7}));
    ASSERT_EQ(coupActAxesIndexes, yarp::sig::VectorOf<std::size_t>({0, 2, 3}));

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
    ASSERT_TRUE(coupling->getPhysicalJointName(6, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint7");
    ASSERT_TRUE(coupling->getPhysicalJointName(7, physicalJointName));
    ASSERT_EQ(physicalJointName, "joint8");

    ASSERT_TRUE(coupling->getActuatedAxisName(0, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor1");
    ASSERT_TRUE(coupling->getActuatedAxisName(1, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor2");
    ASSERT_TRUE(coupling->getActuatedAxisName(2, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor3");
    ASSERT_TRUE(coupling->getActuatedAxisName(3, actuatedAxisName));
    ASSERT_EQ(actuatedAxisName, "motor4");

    double min;
    double max;

    for (auto i = 0; i < numberOfPhysicalJoints; i++)
    {
        ASSERT_TRUE(coupling->getPhysicalJointLimits(i, min, max));
        ASSERT_EQ(min, 0.0);
        ASSERT_EQ(max, 30.0);
    }
}

TEST_F(BasicJointCouplingTest, LinearTransformation)
{
    yarp::os::Property options {
        {"device", yarp::os::Value("BasicJointCoupling")},
    };

    options.put("actuatedAxes", yarp::os::Value::makeList("motor1"));
    options.put("physicalJoints", yarp::os::Value::makeList("joint1 joint2"));
    options.put("mins", yarp::os::Value::makeList("0.0 0.0"));
    options.put("maxs", yarp::os::Value::makeList("30.0 30.0"));

    options.fromString("(motor1 joint1 joint2)", false);

    options.addGroup("joint1") = {
        {"transformation", yarp::os::Value("linear")},
        {"m", yarp::os::Value(1.0)},
        {"b", yarp::os::Value(0.0)}
    };

    options.addGroup("joint2") = {
        {"transformation", yarp::os::Value("linear")},
        {"m", yarp::os::Value(2.0)},
        {"b", yarp::os::Value(5.0)}
    };

    ASSERT_TRUE(device.open(options));
    ASSERT_TRUE(device.view(coupling));
    ASSERT_NE(coupling, nullptr);

    // operator=(double) interprets its argument as a scalar instead of a vector
    actAxesPos = actAxesVel = actAxesAcc = actAxesTrq = yarp::sig::Vector{10.0};

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsPos(actAxesPos, physJointsPos));
    ASSERT_EQ(physJointsPos.size(), 2);
    ASSERT_NEAR(physJointsPos[0], actAxesPos[0] * 1.0 + 0.0, EPS);
    ASSERT_NEAR(physJointsPos[1], actAxesPos[0] * 2.0 + 5.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsVel(actAxesPos, actAxesVel, physJointsVel));
    ASSERT_EQ(physJointsVel.size(), 2);
    ASSERT_NEAR(physJointsVel[0], 1.0, EPS);
    ASSERT_NEAR(physJointsVel[1], 2.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsAcc(actAxesPos, actAxesVel, actAxesAcc, physJointsAcc));
    ASSERT_EQ(physJointsAcc.size(), 2);
    ASSERT_NEAR(physJointsAcc[0], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[1], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsTrq(actAxesPos, actAxesTrq, physJointsTrq));
    ASSERT_EQ(physJointsTrq.size(), 2);
    ASSERT_NEAR(physJointsTrq[0], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[1], actAxesTrq[0], EPS);

    physJointsPos = physJointsVel = physJointsAcc = physJointsTrq = {10.0, 20.0};

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesPos(physJointsPos, actAxesPos));
    ASSERT_EQ(actAxesPos.size(), 1);
    ASSERT_NEAR(actAxesPos[0], 7.5, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesVel(physJointsPos, physJointsVel, actAxesVel));
    ASSERT_EQ(actAxesVel.size(), 1);
    ASSERT_NEAR(actAxesVel[0], 0.5, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesAcc(physJointsPos, physJointsVel, physJointsAcc, actAxesAcc));
    ASSERT_EQ(actAxesAcc.size(), 1);
    ASSERT_NEAR(actAxesAcc[0], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesTrq(physJointsPos, physJointsTrq, actAxesTrq));
    ASSERT_EQ(actAxesTrq.size(), 1);
    ASSERT_NEAR(actAxesTrq[0], 10.0, EPS);
}

TEST_F(BasicJointCouplingTest, PiecewiseLinearTransformation)
{
    yarp::os::Property options {
        {"device", yarp::os::Value("BasicJointCoupling")},
    };

    options.put("actuatedAxes", yarp::os::Value::makeList("motor1"));
    options.put("physicalJoints", yarp::os::Value::makeList("joint1 joint2"));
    options.put("mins", yarp::os::Value::makeList("0.0 0.0"));
    options.put("maxs", yarp::os::Value::makeList("30.0 90.0"));

    options.fromString("(motor1 joint1 joint2)", false);

    auto & joint1 = options.addGroup("joint1") = {{"transformation", yarp::os::Value("piecewiseLinear")}};
    joint1.put("inData", yarp::os::Value::makeList("0.0 15.0 30.0"));
    joint1.put("outData", yarp::os::Value::makeList("0.0 7.5 22.5"));

    auto & joint2 = options.addGroup("joint2") = {{"transformation", yarp::os::Value("piecewiseLinear")}};
    joint2.put("inData", yarp::os::Value::makeList("0.0 15.0 30.0"));
    joint2.put("outData", yarp::os::Value::makeList("0.0 30.0 75.0"));

    ASSERT_TRUE(device.open(options));
    ASSERT_TRUE(device.view(coupling));
    ASSERT_NE(coupling, nullptr);

    actAxesPos = actAxesVel = actAxesAcc = actAxesTrq = yarp::sig::Vector{10.0};

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsPos(actAxesPos, physJointsPos));
    ASSERT_EQ(physJointsPos.size(), 2);
    ASSERT_NEAR(physJointsPos[0], 5.0, EPS);
    ASSERT_NEAR(physJointsPos[1], 20.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsVel(actAxesPos, actAxesVel, physJointsVel));
    ASSERT_EQ(physJointsVel.size(), 2);
    ASSERT_NEAR(physJointsVel[0], 0.5, EPS);
    ASSERT_NEAR(physJointsVel[1], 2.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsAcc(actAxesPos, actAxesVel, actAxesAcc, physJointsAcc));
    ASSERT_EQ(physJointsAcc.size(), 2);
    ASSERT_NEAR(physJointsAcc[0], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[1], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsTrq(actAxesPos, actAxesTrq, physJointsTrq));
    ASSERT_EQ(physJointsTrq.size(), 2);
    ASSERT_NEAR(physJointsTrq[0], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[1], actAxesTrq[0], EPS);

    physJointsPos = physJointsVel = physJointsAcc = physJointsTrq = {5.0, 10.0};

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesPos(physJointsPos, actAxesPos));
    ASSERT_EQ(actAxesPos.size(), 1);
    ASSERT_NEAR(actAxesPos[0], 5.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesVel(physJointsPos, physJointsVel, actAxesVel));
    ASSERT_EQ(actAxesVel.size(), 1);
    ASSERT_NEAR(actAxesVel[0], 0.5, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesAcc(physJointsPos, physJointsVel, physJointsAcc, actAxesAcc));
    ASSERT_EQ(actAxesAcc.size(), 1);
    ASSERT_NEAR(actAxesAcc[0], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesTrq(physJointsPos, physJointsTrq, actAxesTrq));
    ASSERT_EQ(actAxesTrq.size(), 1);
    ASSERT_NEAR(actAxesTrq[0], physJointsTrq[0], EPS);

    actAxesPos = actAxesVel = actAxesAcc = actAxesTrq = yarp::sig::Vector{20.0};

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsPos(actAxesPos, physJointsPos));
    ASSERT_EQ(physJointsPos.size(), 2);
    ASSERT_NEAR(physJointsPos[0], 12.5, EPS);
    ASSERT_NEAR(physJointsPos[1], 45.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsVel(actAxesPos, actAxesVel, physJointsVel));
    ASSERT_EQ(physJointsVel.size(), 2);
    ASSERT_NEAR(physJointsVel[0], 1.0, EPS);
    ASSERT_NEAR(physJointsVel[1], 3.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsAcc(actAxesPos, actAxesVel, actAxesAcc, physJointsAcc));
    ASSERT_EQ(physJointsAcc.size(), 2);
    ASSERT_NEAR(physJointsAcc[0], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[1], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsTrq(actAxesPos, actAxesTrq, physJointsTrq));
    ASSERT_EQ(physJointsTrq.size(), 2);
    ASSERT_NEAR(physJointsTrq[0], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[1], actAxesTrq[0], EPS);

    physJointsPos = physJointsVel = physJointsAcc = physJointsTrq = {12.5, 60.0};

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesPos(physJointsPos, actAxesPos));
    ASSERT_EQ(actAxesPos.size(), 1);
    ASSERT_NEAR(actAxesPos[0], 20.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesVel(physJointsPos, physJointsVel, actAxesVel));
    ASSERT_EQ(actAxesVel.size(), 1);
    ASSERT_NEAR(actAxesVel[0], 0.333333, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesAcc(physJointsPos, physJointsVel, physJointsAcc, actAxesAcc));
    ASSERT_EQ(actAxesAcc.size(), 1);
    ASSERT_NEAR(actAxesAcc[0], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesTrq(physJointsPos, physJointsTrq, actAxesTrq));
    ASSERT_EQ(actAxesTrq.size(), 1);
    ASSERT_NEAR(actAxesTrq[0], physJointsTrq[0], EPS);
}

TEST_F(BasicJointCouplingTest, ActuatedAxesToPhysicalJoints)
{
    ASSERT_TRUE(loadConfig());
    ASSERT_TRUE(device.isValid());
    ASSERT_NE(coupling, nullptr);

    actAxesPos = actAxesVel = actAxesAcc = actAxesTrq = {1.5, 3.0, 4.5, 5.0};

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsPos(actAxesPos, physJointsPos));
    ASSERT_EQ(physJointsPos.size(), 8);
    ASSERT_NEAR(physJointsPos[0], actAxesPos[0] * 0.5 + 0.0, EPS);
    ASSERT_NEAR(physJointsPos[1], actAxesPos[0] * 1.0 + 0.1, EPS);
    ASSERT_NEAR(physJointsPos[2], actAxesPos[1] * 2.0 + 0.5, EPS);
    ASSERT_NEAR(physJointsPos[3], actAxesPos[2] * 0.25 + 1.0, EPS);
    ASSERT_NEAR(physJointsPos[4], actAxesPos[2] * 0.5 + 0.0, EPS);
    ASSERT_NEAR(physJointsPos[5], actAxesPos[2] * 0.75 - 1.0, EPS);
    ASSERT_NEAR(physJointsPos[6], 10.0, EPS);
    ASSERT_NEAR(physJointsPos[7], 10.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsVel(actAxesPos, actAxesVel, physJointsVel));
    ASSERT_EQ(physJointsVel.size(), 8);
    ASSERT_NEAR(physJointsVel[0], 0.5, EPS);
    ASSERT_NEAR(physJointsVel[1], 1.0, EPS);
    ASSERT_NEAR(physJointsVel[2], 2.0, EPS);
    ASSERT_NEAR(physJointsVel[3], 0.25, EPS);
    ASSERT_NEAR(physJointsVel[4], 0.5, EPS);
    ASSERT_NEAR(physJointsVel[5], 0.75, EPS);
    ASSERT_NEAR(physJointsVel[6], 1.0, EPS);
    ASSERT_NEAR(physJointsVel[7], 1.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsAcc(actAxesPos, actAxesVel, actAxesAcc, physJointsAcc));
    ASSERT_EQ(physJointsAcc.size(), 8);
    ASSERT_NEAR(physJointsAcc[0], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[1], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[2], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[3], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[4], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[5], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[6], 0.0, EPS);
    ASSERT_NEAR(physJointsAcc[7], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromActuatedAxesToPhysicalJointsTrq(actAxesPos, actAxesTrq, physJointsTrq));
    ASSERT_EQ(physJointsTrq.size(), 8);
    ASSERT_NEAR(physJointsTrq[0], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[1], actAxesTrq[0], EPS);
    ASSERT_NEAR(physJointsTrq[2], actAxesTrq[1], EPS);
    ASSERT_NEAR(physJointsTrq[3], actAxesTrq[2], EPS);
    ASSERT_NEAR(physJointsTrq[4], actAxesTrq[2], EPS);
    ASSERT_NEAR(physJointsTrq[5], actAxesTrq[2], EPS);
    ASSERT_NEAR(physJointsTrq[6], actAxesTrq[3], EPS);
    ASSERT_NEAR(physJointsTrq[7], actAxesTrq[3], EPS);

    physJointsPos = physJointsVel = physJointsAcc = physJointsTrq = {0.5, 1.0, 2.0, 0.25, 0.5, 0.75, 15.0, 25.0};

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesPos(physJointsPos, actAxesPos));
    ASSERT_EQ(actAxesPos.size(), 4);
    ASSERT_NEAR(actAxesPos[0], 0.9, EPS);
    ASSERT_NEAR(actAxesPos[1], 0.75, EPS);
    ASSERT_NEAR(actAxesPos[2], -3.0, EPS);
    ASSERT_NEAR(actAxesPos[3], 10.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesVel(physJointsPos, physJointsVel, actAxesVel));
    ASSERT_EQ(actAxesVel.size(), 4);
    ASSERT_NEAR(actAxesVel[0], 1.0, EPS);
    ASSERT_NEAR(actAxesVel[1], 0.5, EPS);
    ASSERT_NEAR(actAxesVel[2], 1.333333, EPS);
    ASSERT_NEAR(actAxesVel[3], 1.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesAcc(physJointsPos, physJointsVel, physJointsAcc, actAxesAcc));
    ASSERT_EQ(actAxesAcc.size(), 4);
    ASSERT_NEAR(actAxesAcc[0], 0.0, EPS);
    ASSERT_NEAR(actAxesAcc[1], 0.0, EPS);
    ASSERT_NEAR(actAxesAcc[2], 0.0, EPS);
    ASSERT_NEAR(actAxesAcc[3], 0.0, EPS);

    ASSERT_TRUE(coupling->convertFromPhysicalJointsToActuatedAxesTrq(physJointsPos, physJointsTrq, actAxesTrq));
    ASSERT_EQ(actAxesTrq.size(), 4);
    ASSERT_NEAR(actAxesTrq[0], physJointsTrq[0], EPS);
    ASSERT_NEAR(actAxesTrq[1], physJointsTrq[2], EPS);
    ASSERT_NEAR(actAxesTrq[2], physJointsTrq[3], EPS);
    ASSERT_NEAR(actAxesTrq[3], physJointsTrq[6], EPS);
}

} // namespace roboticslab::test
