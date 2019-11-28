# Testing things #########################################################################################

if(NOT GTestSources_FOUND AND (NOT DEFINED ENABLE_tests OR ENABLE_tests))
    message(WARNING "GTestSources package not found, disabling tests")
endif()

if(ENABLE_tests)
    enable_testing()

    add_subdirectory(${GTestSources_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gtest)
    include_directories(${GTestSources_INCLUDE_DIR})

    # testPlayback

    if(TARGET Playback)
        add_executable(testPlayback testPlayback.cpp)

        target_link_libraries(testPlayback YARP::YARP_OS
                                           ROBOTICSLAB::ColorDebug
                                           Playback
                                           gtest_main)

        gtest_add_tests(testPlayback "" AUTO)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/testPlayback.txt ${CMAKE_CURRENT_BINARY_DIR}/resources/testPlayback.txt COPYONLY)

    endif()

    # testPlaybackThread

    if(TARGET ToolsInterfaces)
        add_executable(testPlaybackThread testPlaybackThread.cpp)

        target_link_libraries(testPlaybackThread YARP::YARP_OS
                                                 YARP::YARP_dev
                                                 ROBOTICSLAB::ColorDebug
                                                 ToolsInterfaces
                                                 gtest_main)

        gtest_add_tests(testPlaybackThread "" AUTO)
    endif()
else()
    set(ENABLE_tests OFF CACHE BOOL "Enable/disable unit tests" FORCE)
endif()
