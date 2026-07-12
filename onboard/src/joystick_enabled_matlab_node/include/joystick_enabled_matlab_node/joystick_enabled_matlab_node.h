//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: joystick_enabled_matlab_node.h
//
// Code generated for Simulink model 'joystick_enabled_matlab_node'.
//
// Model version                  : 1.11
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Jul 11 23:06:24 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef joystick_enabled_matlab_node_h_
#define joystick_enabled_matlab_node_h_
#include <cmath>
#include <cstring>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "slros2_initialize.h"
#include "joystick_enabled_matlab_node_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Block signals for system '<S26>/quatToEul'
struct B_quatToEul_joystick_enabled__T {
  real_T Cbi[9];
  real_T a[9];
  real_T b_a[9];
};

// Block signals (default storage)
struct B_joystick_enabled_matlab_nod_T {
  SL_Bus_custom_interfaces_VR In1;     // '<S221>/In1'
  SL_Bus_custom_interfaces_VR rtb_SourceBlock_o2_m;
  SL_Bus_custom_interfaces_Imu In1_o;  // '<S25>/In1'
  SL_Bus_custom_interfaces_Imu rtb_SourceBlock_o2_b_c;
  real_T force_column_data[201];
  real_T b_varargin_1_data[201];
  real_T b_x_data[201];
  X_bus X_est;                         // '<S6>/derivedStateEstimates'
  char_T temp_char[256];
  SL_Bus_custom_interfaces_Debug debug_msg;// '<S7>/MATLAB Function'
  cmd_bus cmd;                         // '<S1>/cmdMsgToCmdBus'
  cell_wrap_0_joystick_enabled__T varargin_1[13];
  cell_wrap_0_joystick_enabled__T varargin_2[13];
  cell_wrap_0_joystick_enabled__T varargin_3[13];
  SL_Bus_custom_interfaces_Goal In1_e; // '<S22>/In1'
  real_T TmpSignalConversionAtSFunct[22];// '<S7>/MATLAB Function'
  SL_Bus_custom_interfaces_Goal rtb_SourceBlock_o2_e_k;
  real_T c_a[16];
  real_T X_u[13];                      // '<S27>/commandExecuter'
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
  SL_Bus_custom_interfaces_DRR In1_g;  // '<S24>/In1'
  real_T pwms[8];
  real_T FT_cmd_list[8];               // '<S26>/thrusterAllocator'
  real_T dv[8];
  SL_Bus_custom_interfaces_DRR rtb_SourceBlock_o2_l_c;
  real_T varargin_1_f[6];
  real_T R_error[6];
  SL_Bus_custom_interfaces_Gamepad In1_f;// '<S229>/In1'
  SL_Bus_custom_interfaces_Gamepad rtb_SourceBlock_o2_lx_g;
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S15>/Bus Creator3'
  real_T qinv[4];
  real_T qe_matlab[4];
  real_T qe_matlab_g[4];
  real_T qib_int_u[4];                 // '<S26>/guidanceLaw'
  real_T dv1[4];
  real_T DiscreteTransferFcn[4];
  real_T dv2[4];
  real_T qinv_m[4];
  real_T eps[3];
  real_T eps_n[3];
  real_T eps_p[3];
  real_T Rb_u[3];                      // '<S26>/guidanceLaw'
  real_T wb_u[3];                      // '<S26>/quatPID'
  real_T dRb_e[3];                     // '<S26>/rateInjector'
  real_T Integrator_i[3];              // '<S192>/Integrator'
  real_T dv3[3];
  real_T rtb_dvl_pos_l[3];
  real_T dv4[3];
  real_T x[3];
  real_T x_j[3];
  char_T b_zeroDelimTopic[20];
  char_T b_zeroDelimTopic_d[18];
  char_T b_zeroDelimTopic_g[18];
  SL_Bus_custom_interfaces_Result result_msg;// '<S1>/statusKwdToBool'
  char_T b_zeroDelimTopic_l[17];
  char_T x1[16];
  char_T s[16];
  cell_wrap_0_joystick_enabled__T b;
  cell_wrap_0_joystick_enabled__T c;
  cell_wrap_0_joystick_enabled__T d;
  cell_wrap_0_joystick_enabled__T e;
  cell_wrap_0_joystick_enabled__T f;
  cell_wrap_0_joystick_enabled__T g;
  cell_wrap_0_joystick_enabled__T h;
  cell_wrap_0_joystick_enabled__T i;
  cell_wrap_0_joystick_enabled__T j;
  cell_wrap_0_joystick_enabled__T k;
  cell_wrap_0_joystick_enabled__T l;
  cell_wrap_0_joystick_enabled__T m;
  cell_wrap_0_joystick_enabled__T n;
  cell_wrap_0_joystick_enabled__T o;
  cell_wrap_0_joystick_enabled__T p;
  cell_wrap_0_joystick_enabled__T q;
  cell_wrap_0_joystick_enabled__T r;
  cell_wrap_0_joystick_enabled__T s_d;
  cell_wrap_0_joystick_enabled__T u;
  cell_wrap_0_joystick_enabled__T v;
  cell_wrap_0_joystick_enabled__T w;
  cell_wrap_0_joystick_enabled__T x_d;
  cell_wrap_0_joystick_enabled__T y;
  cell_wrap_0_joystick_enabled__T ab;
  cell_wrap_0_joystick_enabled__T bb;
  cell_wrap_0_joystick_enabled__T cb;
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
  real_T upper_force_index;
  real_T alpha;
  real_T phi;
  real_T idx;
  real_T rotm_tmp;
  real_T eps_d;
  real_T rtb_Integrator_i_e;
  real_T rtb_delta_qe_idx_2;
  real_T rtb_delta_qe_idx_1;
  real_T rtb_delta_qe_idx_3;
  real_T pwms_horiz_idx_1;
  real_T pwms_horiz_idx_2;
  real_T pwms_horiz_idx_3;
  real_T rtb_DeadZone_o_idx_0;
  real_T DiscreteTransferFcn_tmp_idx_2;
  real_T rtb_Filter_p_idx_0;
  real_T rtb_X_est_idx_2;
  real_T Qe1_b;
  real_T rtb_Rb_u_j;
  real_T rtb_Rb_u_f;
  real_T eps_a;
  real_T rtb_X_est_wb;
  real_T rtb_X_est_wb_j;
  real_T eps_tmp;
  real_T rtb_delta_qe_idx_1_tmp;
  real_T eta_j;
  real_T scale_o;
  real_T absxk_n;
  real_T b_t_i;
  real_T rotm_tmp_o;
  real_T rotm_tmp_n;
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
  real_T q_m;
  real_T eta_c;
  real_T scale_m;
  real_T absxk_m;
  real_T b_t_j;
  real_T rotm_tmp_h;
  real_T rotm_tmp_c;
  real_T eps_idx_0_c;
  real_T eps_idx_1_p;
  real_T eps_idx_2_p;
  real_T rotm_idx_0_a;
  real_T rotm_idx_8_e;
  real_T rotm_idx_4_tmp_a;
  real_T scale_a;
  real_T absxk_i;
  real_T t_l;
  real_T x_o;
  real_T x_o2;
  SL_Bus_std_msgs_Bool In1_b;          // '<S223>/In1'
  boolean_T b_x[6];
  char_T fd[4];
  int32_T b_index;
  int32_T d_k;
  int32_T pos;
  int32_T db6;
  int32_T i_i;
  int32_T b_varargin_1_size;
  int32_T force_column_size_idx_0;
  int32_T c_ret;
  int32_T d_ret;
  int32_T idx_f;
  int32_T b_k;
  int32_T c_k;
  int32_T c_k_i;
  int32_T trueCount;
  int32_T i_f;
  int32_T i_g;
  int32_T idx_c;
  int32_T b_k_o;
  int32_T c_k_l;
  int32_T b_idx;
  int32_T last;
  int32_T k_m;
  int32_T b_idx_m;
  int32_T k_c;
  int32_T i1;
  int32_T i2;
  int32_T k_f;
  int32_T ret;
  int32_T ret_p;
  int32_T ret_e;
  uint32_T int_part;
  uint32_T frac_part;
  uint32_T temp;
  uint8_T integrator_reset;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_o;
  boolean_T b_varargout_1_h;
  boolean_T DataStoreRead_k;           // '<S1>/Data Store Read'
  boolean_T OR1;                       // '<S4>/OR1'
  boolean_T reset_dvl_pos;
  SL_Bus_std_msgs_Bool rtb_SourceBlock_o2_j_l;
  SL_Bus_std_msgs_Empty r_h;
  B_quatToEul_joystick_enabled__T sf_quatToEul1;// '<S26>/quatToEul1'
  B_quatToEul_joystick_enabled__T sf_quatToEul;// '<S26>/quatToEul'
};

