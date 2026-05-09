//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_CGN.cpp
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
#include "Simple_Joystick_CGN.h"
#include "Simple_Joystick_CGN_types.h"
#include <cmath>
#include "rtwtypes.h"
#include "rmw/qos_profiles.h"
#include <stddef.h>

static void rate_scheduler(RT_MODEL_Simple_Joystick_CGN_T *const
  Simple_Joystick_CGN_M);

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(RT_MODEL_Simple_Joystick_CGN_T *const
  Simple_Joystick_CGN_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (Simple_Joystick_CGN_M->Timing.TaskCounters.TID[1])++;
  if ((Simple_Joystick_CGN_M->Timing.TaskCounters.TID[1]) > 29) {// Sample time: [0.5s, 0.0s] 
    Simple_Joystick_CGN_M->Timing.TaskCounters.TID[1] = 0;
  }
}

void Simple_Joystick_CGN::Simple_J_Subscriber_setupImpl_n(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ps5_controller" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S11>/SourceBlock'
  deadline.sec = 0.0;
  deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 16; i++) {
    // Start for MATLABSystem: '<S11>/SourceBlock'
    Simple_Joystick_CGN_B.b_zeroDelimTopic_k[i] = b_zeroDelimTopic[i];
  }

  Sub_Simple_Joystick_CGN_77.createSubscriber
    (&Simple_Joystick_CGN_B.b_zeroDelimTopic_k[0], qos_profile);
}

void Simple_Joystick_CGN::Simple_Joy_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[20]{ "/joystick_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S8>/SourceBlock'
  deadline.sec = 0.0;
  deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 20; i++) {
    // Start for MATLABSystem: '<S8>/SourceBlock'
    Simple_Joystick_CGN_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Sub_Simple_Joystick_CGN_73.createSubscriber
    (&Simple_Joystick_CGN_B.b_zeroDelimTopic[0], qos_profile);
}

void Simple_Joystick_CGN::Simple_Jo_Publisher_setupImpl_n(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S16>/SinkBlock'
  Simple_Joystick_CGN_B.deadline.sec = 0.0;
  Simple_Joystick_CGN_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 Simple_Joystick_CGN_B.deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S16>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Simple_Joystick_CGN_86_2.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void Simple_Joystick_CGN::Simple_Joys_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S15>/SinkBlock'
  deadline.sec = 0.0;
  deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 16; i++) {
    // Start for MATLABSystem: '<S15>/SinkBlock'
    Simple_Joystick_CGN_B.b_zeroDelimTopic_c[i] = b_zeroDelimTopic[i];
  }

  Pub_Simple_Joystick_CGN_85_150.createPublisher
    (&Simple_Joystick_CGN_B.b_zeroDelimTopic_c[0], qos_profile);
}

