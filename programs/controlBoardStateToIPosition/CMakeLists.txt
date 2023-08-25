# Configure executable build target.
add_executable(controlBoardStateToIPosition main.cpp
                                            ControlBoardStateToIPosition.cpp
                                            ControlBoardStateToIPosition.hpp)

# Link external libraries.
target_link_libraries(controlBoardStateToIPosition YARP::YARP_os
                                                   YARP::YARP_init
                                                   YARP::YARP_dev)

# Create installation rule.
install(TARGETS controlBoardStateToIPosition)
