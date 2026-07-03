//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Mission_Manager_CGN.h
//
// Code generated for Simulink model 'Mission_Manager_CGN'.
//
// Model version                  : 1.131
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jun 30 20:17:55 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef Mission_Manager_CGN_h_
#define Mission_Manager_CGN_h_
#include <cmath>
#include <cstdio>
#include <cstring>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "slros2_initialize.h"
#include "Mission_Manager_CGN_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Block signals (default storage)
struct B_Mission_Manager_CGN_T {
  SL_Bus_custom_interfaces_VR In1;     // '<S205>/In1'
  SL_Bus_custom_interfaces_VR rtb_SourceBlock_o2_m;
  SL_Bus_custom_interfaces_Imu In1_i;  // '<S17>/In1'
  SL_Bus_custom_interfaces_Imu rtb_SourceBlock_o2_o_c;
  real_T force_column_data[201];
  real_T b_varargin_1_data[201];
  real_T b_x_data[201];
  X_bus X_est;                         // '<S5>/derivedStateEstimates'
  cmd_bus cmd;                         // '<S1>/cmdMsgToCmdBus'
  cell_wrap_1_Mission_Manager_C_T varargin_1[13];
  cell_wrap_1_Mission_Manager_C_T varargin_2[13];
  cell_wrap_1_Mission_Manager_C_T varargin_3[13];
  SL_Bus_custom_interfaces_Goal In1_j; // '<S14>/In1'
  SL_Bus_custom_interfaces_Goal rtb_SourceBlock_o2_i_k;
  real_T c_a[16];
  real_T X_u[13];                      // '<S19>/commandExecuter'
  real_T Qe1[12];
  real_T rotm[9];
  real_T Cbi[9];
  real_T Cbi_c[9];                     // '<S5>/Transpose'
  real_T rtb_Cbi_tmp[9];
  real_T rtb_Cbi_tmp_b[9];
  real_T rtb_Cbi_tmp_tmp[9];
  real_T Cbi_p[9];
  real_T a[9];
  real_T b_a[9];
  SL_Bus_custom_interfaces_DRR In1_c;  // '<S16>/In1'
  real_T pwms[8];
  real_T FT_cmd_list[8];               // '<S18>/thrusterAllocator'
  real_T dv[8];
  SL_Bus_custom_interfaces_DRR rtb_SourceBlock_o2_d_c;
  real_T varargin_1_f[6];
  int32_T Cast[8];                     // '<S18>/Cast'
  SL_Bus_custom_interfaces_Pwms BusCreator3;// '<S8>/Bus Creator3'
  real_T qinv[4];
  real_T qe_matlab[4];
  real_T qib_int_u[4];                 // '<S18>/guidanceLaw'
  real_T dv1[4];
  real_T DiscreteTransferFcn[4];
  real_T dv2[4];
  real_T eps[3];
  real_T R_error[3];
  real_T eul_error[3];
  real_T eps_g[3];
  real_T dRb_u[3];                     // '<S18>/dRbSetpointInjector'
  real_T dRb_e[3];                     // '<S18>/rateInjector'
  real_T dv3[3];
  real_T rtb_dvl_pos_g[3];
  real_T dv4[3];
  real_T x[3];
  real_T x_m[3];
  real_T x_n[3];
  SL_Bus_custom_interfaces_Result result_msg;// '<S1>/statusKwdToBool'
  char_T varargin_2_p[17];
  char_T varargin_3_l[17];
  char_T switch_expression[16];
  char_T x1[16];
  cell_wrap_1_Mission_Manager_C_T b;
  cell_wrap_1_Mission_Manager_C_T c;
  cell_wrap_1_Mission_Manager_C_T d;
  cell_wrap_1_Mission_Manager_C_T e;
  cell_wrap_1_Mission_Manager_C_T f;
  cell_wrap_1_Mission_Manager_C_T g;
  cell_wrap_1_Mission_Manager_C_T h;
  cell_wrap_1_Mission_Manager_C_T i;
  cell_wrap_1_Mission_Manager_C_T j;
  cell_wrap_1_Mission_Manager_C_T k;
  cell_wrap_1_Mission_Manager_C_T l;
  cell_wrap_1_Mission_Manager_C_T m;
  cell_wrap_1_Mission_Manager_C_T n;
  cell_wrap_1_Mission_Manager_C_T o;
  cell_wrap_1_Mission_Manager_C_T p;
  cell_wrap_1_Mission_Manager_C_T q;
  cell_wrap_1_Mission_Manager_C_T r;
  cell_wrap_1_Mission_Manager_C_T s;
  cell_wrap_1_Mission_Manager_C_T u;
  cell_wrap_1_Mission_Manager_C_T v;
  cell_wrap_1_Mission_Manager_C_T w;
  cell_wrap_1_Mission_Manager_C_T x_j;
  cell_wrap_1_Mission_Manager_C_T y;
  cell_wrap_1_Mission_Manager_C_T ab;
  cell_wrap_1_Mission_Manager_C_T bb;
  cell_wrap_1_Mission_Manager_C_T cb;
  char_T switch_expression_d[16];
  real_T Ri_xy_e[2];
  real_T dv5[2];
  real_T dv6[2];
  real_T dv7[2];
  real_T dv8[2];
  real_T dv9[2];
  real_T dv10[2];
  real_T eta;
  real_T scale;
  real_T absxk;
  real_T b_t;
  real_T t;
  real_T b_scale;
  real_T b_absxk;
  real_T psi;
  real_T phi;
  real_T lower_voltage_index;
  real_T upper_voltage_index;
  real_T lower_force_index;
  real_T DigitalClock;                 // '<S19>/Digital Clock'
  real_T rtb_FT_cmd_list_g;
  real_T rtb_IntegralGain_b_l;
  real_T rtb_Integrator_f_idx_0;
  real_T rtb_IntegralGain_b_idx_0;
  real_T rtb_FilterCoefficient_g_idx_0;
  real_T rtb_Integrator_f_idx_1;
  real_T rtb_IntegralGain_b_idx_1;
  real_T rtb_Integrator_f_idx_2;
  real_T rtb_Filter_h_idx_0;
  real_T rtb_Filter_h_idx_1;
  real_T rtb_X_est_idx_0;
  real_T rtb_Cbi_tmp_tmp_d;
  real_T force_column_tmp;
  real_T eta_d;
  real_T scale_l;
  real_T absxk_o;
  real_T b_t_b;
  real_T rotm_tmp;
  real_T rotm_tmp_n;
  real_T eps_idx_0;
  real_T eps_idx_1;
  real_T eps_idx_2;
  real_T rotm_idx_0;
  real_T rotm_idx_8;
  real_T rotm_idx_4_tmp;
  real_T a_b;
  real_T b_a_l;
  real_T varargin_1_data;
  real_T q_h;
  real_T eta_b;
  real_T scale_d;
  real_T absxk_e;
  real_T b_t_bj;
  real_T rotm_tmp_j;
  real_T rotm_tmp_f;
  real_T eps_idx_0_a;
  real_T eps_idx_1_j;
  real_T eps_idx_2_j;
  real_T rotm_idx_0_o;
  real_T rotm_idx_8_n;
  real_T rotm_idx_4_tmp_i;
  real_T eta_o;
  real_T y_n;
  real_T scale_m;
  real_T absxk_c;
  real_T b_t_m;
  real_T eps_idx_0_m;
  real_T eps_idx_1_ja;
  real_T eps_idx_2_h;
  real_T rotm_tmp_c;
  real_T rotm_tmp_ct;
  real_T rotm_tmp_p;
  real_T rotm_tmp_p5;
  real_T rotm_tmp_a;
  boolean_T b_x[6];
  char_T switch_expression_e[4];
  int32_T b_index;
  int32_T iindx;
  int32_T i_a;
  int32_T vectorUB;
  int32_T loop_ub;
  int32_T b_varargin_1_size;
  int32_T force_column_size_idx_0;
  int32_T c_ret;
  int32_T d_ret;
  int32_T idx;
  int32_T b_k;
  int32_T c_k;
  int32_T i_as;
  int32_T trueCount;
  int32_T i_i;
  int32_T i1;
  int32_T idx_l;
  int32_T b_k_o;
  int32_T c_k_o;
  int32_T idx_i;
  int32_T b_k_f;
  int32_T c_k_i;
  int32_T i2;
  int32_T i3;
  int8_T rtb_Switch1_f;
  int8_T rtb_Switch1_idx_0;
  int8_T rtb_Switch1_idx_1;
  int8_T i4;
  int8_T i5;
  uint8_T integrator_reset;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_g;
  boolean_T b_varargout_1_c;
  boolean_T rtb_RelationalOperator_f_idx_0;
  boolean_T rtb_RelationalOperator_f_idx_1;
  boolean_T rtb_RelationalOperator_f_idx_2;
  boolean_T rtb_RelationalOperator_o_o;
  boolean_T b_l;
};

