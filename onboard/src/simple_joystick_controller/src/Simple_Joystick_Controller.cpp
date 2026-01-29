//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_Controller.cpp
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
#include "Simple_Joystick_Controller.h"
#include "Simple_Joystick_Controller_types.h"
#include <cmath>
#include "rtwtypes.h"
#include "rmw/qos_profiles.h"
#include <stddef.h>

void Simple_Joystick_Controller::Simple_J_Subscriber_setupImpl_m(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ps5_controller" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S7>/SourceBlock'
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
    // Start for MATLABSystem: '<S7>/SourceBlock'
    Simple_Joystick_Controller_B.b_zeroDelimTopic_c[i] = b_zeroDelimTopic[i];
  }

  Sub_Simple_Joystick_Controller_25.createSubscriber
    (&Simple_Joystick_Controller_B.b_zeroDelimTopic_c[0], qos_profile);
}

void Simple_Joystick_Controller::Simple_Jo_Publisher_setupImpl_m(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S11>/SinkBlock'
  Simple_Joystick_Controller_B.deadline_k.sec = 0.0;
  Simple_Joystick_Controller_B.deadline_k.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 Simple_Joystick_Controller_B.deadline_k, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S11>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Simple_Joystick_Controller_30_2.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

void Simple_Joystick_Controller::Simple_Joy_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S1>/SourceBlock'
  Simple_Joystick_Controller_B.deadline.sec = 0.0;
  Simple_Joystick_Controller_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 Simple_Joystick_Controller_B.deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S1>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_Simple_Joystick_Controller_33.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void Simple_Joystick_Controller::Simple_Joys_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S10>/SinkBlock'
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
    // Start for MATLABSystem: '<S10>/SinkBlock'
    Simple_Joystick_Controller_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Pub_Simple_Joystick_Controller_32_2.createPublisher
    (&Simple_Joystick_Controller_B.b_zeroDelimTopic[0], qos_profile);
}

