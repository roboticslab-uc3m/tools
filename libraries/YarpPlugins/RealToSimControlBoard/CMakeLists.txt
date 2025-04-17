yarp_prepare_plugin(RealToSimControlBoard
                    CATEGORY device
                    TYPE RealToSimControlBoard
                    INCLUDE RealToSimControlBoard.hpp
                    DEFAULT ON
                    EXTRA_CONFIG WRAPPER=controlBoard_nws_yarp
                    GENERATE_PARSER)

if(NOT SKIP_RealToSimControlBoard)

    yarp_add_plugin(RealToSimControlBoard)

    target_sources(RealToSimControlBoard PRIVATE RealToSimControlBoard.hpp
                                                 RealToSimControlBoard.cpp
                                                 DeviceDriverImpl.cpp
                                                 IControlModeImpl.cpp
                                                 IEncodersTimedImpl.cpp
                                                 IPositionControlImpl.cpp
                                                 IVelocityControlImpl.cpp
                                                 Transformation.cpp
                                                 Transformation.hpp
                                                 RealToSimControlBoard_ParamsParser.h
                                                 RealToSimControlBoard_ParamsParser.cpp
                                                 LogComponent.hpp
                                                 LogComponent.cpp)

    target_link_libraries(RealToSimControlBoard YARP::YARP_os
                                                YARP::YARP_dev)

    yarp_install(TARGETS RealToSimControlBoard
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