// Block states (default storage) for system '<Root>'
struct DW_joystick_enabled_matlab_no_T {
  ros_slros2_internal_block_Sub_T obj; // '<S228>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_h;// '<S225>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_c;// '<S222>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_p;// '<S8>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_b;// '<S3>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_a;// '<S2>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_n;// '<S18>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_e;// '<S233>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_f;// '<S232>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_g;// '<S220>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o;// '<S23>/SinkBlock'
  real_T PositionIntegrator_DSTATE[3]; // '<S6>/Position Integrator'
  real_T VelocityIntegrator_DSTATE[3]; // '<S6>/Velocity Integrator'
  real_T UnitDelay_DSTATE;             // '<S4>/Unit Delay'
  real_T UnitDelay1_DSTATE;            // '<S4>/Unit Delay1'
  real_T DelayInput1_DSTATE;           // '<S30>/Delay Input1'
  real_T DiscreteTimeIntegrator_DSTATE[4];// '<S32>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn_states[4];// '<S26>/Discrete Transfer Fcn'
  real_T Integrator_DSTATE[3];         // '<S137>/Integrator'
  real_T Filter_DSTATE[3];             // '<S132>/Filter'
  real_T Integrator_DSTATE_j[3];       // '<S82>/Integrator'
  real_T Filter_DSTATE_n[3];           // '<S77>/Filter'
  real_T Integrator_DSTATE_h[3];       // '<S192>/Integrator'
  real_T Filter_DSTATE_g[3];           // '<S187>/Filter'
  real_T db11;                         // '<Root>/Data Store Memory15'
  real_T time_since_last_beat;         // '<S10>/MATLAB Function'
  real_T offset[3];                    // '<S6>/dvl_reset'
  real_T qk[4];                        // '<S6>/discreteTimeQuatPropagation'
  real_T hold_timer_start_time;        // '<S27>/commandExecuter'
  real_T idle_wp[6];                   // '<S27>/commandExecuter'
  real_T cmd_specific_wp[6];           // '<S27>/commandExecuter'
  real_T prior_action_id;              // '<S27>/commandExecuter'
  real_T body_relative_wp[3];          // '<S27>/commandExecuter'
  real_T persistant_yaw_target;        // '<S26>/guidanceLaw'
  real_T action_id;                    // '<S26>/guidanceLaw'
  real_T prior_action_id_g;            // '<S26>/guidanceLaw'
  real_T prior_Ri_u[3];                // '<S26>/guidanceLaw'
  int8_T UnitDelay_DSTATE_d[4];        // '<S1>/Unit Delay'
  int8_T PositionIntegrator_PrevResetSta;// '<S6>/Position Integrator'
  int8_T VelocityIntegrator_PrevResetSta;// '<S6>/Velocity Integrator'
  int8_T DiscreteTimeIntegrator_PrevRese;// '<S32>/Discrete-Time Integrator'
  int8_T Integrator_PrevResetState;    // '<S137>/Integrator'
  int8_T Filter_PrevResetState;        // '<S132>/Filter'
  int8_T Integrator_PrevResetState_d;  // '<S82>/Integrator'
  int8_T Filter_PrevResetState_j;      // '<S77>/Filter'
  int8_T Integrator_PrevResetState_p;  // '<S192>/Integrator'
  int8_T Filter_PrevResetState_a;      // '<S187>/Filter'
  uint8_T PositionIntegrator_IC_LOADING;// '<S6>/Position Integrator'
  uint8_T VelocityIntegrator_IC_LOADING;// '<S6>/Velocity Integrator'
  boolean_T mission_is_started;        // '<Root>/Data Store Memory3'
  boolean_T joystick_flag;             // '<Root>/joystick_mode_manager'
  boolean_T prior_joystick_flag;       // '<Root>/joystick_mode_manager'
  boolean_T do_mission_file_flag;      // '<Root>/joystick_mode_manager'
  boolean_T prior_do_mission_file_flag;// '<Root>/joystick_mode_manager'
  boolean_T prior_flag;                // '<S6>/dvl_reset'
  boolean_T qk_not_empty;              // '<S6>/discreteTimeQuatPropagation'
  boolean_T hold_timer_start_time_not_empty;// '<S27>/commandExecuter'
  boolean_T idle_wp_not_empty;         // '<S27>/commandExecuter'
  boolean_T cmd_specific_wp_not_empty; // '<S27>/commandExecuter'
  boolean_T wp_defined_latch;          // '<S27>/commandExecuter'
  boolean_T prior_action_id_not_empty; // '<S26>/guidanceLaw'
};

