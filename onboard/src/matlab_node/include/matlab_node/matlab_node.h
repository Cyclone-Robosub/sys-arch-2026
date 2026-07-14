//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_node.h
//
// Code generated for Simulink model 'matlab_node'.
//
// Model version                  : 1.11
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jul  7 19:46:57 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef matlab_node_h_
#define matlab_node_h_
#include <cmath>
#include <cstdio>
#include <cstring>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "slros2_initialize.h"
#include "matlab_node_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Block signals (default storage)
struct B_matlab_node_T {
  SL_Bus_custom_interfaces_VR In1;     // '<S16>/In1'
  SL_Bus_custom_interfaces_VR rtb_SourceBlock_o2_m;
  SL_Bus_custom_interfaces_Imu In1_k;  // '<S12>/In1'
  SL_Bus_custom_interfaces_Imu rtb_SourceBlock_o2_k_c;
  real_T force_column_data[201];
  real_T b_varargin_1_data[201];
  real_T b_x_data[201];
  X_bus X_est;                         // '<S10>/derivedStateEstimates'
  char_T temp_char[256];
  SL_Bus_custom_interfaces_Debug debug_msg;// '<S3>/MATLAB Function'
  cmd_bus cmd;                         // '<S6>/cmdMsgToCmdBus'
  cell_wrap_1_matlab_node_T varargin_1[13];
  cell_wrap_1_matlab_node_T varargin_2[13];
  cell_wrap_1_matlab_node_T varargin_3[13];
  SL_Bus_custom_interfaces_Goal In1_d; // '<S206>/In1'
  SL_Bus_custom_interfaces_Goal rtb_SourceBlock_o2_k1_k;
  real_T TmpSignalConversionAtSFunct[16];// '<S3>/MATLAB Function'
  real_T c_a[16];
  real_T X_u[13];                      // '<S18>/commandExecuter'
  real_T Qe1[12];
  real_T rotm[9];
  real_T Cbi[9];
  real_T Cbi_c[9];                     // '<S10>/Transpose'
  real_T rtb_Cbi_tmp[9];
  real_T rtb_Cbi_tmp_b[9];
  real_T rtb_Cbi_tmp_tmp[9];
  real_T Cbi_p[9];
  real_T a[9];
  real_T b_a[9];
  SL_Bus_custom_interfaces_DRR In1_a;  // '<S11>/In1'
  real_T pwms[8];
  real_T FT_cmd_list[8];               // '<S17>/thrusterAllocator'
  real_T dv[8];
  SL_Bus_custom_interfaces_DRR rtb_SourceBlock_o2_g_c;
  real_T varargin_1_f[6];
  int32_T Cast[8];                     // '<S17>/Cast'
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S8>/Bus Creator3'
  real_T qinv[4];
  real_T qe_matlab[4];
  real_T qe_matlab_g[4];
  real_T dv1[4];
  real_T DiscreteTransferFcn[4];
  real_T dv2[4];
  real_T eps[3];
  real_T R_error[3];
  real_T eul_error[3];
  real_T eps_g[3];
  real_T dRb_u[3];                     // '<S17>/dRbSetpointInjector'
  real_T dRb_e[3];                     // '<S17>/rateInjector'
  real_T IntegralGain_a[3];            // '<S179>/Integral Gain'
  real_T dv3[3];
  real_T rtb_dvl_pos_m[3];
  real_T dv4[3];
  real_T x[3];
  real_T x_n[3];
  real_T x_p[3];
  char_T b_zeroDelimTopic[18];
  SL_Bus_custom_interfaces_Result result_msg;// '<S6>/statusKwdToBool'
  char_T varargin_2_l[17];
  char_T varargin_3_j[17];
  char_T b_zeroDelimTopic_d[17];
  char_T s[16];
  char_T x1[16];
  cell_wrap_1_matlab_node_T b;
  cell_wrap_1_matlab_node_T c;
  cell_wrap_1_matlab_node_T d;
  cell_wrap_1_matlab_node_T e;
  cell_wrap_1_matlab_node_T f;
  cell_wrap_1_matlab_node_T g;
  cell_wrap_1_matlab_node_T h;
  cell_wrap_1_matlab_node_T i;
  cell_wrap_1_matlab_node_T j;
  cell_wrap_1_matlab_node_T k;
  cell_wrap_1_matlab_node_T l;
  cell_wrap_1_matlab_node_T m;
  cell_wrap_1_matlab_node_T n;
  cell_wrap_1_matlab_node_T o;
  cell_wrap_1_matlab_node_T p;
  cell_wrap_1_matlab_node_T q;
  cell_wrap_1_matlab_node_T r;
  cell_wrap_1_matlab_node_T s_g;
  cell_wrap_1_matlab_node_T u;
  cell_wrap_1_matlab_node_T v;
  cell_wrap_1_matlab_node_T w;
  cell_wrap_1_matlab_node_T x_l;
  cell_wrap_1_matlab_node_T y;
  cell_wrap_1_matlab_node_T ab;
  cell_wrap_1_matlab_node_T bb;
  cell_wrap_1_matlab_node_T cb;
  char_T switch_expression[16];
  char_T b_zeroDelimTopic_dh[16];
  char_T b_zeroDelimTopic_dy[16];
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF deadline_l;
  sJ4ih70VmKcvCeguWN0mNVF deadline_o;
  sJ4ih70VmKcvCeguWN0mNVF deadline_b;
  real_T Ri_xy_e[2];
  char_T digits[10];
  real_T eta;
  real_T scale;
  real_T absxk;
  real_T b_t;
  real_T t;
  real_T b_scale;
  real_T b_absxk;
  real_T theta;
  real_T phi;
  real_T psi;
  real_T lower_voltage_index;
  real_T DigitalClock;                 // '<S18>/Digital Clock'
  real_T hold_timer;                   // '<S18>/commandExecuter'
  real_T eps_n;
  real_T rtb_delta_qe_idx_2;
  real_T rtb_delta_qe_idx_3;
  real_T qe_matlab_idx_1;
  real_T qe_matlab_idx_2;
  real_T qe_matlab_idx_3;
  real_T rtb_Integrator_p_idx_0;
  real_T rtb_FilterCoefficient_h_idx_0;
  real_T rtb_Integrator_p_idx_1;
  real_T rtb_Integrator_p_idx_2;
  real_T DiscreteTransferFcn_tmp_idx_2;
  real_T rtb_Filter_h_idx_0;
  real_T rtb_Filter_h_idx_1;
  real_T rtb_X_est_idx_0;
  real_T rtb_X_est_idx_1;
  real_T rtb_X_est_idx_2;
  real_T Qe1_b;
  real_T Qe1_l;
  real_T Qe1_h;
  real_T Qe1_bn;
  real_T rotm_tmp;
  real_T rtb_Cbi_tmp_tmp_d;
  real_T rtb_Cbi_tmp_tmp_e;
  real_T rtb_delta_qe_idx_2_tmp;
  real_T eta_b;
  real_T scale_j;
  real_T absxk_f;
  real_T b_t_a;
  real_T rotm_tmp_j;
  real_T rotm_tmp_jz;
  real_T eps_idx_0;
  real_T eps_idx_1;
  real_T eps_idx_2;
  real_T rotm_idx_0;
  real_T rotm_idx_8;
  real_T rotm_idx_4_tmp;
  real_T a_o;
  real_T b_a_n;
  real_T a_tmp;
  real_T varargin_1_data;
  real_T q_i;
  real_T eta_o;
  real_T scale_n;
  real_T absxk_m;
  real_T b_t_c;
  real_T rotm_tmp_m;
  real_T rotm_tmp_m3;
  real_T eps_idx_0_j;
  real_T eps_idx_1_h;
  real_T eps_idx_2_c;
  real_T rotm_idx_0_c;
  real_T rotm_idx_8_p;
  real_T eta_p;
  real_T y_a;
  real_T scale_e;
  real_T absxk_a;
  real_T b_t_as;
  real_T eps_idx_0_i;
  real_T eps_idx_1_l;
  real_T rotm_tmp_o;
  real_T rotm_tmp_o2;
  real_T rotm_tmp_i;
  real_T scale_f;
  boolean_T b_x[6];
  int32_T ret;
  int32_T pos;
  uint32_T int_part;
  uint32_T frac_part;
  uint32_T temp;
};