// Model step function
void Simple_Joystick_Controller::step()
{
  SL_Bus_std_msgs_Bool rtb_BusCreator1;
  int64_T tmp_0;
  int32_T q1;
  int32_T qY;
  int32_T qY_0;
  int32_T qY_1;
  int32_T qY_2;
  int32_T qY_3;
  int32_T qY_4;
  int32_T qY_5;
  int32_T qY_6;
  real32_T tmp;
  boolean_T b_varargout_1;

  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_Simple_Joystick_Controller_25.getLatestMessage
    (&Simple_Joystick_Controller_B.rtb_SourceBlock_o2_g_m);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  // Start for MATLABSystem: '<S7>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    Simple_Joystick_Controller_B.In1 =
      Simple_Joystick_Controller_B.rtb_SourceBlock_o2_g_m;
  }

  // End of Start for MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces1' incorporates:
  //   SignalConversion generated from: '<S9>/ SFunction '

  tmp = std::round(300.0F * Simple_Joystick_Controller_B.In1.rise - 300.0F *
                   Simple_Joystick_Controller_B.In1.sink);
  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      tmp_0 = -static_cast<int64_T>(static_cast<int32_T>(tmp));
      qY_2 = static_cast<int32_T>(tmp);
    } else {
      tmp_0 = 2147483648L;
      qY_2 = MIN_int32_T;
    }
  } else {
    tmp_0 = -2147483647L;
    qY_2 = MAX_int32_T;
  }

  if (-static_cast<int64_T>(qY_2) > 2147483647L) {
    tmp_0 = 2147483647L;
  }

  if (static_cast<int32_T>(tmp_0) > 2147482147) {
    qY_6 = MAX_int32_T;
  } else {
    qY_6 = static_cast<int32_T>(tmp_0) + 1500;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      tmp_0 = static_cast<int32_T>(tmp);
    } else {
      tmp_0 = -2147483648L;
    }
  } else {
    tmp_0 = 2147483647L;
  }

  if (static_cast<int32_T>(tmp_0) > 2147482147) {
    qY_5 = MAX_int32_T;
  } else {
    qY_5 = static_cast<int32_T>(tmp_0) + 1500;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      tmp_0 = -static_cast<int64_T>(static_cast<int32_T>(tmp));
      qY_2 = static_cast<int32_T>(tmp);
    } else {
      tmp_0 = 2147483648L;
      qY_2 = MIN_int32_T;
    }
  } else {
    tmp_0 = -2147483647L;
    qY_2 = MAX_int32_T;
  }

  if (-static_cast<int64_T>(qY_2) > 2147483647L) {
    tmp_0 = 2147483647L;
  }

  if (static_cast<int32_T>(tmp_0) > 2147482147) {
    qY_4 = MAX_int32_T;
  } else {
    qY_4 = static_cast<int32_T>(tmp_0) + 1500;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      tmp_0 = static_cast<int32_T>(tmp);
    } else {
      tmp_0 = -2147483648L;
    }
  } else {
    tmp_0 = 2147483647L;
  }

  if (static_cast<int32_T>(tmp_0) > 2147482147) {
    qY_3 = MAX_int32_T;
  } else {
    qY_3 = static_cast<int32_T>(tmp_0) + 1500;
  }

  tmp = std::round(300.0F * Simple_Joystick_Controller_B.In1.pitch);
  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      tmp_0 = -static_cast<int64_T>(static_cast<int32_T>(tmp));
      qY_2 = static_cast<int32_T>(tmp);
    } else {
      tmp_0 = 2147483648L;
      qY_2 = MIN_int32_T;
    }
  } else {
    tmp_0 = -2147483647L;
    qY_2 = MAX_int32_T;
  }

  if (-static_cast<int64_T>(qY_2) > 2147483647L) {
    tmp_0 = 2147483647L;
  }

  if ((qY_6 < 0) && (static_cast<int32_T>(tmp_0) < MIN_int32_T - qY_6)) {
    qY_6 = MIN_int32_T;
  } else if ((qY_6 > 0) && (static_cast<int32_T>(tmp_0) > MAX_int32_T - qY_6)) {
    qY_6 = MAX_int32_T;
  } else {
    qY_6 += static_cast<int32_T>(tmp_0);
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
      tmp_0 = -static_cast<int64_T>(static_cast<int32_T>(tmp));
      qY_2 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
      tmp_0 = 2147483648L;
      qY_2 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
    tmp_0 = -2147483647L;
    qY_2 = MAX_int32_T;
  }

  if ((qY_5 >= 0) && (q1 < qY_5 - MAX_int32_T)) {
    qY_5 = MAX_int32_T;
  } else if ((qY_5 < 0) && (q1 > qY_5 - MIN_int32_T)) {
    qY_5 = MIN_int32_T;
  } else {
    qY_5 -= q1;
  }

  if (-static_cast<int64_T>(qY_2) > 2147483647L) {
    tmp_0 = 2147483647L;
  }

  if ((qY_4 >= 0) && (static_cast<int32_T>(tmp_0) < qY_4 - MAX_int32_T)) {
    qY_4 = MAX_int32_T;
  } else if ((qY_4 < 0) && (static_cast<int32_T>(tmp_0) > qY_4 - MIN_int32_T)) {
    qY_4 = MIN_int32_T;
  } else {
    qY_4 -= static_cast<int32_T>(tmp_0);
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_3 < 0) && (q1 < MIN_int32_T - qY_3)) {
    qY_3 = MIN_int32_T;
  } else if ((qY_3 > 0) && (q1 > MAX_int32_T - qY_3)) {
    qY_3 = MAX_int32_T;
  } else {
    qY_3 += q1;
  }

  tmp = std::round(300.0F * Simple_Joystick_Controller_B.In1.y);
  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if (q1 > 2147482147) {
    qY_2 = MAX_int32_T;
  } else {
    qY_2 = q1 + 1500;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if (q1 < -2147482147) {
    qY_1 = MAX_int32_T;
  } else {
    qY_1 = 1500 - q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if (q1 > 2147482147) {
    qY_0 = MAX_int32_T;
  } else {
    qY_0 = q1 + 1500;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if (q1 < -2147482147) {
    qY = MAX_int32_T;
  } else {
    qY = 1500 - q1;
  }

  tmp = std::round(Simple_Joystick_Controller_B.In1.x * 300.0F);
  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_2 < 0) && (q1 < MIN_int32_T - qY_2)) {
    qY_2 = MIN_int32_T;
  } else if ((qY_2 > 0) && (q1 > MAX_int32_T - qY_2)) {
    qY_2 = MAX_int32_T;
  } else {
    qY_2 += q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_1 < 0) && (q1 < MIN_int32_T - qY_1)) {
    qY_1 = MIN_int32_T;
  } else if ((qY_1 > 0) && (q1 > MAX_int32_T - qY_1)) {
    qY_1 = MAX_int32_T;
  } else {
    qY_1 += q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_0 >= 0) && (q1 < qY_0 - MAX_int32_T)) {
    qY_0 = MAX_int32_T;
  } else if ((qY_0 < 0) && (q1 > qY_0 - MIN_int32_T)) {
    qY_0 = MIN_int32_T;
  } else {
    qY_0 -= q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY >= 0) && (q1 < qY - MAX_int32_T)) {
    qY = MAX_int32_T;
  } else if ((qY < 0) && (q1 > qY - MIN_int32_T)) {
    qY = MIN_int32_T;
  } else {
    qY -= q1;
  }

  tmp = std::round(Simple_Joystick_Controller_B.In1.yaw * 300.0F);
  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_2 < 0) && (q1 < MIN_int32_T - qY_2)) {
    qY_2 = MIN_int32_T;
  } else if ((qY_2 > 0) && (q1 > MAX_int32_T - qY_2)) {
    qY_2 = MAX_int32_T;
  } else {
    qY_2 += q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_1 < 0) && (q1 < MIN_int32_T - qY_1)) {
    qY_1 = MIN_int32_T;
  } else if ((qY_1 > 0) && (q1 > MAX_int32_T - qY_1)) {
    qY_1 = MAX_int32_T;
  } else {
    qY_1 += q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY_0 < 0) && (q1 < MIN_int32_T - qY_0)) {
    qY_0 = MIN_int32_T;
  } else if ((qY_0 > 0) && (q1 > MAX_int32_T - qY_0)) {
    qY_0 = MAX_int32_T;
  } else {
    qY_0 += q1;
  }

  if (tmp < 2.14748365E+9F) {
    if (tmp >= -2.14748365E+9F) {
      q1 = static_cast<int32_T>(tmp);
    } else {
      q1 = MIN_int32_T;
    }
  } else {
    q1 = MAX_int32_T;
  }

  if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
    qY = MIN_int32_T;
  } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
    qY = MAX_int32_T;
  } else {
    qY += q1;
  }

  if (qY_2 > 1800) {
    qY_2 = 1800;
  }

  if (qY_2 < 1200) {
    qY_2 = 1200;
  }

  if (qY_6 > 1800) {
    qY_6 = 1800;
  }

  if (qY_6 < 1200) {
    qY_2 = 1200;
  }

  // BusCreator: '<S5>/Bus Creator3' incorporates:
  //   MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'

  Simple_Joystick_Controller_B.BusCreator3.pwms[0] = qY_6;
  Simple_Joystick_Controller_B.BusCreator3.pwms[4] = qY_2;

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'
  qY_2 = qY_1;
  if (qY_1 > 1800) {
    qY_2 = 1800;
  }

  if (qY_2 < 1200) {
    qY_2 = 1200;
  }

  qY_6 = qY_5;
  if (qY_5 > 1800) {
    qY_6 = 1800;
  }

  if (qY_6 < 1200) {
    qY_2 = 1200;
  }

  // BusCreator: '<S5>/Bus Creator3' incorporates:
  //   MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'

  Simple_Joystick_Controller_B.BusCreator3.pwms[1] = qY_6;
  Simple_Joystick_Controller_B.BusCreator3.pwms[5] = qY_2;

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'
  qY_2 = qY_0;
  if (qY_0 > 1800) {
    qY_2 = 1800;
  }

  if (qY_2 < 1200) {
    qY_2 = 1200;
  }

  qY_6 = qY_4;
  if (qY_4 > 1800) {
    qY_6 = 1800;
  }

  if (qY_6 < 1200) {
    qY_2 = 1200;
  }

  // BusCreator: '<S5>/Bus Creator3' incorporates:
  //   MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'

  Simple_Joystick_Controller_B.BusCreator3.pwms[2] = qY_6;
  Simple_Joystick_Controller_B.BusCreator3.pwms[6] = qY_2;

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'
  qY_2 = qY;
  if (qY > 1800) {
    qY_2 = 1800;
  }

  if (qY_2 < 1200) {
    qY_2 = 1200;
  }

  qY_6 = qY_3;
  if (qY_3 > 1800) {
    qY_6 = 1800;
  }

  if (qY_6 < 1200) {
    qY_2 = 1200;
  }

  // BusCreator: '<S5>/Bus Creator3' incorporates:
  //   MATLAB Function: '<S3>/joystick_inputs_to_body_forces1'

  Simple_Joystick_Controller_B.BusCreator3.pwms[3] = qY_6;
  Simple_Joystick_Controller_B.BusCreator3.pwms[7] = qY_2;

  // MATLABSystem: '<S11>/SinkBlock'
  Pub_Simple_Joystick_Controller_30_2.publish
    (&Simple_Joystick_Controller_B.BusCreator3);

  // MATLABSystem: '<S1>/SourceBlock'
  Sub_Simple_Joystick_Controller_33.getLatestMessage
    (&Simple_Joystick_Controller_B.r);

  // BusCreator: '<S4>/Bus Creator1' incorporates:
  //   Constant: '<S3>/heartbeat'

  rtb_BusCreator1.data = true;

  // MATLABSystem: '<S10>/SinkBlock'
  Pub_Simple_Joystick_Controller_32_2.publish(&rtb_BusCreator1);
}

