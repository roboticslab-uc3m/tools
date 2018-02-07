# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

# Safety check against missing dummy library for system-available COLOR_DEBUG.
# Remove if cmake_minimum_required() is set to 3.0 or later.
if(POLICY CMP0046)
    cmake_policy(SET CMP0046 NEW)
endif()

# Disable annoying YCM-related warnings.
# Remove if cmake_minimum_required() is set to 3.1 or later.
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

# Start a project.
project(ROBOTICSLAB_TOOLS)

set(BUILD_SHARED_LIBS TRUE CACHE INTERNAL "hide this!")

# Set module path.
set(ROBOTICSLAB_TOOLS_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ROBOTICSLAB_TOOLS_MODULE_PATH})

# Bootstrap YCM.
# https://github.com/robotology/ycm/issues/118
set(YCM_TAG v0.2.2)
include(YCMBootstrap)

# Superbuild phase - include color-debug
include(FindOrBuildPackage)
find_or_build_package(COLOR_DEBUG)

# Retrieve current ROBOTICSLAB_TOOLS version.
include(ROBOTICSLAB_TOOLSVersion)

# Define standard paths, check system configuration.
include(ROBOTICSLAB_TOOLSSystem)

# Setup build options.
include(ROBOTICSLAB_TOOLSOptions)

# Define global properties to store relevant configuration.
set_property(GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
set_property(GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)
set_property(GLOBAL PROPERTY ROBOTICSLAB_TOOLS_TARGETS)

# Define and enter subdirectories.
add_subdirectory(share)
add_subdirectory(libraries)
add_subdirectory(programs)

if(ENABLE_tests)
    add_subdirectory(tests)
endif()

# Output configuration files.
include(ROBOTICSLAB_TOOLSDescribe)

# Create target for documentation generation.
include(ROBOTICSLAB_TOOLSDoc)

# Invoke CPack from here.
include(ROBOTICSLAB_TOOLSPackage)

# Generate a report of enabled/disabled features.
feature_summary(FATAL_ON_MISSING_REQUIRED_PACKAGES WHAT ALL)

