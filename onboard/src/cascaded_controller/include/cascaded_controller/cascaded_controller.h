//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cascaded_controller.h
//
// Code generated for Simulink model 'cascaded_controller'.
//
// Model version                  : 1.5
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Jul  2 21:06:21 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef cascaded_controller_h_
#define cascaded_controller_h_
#include <cmath>
#include <cstdio>
#include <cstring>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "slros2_initialize.h"
#include "cascaded_controller_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Block signals (default storage)
struct B_cascaded_controller_T {
  SL_Bus_custom_interfaces_VR In1;     // '<S12>/In1'
  SL_Bus_custom_interfaces_VR rtb_SourceBlock_o2_m;
  SL_Bus_custom_interfaces_Imu In1_k;  // '<S11>/In1'
  SL_Bus_custom_interfaces_Imu rtb_SourceBlock_o2_k_c;
  real_T force_column_data[201];
  real_T b_varargin_1_data[201];
  real_T b_x_data[201];
  X_bus X_est;                         // '<S9>/derivedStateEstimates'
  cmd_bus cmd;                         // '<S5>/cmdMsgToCmdBus'
  cell_wrap_1_cascaded_controll_T varargin_1[13];
  cell_wrap_1_cascaded_controll_T varargin_2[13];
  cell_wrap_1_cascaded_controll_T varargin_3[13];
  SL_Bus_custom_interfaces_Goal In1_n; // '<S200>/In1'
  SL_Bus_custom_interfaces_Goal rtb_SourceBlock_o2_p_k;
  real_T c_a[16];
  real_T X_u[13];                      // '<S14>/commandExecuter'
  real_T Qe1[12];
  real_T rotm[9];
  real_T Cbi[9];
  real_T Cbi_c[9];                     // '<S9>/Transpose'
  real_T rtb_Cbi_tmp[9];
  real_T rtb_Cbi_tmp_b[9];
  real_T rtb_Cbi_tmp_tmp[9];
  real_T Cbi_p[9];
  real_T a[9];
  real_T b_a[9];
  SL_Bus_custom_interfaces_DRR In1_a;  // '<S10>/In1'
  real_T pwms[8];
  real_T FT_cmd_list[8];               // '<S13>/thrusterAllocator'
  real_T dv[8];
  SL_Bus_custom_interfaces_DRR rtb_SourceBlock_o2_g_c;
  real_T varargin_1_f[6];
  int32_T Cast[8];                     // '<S13>/Cast'
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S7>/Bus Creator3'
  real_T qinv[4];
  real_T qe_matlab[4];
  real_T dv1[4];
  real_T DiscreteTransferFcn[4];
  real_T dv2[4];
  real_T eps[3];
  real_T R_error[3];
  real_T eul_error[3];
  real_T eps_g[3];
  real_T dRb_u[3];                     // '<S13>/dRbSetpointInjector'
  real_T dRb_e[3];                     // '<S13>/rateInjector'
  real_T dv3[3];
  real_T rtb_dvl_pos_g[3];
  real_T dv4[3];
  real_T x[3];
  real_T x_m[3];
  real_T x_n[3];
  char_T b_zeroDelimTopic[18];
  SL_Bus_custom_interfaces_Result result_msg;// '<S5>/statusKwdToBool'
  char_T varargin_2_p[17];
  char_T varargin_3_l[17];
  char_T b_zeroDelimTopic_j[17];
  char_T switch_expression[16];
  char_T x1[16];
  cell_wrap_1_cascaded_controll_T b;
  cell_wrap_1_cascaded_controll_T c;
  cell_wrap_1_cascaded_controll_T d;
  cell_wrap_1_cascaded_controll_T e;
  cell_wrap_1_cascaded_controll_T f;
  cell_wrap_1_cascaded_controll_T g;
  cell_wrap_1_cascaded_controll_T h;
  cell_wrap_1_cascaded_controll_T i;
  cell_wrap_1_cascaded_controll_T j;
  cell_wrap_1_cascaded_controll_T k;
  cell_wrap_1_cascaded_controll_T l;
  cell_wrap_1_cascaded_controll_T m;
  cell_wrap_1_cascaded_controll_T n;
  cell_wrap_1_cascaded_controll_T o;
  cell_wrap_1_cascaded_controll_T p;
  cell_wrap_1_cascaded_controll_T q;
  cell_wrap_1_cascaded_controll_T r;
  cell_wrap_1_cascaded_controll_T s;
  cell_wrap_1_cascaded_controll_T u;
  cell_wrap_1_cascaded_controll_T v;
  cell_wrap_1_cascaded_controll_T w;
  cell_wrap_1_cascaded_controll_T x_d;
  cell_wrap_1_cascaded_controll_T y;
  cell_wrap_1_cascaded_controll_T ab;
  cell_wrap_1_cascaded_controll_T bb;
  cell_wrap_1_cascaded_controll_T cb;
  char_T switch_expression_g[16];
  char_T b_zeroDelimTopic_l[16];
  char_T b_zeroDelimTopic_d[16];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF deadline_d;
  sJ4ih70VmKcvCeguWN0mNVF deadline_l;
  real_T Ri_xy_e[2];
  real_T eta;
  real_T scale;
  real_T absxk;
  real_T b_t;
  real_T b_scale;
  real_T b_absxk;
  real_T a_o;
  real_T theta;
  real_T phi;
  real_T psi;
  real_T phi_b;
  real_T lower_voltage_index;
  real_T upper_voltage_index;
  real_T lower_force_index;
  real_T DigitalClock;                 // '<S14>/Digital Clock'
  real_T rotm_tmp;
  real_T rtb_delta_qe_idx_2;
  real_T qe_matlab_idx_3;
  real_T rtb_IntegralGain_c_idx_0;
  real_T rtb_Integrator_o_idx_1;
  real_T rtb_IntegralGain_c_idx_1;
  real_T rtb_Integrator_o_idx_2;
  real_T DiscreteTransferFcn_tmp_idx_2;
  real_T rtb_Filter_l_idx_0;
  real_T force_column_tmp;
  real_T eta_n;
  real_T scale_b;
  real_T absxk_l;
  real_T b_t_h;
  real_T rotm_tmp_b;
  real_T rotm_tmp_d;
  real_T eps_idx_0;
  real_T eps_idx_1;
  real_T eps_idx_2;
  real_T rotm_idx_0;
  real_T rotm_idx_8;
  real_T rotm_idx_4_tmp;
  real_T a_e;
  real_T b_a_b;
  real_T a_tmp;
  real_T varargin_1_data;
  real_T q_j;
  real_T eta_f;
  real_T scale_a;
  real_T absxk_j;
  real_T b_t_j;
  real_T rotm_tmp_o;
  real_T rotm_tmp_n;
  real_T eps_idx_0_i;
  real_T eps_idx_1_o;
  real_T eps_idx_2_n;
  real_T rotm_idx_0_m;
  real_T rotm_idx_8_c;
  real_T eta_m;
  real_T y_m;
  real_T scale_j;
  real_T absxk_h;
  real_T b_t_c;
  real_T eps_idx_0_c;
  real_T eps_idx_1_p;
  real_T rotm_tmp_p;
  real_T rotm_tmp_a;
  real_T rotm_tmp_e;
  real_T scale_ax;
  boolean_T b_x[6];
  int32_T iindx;
};

