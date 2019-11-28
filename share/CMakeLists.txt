# Copyright: Universidad Carlos III de Madrid (C) 2019
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

#set(applications)
set(contexts)

if(ENABLE_RealToSimControlboard)
    list(APPEND contexts contexts/RealToSimControlboard)
endif()

#yarp_install(DIRECTORY ${applications}
#             DESTINATION ${ROBOTICSLAB-TOOLS_APPLICATIONS_INSTALL_DIR})

yarp_install(DIRECTORY ${contexts}
             DESTINATION ${ROBOTICSLAB-TOOLS_CONTEXTS_INSTALL_DIR})
