cmake_minimum_required(VERSION 2.8.3)
project(jijin_manipulator_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES you_pkgs
   CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs
#  DEPENDS system_lib
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(read_jointstate_publish_cmd_gazebo_3dof
		src/read_jointstate_publish_cmd_gazebo_3dof.cpp)
target_link_libraries(read_jointstate_publish_cmd_gazebo_3dof ${catkin_LIBRARIES})

add_executable(read_jointstate_publish_cmd_gazebo_6dof
		src/read_jointstate_publish_cmd_gazebo_6dof.cpp)
target_link_libraries(read_jointstate_publish_cmd_gazebo_6dof ${catkin_LIBRARIES})
