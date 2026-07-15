//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_semifinal.h
//
// Code generated for Simulink model 'matlab_semifinal'.
//
// Model version                  : 1.15
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jul 14 17:19:54 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef matlab_semifinal_h_
#define matlab_semifinal_h_
#include <cmath>
#include <cstring>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "slros2_initialize.h"
#include "matlab_semifinal_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Block signals for system '<S25>/quatToEul'
struct B_quatToEul_matlab_semifinal_T {
  real_T Cbi[9];
  real_T a[9];
  real_T b_a[9];
};

// Block signals (default storage)
struct B_matlab_semifinal_T {
  SL_Bus_custom_interfaces_VR In1;     // '<S227>/In1'
  SL_Bus_custom_interfaces_VR rtb_SourceBlock_o2_mb;
  SL_Bus_custom_interfaces_Imu In1_g;  // '<S24>/In1'
  SL_Bus_custom_interfaces_Imu rtb_SourceBlock_o2_k_c;
  real_T force_column_data[201];
  real_T b_varargin_1_data[201];
  real_T b_x_data[201];
  X_bus X_est;                         // '<S6>/derivedStateEstimates'
  char_T temp_char[256];
  SL_Bus_custom_interfaces_Debug debug_msg;// '<S7>/MATLAB Function'
  cell_wrap_0_matlab_semifinal_T varargin_1[14];
  cmd_bus cmd;                         // '<S1>/cmdMsgToCmdBus'
  cell_wrap_0_matlab_semifinal_T varargin_2[13];
  cell_wrap_0_matlab_semifinal_T varargin_3[13];
  SL_Bus_custom_interfaces_Goal In1_h; // '<S21>/In1'
  real_T TmpSignalConversionAtSFunct[22];// '<S7>/MATLAB Function'
  SL_Bus_custom_interfaces_Goal rtb_SourceBlock_o2_p_k;
  real_T c_a[16];
  real_T X_u[13];                      // '<S26>/commandExecuter'
  real_T Qe1[12];
  real_T Cbi[9];
  real_T rtb_sensors_dvl_cov[9];
  real_T Cbi_c[9];                     // '<S6>/Transpose'
  real_T qk_plus_1_tmp[9];
  real_T rtb_Cbi_tmp[9];
  real_T rtb_Cbi_tmp_b[9];
  real_T Cbi_p[9];
  real_T a[9];
  real_T b_a[9];
  SL_Bus_custom_interfaces_DRR In1_c;  // '<S23>/In1'
  real_T pwms[8];
  real_T FT_cmd_list[8];               // '<S25>/thrusterAllocator'
  real_T dv[8];
  SL_Bus_custom_interfaces_DRR rtb_SourceBlock_o2_j_c;
  real_T varargin_1_f[6];
  real_T R_error[6];
  SL_Bus_custom_interfaces_Gamepad In1_k;// '<S232>/In1'
  SL_Bus_custom_interfaces_Gamepad rtb_SourceBlock_o2_e_g;
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S14>/Bus Creator3'
  real_T qinv[4];
  real_T qe_matlab[4];
  real_T qe_matlab_g[4];
  real_T qib_int_u[4];                 // '<S25>/guidanceLaw'
  real_T dv1[4];
  real_T DiscreteTransferFcn[4];
  real_T dv2[4];
  real_T qinv_m[4];
  real_T eps[3];
  real_T eps_n[3];
  real_T eps_p[3];
  real_T Rb_u[3];                      // '<S25>/guidanceLaw'
  real_T dRb_u[3];                     // '<S25>/dRbSetpointInjector'
  real_T dRb_e[3];                     // '<S25>/rateInjector'
  real_T dv3[3];
  real_T rtb_dvl_pos_l[3];
  real_T dv4[3];
  real_T x[3];
  real_T x_j[3];
  char_T b_zeroDelimTopic[18];
  char_T b_zeroDelimTopic_d[18];
  SL_Bus_custom_interfaces_Result result_msg;// '<S1>/statusKwdToBool'
  char_T b_zeroDelimTopic_g[17];
  char_T b_zeroDelimTopic_l[17];
  char_T x1[16];
  char_T s[16];
  cell_wrap_0_matlab_semifinal_T b;
  cell_wrap_0_matlab_semifinal_T c;
  cell_wrap_0_matlab_semifinal_T d;
  cell_wrap_0_matlab_semifinal_T e;
  cell_wrap_0_matlab_semifinal_T f;
  cell_wrap_0_matlab_semifinal_T g;
  cell_wrap_0_matlab_semifinal_T h;
  cell_wrap_0_matlab_semifinal_T i;
  cell_wrap_0_matlab_semifinal_T j;
  cell_wrap_0_matlab_semifinal_T k;
  cell_wrap_0_matlab_semifinal_T l;
  cell_wrap_0_matlab_semifinal_T m;
  cell_wrap_0_matlab_semifinal_T n;
  cell_wrap_0_matlab_semifinal_T o;
  cell_wrap_0_matlab_semifinal_T p;
  cell_wrap_0_matlab_semifinal_T q;
  cell_wrap_0_matlab_semifinal_T r;
  cell_wrap_0_matlab_semifinal_T s_d;
  cell_wrap_0_matlab_semifinal_T u;
  cell_wrap_0_matlab_semifinal_T v;
  cell_wrap_0_matlab_semifinal_T w;
  cell_wrap_0_matlab_semifinal_T x_d;
  cell_wrap_0_matlab_semifinal_T y;
  cell_wrap_0_matlab_semifinal_T ab;
  cell_wrap_0_matlab_semifinal_T bb;
  cell_wrap_0_matlab_semifinal_T cb;
  cell_wrap_0_matlab_semifinal_T db;
  char_T switch_expression[16];
  char_T b_zeroDelimTopic_lx[16];
  char_T b_zeroDelimTopic_o[16];
  char_T b_zeroDelimTopic_b[16];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF deadline_n;
  sJ4ih70VmKcvCeguWN0mNVF deadline_b;
  sJ4ih70VmKcvCeguWN0mNVF deadline_l;
  real_T Ri_xy_e[2];
  char_T digits[10];
  real_T eta;
  real_T scale;
  real_T absxk;
  real_T b_t;
  real_T norm_w;
  real_T b_a_h;
  real_T t;
  real_T b_scale;
  real_T b_absxk;
  real_T theta;
  real_T theta_b;
  real_T lower_voltage_index;
  real_T upper_voltage_index;
  real_T phi;
  real_T idx;
  real_T rotm_tmp;
  real_T rtb_dRb_u_d;
  real_T rtb_delta_qe_idx_2;
  real_T rtb_delta_qe_idx_1;
  real_T rtb_delta_qe_idx_3;
  real_T pwms_horiz_idx_1;
  real_T pwms_horiz_idx_2;
  real_T pwms_horiz_idx_3;
  real_T rtb_DeadZone_p_idx_0;
  real_T rtb_Eul_idx_0;
  real_T rtb_FilterCoefficient_d_idx_0;
  real_T rtb_DeadZone_p_idx_1;
  real_T rtb_Eul_idx_1;
  real_T rtb_FilterCoefficient_d_idx_1;
  real_T rtb_DeadZone_p_idx_2;
  real_T DiscreteTransferFcn_tmp_idx_2;
  real_T Qe1_e;
  real_T eps_b;
  real_T rtb_X_est_wb;
  real_T rtb_X_est_wb_j;
  real_T eps_tmp;
  real_T rtb_Cbi_tmp_tmp;
  real_T rtb_Cbi_tmp_tmp_f;
  real_T eta_a;
  real_T scale_j;
  real_T absxk_j;
  real_T b_t_o;
  real_T rotm_tmp_n;
  real_T rotm_tmp_i;
  real_T eps_idx_0;
  real_T eps_idx_1;
  real_T eps_idx_2;
  real_T rotm_idx_0;
  real_T rotm_idx_8;
  real_T rotm_idx_4_tmp;
  real_T qe_matlab_idx_0;
  real_T qe_matlab_idx_1;
  real_T qe_matlab_idx_2;
  real_T qe_matlab_idx_3;
  real_T varargin_1_data;
  real_T q_o;
  real_T eta_n;
  real_T scale_m;
  real_T absxk_c;
  real_T b_t_m;
  real_T rotm_tmp_m;
  real_T rotm_tmp_j;
  real_T eps_idx_0_h;
  real_T eps_idx_1_c;
  real_T eps_idx_2_c;
  real_T rotm_idx_0_p;
  real_T rotm_idx_8_p;
  real_T rotm_idx_4_tmp_a;
  real_T scale_e;
  real_T absxk_a;
  real_T t_a;
  real_T x_i;
  real_T x_l;
  SL_Bus_std_msgs_Bool In1_j;          // '<S229>/In1'
  boolean_T b_x[6];
  char_T fd[4];
  int32_T k_o;
  int32_T d_k;
  int32_T pos;
  int32_T db6;
  int32_T i_o;
  int32_T b_varargin_1_size;
  int32_T force_column_size_idx_0;
  int32_T c_ret;
  int32_T d_ret;
  int32_T idx_i;
  int32_T b_k;
  int32_T c_k;
  int32_T c_k_f;
  int32_T trueCount;
  int32_T i_i;
  int32_T i_f;
  int32_T idx_g;
  int32_T b_k_c;
  int32_T c_k_o;
  int32_T b_idx;
  int32_T last;
  int32_T k_l;
  int32_T b_idx_m;
  int32_T k_m;
  int32_T i1;
  int32_T i2;
  int32_T k_c;
  int32_T k_f;
  int32_T k_p;
  int32_T k_e;
  int32_T k_o4;
  int32_T k_h;
  int32_T ret;
  int32_T ret_l;
  int32_T ret_h;
  int32_T ret_m;
  int32_T ret_mc;
  uint32_T int_part;
  uint32_T frac_part;
  uint32_T temp;
  boolean_T new_waypoint_latch;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_h;
  boolean_T b_varargout_1_c;
  boolean_T DataStoreRead_n;           // '<S1>/Data Store Read'
  boolean_T dropper_trigger;           // '<S25>/trickFTListInjector'
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_m_k;
  B_quatToEul_matlab_semifinal_T sf_quatToEul1;// '<S25>/quatToEul1'
  B_quatToEul_matlab_semifinal_T sf_quatToEul;// '<S25>/quatToEul'
};

