// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RealToSimControlboard.hpp"

// ------------------ IEncodersTimed Related -----------------------------------------

bool roboticslab::RealToSimControlboard::getEncodersTimed(double *encs, double *time) {
    //CD_INFO("\n");  //-- Way too verbose
    bool ok = true;
    for(unsigned int i=0; i < axes; i++)
        ok &= getEncoderTimed(i,&(encs[i]),&(time[i]));
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoderTimed(int j, double *encs, double *time) {
    //CD_INFO("(%d)\n",j);  //-- Way too verbose

    getEncoder(j, encs);
    *time = yarp::os::Time::now();

    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::resetEncoder(int j) {
    CD_INFO("\n");
    if ((unsigned int)j>axes) return false;
    return setEncoder(j,0.0);
  }

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::resetEncoders() {
    CD_INFO("\n");
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= resetEncoder(i);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setEncoder(int j, double val) {  // encExposed = val;
    CD_INFO("\n");
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::setEncoders(const double *vals) {
    CD_INFO("\n");
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= setEncoder(i,vals[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoder(int j, double *v) {
    //CD_INFO("\n");  //-- Way too verbose
    //*v = radToDegIfNotPrismatic(j, vectorOfJointPtr[j]->GetValue(0) );

    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoders(double *encs) {
    //CD_INFO("\n");  //-- Way too verbose
    bool ok = true;
    for(unsigned int i=0;i<axes;i++)
        ok &= getEncoder(i,&encs[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoderSpeed(int j, double *sp) {
    //CD_INFO("\n");  //-- Way too verbose
    // Make it easy, give the current reference speed.
    *sp = 0;  // begins to look like we should use semaphores.
    return true;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoderSpeeds(double *spds) {
    //CD_INFO("\n");  //-- Way too verbose
    bool ok = true;
    //for(unsigned int i=0;i<axes;i++)
    //    ok &= getEncoderSpeed(i,&spds[i]);
    return ok;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoderAcceleration(int j, double *spds) {
    //CD_INFO("\n");  //-- Way too verbose
    return false;
}

// -----------------------------------------------------------------------------

bool roboticslab::RealToSimControlboard::getEncoderAccelerations(double *accs) {
    //CD_INFO("\n");  //-- Way too verbose
    return false;
}

// -----------------------------------------------------------------------------


