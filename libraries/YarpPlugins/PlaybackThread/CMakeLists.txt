yarp_prepare_plugin(PlaybackThread
                    CATEGORY device
                    TYPE PlaybackThread
                    INCLUDE PlaybackThread.hpp
                    GENERATE_PARSER)

if(NOT SKIP_PlaybackThread)

    yarp_add_plugin(PlaybackThread)

    target_sources(PlaybackThread PRIVATE PlaybackThread.hpp
                                          DeviceDriverImpl.cpp
                                          IPlaybackThreadImpl.cpp
                                          ThreadImpl.cpp
                                          PlaybackThread_ParamsParser.h
                                          PlaybackThread_ParamsParser.cpp
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
