// Copyright 2022-2024 The MathWorks, Inc.
// Generated 02-Jul-2026 21:06:32
#ifndef _SLROS2_INITIALIZE_H_
#define _SLROS2_INITIALIZE_H_
#include "cascaded_controller_types.h"
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
// cascaded_controller/mission_manager_interface_cgn/Subsystem/Publish
extern SimulinkPublisher<custom_interfaces::msg::Result,SL_Bus_custom_interfaces_Result> Pub_cascaded_controller_108_8;
// cascaded_controller/pwm_heartbeat_publisher/Publish2
extern SimulinkPublisher<std_msgs::msg::Empty,SL_Bus_std_msgs_Empty> Pub_cascaded_controller_37_150;
// cascaded_controller/pwm_publisher/Publish
extern SimulinkPublisher<custom_interfaces::msg::Pwms,SL_Bus_custom_interfaces_Pwms> Pub_cascaded_controller_38_2;
// cascaded_controller/DRR
extern SimulinkSubscriber<custom_interfaces::msg::DRR,SL_Bus_custom_interfaces_DRR> Sub_cascaded_controller_3;
// cascaded_controller/IMU
extern SimulinkSubscriber<custom_interfaces::msg::Imu,SL_Bus_custom_interfaces_Imu> Sub_cascaded_controller_8;
// cascaded_controller/VR
extern SimulinkSubscriber<custom_interfaces::msg::VR,SL_Bus_custom_interfaces_VR> Sub_cascaded_controller_20;
// cascaded_controller/mission_manager_interface_cgn/Subscribe
extern SimulinkSubscriber<custom_interfaces::msg::Goal,SL_Bus_custom_interfaces_Goal> Sub_cascaded_controller_108_4;
#endif
