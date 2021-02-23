# Copyright: (C) 2019 Universidad Carlos III de Madrid
# Author: Juan G. Victores

yarp_prepare_plugin(RealToSimControlboard
                    CATEGORY device
                    TYPE roboticslab::RealToSimControlboard
                    INCLUDE RealToSimControlboard.hpp
                    DEFAULT ON
                    EXTRA_CONFIG WRAPPER=controlboardwrapper2)

if(NOT SKIP_RealToSimControlboard)

    if(NOT YARP_VERSION VERSION_GREATER_EQUAL 3.4)
        set(CMAKE_INCLUDE_CURRENT_DIR TRUE) # yarp plugin builder needs this
    endif()

    yarp_add_plugin(RealToSimControlboard RealToSimControlboard.hpp
                                          RealToSimControlboard.cpp
                                          DeviceDriverImpl.cpp
                                          IControlModeImpl.cpp
                                          IEncodersTimedImpl.cpp
                                          IPositionControlImpl.cpp
                                          IVelocityControlImpl.cpp
                                          Transformation.cpp
                                          Transformation.hpp)

    target_link_libraries(RealToSimControlboard YARP::YARP_os
                                                YARP::YARP_dev)

    yarp_install(TARGETS RealToSimControlboard
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
