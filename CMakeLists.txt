cmake_minimum_required(VERSION 2.8.12)

add_compile_options(-std=c++11 -w)

set(OpENer_PLATFORM "POSIX")
set(CMAKE_BUILD_TYPE "")
set(BUILD_SHARED_LIBS ON)

add_subdirectory(OpENer/source)


install(FILES package.xml DESTINATION share/OpENer)