// Block states (default storage) for system '<Root>'
struct DW_Mission_Manager_CGN_T {
  ros_slros2_internal_block_Sub_T obj; // '<S6>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_p;// '<S3>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_b;// '<S2>/SourceBlock'
  ros_slros2_internal_block_Sub_T obj_m;// '<S10>/SourceBlock'
  ros_slros2_internal_block_Pub_T obj_j;// '<S208>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_o;// '<S207>/SinkBlock'
  ros_slros2_internal_block_Pub_T obj_op;// '<S15>/SinkBlock'
  real_T UnitDelay_DSTATE;             // '<S4>/Unit Delay'
  real_T UnitDelay1_DSTATE;            // '<S4>/Unit Delay1'
  real_T PositionIntegrator_DSTATE[3]; // '<S5>/Position Integrator'
  real_T VelocityIntegrator_DSTATE[3]; // '<S5>/Velocity Integrator'
  real_T DelayInput1_DSTATE;           // '<S21>/Delay Input1'
  real_T DiscreteTimeIntegrator_DSTATE[4];// '<S23>/Discrete-Time Integrator'
  real_T DiscreteTransferFcn_states[4];// '<S18>/Discrete Transfer Fcn'
  real_T Integrator_DSTATE[3];         // '<S126>/Integrator'
  real_T Filter_DSTATE[3];             // '<S121>/Filter'
  real_T Integrator_DSTATE_c[3];       // '<S71>/Integrator'
  real_T Filter_DSTATE_g[3];           // '<S66>/Filter'
  real_T Integrator_DSTATE_b[3];       // '<S181>/Integrator'
  real_T Filter_DSTATE_m[3];           // '<S176>/Filter'
  real_T offset[3];                    // '<S5>/dvl_reset'
  real_T qk[4];                        // '<S5>/discreteTimeQuatPropagation'
  real_T hold_timer_start_time;        // '<S19>/commandExecuter'
  real_T idle_wp[6];                   // '<S19>/commandExecuter'
  real_T cmd_specific_wp[6];           // '<S19>/commandExecuter'
  real_T prior_action_id;              // '<S19>/commandExecuter'
  int8_T UnitDelay_DSTATE_g[4];        // '<S1>/Unit Delay'
  int8_T PositionIntegrator_PrevResetSta;// '<S5>/Position Integrator'
  int8_T VelocityIntegrator_PrevResetSta;// '<S5>/Velocity Integrator'
  int8_T DiscreteTimeIntegrator_PrevRese;// '<S23>/Discrete-Time Integrator'
  int8_T Integrator_PrevResetState;    // '<S126>/Integrator'
  int8_T Filter_PrevResetState;        // '<S121>/Filter'
  int8_T Integrator_PrevResetState_i;  // '<S71>/Integrator'
  int8_T Filter_PrevResetState_g;      // '<S66>/Filter'
  int8_T Integrator_PrevResetState_a;  // '<S181>/Integrator'
  int8_T Filter_PrevResetState_l;      // '<S176>/Filter'
  uint8_T PositionIntegrator_IC_LOADING;// '<S5>/Position Integrator'
  uint8_T VelocityIntegrator_IC_LOADING;// '<S5>/Velocity Integrator'
  boolean_T joystick_mode_enabled_flag;// '<Root>/Data Store Memory'
  boolean_T prior_flag;                // '<S5>/dvl_reset'
  boolean_T qk_not_empty;              // '<S5>/discreteTimeQuatPropagation'
  boolean_T hold_timer_start_time_not_empty;// '<S19>/commandExecuter'
  boolean_T idle_wp_not_empty;         // '<S19>/commandExecuter'
  boolean_T cmd_specific_wp_not_empty; // '<S19>/commandExecuter'
  boolean_T prior_action_id_not_empty; // '<S18>/guidanceLaw'
};