// Model step function
void Simple_Joystick_CGN::step()
{
  SL_Bus_std_msgs_Empty tmp;
  real_T pwms_horiz_idx_0;
  real_T pwms_horiz_idx_1;
  real_T pwms_horiz_idx_2;
  real_T pwms_horiz_idx_3;
  real_T pwms_vert_idx_3;
  int32_T i;
  real32_T pwms_horiz_idx_0_tmp;
  real32_T pwms_vert_idx_0_tmp;
  real32_T pwms_vert_idx_0_tmp_0;
  boolean_T b_varargout_1;
  boolean_T tmp_0;

  // MATLABSystem: '<S11>/SourceBlock'
  b_varargout_1 = Sub_Simple_Joystick_CGN_77.getLatestMessage
    (&Simple_Joystick_CGN_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S11>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S12>/Enable'

  // Start for MATLABSystem: '<S11>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S12>/In1'
    Simple_Joystick_CGN_B.In1 = Simple_Joystick_CGN_B.rtb_SourceBlock_o2_m;
  }

  // End of Start for MATLABSystem: '<S11>/SourceBlock'
  // End of Outputs for SubSystem: '<S11>/Enabled Subsystem'

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function'

  pwms_vert_idx_0_tmp = 300.0F * Simple_Joystick_CGN_B.In1.rise - 300.0F *
    Simple_Joystick_CGN_B.In1.sink;
  pwms_vert_idx_0_tmp_0 = 300.0F * Simple_Joystick_CGN_B.In1.pitch;
  Simple_Joystick_CGN_B.pwms_vert_idx_0 = (pwms_vert_idx_0_tmp + 1500.0F) -
    pwms_vert_idx_0_tmp_0;
  Simple_Joystick_CGN_B.pwms_vert_idx_1 = (-pwms_vert_idx_0_tmp + 1500.0F) -
    (-pwms_vert_idx_0_tmp_0);
  Simple_Joystick_CGN_B.pwms_vert_idx_2 = (pwms_vert_idx_0_tmp + 1500.0F) +
    pwms_vert_idx_0_tmp_0;
  pwms_vert_idx_3 = (-pwms_vert_idx_0_tmp + 1500.0F) - pwms_vert_idx_0_tmp_0;
  pwms_vert_idx_0_tmp = 300.0F * Simple_Joystick_CGN_B.In1.y;
  pwms_vert_idx_0_tmp_0 = Simple_Joystick_CGN_B.In1.x * 300.0F;
  pwms_horiz_idx_0_tmp = Simple_Joystick_CGN_B.In1.yaw * 300.0F;
  pwms_horiz_idx_0 = ((pwms_vert_idx_0_tmp + 1500.0F) + pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_1 = ((1500.0F - pwms_vert_idx_0_tmp) + pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_2 = ((pwms_vert_idx_0_tmp + 1500.0F) - pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_3 = ((1500.0F - pwms_vert_idx_0_tmp) - pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  Simple_Joystick_CGN_B.pwms_horiz = pwms_horiz_idx_0;
  if (pwms_horiz_idx_0 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    pwms_horiz_idx_0 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = Simple_Joystick_CGN_B.pwms_vert_idx_0;
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    Simple_Joystick_CGN_B.pwms_vert_idx_0 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = pwms_horiz_idx_1;
  if (pwms_horiz_idx_1 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    pwms_horiz_idx_1 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_1 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = Simple_Joystick_CGN_B.pwms_vert_idx_1;
  if (Simple_Joystick_CGN_B.pwms_vert_idx_1 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    Simple_Joystick_CGN_B.pwms_vert_idx_1 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_1 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = pwms_horiz_idx_2;
  if (pwms_horiz_idx_2 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    pwms_horiz_idx_2 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_2 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = Simple_Joystick_CGN_B.pwms_vert_idx_2;
  if (Simple_Joystick_CGN_B.pwms_vert_idx_2 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    Simple_Joystick_CGN_B.pwms_vert_idx_2 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_2 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = pwms_horiz_idx_3;
  if (pwms_horiz_idx_3 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    pwms_horiz_idx_3 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_3 = 1200.0;
  }

  Simple_Joystick_CGN_B.pwms_horiz = pwms_vert_idx_3;
  if (pwms_vert_idx_3 > 1800.0) {
    Simple_Joystick_CGN_B.pwms_horiz = 1800.0;
    pwms_vert_idx_3 = 1800.0;
  }

  if (Simple_Joystick_CGN_B.pwms_horiz < 1200.0) {
    pwms_horiz_idx_3 = 1200.0;
  }

  tmp_0 = ((&Simple_Joystick_CGN_M)->Timing.TaskCounters.TID[1] == 0);
  if (tmp_0) {
    // MATLABSystem: '<S8>/SourceBlock'
    b_varargout_1 = Sub_Simple_Joystick_CGN_73.getLatestMessage(&tmp);

    // MATLAB Function: '<S1>/MATLAB Function' incorporates:
    //   MATLABSystem: '<S8>/SourceBlock'
    //
    if (!b_varargout_1) {
      Simple_Joystick_CGN_DW.time_since_last_beat += 0.01;
    } else {
      Simple_Joystick_CGN_DW.time_since_last_beat = 0.0;
    }

    Simple_Joystick_CGN_B.manual_control_flag =
      (Simple_Joystick_CGN_DW.time_since_last_beat > 1.0);

    // End of MATLAB Function: '<S1>/MATLAB Function'
  }

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces'
  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_CGN_B.pwms_vert_idx_0);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[0] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[0] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[0] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_0);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[4] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[4] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[4] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_CGN_B.pwms_vert_idx_1);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[1] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[1] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[1] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_1);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[5] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[5] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[5] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_CGN_B.pwms_vert_idx_2);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[2] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[2] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[2] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_2);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[6] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[6] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[6] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round(pwms_vert_idx_3);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[3] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[3] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[3] = MAX_int32_T;
  }

  Simple_Joystick_CGN_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_3);
  if (Simple_Joystick_CGN_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_CGN_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      Simple_Joystick_CGN_B.pwms_vert[7] = static_cast<int32_T>
        (Simple_Joystick_CGN_B.pwms_vert_idx_0);
    } else {
      Simple_Joystick_CGN_B.pwms_vert[7] = MIN_int32_T;
    }
  } else {
    Simple_Joystick_CGN_B.pwms_vert[7] = MAX_int32_T;
  }

  // BusCreator: '<S6>/Bus Creator3'
  for (i = 0; i < 8; i++) {
    // Switch: '<Root>/Switch1' incorporates:
    //   Constant: '<Root>/Constant'

    if (Simple_Joystick_CGN_B.manual_control_flag) {
      Simple_Joystick_CGN_B.BusCreator3.pwms[i] = 1500;
    } else {
      Simple_Joystick_CGN_B.BusCreator3.pwms[i] =
        Simple_Joystick_CGN_B.pwms_vert[i];
    }

    // End of Switch: '<Root>/Switch1'
  }

  // End of BusCreator: '<S6>/Bus Creator3'

  // MATLABSystem: '<S16>/SinkBlock'
  Pub_Simple_Joystick_CGN_86_2.publish(&Simple_Joystick_CGN_B.BusCreator3);

  // MATLAB Function: '<Root>/mode_manager' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function'

  if (Simple_Joystick_CGN_B.In1.circle_button) {
    b_varargout_1 = !Simple_Joystick_CGN_DW.prior_joystick_flag;
    Simple_Joystick_CGN_DW.joystick_flag = (b_varargout_1 ||
      Simple_Joystick_CGN_DW.joystick_flag);
    Simple_Joystick_CGN_DW.joystick_flag = (b_varargout_1 &&
      Simple_Joystick_CGN_DW.joystick_flag);
  } else {
    Simple_Joystick_CGN_DW.prior_joystick_flag =
      Simple_Joystick_CGN_DW.joystick_flag;
  }

  if (Simple_Joystick_CGN_B.In1.cross_button) {
    Simple_Joystick_CGN_DW.do_mission_file_flag =
      ((!Simple_Joystick_CGN_DW.prior_do_mission_file_flag) ||
       Simple_Joystick_CGN_DW.do_mission_file_flag);
  }

  if (Simple_Joystick_CGN_B.In1.circle_button) {
    Simple_Joystick_CGN_DW.do_mission_file_flag =
      ((!Simple_Joystick_CGN_DW.prior_do_mission_file_flag) &&
       Simple_Joystick_CGN_DW.do_mission_file_flag);
  } else {
    Simple_Joystick_CGN_DW.prior_do_mission_file_flag =
      Simple_Joystick_CGN_DW.do_mission_file_flag;
  }

  // End of MATLAB Function: '<Root>/mode_manager'
  if (tmp_0) {
    // MATLABSystem: '<S15>/SinkBlock' incorporates:
    //   Constant: '<S14>/Constant'

    Pub_Simple_Joystick_CGN_85_150.publish(&Simple_Joystick_CGN_ConstP.pooled2);
  }

  rate_scheduler((&Simple_Joystick_CGN_M));
}

