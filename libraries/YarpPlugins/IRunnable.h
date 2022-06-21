// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __I_RUNNABLE__
#define __I_RUNNABLE__

namespace roboticslab
{

/**
 *
 * @brief Abstract base for Runnable.
 *
 */
class IRunnable
{
public:
    /**
     * Destructor.
     */
    virtual ~IRunnable() = default;

    virtual bool run(const std::vector<double>& v) = 0;
};

} // namespace roboticslab

#endif // __I_RUNNABLE__
