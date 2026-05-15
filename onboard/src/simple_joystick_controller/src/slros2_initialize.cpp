// Copyright 2022-2024 The MathWorks, Inc.
// Generated 09-May-2026 13:12:40
#include "slros2_initialize.h"
const std::string SLROSNodeName("Simple_Joystick_CGN");
// Simple_Joystick_CGN/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_Simple_Joystick_CGN_85_150;
// Simple_Joystick_CGN/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_Simple_Joystick_CGN_86_2;
// Simple_Joystick_CGN/joystick_heartbeat/Subscribe
SimulinkSubscriber<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Sub_Simple_Joystick_CGN_73;
// Simple_Joystick_CGN/joystick_output/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Gamepad,SL_Bus_custom_interfaces_Gamepad> Sub_Simple_Joystick_CGN_77;
