set(KEYWORD "Playback")

# Find YARP and color-debug.
find_package(YARP REQUIRED)
find_package(COLOR_DEBUG)

# Add current directory to global include paths, retrieve current values.
set_property(GLOBAL APPEND PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)

# Define include paths.
include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS} ${COLOR_DEBUG_INCLUDE_DIRS})

# Configure library build target.
add_library(${KEYWORD} Playback.cpp Playback.hpp)

# Set target properties.
set_target_properties(${KEYWORD} PROPERTIES PUBLIC_HEADER Playback.hpp)

# Link external libraries.
target_link_libraries(${KEYWORD} LINK_PUBLIC ${YARP_LIBRARIES})

# Create installation rule.
install(TARGETS ${KEYWORD}
        EXPORT ROBOTICSLAB_TOOLS
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT playback_library
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT playback_library
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT playback_library
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT playback_library)

# Export library name and current target. Store include paths in target.
set_property(GLOBAL APPEND PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES ${KEYWORD})
set_property(GLOBAL APPEND PROPERTY ROBOTICSLAB_TOOLS_TARGETS ${KEYWORD})
