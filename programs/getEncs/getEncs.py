#! /usr/bin/env python

import sys

remoteNames = ['/teoSim/leftArm', '/teoSim/rightArm']

import yarp  # imports YARP
yarp.Network.init()  # connect to YARP network
if yarp.Network.checkNetwork() != True:  # let's see if there was actually a reachable YARP network
    print '[error] Please try running yarp server'  # tell the user to start one with 'yarp server' if there isn't any
    quit()

allEncoderValues = []

for remoteName in remoteNames:
    options = yarp.Property()  # create an instance of Property, a nice YARP class for storing name-value (key-value) pairs
    options.put('device','remote_controlboard')  # we add a name-value pair that indicates the YARP device
    options.put('remote',remoteName)  # we add info on to whom we will connect
    options.put('local','/python'+remoteName)  # we add info on how we will call ourselves on the YARP network
    dd = yarp.PolyDriver(options)  # create a YARP multi-use driver with the given options

    enc = dd.viewIEncoders()  # make an encoder controller object we call 'enc'

    axes = enc.getAxes()  # retrieve number of joints

    encoderValues = yarp.DVector(axes)  # create a YARP vector of doubles the size of the number of elements read by enc, call it 'v'
    enc.getEncoders(encoderValues)  # read the encoder values and put them into 'v'

    for encoderValue in encoderValues:
        allEncoderValues.append(encoderValue)

    dd.close()

for encoderValue in allEncoderValues:
    sys.stdout.write(str(encoderValue)+' ')
sys.stdout.flush()

yarp.Network.fini()  # disconnect from the YARP network
