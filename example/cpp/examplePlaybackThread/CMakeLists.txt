cmake_minimum_required(VERSION 2.6)

set(KEYWORD "examplePlaybackThread")

# Start a project.
project(${KEYWORD})

# Find YARP. Point the YARP_DIR environment variable at your build.
find_package(YARP REQUIRED)

# Find ROBOTICSLAB_TOOLS.
find_package(ROBOTICSLAB_TOOLS REQUIRED)

# Include any directories needed for YARP and ROBOTICSLAB_TOOLS.
include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})

# Set up our main executable.
add_executable(${KEYWORD} examplePlaybackThread.cpp)

# Link external libraries.
target_link_libraries(${KEYWORD} ${YARP_LIBRARIES} ROBOTICSLAB_TOOLS::Playback)