// Block states (default storage) for system '<Root>'
struct DW_matlab_node_T {
  ros_slros2_internal_block_Sub_T obj; // '<S202>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_e;// '<S4>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_e3;// '<S2>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_d;// '<S1>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_f;// '<S210>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o;// '<S209>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o3;// '<S207>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_h;// '<S15>/SinkBlock'
  real_T PositionIntegrator_DSTATE[3]; // '<S10>/Position Integrator'
  real_T VelocityIntegrator_DSTATE[3]; // '<S10>/Velocity Integrator'
  real_T UnitDelay2_DSTATE;            // '<S5>/Unit Delay2'
  real_T UnitDelay3_DSTATE;            // '<S5>/Unit Delay3'
  real_T DelayInput1_DSTATE;           // '<S21>/Delay Input1'
  real_T DiscreteTimeIntegrator_DSTATE[4];// '<S23>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn_states[4];// '<S17>/Discrete Transfer Fcn'
  real_T Integrator_DSTATE[3];         // '<S127>/Integrator'
  real_T Filter_DSTATE[3];             // '<S122>/Filter'
  real_T Integrator_DSTATE_l[3];       // '<S72>/Integrator'
  real_T Filter_DSTATE_e[3];           // '<S67>/Filter'
  real_T Integrator_DSTATE_f[3];       // '<S182>/Integrator'
  real_T Filter_DSTATE_k[3];           // '<S177>/Filter'
  real_T offset[3];                    // '<S10>/dvl_reset'
  real_T qk[4];                        // '<S10>/discreteTimeQuatPropagation'
  real_T hold_timer_start_time;        // '<S18>/commandExecuter'
  real_T idle_wp[6];                   // '<S18>/commandExecuter'
  real_T cmd_specific_wp[6];           // '<S18>/commandExecuter'
  real_T prior_action_id;              // '<S18>/commandExecuter'
  int8_T UnitDelay_DSTATE[4];          // '<S6>/Unit Delay'
  int8_T PositionIntegrator_PrevResetSta;// '<S10>/Position Integrator'
  int8_T VelocityIntegrator_PrevResetSta;// '<S10>/Velocity Integrator'
  int8_T DiscreteTimeIntegrator_PrevRese;// '<S23>/Discrete-Time Integrator'
  int8_T Integrator_PrevResetState;    // '<S127>/Integrator'
  int8_T Filter_PrevResetState;        // '<S122>/Filter'
  int8_T Integrator_PrevResetState_l;  // '<S72>/Integrator'
  int8_T Filter_PrevResetState_b;      // '<S67>/Filter'
  int8_T Integrator_PrevResetState_i;  // '<S182>/Integrator'
  int8_T Filter_PrevResetState_n;      // '<S177>/Filter'
  uint8_T PositionIntegrator_IC_LOADING;// '<S10>/Position Integrator'
  uint8_T VelocityIntegrator_IC_LOADING;// '<S10>/Velocity Integrator'
  boolean_T start_new_cmd_flag;        // '<Root>/Data Store Memory1'
  boolean_T reset_dvl_pos;             // '<Root>/Data Store Memory10'
  boolean_T joystick_mode_enabled_flag;// '<Root>/Data Store Memory3'
  boolean_T mission_is_started;        // '<Root>/Data Store Memory4'
  boolean_T prior_flag;                // '<S10>/dvl_reset'
  boolean_T qk_not_empty;              // '<S10>/discreteTimeQuatPropagation'
  boolean_T hold_timer_start_time_not_empty;// '<S18>/commandExecuter'
  boolean_T idle_wp_not_empty;         // '<S18>/commandExecuter'
  boolean_T cmd_specific_wp_not_empty; // '<S18>/commandExecuter'
  boolean_T prior_action_id_not_empty; // '<S17>/guidanceLaw'
};

