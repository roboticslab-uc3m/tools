cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Start a project.
project(examplePlaybackThread LANGUAGES CXX)

# Find YARP. Point the YARP_DIR environment variable at your build.
if(NOT YARP_FOUND)
    find_package(YARP 3.3 REQUIRED COMPONENTS os dev)
endif()

# Find ROBOTICSLAB_TOOLS.
if(NOT TARGET ROBOTICSLAB::ToolsInterfaces)
    find_package(ROBOTICSLAB_TOOLS REQUIRED)
endif()

# Find ROBOTICSLAB_COLOR_DEBUG.
find_package(COLOR_DEBUG REQUIRED)

# Set up our main executable.
add_executable(examplePlaybackThread examplePlaybackThread.cpp)

# Link external libraries.
target_link_libraries(examplePlaybackThread YARP::YARP_os
                                            YARP::YARP_init
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ToolsInterfaces
                                            ROBOTICSLAB::ColorDebug)
