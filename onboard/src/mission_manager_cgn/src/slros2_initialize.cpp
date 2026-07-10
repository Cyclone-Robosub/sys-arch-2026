// Copyright 2022-2024 The MathWorks, Inc.
// Generated 30-Jun-2026 20:18:04
#include "slros2_initialize.h"
const std::string SLROSNodeName("Mission_Manager_CGN");
// Mission_Manager_CGN/ /Subsystem/Publish
SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_Mission_Manager_CGN_286_7;
// Mission_Manager_CGN/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_Mission_Manager_CGN_322_150;
// Mission_Manager_CGN/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_Mission_Manager_CGN_323_2;
// Mission_Manager_CGN/ /Subscribe
SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_Mission_Manager_CGN_286_284;
// Mission_Manager_CGN/DRR
SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_Mission_Manager_CGN_288;
// Mission_Manager_CGN/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_Mission_Manager_CGN_293;
// Mission_Manager_CGN/VR
SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_Mission_Manager_CGN_305;
