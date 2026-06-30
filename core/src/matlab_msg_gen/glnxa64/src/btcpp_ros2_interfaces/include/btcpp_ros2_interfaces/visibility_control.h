#ifndef BTCPP_ROS2_INTERFACES__VISIBILITY_CONTROL_H_
#define BTCPP_ROS2_INTERFACES__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define BTCPP_ROS2_INTERFACES_EXPORT __attribute__ ((dllexport))
    #define BTCPP_ROS2_INTERFACES_IMPORT __attribute__ ((dllimport))
  #else
    #define BTCPP_ROS2_INTERFACES_EXPORT __declspec(dllexport)
    #define BTCPP_ROS2_INTERFACES_IMPORT __declspec(dllimport)
  #endif
  #ifdef BTCPP_ROS2_INTERFACES_BUILDING_LIBRARY
    #define BTCPP_ROS2_INTERFACES_PUBLIC BTCPP_ROS2_INTERFACES_EXPORT
  #else
    #define BTCPP_ROS2_INTERFACES_PUBLIC BTCPP_ROS2_INTERFACES_IMPORT
  #endif
  #define BTCPP_ROS2_INTERFACES_PUBLIC_TYPE BTCPP_ROS2_INTERFACES_PUBLIC
  #define BTCPP_ROS2_INTERFACES_LOCAL
#else
  #define BTCPP_ROS2_INTERFACES_EXPORT __attribute__ ((visibility("default")))
  #define BTCPP_ROS2_INTERFACES_IMPORT
  #if __GNUC__ >= 4
    #define BTCPP_ROS2_INTERFACES_PUBLIC __attribute__ ((visibility("default")))
    #define BTCPP_ROS2_INTERFACES_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define BTCPP_ROS2_INTERFACES_PUBLIC
    #define BTCPP_ROS2_INTERFACES_LOCAL
  #endif
  #define BTCPP_ROS2_INTERFACES_PUBLIC_TYPE
#endif
#endif  // BTCPP_ROS2_INTERFACES__VISIBILITY_CONTROL_H_
// Generated 29-Jun-2026 17:48:19
 