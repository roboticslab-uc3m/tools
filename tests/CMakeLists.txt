# Testing things #########################################################################################

if(NOT GTestSources_FOUND AND (NOT DEFINED ENABLE_tests OR ENABLE_tests))
    message(WARNING "GTestSources package not found, disabling tests")
endif()

if(ENABLE_tests)
    enable_testing()

    add_subdirectory(${GTestSources_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gtest)
    include_directories(${GTestSources_INCLUDE_DIR})

    add_subdirectory(testPlayback)
    add_subdirectory(testPlaybackThread)
else()
    set(ENABLE_tests OFF CACHE BOOL "Enable/disable unit tests" FORCE)
endif()