// Block states (default storage) for system '<Root>'
struct DW_matlab_semifinal_T {
  ros_slros2_internal_block_Sub_T obj; // '<S231>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_i;// '<S228>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_p;// '<S8>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_b;// '<S3>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_bu;// '<S2>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_j;// '<S17>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_n;// '<S236>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o;// '<S235>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_iq;// '<S226>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_oc;// '<S160>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_f;// '<S22>/SinkBlock'
  real_T PositionIntegrator_DSTATE[3]; // '<S6>/Position Integrator'
  real_T VelocityIntegrator_DSTATE[3]; // '<S6>/Velocity Integrator'
  real_T UnitDelay_DSTATE;             // '<S4>/Unit Delay'
  real_T UnitDelay1_DSTATE;            // '<S4>/Unit Delay1'
  real_T DelayInput1_DSTATE;           // '<S29>/Delay Input1'
  real_T DiscreteTimeIntegrator_DSTATE[4];// '<S32>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn_states[4];// '<S25>/Discrete Transfer Fcn'
  real_T Integrator_DSTATE[3];         // '<S139>/Integrator'
  real_T Filter_DSTATE[3];             // '<S134>/Filter'
  real_T Integrator_DSTATE_m[3];       // '<S83>/Integrator'
  real_T Filter_DSTATE_d[3];           // '<S78>/Filter'
  real_T Integrator_DSTATE_d[3];       // '<S198>/Integrator'
  real_T Filter_DSTATE_c[3];           // '<S193>/Filter'
  real_T db11;                         // '<Root>/Data Store Memory15'
  real_T offset[3];                    // '<S6>/dvl_reset'
  real_T qk[4];                        // '<S6>/discreteTimeQuatPropagation'
  real_T hold_timer_start_time;        // '<S26>/commandExecuter'
  real_T idle_wp[6];                   // '<S26>/commandExecuter'
  real_T cmd_specific_wp[6];           // '<S26>/commandExecuter'
  real_T prior_action_id;              // '<S26>/commandExecuter'
  real_T body_relative_wp[3];          // '<S26>/commandExecuter'
  real_T persistant_yaw_target;        // '<S25>/guidanceLaw'
  real_T action_id;                    // '<S25>/guidanceLaw'
  real_T prior_action_id_n;            // '<S25>/guidanceLaw'
  real_T prior_Ri_u[3];                // '<S25>/guidanceLaw'
  real_T ammo;                         // '<S33>/Dropper Magazine'
  real_T last_drop_time;               // '<S33>/Dropper Magazine'
  int8_T UnitDelay_DSTATE_f[4];        // '<S1>/Unit Delay'
  boolean_T DelayInput1_DSTATE_g;      // '<S30>/Delay Input1'
  int8_T PositionIntegrator_PrevResetSta;// '<S6>/Position Integrator'
  int8_T VelocityIntegrator_PrevResetSta;// '<S6>/Velocity Integrator'
  int8_T DiscreteTimeIntegrator_PrevRese;// '<S32>/Discrete-Time Integrator'
  int8_T Integrator_PrevResetState;    // '<S139>/Integrator'
  int8_T Filter_PrevResetState;        // '<S134>/Filter'
  int8_T Integrator_PrevResetState_d;  // '<S83>/Integrator'
  int8_T Filter_PrevResetState_g;      // '<S78>/Filter'
  int8_T Integrator_PrevResetState_p;  // '<S198>/Integrator'
  int8_T Filter_PrevResetState_k;      // '<S193>/Filter'
  uint8_T PositionIntegrator_IC_LOADING;// '<S6>/Position Integrator'
  uint8_T VelocityIntegrator_IC_LOADING;// '<S6>/Velocity Integrator'
  boolean_T mission_is_started;        // '<Root>/Data Store Memory3'
  boolean_T joystick_flag;             // '<Root>/joystick_mode_manager'
  boolean_T joystick_flag_not_empty;   // '<Root>/joystick_mode_manager'
  boolean_T prior_joystick_flag;       // '<Root>/joystick_mode_manager'
  boolean_T prior_joystick_flag_not_empty;// '<Root>/joystick_mode_manager'
  boolean_T do_mission_file_flag;      // '<Root>/joystick_mode_manager'
  boolean_T do_mission_file_flag_not_empty;// '<Root>/joystick_mode_manager'
  boolean_T prior_do_mission_file_flag;// '<Root>/joystick_mode_manager'
  boolean_T prior_do_mission_file_flag_not_;// '<Root>/joystick_mode_manager'
  boolean_T prior_flag;                // '<S6>/dvl_reset'
  boolean_T qk_not_empty;              // '<S6>/discreteTimeQuatPropagation'
  boolean_T hold_timer_start_time_not_empty;// '<S26>/commandExecuter'
  boolean_T idle_wp_not_empty;         // '<S26>/commandExecuter'
  boolean_T cmd_specific_wp_not_empty; // '<S26>/commandExecuter'
  boolean_T wp_defined_latch;          // '<S26>/commandExecuter'
  boolean_T prior_action_id_not_empty; // '<S25>/guidanceLaw'
};

