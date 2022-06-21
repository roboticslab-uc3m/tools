yarp_prepare_plugin(RealToSimControlboard
                    CATEGORY device
                    TYPE roboticslab::RealToSimControlboard
                    INCLUDE RealToSimControlboard.hpp
                    DEFAULT ON
                    EXTRA_CONFIG WRAPPER=controlBoard_nws_yarp)

if(NOT SKIP_RealToSimControlboard)

    yarp_add_plugin(RealToSimControlboard RealToSimControlboard.hpp
                                          RealToSimControlboard.cpp
                                          DeviceDriverImpl.cpp
                                          IControlModeImpl.cpp
                                          IEncodersTimedImpl.cpp
                                          IPositionControlImpl.cpp
                                          IVelocityControlImpl.cpp
                                          Transformation.cpp
                                          Transformation.hpp
                                          LogComponent.hpp
                                          LogComponent.cpp)

    target_link_libraries(RealToSimControlboard YARP::YARP_os
                                                YARP::YARP_dev)

    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
