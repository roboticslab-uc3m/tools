cmake_minimum_required(VERSION 3.16)

# Start a project.
project(examplePlaybackThread LANGUAGES CXX)

# Find YARP. Point the YARP_DIR environment variable at your build.
if(NOT YARP_FOUND)
    find_package(YARP 3.6 REQUIRED COMPONENTS os dev)
endif()

# Find ROBOTICSLAB_TOOLS.
if(NOT TARGET ROBOTICSLAB::ToolsInterfaces)
    find_package(ROBOTICSLAB_TOOLS REQUIRED)
endif()

# Set up our main executable.
add_executable(examplePlaybackThread examplePlaybackThread.cpp)

# Link external libraries.
target_link_libraries(examplePlaybackThread YARP::YARP_os
                                            YARP::YARP_init
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ToolsInterfaces)

# Hardcode path to resource file.
configure_file(examplePlaybackThread.ini.template ${CMAKE_CURRENT_BINARY_DIR}/examplePlaybackThread.ini)

# Use sample config.
target_compile_definitions(examplePlaybackThread PRIVATE SAMPLE_CONFIG="${CMAKE_CURRENT_BINARY_DIR}/examplePlaybackThread.ini")
