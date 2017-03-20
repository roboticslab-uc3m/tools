# Testing things #########################################################################################

enable_testing()

find_package(YARP REQUIRED)
find_package(COLOR_DEBUG REQUIRED)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${YARP_INCLUDE_DIRS} ${COLOR_DEBUG_INCLUDE_DIRS} ${ROBOTICSLAB_TOOLS_INCLUDE_DIRS})
link_directories(${ROBOTICSLAB_TOOLS_LINK_DIRS})

add_executable(testPlaybackThread testPlaybackThread.cpp)
target_link_libraries(testPlaybackThread ${YARP_LIBRARIES} ${ROBOTICSLAB_TOOLS_LIBRARIES} gtest gtest_main)

