yarp_prepare_plugin(BasicJointCoupling
                    CATEGORY device
                    TYPE BasicJointCoupling
                    INCLUDE BasicJointCoupling.hpp
                    DEFAULT ON
                    GENERATE_PARSER)

if(NOT SKIP_BasicJointCoupling)

    yarp_add_plugin(BasicJointCoupling)

    target_sources(BasicJointCoupling PRIVATE BasicJointCoupling.hpp
                                              DeviceDriverImpl.cpp
                                              IJointCouplingImpl.cpp
                                              Transformation.hpp
                                              Transformation.cpp
                                              BasicJointCoupling_ParamsParser.h
                                              BasicJointCoupling_ParamsParser.cpp
                                              LogComponent.hpp
                                              LogComponent.cpp)

    target_link_libraries(BasicJointCoupling YARP::YARP_os
                                             YARP::YARP_dev)

    yarp_install(TARGETS BasicJointCoupling
                 LIBRARY DESTINATION ${ROBOTICSLAB-TOOLS_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ROBOTICSLAB-TOOLS_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ROBOTICSLAB-TOOLS_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
