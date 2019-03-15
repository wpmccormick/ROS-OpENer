cmake_minimum_required(VERSION 2.8.3)
project(eip_device)

add_definitions(-std=c++11)

#set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -std=c99 -Werror=implicit-function-declaration" )
#add_definitions( -D_POSIX_C_SOURCE=200112L -D__USE_GNU -D__USE_XOPEN2K -DOPENER_POSIX)

# TODO: Which of these do we really need?
#add_definitions(-DRESTRICT=)
#add_definitions(-DRESTRICT=restrict)

find_package(catkin REQUIRED COMPONENTS opener_ros roscpp)

catkin_package(
  INCLUDE_DIRS include include/eip_device
  CATKIN_DEPENDS opener_ros roscpp
  LIBRARIES lib
  )

include_directories(include include/eip_device ${catkin_INCLUDE_DIRS})

add_executable(eip_device src/eip_device.cpp)

target_link_libraries(
  eip_device
  ${catkin_LIBRARIES}
  rt cap pthread
  )
