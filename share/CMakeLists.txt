# Copyright: Universidad Carlos III de Madrid (C) 2019
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

set(contexts)

if(ENABLE_RealToSimControlBoard)
    list(APPEND contexts contexts/RealToSimControlBoard)
endif()

yarp_install(DIRECTORY ${contexts}
             DESTINATION ${ROBOTICSLAB-TOOLS_CONTEXTS_INSTALL_DIR})
