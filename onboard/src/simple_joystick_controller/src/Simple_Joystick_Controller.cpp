//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Simple_Joystick_Controller.cpp
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
#include "Simple_Joystick_Controller.h"
#include "Simple_Joystick_Controller_types.h"
#include <cmath>
#include "rtwtypes.h"
#include "rmw/qos_profiles.h"
#include <stddef.h>

void Simple_Joystick_Controller::Simple_Joy_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ps5_controller" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S5>/SourceBlock'
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
    // Start for MATLABSystem: '<S5>/SourceBlock'
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

  // Start for MATLABSystem: '<S9>/SinkBlock'
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
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S9>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Simple_Joystick_Controller_30_2.createPublisher(&b_zeroDelimTopic[0],
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

  // Start for MATLABSystem: '<S7>/SinkBlock'
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
    // Start for MATLABSystem: '<S7>/SinkBlock'
    Simple_Joystick_Controller_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Pub_Simple_Joystick_HIL_32_150.createPublisher
    (&Simple_Joystick_Controller_B.b_zeroDelimTopic[0], qos_profile);
}

// Model step function
void Simple_Joystick_Controller::step()
{
  SL_Bus_std_msgs_Bool rtb_BusCreator1;
  real_T pwms_horiz_idx_0;
  real_T pwms_horiz_idx_1;
  real_T pwms_horiz_idx_2;
  real_T pwms_horiz_idx_3;
  real_T pwms_vert_idx_2;
  real_T pwms_vert_idx_3;
  real32_T pwms_horiz_idx_0_tmp;
  real32_T pwms_vert_idx_0_tmp;
  real32_T pwms_vert_idx_0_tmp_0;
  boolean_T b_varargout_1;

  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = Sub_Simple_Joystick_Controller_25.getLatestMessage
    (&Simple_Joystick_Controller_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S6>/Enable'

  // Start for MATLABSystem: '<S5>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S6>/In1'
    Simple_Joystick_Controller_B.In1 =
      Simple_Joystick_Controller_B.rtb_SourceBlock_o2_m;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'

  // MATLAB Function: '<S3>/joystick_inputs_to_body_forces' incorporates:
  //   SignalConversion generated from: '<S8>/ SFunction '

  pwms_vert_idx_0_tmp = 300.0F * Simple_Joystick_Controller_B.In1.rise - 300.0F *
    Simple_Joystick_Controller_B.In1.sink;
  pwms_vert_idx_0_tmp_0 = 300.0F * Simple_Joystick_Controller_B.In1.pitch;
  Simple_Joystick_Controller_B.pwms_vert_idx_0 = (pwms_vert_idx_0_tmp + 1500.0F)
    - pwms_vert_idx_0_tmp_0;
  Simple_Joystick_Controller_B.pwms_vert_idx_1 = (-pwms_vert_idx_0_tmp + 1500.0F)
    - (-pwms_vert_idx_0_tmp_0);
  pwms_vert_idx_2 = (pwms_vert_idx_0_tmp + 1500.0F) + pwms_vert_idx_0_tmp_0;
  pwms_vert_idx_3 = (-pwms_vert_idx_0_tmp + 1500.0F) - pwms_vert_idx_0_tmp_0;
  pwms_vert_idx_0_tmp = 300.0F * Simple_Joystick_Controller_B.In1.y;
  pwms_vert_idx_0_tmp_0 = Simple_Joystick_Controller_B.In1.x * 300.0F;
  pwms_horiz_idx_0_tmp = Simple_Joystick_Controller_B.In1.yaw * 300.0F;
  pwms_horiz_idx_0 = ((pwms_vert_idx_0_tmp + 1500.0F) + pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_1 = ((1500.0F - pwms_vert_idx_0_tmp) + pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_2 = ((pwms_vert_idx_0_tmp + 1500.0F) - pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  pwms_horiz_idx_3 = ((1500.0F - pwms_vert_idx_0_tmp) - pwms_vert_idx_0_tmp_0) +
    pwms_horiz_idx_0_tmp;
  if (pwms_horiz_idx_0 > 1800.0) {
    pwms_horiz_idx_0 = 1800.0;
  }

  if (pwms_horiz_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 > 1800.0) {
    Simple_Joystick_Controller_B.pwms_vert_idx_0 = 1800.0;
  }

  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_Controller_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[0] = static_cast<int32_T>
        (Simple_Joystick_Controller_B.pwms_vert_idx_0);
    } else {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[0] = MIN_int32_T;
    }
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[0] = MAX_int32_T;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[4] = static_cast<int32_T>
      (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[4] = MAX_int32_T;
  }

  pwms_horiz_idx_0 = pwms_horiz_idx_1;
  if (pwms_horiz_idx_1 > 1800.0) {
    pwms_horiz_idx_0 = 1800.0;
  }

  if (pwms_horiz_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 =
    Simple_Joystick_Controller_B.pwms_vert_idx_1;
  if (Simple_Joystick_Controller_B.pwms_vert_idx_1 > 1800.0) {
    Simple_Joystick_Controller_B.pwms_vert_idx_0 = 1800.0;
  }

  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_Controller_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[1] = static_cast<int32_T>
        (Simple_Joystick_Controller_B.pwms_vert_idx_0);
    } else {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[1] = MIN_int32_T;
    }
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[1] = MAX_int32_T;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[5] = static_cast<int32_T>
      (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[5] = MAX_int32_T;
  }

  pwms_horiz_idx_0 = pwms_horiz_idx_2;
  if (pwms_horiz_idx_2 > 1800.0) {
    pwms_horiz_idx_0 = 1800.0;
  }

  if (pwms_horiz_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = pwms_vert_idx_2;
  if (pwms_vert_idx_2 > 1800.0) {
    Simple_Joystick_Controller_B.pwms_vert_idx_0 = 1800.0;
  }

  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_Controller_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[2] = static_cast<int32_T>
        (Simple_Joystick_Controller_B.pwms_vert_idx_0);
    } else {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[2] = MIN_int32_T;
    }
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[2] = MAX_int32_T;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[6] = static_cast<int32_T>
      (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[6] = MAX_int32_T;
  }

  pwms_horiz_idx_0 = pwms_horiz_idx_3;
  if (pwms_horiz_idx_3 > 1800.0) {
    pwms_horiz_idx_0 = 1800.0;
  }

  if (pwms_horiz_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = pwms_vert_idx_3;
  if (pwms_vert_idx_3 > 1800.0) {
    Simple_Joystick_Controller_B.pwms_vert_idx_0 = 1800.0;
  }

  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 1200.0) {
    pwms_horiz_idx_0 = 1200.0;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round
    (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    if (Simple_Joystick_Controller_B.pwms_vert_idx_0 >= -2.147483648E+9) {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[3] = static_cast<int32_T>
        (Simple_Joystick_Controller_B.pwms_vert_idx_0);
    } else {
      // BusCreator: '<S4>/Bus Creator3'
      Simple_Joystick_Controller_B.BusCreator3.pwms[3] = MIN_int32_T;
    }
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[3] = MAX_int32_T;
  }

  Simple_Joystick_Controller_B.pwms_vert_idx_0 = std::round(pwms_horiz_idx_0);
  if (Simple_Joystick_Controller_B.pwms_vert_idx_0 < 2.147483648E+9) {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[7] = static_cast<int32_T>
      (Simple_Joystick_Controller_B.pwms_vert_idx_0);
  } else {
    // BusCreator: '<S4>/Bus Creator3'
    Simple_Joystick_Controller_B.BusCreator3.pwms[7] = MAX_int32_T;
  }

  // End of MATLAB Function: '<S3>/joystick_inputs_to_body_forces'

  // MATLABSystem: '<S9>/SinkBlock'
  Pub_Simple_Joystick_Controller_30_2.publish
    (&Simple_Joystick_Controller_B.BusCreator3);

  // BusCreator: '<S2>/Bus Creator1' incorporates:
  //   Constant: '<S2>/Constant'

  rtb_BusCreator1.data = true;

  // MATLABSystem: '<S7>/SinkBlock'
  Pub_Simple_Joystick_HIL_32_150.publish(&rtb_BusCreator1);
}

// Model initialize function
void Simple_Joystick_Controller::initialize()
{
  // Start for MATLABSystem: '<S5>/SourceBlock'
  Simple_Joystick_Controller_DW.obj.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj.isInitialized = 1;
  Simple_Joy_Subscriber_setupImpl(&Simple_Joystick_Controller_DW.obj);
  Simple_Joystick_Controller_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S9>/SinkBlock'
  Simple_Joystick_Controller_DW.obj_a.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj_a.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj_a.isInitialized = 1;
  Simple_Jo_Publisher_setupImpl_m(&Simple_Joystick_Controller_DW.obj_a);
  Simple_Joystick_Controller_DW.obj_a.isSetupComplete = true;

  // Start for MATLABSystem: '<S7>/SinkBlock'
  Simple_Joystick_Controller_DW.obj_e.QOSAvoidROSNamespaceConventions = false;
  Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted = false;
  Simple_Joystick_Controller_DW.obj_e.isSetupComplete = false;
  Simple_Joystick_Controller_DW.obj_e.isInitialized = 1;
  Simple_Joys_Publisher_setupImpl(&Simple_Joystick_Controller_DW.obj_e);
  Simple_Joystick_Controller_DW.obj_e.isSetupComplete = true;
}

// Model terminate function
void Simple_Joystick_Controller::terminate()
{
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj.isSetupComplete) {
      Sub_Simple_Joystick_Controller_25.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'

  // Terminate for MATLABSystem: '<S9>/SinkBlock'
  if (!Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj_a.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj_a.isSetupComplete) {
      Pub_Simple_Joystick_Controller_30_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S9>/SinkBlock'

  // Terminate for MATLABSystem: '<S7>/SinkBlock'
  if (!Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted) {
    Simple_Joystick_Controller_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((Simple_Joystick_Controller_DW.obj_e.isInitialized == 1) &&
        Simple_Joystick_Controller_DW.obj_e.isSetupComplete) {
      Pub_Simple_Joystick_HIL_32_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S7>/SinkBlock'
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
