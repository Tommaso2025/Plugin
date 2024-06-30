cmake_minimum_required(VERSION 3.0.2)
project(ik_load)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  class_loader
  geometry_msgs
  kdl_kinematics_plugin REQUIRED
  moveit_core
  moveit_kinematics
  moveit_msgs
  pluginlib
  roscpp
)

catkin_package()

## Specify additional locations of header files
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${kdl_kinematics_plugin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(ik_load src/load_ik.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(ik_load
  ${catkin_LIBRARIES}
#  ${kdl_kinematics_plugin_LIBRARIES}
)


#############
## Install ##
#############

 install(TARGETS ik_load
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )


## Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
   PATTERN ".svn" EXCLUDE
 )