// Constant parameters (default storage)
struct ConstP_matlab_semifinal_T {
  // Expression: FF_maneuvers
  //  Referenced by: '<S25>/trickFTListInjector'

  FF_maneuvers_bus trickFTListInjector_FF_maneuver;

  // Computed Parameter: Constant_Value_n
  //  Referenced by: '<S234>/Constant'

  SL_Bus_std_msgs_Empty Constant_Value_n;

  // Expression: ccw_force
  //  Referenced by: '<S34>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_force[1206];

  // Expression: ccw_pwm
  //  Referenced by: '<S34>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_pwm[201];

  // Expression: cw_force
  //  Referenced by: '<S34>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_force[1206];

  // Expression: cw_pwm
  //  Referenced by: '<S34>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_pwm[201];

  // Expression: voltage
  //  Referenced by: '<S34>/forceToPWMCalculator'

  real_T forceToPWMCalculator_voltage[6];

  // Expression: invMT_wrench
  //  Referenced by: '<S25>/Constant'

  real_T Constant_Value_i[24];

  // Expression: invFT_wrench
  //  Referenced by: '<S25>/Constant1'

  real_T Constant1_Value[24];

  // Expression: gi
  //  Referenced by: '<S6>/Constant'

  real_T Constant_Value_l0[3];

