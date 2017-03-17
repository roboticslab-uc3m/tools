# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

set(KEYWORD "exampleProgram")

# Find YARP.
find_package(YARP REQUIRED)

# Retrieve global include paths and libraries.
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
get_property(ROBOTICSLAB_TOOLS_LIBRARIES GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)

# Define include paths.
include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})

# Configure executable build target.
add_library(${KEYWORD} main.cpp ExampleProgram.cpp ExampleProgram.hpp)

# Link external libraries.
target_link_libraries(${KEYWORD} ${YARP_LIBRARIES} ${ROBOTICSLAB_TOOLS_LIBRARIES})

# Create installation rule.
install(TARGETS ${_example_target}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT example_program)

