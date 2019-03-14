cmake_minimum_required(VERSION 2.8.3)
project(eip_device)

find_package(catkin REQUIRED
  COMPONENTS
    opener_ros
  )

#add_definitions(-std=c++11)
# TODO: Figure out how to not use the hard-coded path for OpENer C source files
set( PLATFORM_SPEC_SRC
  src/sampleapplication.c
  ../opener_ros/OpENer/source/src/ports/POSIX/networkhandler.c
  ../opener_ros/OpENer/source/src/ports/POSIX/opener_error.c
  ../opener_ros/OpENer/source/src/ports/POSIX/networkconfig.c
  )

catkin_package(
  INCLUDE_DIRS
    include
    include/eip_device
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    opener_ros
  )

include_directories(include include/eip_device
  ${catkin_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}/cip
  ${catkin_INCLUDE_DIRS}/ports
  ${catkin_INCLUDE_DIRS}/ports/POSIX
  ${catkin_INCLUDE_DIRS}/utils
  ${catkin_INCLUDE_DIRS}/enet_encap
)

add_executable(eip_device src/main.c)

#target_link_libraries( OpENer_Test ${catkin_LIBRARIES} ${PROJECT_NAME} CIP Utils ENET_ENCAP PLATFORM_GENERIC rt cap pthread)
#target_link_libraries( OpENer_Test ${catkin_LIBRARIES} ${PROJECT_NAME} )
