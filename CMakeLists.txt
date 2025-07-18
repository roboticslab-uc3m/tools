cmake_minimum_required(VERSION 3.19..3.28)

# Start a project.
project(ROBOTICSLAB_TOOLS LANGUAGES CXX)

# Load CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake
                              ${CMAKE_SOURCE_DIR}/cmake/find-modules)

# Hard dependencies
find_package(YCM 0.11 REQUIRED)
find_package(YARP 3.11 REQUIRED COMPONENTS os dev)

# Soft dependencies.
find_package(Doxygen QUIET)
find_package(GTestSources 1.8 QUIET)

# Retrieve current ROBOTICSLAB_TOOLS version.
include(ROBOTICSLAB_TOOLSVersion)

# Define standard paths, check system configuration.
include(ROBOTICSLAB_TOOLSSystem)

# Setup build options.
include(ROBOTICSLAB_TOOLSOptions)

# Acknowledge this is a CTest-friendly project.
enable_testing()

# Define and enter subdirectories.
add_subdirectory(libraries)
add_subdirectory(programs)
add_subdirectory(tests)
add_subdirectory(share)
add_subdirectory(doc)
add_subdirectory(examples/cpp)

# Output configuration files.
include(ROBOTICSLAB_TOOLSDescribe)

# Invoke CPack from here.
include(ROBOTICSLAB_TOOLSPackage)

# Generate a report of enabled/disabled features.
feature_summary(WHAT ALL)
