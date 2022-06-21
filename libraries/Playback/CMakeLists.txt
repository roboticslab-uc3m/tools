# Configure library build target.
add_library(Playback SHARED Playback.cpp
                            Playback.hpp)

# Set target properties.
set_target_properties(Playback PROPERTIES PUBLIC_HEADER Playback.hpp)

# Specify include directories.
target_include_directories(Playback PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Specify usage requirements.
target_link_libraries(Playback PRIVATE YARP::YARP_os)

# Create installation rule.
install(TARGETS Playback
        EXPORT ROBOTICSLAB_TOOLS)

# Create alias target.
add_library(ROBOTICSLAB::Playback ALIAS Playback)
