add_executable(testPlayback testPlayback.cpp)

add_dependencies(testPlayback COLOR_DEBUG)

target_link_libraries(testPlayback Playback
                                   gtest_main)
