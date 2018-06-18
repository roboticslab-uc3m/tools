cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Start a project.
project(examplePlaybackThread)

# Find YARP. Point the YARP_DIR environment variable at your build.
find_package(YARP REQUIRED)

# Find ROBOTICSLAB_TOOLS.
find_package(ROBOTICSLAB_TOOLS REQUIRED)

# Include any directories needed for YARP (only <v2.3.70).
include_directories(${YARP_INCLUDE_DIRS})

# Set up our main executable.
add_executable(examplePlaybackThread examplePlaybackThread.cpp)

# Link external libraries.
target_link_libraries(examplePlaybackThread YARP::YARP_OS
                                            YARP::YARP_init
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ToolsInterfaces)

include(GNUInstallDirs)

# Install rule.
install(TARGETS examplePlaybackThread
        DESTINATION ${CMAKE_INSTALL_BINDIR})
