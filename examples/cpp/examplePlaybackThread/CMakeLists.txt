cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Start a project.
project(examplePlaybackThread LANGUAGES CXX)

# Find YARP. Point the YARP_DIR environment variable at your build.
find_package(YARP 3.2 REQUIRED COMPONENTS OS dev)

# Find ROBOTICSLAB_COLOR_DEBUG.
find_package(COLOR_DEBUG REQUIRED)

# Find ROBOTICSLAB_TOOLS.
find_package(ROBOTICSLAB_TOOLS REQUIRED)

# Set up our main executable.
add_executable(examplePlaybackThread examplePlaybackThread.cpp)

# Link external libraries.
target_link_libraries(examplePlaybackThread YARP::YARP_OS
                                            YARP::YARP_init
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ToolsInterfaces
                                            ROBOTICSLAB::ColorDebug)
