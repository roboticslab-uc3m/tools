add_executable(testPlayback testPlayback.cpp)

target_link_libraries(testPlayback YARP::YARP_OS
                                   ROBOTICSLAB::ColorDebug
                                   Playback
                                   gtest_main)

gtest_add_tests(testPlayback "" AUTO)