// Model initialize function
void Simple_Joystick_CGN::initialize()
{
  // SystemInitialize for MATLAB Function: '<S1>/MATLAB Function'
  Simple_Joystick_CGN_DW.time_since_last_beat = 2.0;

  // SystemInitialize for MATLAB Function: '<Root>/mode_manager'
  Simple_Joystick_CGN_DW.joystick_flag = true;
  Simple_Joystick_CGN_DW.prior_joystick_flag = true;

  // Start for MATLABSystem: '<S11>/SourceBlock'
  Simple_Joystick_CGN_DW.obj.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_CGN_DW.obj.matlabCodegenIsDeleted = false;
  Simple_Joystick_CGN_DW.obj.isSetupComplete = false;
  Simple_Joystick_CGN_DW.obj.isInitialized = 1;
  Simple_J_Subscriber_setupImpl_n(&Simple_Joystick_CGN_DW.obj);
  Simple_Joystick_CGN_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S8>/SourceBlock'
  Simple_Joystick_CGN_DW.obj_g.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_CGN_DW.obj_g.matlabCodegenIsDeleted = false;
  Simple_Joystick_CGN_DW.obj_g.isSetupComplete = false;
  Simple_Joystick_CGN_DW.obj_g.isInitialized = 1;
  Simple_Joy_Subscriber_setupImpl(&Simple_Joystick_CGN_DW.obj_g);
  Simple_Joystick_CGN_DW.obj_g.isSetupComplete = true;

  // Start for MATLABSystem: '<S16>/SinkBlock'
  Simple_Joystick_CGN_DW.obj_c.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_CGN_DW.obj_c.matlabCodegenIsDeleted = false;
  Simple_Joystick_CGN_DW.obj_c.isSetupComplete = false;
  Simple_Joystick_CGN_DW.obj_c.isInitialized = 1;
  Simple_Jo_Publisher_setupImpl_n(&Simple_Joystick_CGN_DW.obj_c);
  Simple_Joystick_CGN_DW.obj_c.isSetupComplete = true;

  // Start for MATLABSystem: '<S15>/SinkBlock'
  Simple_Joystick_CGN_DW.obj_gk.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_CGN_DW.obj_gk.matlabCodegenIsDeleted = false;
  Simple_Joystick_CGN_DW.obj_gk.isSetupComplete = false;
  Simple_Joystick_CGN_DW.obj_gk.isInitialized = 1;
  Simple_Joys_Publisher_setupImpl(&Simple_Joystick_CGN_DW.obj_gk);
  Simple_Joystick_CGN_DW.obj_gk.isSetupComplete = true;
}

