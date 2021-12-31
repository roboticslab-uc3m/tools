#ifndef __CONTROL_STATE_TO_I_POSITION_HPP__
#define __CONTROL_STATE_TO_I_POSITION_HPP__

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
 * @brief Reads joint positions from an input controlboard, sends to an output controlboard.
 */
class ControlboardStateToIPosition : public yarp::os::RFModule,
                                     public yarp::os::PeriodicThread
{
public:

    ControlboardStateToIPosition()
        : yarp::os::PeriodicThread(1.0, yarp::os::PeriodicThreadClock::Absolute)
    {}

    /**
     * Configure the module, pass a ResourceFinder object to the module.
     *
     * @param rf a previously initialized ResourceFinder
     * @return true/false upon success/failure
     *
     * \note attachTerminal() is no longer called automatically. You
     * can call it in the configure function.
     */
    bool configure(yarp::os::ResourceFinder &rf) override;

    /**
     * Close function.
     *
     * This is called automatically when the module closes, after the last call
     * to updateModule. Override this to cleanup memory allocated in the
     * configure() function or perform other activities that ensure graceful
     * shutdown.
     *
     * @return true/false on success failure.
     */
    bool close() override;

    /**
     * Override this to do whatever your module needs to do.
     *
     * When your module wants to stop, return false.  The module's actual
     * work could be done during this call, or it could just check the
     * state of a thread running in the background.
     *
     * @return true iff module should continue
    */
    bool updateModule() override;

    /**
     * Loop function. This is the thread itself.
     * The thread calls the run() function every <period> ms.
     * At the end of each run, the thread will sleep the amounth of time
     * required, taking into account the time spent inside the loop function.
     * Example:  requested period is 10ms, the run() function take 3ms to
     * be executed, the thread will sleep for 7ms.
     *
     * Note: after each run is completed, the thread will call a yield()
     * in order to facilitate other threads to run.
     */
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

#endif // __CONTROL_STATE_TO_I_POSITION_HPP__
