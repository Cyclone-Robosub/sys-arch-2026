//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_Controller_types.h
//
// Code generated for Simulink model 'Simple_Joystick_Controller'.
//
// Model version                  : 1.10
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Feb 19 19:35:40 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef Simple_Joystick_Controller_types_h_
#define Simple_Joystick_Controller_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_custom_interfaces_Pwms_
#define DEFINED_TYPEDEF_FOR_SL_Bus_custom_interfaces_Pwms_

// MsgType=custom_interfaces/Pwms
struct SL_Bus_custom_interfaces_Pwms
{
  int32_T pwms[8];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_custom_interfaces_Gamepad_
#define DEFINED_TYPEDEF_FOR_SL_Bus_custom_interfaces_Gamepad_

// MsgType=custom_interfaces/Gamepad
struct SL_Bus_custom_interfaces_Gamepad
{
  real32_T x;
  real32_T y;
  real32_T rise;
  real32_T sink;
  real32_T yaw;
  real32_T pitch;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Bool_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Bool_

// MsgType=std_msgs/Bool
struct SL_Bus_std_msgs_Bool
{
  boolean_T data;
};

#endif

// Custom Type definition for MATLABSystem: '<S9>/SinkBlock'
#include "rmw/qos_profiles.h"
#ifndef struct_sJ4ih70VmKcvCeguWN0mNVF
#define struct_sJ4ih70VmKcvCeguWN0mNVF

struct sJ4ih70VmKcvCeguWN0mNVF
{
  real_T sec;
  real_T nsec;
};

#endif                                 // struct_sJ4ih70VmKcvCeguWN0mNVF

#ifndef struct_ros_slros2_internal_block_Sub_T
#define struct_ros_slros2_internal_block_Sub_T

struct ros_slros2_internal_block_Sub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                                // struct_ros_slros2_internal_block_Sub_T

#ifndef struct_ros_slros2_internal_block_Pub_T
#define struct_ros_slros2_internal_block_Pub_T

struct ros_slros2_internal_block_Pub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T QOSAvoidROSNamespaceConventions;
};

#endif                                // struct_ros_slros2_internal_block_Pub_T

// Forward declaration for rtModel
typedef struct tag_RTM_Simple_Joystick_Contr_T RT_MODEL_Simple_Joystick_Cont_T;

#endif                                 // Simple_Joystick_Controller_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
