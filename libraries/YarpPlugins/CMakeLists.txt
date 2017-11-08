# Copyright: (C) 2017 Universidad Carlos III de Madrid
# Authors: Juan G. Victores & Raul de Santos Rico
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

# Find YARP.
find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})  
include(YarpPlugin)

# Add current directory to global include paths, retrieve current values.
set_property(GLOBAL APPEND PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
get_property(ROBOTICSLAB_TOOLS_LIBRARIES GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)

# Define include paths.
include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})

if(ENABLE_PlaybackThread)
    add_subdirectory(PlaybackThread)
endif()

# Create installation rule.
install(FILES IPlaybackThread.h IRunnable.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT tools_yarp_plugins)

