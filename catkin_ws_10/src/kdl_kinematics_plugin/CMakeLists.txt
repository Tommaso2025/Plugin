cmake_minimum_required(VERSION 3.0.2)
project(kdl_kinematics_plugin)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Eigen3 REQUIRED)
find_package(orocos_kdl REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  moveit_core
  pluginlib
  roscpp
  tf2
  tf2_kdl
  class_loader
)

moveit_build_options()

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

## Catkin package
catkin_package(
  LIBRARIES kdl_kinematics_plugin
  INCLUDE_DIRS include
  CATKIN_DEPENDS moveit_core pluginlib roscpp class_loader
  DEPENDS EIGEN3 Boost
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(kdl_kinematics_plugin
  src/kdl_kinematics_plugin.cpp
)

## Add cmake target dependencies of the library
add_dependencies(kdl_kinematics_plugin ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(kdl_kinematics_plugin
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

install(TARGETS kdl_kinematics_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

## Install plugin description file
#install(FILES
#  kdl_kinematics_plugin_description.xml
#  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)

# Install the plugin description file to a custom directory
install(FILES
  plugin_description.xml
  DESTINATION share/${PROJECT_NAME}
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_my_ik_solver_plugin.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