// Constant parameters (default storage)
struct ConstP_matlab_node_T {
  // Expression: FF_maneuvers
  //  Referenced by: '<S17>/trickFTListInjector'

  FF_maneuvers_bus trickFTListInjector_FF_maneuver;

  // Computed Parameter: Constant_Value_e
  //  Referenced by: '<S208>/Constant'

  SL_Bus_std_msgs_Empty Constant_Value_e;

  // Expression: ccw_force
  //  Referenced by: '<S24>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_force[1206];

  // Expression: ccw_pwm
  //  Referenced by: '<S24>/forceToPWMCalculator'

  real_T forceToPWMCalculator_ccw_pwm[201];

  // Expression: cw_force
  //  Referenced by: '<S24>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_force[1206];

  // Expression: cw_pwm
  //  Referenced by: '<S24>/forceToPWMCalculator'

  real_T forceToPWMCalculator_cw_pwm[201];

  // Expression: voltage
  //  Referenced by: '<S24>/forceToPWMCalculator'

  real_T forceToPWMCalculator_voltage[6];

  // Expression: invMT_wrench
  //  Referenced by: '<S17>/Constant'

  real_T Constant_Value_i[24];

  // Expression: invFT_wrench
  //  Referenced by: '<S17>/Constant1'

  real_T Constant1_Value[24];

