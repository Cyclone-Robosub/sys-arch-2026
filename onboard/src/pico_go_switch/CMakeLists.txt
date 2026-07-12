cmake_minimum_required(VERSION 3.8)
project(pico_go_switch)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(fd_interface REQUIRED)

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# Main executable (without ENABLE_TESTING defined)
add_executable(pico_go_switch src/pico_go_switch.cpp)
ament_target_dependencies(pico_go_switch
  rclcpp
  custom_interfaces
  std_msgs
  fd_interface
)

# Install main executable
install(TARGETS
  pico_go_switch
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  # No unit tests yet :(
endif()

# Install launch files.
install(DIRECTORY
launch
DESTINATION share/${PROJECT_NAME}/
)

ament_package()