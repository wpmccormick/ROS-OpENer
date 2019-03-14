cmake_minimum_required(VERSION 2.8.3)
project(eip_device)

find_package(catkin REQUIRED
  COMPONENTS
    opener_ros
  )

#find_path( OpENer_BUILDSUPPORT_DIR OpENer.cmake ../opener_ros/OpENer/source/buildsupport )
#INCLUDE( ${OpENer_BUILDSUPPORT_DIR}/OpENer.cmake )
#opener_common_includes()

# add_definitions(-std=c++11)

set( PLATFORM_SPEC_SRC
  src/sampleapplication.c
  ../opener_ros/OpENer/source/src/ports/POSIX/networkhandler.c
  ../opener_ros/OpENer/source/src/ports/POSIX/opener_error.c
  ../opener_ros/OpENer/source/src/ports/POSIX/networkconfig.c
  )

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    opener_ros
  )

include_directories(include
  ${catkin_INCLUDE_DIRS}
)

# add_library( TESTING ${PLATFORM_SPEC_SRC} )

add_executable(OpENer_Test src/main.c)

target_link_libraries( OpENer_Test CIP Utils ENET_ENCAP PLATFORM_GENERIC rt cap pthread)
