# Copyright: (C) 2013 Universidad Carlos III de Madrid
# Author: Juan G. Victores
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

yarp_prepare_plugin(PlaybackThread
                    CATEGORY device
                    TYPE roboticslab::PlaybackThread
                    INCLUDE PlaybackThread.hpp)

if(NOT SKIP_PlaybackThread)

    set(CMAKE_INCLUDE_CURRENT_DIR TRUE) # yarp plugin builder needs this

    yarp_add_plugin(PlaybackThread PlaybackThread.hpp
                                   PlaybackThread.cpp
                                   DeviceDriverImpl.cpp
                                   IPlaybackThreadImpl.cpp
                                   ThreadImpl.cpp)

    target_link_libraries(PlaybackThread YARP::YARP_OS
                                         YARP::YARP_dev
                                         ROBOTICSLAB::ColorDebug
                                         Playback
                                         ToolsInterfaces)

    if(NOT YARP_VERSION_SHORT VERSION_LESS 3.2)
        yarp_install(TARGETS PlaybackThread
                     LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                     ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                     YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})
    else()
        yarp_install(TARGETS PlaybackThread
                     LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                     ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR})

        yarp_install(FILES PlaybackThread.ini
                     DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})
    endif()

endif()
