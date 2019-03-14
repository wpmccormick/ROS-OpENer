cmake_minimum_required(VERSION 2.8.12)
project(opener_ros)

find_package(catkin REQUIRED)

set(OpENer_PLATFORM "POSIX" CACHE STRING "Set Platform")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Use Sharedd Libs")

add_subdirectory(OpENer/source)

install(FILES package.xml DESTINATION share/opener_ros)
