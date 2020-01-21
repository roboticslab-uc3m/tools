# Copyright: Universidad Carlos III de Madrid (C) 2019
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

set(contexts)

if(ENABLE_RealToSimControlboard)
    list(APPEND contexts contexts/RealToSimControlboard)
endif()

yarp_install(DIRECTORY ${contexts}
             DESTINATION ${ROBOTICSLAB-TOOLS_CONTEXTS_INSTALL_DIR})