// Constant parameters (default storage)
struct ConstP_joystick_enabled_matla_T {
  // Expression: FF_maneuvers
  //  Referenced by: '<S26>/trickFTListInjector'

  FF_maneuvers_bus trickFTListInjector_FF_maneuver;

  // Pooled Parameter (Expression: )
  //  Referenced by:
  //    '<S225>/Constant'
  //    '<S231>/Constant'
  //    '<S226>/Out1'

  SL_Bus_std_msgs_Empty pooled7;

  // Expression: ccw_force
  //  Referenced by: '<S33>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_force[1206];

  // Expression: ccw_pwm
  //  Referenced by: '<S33>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_pwm[201];

  // Expression: cw_force
  //  Referenced by: '<S33>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_force[1206];

  // Expression: cw_pwm
  //  Referenced by: '<S33>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_pwm[201];

  // Expression: voltage
  //  Referenced by: '<S33>/forceToPWMCalculator'

  real_T forceToPWMCalculator_voltage[6];

  // Expression: invMT_wrench
  //  Referenced by: '<S26>/Constant'

  real_T Constant_Value_p[24];

  // Expression: invFT_wrench
  //  Referenced by: '<S26>/Constant1'

  real_T Constant1_Value[24];

  // Expression: gi
  //  Referenced by: '<S6>/Constant'

