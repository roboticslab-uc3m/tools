if(NOT GTestSources_FOUND AND (NOT DEFINED ENABLE_tests OR ENABLE_tests))
    message(WARNING "GTestSources package not found, disabling tests")
endif()

if(ENABLE_tests)
    add_subdirectory(${GTestSources_SOURCE_DIR} ${CMAKE_BINARY_DIR}/googletest)
    include_directories(${GTestSources_INCLUDE_DIR})

    if(ENABLE_BasicJointCoupling)
        add_executable(testBasicJointCoupling testBasicJointCoupling.cpp)

        target_link_libraries(testBasicJointCoupling YARP::YARP_os
                                                     YARP::YARP_dev
                                                     gtest_main)

        gtest_discover_tests(testBasicJointCoupling)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/testBasicJointCoupling.ini
                       ${CMAKE_CURRENT_BINARY_DIR}/resources/testBasicJointCoupling.ini COPYONLY)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/testBasicJointCoupling.csv
                       ${CMAKE_CURRENT_BINARY_DIR}/resources/testBasicJointCoupling.csv COPYONLY)
    endif()

    if(TARGET ROBOTICSLAB::Playback)
        add_executable(testPlayback testPlayback.cpp)

        target_link_libraries(testPlayback YARP::YARP_os
                                           ROBOTICSLAB::Playback
                                           gtest_main)

        gtest_discover_tests(testPlayback)

        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/testPlayback.txt
                       ${CMAKE_CURRENT_BINARY_DIR}/resources/testPlayback.txt COPYONLY)

    endif()

    if(TARGET ROBOTICSLAB::ToolsInterfaces)
        add_executable(testPlaybackThread testPlaybackThread.cpp)

        target_link_libraries(testPlaybackThread YARP::YARP_os
                                                 YARP::YARP_dev
                                                 ROBOTICSLAB::ToolsInterfaces
                                                 gtest_main)

        gtest_discover_tests(testPlaybackThread)
    endif()
else()
    set(ENABLE_tests OFF CACHE BOOL "Enable/disable unit tests" FORCE)
endif()
