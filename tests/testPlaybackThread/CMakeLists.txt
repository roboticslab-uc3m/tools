# Testing things #########################################################################################

enable_testing()

find_package(YARP REQUIRED)
find_package(COLOR_DEBUG REQUIRED)

# Retrieve global include paths and libraries.
get_property(ROBOTICSLAB_TOOLS_INCLUDE_DIRS GLOBAL PROPERTY ROBOTICSLAB_TOOLS_INCLUDE_DIRS)
get_property(ROBOTICSLAB_TOOLS_LIBRARIES GLOBAL PROPERTY ROBOTICSLAB_TOOLS_LIBRARIES)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${YARP_INCLUDE_DIRS} ${COLOR_DEBUG_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})

add_executable(testPlaybackThread testPlaybackThread.cpp)
target_link_libraries(testPlaybackThread ${YARP_LIBRARIES} ${ROBOTICSLAB_TOOLS_LIBRARIES} gtest gtest_main)

