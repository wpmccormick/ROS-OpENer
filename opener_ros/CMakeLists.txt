cmake_minimum_required(VERSION 2.8.12)
project(opener_ros)

find_package(catkin REQUIRED)

catkin_package(
  INCLUDE_DIRS
    OpENer/source
  LIBRARIES
    ENET_ENCAP
    Utils
    CIP
    PLATFORM_GENERIC
  )

set(OpENer_PLATFORM "POSIX" CACHE STRING "Set Platform")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Use Sharedd Libs")
set(CMAKE_INSTALL_INCLUDEDIR ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
set(CMAKE_INSTALL_LIBDIR ${CATKIN_PACKAGE_LIB_DESTINATION})

# TODO: Figure out how to not use the hard-coded path for OpENer C source files
set( PLATFORM_SPEC_SRC
  ../opener_ros/OpENer/source/src/ports/POSIX/networkhandler.c
  ../opener_ros/OpENer/source/src/ports/POSIX/opener_error.c
  ../opener_ros/OpENer/source/src/ports/POSIX/networkconfig.c
  )

add_subdirectory(OpENer/source)

#message("CMAKE_INSTALL_INCLUDEDIR:" ${CMAKE_INSTALL_INCLUDEDIR})
#include_directories(${CMAKE_INSTALL_INCLUDEDIR})
#add_library(PLATFORM ${PLATFORM_SPEC_SRC})
#install(TARGETS PLATFORM
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/OpENer/bin/posix/src/ports"
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "devicedata.h"
 )

# TODO add headers/libs to INSTALL_DIR
install(FILES package.xml DESTINATION share/opener_ros)

