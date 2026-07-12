// Copyright 2022-2024 The MathWorks, Inc.
// Generated 11-Jul-2026 23:06:32
#include "slros2_initialize.h"
const std::string SLROSNodeName("joystick_enabled_matlab_node");
// joystick_enabled_matlab_node/ /Subsystem/Publish
SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_joystick_enabled_matlab_node_360_7;
// joystick_enabled_matlab_node/Subsystem Reference1/Publish
SimulinkPublisher<custom_interfaces::msg::Debug,SL_Bus_custom_interfaces_Debug> Pub_joystick_enabled_matlab_node_404_3;
// joystick_enabled_matlab_node/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_joystick_enabled_matlab_node_435_150;
// joystick_enabled_matlab_node/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_joystick_enabled_matlab_node_436_2;
// joystick_enabled_matlab_node/ /Subscribe
SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_joystick_enabled_matlab_node_360_284;
// joystick_enabled_matlab_node/DRR
SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_joystick_enabled_matlab_node_363;
// joystick_enabled_matlab_node/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_joystick_enabled_matlab_node_397;
// joystick_enabled_matlab_node/VR
SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_joystick_enabled_matlab_node_412;
// joystick_enabled_matlab_node/dvl_reset_subscriber/Subscribe
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_joystick_enabled_matlab_node_416;
// joystick_enabled_matlab_node/joystick_heartbeat/Subscribe
SimulinkSubscriber<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Sub_joystick_enabled_matlab_node_423;
// joystick_enabled_matlab_node/joystick_output/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Gamepad,SL_Bus_custom_interfaces_Gamepad> Sub_joystick_enabled_matlab_node_428;
