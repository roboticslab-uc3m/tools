# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpInstallationHelpers)
yarp_configure_external_installation(roboticslab-tools)

### Go through single applications

#add_subdirectory(prog)

