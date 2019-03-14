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

add_subdirectory(OpENer/source)

# TODO add headers/libs to INSTALL_DIR
install(FILES package.xml DESTINATION share/opener_ros)