  // Expression: qib_PID.Kp
  //  Referenced by: '<S17>/Gain1'

  real_T Gain1_Gain[4];

  // Expression: P
  //  Referenced by: '<S132>/Proportional Gain'

  real_T ProportionalGain_Gain[3];

  // Expression: gi
  //  Referenced by: '<S10>/Constant'

  real_T Constant_Value_ep[3];

  // Expression: Cbimu_meas
  //  Referenced by: '<S10>/Constant1'

  real_T Constant1_Value_o[9];
};

// Real-time Model Data Structure
struct tag_RTM_matlab_node_T {
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
extern const ConstP_matlab_node_T matlab_node_ConstP;

// External function called from main
#ifdef __cplusplus

extern "C"
{

#endif

  extern void matlab_node_SetEventsForThisBaseStep(boolean_T *eventFlags,
    RT_MODEL_matlab_node_T *const matlab_node_M);

#ifdef __cplusplus

}

#endif

// Class declaration for model matlab_node
class matlab_node final
{
  // public data and function members
 public:
  // Copy Constructor
  matlab_node(matlab_node const&) = delete;

  // Assignment Operator
  matlab_node& operator= (matlab_node const&) & = delete;

  // Move Constructor
  matlab_node(matlab_node &&) = delete;

  // Move Assignment Operator
  matlab_node& operator= (matlab_node &&) = delete;

  // Real-Time Model get method
  RT_MODEL_matlab_node_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step0();

  // model step function
  void step1();

  // model terminate function
  void terminate();

  // Constructor
  matlab_node();

  // Destructor
  ~matlab_node();

  // private data and function members
 private:
  // Block signals
  B_matlab_node_T matlab_node_B;

  // Block states
  DW_matlab_node_T matlab_node_DW;

