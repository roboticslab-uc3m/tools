# Copyright: (C) 2017 Universidad Carlos III de Madrid
# Authors: Juan G. Victores & Raul de Santos Rico
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

if(YARP_VERSION_SHORT VERSION_LESS 2.3.70)
    list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
    include(YarpPlugin)
    include_directories(${YARP_INCLUDE_DIRS})
endif()

# Create device interface target.
add_library(ToolsInterfaces INTERFACE)

# Configure usage requirements.
target_include_directories(ToolsInterfaces INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install interface headers.
install(FILES IPlaybackThread.h
              IRunnable.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT tools_yarp_plugins)

# Register export set.
install(TARGETS ToolsInterfaces
        EXPORT ROBOTICSLAB_TOOLS)

# Export variables to the global scope.
set_property(GLOBAL APPEND PROPERTY ROBOTICSLAB_TOOLS_TARGETS ToolsInterfaces)

# YARP devices.
add_subdirectory(PlaybackThread)