  // Expression: Cbimu_meas
  //  Referenced by: '<S6>/Constant1'

  real_T Constant1_Value_h[9];

  // Expression: qib_PID.Kp
  //  Referenced by: '<S25>/Gain1'

  real_T Gain1_Gain[4];

  // Expression: P
  //  Referenced by: '<S144>/Proportional Gain'

  real_T ProportionalGain_Gain[3];
};

// Real-time Model Data Structure
struct tag_RTM_matlab_semifinal_T {
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

  uint8_T &TaskCounter(int32_T idx);
  boolean_T StepTask(int32_T idx) const;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Constant parameters (default storage)
extern const ConstP_matlab_semifinal_T matlab_semifinal_ConstP;

// External function called from main
#ifdef __cplusplus

extern "C"
{

#endif

  extern void matlab_semifinal_SetEventsForThisBaseStep(boolean_T *eventFlags,
    RT_MODEL_matlab_semifinal_T *const matlab_semifinal_M);

#ifdef __cplusplus

}

#endif

// Class declaration for model matlab_semifinal
class matlab_semifinal final
{
  // public data and function members
 public:
  // Copy Constructor
  matlab_semifinal(matlab_semifinal const&) = delete;

  // Assignment Operator
  matlab_semifinal& operator= (matlab_semifinal const&) & = delete;

