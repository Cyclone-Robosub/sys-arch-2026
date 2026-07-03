// Copyright 2022-2024 The MathWorks, Inc.
// Generated 02-Jul-2026 19:07:14
#include "slros2_initialize.h"
const std::string SLROSNodeName("cascaded_controller");
// cascaded_controller/mission_manager_interface_cgn/Subsystem/Publish
SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_cascaded_controller_108_8;
// cascaded_controller/pwm_heartbeat_publisher/Publish2
SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_cascaded_controller_37_150;
// cascaded_controller/pwm_publisher/Publish
SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_cascaded_controller_38_2;
// cascaded_controller/DRR
SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_cascaded_controller_3;
// cascaded_controller/IMU
SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_cascaded_controller_8;
// cascaded_controller/VR
SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_cascaded_controller_20;
// cascaded_controller/mission_manager_interface_cgn/Subscribe
SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_cascaded_controller_108_4;
