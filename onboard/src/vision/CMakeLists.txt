cmake_minimum_required(VERSION 3.8)
project(vision)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── ROS 2 dependencies ────────────────────────────────────────────────────────
find_package(ament_cmake REQUIRED)
find_package(rclcpp      REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs    REQUIRED)
find_package(cv_bridge   REQUIRED)

# ── OpenCV ────────────────────────────────────────────────────────────────────
find_package(OpenCV REQUIRED)

# ── LibTorch ──────────────────────────────────────────────────────────────────
# Set TORCH_DIR to your LibTorch installation, e.g.:
#   cmake .. -DTORCH_DIR=/opt/libtorch/share/cmake/Torch
find_package(Torch REQUIRED)

# ── keypoint_detector library ─────────────────────────────────────────────────
add_library(keypoint_detector
  src/keypoint_detector.cpp
)

target_include_directories(keypoint_detector PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${TORCH_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(keypoint_detector
  ${TORCH_LIBRARIES}
  ${OpenCV_LIBS}
)

ament_target_dependencies(keypoint_detector
  rclcpp
)

# ── keypoint_node executable ──────────────────────────────────────────────────
add_executable(keypoint_node
  src/keypoint_node.cpp
)

target_include_directories(keypoint_node PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${TORCH_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(keypoint_node
  keypoint_detector
  ${TORCH_LIBRARIES}
  ${OpenCV_LIBS}
)

ament_target_dependencies(keypoint_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
)

# ── install ───────────────────────────────────────────────────────────────────
install(TARGETS keypoint_detector keypoint_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_keypoint_detector
    test/test_keypoint_detector.cpp
  )

  target_link_libraries(test_keypoint_detector
    keypoint_detector
    ${TORCH_LIBRARIES}
    ${OpenCV_LIBS}
  )
endif()

ament_package()
