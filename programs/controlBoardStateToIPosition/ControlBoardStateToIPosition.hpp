#ifndef __CONTROL_BOARD_STATE_TO_I_POSITION_HPP__
#define __CONTROL_BOARD_STATE_TO_I_POSITION_HPP__

#include <vector>

#include <yarp/os/PeriodicThread.h>
#include <yarp/os/RFModule.h>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IControlMode.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/dev/IPositionDirect.h>

namespace roboticslab
{

/**
 * @brief Reads joint positions from an input control board, sends to an output control board.
 */
class ControlBoardStateToIPosition : public yarp::os::RFModule,
                                     public yarp::os::PeriodicThread
{
public:

    ControlBoardStateToIPosition()
        : yarp::os::PeriodicThread(1.0, yarp::os::PeriodicThreadClock::Absolute)
    {}

    bool configure(yarp::os::ResourceFinder &rf) override;
    bool close() override;
    bool updateModule() override;
    void run() override;

private:

    std::vector< double > encPoss;

    // In and out devices
    yarp::dev::PolyDriver inRobotDevice;
    yarp::dev::PolyDriver outRobotDevice;

    // In interfaces
    yarp::dev::IEncoders *iEncodersIn;

    // Out interfaces
    yarp::dev::IControlMode *iControlModeOut;
    yarp::dev::IPositionDirect *iPositionDirectOut;
};

}

#endif // __CONTROL_BOARD_STATE_TO_I_POSITION_HPP__