  // private member function(s) for subsystem '<Root>'
  void matlab_node_wrapToPi(real_T *lambda);
  void matlab_node_eulToQuat_c(const real_T Eul[3], real_T qib[4]);
  void matlab_nod_executeDurationTrick(real_T cmd_hold_time, const int8_T
    cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
    real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
    real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
    cmd_status[4], real_T *hold_timer, real_T X_u[13]);
  real_T matlab_node_norm(const real_T x[2]);
  void matlab_node_quatToEul(const real_T qib[4], real_T Eul[3]);
  void matlab_node_eulToRotm(const real_T Eul[3], real_T rotm[9]);
  void matlab_node_rotmToQuat(const real_T rotm[9], real_T qib[4]);
  void matlab_node_eulToQuat(const real_T Eul[3], real_T qib[4]);
  boolean_T matlab_node_isequal(const char_T varargin_1[16]);
  boolean_T matlab_node_strcmp(const char_T b[16]);
  boolean_T matlab_node_strcmp_n(const char_T b[16]);
  boolean_T matlab_node_strcmp_nj(const char_T b[16]);
  void matlab_node_minimum(const real_T x[6], real_T *ex, int32_T *idx);
  void matlab_node_minimum_d(const real_T x_data[], const int32_T *x_size,
    real_T *ex, int32_T *idx);
  void matlab_no_Publisher_setupImpl_g(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab_Subscriber_setupImpl_gzo(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_n_Subscriber_setupImpl_g(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab__Subscriber_setupImpl_gz(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab_nod_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void matlab__Publisher_setupImpl_gzo(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab_node_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  void matlab_n_Publisher_setupImpl_gz(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_matlab_node_T matlab_node_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Display' : Unused code path elimination
//  Block '<Root>/Display1' : Unused code path elimination
//  Block '<S17>/Discrete-Time Integrator' : Unused code path elimination
//  Block '<S17>/Scope1' : Unused code path elimination
//  Block '<S17>/Scope4' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S6>/Scope1' : Unused code path elimination
//  Block '<S6>/Scope2' : Unused code path elimination
//  Block '<S17>/Gain' : Eliminated nontunable gain of 1
//  Block '<S17>/Gain3' : Eliminated nontunable gain of 1
//  Block '<S17>/Gain4' : Eliminated nontunable gain of 1


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
//  '<Root>' : 'matlab_node'
//  '<S1>'   : 'matlab_node/DRR'
//  '<S2>'   : 'matlab_node/IMU'
//  '<S3>'   : 'matlab_node/Subsystem Reference1'
//  '<S4>'   : 'matlab_node/VR'
//  '<S5>'   : 'matlab_node/low_level_controller_cgn'
//  '<S6>'   : 'matlab_node/mission_manager_interface_cgn'
//  '<S7>'   : 'matlab_node/pwm_heartbeat_publisher'
//  '<S8>'   : 'matlab_node/pwm_publisher'
//  '<S9>'   : 'matlab_node/sensorRosMsgToBus'
//  '<S10>'  : 'matlab_node/state_estimator_cgn'
//  '<S11>'  : 'matlab_node/DRR/Enabled Subsystem'
//  '<S12>'  : 'matlab_node/IMU/Enabled Subsystem'
//  '<S13>'  : 'matlab_node/Subsystem Reference1/Blank Message'
//  '<S14>'  : 'matlab_node/Subsystem Reference1/MATLAB Function'
//  '<S15>'  : 'matlab_node/Subsystem Reference1/Publish'
//  '<S16>'  : 'matlab_node/VR/Enabled Subsystem'
//  '<S17>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn'
//  '<S18>'  : 'matlab_node/low_level_controller_cgn/execute_command_cgn'
//  '<S19>'  : 'matlab_node/low_level_controller_cgn/quatToEul'
//  '<S20>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller'
//  '<S21>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Detect Change'
//  '<S22>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb'
//  '<S23>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem'
//  '<S24>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem Reference1'
//  '<S25>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller'
//  '<S26>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRbSetpointInjector'
//  '<S27>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/deltaQuatError'
//  '<S28>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/guidanceLaw'
//  '<S29>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/quatInjector'
//  '<S30>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/quatPID'
//  '<S31>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/quatToEul1'
//  '<S32>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/quatToRotm'
//  '<S33>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/rateInjector'
//  '<S34>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/thrusterAllocator'
//  '<S35>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/trickFTListInjector'
//  '<S36>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup'
//  '<S37>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/D Gain'
//  '<S38>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/External Derivative'
//  '<S39>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter'
//  '<S40>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter ICs'
//  '<S41>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/I Gain'
//  '<S42>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain'
//  '<S43>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain Fdbk'
//  '<S44>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator'
//  '<S45>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator ICs'
//  '<S46>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Copy'
//  '<S47>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Gain'
//  '<S48>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/P Copy'
//  '<S49>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Parallel P Gain'
//  '<S50>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Reset Signal'
//  '<S51>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation'
//  '<S52>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation Fdbk'
//  '<S53>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum'
//  '<S54>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum Fdbk'
//  '<S55>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode'
//  '<S56>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode Sum'
//  '<S57>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Integral'
//  '<S58>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Ngain'
//  '<S59>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/postSat Signal'
//  '<S60>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preInt Signal'
//  '<S61>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preSat Signal'
//  '<S62>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S63>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S64>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S65>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/D Gain/Internal Parameters'
//  '<S66>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/External Derivative/Error'
//  '<S67>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter/Disc. Forward Euler Filter'
//  '<S68>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Filter ICs/Internal IC - Filter'
//  '<S69>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/I Gain/Internal Parameters'
//  '<S70>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain/Passthrough'
//  '<S71>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Ideal P Gain Fdbk/Disabled'
//  '<S72>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator/Discrete'
//  '<S73>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Integrator ICs/Internal IC'
//  '<S74>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Copy/Disabled'
//  '<S75>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/N Gain/Internal Parameters'
//  '<S76>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/P Copy/Disabled'
//  '<S77>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Parallel P Gain/Internal Parameters'
//  '<S78>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Reset Signal/External Reset'
//  '<S79>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation/Enabled'
//  '<S80>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Saturation Fdbk/Disabled'
//  '<S81>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum/Sum_PID'
//  '<S82>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Sum Fdbk/Disabled'
//  '<S83>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode/Disabled'
//  '<S84>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tracking Mode Sum/Passthrough'
//  '<S85>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S86>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/Tsamp - Ngain/Passthrough'
//  '<S87>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/postSat Signal/Forward_Path'
//  '<S88>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preInt Signal/Internal PreInt'
//  '<S89>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Angular Velocity Controller/preSat Signal/Forward_Path'
//  '<S90>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller'
//  '<S91>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup'
//  '<S92>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/D Gain'
//  '<S93>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/External Derivative'
//  '<S94>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter'
//  '<S95>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter ICs'
//  '<S96>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/I Gain'
//  '<S97>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain'
//  '<S98>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain Fdbk'
//  '<S99>'  : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator'
//  '<S100>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator ICs'
//  '<S101>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Copy'
//  '<S102>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Gain'
//  '<S103>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/P Copy'
//  '<S104>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Parallel P Gain'
//  '<S105>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Reset Signal'
//  '<S106>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation'
//  '<S107>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation Fdbk'
//  '<S108>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum'
//  '<S109>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum Fdbk'
//  '<S110>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode'
//  '<S111>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode Sum'
//  '<S112>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Integral'
//  '<S113>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Ngain'
//  '<S114>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/postSat Signal'
//  '<S115>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preInt Signal'
//  '<S116>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preSat Signal'
//  '<S117>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S118>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S119>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S120>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/D Gain/Internal Parameters'
//  '<S121>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/External Derivative/Error'
//  '<S122>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S123>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S124>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/I Gain/Internal Parameters'
//  '<S125>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain/Passthrough'
//  '<S126>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S127>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator/Discrete'
//  '<S128>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Integrator ICs/Internal IC'
//  '<S129>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Copy/Disabled'
//  '<S130>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/N Gain/Internal Parameters'
//  '<S131>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/P Copy/Disabled'
//  '<S132>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S133>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Reset Signal/External Reset'
//  '<S134>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation/Enabled'
//  '<S135>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Saturation Fdbk/Disabled'
//  '<S136>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum/Sum_PID'
//  '<S137>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Sum Fdbk/Disabled'
//  '<S138>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode/Disabled'
//  '<S139>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S140>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S141>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S142>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/postSat Signal/Forward_Path'
//  '<S143>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preInt Signal/Internal PreInt'
//  '<S144>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/PID for Rb/PID Controller/preSat Signal/Forward_Path'
//  '<S145>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/Subsystem Reference1/forceToPWMCalculator'
//  '<S146>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup'
//  '<S147>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/D Gain'
//  '<S148>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/External Derivative'
//  '<S149>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter'
//  '<S150>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter ICs'
//  '<S151>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/I Gain'
//  '<S152>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain'
//  '<S153>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain Fdbk'
//  '<S154>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator'
//  '<S155>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator ICs'
//  '<S156>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Copy'
//  '<S157>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Gain'
//  '<S158>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/P Copy'
//  '<S159>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Parallel P Gain'
//  '<S160>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Reset Signal'
//  '<S161>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation'
//  '<S162>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation Fdbk'
//  '<S163>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum'
//  '<S164>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum Fdbk'
//  '<S165>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode'
//  '<S166>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode Sum'
//  '<S167>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Integral'
//  '<S168>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Ngain'
//  '<S169>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/postSat Signal'
//  '<S170>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preInt Signal'
//  '<S171>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preSat Signal'
//  '<S172>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S173>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S174>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S175>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/D Gain/Internal Parameters'
//  '<S176>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/External Derivative/Error'
//  '<S177>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter/Disc. Forward Euler Filter'
//  '<S178>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Filter ICs/Internal IC - Filter'
//  '<S179>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/I Gain/Internal Parameters'
//  '<S180>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain/Passthrough'
//  '<S181>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Ideal P Gain Fdbk/Disabled'
//  '<S182>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator/Discrete'
//  '<S183>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Integrator ICs/Internal IC'
//  '<S184>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Copy/Disabled'
//  '<S185>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/N Gain/Internal Parameters'
//  '<S186>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/P Copy/Disabled'
//  '<S187>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Parallel P Gain/Internal Parameters'
//  '<S188>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Reset Signal/External Reset'
//  '<S189>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation/Enabled'
//  '<S190>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Saturation Fdbk/Disabled'
//  '<S191>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum/Sum_PID'
//  '<S192>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Sum Fdbk/Disabled'
//  '<S193>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode/Disabled'
//  '<S194>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tracking Mode Sum/Passthrough'
//  '<S195>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S196>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/Tsamp - Ngain/Passthrough'
//  '<S197>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/postSat Signal/Forward_Path'
//  '<S198>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preInt Signal/Internal PreInt'
//  '<S199>' : 'matlab_node/low_level_controller_cgn/cascaded_pid_controller_cgn/dRb Controller/preSat Signal/Forward_Path'
//  '<S200>' : 'matlab_node/low_level_controller_cgn/execute_command_cgn/commandExecuter'
//  '<S201>' : 'matlab_node/mission_manager_interface_cgn/MATLAB Function'
//  '<S202>' : 'matlab_node/mission_manager_interface_cgn/Subscribe'
//  '<S203>' : 'matlab_node/mission_manager_interface_cgn/Subsystem'
//  '<S204>' : 'matlab_node/mission_manager_interface_cgn/cmdMsgToCmdBus'
//  '<S205>' : 'matlab_node/mission_manager_interface_cgn/statusKwdToBool'
//  '<S206>' : 'matlab_node/mission_manager_interface_cgn/Subscribe/Enabled Subsystem'
//  '<S207>' : 'matlab_node/mission_manager_interface_cgn/Subsystem/Publish'
//  '<S208>' : 'matlab_node/pwm_heartbeat_publisher/Blank Message1'
//  '<S209>' : 'matlab_node/pwm_heartbeat_publisher/Publish2'
//  '<S210>' : 'matlab_node/pwm_publisher/Publish'
//  '<S211>' : 'matlab_node/state_estimator_cgn/derivedStateEstimates'
//  '<S212>' : 'matlab_node/state_estimator_cgn/discreteTimeQuatPropagation'
//  '<S213>' : 'matlab_node/state_estimator_cgn/dvl_reset'
//  '<S214>' : 'matlab_node/state_estimator_cgn/eulToQuat'
//  '<S215>' : 'matlab_node/state_estimator_cgn/quatToRotm'

#endif                                 // matlab_node_h_

//
// File trailer for generated code.
//
// [EOF]
//
