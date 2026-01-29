//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_Controller.h
//
// Code generated for Simulink model 'Simple_Joystick_Controller'.
//
// Model version                  : 1.7
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Jan 28 23:12:33 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef Simple_Joystick_Controller_h_
#define Simple_Joystick_Controller_h_
#include <cmath>
#include "rtwtypes.h"
#include "slros2_initialize.h"
#include "Simple_Joystick_Controller_types.h"

// Block signals (default storage)
struct B_Simple_Joystick_Controller_T {
  SL_Bus_custom_interfaces_Imu r;
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S5>/Bus Creator3'
  SL_Bus_remote_control_interface_Gamepad In1;// '<S8>/In1'
  SL_Bus_remote_control_interface_Gamepad rtb_SourceBlock_o2_g_m;
  char_T b_zeroDelimTopic[16];
  char_T b_zeroDelimTopic_c[16];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF deadline_k;
};

// Block states (default storage) for system '<Root>'
struct DW_Simple_Joystick_Controller_T {
  ros_slros2_internal_block_Sub_T obj; // '<S7>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_e;// '<S1>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_a;// '<S11>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_l;// '<S10>/SinkBlock'
};

// Real-time Model Data Structure
struct tag_RTM_Simple_Joystick_Contr_T {
  const char_T * volatile errorStatus;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Class declaration for model Simple_Joystick_Controller
class Simple_Joystick_Controller final
{
  // public data and function members
 public:
  // Copy Constructor
  Simple_Joystick_Controller(Simple_Joystick_Controller const&) = delete;

  // Assignment Operator
  Simple_Joystick_Controller& operator= (Simple_Joystick_Controller const&) & =
    delete;

  // Move Constructor
  Simple_Joystick_Controller(Simple_Joystick_Controller &&) = delete;

  // Move Assignment Operator
  Simple_Joystick_Controller& operator= (Simple_Joystick_Controller &&) = delete;

  // Real-Time Model get method
  RT_MODEL_Simple_Joystick_Cont_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  Simple_Joystick_Controller();

  // Destructor
  ~Simple_Joystick_Controller();

  // private data and function members
 private:
  // Block signals
  B_Simple_Joystick_Controller_T Simple_Joystick_Controller_B;

  // Block states
  DW_Simple_Joystick_Controller_T Simple_Joystick_Controller_DW;

  // private member function(s) for subsystem '<Root>'
  void Simple_J_Subscriber_setupImpl_m(const ros_slros2_internal_block_Sub_T
    *obj);
  void Simple_Jo_Publisher_setupImpl_m(const ros_slros2_internal_block_Pub_T
    *obj);
  void Simple_Joy_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void Simple_Joys_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_Simple_Joystick_Cont_T Simple_Joystick_Controller_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'Simple_Joystick_Controller'
//  '<S1>'   : 'Simple_Joystick_Controller/IMU'
//  '<S2>'   : 'Simple_Joystick_Controller/Subsystem'
//  '<S3>'   : 'Simple_Joystick_Controller/joystick_to_pwm'
//  '<S4>'   : 'Simple_Joystick_Controller/pwm_heartbeat_publisher'
//  '<S5>'   : 'Simple_Joystick_Controller/pwm_publisher'
//  '<S6>'   : 'Simple_Joystick_Controller/IMU/Enabled Subsystem'
//  '<S7>'   : 'Simple_Joystick_Controller/Subsystem/Subscribe'
//  '<S8>'   : 'Simple_Joystick_Controller/Subsystem/Subscribe/Enabled Subsystem'
//  '<S9>'   : 'Simple_Joystick_Controller/joystick_to_pwm/joystick_inputs_to_body_forces1'
//  '<S10>'  : 'Simple_Joystick_Controller/pwm_heartbeat_publisher/Publish1'
//  '<S11>'  : 'Simple_Joystick_Controller/pwm_publisher/Publish'

#endif                                 // Simple_Joystick_Controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