// Constant parameters (default storage)
struct ConstP_Mission_Manager_CGN_T {
  // Expression: FF_maneuvers
  //  Referenced by: '<S18>/trickFTListInjector'

  FF_maneuvers_bus trickFTListInjector_FF_maneuver;

  // Computed Parameter: Constant_Value
  //  Referenced by: '<S206>/Constant'

  SL_Bus_std_msgs_Empty Constant_Value;

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
  //  Referenced by: '<S18>/Constant'

  real_T Constant_Value_e[24];

  // Expression: invFT_wrench
  //  Referenced by: '<S18>/Constant1'

  real_T Constant1_Value[24];

  // Expression: qib_PID.Kp
  //  Referenced by: '<S18>/Gain1'

  real_T Gain1_Gain[4];

  // Expression: P
  //  Referenced by: '<S131>/Proportional Gain'

  real_T ProportionalGain_Gain[3];

  // Expression: gi
  //  Referenced by: '<S5>/Constant'

  real_T Constant_Value_n[3];

  // Expression: Cbimu_meas
  //  Referenced by: '<S5>/Constant1'

  real_T Constant1_Value_n[9];
};

// Real-time Model Data Structure
struct tag_RTM_Mission_Manager_CGN_T {
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
extern const ConstP_Mission_Manager_CGN_T Mission_Manager_CGN_ConstP;

// Class declaration for model Mission_Manager_CGN
class Mission_Manager_CGN final
{
  // public data and function members
 public:
  // Copy Constructor
  Mission_Manager_CGN(Mission_Manager_CGN const&) = delete;

