cmake_minimum_required(VERSION 3.14)
project(mission_executive)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# All dependencies from colcon/rosdep
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(behaviortree_cpp REQUIRED)

add_executable(mission_executor_node
  src/mission_executor_node.cpp
  src/bt_nodes/navigate_to_waypoint.cpp
  src/bt_nodes/detect_object.cpp
  src/bt_nodes/send_manipulator_command.cpp
  src/bt_nodes/wait_duration.cpp
)

target_include_directories(mission_executor_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_compile_features(mission_executor_node PUBLIC cxx_std_17)

ament_target_dependencies(mission_executor_node
  rclcpp
  rclcpp_action
  std_msgs
  geometry_msgs
  nav2_msgs
)

target_link_libraries(mission_executor_node
  behaviortree_cpp::behaviortree_cpp
)

install(TARGETS mission_executor_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files if they exist
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
  OPTIONAL
)

# Install tree XML files if they exist
install(DIRECTORY trees/
  DESTINATION share/${PROJECT_NAME}/trees
  OPTIONAL
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
