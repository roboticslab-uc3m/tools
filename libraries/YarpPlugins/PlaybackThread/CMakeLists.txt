# Copyright: (C) 2013 Universidad Carlos III de Madrid
# Author: Juan G. Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

yarp_prepare_plugin(PlaybackThread
                    CATEGORY device
                    TYPE roboticslab::PlaybackThread
                    INCLUDE PlaybackThread.hpp)

if(NOT SKIP_PlaybackThread)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR})

  yarp_add_plugin(PlaybackThread PlaybackThread.hpp
                                 PlaybackThread.cpp
                                 DeviceDriverImpl.cpp
                                 IPlaybackThreadImpl.cpp
                                 ThreadImpl.cpp)

  add_dependencies(PlaybackThread COLOR_DEBUG)

  target_link_libraries(PlaybackThread YARP::YARP_OS
                                       YARP::YARP_dev
                                       Playback
                                       ToolsInterfaces)

  yarp_install(TARGETS PlaybackThread
               EXPORT ROBOTICSLAB_TOOLS
               COMPONENT runtime
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

  yarp_install(FILES PlaybackThread.ini
               COMPONENT runtime
               DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
