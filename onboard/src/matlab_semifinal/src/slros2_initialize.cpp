// Copyright 2022-2024 The MathWorks, Inc.
// Generated 14-Jul-2026 17:20:11
#include "slros2_initialize.h"
const std::string SLROSNodeName("matlab_semifinal");
// matlab_semifinal/ /Subsystem/Publish
SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_Mission_Manager_HIL_209_7;
// matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Subsystem/Publish
SimulinkPublisher<std_msgs::msg::UInt8,SL_Bus_std_msgs_UInt8> Pub_Mission_Manager_HIL_123_262_826_2;
// matlab_semifinal/Subsystem Reference1/Publish
SimulinkPublisher<custom_interfaces::msg::Debug,SL_Bus_custom_interfaces_Debug> Pub_matlab_semifinal_594_3;
// matlab_semifinal/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_matlab_semifinal_625_150;
// matlab_semifinal/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_matlab_semifinal_626_2;
// matlab_semifinal/ /Subscribe
SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_Mission_Manager_HIL_209_284;
// matlab_semifinal/DRR
SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_matlab_semifinal_552;
// matlab_semifinal/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_matlab_semifinal_587;
// matlab_semifinal/VR
SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_matlab_semifinal_602;
// matlab_semifinal/dvl_reset_subscriber/Subscribe
SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_matlab_semifinal_606;
// matlab_semifinal/joystick_output/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Gamepad,SL_Bus_custom_interfaces_Gamepad> Sub_matlab_semifinal_618;
