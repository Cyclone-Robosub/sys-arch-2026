if(EXISTS "/usr/include/NvInfer.h")

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
find_package(custom_interfaces REQUIRED)

# ── OpenCV ────────────────────────────────────────────────────────────────────
find_package(OpenCV REQUIRED)

# ── GStreamer ─────────────────────────────────────────────────────────────────
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-app-1.0)

# ── TensorRT ──────────────────────────────────────────────────────────────────
find_path(TENSORRT_INCLUDE_DIR NvInfer.h
  PATHS /usr/include /usr/local/include
  REQUIRED
)
find_library(NVINFER_LIB nvinfer
  PATHS /usr/lib/aarch64-linux-gnu /usr/lib/x86_64-linux-gnu /usr/local/lib
  REQUIRED
)

# ── CUDA ──────────────────────────────────────────────────────────────────────
find_package(CUDAToolkit REQUIRED)

# ── keypoint_detector library ─────────────────────────────────────────────────
add_library(keypoint_detector
  src/keypoint_detector.cpp
)

target_include_directories(keypoint_detector PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${TENSORRT_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(keypoint_detector
  ${NVINFER_LIB}
  CUDA::cudart
  ${OpenCV_LIBS}
)

ament_target_dependencies(keypoint_detector
  rclcpp
  custom_interfaces
)

# ── keypoint_node executable ──────────────────────────────────────────────────
add_executable(keypoint_node
  src/keypoint_node.cpp
)

target_include_directories(keypoint_node PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${TENSORRT_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(keypoint_node
  keypoint_detector
  ${NVINFER_LIB}
  CUDA::cudart
  ${OpenCV_LIBS}
)

ament_target_dependencies(keypoint_node
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  custom_interfaces
)

# ── camera_feed_node executable ───────────────────────────────────────────────
add_executable(camera_feed_node
  src/camera_feed_node.cpp
)

target_include_directories(camera_feed_node PRIVATE
  ${GST_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(camera_feed_node
  ${GST_LIBRARIES}
  ${OpenCV_LIBS}
)

ament_target_dependencies(camera_feed_node
  rclcpp
  sensor_msgs
  cv_bridge
)

# ── install ───────────────────────────────────────────────────────────────────
install(TARGETS keypoint_detector keypoint_node camera_feed_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
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
    ${NVINFER_LIB}
    CUDA::cudart
    ${OpenCV_LIBS}
  )
endif()

ament_package()

endif() # vision exists