// Block states (default storage) for system '<Root>'
struct DW_cascaded_controller_T {
  ros_slros2_internal_block_Sub_T obj; // '<S196>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_e;// '<S3>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_e3;// '<S2>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_d;// '<S1>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_f;// '<S204>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o;// '<S203>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_i;// '<S201>/SinkBlock'
  real_T UnitDelay_DSTATE;             // '<S4>/Unit Delay'
  real_T UnitDelay1_DSTATE;            // '<S4>/Unit Delay1'
  real_T PositionIntegrator_DSTATE[3]; // '<S9>/Position Integrator'
  real_T VelocityIntegrator_DSTATE[3]; // '<S9>/Velocity Integrator'
  real_T DelayInput1_DSTATE;           // '<S16>/Delay Input1'
  real_T DiscreteTimeIntegrator_DSTATE[4];// '<S18>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn_states[4];// '<S13>/Discrete Transfer Fcn'
  real_T Integrator_DSTATE[3];         // '<S121>/Integrator'
  real_T Filter_DSTATE[3];             // '<S116>/Filter'
  real_T Integrator_DSTATE_f[3];       // '<S66>/Integrator'
  real_T Filter_DSTATE_l[3];           // '<S61>/Filter'
  real_T Integrator_DSTATE_l[3];       // '<S176>/Integrator'
  real_T Filter_DSTATE_k[3];           // '<S171>/Filter'
  real_T offset[3];                    // '<S9>/dvl_reset'
  real_T qk[4];                        // '<S9>/discreteTimeQuatPropagation'
  real_T hold_timer_start_time;        // '<S14>/commandExecuter'
  real_T idle_wp[6];                   // '<S14>/commandExecuter'
  real_T cmd_specific_wp[6];           // '<S14>/commandExecuter'
  real_T prior_action_id;              // '<S14>/commandExecuter'
  real_T qib[4];                       // '<S13>/Data Store Memory2'
  real_T dRi[3];                       // '<S13>/Data Store Memory4'
  real_T wb[3];                        // '<S13>/Data Store Memory5'
  int8_T UnitDelay_DSTATE_k[4];        // '<S5>/Unit Delay'
  int8_T PositionIntegrator_PrevResetSta;// '<S9>/Position Integrator'
  int8_T VelocityIntegrator_PrevResetSta;// '<S9>/Velocity Integrator'
  int8_T DiscreteTimeIntegrator_PrevRese;// '<S18>/Discrete-Time Integrator'
  int8_T Integrator_PrevResetState;    // '<S121>/Integrator'
  int8_T Filter_PrevResetState;        // '<S116>/Filter'
  int8_T Integrator_PrevResetState_h;  // '<S66>/Integrator'
  int8_T Filter_PrevResetState_e;      // '<S61>/Filter'
  int8_T Integrator_PrevResetState_d;  // '<S176>/Integrator'
  int8_T Filter_PrevResetState_a;      // '<S171>/Filter'
  uint8_T PositionIntegrator_IC_LOADING;// '<S9>/Position Integrator'
  uint8_T VelocityIntegrator_IC_LOADING;// '<S9>/Velocity Integrator'
  boolean_T start_new_mission_flag;    // '<Root>/Data Store Memory'
  boolean_T start_new_cmd_flag;        // '<Root>/Data Store Memory1'
  boolean_T prior_flag;                // '<S9>/dvl_reset'
  boolean_T qk_not_empty;              // '<S9>/discreteTimeQuatPropagation'
  boolean_T start_new_mission_flag_a;  // '<S5>/MATLAB Function'
  boolean_T hold_timer_start_time_not_empty;// '<S14>/commandExecuter'
  boolean_T idle_wp_not_empty;         // '<S14>/commandExecuter'
  boolean_T cmd_specific_wp_not_empty; // '<S14>/commandExecuter'
  boolean_T prior_action_id_not_empty; // '<S13>/guidanceLaw'
};

