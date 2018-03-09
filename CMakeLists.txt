# Copyright: Universidad Carlos III de Madrid (C) 2017
# Authors: Juan G Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Start a project.
project(ROBOTICSLAB_TOOLS)

set(BUILD_SHARED_LIBS TRUE CACHE INTERNAL "hide this!")

# Set module path.
set(ROBOTICSLAB_TOOLS_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ROBOTICSLAB_TOOLS_MODULE_PATH})

# Bootstrap YCM.
# https://github.com/robotology/ycm/issues/118
set(YCM_TAG v0.6.0)
include(YCMBootstrap)

# Retrieve current ROBOTICSLAB_TOOLS version.
include(ROBOTICSLAB_TOOLSVersion)

# Define standard paths, check system configuration.
include(ROBOTICSLAB_TOOLSSystem)

# Setup build options.
include(ROBOTICSLAB_TOOLSOptions)

# Define global properties to store relevant configuration.
set_property(GLOBAL PROPERTY ROBOTICSLAB_TOOLS_TARGETS)

# Superbuild phase - include color-debug
include(FindOrBuildPackage)
find_or_build_package(COLOR_DEBUG)

# find_or_build_package() doesn't bring into scope COLOR_DEBUG_INCLUDE_DIRS
# nor other config variables. If a system copy is found, we have to call the
# find_package() command and proceed as usual.
if(USE_SYSTEM_COLOR_DEBUG)
    find_package(COLOR_DEBUG REQUIRED)
    include_directories(${COLOR_DEBUG_INCLUDE_DIRS})
    add_library(COLOR_DEBUG UNKNOWN IMPORTED)
endif()

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