  real_T Constant_Value_m[3];

  // Expression: Cbimu_meas
  //  Referenced by: '<S6>/Constant1'

  real_T Constant1_Value_e[9];

  // Expression: qib_PID.Kp
  //  Referenced by: '<S26>/Gain1'

  real_T Gain1_Gain[4];

  // Expression: P
  //  Referenced by: '<S142>/Proportional Gain'

  real_T ProportionalGain_Gain[3];
};

// Real-time Model Data Structure
struct tag_RTM_joystick_enabled_matl_T {
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
extern const ConstP_joystick_enabled_matla_T joystick_enabled_matlab__ConstP;

// External function called from main
#ifdef __cplusplus

extern "C"
{

#endif

  extern void joystick_enabled_matlab_node_SetEventsForThisBaseStep(boolean_T
    *eventFlags, RT_MODEL_joystick_enabled_mat_T *const
    joystick_enabled_matlab_node_M);

#ifdef __cplusplus

}

#endif

// Class declaration for model joystick_enabled_matlab_node
class joystick_enabled_matlab_node final
{
  // public data and function members
 public:
  // Copy Constructor
  joystick_enabled_matlab_node(joystick_enabled_matlab_node const&) = delete;

  // Assignment Operator
  joystick_enabled_matlab_node& operator= (joystick_enabled_matlab_node const&)
    & = delete;

