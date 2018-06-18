add_executable(testPlayback testPlayback.cpp)

target_link_libraries(testPlayback ROBOTICSLAB::ColorDebug
                                   Playback
                                   gtest_main)
