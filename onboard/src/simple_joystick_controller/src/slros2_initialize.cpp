// Copyright 2022-2024 The MathWorks, Inc.
// Generated 28-Jan-2026 23:12:37
#include "slros2_initialize.h"
const std::string SLROSNodeName("Simple_Joystick_Controller");
// Simple_Joystick_Controller/pwm_heartbeat_publisher/Publish1
SimulinkPublisher<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Pub_Simple_Joystick_Controller_32_2;
// Simple_Joystick_Controller/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_Simple_Joystick_Controller_30_2;
// Simple_Joystick_Controller/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_Simple_Joystick_Controller_33;
// Simple_Joystick_Controller/Subsystem/Subscribe
SimulinkSubscriber<remote_control_interface::msg::Gamepad,SL_Bus_remote_control_interface_Gamepad> Sub_Simple_Joystick_Controller_25;
