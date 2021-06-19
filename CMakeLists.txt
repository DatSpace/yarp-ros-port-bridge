cmake_minimum_required(VERSION 3.10)
project(yarp-ros-port-bridge VERSION 0.1.0)


file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(YARP 3.4 REQUIRED COMPONENTS os)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${YARP_LIBRARIES})


find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs)
include_directories(include ${catkin_INCLUDE_DIRS})
add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})