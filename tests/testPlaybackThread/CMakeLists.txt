include_directories(${YARP_INCLUDE_DIRS}) # remove if YARP > v2.3.70

add_executable(testPlaybackThread testPlaybackThread.cpp)

target_link_libraries(testPlaybackThread YARP::YARP_OS
                                         YARP::YARP_dev
                                         ROBOTICSLAB::ColorDebug
                                         ToolsInterfaces
                                         gtest_main)
