cmake_minimum_required(VERSION 3.8)
project(imu_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_options(-g)
endif()
add_subdirectory(ros2_ws/src/ros2)
# find dependencies
set(CMAKE_CXX_STANDARD 20)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(custom_interfaces REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(imu imu.cpp)

ament_target_dependencies(imu rclcpp custom_interfaces std_msgs std_srvs)

install(TARGETS
  imu
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  add_library(${PROJECT_NAME}_lib imu.cpp)
  target_compile_definitions(${PROJECT_NAME}_lib PUBLIC ENABLE_TESTING)
  ament_target_dependencies(${PROJECT_NAME}_lib
    rclcpp
    std_msgs
    custom_interfaces
    std_srvs
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
  )
endif()



ament_package()
