// Copyright 2022-2024 The MathWorks, Inc.
// Generated 14-Jul-2026 08:59:35
#ifndef _SLROS2_INITIALIZE_H_
#define _SLROS2_INITIALIZE_H_
#include "matlab_semifinal_types.h"
// Generic pub-sub header
#include "slros2_generic_pubsub.h"
#ifndef SET_QOS_VALUES
#define SET_QOS_VALUES(qosStruct, _history, _depth, _durability, _reliability, _deadline \
, _lifespan, _liveliness, _lease_duration, _avoid_ros_namespace_conventions)             \
    {                                                                                    \
        qosStruct.history = _history;                                                    \
        qosStruct.depth = _depth;                                                        \
        qosStruct.durability = _durability;                                              \
        qosStruct.reliability = _reliability;                                            \
        qosStruct.deadline.sec = _deadline.sec;                                          \
        qosStruct.deadline.nsec = _deadline.nsec;                                        \
        qosStruct.lifespan.sec = _lifespan.sec;                                          \
        qosStruct.lifespan.nsec = _lifespan.nsec;                                        \
        qosStruct.liveliness = _liveliness;                                              \
        qosStruct.liveliness_lease_duration.sec = _lease_duration.sec;                   \
        qosStruct.liveliness_lease_duration.nsec = _lease_duration.nsec;                 \
        qosStruct.avoid_ros_namespace_conventions = _avoid_ros_namespace_conventions;    \
    }
#endif
inline rclcpp::QoS getQOSSettingsFromRMW(const rmw_qos_profile_t& qosProfile) {
    rclcpp::QoS qos(rclcpp::QoSInitialization::from_rmw(qosProfile));
    if (RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL == qosProfile.durability) {
        qos.transient_local();
    } else {
        qos.durability_volatile();
    }
    if (RMW_QOS_POLICY_RELIABILITY_RELIABLE == qosProfile.reliability) {
        qos.reliable();
    } else {
        qos.best_effort();
    }
    return qos;
}
// matlab_semifinal/ /Subsystem/Publish
extern SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_matlab_semifinal_549_7;
// matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Subsystem/Publish
extern SimulinkPublisher<std_msgs::msg::UInt8,SL_Bus_std_msgs_UInt8> Pub_matlab_semifinal_588_262_826_2;
// matlab_semifinal/Subsystem Reference1/Publish
extern SimulinkPublisher<custom_interfaces::msg::Debug,SL_Bus_custom_interfaces_Debug> Pub_matlab_semifinal_594_3;
// matlab_semifinal/pwm_heartbeat_publisher/Publish2
extern SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_matlab_semifinal_625_150;
// matlab_semifinal/pwm_publisher/Publish
extern SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_matlab_semifinal_626_2;
// matlab_semifinal/ /Subscribe
extern SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_matlab_semifinal_549_284;
// matlab_semifinal/DRR
extern SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_matlab_semifinal_552;
// matlab_semifinal/IMU
extern SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_matlab_semifinal_587;
// matlab_semifinal/VR
extern SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_matlab_semifinal_602;
// matlab_semifinal/dvl_reset_subscriber/Subscribe
extern SimulinkSubscriber<std_msgs::msg::Bool,SL_Bus_std_msgs_Bool> Sub_matlab_semifinal_606;
// matlab_semifinal/joystick_output/Subscribe
extern SimulinkSubscriber<custom_interfaces::msg::Gamepad,SL_Bus_custom_interfaces_Gamepad> Sub_matlab_semifinal_618;
#endif