// Model initialize function
void Simple_Joystick_Controller::initialize()
{
  // Start for MATLABSystem: '<S7>/SourceBlock'
  Simple_Joystick_Controller_DW.obj.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj.isInitialized = 1;
  Simple_J_Subscriber_setupImpl_m(&Simple_Joystick_Controller_DW.obj);
  Simple_Joystick_Controller_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S11>/SinkBlock'
  Simple_Joystick_Controller_DW.obj_a.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj_a.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj_a.isInitialized = 1;
  Simple_Jo_Publisher_setupImpl_m(&Simple_Joystick_Controller_DW.obj_a);
  Simple_Joystick_Controller_DW.obj_a.isSetupComplete = true;

  // Start for MATLABSystem: '<S1>/SourceBlock'
  Simple_Joystick_Controller_DW.obj_e.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj_e.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj_e.isInitialized = 1;
  Simple_Joy_Subscriber_setupImpl(&Simple_Joystick_Controller_DW.obj_e);
  Simple_Joystick_Controller_DW.obj_e.isSetupComplete = true;

  // Start for MATLABSystem: '<S10>/SinkBlock'
  Simple_Joystick_Controller_DW.obj_l.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj_l.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj_l.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj_l.isInitialized = 1;
  Simple_Joys_Publisher_setupImpl(&Simple_Joystick_Controller_DW.obj_l);
  Simple_Joystick_Controller_DW.obj_l.isSetupComplete = true;
}

