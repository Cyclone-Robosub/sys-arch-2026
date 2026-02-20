#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include "rclcpp/rclcpp.hpp"
#include <custom_interfaces/msg/gamepad.hpp>
#include <custom_interfaces/msg/pwms.hpp>
#include <std_msgs/msg/bool.hpp>
#include "Simple_Joystick_Controller_types.h"
#include "slros_msgconvert_utils.h"


[[maybe_unused]] static void convertFromBus(custom_interfaces::msg::Gamepad& msgPtr, SL_Bus_custom_interfaces_Gamepad const* busPtr);
[[maybe_unused]] static void convertToBus(SL_Bus_custom_interfaces_Gamepad* busPtr, const custom_interfaces::msg::Gamepad& msgPtr);

[[maybe_unused]] static void convertFromBus(custom_interfaces::msg::Pwms& msgPtr, SL_Bus_custom_interfaces_Pwms const* busPtr);
[[maybe_unused]] static void convertToBus(SL_Bus_custom_interfaces_Pwms* busPtr, const custom_interfaces::msg::Pwms& msgPtr);

[[maybe_unused]] static void convertFromBus(std_msgs::msg::Bool& msgPtr, SL_Bus_std_msgs_Bool const* busPtr);
[[maybe_unused]] static void convertToBus(SL_Bus_std_msgs_Bool* busPtr, const std_msgs::msg::Bool& msgPtr);



// Conversions between SL_Bus_custom_interfaces_Gamepad and custom_interfaces::msg::Gamepad

[[maybe_unused]] static void convertFromBus(custom_interfaces::msg::Gamepad& msgPtr, SL_Bus_custom_interfaces_Gamepad const* busPtr)
{
  const std::string rosMessageType("custom_interfaces/Gamepad");

  msgPtr.pitch =  busPtr->pitch;
  msgPtr.rise =  busPtr->rise;
  msgPtr.sink =  busPtr->sink;
  msgPtr.x =  busPtr->x;
  msgPtr.y =  busPtr->y;
  msgPtr.yaw =  busPtr->yaw;
}

[[maybe_unused]] static void convertToBus(SL_Bus_custom_interfaces_Gamepad* busPtr, const custom_interfaces::msg::Gamepad& msgPtr)
{
  const std::string rosMessageType("custom_interfaces/Gamepad");

  busPtr->pitch =  msgPtr.pitch;
  busPtr->rise =  msgPtr.rise;
  busPtr->sink =  msgPtr.sink;
  busPtr->x =  msgPtr.x;
  busPtr->y =  msgPtr.y;
  busPtr->yaw =  msgPtr.yaw;
}


// Conversions between SL_Bus_custom_interfaces_Pwms and custom_interfaces::msg::Pwms

[[maybe_unused]] static void convertFromBus(custom_interfaces::msg::Pwms& msgPtr, SL_Bus_custom_interfaces_Pwms const* busPtr)
{
  const std::string rosMessageType("custom_interfaces/Pwms");

  convertFromBusFixedPrimitiveArray(msgPtr.pwms, busPtr->pwms);
}

[[maybe_unused]] static void convertToBus(SL_Bus_custom_interfaces_Pwms* busPtr, const custom_interfaces::msg::Pwms& msgPtr)
{
  const std::string rosMessageType("custom_interfaces/Pwms");

  convertToBusFixedPrimitiveArray(busPtr->pwms, msgPtr.pwms, slros::NoopWarning());
}


// Conversions between SL_Bus_std_msgs_Bool and std_msgs::msg::Bool

[[maybe_unused]] static void convertFromBus(std_msgs::msg::Bool& msgPtr, SL_Bus_std_msgs_Bool const* busPtr)
{
  const std::string rosMessageType("std_msgs/Bool");

  msgPtr.data =  busPtr->data;
}

[[maybe_unused]] static void convertToBus(SL_Bus_std_msgs_Bool* busPtr, const std_msgs::msg::Bool& msgPtr)
{
  const std::string rosMessageType("std_msgs/Bool");

  busPtr->data =  msgPtr.data;
}



#endif
