# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

# Find YARP.
find_package(YARP REQUIRED)

# Define include paths.
include_directories(${YARP_INCLUDE_DIRS}) # remove if YARP > v2.3.70

# Configure executable build target.
add_executable(controlboardStateToIPosition main.cpp
                                            ControlboardStateToIPosition.cpp
                                            ControlboardStateToIPosition.hpp)

# Link external libraries.
target_link_libraries(controlboardStateToIPosition YARP::YARP_OS
                                                   YARP::YARP_init
                                                   YARP::YARP_dev
                                                   ROBOTICSLAB::ColorDebug)

# Create installation rule.
install(TARGETS controlboardStateToIPosition
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT controlboard_state_to_i_position)
