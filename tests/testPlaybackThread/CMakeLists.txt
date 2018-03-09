find_package(YARP REQUIRED)

include_directories(${YARP_INCLUDE_DIRS}) # remove if YARP > v2.3.70

add_executable(testPlaybackThread testPlaybackThread.cpp)

add_dependencies(testPlaybackThread COLOR_DEBUG)

target_link_libraries(testPlaybackThread YARP::YARP_OS
                                         YARP::YARP_dev
                                         ToolsInterfaces
                                         gtest_main)
