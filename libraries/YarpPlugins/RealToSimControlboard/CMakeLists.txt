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
                                      DeviceDriverImpl.cpp
                                      IEncodersTimedImpl.cpp
                                      IPositionControlImpl.cpp
                                      IVelocityControlImpl.cpp)

target_link_libraries(RealToSimControlboard YARP::YARP_OS
                                            YARP::YARP_dev
                                            ROBOTICSLAB::ColorDebug)

if(NOT YARP_VERSION_SHORT VERSION_LESS 3.2)
    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_PLUGIN_MANIFESTS_INSTALL_DIR})
else()
    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RealToSimControlboard.ini
                 DESTINATION ${ROBOTICSLAB-OPENRAVE-YARP-PLUGINS_PLUGIN_MANIFESTS_INSTALL_DIR})
endif()

endif()