// Constant parameters (default storage)
struct ConstP_cascaded_controller_T {
  // Expression: FF_maneuvers
  //  Referenced by: '<S13>/trickFTListInjector'

  FF_maneuvers_bus trickFTListInjector_FF_maneuver;

  // Computed Parameter: Constant_Value
  //  Referenced by: '<S202>/Constant'

  SL_Bus_std_msgs_Empty Constant_Value;

  // Expression: ccw_force
  //  Referenced by: '<S19>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_force[1206];

  // Expression: ccw_pwm
  //  Referenced by: '<S19>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_pwm[201];

  // Expression: cw_force
  //  Referenced by: '<S19>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_force[1206];

  // Expression: cw_pwm
  //  Referenced by: '<S19>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_pwm[201];

  // Expression: voltage
  //  Referenced by: '<S19>/forceToPWMCalculator'

  real_T forceToPWMCalculator_voltage[6];

  // Expression: invMT_wrench
  //  Referenced by: '<S13>/Constant'

  real_T Constant_Value_n[24];

  // Expression: invFT_wrench
  //  Referenced by: '<S13>/Constant1'

  real_T Constant1_Value[24];

  // Expression: qib_PID.Kp
  //  Referenced by: '<S13>/Gain1'

  real_T Gain1_Gain[4];

  // Expression: P
  //  Referenced by: '<S126>/Proportional Gain'

  real_T ProportionalGain_Gain[3];

  // Expression: gi
  //  Referenced by: '<S9>/Constant'

  real_T Constant_Value_m[3];

  // Expression: Cbimu_meas
  //  Referenced by: '<S9>/Constant1'

  real_T Constant1_Value_l[9];
};

// Real-time Model Data Structure
struct tag_RTM_cascaded_controller_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;

  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Constant parameters (default storage)
