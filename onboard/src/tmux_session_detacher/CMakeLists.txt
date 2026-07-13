cmake_minimum_required(VERSION 3.8)
project(tmux_session_detacher)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# Main executable (without ENABLE_TESTING defined)
add_executable(tmux_session_detacher src/tmux_session_detacher.cpp)
ament_target_dependencies(tmux_session_detacher
  rclcpp
  std_srvs
)

# Install main executable
install(TARGETS
  tmux_session_detacher
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  # Nothing yet
endif()

ament_package()