  // Move Constructor
  joystick_enabled_matlab_node(joystick_enabled_matlab_node &&) = delete;

  // Move Assignment Operator
  joystick_enabled_matlab_node& operator= (joystick_enabled_matlab_node &&) =
    delete;

  // Real-Time Model get method
  RT_MODEL_joystick_enabled_mat_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step0();

  // model step function
  void step1();

  // model terminate function
  void terminate();

  // Constructor
  joystick_enabled_matlab_node();

  // Destructor
  ~joystick_enabled_matlab_node();

  // private data and function members
 private:
  // Block signals
  B_joystick_enabled_matlab_nod_T joystick_enabled_matlab_node_B;

  // Block states
  DW_joystick_enabled_matlab_no_T joystick_enabled_matlab_node_DW;

  // private member function(s) for subsystem '<S26>/quatToEul'
  void joystick_enabled__quatToEul(const real_T rtu_qib_u[4], real_T rty_Eul_u[3],
    B_quatToEul_joystick_enabled__T *localB);
  void joystick_enabled_matla_wrapToPi(real_T *lambda);

  // private member function(s) for subsystem '<Root>'
  real_T joystick_enabled__rt_atan2d_snf(real_T u0, real_T u1);
  void joystick_enabled_mat_wrapToPi_k(real_T *lambda);
  void joystick_enabled_ma_eulToQuat_f(const real_T Eul[3], real_T qib[4]);
  boolean_T joystick_enabled_ma_withinWPTol(const real_T X_Ri[3], const real_T
    X_qib[4], const real_T X_u[13], const real_T cmd_wp_tol[6]);
  void joystick_e_executeDurationTrick(real_T cmd_hold_time, const int8_T
    cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
    real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
    real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
    cmd_status[4], real_T *hold_timer, real_T X_u[13]);
  real_T joystick_enabled_matlab_no_norm(const real_T x[2]);
  void joystick_enabled_matl_eulToQuat(const real_T Eul[3], real_T qib[4]);
  boolean_T joystick_enabled_matlab_isequal(const char_T varargin_1[16]);
  boolean_T joystick_enabled_matlab__strcmp(const char_T b[16]);
  boolean_T joystick_enabled_matla_strcmp_g(const char_T b[16]);
  boolean_T joystick_enabled_matl_strcmp_gy(const char_T b[16]);
  void joystick_enabled_matlab_minimum(const real_T x[6], real_T *ex, int32_T
    *idx);
  void joystick_enabled_matl_minimum_i(const real_T x_data[], const int32_T
    *x_size, real_T *ex, int32_T *idx);
  void joystick_en_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  void joy_Subscriber_setupImpl_oroz0s(const ros_slros2_internal_block_Sub_T
    *obj);
  void joystic_Subscriber_setupImpl_or(const ros_slros2_internal_block_Sub_T
    *obj);
  void joysti_Subscriber_setupImpl_oro(const ros_slros2_internal_block_Sub_T
    *obj);
  void joystick_Subscriber_setupImpl_o(const ros_slros2_internal_block_Sub_T
    *obj);
  void joystick_e_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void joyst_Subscriber_setupImpl_oroz(const ros_slros2_internal_block_Sub_T
    *obj);
  void joys_Subscriber_setupImpl_oroz0(const ros_slros2_internal_block_Sub_T
    *obj);
  void joystic_Publisher_setupImpl_oro(const ros_slros2_internal_block_Pub_T
    *obj);
  void joystick__Publisher_setupImpl_o(const ros_slros2_internal_block_Pub_T
    *obj);
  void joystick_Publisher_setupImpl_or(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_joystick_enabled_mat_T joystick_enabled_matlab_node_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Constant' : Unused code path elimination
//  Block '<S1>/Scope' : Unused code path elimination
//  Block '<S26>/Discrete-Time Integrator' : Unused code path elimination
//  Block '<S26>/Discrete-Time Integrator1' : Unused code path elimination
//  Block '<S26>/Scope' : Unused code path elimination
//  Block '<S26>/Scope1' : Unused code path elimination
//  Block '<S26>/Scope4' : Unused code path elimination
//  Block '<S27>/Display' : Unused code path elimination
//  Block '<S27>/Display1' : Unused code path elimination
//  Block '<S27>/Scope' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination
//  Block '<S10>/Scope1' : Unused code path elimination
//  Block '<S26>/Gain' : Eliminated nontunable gain of 1
//  Block '<S26>/Gain3' : Eliminated nontunable gain of 1
//  Block '<S26>/Gain4' : Eliminated nontunable gain of 1


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
//  '<Root>' : 'joystick_enabled_matlab_node'
//  '<S1>'   : 'joystick_enabled_matlab_node/ '
//  '<S2>'   : 'joystick_enabled_matlab_node/DRR'
//  '<S3>'   : 'joystick_enabled_matlab_node/IMU'
//  '<S4>'   : 'joystick_enabled_matlab_node/Low-Level Controller'
//  '<S5>'   : 'joystick_enabled_matlab_node/MATLAB Function'
//  '<S6>'   : 'joystick_enabled_matlab_node/Subsystem Reference'
//  '<S7>'   : 'joystick_enabled_matlab_node/Subsystem Reference1'
//  '<S8>'   : 'joystick_enabled_matlab_node/VR'
//  '<S9>'   : 'joystick_enabled_matlab_node/dvl_reset_subscriber'
//  '<S10>'  : 'joystick_enabled_matlab_node/joystick_heartbeat'
//  '<S11>'  : 'joystick_enabled_matlab_node/joystick_mode_manager'
//  '<S12>'  : 'joystick_enabled_matlab_node/joystick_output'
//  '<S13>'  : 'joystick_enabled_matlab_node/joystick_to_pwm'
//  '<S14>'  : 'joystick_enabled_matlab_node/pwm_heartbeat_publisher'
//  '<S15>'  : 'joystick_enabled_matlab_node/pwm_publisher'
//  '<S16>'  : 'joystick_enabled_matlab_node/sensorRosMsgToBus'
//  '<S17>'  : 'joystick_enabled_matlab_node/ /MATLAB Function'
//  '<S18>'  : 'joystick_enabled_matlab_node/ /Subscribe'
//  '<S19>'  : 'joystick_enabled_matlab_node/ /Subsystem'
//  '<S20>'  : 'joystick_enabled_matlab_node/ /cmdMsgToCmdBus'
//  '<S21>'  : 'joystick_enabled_matlab_node/ /statusKwdToBool'
//  '<S22>'  : 'joystick_enabled_matlab_node/ /Subscribe/Enabled Subsystem'
//  '<S23>'  : 'joystick_enabled_matlab_node/ /Subsystem/Publish'
//  '<S24>'  : 'joystick_enabled_matlab_node/DRR/Enabled Subsystem'
//  '<S25>'  : 'joystick_enabled_matlab_node/IMU/Enabled Subsystem'
//  '<S26>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller'
//  '<S27>'  : 'joystick_enabled_matlab_node/Low-Level Controller/execute_command'
//  '<S28>'  : 'joystick_enabled_matlab_node/Low-Level Controller/quatToEul'
//  '<S29>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller'
//  '<S30>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Detect Change'
//  '<S31>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb'
//  '<S32>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Subsystem'
//  '<S33>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1'
//  '<S34>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller'
//  '<S35>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRbSetpointInjector'
//  '<S36>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/deltaQuatError'
//  '<S37>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/guidanceLaw'
//  '<S38>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/quatInjector'
//  '<S39>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/quatPID'
//  '<S40>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/quatToEul'
//  '<S41>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/quatToEul1'
//  '<S42>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/quatToRotm'
//  '<S43>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/rateInjector'
//  '<S44>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/thrusterAllocator'
//  '<S45>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/trickFTListInjector'
//  '<S46>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup'
//  '<S47>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain'
//  '<S48>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative'
//  '<S49>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter'
//  '<S50>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs'
//  '<S51>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain'
//  '<S52>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain'
//  '<S53>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk'
//  '<S54>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator'
//  '<S55>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs'
//  '<S56>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy'
//  '<S57>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain'
//  '<S58>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy'
//  '<S59>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain'
//  '<S60>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal'
//  '<S61>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation'
//  '<S62>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk'
//  '<S63>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum'
//  '<S64>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk'
//  '<S65>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode'
//  '<S66>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum'
//  '<S67>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral'
//  '<S68>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain'
//  '<S69>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal'
//  '<S70>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal'
//  '<S71>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal'
//  '<S72>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S73>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S74>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S75>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain/Internal Parameters'
//  '<S76>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative/Error'
//  '<S77>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter/Disc. Forward Euler Filter'
//  '<S78>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs/Internal IC - Filter'
//  '<S79>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain/Internal Parameters'
//  '<S80>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain/Passthrough'
//  '<S81>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk/Disabled'
//  '<S82>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator/Discrete'
//  '<S83>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs/Internal IC'
//  '<S84>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy/Disabled'
//  '<S85>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain/Internal Parameters'
//  '<S86>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy/Disabled'
//  '<S87>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain/Internal Parameters'
//  '<S88>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal/External Reset'
//  '<S89>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation/Enabled'
//  '<S90>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk/Disabled'
//  '<S91>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum/Sum_PID'
//  '<S92>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk/Disabled'
//  '<S93>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode/Disabled'
//  '<S94>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum/Passthrough'
//  '<S95>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S96>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain/Passthrough'
//  '<S97>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal/Forward_Path'
//  '<S98>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal/Internal PreInt'
//  '<S99>'  : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal/Forward_Path'
//  '<S100>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller'
//  '<S101>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup'
//  '<S102>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain'
//  '<S103>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative'
//  '<S104>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter'
//  '<S105>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs'
//  '<S106>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain'
//  '<S107>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain'
//  '<S108>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk'
//  '<S109>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator'
//  '<S110>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs'
//  '<S111>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy'
//  '<S112>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain'
//  '<S113>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy'
//  '<S114>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain'
//  '<S115>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal'
//  '<S116>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation'
//  '<S117>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk'
//  '<S118>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum'
//  '<S119>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk'
//  '<S120>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode'
//  '<S121>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum'
//  '<S122>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral'
//  '<S123>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain'
//  '<S124>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal'
//  '<S125>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal'
//  '<S126>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal'
//  '<S127>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S128>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S129>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S130>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain/Internal Parameters'
//  '<S131>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative/Error'
//  '<S132>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S133>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S134>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain/Internal Parameters'
//  '<S135>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain/Passthrough'
//  '<S136>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S137>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator/Discrete'
//  '<S138>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs/Internal IC'
//  '<S139>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy/Disabled'
//  '<S140>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain/Internal Parameters'
//  '<S141>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy/Disabled'
//  '<S142>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S143>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal/External Reset'
//  '<S144>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation/Enabled'
//  '<S145>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk/Disabled'
//  '<S146>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum/Sum_PID'
//  '<S147>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk/Disabled'
//  '<S148>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode/Disabled'
//  '<S149>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S150>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S151>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S152>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal/Forward_Path'
//  '<S153>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal/Internal PreInt'
//  '<S154>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal/Forward_Path'
//  '<S155>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1/forceToPWMCalculator'
//  '<S156>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup'
//  '<S157>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain'
//  '<S158>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative'
//  '<S159>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter'
//  '<S160>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs'
//  '<S161>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain'
//  '<S162>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain'
//  '<S163>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk'
//  '<S164>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator'
//  '<S165>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs'
//  '<S166>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy'
//  '<S167>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain'
//  '<S168>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy'
//  '<S169>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain'
//  '<S170>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal'
//  '<S171>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation'
//  '<S172>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk'
//  '<S173>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum'
//  '<S174>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk'
//  '<S175>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode'
//  '<S176>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum'
//  '<S177>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral'
//  '<S178>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain'
//  '<S179>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal'
//  '<S180>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal'
//  '<S181>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal'
//  '<S182>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S183>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S184>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S185>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain/Internal Parameters'
//  '<S186>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative/Error'
//  '<S187>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter/Disc. Forward Euler Filter'
//  '<S188>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs/Internal IC - Filter'
//  '<S189>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain/Internal Parameters'
//  '<S190>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain/Passthrough'
//  '<S191>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk/Disabled'
//  '<S192>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator/Discrete'
//  '<S193>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs/Internal IC'
//  '<S194>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy/Disabled'
//  '<S195>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain/Internal Parameters'
//  '<S196>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy/Disabled'
//  '<S197>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain/Internal Parameters'
//  '<S198>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal/External Reset'
//  '<S199>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation/Enabled'
//  '<S200>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk/Disabled'
//  '<S201>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum/Sum_PID'
//  '<S202>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk/Disabled'
//  '<S203>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode/Disabled'
//  '<S204>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum/Passthrough'
//  '<S205>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S206>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain/Passthrough'
//  '<S207>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal/Forward_Path'
//  '<S208>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal/Internal PreInt'
//  '<S209>' : 'joystick_enabled_matlab_node/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal/Forward_Path'
//  '<S210>' : 'joystick_enabled_matlab_node/Low-Level Controller/execute_command/cmdStatusID'
//  '<S211>' : 'joystick_enabled_matlab_node/Low-Level Controller/execute_command/commandExecuter'
//  '<S212>' : 'joystick_enabled_matlab_node/Low-Level Controller/execute_command/quatToEul'
//  '<S213>' : 'joystick_enabled_matlab_node/Subsystem Reference/derivedStateEstimates'
//  '<S214>' : 'joystick_enabled_matlab_node/Subsystem Reference/discreteTimeQuatPropagation'
//  '<S215>' : 'joystick_enabled_matlab_node/Subsystem Reference/dvl_reset'
//  '<S216>' : 'joystick_enabled_matlab_node/Subsystem Reference/eulToQuat'
//  '<S217>' : 'joystick_enabled_matlab_node/Subsystem Reference/quatToRotm'
//  '<S218>' : 'joystick_enabled_matlab_node/Subsystem Reference1/Blank Message'
//  '<S219>' : 'joystick_enabled_matlab_node/Subsystem Reference1/MATLAB Function'
//  '<S220>' : 'joystick_enabled_matlab_node/Subsystem Reference1/Publish'
//  '<S221>' : 'joystick_enabled_matlab_node/VR/Enabled Subsystem'
//  '<S222>' : 'joystick_enabled_matlab_node/dvl_reset_subscriber/Subscribe'
//  '<S223>' : 'joystick_enabled_matlab_node/dvl_reset_subscriber/Subscribe/Enabled Subsystem'
//  '<S224>' : 'joystick_enabled_matlab_node/joystick_heartbeat/MATLAB Function'
//  '<S225>' : 'joystick_enabled_matlab_node/joystick_heartbeat/Subscribe'
//  '<S226>' : 'joystick_enabled_matlab_node/joystick_heartbeat/Subscribe/Enabled Subsystem'
//  '<S227>' : 'joystick_enabled_matlab_node/joystick_output/MATLAB Function'
//  '<S228>' : 'joystick_enabled_matlab_node/joystick_output/Subscribe'
//  '<S229>' : 'joystick_enabled_matlab_node/joystick_output/Subscribe/Enabled Subsystem'
//  '<S230>' : 'joystick_enabled_matlab_node/joystick_to_pwm/joystick_inputs_to_body_forces'
//  '<S231>' : 'joystick_enabled_matlab_node/pwm_heartbeat_publisher/Blank Message1'
//  '<S232>' : 'joystick_enabled_matlab_node/pwm_heartbeat_publisher/Publish2'
//  '<S233>' : 'joystick_enabled_matlab_node/pwm_publisher/Publish'

#endif                                 // joystick_enabled_matlab_node_h_

//
// File trailer for generated code.
//
// [EOF]
//
