include(CMakeDependentOption)

# options: cpp libraries
option(ENABLE_Playback "Enable/disable compilation of Playback" ON)

# options: cpp libraries (plugins)
option(ENABLE_YarpPlugins "Enable/disable compilation of YARP plugins" ON)

# options: cpp programs
option(ENABLE_controlboardStateToIPosition "Enable/disable compilation of controlboardStateToIPosition" ON)

# options: YARP plugins dependent on the ENABLE_YarpPlugins option
cmake_dependent_option(ENABLE_PlaybackThread "Enable/disable compilation of PlaybackThread" ON
                       ENABLE_YarpPlugins OFF)

# options: cpp libraries (plugins)

##### test and coverage options
option(ENABLE_tests "Choose if you want to compile tests" ON)
option(ENABLE_coverage "Choose if you want to enable coverage collection" OFF)

# Register features.
add_feature_info(Playback ENABLE_Playback "Playback library.")
add_feature_info(YarpPlugins ENABLE_YarpPlugins "YARP DL plugins.")
add_feature_info(PlayBackThread ENABLE_PlaybackThread "PlaybackThread YARP plugin.")
add_feature_info(controlboardStateToIPosition ENABLE_controlboardStateToIPosition "controlboardStateToIPosition program.")

# Let the user specify a configuration (only single-config generators).
if(NOT CMAKE_CONFIGURATION_TYPES)
  # Possible values.
  set(_configurations Debug Release MinSizeRel RelWithDebInfo)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${_configurations})

  foreach(_conf ${_configurations})
    set(_conf_string "${_conf_string} ${_conf}")
  endforeach()

  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING
               "Choose the type of build, options are:${_conf_string}")

  if(NOT CMAKE_BUILD_TYPE)
    # Encourage the user to specify build type.
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Release)
  endif()
endif()

# Hide variable to MSVC users since it is not needed.
if(MSVC)
  mark_as_advanced(CMAKE_BUILD_TYPE)
endif()
