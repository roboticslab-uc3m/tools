yarp_prepare_plugin(PlaybackThread
                    CATEGORY device
                    TYPE roboticslab::PlaybackThread
                    INCLUDE PlaybackThread.hpp)

if(NOT SKIP_PlaybackThread)

    yarp_add_plugin(PlaybackThread PlaybackThread.hpp
                                   DeviceDriverImpl.cpp
                                   IPlaybackThreadImpl.cpp
                                   ThreadImpl.cpp
                                   LogComponent.hpp
                                   LogComponent.cpp)

    target_link_libraries(PlaybackThread YARP::YARP_os
                                         YARP::YARP_dev
                                         ROBOTICSLAB::Playback
                                         ROBOTICSLAB::ToolsInterfaces)

    yarp_install(TARGETS PlaybackThread
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