// Model terminate function
void Simple_Joystick_CGN::terminate()
{
  // Terminate for MATLABSystem: '<S11>/SourceBlock'
  if (!Simple_Joystick_CGN_DW.obj.matlabCodegenIsDeleted) {
    Simple_Joystick_CGN_DW.obj.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_CGN_DW.obj.isInitialized == 1) &&
        Simple_Joystick_CGN_DW.obj.isSetupComplete) {
      Sub_Simple_Joystick_CGN_77.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S11>/SourceBlock'

  // Terminate for MATLABSystem: '<S8>/SourceBlock'
  if (!Simple_Joystick_CGN_DW.obj_g.matlabCodegenIsDeleted) {
    Simple_Joystick_CGN_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_CGN_DW.obj_g.isInitialized == 1) &&
        Simple_Joystick_CGN_DW.obj_g.isSetupComplete) {
      Sub_Simple_Joystick_CGN_73.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S8>/SourceBlock'

  // Terminate for MATLABSystem: '<S16>/SinkBlock'
  if (!Simple_Joystick_CGN_DW.obj_c.matlabCodegenIsDeleted) {
    Simple_Joystick_CGN_DW.obj_c.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_CGN_DW.obj_c.isInitialized == 1) &&
        Simple_Joystick_CGN_DW.obj_c.isSetupComplete) {
      Pub_Simple_Joystick_CGN_86_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S16>/SinkBlock'

  // Terminate for MATLABSystem: '<S15>/SinkBlock'
  if (!Simple_Joystick_CGN_DW.obj_gk.matlabCodegenIsDeleted) {
    Simple_Joystick_CGN_DW.obj_gk.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_CGN_DW.obj_gk.isInitialized == 1) &&
        Simple_Joystick_CGN_DW.obj_gk.isSetupComplete) {
      Pub_Simple_Joystick_CGN_85_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S15>/SinkBlock'
}

// Constructor
Simple_Joystick_CGN::Simple_Joystick_CGN() :
  Simple_Joystick_CGN_B(),
  Simple_Joystick_CGN_DW(),
  Simple_Joystick_CGN_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Simple_Joystick_CGN::~Simple_Joystick_CGN() = default;

// Real-Time Model get method
RT_MODEL_Simple_Joystick_CGN_T * Simple_Joystick_CGN::getRTM()
{
  return (&Simple_Joystick_CGN_M);
}

const char_T* RT_MODEL_Simple_Joystick_CGN_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_Simple_Joystick_CGN_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
