# Testing things #########################################################################################

find_package(YARP REQUIRED)

# Retrieve global include paths and libraries.
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
get_property(ROBOTICSLAB_TOOLS_LIBRARIES GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)

include_directories(${YARP_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})

add_executable(testPlayback testPlayback.cpp)
add_dependencies(testPlayback COLOR_DEBUG)
target_link_libraries(testPlayback ${YARP_LIBRARIES} ${ROBOTICSLAB_TOOLS_LIBRARIES} gtest gtest_main)
