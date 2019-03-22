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
    POSIXPLATFORM
  )

if( DEFINED OpENer_Device_Config_Vendor_Id )
  message("!!!! OpENer_Device_Config_Vendor_Id IS DEFINED !!!!:" ${OpENer_Device_Config_Vendor_Id})
else()
  message("!!!! OpENer_Device_Config_Vendor_Id IS NOT DEFINED !!!!")
endif()


set( OpENer_Device_Config_Vendor_Id 1 CACHE STRING "Device Vendor ID")
set( OpENer_Device_Config_Device_Type 12 CACHE STRING "Device Type ID")
set( OpENer_Device_Config_Product_Code 65001 CACHE STRING "Device Product Code")
set( OpENer_Device_Config_Device_Name "ROS [OpENer PC]" CACHE STRING "Device Name")
set( OpENer_VERSION_MAJOR 2 )
set( OpENer_VERSION_MINOR 3 )
set(OpENer_PLATFORM "POSIX" CACHE STRING "Set Platform")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Use Sharedd Libs")
set(CMAKE_INSTALL_INCLUDEDIR ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
set(CMAKE_INSTALL_LIBDIR ${CATKIN_PACKAGE_LIB_DESTINATION})

if( DEFINED OpENer_Device_Config_Vendor_Id )
  message("!!!! OpENer_Device_Config_Vendor_Id IS DEFINED !!!!:" ${OpENer_Device_Config_Vendor_Id})
endif()

add_subdirectory(OpENer/source)

# TODO add headers/libs to INSTALL_DIR
install(FILES package.xml DESTINATION share/opener_ros)
