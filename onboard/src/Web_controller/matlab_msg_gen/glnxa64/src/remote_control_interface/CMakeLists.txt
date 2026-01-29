cmake_minimum_required(VERSION 3.5)
project(remote_control_interface)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(ALIAS_ROS2_TF2)
  add_definitions(-Dtf2=ros2_tf2)
  add_definitions(-Dtf2_ros=ros2_tf2_ros)
  add_definitions(-Dmessage_filters=ros2_message_filters)
endif()
# Check the ROS 2 distribution and define a macro
if("$ENV{ROS_DISTRO}" STREQUAL "humble")
    message(STATUS "Building for ROS 2 Humble")
    add_definitions(-DROS2_DISTRO_HUMBLE)
elseif("$ENV{ROS_DISTRO}" STREQUAL "jazzy")
    message(STATUS "Building for ROS 2 Jazzy")
    add_definitions(-DROS2_DISTRO_JAZZY)
else()
    message(WARNING "ROS 2 distribution $ENV{ROS_DISTRO} is not recommended for this MATLAB version. Use 'ROS 2 Jazzy' for this MATLAB version.")
    message(WARNING "Building for ROS 2 Jazzy")
    add_definitions(-DROS2_DISTRO_JAZZY)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rosidl_typesupport_c REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package( class_loader REQUIRED)
find_package( console_bridge REQUIRED)
find_package( rclcpp REQUIRED)
find_package( rcutils REQUIRED)
# Add package include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/remote_control_interface")
include_directories("/usr/local/MATLAB/R2025b/extern/include")
include_directories("/usr/local/MATLAB/R2025b/extern/include/MatlabDataArray")
include_directories("/usr/local/MATLAB/R2025b/toolbox/ros/include/ros2")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(msg_files
  "msg/Gamepad.msg"
)
set(srv_files
)
set(action_files
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  ${action_files}
)
link_directories("/usr/local/MATLAB/R2025b/extern/bin/glnxa64")
# Library
add_library(
    remote_control_interface_matlab 
    SHARED
    src/remote_control_interface_Gamepad_message.cpp
)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(remote_control_interface_matlab PUBLIC 
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Wall -Wextra -Wpedantic
  >)
endif()
target_include_directories(remote_control_interface_matlab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/remote_control_interface>
  $<INSTALL_INTERFACE:include>)
target_link_libraries( remote_control_interface_matlab
	"/usr/local/MATLAB/R2025b/sys/os/glnxa64/orig/libstdc++.so.6"
	"/usr/local/MATLAB/R2025b/extern/bin/glnxa64/libMatlabDataArray.so"
	${CMAKE_DL_LIBS}
	)
ament_target_dependencies(
  remote_control_interface_matlab
  "class_loader"
  "console_bridge"
  "rclcpp"
  "rcutils"
)
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(remote_control_interface_matlab "${cpp_typesupport_target}")
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(remote_control_interface_matlab PRIVATE "REMOTE_CONTROL_INTERFACE_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS remote_control_interface_matlab
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (DIRECTORY m/ DESTINATION m/ FILES_MATCHING PATTERN "*.m")
ament_export_include_directories(
  include
)
ament_export_libraries(
  remote_control_interface_matlab
)
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/_ert_rtw/${file_i}
				   )
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CMAKE_INSTALL_PREFIX}/codegen/exe//${file_i}
				   )				   
endforeach(file_i)
ament_package()
# Generated on Thu Dec 04 19:55:55 2025
