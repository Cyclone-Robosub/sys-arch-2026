cmake_minimum_required(VERSION 3.8)
project(imu_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_options(-g)
endif()

# find dependencies
set(CMAKE_CXX_STANDARD 20)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(inertial_sense_ros2 REQUIRED)

find_package(yaml-cpp REQUIRED)
find_package(custom_interfaces REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(imu imu.cpp)
target_include_directories(imu PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/ros2_ws/src/ros2/shared/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ros2_ws/src/inertial-sense-sdk
)
ament_target_dependencies(imu rclcpp custom_interfaces std_msgs std_srvs)


install(TARGETS
  imu
  DESTINATION lib/${PROJECT_NAME})
ament_export_include_directories(ros2_ws/srccshared/include)
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  add_library(${PROJECT_NAME}_lib imu.cpp)
  
  target_compile_definitions(${PROJECT_NAME}_lib PUBLIC ENABLE_TESTING)
  ament_target_dependencies(${PROJECT_NAME}_lib
    rclcpp
    std_msgs
    custom_interfaces
    std_srvs
    inertial_sense_ros2
  )
  target_include_directories(${PROJECT_NAME}_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

  ament_add_gtest(${PROJECT_NAME}_test imu_test/imu_test.cpp imu.cpp)
  target_compile_definitions(${PROJECT_NAME}_test PUBLIC ENABLE_TESTING)
  target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)
  target_include_directories(${PROJECT_NAME}_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  ament_target_dependencies(${PROJECT_NAME}_test
    rclcpp
    std_msgs
    std_srvs
    custom_interfaces
    inertial_sense_ros2
  )
endif()



ament_package()
