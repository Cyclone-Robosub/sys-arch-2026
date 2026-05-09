//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_CGN.h
//
// Code generated for Simulink model 'Simple_Joystick_CGN'.
//
// Model version                  : 1.14
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat May  9 13:12:35 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef Simple_Joystick_CGN_h_
#define Simple_Joystick_CGN_h_
#include <cmath>
#include "rtwtypes.h"
#include "slros2_initialize.h"
#include "Simple_Joystick_CGN_types.h"

// Block signals (default storage)
struct B_Simple_Joystick_CGN_T {
  SL_Bus_custom_interfaces_Gamepad In1;// '<S12>/In1'
  SL_Bus_custom_interfaces_Gamepad rtb_SourceBlock_o2_m;
  int32_T pwms_vert[8];
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S6>/Bus Creator3'
  char_T b_zeroDelimTopic[20];
  char_T b_zeroDelimTopic_c[16];
  char_T b_zeroDelimTopic_k[16];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  real_T pwms_horiz;
  real_T pwms_vert_idx_0;
  real_T pwms_vert_idx_1;
  real_T pwms_vert_idx_2;
  boolean_T manual_control_flag;       // '<S1>/MATLAB Function'
};

// Block states (default storage) for system '<Root>'
struct DW_Simple_Joystick_CGN_T {
  ros_slros2_internal_block_Sub_T obj; // '<S11>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_g;// '<S8>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_c;// '<S16>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_gk;// '<S15>/SinkBlock'
  real_T time_since_last_beat;         // '<S1>/MATLAB Function'
  boolean_T joystick_flag;             // '<Root>/mode_manager'
  boolean_T prior_joystick_flag;       // '<Root>/mode_manager'
  boolean_T do_mission_file_flag;      // '<Root>/mode_manager'
  boolean_T prior_do_mission_file_flag;// '<Root>/mode_manager'
};

// Constant parameters (default storage)
struct ConstP_Simple_Joystick_CGN_T {
  // Pooled Parameter (Expression: )
  //  Referenced by:
  //    '<S8>/Constant'
  //    '<S14>/Constant'
  //    '<S9>/Out1'

  SL_Bus_std_msgs_Empty pooled2;
};

// Real-time Model Data Structure
struct tag_RTM_Simple_Joystick_CGN_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;

  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Constant parameters (default storage)
extern const ConstP_Simple_Joystick_CGN_T Simple_Joystick_CGN_ConstP;

// Class declaration for model Simple_Joystick_CGN
class Simple_Joystick_CGN final
{
  // public data and function members
 public:
  // Copy Constructor
  Simple_Joystick_CGN(Simple_Joystick_CGN const&) = delete;

  // Assignment Operator
  Simple_Joystick_CGN& operator= (Simple_Joystick_CGN const&) & = delete;

  // Move Constructor
  Simple_Joystick_CGN(Simple_Joystick_CGN &&) = delete;

  // Move Assignment Operator
  Simple_Joystick_CGN& operator= (Simple_Joystick_CGN &&) = delete;

  // Real-Time Model get method
  RT_MODEL_Simple_Joystick_CGN_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  Simple_Joystick_CGN();

  // Destructor
  ~Simple_Joystick_CGN();

  // private data and function members
 private:
  // Block signals
  B_Simple_Joystick_CGN_T Simple_Joystick_CGN_B;

  // Block states
  DW_Simple_Joystick_CGN_T Simple_Joystick_CGN_DW;

  // private member function(s) for subsystem '<Root>'
  void Simple_J_Subscriber_setupImpl_n(const ros_slros2_internal_block_Sub_T
    *obj);
  void Simple_Joy_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void Simple_Jo_Publisher_setupImpl_n(const ros_slros2_internal_block_Pub_T
    *obj);
  void Simple_Joys_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_Simple_Joystick_CGN_T Simple_Joystick_CGN_M;
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
//  '<Root>' : 'Simple_Joystick_CGN'
//  '<S1>'   : 'Simple_Joystick_CGN/joystick_heartbeat'
//  '<S2>'   : 'Simple_Joystick_CGN/joystick_output'
//  '<S3>'   : 'Simple_Joystick_CGN/joystick_to_pwm'
//  '<S4>'   : 'Simple_Joystick_CGN/mode_manager'
//  '<S5>'   : 'Simple_Joystick_CGN/pwm_heartbeat_publisher'
//  '<S6>'   : 'Simple_Joystick_CGN/pwm_publisher'
//  '<S7>'   : 'Simple_Joystick_CGN/joystick_heartbeat/MATLAB Function'
//  '<S8>'   : 'Simple_Joystick_CGN/joystick_heartbeat/Subscribe'
//  '<S9>'   : 'Simple_Joystick_CGN/joystick_heartbeat/Subscribe/Enabled Subsystem'
//  '<S10>'  : 'Simple_Joystick_CGN/joystick_output/MATLAB Function'
//  '<S11>'  : 'Simple_Joystick_CGN/joystick_output/Subscribe'
//  '<S12>'  : 'Simple_Joystick_CGN/joystick_output/Subscribe/Enabled Subsystem'
//  '<S13>'  : 'Simple_Joystick_CGN/joystick_to_pwm/joystick_inputs_to_body_forces'
//  '<S14>'  : 'Simple_Joystick_CGN/pwm_heartbeat_publisher/Blank Message1'
//  '<S15>'  : 'Simple_Joystick_CGN/pwm_heartbeat_publisher/Publish2'
//  '<S16>'  : 'Simple_Joystick_CGN/pwm_publisher/Publish'

#endif                                 // Simple_Joystick_CGN_h_

//
// File trailer for generated code.
//
// [EOF]
//