// Model terminate function
void Simple_Joystick_Controller::terminate()
{
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj.isSetupComplete) {
      Sub_Simple_Joystick_Controller_25.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'

  // Terminate for MATLABSystem: '<S11>/SinkBlock'
  if (!Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj_a.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj_a.isSetupComplete) {
      Pub_Simple_Joystick_Controller_30_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S11>/SinkBlock'

  // Terminate for MATLABSystem: '<S1>/SourceBlock'
  if (!Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj_e.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj_e.isSetupComplete) {
      Sub_Simple_Joystick_Controller_33.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SourceBlock'

  // Terminate for MATLABSystem: '<S10>/SinkBlock'
  if (!Simple_Joystick_Controller_DW.obj_l.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj_l.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj_l.isSetupComplete) {
      Pub_Simple_Joystick_Controller_32_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S10>/SinkBlock'
}

// Constructor
Simple_Joystick_Controller::Simple_Joystick_Controller() :
  Simple_Joystick_Controller_B(),
  Simple_Joystick_Controller_DW(),
  Simple_Joystick_Controller_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Simple_Joystick_Controller::~Simple_Joystick_Controller() = default;

// Real-Time Model get method
RT_MODEL_Simple_Joystick_Cont_T * Simple_Joystick_Controller::getRTM()
{
  return (&Simple_Joystick_Controller_M);
}

const char_T* RT_MODEL_Simple_Joystick_Cont_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_Simple_Joystick_Cont_T::setErrorStatus(const char_T* const
  volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