  // Move Constructor
  matlab_semifinal(matlab_semifinal &&) = delete;

  // Move Assignment Operator
  matlab_semifinal& operator= (matlab_semifinal &&) = delete;

  // Real-Time Model get method
  RT_MODEL_matlab_semifinal_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step0();

  // model step function
  void step1();

  // model terminate function
  void terminate();

  // Constructor
  matlab_semifinal();

  // Destructor
  ~matlab_semifinal();

  // private data and function members
 private:
  // Block signals
  B_matlab_semifinal_T matlab_semifinal_B;

  // Block states
  DW_matlab_semifinal_T matlab_semifinal_DW;

  // private member function(s) for subsystem '<S25>/quatToEul'
  void matlab_semifinal_quatToEul(const real_T rtu_qib_u[4], real_T rty_Eul_u[3],
    B_quatToEul_matlab_semifinal_T *localB);
  void matlab_semifinal_wrapToPi(real_T *lambda);

  // private member function(s) for subsystem '<Root>'
  real_T matlab_semifinal_rt_atan2d_snf(real_T u0, real_T u1);
  void matlab_semifinal_wrapToPi_k(real_T *lambda);
  void matlab_semifinal_eulToQuat_o(const real_T Eul[3], real_T qib[4]);
  boolean_T matlab_semifinal_withinWPTol(const real_T X_Ri[3], const real_T
    X_qib[4], const real_T X_u[13], const real_T cmd_wp_tol[6]);
  void matlab_sem_executeDurationTrick(real_T cmd_hold_time, const int8_T
    cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
    real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
    real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
    cmd_status[4], real_T *hold_timer, real_T X_u[13]);
  real_T matlab_semifinal_norm(const real_T x[2]);
  void matlab_semifinal_eulToQuat(const real_T Eul[3], real_T qib[4]);
  boolean_T matlab_semifinal_isequal(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_strcmp(const char_T b[16]);
  boolean_T matlab_semifinal_strcmp_b(const char_T b[16]);
  boolean_T matlab_semifinal_strcmp_b5(const char_T b[16]);
  boolean_T matlab_semifinal_isequal_hj(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_isequal_hj4(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_isequal_hj43(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_isequal_hj43r(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_isequal_hj43rz(const char_T varargin_1[16]);
  boolean_T matlab_semifinal_strcmp_l(const char_T b[16]);
  boolean_T matlab_semifinal_strcmp_lp(const char_T b[16]);
  void matlab_semifinal_minimum(const real_T x[6], real_T *ex, int32_T *idx);
  void matlab_semifinal_minimum_g(const real_T x_data[], const int32_T *x_size,
    real_T *ex, int32_T *idx);
  void matlab_semi_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab_se_Publisher_setupImpl_m(const ros_slros2_internal_block_Pub_T
    *obj);
  void matl_Subscriber_setupImpl_mj3b3(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab__Subscriber_setupImpl_mj(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_Subscriber_setupImpl_mj3(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_s_Subscriber_setupImpl_m(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_sem_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void matla_Subscriber_setupImpl_mj3b(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_Publisher_setupImpl_mj3b(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab_s_Publisher_setupImpl_mj(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab__Publisher_setupImpl_mj3(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_matlab_semifinal_T matlab_semifinal_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Constant' : Unused code path elimination
//  Block '<S1>/Scope' : Unused code path elimination
//  Block '<S25>/Discrete-Time Integrator' : Unused code path elimination
//  Block '<S25>/Discrete-Time Integrator1' : Unused code path elimination
//  Block '<S25>/Scope' : Unused code path elimination
//  Block '<S25>/Scope1' : Unused code path elimination
//  Block '<S25>/Scope2' : Unused code path elimination
//  Block '<S25>/Scope4' : Unused code path elimination
//  Block '<S33>/Scope' : Unused code path elimination
//  Block '<S6>/Display' : Unused code path elimination
//  Block '<S6>/Display1' : Unused code path elimination
//  Block '<S6>/Display2' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S25>/Gain' : Eliminated nontunable gain of 1
//  Block '<S25>/Gain3' : Eliminated nontunable gain of 1
//  Block '<S25>/Gain4' : Eliminated nontunable gain of 1


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
//  '<Root>' : 'matlab_semifinal'
//  '<S1>'   : 'matlab_semifinal/ '
//  '<S2>'   : 'matlab_semifinal/DRR'
//  '<S3>'   : 'matlab_semifinal/IMU'
//  '<S4>'   : 'matlab_semifinal/Low-Level Controller'
//  '<S5>'   : 'matlab_semifinal/MATLAB Function'
//  '<S6>'   : 'matlab_semifinal/Subsystem Reference'
//  '<S7>'   : 'matlab_semifinal/Subsystem Reference1'
//  '<S8>'   : 'matlab_semifinal/VR'
//  '<S9>'   : 'matlab_semifinal/dvl_reset_subscriber'
//  '<S10>'  : 'matlab_semifinal/joystick_mode_manager'
//  '<S11>'  : 'matlab_semifinal/joystick_output'
//  '<S12>'  : 'matlab_semifinal/joystick_to_pwm'
//  '<S13>'  : 'matlab_semifinal/pwm_heartbeat_publisher'
//  '<S14>'  : 'matlab_semifinal/pwm_publisher'
//  '<S15>'  : 'matlab_semifinal/sensorRosMsgToBus'
//  '<S16>'  : 'matlab_semifinal/ /MATLAB Function'
//  '<S17>'  : 'matlab_semifinal/ /Subscribe'
//  '<S18>'  : 'matlab_semifinal/ /Subsystem'
//  '<S19>'  : 'matlab_semifinal/ /cmdMsgToCmdBus'
//  '<S20>'  : 'matlab_semifinal/ /statusKwdToBool'
//  '<S21>'  : 'matlab_semifinal/ /Subscribe/Enabled Subsystem'
//  '<S22>'  : 'matlab_semifinal/ /Subsystem/Publish'
//  '<S23>'  : 'matlab_semifinal/DRR/Enabled Subsystem'
//  '<S24>'  : 'matlab_semifinal/IMU/Enabled Subsystem'
//  '<S25>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller'
//  '<S26>'  : 'matlab_semifinal/Low-Level Controller/execute_command'
//  '<S27>'  : 'matlab_semifinal/Low-Level Controller/quatToEul'
//  '<S28>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller'
//  '<S29>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Detect Change'
//  '<S30>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Detect Rise Positive'
//  '<S31>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb'
//  '<S32>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem'
//  '<S33>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference'
//  '<S34>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1'
//  '<S35>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller'
//  '<S36>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRbSetpointInjector'
//  '<S37>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/deltaQuatError'
//  '<S38>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/guidanceLaw'
//  '<S39>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/quatInjector'
//  '<S40>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/quatPID'
//  '<S41>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/quatToEul'
//  '<S42>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/quatToEul1'
//  '<S43>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/quatToRotm'
//  '<S44>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/rateInjector'
//  '<S45>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/thrusterAllocator'
//  '<S46>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/trickFTListInjector'
//  '<S47>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup'
//  '<S48>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain'
//  '<S49>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative'
//  '<S50>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter'
//  '<S51>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs'
//  '<S52>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain'
//  '<S53>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain'
//  '<S54>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk'
//  '<S55>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator'
//  '<S56>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs'
//  '<S57>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy'
//  '<S58>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain'
//  '<S59>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy'
//  '<S60>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain'
//  '<S61>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal'
//  '<S62>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation'
//  '<S63>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk'
//  '<S64>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum'
//  '<S65>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk'
//  '<S66>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode'
//  '<S67>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum'
//  '<S68>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral'
//  '<S69>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain'
//  '<S70>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal'
//  '<S71>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal'
//  '<S72>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal'
//  '<S73>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S74>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S75>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S76>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain/Internal Parameters'
//  '<S77>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative/Error'
//  '<S78>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter/Disc. Forward Euler Filter'
//  '<S79>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs/Internal IC - Filter'
//  '<S80>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain/Internal Parameters'
//  '<S81>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain/Passthrough'
//  '<S82>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk/Disabled'
//  '<S83>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator/Discrete'
//  '<S84>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs/Internal IC'
//  '<S85>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy/Disabled'
//  '<S86>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain/Internal Parameters'
//  '<S87>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy/Disabled'
//  '<S88>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain/Internal Parameters'
//  '<S89>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal/External Reset'
//  '<S90>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation/Enabled'
//  '<S91>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk/Disabled'
//  '<S92>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum/Sum_PID'
//  '<S93>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk/Disabled'
//  '<S94>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode/Disabled'
//  '<S95>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum/Passthrough'
//  '<S96>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S97>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain/Passthrough'
//  '<S98>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal/Forward_Path'
//  '<S99>'  : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal/Internal PreInt'
//  '<S100>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal/Forward_Path'
//  '<S101>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Detect Rise Positive/Positive'
//  '<S102>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller'
//  '<S103>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup'
//  '<S104>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain'
//  '<S105>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative'
//  '<S106>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter'
//  '<S107>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs'
//  '<S108>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain'
//  '<S109>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain'
//  '<S110>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk'
//  '<S111>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator'
//  '<S112>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs'
//  '<S113>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy'
//  '<S114>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain'
//  '<S115>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy'
//  '<S116>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain'
//  '<S117>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal'
//  '<S118>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation'
//  '<S119>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk'
//  '<S120>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum'
//  '<S121>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk'
//  '<S122>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode'
//  '<S123>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum'
//  '<S124>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral'
//  '<S125>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain'
//  '<S126>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal'
//  '<S127>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal'
//  '<S128>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal'
//  '<S129>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S130>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S131>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S132>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain/Internal Parameters'
//  '<S133>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative/Error'
//  '<S134>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S135>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S136>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain/Internal Parameters'
//  '<S137>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain/Passthrough'
//  '<S138>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S139>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator/Discrete'
//  '<S140>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs/Internal IC'
//  '<S141>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy/Disabled'
//  '<S142>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain/Internal Parameters'
//  '<S143>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy/Disabled'
//  '<S144>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S145>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal/External Reset'
//  '<S146>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation/Enabled'
//  '<S147>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk/Disabled'
//  '<S148>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum/Sum_PID'
//  '<S149>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk/Disabled'
//  '<S150>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode/Disabled'
//  '<S151>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S152>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S153>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S154>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal/Forward_Path'
//  '<S155>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal/Internal PreInt'
//  '<S156>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal/Forward_Path'
//  '<S157>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Blank Message'
//  '<S158>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Dropper Magazine'
//  '<S159>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Subsystem'
//  '<S160>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference/Subsystem/Publish'
//  '<S161>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1/forceToPWMCalculator'
//  '<S162>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup'
//  '<S163>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain'
//  '<S164>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative'
//  '<S165>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter'
//  '<S166>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs'
//  '<S167>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain'
//  '<S168>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain'
//  '<S169>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk'
//  '<S170>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator'
//  '<S171>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs'
//  '<S172>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy'
//  '<S173>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain'
//  '<S174>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy'
//  '<S175>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain'
//  '<S176>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal'
//  '<S177>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation'
//  '<S178>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk'
//  '<S179>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum'
//  '<S180>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk'
//  '<S181>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode'
//  '<S182>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum'
//  '<S183>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral'
//  '<S184>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain'
//  '<S185>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal'
//  '<S186>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal'
//  '<S187>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal'
//  '<S188>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S189>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S190>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S191>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain/Internal Parameters'
//  '<S192>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative/Error'
//  '<S193>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter/Disc. Forward Euler Filter'
//  '<S194>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs/Internal IC - Filter'
//  '<S195>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain/Internal Parameters'
//  '<S196>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain/Passthrough'
//  '<S197>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk/Disabled'
//  '<S198>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator/Discrete'
//  '<S199>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs/Internal IC'
//  '<S200>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy/Disabled'
//  '<S201>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain/Internal Parameters'
//  '<S202>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy/Disabled'
//  '<S203>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain/Internal Parameters'
//  '<S204>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal/External Reset'
//  '<S205>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation/Enabled'
//  '<S206>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk/Disabled'
//  '<S207>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum/Sum_PID'
//  '<S208>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk/Disabled'
//  '<S209>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode/Disabled'
//  '<S210>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum/Passthrough'
//  '<S211>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S212>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain/Passthrough'
//  '<S213>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal/Forward_Path'
//  '<S214>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal/Internal PreInt'
//  '<S215>' : 'matlab_semifinal/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal/Forward_Path'
//  '<S216>' : 'matlab_semifinal/Low-Level Controller/execute_command/cmdStatusID'
//  '<S217>' : 'matlab_semifinal/Low-Level Controller/execute_command/commandExecuter'
//  '<S218>' : 'matlab_semifinal/Low-Level Controller/execute_command/quatToEul'
//  '<S219>' : 'matlab_semifinal/Subsystem Reference/derivedStateEstimates'
//  '<S220>' : 'matlab_semifinal/Subsystem Reference/discreteTimeQuatPropagation'
//  '<S221>' : 'matlab_semifinal/Subsystem Reference/dvl_reset'
//  '<S222>' : 'matlab_semifinal/Subsystem Reference/eulToQuat'
//  '<S223>' : 'matlab_semifinal/Subsystem Reference/quatToRotm'
//  '<S224>' : 'matlab_semifinal/Subsystem Reference1/Blank Message'
//  '<S225>' : 'matlab_semifinal/Subsystem Reference1/MATLAB Function'
//  '<S226>' : 'matlab_semifinal/Subsystem Reference1/Publish'
//  '<S227>' : 'matlab_semifinal/VR/Enabled Subsystem'
//  '<S228>' : 'matlab_semifinal/dvl_reset_subscriber/Subscribe'
//  '<S229>' : 'matlab_semifinal/dvl_reset_subscriber/Subscribe/Enabled Subsystem'
//  '<S230>' : 'matlab_semifinal/joystick_output/MATLAB Function'
//  '<S231>' : 'matlab_semifinal/joystick_output/Subscribe'
//  '<S232>' : 'matlab_semifinal/joystick_output/Subscribe/Enabled Subsystem'
//  '<S233>' : 'matlab_semifinal/joystick_to_pwm/joystick_inputs_to_body_forces'
//  '<S234>' : 'matlab_semifinal/pwm_heartbeat_publisher/Blank Message1'
//  '<S235>' : 'matlab_semifinal/pwm_heartbeat_publisher/Publish2'
//  '<S236>' : 'matlab_semifinal/pwm_publisher/Publish'

#endif                                 // matlab_semifinal_h_

//
// File trailer for generated code.
//
// [EOF]
//
