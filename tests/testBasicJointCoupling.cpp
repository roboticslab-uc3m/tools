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

} // namespace roboticslab::test
