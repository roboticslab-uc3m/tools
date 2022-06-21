# Configure executable build target.
add_executable(controlboardStateToIPosition main.cpp
                                            ControlboardStateToIPosition.cpp
                                            ControlboardStateToIPosition.hpp)

# Link external libraries.
target_link_libraries(controlboardStateToIPosition YARP::YARP_os
                                                   YARP::YARP_init
                                                   YARP::YARP_dev)

# Create installation rule.
install(TARGETS controlboardStateToIPosition)
