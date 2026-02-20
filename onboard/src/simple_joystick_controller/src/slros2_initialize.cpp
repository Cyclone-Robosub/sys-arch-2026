// Copyright 2022-2024 The MathWorks, Inc.
// Generated 19-Feb-2026 19:35:43
#include "slros2_initialize.h"
const std::string SLROSNodeName("Simple_Joystick_Controller");
// Simple_Joystick_Controller/Subsystem Reference/Publish2
SimulinkPublisher<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Pub_Simple_Joystick_HIL_32_150;
// Simple_Joystick_Controller/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_Simple_Joystick_Controller_30_2;
// Simple_Joystick_Controller/Subsystem/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Gamepad,SL_Bus_custom_interfaces_Gamepad> Sub_Simple_Joystick_Controller_25;