  // Assignment Operator
  Mission_Manager_CGN& operator= (Mission_Manager_CGN const&) & = delete;

  // Move Constructor
  Mission_Manager_CGN(Mission_Manager_CGN &&) = delete;

  // Move Assignment Operator
  Mission_Manager_CGN& operator= (Mission_Manager_CGN &&) = delete;

  // Real-Time Model get method
  RT_MODEL_Mission_Manager_CGN_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  Mission_Manager_CGN();

  // Destructor
  ~Mission_Manager_CGN();

  // private data and function members
 private:
  // Block signals
  B_Mission_Manager_CGN_T Mission_Manager_CGN_B;

  // Block states
  DW_Mission_Manager_CGN_T Mission_Manager_CGN_DW;

  // private member function(s) for subsystem '<Root>'
  real_T Mission_Manager_C_rt_atan2d_snf(real_T u0, real_T u1);
  void Mission_Manager_CGN_wrapToPi(real_T *lambda);
  void Mission_Manager_CGN_eulToQuat_k(const real_T Eul[3], real_T qib[4]);
  void Mission_Ma_executeDurationTrick(real_T cmd_hold_time, const int8_T
    cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
    real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
    real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
    cmd_status[4], real_T *hold_timer, real_T X_u[13]);
  real_T Mission_Manager_CGN_norm(const real_T x[2]);
  void Mission_Manager_CGN_quatToEul(const real_T qib[4], real_T Eul[3]);
  void Mission_Manager_CGN_eulToRotm(const real_T Eul[3], real_T rotm[9]);
  void Mission_Manager_CGN_rotmToQuat(const real_T rotm[9], real_T qib[4]);
  void Mission_Manager_CGN_eulToQuat(const real_T Eul[3], real_T qib[4]);
  boolean_T Mission_Manager_CGN_isequal(const char_T varargin_1[16]);
  boolean_T Mission_Manager_CGN_strcmp(const char_T b[16]);
  boolean_T Mission_Manager_CGN_strcmp_j(const char_T b[16]);
  boolean_T Mission_Manager_CGN_strcmp_jy(const char_T b[16]);
  void Mission_Manager_CGN_minimum(const real_T x[6], real_T *ex, int32_T *idx);
  void Mission_Manager_CGN_minimum_m(const real_T x_data[], const int32_T
    *x_size, real_T *ex, int32_T *idx);
  void Mission_Man_Publisher_setupImpl(const ros_slros2_internal_block_Pub_T
    *obj);
  void Mission_Ma_Subscriber_setupImpl(const ros_slros2_internal_block_Sub_T
    *obj);
  void Mission_Subscriber_setupImpl_be(const ros_slros2_internal_block_Sub_T
    *obj);
  void Missio_Subscriber_setupImpl_bea(const ros_slros2_internal_block_Sub_T
    *obj);
  void Mission__Subscriber_setupImpl_b(const ros_slros2_internal_block_Sub_T
    *obj);
  void Mission__Publisher_setupImpl_be(const ros_slros2_internal_block_Pub_T
    *obj);
  void Mission_M_Publisher_setupImpl_b(const ros_slros2_internal_block_Pub_T
    *obj);

