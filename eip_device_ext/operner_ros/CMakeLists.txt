cmake_minimum_required(VERSION 2.8.12)

add_compile_options(-std=c++11 -w)

set(OpENer_PLATFORM "POSIX" CACHE STRING "Set Platform")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Use Sharedd Libs")

add_subdirectory(OpENer/source)


install(FILES package.xml DESTINATION share/OpENer)
