#! /usr/bin/env python

remoteNames = ['/teoSim/leftArm', '/teoSim/rightArm']

import yarp  # imports YARP
yarp.Network.init()  # connect to YARP network
if yarp.Network.checkNetwork() != True:  # let's see if there was actually a reachable YARP network
    print '[error] Please try running yarp server'  # tell the user to start one with 'yarp server' if there isn't any
    quit()

for remoteName in remoteNames:
    options = yarp.Property()  # create an instance of Property, a nice YARP class for storing name-value (key-value) pairs
    options.put('device','remote_controlboard')  # we add a name-value pair that indicates the YARP device
    options.put('remote',remoteName)  # we add info on to whom we will connect
    options.put('local','/python'+remoteName)  # we add info on how we will call ourselves on the YARP network
    dd = yarp.PolyDriver(options)  # create a YARP multi-use driver with the given options

    enc = dd.viewIEncoders()  # make an encoder controller object we call 'enc'

    axes = enc.getAxes()  # retrieve number of joints

    v = yarp.DVector(axes)  # create a YARP vector of doubles the size of the number of elements read by enc, call it 'v'
    enc.getEncoders(v)  # read the encoder values and put them into 'v'
    print 'v[1] is: ' + str(v[1])  # print element 1 of 'v', note that motors and encoders start at 0

    dd.close()

yarp.Network.fini()  # disconnect from the YARP network