  // Real-Time Model
  RT_MODEL_Mission_Manager_CGN_T Mission_Manager_CGN_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S18>/Gain' : Eliminated nontunable gain of 1
//  Block '<S18>/Gain3' : Eliminated nontunable gain of 1
//  Block '<S18>/Gain4' : Eliminated nontunable gain of 1
//  Block '<S19>/Zero-Order Hold' : Eliminated since input and output rates are identical


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
//  '<Root>' : 'Mission_Manager_CGN'
//  '<S1>'   : 'Mission_Manager_CGN/ '
//  '<S2>'   : 'Mission_Manager_CGN/DRR'
//  '<S3>'   : 'Mission_Manager_CGN/IMU'
//  '<S4>'   : 'Mission_Manager_CGN/Low-Level Controller'
//  '<S5>'   : 'Mission_Manager_CGN/Subsystem Reference'
//  '<S6>'   : 'Mission_Manager_CGN/VR'
//  '<S7>'   : 'Mission_Manager_CGN/pwm_heartbeat_publisher'
//  '<S8>'   : 'Mission_Manager_CGN/pwm_publisher'
//  '<S9>'   : 'Mission_Manager_CGN/sensorRosMsgToBus'
//  '<S10>'  : 'Mission_Manager_CGN/ /Subscribe'
//  '<S11>'  : 'Mission_Manager_CGN/ /Subsystem'
//  '<S12>'  : 'Mission_Manager_CGN/ /cmdMsgToCmdBus'
//  '<S13>'  : 'Mission_Manager_CGN/ /statusKwdToBool'
//  '<S14>'  : 'Mission_Manager_CGN/ /Subscribe/Enabled Subsystem'
//  '<S15>'  : 'Mission_Manager_CGN/ /Subsystem/Publish'
//  '<S16>'  : 'Mission_Manager_CGN/DRR/Enabled Subsystem'
//  '<S17>'  : 'Mission_Manager_CGN/IMU/Enabled Subsystem'
//  '<S18>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller'
//  '<S19>'  : 'Mission_Manager_CGN/Low-Level Controller/execute_command'
//  '<S20>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller'
//  '<S21>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Detect Change'
//  '<S22>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb'
//  '<S23>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Subsystem'
//  '<S24>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1'
//  '<S25>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller'
//  '<S26>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRbSetpointInjector'
//  '<S27>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/deltaQuatError'
//  '<S28>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/guidanceLaw'
//  '<S29>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/quatInjector'
//  '<S30>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/quatPID'
//  '<S31>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/quatToRotm'
//  '<S32>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/rateInjector'
//  '<S33>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/thrusterAllocator'
//  '<S34>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/trickFTListInjector'
//  '<S35>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup'
//  '<S36>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain'
//  '<S37>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative'
//  '<S38>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter'
//  '<S39>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs'
//  '<S40>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain'
//  '<S41>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain'
//  '<S42>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk'
//  '<S43>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator'
//  '<S44>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs'
//  '<S45>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy'
//  '<S46>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain'
//  '<S47>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy'
//  '<S48>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain'
//  '<S49>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal'
//  '<S50>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation'
//  '<S51>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk'
//  '<S52>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum'
//  '<S53>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk'
//  '<S54>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode'
//  '<S55>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum'
//  '<S56>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral'
//  '<S57>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain'
//  '<S58>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal'
//  '<S59>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal'
//  '<S60>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal'
//  '<S61>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S62>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S63>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S64>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/D Gain/Internal Parameters'
//  '<S65>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/External Derivative/Error'
//  '<S66>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter/Disc. Forward Euler Filter'
//  '<S67>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Filter ICs/Internal IC - Filter'
//  '<S68>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/I Gain/Internal Parameters'
//  '<S69>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain/Passthrough'
//  '<S70>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Ideal P Gain Fdbk/Disabled'
//  '<S71>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator/Discrete'
//  '<S72>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Integrator ICs/Internal IC'
//  '<S73>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Copy/Disabled'
//  '<S74>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/N Gain/Internal Parameters'
//  '<S75>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/P Copy/Disabled'
//  '<S76>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Parallel P Gain/Internal Parameters'
//  '<S77>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Reset Signal/External Reset'
//  '<S78>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation/Enabled'
//  '<S79>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Saturation Fdbk/Disabled'
//  '<S80>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum/Sum_PID'
//  '<S81>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Sum Fdbk/Disabled'
//  '<S82>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode/Disabled'
//  '<S83>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tracking Mode Sum/Passthrough'
//  '<S84>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S85>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/Tsamp - Ngain/Passthrough'
//  '<S86>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/postSat Signal/Forward_Path'
//  '<S87>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preInt Signal/Internal PreInt'
//  '<S88>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Angular Velocity Controller/preSat Signal/Forward_Path'
//  '<S89>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller'
//  '<S90>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup'
//  '<S91>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain'
//  '<S92>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative'
//  '<S93>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter'
//  '<S94>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs'
//  '<S95>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain'
//  '<S96>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain'
//  '<S97>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk'
//  '<S98>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator'
//  '<S99>'  : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs'
//  '<S100>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy'
//  '<S101>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain'
//  '<S102>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy'
//  '<S103>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain'
//  '<S104>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal'
//  '<S105>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation'
//  '<S106>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk'
//  '<S107>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum'
//  '<S108>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk'
//  '<S109>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode'
//  '<S110>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum'
//  '<S111>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral'
//  '<S112>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain'
//  '<S113>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal'
//  '<S114>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal'
//  '<S115>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal'
//  '<S116>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S117>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S118>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S119>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/D Gain/Internal Parameters'
//  '<S120>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/External Derivative/Error'
//  '<S121>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S122>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S123>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/I Gain/Internal Parameters'
//  '<S124>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain/Passthrough'
//  '<S125>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S126>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator/Discrete'
//  '<S127>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Integrator ICs/Internal IC'
//  '<S128>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Copy/Disabled'
//  '<S129>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/N Gain/Internal Parameters'
//  '<S130>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/P Copy/Disabled'
//  '<S131>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S132>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Reset Signal/External Reset'
//  '<S133>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation/Enabled'
//  '<S134>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Saturation Fdbk/Disabled'
//  '<S135>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum/Sum_PID'
//  '<S136>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Sum Fdbk/Disabled'
//  '<S137>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode/Disabled'
//  '<S138>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S139>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S140>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S141>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/postSat Signal/Forward_Path'
//  '<S142>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preInt Signal/Internal PreInt'
//  '<S143>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/PID for Rb/PID Controller/preSat Signal/Forward_Path'
//  '<S144>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/Subsystem Reference1/forceToPWMCalculator'
//  '<S145>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup'
//  '<S146>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain'
//  '<S147>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative'
//  '<S148>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter'
//  '<S149>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs'
//  '<S150>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain'
//  '<S151>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain'
//  '<S152>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk'
//  '<S153>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator'
//  '<S154>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs'
//  '<S155>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy'
//  '<S156>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain'
//  '<S157>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy'
//  '<S158>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain'
//  '<S159>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal'
//  '<S160>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation'
//  '<S161>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk'
//  '<S162>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum'
//  '<S163>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk'
//  '<S164>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode'
//  '<S165>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum'
//  '<S166>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral'
//  '<S167>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain'
//  '<S168>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal'
//  '<S169>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal'
//  '<S170>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal'
//  '<S171>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S172>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
//  '<S173>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
//  '<S174>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/D Gain/Internal Parameters'
//  '<S175>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/External Derivative/Error'
//  '<S176>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter/Disc. Forward Euler Filter'
//  '<S177>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Filter ICs/Internal IC - Filter'
//  '<S178>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/I Gain/Internal Parameters'
//  '<S179>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain/Passthrough'
//  '<S180>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Ideal P Gain Fdbk/Disabled'
//  '<S181>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator/Discrete'
//  '<S182>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Integrator ICs/Internal IC'
//  '<S183>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Copy/Disabled'
//  '<S184>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/N Gain/Internal Parameters'
//  '<S185>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/P Copy/Disabled'
//  '<S186>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Parallel P Gain/Internal Parameters'
//  '<S187>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Reset Signal/External Reset'
//  '<S188>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation/Enabled'
//  '<S189>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Saturation Fdbk/Disabled'
//  '<S190>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum/Sum_PID'
//  '<S191>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Sum Fdbk/Disabled'
//  '<S192>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode/Disabled'
//  '<S193>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tracking Mode Sum/Passthrough'
//  '<S194>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S195>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/Tsamp - Ngain/Passthrough'
//  '<S196>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/postSat Signal/Forward_Path'
//  '<S197>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/preInt Signal/Internal PreInt'
//  '<S198>' : 'Mission_Manager_CGN/Low-Level Controller/cascaded_pid_controller/dRb Controller/preSat Signal/Forward_Path'
//  '<S199>' : 'Mission_Manager_CGN/Low-Level Controller/execute_command/commandExecuter'
//  '<S200>' : 'Mission_Manager_CGN/Subsystem Reference/derivedStateEstimates'
//  '<S201>' : 'Mission_Manager_CGN/Subsystem Reference/discreteTimeQuatPropagation'
//  '<S202>' : 'Mission_Manager_CGN/Subsystem Reference/dvl_reset'
//  '<S203>' : 'Mission_Manager_CGN/Subsystem Reference/eulToQuat'
//  '<S204>' : 'Mission_Manager_CGN/Subsystem Reference/quatToRotm'
//  '<S205>' : 'Mission_Manager_CGN/VR/Enabled Subsystem'
//  '<S206>' : 'Mission_Manager_CGN/pwm_heartbeat_publisher/Blank Message1'
//  '<S207>' : 'Mission_Manager_CGN/pwm_heartbeat_publisher/Publish2'
//  '<S208>' : 'Mission_Manager_CGN/pwm_publisher/Publish'

#endif                                 // Mission_Manager_CGN_h_

//
// File trailer for generated code.
//
// [EOF]
//
