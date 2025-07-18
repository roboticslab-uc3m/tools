# Create device interface target.
add_library(ToolsInterfaces INTERFACE)

# Configure usage requirements.
target_include_directories(ToolsInterfaces INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Register interface headers.
set_property(TARGET ToolsInterfaces PROPERTY PUBLIC_HEADER IPlaybackThread.h
                                                           IRunnable.h)

# Register export set.
install(TARGETS ToolsInterfaces
        EXPORT ROBOTICSLAB_TOOLS)

# Create alias target.
add_library(ROBOTICSLAB::ToolsInterfaces ALIAS ToolsInterfaces)

# FIXME: workaround for YARP 3.12.
if(YARP_VERSION VERSION_LESS 3.11.100)
    set(ALLOW_DEVICE_PARAM_PARSER_GENERATION_DEFAULT_VALUE OFF)
else()
    set(ALLOW_DEVICE_PARAM_PARSER_GENERATION_DEFAULT_VALUE ON)
endif()

option(ALLOW_DEVICE_PARAM_PARSER_GENERATION "Allow YARP to (re)build device param parsers"
       ${ALLOW_DEVICE_PARAM_PARSER_GENERATION_DEFAULT_VALUE})

# YARP devices.
add_subdirectory(PlaybackThread)
add_subdirectory(RealToSimControlBoard)
