# Copyright: (C) 2019 Universidad Carlos III de Madrid
# Author: Juan G. Victores

yarp_prepare_plugin(RealToSimControlboard
                    CATEGORY device
                    TYPE roboticslab::RealToSimControlboard
                    INCLUDE RealToSimControlboard.hpp
                    DEFAULT ON)

if(NOT SKIP_RealToSimControlboard)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) # yarp plugin builder needs this

yarp_add_plugin(RealToSimControlboard RealToSimControlboard.hpp
                                      RealToSimControlboard.cpp
                                      DeviceDriverImpl.cpp
                                      IEncodersTimedImpl.cpp
                                      IPositionControlImpl.cpp
                                      IVelocityControlImpl.cpp
                                      Transformation.cpp
                                      Transformation.hpp)

target_link_libraries(RealToSimControlboard YARP::YARP_OS
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ColorDebug)

if(NOT YARP_VERSION_SHORT VERSION_LESS 3.2)
    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})
else()
    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RealToSimControlboard.ini
                 DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})
endif()

endif()