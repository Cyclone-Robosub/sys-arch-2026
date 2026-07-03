cmake_minimum_required(VERSION 3.5)
project(custom_interfaces)
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
find_package(rclcpp_action REQUIRED)
find_package( action_msgs REQUIRED)
find_package( builtin_interfaces REQUIRED)
find_package( class_loader REQUIRED)
find_package( console_bridge REQUIRED)
find_package( geometry_msgs REQUIRED)
find_package( nav_msgs REQUIRED)
find_package( rclcpp REQUIRED)
find_package( rcutils REQUIRED)
find_package( sensor_msgs REQUIRED)
find_package( std_msgs REQUIRED)
find_package( unique_identifier_msgs REQUIRED)
# Add package include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/custom_interfaces")
include_directories("/home/kjhaydon/Programs/MATLAB/R2025b/extern/include")
include_directories("/home/kjhaydon/Programs/MATLAB/R2025b/extern/include/MatlabDataArray")
include_directories("/home/kjhaydon/Programs/MATLAB/R2025b/toolbox/ros/include/ros2")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(msg_files
  "msg/Battery.msg"
  "msg/CommandTree.msg"
  "msg/Config.msg"
  "msg/DRR.msg"
  "msg/Gamepad.msg"
  "msg/Goal.msg"
  "msg/Imu.msg"
  "msg/Pose6D.msg"
  "msg/Position.msg"
  "msg/Pwms.msg"
  "msg/Result.msg"
  "msg/State.msg"
  "msg/VR.msg"
  "msg/WaypointMask.msg"
)
set(srv_files
  "srv/ControlMode.srv"
  "srv/GetConfidence.srv"
  "srv/SetConfig.srv"
)
set(action_files
  "action/DistanceTrick.action"
  "action/Dropper.action"
  "action/DurationTrick.action"
  "action/Idle.action"
  "action/ObjectRelativeWaypoint.action"
  "action/SeekObject.action"
  "action/Waypoint.action"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  ${action_files}
  DEPENDENCIES 
  action_msgs
  builtin_interfaces
  geometry_msgs
  nav_msgs
  sensor_msgs
  std_msgs
  unique_identifier_msgs
)
link_directories("/home/kjhaydon/Programs/MATLAB/R2025b/extern/bin/glnxa64")
# Library
add_library(
    custom_interfaces_matlab 
    SHARED
    src/custom_interfaces_Battery_message.cpp
    src/custom_interfaces_CommandTree_message.cpp
    src/custom_interfaces_Config_message.cpp
    src/custom_interfaces_DRR_message.cpp
    src/custom_interfaces_Gamepad_message.cpp
    src/custom_interfaces_Goal_message.cpp
    src/custom_interfaces_Imu_message.cpp
    src/custom_interfaces_Pose6D_message.cpp
    src/custom_interfaces_Position_message.cpp
    src/custom_interfaces_Pwms_message.cpp
    src/custom_interfaces_Result_message.cpp
    src/custom_interfaces_State_message.cpp
    src/custom_interfaces_VR_message.cpp
    src/custom_interfaces_WaypointMask_message.cpp
    src/custom_interfaces_ControlMode_service.cpp
    src/custom_interfaces_GetConfidence_service.cpp
    src/custom_interfaces_SetConfig_service.cpp
    src/custom_interfaces_DistanceTrick_action.cpp
    src/custom_interfaces_Dropper_action.cpp
    src/custom_interfaces_DurationTrick_action.cpp
    src/custom_interfaces_Idle_action.cpp
    src/custom_interfaces_ObjectRelativeWaypoint_action.cpp
    src/custom_interfaces_SeekObject_action.cpp
    src/custom_interfaces_Waypoint_action.cpp
)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
target_compile_options(custom_interfaces_matlab PUBLIC 
  $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>:
  -Wall -Wextra -Wpedantic
  >)
endif()
target_include_directories(custom_interfaces_matlab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/custom_interfaces>
  $<INSTALL_INTERFACE:include>)
target_link_libraries( custom_interfaces_matlab
	"/home/kjhaydon/Programs/MATLAB/R2025b/sys/os/glnxa64/orig/libstdc++.so.6"
	"/home/kjhaydon/Programs/MATLAB/R2025b/extern/bin/glnxa64/libMatlabDataArray.so"
	"/home/kjhaydon/Programs/MATLAB/R2025b/sys/ros2/glnxa64/ros2/lib/librclcpp_action.so"
	${CMAKE_DL_LIBS}
	)
ament_target_dependencies(
  custom_interfaces_matlab
  "action_msgs"
  "builtin_interfaces"
  "class_loader"
  "console_bridge"
  "geometry_msgs"
  "nav_msgs"
  "rclcpp"
  "rcutils"
  "sensor_msgs"
  "std_msgs"
  "unique_identifier_msgs"
rclcpp_action
)
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")
target_link_libraries(custom_interfaces_matlab "${cpp_typesupport_target}")
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(custom_interfaces_matlab PRIVATE "CUSTOM_INTERFACES_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  action_msgs
  builtin_interfaces
  class_loader
  console_bridge
  geometry_msgs
  nav_msgs
  rclcpp
  rcutils
  sensor_msgs
  std_msgs
  unique_identifier_msgs
)
install(
  TARGETS custom_interfaces_matlab
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
  custom_interfaces_matlab
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
# Generated on Mon Jun 29 17:48:23 2026