extern const ConstP_cascaded_controller_T cascaded_controller_ConstP;

// Class declaration for model cascaded_controller
class cascaded_controller final
{
  // public data and function members
 public:
  // Copy Constructor
  cascaded_controller(cascaded_controller const&) = delete;

  // Assignment Operator
  cascaded_controller& operator= (cascaded_controller const&) & = delete;

  // Move Constructor
  cascaded_controller(cascaded_controller &&) = delete;

  // Move Assignment Operator
  cascaded_controller& operator= (cascaded_controller &&) = delete;

  // Real-Time Model get method
  RT_MODEL_cascaded_controller_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  cascaded_controller();

  // Destructor
  ~cascaded_controller();

  // private data and function members
 private:
  // Block signals
  B_cascaded_controller_T cascaded_controller_B;

  // Block states
  DW_cascaded_controller_T cascaded_controller_DW;

  // private member function(s) for subsystem '<Root>'
  void cascaded_controller_wrapToPi(real_T *lambda);
  void cascaded_controller_eulToQuat_m(const real_T Eul[3], real_T qib[4]);
  void cascaded_c_executeDurationTrick(real_T cmd_hold_time, const int8_T
    cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
    real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
    real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
    cmd_status[4], real_T *hold_timer, real_T X_u[13]);
  real_T cascaded_controller_norm(const real_T x[2]);
  void cascaded_controller_quatToEul(const real_T qib[4], real_T Eul[3]);
  void cascaded_controller_eulToRotm(const real_T Eul[3], real_T rotm[9]);
  void cascaded_controller_rotmToQuat(const real_T rotm[9], real_T qib[4]);
  void cascaded_controller_eulToQuat(const real_T Eul[3], real_T qib[4]);
  boolean_T cascaded_controller_isequal(const char_T varargin_1[16]);
  boolean_T cascaded_controller_strcmp(const char_T b[16]);
  boolean_T cascaded_controller_strcmp_a(const char_T b[16]);
  boolean_T cascaded_controller_strcmp_ax(const char_T b[16]);
  void cascaded_controller_minimum(const real_T x[6], real_T *ex, int32_T *idx);
  void cascaded_controller_minimum_c(const real_T x_data[], const int32_T
    *x_size, real_T *ex, int32_T *idx);
  void cascaded_co_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  void cascad_Subscriber_setupImpl_dsx(const ros_slros2_internal_block_Sub_T
    *obj);
  void cascaded_Subscriber_setupImpl_d(const ros_slros2_internal_block_Sub_T
    *obj);
  void cascade_Subscriber_setupImpl_ds(const ros_slros2_internal_block_Sub_T
    *obj);
  void cascaded_c_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void cascaded_Publisher_setupImpl_ds(const ros_slros2_internal_block_Pub_T
    *obj);
  void cascaded__Publisher_setupImpl_d(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_cascaded_controller_T cascaded_controller_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S13>/Gain' : Eliminated nontunable gain of 1
//  Block '<S13>/Gain3' : Eliminated nontunable gain of 1
//  Block '<S13>/Gain4' : Eliminated nontunable gain of 1


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
//  '<Root>' : 'cascaded_controller'
//  '<S1>'   : 'cascaded_controller/DRR'
//  '<S2>'   : 'cascaded_controller/IMU'
//  '<S3>'   : 'cascaded_controller/VR'
//  '<S4>'   : 'cascaded_controller/low_level_controller_cgn'
//  '<S5>'   : 'cascaded_controller/mission_manager_interface_cgn'
//  '<S6>'   : 'cascaded_controller/pwm_heartbeat_publisher'
//  '<S7>'   : 'cascaded_controller/pwm_publisher'
//  '<S8>'   : 'cascaded_controller/sensorRosMsgToBus'
//  '<S9>'   : 'cascaded_controller/state_estimator_cgn'
//  '<S10>'  : 'cascaded_controller/DRR/Enabled Subsystem'
//  '<S11>'  : 'cascaded_controller/IMU/Enabled Subsystem'
//  '<S12>'  : 'cascaded_controller/VR/Enabled Subsystem'
//  '<S13>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn'
//  '<S14>'  : 'cascaded_controller/low_level_controller_cgn/execute_command_cgn'
//  '<S15>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller'
//  '<S16>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Detect Change'
//  '<S17>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb'
//  '<S18>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem'
//  '<S19>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem Reference1'
//  '<S20>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller'
//  '<S21>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRbSetpointInjector'
//  '<S22>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/deltaQuatError'
//  '<S23>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/guidanceLaw'
//  '<S24>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/quatInjector'
//  '<S25>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/quatPID'
//  '<S26>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/quatToRotm'
//  '<S27>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/rateInjector'
//  '<S28>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/thrusterAllocator'
//  '<S29>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/trickFTListInjector'
//  '<S30>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup'
//  '<S31>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/D Gain'
//  '<S32>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/External Derivative'
//  '<S33>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter'
//  '<S34>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter ICs'
//  '<S35>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/I Gain'
//  '<S36>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain'
//  '<S37>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain Fdbk'
//  '<S38>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator'
//  '<S39>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator ICs'
//  '<S40>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Copy'
//  '<S41>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Gain'
//  '<S42>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/P Copy'
//  '<S43>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Parallel P Gain'
//  '<S44>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Reset Signal'
//  '<S45>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation'
//  '<S46>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation Fdbk'
//  '<S47>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum'
//  '<S48>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum Fdbk'
//  '<S49>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode'
//  '<S50>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode Sum'
//  '<S51>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Integral'
//  '<S52>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Ngain'
//  '<S53>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/postSat Signal'
//  '<S54>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preInt Signal'
//  '<S55>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preSat Signal'
//  '<S56>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S57>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S58>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S59>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/D Gain/Internal Parameters'
//  '<S60>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/External Derivative/Error'
//  '<S61>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter/Disc. Forward Euler Filter'
//  '<S62>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter ICs/Internal IC - Filter'
//  '<S63>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/I Gain/Internal Parameters'
//  '<S64>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain/Passthrough'
//  '<S65>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain Fdbk/Disabled'
//  '<S66>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator/Discrete'
//  '<S67>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator ICs/Internal IC'
//  '<S68>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Copy/Disabled'
//  '<S69>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Gain/Internal Parameters'
//  '<S70>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/P Copy/Disabled'
//  '<S71>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Parallel P Gain/Internal Parameters'
//  '<S72>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Reset Signal/External Reset'
//  '<S73>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation/Enabled'
//  '<S74>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation Fdbk/Disabled'
//  '<S75>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum/Sum_PID'
//  '<S76>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum Fdbk/Disabled'
//  '<S77>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode/Disabled'
//  '<S78>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode Sum/Passthrough'
//  '<S79>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S80>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Ngain/Passthrough'
//  '<S81>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/postSat Signal/Forward_Path'
//  '<S82>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preInt Signal/Internal PreInt'
//  '<S83>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preSat Signal/Forward_Path'
//  '<S84>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller'
//  '<S85>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup'
//  '<S86>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/D Gain'
//  '<S87>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/External Derivative'
//  '<S88>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter'
//  '<S89>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter ICs'
//  '<S90>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/I Gain'
//  '<S91>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain'
//  '<S92>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain Fdbk'
//  '<S93>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator'
//  '<S94>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator ICs'
//  '<S95>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Copy'
//  '<S96>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Gain'
//  '<S97>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/P Copy'
//  '<S98>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Parallel P Gain'
//  '<S99>'  : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Reset Signal'
//  '<S100>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation'
//  '<S101>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation Fdbk'
//  '<S102>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum'
//  '<S103>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum Fdbk'
//  '<S104>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode'
//  '<S105>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode Sum'
//  '<S106>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Integral'
//  '<S107>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Ngain'
//  '<S108>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/postSat Signal'
//  '<S109>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preInt Signal'
//  '<S110>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preSat Signal'
//  '<S111>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S112>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S113>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S114>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/D Gain/Internal Parameters'
//  '<S115>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/External Derivative/Error'
//  '<S116>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S117>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S118>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/I Gain/Internal Parameters'
//  '<S119>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain/Passthrough'
//  '<S120>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S121>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator/Discrete'
//  '<S122>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator ICs/Internal IC'
//  '<S123>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Copy/Disabled'
//  '<S124>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Gain/Internal Parameters'
//  '<S125>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/P Copy/Disabled'
//  '<S126>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S127>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Reset Signal/External Reset'
//  '<S128>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation/Enabled'
//  '<S129>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation Fdbk/Disabled'
//  '<S130>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum/Sum_PID'
//  '<S131>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum Fdbk/Disabled'
//  '<S132>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode/Disabled'
//  '<S133>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S134>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S135>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S136>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/postSat Signal/Forward_Path'
//  '<S137>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preInt Signal/Internal PreInt'
//  '<S138>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preSat Signal/Forward_Path'
//  '<S139>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem Reference1/forceToPWMCalculator'
//  '<S140>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup'
//  '<S141>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/D Gain'
//  '<S142>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/External Derivative'
//  '<S143>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter'
//  '<S144>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter ICs'
//  '<S145>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/I Gain'
//  '<S146>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain'
//  '<S147>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain Fdbk'
//  '<S148>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator'
//  '<S149>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator ICs'
//  '<S150>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Copy'
//  '<S151>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Gain'
//  '<S152>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/P Copy'
//  '<S153>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Parallel P Gain'
//  '<S154>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Reset Signal'
//  '<S155>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation'
//  '<S156>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation Fdbk'
//  '<S157>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum'
//  '<S158>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum Fdbk'
//  '<S159>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode'
//  '<S160>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode Sum'
//  '<S161>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Integral'
//  '<S162>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Ngain'
//  '<S163>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/postSat Signal'
//  '<S164>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preInt Signal'
//  '<S165>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preSat Signal'
//  '<S166>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S167>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S168>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S169>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/D Gain/Internal Parameters'
//  '<S170>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/External Derivative/Error'
//  '<S171>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter/Disc. Forward Euler Filter'
//  '<S172>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter ICs/Internal IC - Filter'
//  '<S173>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/I Gain/Internal Parameters'
//  '<S174>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain/Passthrough'
//  '<S175>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain Fdbk/Disabled'
//  '<S176>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator/Discrete'
//  '<S177>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator ICs/Internal IC'
//  '<S178>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Copy/Disabled'
//  '<S179>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Gain/Internal Parameters'
//  '<S180>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/P Copy/Disabled'
//  '<S181>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Parallel P Gain/Internal Parameters'
//  '<S182>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Reset Signal/External Reset'
//  '<S183>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation/Enabled'
//  '<S184>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation Fdbk/Disabled'
//  '<S185>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum/Sum_PID'
//  '<S186>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum Fdbk/Disabled'
//  '<S187>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode/Disabled'
//  '<S188>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode Sum/Passthrough'
//  '<S189>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S190>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Ngain/Passthrough'
//  '<S191>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/postSat Signal/Forward_Path'
//  '<S192>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preInt Signal/Internal PreInt'
//  '<S193>' : 'cascaded_controller/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preSat Signal/Forward_Path'
//  '<S194>' : 'cascaded_controller/low_level_controller_cgn/execute_command_cgn/commandExecuter'
//  '<S195>' : 'cascaded_controller/mission_manager_interface_cgn/MATLAB Function'
//  '<S196>' : 'cascaded_controller/mission_manager_interface_cgn/Subscribe'
//  '<S197>' : 'cascaded_controller/mission_manager_interface_cgn/Subsystem'
//  '<S198>' : 'cascaded_controller/mission_manager_interface_cgn/cmdMsgToCmdBus'
//  '<S199>' : 'cascaded_controller/mission_manager_interface_cgn/statusKwdToBool'
//  '<S200>' : 'cascaded_controller/mission_manager_interface_cgn/Subscribe/Enabled Subsystem'
//  '<S201>' : 'cascaded_controller/mission_manager_interface_cgn/Subsystem/Publish'
//  '<S202>' : 'cascaded_controller/pwm_heartbeat_publisher/Blank Message1'
//  '<S203>' : 'cascaded_controller/pwm_heartbeat_publisher/Publish2'
//  '<S204>' : 'cascaded_controller/pwm_publisher/Publish'
//  '<S205>' : 'cascaded_controller/state_estimator_cgn/derivedStateEstimates'
//  '<S206>' : 'cascaded_controller/state_estimator_cgn/discreteTimeQuatPropagation'
//  '<S207>' : 'cascaded_controller/state_estimator_cgn/dvl_reset'
//  '<S208>' : 'cascaded_controller/state_estimator_cgn/eulToQuat'
//  '<S209>' : 'cascaded_controller/state_estimator_cgn/quatToRotm'

#endif                                 // cascaded_controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
