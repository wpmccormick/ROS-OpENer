cmake_minimum_required(VERSION 2.8.3)
project(eip_device)

add_definitions(-std=c++11)

# TODO: Which of these do we really need?
add_definitions(-DRESTRICT=)

find_package(catkin REQUIRED COMPONENTS opener_ros roscpp)

catkin_package(
  INCLUDE_DIRS include 
    include/eip_device 
    ${catkin_INCLUDE_DIRS}
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros  
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/cip  
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/enet_encap  
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports  
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports/POSIX  
    ${opener_ros_INSTALL_PREFIX}/include/opener_ros/utils  
  CATKIN_DEPENDS opener_ros roscpp
  LIBRARIES lib
  )

include_directories(
  include 
  include/eip_device 
  ${catkin_INCLUDE_DIRS}
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros  
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/cip  
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/enet_encap  
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports  
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/ports/POSIX  
  ${opener_ros_INSTALL_PREFIX}/include/opener_ros/utils  
  )


add_executable(eip_device src/eip_device_node.cpp src/eip_device_application.c)

target_link_libraries(
  eip_device
  ${catkin_LIBRARIES}
  rt cap pthread
  )
