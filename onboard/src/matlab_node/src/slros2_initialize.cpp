// Copyright 2022-2024 The MathWorks, Inc.
// Generated 07-Jul-2026 19:47:03
#include "slros2_initialize.h"
const std::string SLROSNodeName("matlab_node");
// matlab_node/Subsystem Reference1/Publish
SimulinkPublisher<custom_interfaces::msg::Debug,SL_Bus_custom_interfaces_Debug> Pub_matlab_node_266_3;
// matlab_node/mission_manager_interface_cgn/Subsystem/Publish
SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_matlab_node_108_269;
// matlab_node/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_matlab_node_37_150;
// matlab_node/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_matlab_node_38_2;
// matlab_node/DRR
SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_matlab_node_3;
// matlab_node/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_matlab_node_8;
// matlab_node/VR
SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_matlab_node_20;
// matlab_node/mission_manager_interface_cgn/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_matlab_node_108_265;
