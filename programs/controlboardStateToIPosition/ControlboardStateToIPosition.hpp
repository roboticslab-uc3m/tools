#ifndef __CONTROL_STATE_TO_I_POSITION_HPP__
#define __CONTROL_STATE_TO_I_POSITION_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#define DEFAULT_INPUT "/ControlboardStateToIPosition/state:i"
#define DEFAULT_REMOTE "/ravebot"

namespace roboticslab
{

class DataPort : public yarp::os::BufferedPort<yarp::sig::Vector>
{
private:
    virtual void onRead(yarp::sig::Vector& v)
    {
        iPositionDirect->setPositions( v.data() );
        return;
    }
public:
    yarp::dev::IPositionDirect *iPositionDirect;
};

class ControlboardStateToIPosition : public yarp::os::RFModule
{
public:
    /**
     * Configure the module, pass a ResourceFinder object to the module.
     *
     * @param rf a previously initialized ResourceFinder
     * @return true/false upon success/failure
     *
     * \note attachTerminal() is no longer called automatically. You
     * can call it in the configure function.
     */
    virtual bool configure(yarp::os::ResourceFinder &rf);

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
    virtual bool close();

    /**
     * Override this to do whatever your module needs to do.
     *
     * When your module wants to stop, return false.  The module's actual
     * work could be done during this call, or it could just check the
     * state of a thread running in the background.
     *
     * @return true iff module should continue
    */
    virtual bool updateModule();

private:
    DataPort inStreamPort;
    yarp::dev::PolyDriver outRobotDevice;
};

}

#endif // __CONTROL_STATE_TO_I_POSITION_HPP__
