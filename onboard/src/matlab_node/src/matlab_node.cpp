//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_node.cpp
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
#include "matlab_node.h"
#include "matlab_node_types.h"
#include "rtwtypes.h"
#include <cmath>
#include "matlab_node_private.h"
#include <cstring>
#include "rmw/qos_profiles.h"
#include <stddef.h>
#include "cmath"
#include "rt_defines.h"

static void rate_monotonic_scheduler(RT_MODEL_matlab_node_T *const matlab_node_M);

//
// Set which subrates need to run this base step (base rate always runs).
// This function must be called prior to calling the model step function
// in order to remember which rates need to run this base step.  The
// buffering of events allows for overlapping preemption.
//
void matlab_node_SetEventsForThisBaseStep(boolean_T *eventFlags,
  RT_MODEL_matlab_node_T *const matlab_node_M)
{
  // Task runs when its counter is zero, computed via rtmStepTask macro
  eventFlags[1] = ((boolean_T)matlab_node_M->StepTask(1));
}

//
//         This function updates active task flag for each subrate
//         and rate transition flags for tasks that exchange data.
//         The function assumes rate-monotonic multitasking scheduler.
//         The function must be called at model base rate so that
//         the generated code self-manages all its subrates and rate
//         transition flags.
//
static void rate_monotonic_scheduler(RT_MODEL_matlab_node_T *const matlab_node_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (matlab_node_M->Timing.TaskCounters.TID[1])++;
  if ((matlab_node_M->Timing.TaskCounters.TID[1]) > 49) {// Sample time: [0.5s, 0.0s] 
    matlab_node_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Function for MATLAB Function: '<S17>/guidanceLaw'
void matlab_node::matlab_node_wrapToPi(real_T *lambda)
{
  int32_T trueCount;
  boolean_T tmp;
  trueCount = 0;
  tmp = ((*lambda < -3.1415926535897931) || (*lambda > 3.1415926535897931));
  if (tmp) {
    for (int32_T i{0}; i < 1; i++) {
      trueCount++;
    }
  }

  if (trueCount - 1 >= 0) {
    if (std::isnan(*lambda + 3.1415926535897931)) {
      matlab_node_B.q_i = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      matlab_node_B.q_i = (rtNaN);
    } else {
      matlab_node_B.q_i = std::abs((*lambda + 3.1415926535897931) /
        6.2831853071795862);
      if (std::abs(matlab_node_B.q_i - std::floor(matlab_node_B.q_i + 0.5)) >
          2.2204460492503131E-16 * matlab_node_B.q_i) {
        matlab_node_B.q_i = std::fmod(*lambda + 3.1415926535897931,
          6.2831853071795862);
      } else {
        matlab_node_B.q_i = 0.0;
      }

      if (matlab_node_B.q_i == 0.0) {
        matlab_node_B.q_i = 0.0;
      } else if (matlab_node_B.q_i < 0.0) {
        matlab_node_B.q_i += 6.2831853071795862;
      }
    }

    matlab_node_B.varargin_1_data = matlab_node_B.q_i;
  }

  for (int32_T i{0}; i < trueCount; i++) {
    if ((matlab_node_B.varargin_1_data == 0.0) && (*lambda + 3.1415926535897931 >
         0.0)) {
      matlab_node_B.varargin_1_data = 6.2831853071795862;
    }
  }

  if (tmp) {
    *lambda = matlab_node_B.varargin_1_data - 3.1415926535897931;
  }
}

// Function for MATLAB Function: '<S18>/commandExecuter'
void matlab_node::matlab_node_eulToQuat_c(const real_T Eul[3], real_T qib[4])
{
  matlab_node_B.eta_b = std::cos(Eul[1]);
  matlab_node_B.scale_j = std::sin(Eul[1]);
  matlab_node_B.b_t_a = std::cos(Eul[2]);
  matlab_node_B.rotm_tmp_j = std::sin(Eul[2]);
  matlab_node_B.eps_idx_1 = std::sin(Eul[0]);
  matlab_node_B.rotm_tmp_jz = std::cos(Eul[0]);
  matlab_node_B.rotm_idx_0 = matlab_node_B.eta_b * matlab_node_B.b_t_a;
  matlab_node_B.eps_idx_2 = matlab_node_B.eta_b * matlab_node_B.rotm_tmp_j;
  matlab_node_B.rotm_idx_4_tmp = matlab_node_B.eps_idx_1 * matlab_node_B.scale_j;
  matlab_node_B.eps_idx_0 = matlab_node_B.rotm_idx_4_tmp *
    matlab_node_B.rotm_tmp_j + matlab_node_B.rotm_tmp_jz * matlab_node_B.b_t_a;
  matlab_node_B.absxk_f = matlab_node_B.eps_idx_1 * matlab_node_B.eta_b;
  matlab_node_B.rotm_idx_8 = matlab_node_B.rotm_tmp_jz * matlab_node_B.eta_b;
  matlab_node_B.eta_b = std::sqrt(((matlab_node_B.rotm_idx_0 +
    matlab_node_B.eps_idx_0) + matlab_node_B.rotm_idx_8) + 1.0) / 2.0;
  if (matlab_node_B.eta_b != 0.0) {
    matlab_node_B.rotm_idx_0 = matlab_node_B.rotm_tmp_jz * matlab_node_B.scale_j;
    matlab_node_B.rotm_idx_8 = 4.0 * matlab_node_B.eta_b;
    matlab_node_B.eps_idx_0 = (matlab_node_B.absxk_f - (matlab_node_B.rotm_idx_0
      * matlab_node_B.rotm_tmp_j - matlab_node_B.eps_idx_1 * matlab_node_B.b_t_a))
      / matlab_node_B.rotm_idx_8;
    matlab_node_B.eps_idx_1 = ((matlab_node_B.rotm_idx_0 * matlab_node_B.b_t_a +
      matlab_node_B.eps_idx_1 * matlab_node_B.rotm_tmp_j) -
      (-matlab_node_B.scale_j)) / matlab_node_B.rotm_idx_8;
    matlab_node_B.eps_idx_2 = (matlab_node_B.eps_idx_2 -
      (matlab_node_B.rotm_idx_4_tmp * matlab_node_B.b_t_a -
       matlab_node_B.rotm_tmp_jz * matlab_node_B.rotm_tmp_j)) /
      matlab_node_B.rotm_idx_8;
  } else {
    int32_T b_k;
    int32_T idx;
    matlab_node_B.b_t_a = (matlab_node_B.rotm_idx_0 + 1.0) / 2.0;
    matlab_node_B.x[0] = matlab_node_B.b_t_a;
    matlab_node_B.eps_idx_1 = (matlab_node_B.eps_idx_0 + 1.0) / 2.0;
    matlab_node_B.x[1] = matlab_node_B.eps_idx_1;
    matlab_node_B.rotm_tmp_j = (matlab_node_B.rotm_idx_8 + 1.0) / 2.0;
    matlab_node_B.x[2] = matlab_node_B.rotm_tmp_j;
    if (!std::isnan(matlab_node_B.b_t_a)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(matlab_node_B.x[b_k - 1])) {
          idx = b_k;
          exitg1 = true;
        } else {
          b_k++;
        }
      }
    }

    if (idx == 0) {
      b_k = 1;
    } else {
      matlab_node_B.eps_idx_0 = matlab_node_B.x[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        matlab_node_B.rotm_tmp_jz = matlab_node_B.x[c_k - 1];
        if (matlab_node_B.eps_idx_0 < matlab_node_B.rotm_tmp_jz) {
          matlab_node_B.eps_idx_0 = matlab_node_B.rotm_tmp_jz;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_a));
      if (std::isnan(matlab_node_B.eps_idx_2)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (matlab_node_B.eps_idx_2 < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (matlab_node_B.eps_idx_2 > 0.0);
      }

      matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0, matlab_node_B.eps_idx_1))
        * matlab_node_B.rotm_tmp_jz;
      if (std::isnan(-matlab_node_B.scale_j)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (-matlab_node_B.scale_j < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (-matlab_node_B.scale_j > 0.0);
      }

      matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_j)) * matlab_node_B.rotm_tmp_jz;
      break;

     case 2:
      matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0, matlab_node_B.eps_idx_1));
      if (std::isnan(matlab_node_B.eps_idx_2)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (matlab_node_B.eps_idx_2 < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (matlab_node_B.eps_idx_2 > 0.0);
      }

      matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_a)) *
        matlab_node_B.rotm_tmp_jz;
      if (std::isnan(matlab_node_B.absxk_f)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (matlab_node_B.absxk_f < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (matlab_node_B.absxk_f > 0.0);
      }

      matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_j)) * matlab_node_B.rotm_tmp_jz;
      break;

     default:
      matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_j));
      if (std::isnan(-matlab_node_B.scale_j)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (-matlab_node_B.scale_j < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (-matlab_node_B.scale_j > 0.0);
      }

      matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_a)) *
        matlab_node_B.rotm_tmp_jz;
      if (std::isnan(matlab_node_B.absxk_f)) {
        matlab_node_B.rotm_tmp_jz = (rtNaN);
      } else if (matlab_node_B.absxk_f < 0.0) {
        matlab_node_B.rotm_tmp_jz = -1.0;
      } else {
        matlab_node_B.rotm_tmp_jz = (matlab_node_B.absxk_f > 0.0);
      }

      matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0, matlab_node_B.eps_idx_1))
        * matlab_node_B.rotm_tmp_jz;
      break;
    }
  }

  matlab_node_B.scale_j = 3.3121686421112381E-170;
  matlab_node_B.absxk_f = std::abs(matlab_node_B.eps_idx_0);
  if (matlab_node_B.absxk_f > 3.3121686421112381E-170) {
    matlab_node_B.rotm_tmp_j = 1.0;
    matlab_node_B.scale_j = matlab_node_B.absxk_f;
  } else {
    matlab_node_B.b_t_a = matlab_node_B.absxk_f / 3.3121686421112381E-170;
    matlab_node_B.rotm_tmp_j = matlab_node_B.b_t_a * matlab_node_B.b_t_a;
  }

  matlab_node_B.absxk_f = std::abs(matlab_node_B.eps_idx_1);
  if (matlab_node_B.absxk_f > matlab_node_B.scale_j) {
    matlab_node_B.b_t_a = matlab_node_B.scale_j / matlab_node_B.absxk_f;
    matlab_node_B.rotm_tmp_j = matlab_node_B.rotm_tmp_j * matlab_node_B.b_t_a *
      matlab_node_B.b_t_a + 1.0;
    matlab_node_B.scale_j = matlab_node_B.absxk_f;
  } else {
    matlab_node_B.b_t_a = matlab_node_B.absxk_f / matlab_node_B.scale_j;
    matlab_node_B.rotm_tmp_j += matlab_node_B.b_t_a * matlab_node_B.b_t_a;
  }

  matlab_node_B.absxk_f = std::abs(matlab_node_B.eps_idx_2);
  if (matlab_node_B.absxk_f > matlab_node_B.scale_j) {
    matlab_node_B.b_t_a = matlab_node_B.scale_j / matlab_node_B.absxk_f;
    matlab_node_B.rotm_tmp_j = matlab_node_B.rotm_tmp_j * matlab_node_B.b_t_a *
      matlab_node_B.b_t_a + 1.0;
    matlab_node_B.scale_j = matlab_node_B.absxk_f;
  } else {
    matlab_node_B.b_t_a = matlab_node_B.absxk_f / matlab_node_B.scale_j;
    matlab_node_B.rotm_tmp_j += matlab_node_B.b_t_a * matlab_node_B.b_t_a;
  }

  if (matlab_node_B.eta_b > matlab_node_B.scale_j) {
    matlab_node_B.b_t_a = matlab_node_B.scale_j / matlab_node_B.eta_b;
    matlab_node_B.rotm_tmp_j = matlab_node_B.rotm_tmp_j * matlab_node_B.b_t_a *
      matlab_node_B.b_t_a + 1.0;
    matlab_node_B.scale_j = matlab_node_B.eta_b;
  } else {
    matlab_node_B.b_t_a = matlab_node_B.eta_b / matlab_node_B.scale_j;
    matlab_node_B.rotm_tmp_j += matlab_node_B.b_t_a * matlab_node_B.b_t_a;
  }

  matlab_node_B.rotm_tmp_j = matlab_node_B.scale_j * std::sqrt
    (matlab_node_B.rotm_tmp_j);
  qib[0] = matlab_node_B.eps_idx_0 / matlab_node_B.rotm_tmp_j;
  qib[1] = matlab_node_B.eps_idx_1 / matlab_node_B.rotm_tmp_j;
  qib[2] = matlab_node_B.eps_idx_2 / matlab_node_B.rotm_tmp_j;
  qib[3] = matlab_node_B.eta_b / matlab_node_B.rotm_tmp_j;
}

// Function for MATLAB Function: '<S18>/commandExecuter'
void matlab_node::matlab_nod_executeDurationTrick(real_T cmd_hold_time, const
  int8_T cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3], const
  real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time, real_T
  t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T cmd_status[4],
  real_T *hold_timer, real_T X_u[13])
{
  int32_T c_ret;
  int32_T d_ret;
  static const char_T a[16]{ 's', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T b_a[16]{ 's', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w',
    'a', 'r', 'd', '_', '_', '_' };

  static const char_T c_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T d_a[16]{ 's', 's', 'f', 'f', '_', 'l', 'e', 'f', 't', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T e_a[16]{ 's', 's', 'f', 'f', '_', 'u', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T f_a[16]{ 's', 's', 'f', 'f', '_', 'd', 'o', 'w', 'n', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T g_a[16]{ 's', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T h_a[16]{ 's', 's', 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i',
    'g', 'h', 't', '_', '_', '_' };

  static const char_T i_a[16]{ 's', 's', 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e',
    'f', 't', '_', '_', '_', '_' };

  static const char_T j_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  static const char_T k_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  static const char_T l_a[16]{ 's', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'U', 'p', '_', '_', '_', '_' };

  static const char_T m_a[16]{ 's', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'D', 'o', 'w', 'n', '_', '_' };

  static const char_T rb[16]{ 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a', 'r', 'd',
    '_', '_', '_', '_', '_', '_' };

  static const char_T sb[16]{ 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w', 'a', 'r',
    'd', '_', '_', '_', '_', '_' };

  static const char_T tb[16]{ 'f', 'f', '_', 'u', 'p', '_', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T ub[16]{ 'f', 'f', '_', 'd', 'o', 'w', 'n', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T vb[16]{ 'f', 'f', '_', 'r', 'i', 'g', 'h', 't', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T wb[16]{ 'f', 'f', '_', 'l', 'e', 'f', 't', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T xb[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'U', 'p',
    '_', '_', '_', '_', '_', '_' };

  static const char_T yb[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'D', 'o',
    'w', 'n', '_', '_', '_', '_' };

  static const char_T ac[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i', 'g', 'h',
    't', '_', '_', '_', '_', '_' };

  static const char_T bc[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e', 'f', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T cc[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R', 'i', 'g',
    'h', 't', '_', '_', '_', '_' };

  static const char_T dc[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L', 'e', 'f',
    't', '_', '_', '_', '_', '_' };

  static const char_T ec[16]{ 'f', 'f', '_', 's', 't', 'o', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T fc[16]{ 'r', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T gc[16]{ 'r', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w',
    'a', 'r', 'd', '_', '_', '_' };

  static const char_T hc[16]{ 'r', 's', 'f', 'f', '_', 'u', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T ic[16]{ 'r', 's', 'f', 'f', '_', 'd', 'o', 'w', 'n', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T jc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T kc[16]{ 'r', 's', 'f', 'f', '_', 'l', 'e', 'f', 't', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T lc[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'U', 'p', '_', '_', '_', '_' };

  static const char_T mc[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'D', 'o', 'w', 'n', '_', '_' };

  static const char_T nc[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i',
    'g', 'h', 't', '_', '_', '_' };

  static const char_T oc[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e',
    'f', 't', '_', '_', '_', '_' };

  static const char_T pc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  static const char_T qc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  static const char_T rc[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T n_a[16]{ 's', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T o_a[16]{ 's', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w',
    'a', 'r', 'd', '_', '_', '_' };

  static const char_T p_a[16]{ 's', 's', 'f', 'f', '_', 'u', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T q_a[16]{ 's', 's', 'f', 'f', '_', 'd', 'o', 'w', 'n', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T r_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T s_a[16]{ 's', 's', 'f', 'f', '_', 'l', 'e', 'f', 't', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T t_a[16]{ 's', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'U', 'p', '_', '_', '_', '_' };

  static const char_T u_a[16]{ 's', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'D', 'o', 'w', 'n', '_', '_' };

  static const char_T v_a[16]{ 's', 's', 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i',
    'g', 'h', 't', '_', '_', '_' };

  static const char_T w_a[16]{ 's', 's', 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e',
    'f', 't', '_', '_', '_', '_' };

  static const char_T x_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  static const char_T y_a[16]{ 's', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  static const char_T ab_a[16]{ 's', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T sc[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  for (c_ret = 0; c_ret < 16; c_ret++) {
    matlab_node_B.b.f1[c_ret] = rb[c_ret];
    matlab_node_B.c.f1[c_ret] = sb[c_ret];
    matlab_node_B.d.f1[c_ret] = tb[c_ret];
    matlab_node_B.e.f1[c_ret] = ub[c_ret];
    matlab_node_B.f.f1[c_ret] = vb[c_ret];
    matlab_node_B.g.f1[c_ret] = wb[c_ret];
    matlab_node_B.h.f1[c_ret] = xb[c_ret];
    matlab_node_B.i.f1[c_ret] = yb[c_ret];
    matlab_node_B.j.f1[c_ret] = ac[c_ret];
    matlab_node_B.k.f1[c_ret] = bc[c_ret];
    matlab_node_B.l.f1[c_ret] = cc[c_ret];
    matlab_node_B.m.f1[c_ret] = dc[c_ret];
    matlab_node_B.n.f1[c_ret] = ec[c_ret];
    matlab_node_B.o.f1[c_ret] = fc[c_ret];
    matlab_node_B.p.f1[c_ret] = gc[c_ret];
    matlab_node_B.q.f1[c_ret] = hc[c_ret];
    matlab_node_B.r.f1[c_ret] = ic[c_ret];
    matlab_node_B.s_g.f1[c_ret] = jc[c_ret];
    matlab_node_B.u.f1[c_ret] = kc[c_ret];
    matlab_node_B.v.f1[c_ret] = lc[c_ret];
    matlab_node_B.w.f1[c_ret] = mc[c_ret];
    matlab_node_B.x_l.f1[c_ret] = nc[c_ret];
    matlab_node_B.y.f1[c_ret] = oc[c_ret];
    matlab_node_B.ab.f1[c_ret] = pc[c_ret];
    matlab_node_B.bb.f1[c_ret] = qc[c_ret];
    matlab_node_B.cb.f1[c_ret] = rc[c_ret];
  }

  matlab_node_B.varargin_1[0] = matlab_node_B.b;
  matlab_node_B.varargin_1[1] = matlab_node_B.c;
  matlab_node_B.varargin_1[2] = matlab_node_B.d;
  matlab_node_B.varargin_1[3] = matlab_node_B.e;
  matlab_node_B.varargin_1[4] = matlab_node_B.f;
  matlab_node_B.varargin_1[5] = matlab_node_B.g;
  matlab_node_B.varargin_1[6] = matlab_node_B.h;
  matlab_node_B.varargin_1[7] = matlab_node_B.i;
  matlab_node_B.varargin_1[8] = matlab_node_B.j;
  matlab_node_B.varargin_1[9] = matlab_node_B.k;
  matlab_node_B.varargin_1[10] = matlab_node_B.l;
  matlab_node_B.varargin_1[11] = matlab_node_B.m;
  matlab_node_B.varargin_1[12] = matlab_node_B.n;
  matlab_node_B.varargin_2[0] = matlab_node_B.o;
  matlab_node_B.varargin_2[1] = matlab_node_B.p;
  matlab_node_B.varargin_2[2] = matlab_node_B.q;
  matlab_node_B.varargin_2[3] = matlab_node_B.r;
  matlab_node_B.varargin_2[4] = matlab_node_B.s_g;
  matlab_node_B.varargin_2[5] = matlab_node_B.u;
  matlab_node_B.varargin_2[6] = matlab_node_B.v;
  matlab_node_B.varargin_2[7] = matlab_node_B.w;
  matlab_node_B.varargin_2[8] = matlab_node_B.x_l;
  matlab_node_B.varargin_2[9] = matlab_node_B.y;
  matlab_node_B.varargin_2[10] = matlab_node_B.ab;
  matlab_node_B.varargin_2[11] = matlab_node_B.bb;
  matlab_node_B.varargin_2[12] = matlab_node_B.cb;
  for (c_ret = 0; c_ret < 16; c_ret++) {
    matlab_node_B.b.f1[c_ret] = n_a[c_ret];
    matlab_node_B.c.f1[c_ret] = o_a[c_ret];
    matlab_node_B.d.f1[c_ret] = p_a[c_ret];
    matlab_node_B.e.f1[c_ret] = q_a[c_ret];
    matlab_node_B.f.f1[c_ret] = r_a[c_ret];
    matlab_node_B.g.f1[c_ret] = s_a[c_ret];
    matlab_node_B.h.f1[c_ret] = t_a[c_ret];
    matlab_node_B.i.f1[c_ret] = u_a[c_ret];
    matlab_node_B.j.f1[c_ret] = v_a[c_ret];
    matlab_node_B.k.f1[c_ret] = w_a[c_ret];
    matlab_node_B.l.f1[c_ret] = x_a[c_ret];
    matlab_node_B.m.f1[c_ret] = y_a[c_ret];
    matlab_node_B.n.f1[c_ret] = ab_a[c_ret];
    matlab_node_B.o.f1[c_ret] = sc[c_ret];
  }

  matlab_node_B.varargin_3[0] = matlab_node_B.b;
  matlab_node_B.varargin_3[1] = matlab_node_B.c;
  matlab_node_B.varargin_3[2] = matlab_node_B.d;
  matlab_node_B.varargin_3[3] = matlab_node_B.e;
  matlab_node_B.varargin_3[4] = matlab_node_B.f;
  matlab_node_B.varargin_3[5] = matlab_node_B.g;
  matlab_node_B.varargin_3[6] = matlab_node_B.h;
  matlab_node_B.varargin_3[7] = matlab_node_B.i;
  matlab_node_B.varargin_3[8] = matlab_node_B.j;
  matlab_node_B.varargin_3[9] = matlab_node_B.k;
  matlab_node_B.varargin_3[10] = matlab_node_B.l;
  matlab_node_B.varargin_3[11] = matlab_node_B.m;
  matlab_node_B.varargin_3[12] = matlab_node_B.n;
  for (c_ret = 0; c_ret < 16; c_ret++) {
    matlab_node_B.switch_expression[c_ret] = cmd_trick_id[c_ret];
  }

  c_ret = 0;
  do {
    exitg3 = 0;
    if (c_ret < 13) {
      d_ret = std::memcmp(&matlab_node_B.varargin_1[c_ret].f1[0],
                          &matlab_node_B.switch_expression[0], 16);
      if (d_ret == 0) {
        c_ret = 0;
        exitg3 = 1;
      } else {
        c_ret++;
      }
    } else {
      c_ret = 0;
      exitg3 = 2;
    }
  } while (exitg3 == 0);

  if (exitg3 == 1) {
  } else {
    do {
      exitg2 = 0;
      if (c_ret < 13) {
        d_ret = std::memcmp(&matlab_node_B.varargin_2[c_ret].f1[0],
                            &matlab_node_B.switch_expression[0], 16);
        if (d_ret == 0) {
          c_ret = 1;
          exitg2 = 1;
        } else {
          c_ret++;
        }
      } else {
        c_ret = 0;
        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (c_ret < 13) {
          d_ret = std::memcmp(&matlab_node_B.varargin_3[c_ret].f1[0],
                              &matlab_node_B.switch_expression[0], 16);
          if (d_ret == 0) {
            c_ret = 2;
            exitg1 = 1;
          } else {
            c_ret++;
          }
        } else {
          c_ret = std::memcmp(&matlab_node_B.o.f1[0],
                              &matlab_node_B.switch_expression[0], 16);
          if (c_ret == 0) {
            c_ret = 3;
          } else {
            c_ret = -1;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  switch (c_ret) {
   case 0:
    std::memset(&X_u[0], 0, 13U * sizeof(real_T));
    *hold_timer = t - *hold_timer_start_time;
    if (*hold_timer >= cmd_hold_time) {
      cmd_status[0] = 83;
      cmd_status[1] = 85;
      cmd_status[2] = 67;
      cmd_status[3] = 67;
      *hold_timer_start_time = t;
    } else {
      cmd_status[0] = 82;
      cmd_status[1] = 85;
      cmd_status[2] = 78;
      cmd_status[3] = 78;
    }

    for (c_ret = 0; c_ret < 6; c_ret++) {
      cmd_specific_wp[c_ret] = idle_wp[c_ret];
    }
    break;

   case 1:
    std::memset(&X_u[0], 0, 13U * sizeof(real_T));
    *hold_timer = t - *hold_timer_start_time;
    if (*hold_timer >= cmd_hold_time) {
      cmd_status[0] = 83;
      cmd_status[1] = 85;
      cmd_status[2] = 67;
      cmd_status[3] = 67;
      *hold_timer_start_time = t;
    } else {
      cmd_status[0] = 82;
      cmd_status[1] = 85;
      cmd_status[2] = 78;
      cmd_status[3] = 78;
    }

    for (c_ret = 0; c_ret < 6; c_ret++) {
      cmd_specific_wp[c_ret] = idle_wp[c_ret];
    }
    break;

   case 2:
    *hold_timer = t - *hold_timer_start_time;
    if (new_cmd_reset) {
      cmd_specific_wp[0] = X_Ri[0];
      cmd_specific_wp[1] = X_Ri[1];
      cmd_specific_wp[2] = X_Ri[2];
      cmd_specific_wp[3] = 0.0;
      cmd_specific_wp[4] = 0.0;
      cmd_specific_wp[5] = X_Eul[2];
    }

    c_ret = std::memcmp(&a[0], &matlab_node_B.switch_expression[0], 16);
    if (c_ret == 0) {
      c_ret = 0;
    } else {
      c_ret = std::memcmp(&b_a[0], &matlab_node_B.switch_expression[0], 16);
      if (c_ret == 0) {
        c_ret = 1;
      } else {
        c_ret = std::memcmp(&c_a[0], &matlab_node_B.switch_expression[0], 16);
        if (c_ret == 0) {
          c_ret = 2;
        } else {
          c_ret = std::memcmp(&d_a[0], &matlab_node_B.switch_expression[0], 16);
          if (c_ret == 0) {
            c_ret = 3;
          } else {
            c_ret = std::memcmp(&e_a[0], &matlab_node_B.switch_expression[0], 16);
            if (c_ret == 0) {
              c_ret = 4;
            } else {
              c_ret = std::memcmp(&f_a[0], &matlab_node_B.switch_expression[0],
                                  16);
              if (c_ret == 0) {
                c_ret = 5;
              } else {
                c_ret = std::memcmp(&g_a[0], &matlab_node_B.switch_expression[0],
                                    16);
                if (c_ret == 0) {
                  c_ret = 6;
                } else {
                  c_ret = std::memcmp(&h_a[0], &matlab_node_B.switch_expression
                                      [0], 16);
                  if (c_ret == 0) {
                    c_ret = 7;
                  } else {
                    c_ret = std::memcmp(&i_a[0],
                                        &matlab_node_B.switch_expression[0], 16);
                    if (c_ret == 0) {
                      c_ret = 8;
                    } else {
                      c_ret = std::memcmp(&j_a[0],
                                          &matlab_node_B.switch_expression[0],
                                          16);
                      if (c_ret == 0) {
                        c_ret = 9;
                      } else {
                        c_ret = std::memcmp(&k_a[0],
                                            &matlab_node_B.switch_expression[0],
                                            16);
                        if (c_ret == 0) {
                          c_ret = 10;
                        } else {
                          c_ret = std::memcmp(&l_a[0],
                                              &matlab_node_B.switch_expression[0],
                                              16);
                          if (c_ret == 0) {
                            c_ret = 11;
                          } else {
                            c_ret = std::memcmp(&m_a[0],
                                                &matlab_node_B.switch_expression[
                                                0], 16);
                            if (c_ret == 0) {
                              c_ret = 12;
                            } else {
                              c_ret = -1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    switch (c_ret) {
     case 0:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 0.0 + X_Cib[c_ret] *
            1000.0) + X_Cib[c_ret + 6] * 0.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 1:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 0.0 + X_Cib[c_ret] *
            -1000.0) + X_Cib[c_ret + 6] * 0.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 2:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 1000.0 + X_Cib[c_ret] *
            0.0) + X_Cib[c_ret + 6] * 0.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 3:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * -1000.0 + X_Cib[c_ret] *
            0.0) + X_Cib[c_ret + 6] * 0.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 4:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 0.0 + X_Cib[c_ret] * 0.0)
            + X_Cib[c_ret + 6] * -1000.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 5:
      if (new_cmd_reset) {
        for (c_ret = 0; c_ret < 3; c_ret++) {
          cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 0.0 + X_Cib[c_ret] * 0.0)
            + X_Cib[c_ret + 6] * 1000.0) + X_Ri[c_ret];
        }
      }

      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 6:
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 7:
      cmd_specific_wp[5] = X_Eul[2] + 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 8:
      cmd_specific_wp[5] = X_Eul[2] - 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 9:
      cmd_specific_wp[5] = X_Eul[0] + 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 10:
      cmd_specific_wp[5] = X_Eul[0] - 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 11:
      cmd_specific_wp[5] = X_Eul[1] + 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 12:
      cmd_specific_wp[5] = X_Eul[1] - 0.52359877559829882;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     default:
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;
    }

    if (*hold_timer >= cmd_hold_time) {
      cmd_status[0] = 83;
      cmd_status[1] = 85;
      cmd_status[2] = 67;
      cmd_status[3] = 67;
      *hold_timer_start_time = t;
      matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_node_B.dv2[0];
      X_u[4] = matlab_node_B.dv2[1];
      X_u[5] = matlab_node_B.dv2[2];
      X_u[6] = matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
    } else {
      cmd_status[0] = 82;
      cmd_status[1] = 85;
      cmd_status[2] = 78;
      cmd_status[3] = 78;
    }
    break;

   case 3:
    if (new_cmd_reset) {
      for (c_ret = 0; c_ret < 3; c_ret++) {
        cmd_specific_wp[c_ret] = ((X_Cib[c_ret + 3] * 0.0 + X_Cib[c_ret] *
          1000.0) + X_Cib[c_ret + 6] * 0.0) + X_Ri[c_ret];
      }
    }

    matlab_node_eulToQuat_c(&cmd_specific_wp[3], matlab_node_B.dv2);
    X_u[0] = cmd_specific_wp[0];
    X_u[1] = cmd_specific_wp[1];
    X_u[2] = cmd_specific_wp[2];
    X_u[3] = matlab_node_B.dv2[0];
    X_u[4] = matlab_node_B.dv2[1];
    X_u[5] = matlab_node_B.dv2[2];
    X_u[6] = matlab_node_B.dv2[3];
    X_u[7] = 0.0;
    X_u[10] = 0.0;
    X_u[8] = 0.0;
    X_u[11] = 0.0;
    X_u[9] = 0.0;
    X_u[12] = 0.0;
    *hold_timer = t - *hold_timer_start_time;
    if (*hold_timer >= cmd_hold_time) {
      cmd_status[0] = 83;
      cmd_status[1] = 85;
      cmd_status[2] = 67;
      cmd_status[3] = 67;
      *hold_timer_start_time = t;
    } else {
      cmd_status[0] = 82;
      cmd_status[1] = 85;
      cmd_status[2] = 78;
      cmd_status[3] = 78;
    }
    break;

   default:
    cmd_status[0] = 70;
    cmd_status[1] = 65;
    cmd_status[2] = 73;
    cmd_status[3] = 76;
    *hold_timer = 0.0;
    *hold_timer_start_time = t;
    std::memset(&X_u[0], 0, 13U * sizeof(real_T));
    for (c_ret = 0; c_ret < 6; c_ret++) {
      cmd_specific_wp[c_ret] = idle_wp[c_ret];
    }
    break;
  }
}

// Function for MATLAB Function: '<S17>/guidanceLaw'
real_T matlab_node::matlab_node_norm(const real_T x[2])
{
  real_T absxk;
  real_T t;
  real_T y;
  matlab_node_B.scale_f = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    matlab_node_B.scale_f = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > matlab_node_B.scale_f) {
    t = matlab_node_B.scale_f / absxk;
    y = y * t * t + 1.0;
    matlab_node_B.scale_f = absxk;
  } else {
    t = absxk / matlab_node_B.scale_f;
    y += t * t;
  }

  return matlab_node_B.scale_f * std::sqrt(y);
}

// Function for MATLAB Function: '<S17>/guidanceLaw'
void matlab_node::matlab_node_quatToEul(const real_T qib[4], real_T Eul[3])
{
  int32_T i;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  matlab_node_B.a_o = qib[3] * qib[3] * 2.0 - 1.0;
  matlab_node_B.b_a_n = 2.0 * qib[3];
  for (i = 0; i < 3; i++) {
    matlab_node_B.a_tmp = 2.0 * qib[i];
    matlab_node_B.a[3 * i] = matlab_node_B.a_tmp * qib[0] + matlab_node_B.a_o *
      static_cast<real_T>(b[i]);
    matlab_node_B.a[3 * i + 1] = static_cast<real_T>(b[i + 3]) *
      matlab_node_B.a_o + matlab_node_B.a_tmp * qib[1];
    matlab_node_B.a[3 * i + 2] = static_cast<real_T>(b[i + 6]) *
      matlab_node_B.a_o + matlab_node_B.a_tmp * qib[2];
  }

  matlab_node_B.a_o = matlab_node_B.b_a_n * 0.0;
  matlab_node_B.b_a[0] = matlab_node_B.a_o;
  matlab_node_B.b_a[1] = matlab_node_B.b_a_n * -qib[2];
  matlab_node_B.b_a[2] = matlab_node_B.b_a_n * qib[1];
  matlab_node_B.b_a[3] = matlab_node_B.b_a_n * qib[2];
  matlab_node_B.b_a[4] = matlab_node_B.a_o;
  matlab_node_B.b_a[5] = matlab_node_B.b_a_n * -qib[0];
  matlab_node_B.b_a[6] = matlab_node_B.b_a_n * -qib[1];
  matlab_node_B.b_a[7] = matlab_node_B.b_a_n * qib[0];
  matlab_node_B.b_a[8] = matlab_node_B.a_o;
  for (i = 0; i < 9; i++) {
    matlab_node_B.Cbi_p[i] = matlab_node_B.a[i] + matlab_node_B.b_a[i];
  }

  matlab_node_B.b_a_n = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_node_B.Cbi_p[6])));
  if (std::abs(std::cos(-matlab_node_B.b_a_n)) < 1.0E-6) {
    Eul[0] = 0.0;
    Eul[2] = rt_atan2d_snf(-matlab_node_B.Cbi_p[1], matlab_node_B.Cbi_p[4]);
  } else {
    Eul[0] = rt_atan2d_snf(matlab_node_B.Cbi_p[7], matlab_node_B.Cbi_p[8]);
    Eul[2] = rt_atan2d_snf(matlab_node_B.Cbi_p[3], matlab_node_B.Cbi_p[0]);
  }

  matlab_node_wrapToPi(&Eul[0]);
  Eul[1] = -matlab_node_B.b_a_n;
  matlab_node_wrapToPi(&Eul[1]);
  matlab_node_wrapToPi(&Eul[2]);
}

// Function for MATLAB Function: '<S17>/guidanceLaw'
void matlab_node::matlab_node_eulToRotm(const real_T Eul[3], real_T rotm[9])
{
  real_T rotm_tmp;
  real_T rotm_tmp_0;
  matlab_node_B.rotm_tmp_o = std::cos(Eul[1]);
  matlab_node_B.rotm_tmp_o2 = std::sin(Eul[1]);
  matlab_node_B.rotm_tmp_i = std::cos(Eul[2]);
  rotm_tmp = std::sin(Eul[2]);
  rotm[0] = matlab_node_B.rotm_tmp_o * matlab_node_B.rotm_tmp_i;
  rotm[3] = matlab_node_B.rotm_tmp_o * rotm_tmp;
  rotm[6] = -matlab_node_B.rotm_tmp_o2;
  rotm_tmp_0 = 0.0 * matlab_node_B.rotm_tmp_o2;
  rotm[1] = rotm_tmp_0 * matlab_node_B.rotm_tmp_i - rotm_tmp;
  rotm[4] = rotm_tmp_0 * rotm_tmp + matlab_node_B.rotm_tmp_i;
  rotm[7] = 0.0 * matlab_node_B.rotm_tmp_o;
  rotm[2] = matlab_node_B.rotm_tmp_o2 * matlab_node_B.rotm_tmp_i + 0.0 *
    rotm_tmp;
  rotm[5] = matlab_node_B.rotm_tmp_o2 * rotm_tmp - 0.0 *
    matlab_node_B.rotm_tmp_i;
  rotm[8] = matlab_node_B.rotm_tmp_o;
}

// Function for MATLAB Function: '<S17>/guidanceLaw'
void matlab_node::matlab_node_rotmToQuat(const real_T rotm[9], real_T qib[4])
{
  real_T eps_idx_2;
  matlab_node_B.eta_p = std::sqrt(((rotm[0] + rotm[4]) + rotm[8]) + 1.0) / 2.0;
  if (matlab_node_B.eta_p != 0.0) {
    eps_idx_2 = 4.0 * matlab_node_B.eta_p;
    matlab_node_B.eps_idx_0_i = (rotm[7] - rotm[5]) / eps_idx_2;
    matlab_node_B.eps_idx_1_l = (rotm[2] - rotm[6]) / eps_idx_2;
    eps_idx_2 = (rotm[3] - rotm[1]) / eps_idx_2;
  } else {
    int32_T b_k;
    int32_T idx;
    matlab_node_B.eps_idx_0_i = (rotm[0] + 1.0) / 2.0;
    matlab_node_B.x_p[0] = matlab_node_B.eps_idx_0_i;
    matlab_node_B.eps_idx_1_l = (rotm[4] + 1.0) / 2.0;
    matlab_node_B.x_p[1] = matlab_node_B.eps_idx_1_l;
    eps_idx_2 = (rotm[8] + 1.0) / 2.0;
    matlab_node_B.x_p[2] = eps_idx_2;
    if (!std::isnan(matlab_node_B.eps_idx_0_i)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(matlab_node_B.x_p[b_k - 1])) {
          idx = b_k;
          exitg1 = true;
        } else {
          b_k++;
        }
      }
    }

    if (idx == 0) {
      b_k = 1;
    } else {
      matlab_node_B.scale_e = matlab_node_B.x_p[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        matlab_node_B.absxk_a = matlab_node_B.x_p[c_k - 1];
        if (matlab_node_B.scale_e < matlab_node_B.absxk_a) {
          matlab_node_B.scale_e = matlab_node_B.absxk_a;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      matlab_node_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_0_i));
      if (std::isnan(rotm[3])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[3] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[3] > 0.0);
      }

      matlab_node_B.eps_idx_1_l = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_l)) * matlab_node_B.scale_e;
      if (std::isnan(rotm[6])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[6] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[6] > 0.0);
      }

      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2)) * matlab_node_B.scale_e;
      break;

     case 2:
      matlab_node_B.eps_idx_1_l = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_l));
      if (std::isnan(rotm[3])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[3] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[3] > 0.0);
      }

      matlab_node_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_0_i)) * matlab_node_B.scale_e;
      if (std::isnan(rotm[7])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[7] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[7] > 0.0);
      }

      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2)) * matlab_node_B.scale_e;
      break;

     default:
      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2));
      if (std::isnan(rotm[6])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[6] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[6] > 0.0);
      }

      matlab_node_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_0_i)) * matlab_node_B.scale_e;
      if (std::isnan(rotm[7])) {
        matlab_node_B.scale_e = (rtNaN);
      } else if (rotm[7] < 0.0) {
        matlab_node_B.scale_e = -1.0;
      } else {
        matlab_node_B.scale_e = (rotm[7] > 0.0);
      }

      matlab_node_B.eps_idx_1_l = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_l)) * matlab_node_B.scale_e;
      break;
    }
  }

  matlab_node_B.scale_e = 3.3121686421112381E-170;
  matlab_node_B.absxk_a = std::abs(matlab_node_B.eps_idx_0_i);
  if (matlab_node_B.absxk_a > 3.3121686421112381E-170) {
    matlab_node_B.y_a = 1.0;
    matlab_node_B.scale_e = matlab_node_B.absxk_a;
  } else {
    matlab_node_B.b_t_as = matlab_node_B.absxk_a / 3.3121686421112381E-170;
    matlab_node_B.y_a = matlab_node_B.b_t_as * matlab_node_B.b_t_as;
  }

  matlab_node_B.absxk_a = std::abs(matlab_node_B.eps_idx_1_l);
  if (matlab_node_B.absxk_a > matlab_node_B.scale_e) {
    matlab_node_B.b_t_as = matlab_node_B.scale_e / matlab_node_B.absxk_a;
    matlab_node_B.y_a = matlab_node_B.y_a * matlab_node_B.b_t_as *
      matlab_node_B.b_t_as + 1.0;
    matlab_node_B.scale_e = matlab_node_B.absxk_a;
  } else {
    matlab_node_B.b_t_as = matlab_node_B.absxk_a / matlab_node_B.scale_e;
    matlab_node_B.y_a += matlab_node_B.b_t_as * matlab_node_B.b_t_as;
  }

  matlab_node_B.absxk_a = std::abs(eps_idx_2);
  if (matlab_node_B.absxk_a > matlab_node_B.scale_e) {
    matlab_node_B.b_t_as = matlab_node_B.scale_e / matlab_node_B.absxk_a;
    matlab_node_B.y_a = matlab_node_B.y_a * matlab_node_B.b_t_as *
      matlab_node_B.b_t_as + 1.0;
    matlab_node_B.scale_e = matlab_node_B.absxk_a;
  } else {
    matlab_node_B.b_t_as = matlab_node_B.absxk_a / matlab_node_B.scale_e;
    matlab_node_B.y_a += matlab_node_B.b_t_as * matlab_node_B.b_t_as;
  }

  if (matlab_node_B.eta_p > matlab_node_B.scale_e) {
    matlab_node_B.b_t_as = matlab_node_B.scale_e / matlab_node_B.eta_p;
    matlab_node_B.y_a = matlab_node_B.y_a * matlab_node_B.b_t_as *
      matlab_node_B.b_t_as + 1.0;
    matlab_node_B.scale_e = matlab_node_B.eta_p;
  } else {
    matlab_node_B.b_t_as = matlab_node_B.eta_p / matlab_node_B.scale_e;
    matlab_node_B.y_a += matlab_node_B.b_t_as * matlab_node_B.b_t_as;
  }

  matlab_node_B.y_a = matlab_node_B.scale_e * std::sqrt(matlab_node_B.y_a);
  qib[0] = matlab_node_B.eps_idx_0_i / matlab_node_B.y_a;
  qib[1] = matlab_node_B.eps_idx_1_l / matlab_node_B.y_a;
  qib[2] = eps_idx_2 / matlab_node_B.y_a;
  qib[3] = matlab_node_B.eta_p / matlab_node_B.y_a;
}

// Function for MATLAB Function: '<S17>/quatInjector'
void matlab_node::matlab_node_eulToQuat(const real_T Eul[3], real_T qib[4])
{
  real_T rotm_idx_4_tmp;
  matlab_node_B.eta_o = std::cos(Eul[1]);
  matlab_node_B.scale_n = std::sin(Eul[1]);
  matlab_node_B.b_t_c = std::cos(Eul[2]);
  matlab_node_B.rotm_tmp_m = std::sin(Eul[2]);
  matlab_node_B.eps_idx_1_h = std::sin(Eul[0]);
  matlab_node_B.rotm_tmp_m3 = std::cos(Eul[0]);
  matlab_node_B.rotm_idx_0_c = matlab_node_B.eta_o * matlab_node_B.b_t_c;
  matlab_node_B.eps_idx_2_c = matlab_node_B.eta_o * matlab_node_B.rotm_tmp_m;
  rotm_idx_4_tmp = matlab_node_B.eps_idx_1_h * matlab_node_B.scale_n;
  matlab_node_B.eps_idx_0_j = rotm_idx_4_tmp * matlab_node_B.rotm_tmp_m +
    matlab_node_B.rotm_tmp_m3 * matlab_node_B.b_t_c;
  matlab_node_B.absxk_m = matlab_node_B.eps_idx_1_h * matlab_node_B.eta_o;
  matlab_node_B.rotm_idx_8_p = matlab_node_B.rotm_tmp_m3 * matlab_node_B.eta_o;
  matlab_node_B.eta_o = std::sqrt(((matlab_node_B.rotm_idx_0_c +
    matlab_node_B.eps_idx_0_j) + matlab_node_B.rotm_idx_8_p) + 1.0) / 2.0;
  if (matlab_node_B.eta_o != 0.0) {
    matlab_node_B.rotm_idx_0_c = matlab_node_B.rotm_tmp_m3 *
      matlab_node_B.scale_n;
    matlab_node_B.rotm_idx_8_p = 4.0 * matlab_node_B.eta_o;
    matlab_node_B.eps_idx_0_j = (matlab_node_B.absxk_m -
      (matlab_node_B.rotm_idx_0_c * matlab_node_B.rotm_tmp_m -
       matlab_node_B.eps_idx_1_h * matlab_node_B.b_t_c)) /
      matlab_node_B.rotm_idx_8_p;
    matlab_node_B.eps_idx_1_h = ((matlab_node_B.rotm_idx_0_c *
      matlab_node_B.b_t_c + matlab_node_B.eps_idx_1_h * matlab_node_B.rotm_tmp_m)
      - (-matlab_node_B.scale_n)) / matlab_node_B.rotm_idx_8_p;
    matlab_node_B.eps_idx_2_c = (matlab_node_B.eps_idx_2_c - (rotm_idx_4_tmp *
      matlab_node_B.b_t_c - matlab_node_B.rotm_tmp_m3 * matlab_node_B.rotm_tmp_m))
      / matlab_node_B.rotm_idx_8_p;
  } else {
    int32_T b_k;
    int32_T idx;
    matlab_node_B.b_t_c = (matlab_node_B.rotm_idx_0_c + 1.0) / 2.0;
    matlab_node_B.x_n[0] = matlab_node_B.b_t_c;
    matlab_node_B.eps_idx_1_h = (matlab_node_B.eps_idx_0_j + 1.0) / 2.0;
    matlab_node_B.x_n[1] = matlab_node_B.eps_idx_1_h;
    matlab_node_B.rotm_tmp_m = (matlab_node_B.rotm_idx_8_p + 1.0) / 2.0;
    matlab_node_B.x_n[2] = matlab_node_B.rotm_tmp_m;
    if (!std::isnan(matlab_node_B.b_t_c)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(matlab_node_B.x_n[b_k - 1])) {
          idx = b_k;
          exitg1 = true;
        } else {
          b_k++;
        }
      }
    }

    if (idx == 0) {
      b_k = 1;
    } else {
      matlab_node_B.eps_idx_0_j = matlab_node_B.x_n[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        matlab_node_B.rotm_tmp_m3 = matlab_node_B.x_n[c_k - 1];
        if (matlab_node_B.eps_idx_0_j < matlab_node_B.rotm_tmp_m3) {
          matlab_node_B.eps_idx_0_j = matlab_node_B.rotm_tmp_m3;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      matlab_node_B.eps_idx_0_j = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_c));
      if (std::isnan(matlab_node_B.eps_idx_2_c)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (matlab_node_B.eps_idx_2_c < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (matlab_node_B.eps_idx_2_c > 0.0);
      }

      matlab_node_B.eps_idx_1_h = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_h)) * matlab_node_B.rotm_tmp_m3;
      if (std::isnan(-matlab_node_B.scale_n)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (-matlab_node_B.scale_n < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (-matlab_node_B.scale_n > 0.0);
      }

      matlab_node_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_m)) * matlab_node_B.rotm_tmp_m3;
      break;

     case 2:
      matlab_node_B.eps_idx_1_h = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_h));
      if (std::isnan(matlab_node_B.eps_idx_2_c)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (matlab_node_B.eps_idx_2_c < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (matlab_node_B.eps_idx_2_c > 0.0);
      }

      matlab_node_B.eps_idx_0_j = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_c))
        * matlab_node_B.rotm_tmp_m3;
      if (std::isnan(matlab_node_B.absxk_m)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (matlab_node_B.absxk_m < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (matlab_node_B.absxk_m > 0.0);
      }

      matlab_node_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_m)) * matlab_node_B.rotm_tmp_m3;
      break;

     default:
      matlab_node_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_node_B.rotm_tmp_m));
      if (std::isnan(-matlab_node_B.scale_n)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (-matlab_node_B.scale_n < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (-matlab_node_B.scale_n > 0.0);
      }

      matlab_node_B.eps_idx_0_j = std::sqrt(std::fmax(0.0, matlab_node_B.b_t_c))
        * matlab_node_B.rotm_tmp_m3;
      if (std::isnan(matlab_node_B.absxk_m)) {
        matlab_node_B.rotm_tmp_m3 = (rtNaN);
      } else if (matlab_node_B.absxk_m < 0.0) {
        matlab_node_B.rotm_tmp_m3 = -1.0;
      } else {
        matlab_node_B.rotm_tmp_m3 = (matlab_node_B.absxk_m > 0.0);
      }

      matlab_node_B.eps_idx_1_h = std::sqrt(std::fmax(0.0,
        matlab_node_B.eps_idx_1_h)) * matlab_node_B.rotm_tmp_m3;
      break;
    }
  }

  matlab_node_B.scale_n = 3.3121686421112381E-170;
  matlab_node_B.absxk_m = std::abs(matlab_node_B.eps_idx_0_j);
  if (matlab_node_B.absxk_m > 3.3121686421112381E-170) {
    matlab_node_B.rotm_tmp_m = 1.0;
    matlab_node_B.scale_n = matlab_node_B.absxk_m;
  } else {
    matlab_node_B.b_t_c = matlab_node_B.absxk_m / 3.3121686421112381E-170;
    matlab_node_B.rotm_tmp_m = matlab_node_B.b_t_c * matlab_node_B.b_t_c;
  }

  matlab_node_B.absxk_m = std::abs(matlab_node_B.eps_idx_1_h);
  if (matlab_node_B.absxk_m > matlab_node_B.scale_n) {
    matlab_node_B.b_t_c = matlab_node_B.scale_n / matlab_node_B.absxk_m;
    matlab_node_B.rotm_tmp_m = matlab_node_B.rotm_tmp_m * matlab_node_B.b_t_c *
      matlab_node_B.b_t_c + 1.0;
    matlab_node_B.scale_n = matlab_node_B.absxk_m;
  } else {
    matlab_node_B.b_t_c = matlab_node_B.absxk_m / matlab_node_B.scale_n;
    matlab_node_B.rotm_tmp_m += matlab_node_B.b_t_c * matlab_node_B.b_t_c;
  }

  matlab_node_B.absxk_m = std::abs(matlab_node_B.eps_idx_2_c);
  if (matlab_node_B.absxk_m > matlab_node_B.scale_n) {
    matlab_node_B.b_t_c = matlab_node_B.scale_n / matlab_node_B.absxk_m;
    matlab_node_B.rotm_tmp_m = matlab_node_B.rotm_tmp_m * matlab_node_B.b_t_c *
      matlab_node_B.b_t_c + 1.0;
    matlab_node_B.scale_n = matlab_node_B.absxk_m;
  } else {
    matlab_node_B.b_t_c = matlab_node_B.absxk_m / matlab_node_B.scale_n;
    matlab_node_B.rotm_tmp_m += matlab_node_B.b_t_c * matlab_node_B.b_t_c;
  }

  if (matlab_node_B.eta_o > matlab_node_B.scale_n) {
    matlab_node_B.b_t_c = matlab_node_B.scale_n / matlab_node_B.eta_o;
    matlab_node_B.rotm_tmp_m = matlab_node_B.rotm_tmp_m * matlab_node_B.b_t_c *
      matlab_node_B.b_t_c + 1.0;
    matlab_node_B.scale_n = matlab_node_B.eta_o;
  } else {
    matlab_node_B.b_t_c = matlab_node_B.eta_o / matlab_node_B.scale_n;
    matlab_node_B.rotm_tmp_m += matlab_node_B.b_t_c * matlab_node_B.b_t_c;
  }

  matlab_node_B.rotm_tmp_m = matlab_node_B.scale_n * std::sqrt
    (matlab_node_B.rotm_tmp_m);
  qib[0] = matlab_node_B.eps_idx_0_j / matlab_node_B.rotm_tmp_m;
  qib[1] = matlab_node_B.eps_idx_1_h / matlab_node_B.rotm_tmp_m;
  qib[2] = matlab_node_B.eps_idx_2_c / matlab_node_B.rotm_tmp_m;
  qib[3] = matlab_node_B.eta_o / matlab_node_B.rotm_tmp_m;
}

// Function for MATLAB Function: '<S17>/rateInjector'
boolean_T matlab_node::matlab_node_isequal(const char_T varargin_1[16])
{
  int32_T k;
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 16)) {
    if (varargin_1[k] != b[k]) {
      b_p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S17>/rateInjector'
boolean_T matlab_node::matlab_node_strcmp(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S17>/rateInjector'
boolean_T matlab_node::matlab_node_strcmp_n(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S17>/rateInjector'
boolean_T matlab_node::matlab_node_strcmp_nj(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S24>/forceToPWMCalculator'
void matlab_node::matlab_node_minimum(const real_T x[6], real_T *ex, int32_T
  *idx)
{
  int32_T b_idx;
  int32_T k;
  if (!std::isnan(x[0])) {
    b_idx = 1;
  } else {
    boolean_T exitg1;
    b_idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 7)) {
      if (!std::isnan(x[k - 1])) {
        b_idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (b_idx == 0) {
    *ex = x[0];
    *idx = 1;
  } else {
    *ex = x[b_idx - 1];
    *idx = b_idx;
    for (k = b_idx + 1; k < 7; k++) {
      real_T x_0;
      x_0 = x[k - 1];
      if (*ex > x_0) {
        *ex = x_0;
        *idx = k;
      }
    }
  }
}

// Function for MATLAB Function: '<S24>/forceToPWMCalculator'
void matlab_node::matlab_node_minimum_d(const real_T x_data[], const int32_T
  *x_size, real_T *ex, int32_T *idx)
{
  int32_T last;
  last = *x_size;
  if (static_cast<uint8_T>(*x_size - 1) + 1 <= 2) {
    if (static_cast<uint8_T>(*x_size - 1) == 0) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[*x_size - 1];
      if ((x_data[0] > *ex) || (std::isnan(x_data[0]) && (!std::isnan(*ex)))) {
        *idx = *x_size;
      } else {
        *ex = x_data[0];
        *idx = 1;
      }
    }
  } else {
    int32_T b_idx;
    int32_T k;
    if (!std::isnan(x_data[0])) {
      b_idx = 1;
    } else {
      boolean_T exitg1;
      b_idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= *x_size)) {
        if (!std::isnan(x_data[k - 1])) {
          b_idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (b_idx == 0) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[b_idx - 1];
      *idx = b_idx;
      for (k = b_idx + 1; k <= last; k++) {
        real_T x;
        x = x_data[k - 1];
        if (*ex > x) {
          *ex = x;
          *idx = k;
        }
      }
    }
  }
}

void matlab_node::matlab_no_Publisher_setupImpl_g(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/command_result" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S207>/SinkBlock'
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
    // Start for MATLABSystem: '<S207>/SinkBlock'
    matlab_node_B.b_zeroDelimTopic_dy[i] = b_zeroDelimTopic[i];
  }

  Pub_matlab_node_108_269.createPublisher(&matlab_node_B.b_zeroDelimTopic_dy[0],
    qos_profile);
}

void matlab_node::matlab_Subscriber_setupImpl_gzo(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[13]{ "/command_msg" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[13];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S202>/SourceBlock'
  matlab_node_B.deadline_l.sec = 0.0;
  matlab_node_B.deadline_l.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, matlab_node_B.deadline_l,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 13; i++) {
    // Start for MATLABSystem: '<S202>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_matlab_node_108_265.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_node::matlab_n_Subscriber_setupImpl_g(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  matlab_node_B.deadline_o.sec = 0.0;
  matlab_node_B.deadline_o.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, matlab_node_B.deadline_o,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S2>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_matlab_node_8.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_node::matlab__Subscriber_setupImpl_gz(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[17]{ "/velocity_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S4>/SourceBlock'
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
  for (int32_T i{0}; i < 17; i++) {
    // Start for MATLABSystem: '<S4>/SourceBlock'
    matlab_node_B.b_zeroDelimTopic_d[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_node_20.createSubscriber(&matlab_node_B.b_zeroDelimTopic_d[0],
    qos_profile);
}

void matlab_node::matlab_nod_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[18]{ "/dead_reck_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S1>/SourceBlock'
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
  for (int32_T i{0}; i < 18; i++) {
    // Start for MATLABSystem: '<S1>/SourceBlock'
    matlab_node_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_node_3.createSubscriber(&matlab_node_B.b_zeroDelimTopic[0],
    qos_profile);
}

void matlab_node::matlab__Publisher_setupImpl_gzo(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S210>/SinkBlock'
  matlab_node_B.deadline_b.sec = 0.0;
  matlab_node_B.deadline_b.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, matlab_node_B.deadline_b,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S210>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_matlab_node_38_2.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_node::matlab_node_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[14]{ "/matlab_debug" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[14];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S15>/SinkBlock'
  matlab_node_B.deadline.sec = 0.0;
  matlab_node_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE, matlab_node_B.deadline,
                 lifespan, RMW_QOS_POLICY_LIVELINESS_AUTOMATIC,
                 liveliness_lease_duration, (bool)
                 obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 14; i++) {
    // Start for MATLABSystem: '<S15>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_matlab_node_266_3.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_node::matlab_n_Publisher_setupImpl_gz(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S209>/SinkBlock'
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
    // Start for MATLABSystem: '<S209>/SinkBlock'
    matlab_node_B.b_zeroDelimTopic_dh[i] = b_zeroDelimTopic[i];
  }

  Pub_matlab_node_37_150.createPublisher(&matlab_node_B.b_zeroDelimTopic_dh[0],
    qos_profile);
}

// Model step function for TID0
void matlab_node::step0()              // Sample time: [0.01s, 0.0s]
{
  static const char_T c_a[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o', 'r',
    'l', 'd', '_', 'w', 'p', '_' };

  static const char_T d_a[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  static const char_T e_a[16]{ 'i', 'd', 'l', 'e', '_', '_', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T a[4]{ 'S', 'U', 'C', 'C' };

  static const char_T b_a[4]{ 'F', 'A', 'I', 'L' };

  static const char_T c_a_0[4]{ 'R', 'U', 'N', 'N' };

  char_T fd[4];
  boolean_T b_p;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  boolean_T b_varargout_1_1;
  static const char_T a_0[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  static const char_T a_1[16]{ 'r', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T b_a_0[16]{ 'r', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k',
    'w', 'a', 'r', 'd', '_', '_', '_' };

  static const char_T c_a_1[16]{ 'r', 's', 'f', 'f', '_', 'u', 'p', '_', '_',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T d_a_0[16]{ 'r', 's', 'f', 'f', '_', 'd', 'o', 'w', 'n',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T e_a_0[16]{ 'r', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h',
    't', '_', '_', '_', '_', '_', '_' };

  static const char_T f_a[16]{ 'r', 's', 'f', 'f', '_', 'l', 'e', 'f', 't', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T g_a[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'U', 'p', '_', '_', '_', '_' };

  static const char_T h_a[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'D', 'o', 'w', 'n', '_', '_' };

  static const char_T i_a[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i',
    'g', 'h', 't', '_', '_', '_' };

  static const char_T j_a[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e',
    'f', 't', '_', '_', '_', '_' };

  static const char_T a_2[16]{ 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a', 'r', 'd',
    '_', '_', '_', '_', '_', '_' };

  static const char_T b_a_1[16]{ 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w', 'a',
    'r', 'd', '_', '_', '_', '_', '_' };

  static const char_T c_a_2[16]{ 'f', 'f', '_', 'u', 'p', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T d_a_1[16]{ 'f', 'f', '_', 'd', 'o', 'w', 'n', '_', '_',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T e_a_1[16]{ 'f', 'f', '_', 'r', 'i', 'g', 'h', 't', '_',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T f_a_0[16]{ 'f', 'f', '_', 'l', 'e', 'f', 't', '_', '_',
    '_', '_', '_', '_', '_', '_', '_' };

  static const char_T g_a_0[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'U',
    'p', '_', '_', '_', '_', '_', '_' };

  static const char_T h_a_0[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'D',
    'o', 'w', 'n', '_', '_', '_', '_' };

  static const char_T i_a_0[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i', 'g',
    'h', 't', '_', '_', '_', '_', '_' };

  static const char_T j_a_0[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e', 'f',
    't', '_', '_', '_', '_', '_', '_' };

  static const char_T k_a[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R', 'i', 'g',
    'h', 't', '_', '_', '_', '_' };

  static const char_T l_a[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L', 'e', 'f',
    't', '_', '_', '_', '_', '_' };

  static const char_T m_a[16]{ 'f', 'f', '_', 's', 't', 'o', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  int32_T debug_start_new_cmd_flag;
  int32_T i;
  int8_T rtb_cmd_status[4];
  int8_T rtb_Switch1[3];
  int8_T tmp;
  int8_T tmp_0;
  uint8_T integrator_reset;
  boolean_T rtb_RelationalOperator_b[3];
  boolean_T rtb_RelationalOperator_c[3];
  boolean_T rtb_OR;
  boolean_T rtb_OR1;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const char_T c[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  static const char_T d[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  static const uint8_T b_0[16]{ 112U, 108U, 97U, 99U, 101U, 104U, 111U, 108U,
    100U, 101U, 114U, 95U, 95U, 95U, 95U, 95U };

  int32_T force_column_size_idx_0;
  boolean_T exitg1;

  {                                    // Sample time: [0.01s, 0.0s]
    rate_monotonic_scheduler((&matlab_node_M));
  }

  // DigitalClock: '<S18>/Digital Clock'
  matlab_node_B.DigitalClock = (((&matlab_node_M)->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S202>/SourceBlock'
  b_varargout_1 = Sub_matlab_node_108_265.getLatestMessage
    (&matlab_node_B.rtb_SourceBlock_o2_k1_k);

  // Outputs for Enabled SubSystem: '<S202>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S206>/Enable'

  // Start for MATLABSystem: '<S202>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S206>/In1'
    matlab_node_B.In1_d = matlab_node_B.rtb_SourceBlock_o2_k1_k;
  }

  // End of Outputs for SubSystem: '<S202>/Enabled Subsystem'

  // MATLAB Function: '<S6>/cmdMsgToCmdBus'
  for (i = 0; i < 16; i++) {
    integrator_reset = matlab_node_B.In1_d.command_id[i];
    if (integrator_reset > 127) {
      integrator_reset = 127U;
    }

    matlab_node_B.cmd.cmd_id[i] = static_cast<int8_T>(integrator_reset);
    integrator_reset = matlab_node_B.In1_d.trick[i];
    if (integrator_reset > 127) {
      integrator_reset = 127U;
    }

    matlab_node_B.cmd.trick_id[i] = static_cast<int8_T>(integrator_reset);
  }

  // MATLABSystem: '<S2>/SourceBlock'
  b_varargout_1_0 = Sub_matlab_node_8.getLatestMessage
    (&matlab_node_B.rtb_SourceBlock_o2_k_c);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S12>/Enable'

  // Start for MATLABSystem: '<S2>/SourceBlock'
  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S12>/In1'
    matlab_node_B.In1_k = matlab_node_B.rtb_SourceBlock_o2_k_c;
  }

  // End of Start for MATLABSystem: '<S2>/SourceBlock'
  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1_0 = Sub_matlab_node_20.getLatestMessage
    (&matlab_node_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S16>/Enable'

  // Start for MATLABSystem: '<S4>/SourceBlock'
  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S16>/In1'
    matlab_node_B.In1 = matlab_node_B.rtb_SourceBlock_o2_m;
  }

  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'

  // MATLABSystem: '<S1>/SourceBlock'
  b_varargout_1_1 = Sub_matlab_node_3.getLatestMessage
    (&matlab_node_B.rtb_SourceBlock_o2_g_c);

  // Outputs for Enabled SubSystem: '<S1>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S11>/Enable'

  // Start for MATLABSystem: '<S1>/SourceBlock'
  if (b_varargout_1_1) {
    // SignalConversion generated from: '<S11>/In1'
    matlab_node_B.In1_a = matlab_node_B.rtb_SourceBlock_o2_g_c;
  }

  // End of Outputs for SubSystem: '<S1>/Enabled Subsystem'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  matlab_node_B.eul_error[0] = matlab_node_B.In1_a.angle.x *
    0.017453292519943295;
  matlab_node_B.eul_error[1] = matlab_node_B.In1_a.angle.y *
    0.017453292519943295;
  matlab_node_B.eul_error[2] = matlab_node_B.In1_a.angle.z *
    0.017453292519943295;

  // MATLAB Function: '<S10>/eulToQuat'
  matlab_node_B.eta = std::cos(matlab_node_B.eul_error[1]);
  matlab_node_B.t = std::sin(matlab_node_B.eul_error[1]);
  matlab_node_B.b_t = std::cos(matlab_node_B.eul_error[2]);
  matlab_node_B.scale = std::sin(matlab_node_B.eul_error[2]);
  matlab_node_B.absxk = std::sin(matlab_node_B.eul_error[0]);
  matlab_node_B.b_scale = std::cos(matlab_node_B.eul_error[0]);
  matlab_node_B.rotm[0] = matlab_node_B.eta * matlab_node_B.b_t;
  matlab_node_B.rotm[3] = matlab_node_B.eta * matlab_node_B.scale;
  matlab_node_B.rotm_tmp = matlab_node_B.absxk * matlab_node_B.t;
  matlab_node_B.rotm[4] = matlab_node_B.rotm_tmp * matlab_node_B.scale +
    matlab_node_B.b_scale * matlab_node_B.b_t;
  matlab_node_B.rotm[7] = matlab_node_B.absxk * matlab_node_B.eta;
  matlab_node_B.rotm[8] = matlab_node_B.b_scale * matlab_node_B.eta;
  matlab_node_B.eta = std::sqrt(((matlab_node_B.rotm[0] + matlab_node_B.rotm[4])
    + matlab_node_B.rotm[8]) + 1.0) / 2.0;
  if (matlab_node_B.eta != 0.0) {
    matlab_node_B.rtb_Integrator_p_idx_1 = matlab_node_B.b_scale *
      matlab_node_B.t;
    matlab_node_B.rtb_Integrator_p_idx_2 = 4.0 * matlab_node_B.eta;
    matlab_node_B.eps[0] = (matlab_node_B.rotm[7] -
      (matlab_node_B.rtb_Integrator_p_idx_1 * matlab_node_B.scale -
       matlab_node_B.absxk * matlab_node_B.b_t)) /
      matlab_node_B.rtb_Integrator_p_idx_2;
    matlab_node_B.eps[1] = ((matlab_node_B.rtb_Integrator_p_idx_1 *
      matlab_node_B.b_t + matlab_node_B.absxk * matlab_node_B.scale) -
      (-matlab_node_B.t)) / matlab_node_B.rtb_Integrator_p_idx_2;
    matlab_node_B.eps[2] = (matlab_node_B.rotm[3] - (matlab_node_B.rotm_tmp *
      matlab_node_B.b_t - matlab_node_B.b_scale * matlab_node_B.scale)) /
      matlab_node_B.rtb_Integrator_p_idx_2;
  } else {
    matlab_node_B.b_t = (matlab_node_B.rotm[0] + 1.0) / 2.0;
    matlab_node_B.eul_error[0] = matlab_node_B.b_t;
    matlab_node_B.scale = (matlab_node_B.rotm[4] + 1.0) / 2.0;
    matlab_node_B.eul_error[1] = matlab_node_B.scale;
    matlab_node_B.absxk = (matlab_node_B.rotm[8] + 1.0) / 2.0;
    matlab_node_B.eul_error[2] = matlab_node_B.absxk;
    if (!std::isnan(matlab_node_B.b_t)) {
      matlab_node_B.ret = 1;
    } else {
      matlab_node_B.ret = 0;
      matlab_node_B.pos = 2;
      exitg1 = false;
      while ((!exitg1) && (matlab_node_B.pos < 4)) {
        if (!std::isnan(matlab_node_B.eul_error[matlab_node_B.pos - 1])) {
          matlab_node_B.ret = matlab_node_B.pos;
          exitg1 = true;
        } else {
          matlab_node_B.pos++;
        }
      }
    }

    if (matlab_node_B.ret == 0) {
      i = 1;
    } else {
      matlab_node_B.hold_timer = matlab_node_B.eul_error[matlab_node_B.ret - 1];
      i = matlab_node_B.ret;
      for (matlab_node_B.pos = matlab_node_B.ret + 1; matlab_node_B.pos < 4;
           matlab_node_B.pos++) {
        matlab_node_B.phi = matlab_node_B.eul_error[matlab_node_B.pos - 1];
        if (matlab_node_B.hold_timer < matlab_node_B.phi) {
          matlab_node_B.hold_timer = matlab_node_B.phi;
          i = matlab_node_B.pos;
        }
      }
    }

    switch (i) {
     case 1:
      matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_node_B.b_t));
      if (std::isnan(matlab_node_B.rotm[3])) {
        matlab_node_B.phi = (rtNaN);
      } else if (matlab_node_B.rotm[3] < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.rotm[3] > 0.0);
      }

      matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0, matlab_node_B.scale)) *
        matlab_node_B.phi;
      if (std::isnan(-matlab_node_B.t)) {
        matlab_node_B.phi = (rtNaN);
      } else if (-matlab_node_B.t < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (-matlab_node_B.t > 0.0);
      }

      matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0, matlab_node_B.absxk)) *
        matlab_node_B.phi;
      break;

     case 2:
      matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0, matlab_node_B.scale));
      if (std::isnan(matlab_node_B.rotm[3])) {
        matlab_node_B.phi = (rtNaN);
      } else if (matlab_node_B.rotm[3] < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.rotm[3] > 0.0);
      }

      matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_node_B.b_t)) *
        matlab_node_B.phi;
      if (std::isnan(matlab_node_B.rotm[7])) {
        matlab_node_B.phi = (rtNaN);
      } else if (matlab_node_B.rotm[7] < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.rotm[7] > 0.0);
      }

      matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0, matlab_node_B.absxk)) *
        matlab_node_B.phi;
      break;

     default:
      matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0, matlab_node_B.absxk));
      if (std::isnan(-matlab_node_B.t)) {
        matlab_node_B.phi = (rtNaN);
      } else if (-matlab_node_B.t < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (-matlab_node_B.t > 0.0);
      }

      matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_node_B.b_t)) *
        matlab_node_B.phi;
      if (std::isnan(matlab_node_B.rotm[7])) {
        matlab_node_B.phi = (rtNaN);
      } else if (matlab_node_B.rotm[7] < 0.0) {
        matlab_node_B.phi = -1.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.rotm[7] > 0.0);
      }

      matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0, matlab_node_B.scale)) *
        matlab_node_B.phi;
      break;
    }
  }

  matlab_node_B.scale = 3.3121686421112381E-170;
  matlab_node_B.absxk = std::abs(matlab_node_B.eps[0]);
  if (matlab_node_B.absxk > 3.3121686421112381E-170) {
    matlab_node_B.t = 1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.absxk / 3.3121686421112381E-170;
    matlab_node_B.t = matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_B.absxk = std::abs(matlab_node_B.eps[1]);
  if (matlab_node_B.absxk > matlab_node_B.scale) {
    matlab_node_B.b_t = matlab_node_B.scale / matlab_node_B.absxk;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.absxk / matlab_node_B.scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_B.absxk = std::abs(matlab_node_B.eps[2]);
  if (matlab_node_B.absxk > matlab_node_B.scale) {
    matlab_node_B.b_t = matlab_node_B.scale / matlab_node_B.absxk;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.absxk / matlab_node_B.scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  if (matlab_node_B.eta > matlab_node_B.scale) {
    matlab_node_B.b_t = matlab_node_B.scale / matlab_node_B.eta;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.scale = matlab_node_B.eta;
  } else {
    matlab_node_B.b_t = matlab_node_B.eta / matlab_node_B.scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_B.t = matlab_node_B.scale * std::sqrt(matlab_node_B.t);

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  matlab_node_B.dv3[0] = matlab_node_B.In1_k.imu_fusion.angular_velocity.x;
  matlab_node_B.dv3[1] = matlab_node_B.In1_k.imu_fusion.angular_velocity.y;
  matlab_node_B.dv3[2] = matlab_node_B.In1_k.imu_fusion.angular_velocity.z;

  // Product: '<S10>/Matrix Multiply2' incorporates:
  //   Constant: '<S10>/Constant1'

  matlab_node_B.rotm_tmp = 0.0;
  matlab_node_B.rtb_Integrator_p_idx_1 = 0.0;
  matlab_node_B.rtb_Integrator_p_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_B.dv3[i];
    matlab_node_B.rotm_tmp += matlab_node_ConstP.Constant1_Value_o[3 * i] *
      matlab_node_B.phi;
    matlab_node_B.rtb_Integrator_p_idx_1 +=
      matlab_node_ConstP.Constant1_Value_o[3 * i + 1] * matlab_node_B.phi;
    matlab_node_B.rtb_Integrator_p_idx_2 +=
      matlab_node_ConstP.Constant1_Value_o[3 * i + 2] * matlab_node_B.phi;
  }

  matlab_node_B.X_est.wb[2] = matlab_node_B.rtb_Integrator_p_idx_2;
  matlab_node_B.X_est.wb[1] = matlab_node_B.rtb_Integrator_p_idx_1;
  matlab_node_B.X_est.wb[0] = matlab_node_B.rotm_tmp;

  // MATLAB Function: '<S10>/discreteTimeQuatPropagation' incorporates:
  //   MATLAB Function: '<S10>/eulToQuat'
  //   MATLABSystem: '<S1>/SourceBlock'
  //   Product: '<S10>/Matrix Multiply2'
  //
  if (!matlab_node_DW.qk_not_empty) {
    matlab_node_DW.qk[0] = 0.0;
    matlab_node_DW.qk[1] = 0.0;
    matlab_node_DW.qk[2] = 0.0;
    matlab_node_DW.qk[3] = 1.0;
    matlab_node_DW.qk_not_empty = true;
  }

  if (b_varargout_1_1) {
    matlab_node_DW.qk[0] = matlab_node_B.eps[0] / matlab_node_B.t;
    matlab_node_DW.qk[1] = matlab_node_B.eps[1] / matlab_node_B.t;
    matlab_node_DW.qk[2] = matlab_node_B.eps[2] / matlab_node_B.t;
    matlab_node_DW.qk[3] = matlab_node_B.eta / matlab_node_B.t;
  }

  matlab_node_B.scale = 3.3121686421112381E-170;
  matlab_node_B.absxk = std::abs(matlab_node_B.rotm_tmp);
  if (matlab_node_B.absxk > 3.3121686421112381E-170) {
    matlab_node_B.eta = 1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.t = matlab_node_B.absxk / 3.3121686421112381E-170;
    matlab_node_B.eta = matlab_node_B.t * matlab_node_B.t;
  }

  matlab_node_B.absxk = std::abs(matlab_node_B.rtb_Integrator_p_idx_1);
  if (matlab_node_B.absxk > matlab_node_B.scale) {
    matlab_node_B.t = matlab_node_B.scale / matlab_node_B.absxk;
    matlab_node_B.eta = matlab_node_B.eta * matlab_node_B.t * matlab_node_B.t +
      1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.t = matlab_node_B.absxk / matlab_node_B.scale;
    matlab_node_B.eta += matlab_node_B.t * matlab_node_B.t;
  }

  matlab_node_B.absxk = std::abs(matlab_node_B.rtb_Integrator_p_idx_2);
  if (matlab_node_B.absxk > matlab_node_B.scale) {
    matlab_node_B.t = matlab_node_B.scale / matlab_node_B.absxk;
    matlab_node_B.eta = matlab_node_B.eta * matlab_node_B.t * matlab_node_B.t +
      1.0;
    matlab_node_B.scale = matlab_node_B.absxk;
  } else {
    matlab_node_B.t = matlab_node_B.absxk / matlab_node_B.scale;
    matlab_node_B.eta += matlab_node_B.t * matlab_node_B.t;
  }

  matlab_node_B.eta = matlab_node_B.scale * std::sqrt(matlab_node_B.eta);
  if (matlab_node_B.eta > 1.0E-10) {
    matlab_node_B.psi = std::sin(0.5 * matlab_node_B.eta * 0.01) /
      matlab_node_B.eta;
    matlab_node_B.eps[0] = matlab_node_B.psi * matlab_node_B.rotm_tmp;
    matlab_node_B.eps[1] = matlab_node_B.psi *
      matlab_node_B.rtb_Integrator_p_idx_1;
    matlab_node_B.eps[2] = matlab_node_B.psi *
      matlab_node_B.rtb_Integrator_p_idx_2;
  } else {
    matlab_node_B.eps[0] = 0.005 * matlab_node_B.rotm_tmp;
    matlab_node_B.eps[1] = 0.005 * matlab_node_B.rtb_Integrator_p_idx_1;
    matlab_node_B.eps[2] = 0.005 * matlab_node_B.rtb_Integrator_p_idx_2;
  }

  matlab_node_B.eta = std::cos(0.5 * matlab_node_B.eta * 0.01);
  for (i = 0; i < 9; i++) {
    // MATLAB Function: '<S10>/quatToRotm' incorporates:
    //   MATLAB Function: '<S10>/derivedStateEstimates'

    matlab_node_B.rotm[i] = b[i];
  }

  matlab_node_B.rtb_Cbi_tmp_tmp[0] = 0.0;
  matlab_node_B.rtb_Cbi_tmp_tmp[3] = -matlab_node_B.eps[2];
  matlab_node_B.rtb_Cbi_tmp_tmp[6] = matlab_node_B.eps[1];
  matlab_node_B.rtb_Cbi_tmp_tmp[1] = matlab_node_B.eps[2];
  matlab_node_B.rtb_Cbi_tmp_tmp[4] = 0.0;
  matlab_node_B.rtb_Cbi_tmp_tmp[7] = -matlab_node_B.eps[0];
  matlab_node_B.rtb_Cbi_tmp_tmp[2] = -matlab_node_B.eps[1];
  matlab_node_B.rtb_Cbi_tmp_tmp[5] = matlab_node_B.eps[0];
  matlab_node_B.rtb_Cbi_tmp_tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    matlab_node_B.ret = i << 2;
    matlab_node_B.c_a[matlab_node_B.ret] = matlab_node_B.rotm[3 * i] *
      matlab_node_B.eta - matlab_node_B.rtb_Cbi_tmp_tmp[3 * i];
    debug_start_new_cmd_flag = 3 * i + 1;
    matlab_node_B.c_a[matlab_node_B.ret + 1] =
      matlab_node_B.rotm[debug_start_new_cmd_flag] * matlab_node_B.eta -
      matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag];
    debug_start_new_cmd_flag = 3 * i + 2;
    matlab_node_B.c_a[matlab_node_B.ret + 2] =
      matlab_node_B.rotm[debug_start_new_cmd_flag] * matlab_node_B.eta -
      matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag];
    matlab_node_B.eps_n = matlab_node_B.eps[i];
    matlab_node_B.c_a[i + 12] = matlab_node_B.eps_n;
    matlab_node_B.c_a[matlab_node_B.ret + 3] = -matlab_node_B.eps_n;
  }

  matlab_node_B.c_a[15] = matlab_node_B.eta;
  matlab_node_B.t = 0.0;
  matlab_node_B.eta = 0.0;
  matlab_node_B.scale = 0.0;
  matlab_node_B.absxk = 0.0;
  for (i = 0; i < 4; i++) {
    matlab_node_B.phi = matlab_node_DW.qk[i];
    debug_start_new_cmd_flag = i << 2;
    matlab_node_B.t += matlab_node_B.c_a[debug_start_new_cmd_flag] *
      matlab_node_B.phi;
    matlab_node_B.eta += matlab_node_B.c_a[debug_start_new_cmd_flag + 1] *
      matlab_node_B.phi;
    matlab_node_B.scale += matlab_node_B.c_a[debug_start_new_cmd_flag + 2] *
      matlab_node_B.phi;
    matlab_node_B.absxk += matlab_node_B.c_a[debug_start_new_cmd_flag + 3] *
      matlab_node_B.phi;
  }

  matlab_node_B.b_scale = 3.3121686421112381E-170;
  matlab_node_DW.qk[0] = matlab_node_B.t;
  matlab_node_B.b_absxk = std::abs(matlab_node_DW.qk[0]);
  if (matlab_node_B.b_absxk > 3.3121686421112381E-170) {
    matlab_node_B.t = 1.0;
    matlab_node_B.b_scale = matlab_node_B.b_absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.b_absxk / 3.3121686421112381E-170;
    matlab_node_B.t = matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_DW.qk[1] = matlab_node_B.eta;
  matlab_node_B.b_absxk = std::abs(matlab_node_DW.qk[1]);
  if (matlab_node_B.b_absxk > matlab_node_B.b_scale) {
    matlab_node_B.b_t = matlab_node_B.b_scale / matlab_node_B.b_absxk;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.b_scale = matlab_node_B.b_absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.b_absxk / matlab_node_B.b_scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_DW.qk[2] = matlab_node_B.scale;
  matlab_node_B.b_absxk = std::abs(matlab_node_DW.qk[2]);
  if (matlab_node_B.b_absxk > matlab_node_B.b_scale) {
    matlab_node_B.b_t = matlab_node_B.b_scale / matlab_node_B.b_absxk;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.b_scale = matlab_node_B.b_absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.b_absxk / matlab_node_B.b_scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_DW.qk[3] = matlab_node_B.absxk;
  matlab_node_B.b_absxk = std::abs(matlab_node_DW.qk[3]);
  if (matlab_node_B.b_absxk > matlab_node_B.b_scale) {
    matlab_node_B.b_t = matlab_node_B.b_scale / matlab_node_B.b_absxk;
    matlab_node_B.t = matlab_node_B.t * matlab_node_B.b_t * matlab_node_B.b_t +
      1.0;
    matlab_node_B.b_scale = matlab_node_B.b_absxk;
  } else {
    matlab_node_B.b_t = matlab_node_B.b_absxk / matlab_node_B.b_scale;
    matlab_node_B.t += matlab_node_B.b_t * matlab_node_B.b_t;
  }

  matlab_node_B.t = matlab_node_B.b_scale * std::sqrt(matlab_node_B.t);
  matlab_node_B.rtb_delta_qe_idx_2 = matlab_node_DW.qk[0] / matlab_node_B.t;
  matlab_node_DW.qk[0] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.X_est.qib[0] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.rtb_delta_qe_idx_2 = matlab_node_DW.qk[1] / matlab_node_B.t;
  matlab_node_DW.qk[1] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.X_est.qib[1] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.rtb_delta_qe_idx_2 = matlab_node_DW.qk[2] / matlab_node_B.t;
  matlab_node_DW.qk[2] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.X_est.qib[2] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.rtb_delta_qe_idx_2 = matlab_node_DW.qk[3] / matlab_node_B.t;
  matlab_node_DW.qk[3] = matlab_node_B.rtb_delta_qe_idx_2;
  matlab_node_B.X_est.qib[3] = matlab_node_B.rtb_delta_qe_idx_2;

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/discreteTimeQuatPropagation'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'
  //   Math: '<S10>/Transpose'

  matlab_node_B.b_absxk = matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.rtb_delta_qe_idx_2 * 2.0 - 1.0;
  matlab_node_B.psi = 2.0 * matlab_node_B.rtb_delta_qe_idx_2;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  for (i = 0; i < 3; i++) {
    matlab_node_B.rtb_Cbi_tmp[3 * i] = 2.0 * matlab_node_B.X_est.qib[0] *
      matlab_node_B.X_est.qib[i];

    // Math: '<S10>/Transpose' incorporates:
    //   MATLAB Function: '<S17>/quatToEul1'
    //   MATLAB Function: '<S18>/commandExecuter'
    //   MATLAB Function: '<S5>/quatToEul'
    //   Math: '<S17>/Transpose'

    matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] = matlab_node_B.rotm[i];
    debug_start_new_cmd_flag = 3 * i + 1;
    matlab_node_B.rtb_Cbi_tmp[debug_start_new_cmd_flag] = 2.0 *
      matlab_node_B.X_est.qib[1] * matlab_node_B.X_est.qib[i];

    // Math: '<S10>/Transpose' incorporates:
    //   MATLAB Function: '<S17>/quatToEul1'
    //   MATLAB Function: '<S18>/commandExecuter'
    //   MATLAB Function: '<S5>/quatToEul'
    //   Math: '<S17>/Transpose'

    matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag] =
      matlab_node_B.rotm[i + 3];
    debug_start_new_cmd_flag = 3 * i + 2;
    matlab_node_B.rtb_Cbi_tmp[debug_start_new_cmd_flag] = 2.0 *
      matlab_node_B.X_est.qib[2] * matlab_node_B.X_est.qib[i];

    // Math: '<S10>/Transpose' incorporates:
    //   MATLAB Function: '<S17>/quatToEul1'
    //   MATLAB Function: '<S18>/commandExecuter'
    //   MATLAB Function: '<S5>/quatToEul'
    //   Math: '<S17>/Transpose'

    matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag] =
      matlab_node_B.rotm[i + 6];
  }

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'
  for (i = 0; i < 3; i++) {
    matlab_node_B.Cbi[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
      matlab_node_B.b_absxk + matlab_node_B.rtb_Cbi_tmp[i];

    // Math: '<S10>/Transpose'
    debug_start_new_cmd_flag = 3 * i + 1;
    matlab_node_B.Cbi[debug_start_new_cmd_flag] =
      matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag] *
      matlab_node_B.b_absxk + matlab_node_B.rtb_Cbi_tmp[i + 3];

    // Math: '<S10>/Transpose'
    debug_start_new_cmd_flag = 3 * i + 2;
    matlab_node_B.Cbi[debug_start_new_cmd_flag] =
      matlab_node_B.rtb_Cbi_tmp_tmp[debug_start_new_cmd_flag] *
      matlab_node_B.b_absxk + matlab_node_B.rtb_Cbi_tmp[i + 6];
  }

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  matlab_node_B.rtb_Cbi_tmp_tmp_d = matlab_node_B.psi * 0.0;

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[0] = matlab_node_B.rtb_Cbi_tmp_tmp_d;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.rtb_FilterCoefficient_h_idx_0 = matlab_node_B.psi *
    -matlab_node_B.X_est.qib[2];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[1] = matlab_node_B.rtb_FilterCoefficient_h_idx_0;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.rtb_Filter_h_idx_0 = matlab_node_B.psi *
    matlab_node_B.X_est.qib[1];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[2] = matlab_node_B.rtb_Filter_h_idx_0;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.rtb_Integrator_p_idx_0 = matlab_node_B.psi *
    matlab_node_B.X_est.qib[2];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[3] = matlab_node_B.rtb_Integrator_p_idx_0;
  matlab_node_B.rtb_Cbi_tmp_b[4] = matlab_node_B.rtb_Cbi_tmp_tmp_d;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.rtb_Filter_h_idx_1 = matlab_node_B.psi *
    -matlab_node_B.X_est.qib[0];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[5] = matlab_node_B.rtb_Filter_h_idx_1;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.lower_voltage_index = matlab_node_B.psi *
    -matlab_node_B.X_est.qib[1];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[6] = matlab_node_B.lower_voltage_index;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S10>/quatToRotm' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_tmp_e = matlab_node_B.psi * matlab_node_B.X_est.qib
    [0];

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // Math: '<S10>/Transpose' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/quatToRotm'

  matlab_node_B.rtb_Cbi_tmp_b[7] = matlab_node_B.rtb_Cbi_tmp_tmp_e;
  matlab_node_B.rtb_Cbi_tmp_b[8] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  for (i = 0; i < 9; i++) {
    matlab_node_B.Cbi_c[i] = matlab_node_B.Cbi[i] +
      matlab_node_B.rtb_Cbi_tmp_b[i];
  }

  // Logic: '<S10>/OR' incorporates:
  //   DataStoreRead: '<S10>/Data Store Read1'
  //   DataStoreRead: '<S10>/Data Store Read7'

  rtb_OR = (matlab_node_DW.reset_dvl_pos ||
            matlab_node_DW.joystick_mode_enabled_flag);

  // MATLAB Function: '<S10>/dvl_reset' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'

  if (matlab_node_DW.prior_flag && (!rtb_OR)) {
    matlab_node_DW.offset[0] = matlab_node_B.In1_a.position.x;
    matlab_node_DW.offset[1] = matlab_node_B.In1_a.position.y;
    matlab_node_DW.offset[2] = matlab_node_B.In1_a.position.z;
  }

  matlab_node_DW.prior_flag = rtb_OR;
  matlab_node_B.rtb_dvl_pos_m[0] = matlab_node_B.In1_a.position.x -
    matlab_node_DW.offset[0];
  matlab_node_B.rtb_dvl_pos_m[1] = matlab_node_B.In1_a.position.y -
    matlab_node_DW.offset[1];
  matlab_node_B.rtb_dvl_pos_m[2] = matlab_node_B.In1_a.position.z -
    matlab_node_DW.offset[2];

  // End of MATLAB Function: '<S10>/dvl_reset'

  // Product: '<S10>/Matrix Multiply3' incorporates:
  //   Math: '<S10>/Transpose'

  matlab_node_B.eps_n = 0.0;
  matlab_node_B.theta = 0.0;
  matlab_node_B.psi = 0.0;
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_B.rtb_dvl_pos_m[i];
    matlab_node_B.eps_n += matlab_node_B.Cbi_c[3 * i] * matlab_node_B.phi;
    matlab_node_B.theta += matlab_node_B.Cbi_c[3 * i + 1] * matlab_node_B.phi;
    matlab_node_B.psi += matlab_node_B.Cbi_c[3 * i + 2] * matlab_node_B.phi;
  }

  // DiscreteIntegrator: '<S10>/Position Integrator' incorporates:
  //   MATLABSystem: '<S1>/SourceBlock'
  //   Product: '<S10>/Matrix Multiply3'
  //
  if (matlab_node_DW.PositionIntegrator_IC_LOADING != 0) {
    matlab_node_DW.PositionIntegrator_DSTATE[0] = matlab_node_B.eps_n;
    matlab_node_DW.PositionIntegrator_DSTATE[1] = matlab_node_B.theta;
    matlab_node_DW.PositionIntegrator_DSTATE[2] = matlab_node_B.psi;
  }

  if (b_varargout_1_1 && (matlab_node_DW.PositionIntegrator_PrevResetSta <= 0))
  {
    matlab_node_DW.PositionIntegrator_DSTATE[0] = matlab_node_B.eps_n;
    matlab_node_DW.PositionIntegrator_DSTATE[1] = matlab_node_B.theta;
    matlab_node_DW.PositionIntegrator_DSTATE[2] = matlab_node_B.psi;
  }

  // DiscreteIntegrator: '<S10>/Velocity Integrator' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLABSystem: '<S4>/SourceBlock'
  //
  if (matlab_node_DW.VelocityIntegrator_IC_LOADING != 0) {
    matlab_node_DW.VelocityIntegrator_DSTATE[0] =
      matlab_node_B.In1.velocity_data.x;
    matlab_node_DW.VelocityIntegrator_DSTATE[1] =
      matlab_node_B.In1.velocity_data.y;
    matlab_node_DW.VelocityIntegrator_DSTATE[2] =
      matlab_node_B.In1.velocity_data.z;
  }

  if (b_varargout_1_0 && (matlab_node_DW.VelocityIntegrator_PrevResetSta <= 0))
  {
    matlab_node_DW.VelocityIntegrator_DSTATE[0] =
      matlab_node_B.In1.velocity_data.x;
    matlab_node_DW.VelocityIntegrator_DSTATE[1] =
      matlab_node_B.In1.velocity_data.y;
    matlab_node_DW.VelocityIntegrator_DSTATE[2] =
      matlab_node_B.In1.velocity_data.z;
  }

  // Product: '<S10>/Matrix Multiply' incorporates:
  //   Constant: '<S10>/Constant'
  //   Math: '<S10>/Transpose'

  matlab_node_B.eta = 0.0;
  matlab_node_B.t = 0.0;
  matlab_node_B.b_t = 0.0;
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_ConstP.Constant_Value_ep[i];
    matlab_node_B.eta += matlab_node_B.Cbi_c[3 * i] * matlab_node_B.phi;
    matlab_node_B.t += matlab_node_B.Cbi_c[3 * i + 1] * matlab_node_B.phi;
    matlab_node_B.b_t += matlab_node_B.Cbi_c[3 * i + 2] * matlab_node_B.phi;
  }

  matlab_node_B.eul_error[2] = matlab_node_B.b_t;
  matlab_node_B.eul_error[1] = matlab_node_B.t;
  matlab_node_B.eul_error[0] = matlab_node_B.eta;

  // End of Product: '<S10>/Matrix Multiply'

  // Sum: '<S10>/Sum' incorporates:
  //   Constant: '<S10>/Constant1'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   Product: '<S10>/Matrix Multiply1'

  for (i = 0; i < 3; i++) {
    matlab_node_B.rtb_dvl_pos_m[i] = ((matlab_node_ConstP.Constant1_Value_o[i +
      3] * matlab_node_B.In1_k.imu_fusion.linear_acceleration.y +
      matlab_node_ConstP.Constant1_Value_o[i] *
      matlab_node_B.In1_k.imu_fusion.linear_acceleration.x) +
      matlab_node_ConstP.Constant1_Value_o[i + 6] *
      matlab_node_B.In1_k.imu_fusion.linear_acceleration.z) -
      matlab_node_B.eul_error[i];
  }

  // End of Sum: '<S10>/Sum'

  // MATLAB Function: '<S10>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S10>/Position Integrator'
  //   DiscreteIntegrator: '<S10>/Velocity Integrator'

  matlab_node_B.Cbi_c[0] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.Cbi_c[3] = matlab_node_B.rtb_FilterCoefficient_h_idx_0;
  matlab_node_B.Cbi_c[6] = matlab_node_B.rtb_Filter_h_idx_0;
  matlab_node_B.Cbi_c[1] = matlab_node_B.rtb_Integrator_p_idx_0;
  matlab_node_B.Cbi_c[4] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.Cbi_c[7] = matlab_node_B.rtb_Filter_h_idx_1;
  matlab_node_B.Cbi_c[2] = matlab_node_B.lower_voltage_index;
  matlab_node_B.Cbi_c[5] = matlab_node_B.rtb_Cbi_tmp_tmp_e;
  matlab_node_B.Cbi_c[8] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  for (i = 0; i < 9; i++) {
    matlab_node_B.X_est.Cib[i] = (matlab_node_B.b_absxk * matlab_node_B.rotm[i]
      + matlab_node_B.rtb_Cbi_tmp[i]) + matlab_node_B.Cbi_c[i];
    matlab_node_B.Cbi[i] += matlab_node_B.rtb_Cbi_tmp_b[i];
  }

  matlab_node_B.theta = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_node_B.theta)) < 1.0E-6) {
    matlab_node_B.eta = 0.0;
    matlab_node_B.t = rt_atan2d_snf(-matlab_node_B.Cbi[1], matlab_node_B.Cbi[4]);
  } else {
    matlab_node_B.eta = rt_atan2d_snf(matlab_node_B.Cbi[7], matlab_node_B.Cbi[8]);
    matlab_node_B.t = rt_atan2d_snf(matlab_node_B.Cbi[3], matlab_node_B.Cbi[0]);
  }

  matlab_node_wrapToPi(&matlab_node_B.eta);
  matlab_node_B.b_t = -matlab_node_B.theta;
  matlab_node_wrapToPi(&matlab_node_B.b_t);
  matlab_node_wrapToPi(&matlab_node_B.t);
  matlab_node_B.scale = 0.0;
  matlab_node_B.absxk = 0.0;
  matlab_node_B.b_scale = 0.0;
  matlab_node_B.X_est.Eul[0] = matlab_node_B.eta;
  matlab_node_B.X_est.Eul[1] = matlab_node_B.b_t;
  matlab_node_B.X_est.Eul[2] = matlab_node_B.t;
  matlab_node_B.rtb_X_est_idx_0 = 0.0;
  matlab_node_B.rtb_X_est_idx_1 = 0.0;
  matlab_node_B.rtb_X_est_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_DW.PositionIntegrator_DSTATE[i];
    matlab_node_B.hold_timer = matlab_node_B.X_est.Cib[3 * i];
    matlab_node_B.scale += matlab_node_B.hold_timer * matlab_node_B.phi;
    matlab_node_B.qe_matlab_idx_1 = matlab_node_B.X_est.Cib[3 * i + 1];
    matlab_node_B.absxk += matlab_node_B.qe_matlab_idx_1 * matlab_node_B.phi;
    matlab_node_B.qe_matlab_idx_2 = matlab_node_B.X_est.Cib[3 * i + 2];
    matlab_node_B.b_scale += matlab_node_B.qe_matlab_idx_2 * matlab_node_B.phi;
    matlab_node_B.phi = matlab_node_DW.VelocityIntegrator_DSTATE[i];
    matlab_node_B.rtb_X_est_idx_0 += matlab_node_B.hold_timer *
      matlab_node_B.phi;
    matlab_node_B.rtb_X_est_idx_1 += matlab_node_B.qe_matlab_idx_1 *
      matlab_node_B.phi;
    matlab_node_B.rtb_X_est_idx_2 += matlab_node_B.qe_matlab_idx_2 *
      matlab_node_B.phi;
  }

  matlab_node_B.X_est.Ri[0] = matlab_node_B.scale;
  matlab_node_B.X_est.Ri[1] = matlab_node_B.absxk;
  matlab_node_B.X_est.Ri[2] = matlab_node_B.b_scale;

  // Logic: '<S5>/OR1' incorporates:
  //   DataStoreRead: '<S5>/Data Store Read5'
  //   DataStoreRead: '<S5>/Data Store Read7'

  rtb_OR1 = (matlab_node_DW.start_new_cmd_flag ||
             matlab_node_DW.joystick_mode_enabled_flag);

  // MATLAB Function: '<S18>/commandExecuter' incorporates:
  //   DataStoreWrite: '<S18>/Data Store Write'
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/discreteTimeQuatPropagation'
  //   MATLAB Function: '<S6>/cmdMsgToCmdBus'
  //   UnitDelay: '<S5>/Unit Delay2'
  //   UnitDelay: '<S5>/Unit Delay3'

  if (!matlab_node_DW.hold_timer_start_time_not_empty) {
    matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
    matlab_node_DW.hold_timer_start_time_not_empty = true;
  }

  if (!matlab_node_DW.idle_wp_not_empty) {
    matlab_node_DW.idle_wp[0] = matlab_node_B.scale;
    matlab_node_DW.idle_wp[1] = matlab_node_B.absxk;
    matlab_node_DW.idle_wp[2] = matlab_node_B.b_scale;
    matlab_node_DW.idle_wp[3] = 0.0;
    matlab_node_DW.idle_wp[4] = 0.0;
    matlab_node_DW.idle_wp[5] = matlab_node_B.t;
    matlab_node_DW.idle_wp_not_empty = true;
  }

  if (!matlab_node_DW.cmd_specific_wp_not_empty) {
    for (i = 0; i < 6; i++) {
      matlab_node_DW.cmd_specific_wp[i] = matlab_node_DW.idle_wp[i];
    }

    matlab_node_DW.cmd_specific_wp_not_empty = true;
  }

  if ((matlab_node_DW.UnitDelay2_DSTATE == 2.0) &&
      (matlab_node_DW.prior_action_id != 2.0)) {
    matlab_node_DW.idle_wp[5] = matlab_node_DW.UnitDelay3_DSTATE;
  }

  matlab_node_DW.prior_action_id = matlab_node_DW.UnitDelay2_DSTATE;
  if (rtb_OR1) {
    matlab_node_DW.idle_wp[0] = 0.0;
    matlab_node_DW.idle_wp[1] = 0.0;
    matlab_node_DW.idle_wp[2] = 0.0;
    matlab_node_DW.idle_wp[3] = 0.0;
    matlab_node_DW.idle_wp[4] = 0.0;
    matlab_node_DW.idle_wp[5] = matlab_node_B.t;
    matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
    matlab_node_DW.prior_action_id = 0.0;
    matlab_node_B.varargin_2_l[16] = '\x00';
    for (i = 0; i < 16; i++) {
      matlab_node_B.varargin_2_l[i] = matlab_node_B.cmd.cmd_id[i];
      matlab_node_B.varargin_3_j[i] = matlab_node_B.cmd.trick_id[i];
    }

    matlab_node_B.varargin_3_j[16] = '\x00';
    std::printf("%.2f: Working on command %s with trick %s.\n",
                matlab_node_B.DigitalClock, &matlab_node_B.varargin_2_l[0],
                &matlab_node_B.varargin_3_j[0]);
    std::fflush(stdout);
  }

  for (i = 0; i < 16; i++) {
    matlab_node_B.s[i] = matlab_node_B.cmd.cmd_id[i];
  }

  matlab_node_B.ret = std::memcmp(&c_a[0], &matlab_node_B.s[0], 16);
  if (matlab_node_B.ret == 0) {
    matlab_node_B.ret = 0;
  } else {
    matlab_node_B.ret = std::memcmp(&d_a[0], &matlab_node_B.s[0], 16);
    if (matlab_node_B.ret == 0) {
      matlab_node_B.ret = 1;
    } else {
      matlab_node_B.ret = std::memcmp(&e_a[0], &matlab_node_B.s[0], 16);
      if (matlab_node_B.ret == 0) {
        matlab_node_B.ret = 2;
      } else {
        matlab_node_B.ret = -1;
      }
    }
  }

  switch (matlab_node_B.ret) {
   case 0:
    matlab_node_B.dv3[0] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.roll) * matlab_node_DW.idle_wp[3] +
      matlab_node_B.In1_d.waypoint.roll * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.roll);
    matlab_node_B.X_u[0] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.x) * matlab_node_DW.idle_wp[0] +
      matlab_node_B.In1_d.waypoint.x * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.x);
    matlab_node_B.dv3[1] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.pitch) * matlab_node_DW.idle_wp[4] +
      matlab_node_B.In1_d.waypoint.pitch * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.pitch);
    matlab_node_B.X_u[1] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.y) * matlab_node_DW.idle_wp[1] +
      matlab_node_B.In1_d.waypoint.y * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.y);
    matlab_node_B.dv3[2] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.yaw) * matlab_node_DW.idle_wp[5] +
      matlab_node_B.In1_d.waypoint.yaw * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.yaw);
    matlab_node_B.X_u[2] = static_cast<real_T>
      (!matlab_node_B.In1_d.waypoint_mask.z) * matlab_node_DW.idle_wp[2] +
      matlab_node_B.In1_d.waypoint.z * static_cast<real_T>
      (matlab_node_B.In1_d.waypoint_mask.z);
    matlab_node_eulToQuat_c(matlab_node_B.dv3, matlab_node_B.dv1);
    matlab_node_B.X_u[3] = matlab_node_B.dv1[0];
    matlab_node_B.X_u[4] = matlab_node_B.dv1[1];
    matlab_node_B.X_u[5] = matlab_node_B.dv1[2];
    matlab_node_B.X_u[6] = matlab_node_B.dv1[3];
    matlab_node_B.X_u[7] = 0.0;
    matlab_node_B.X_u[10] = 0.0;
    matlab_node_B.X_u[8] = 0.0;
    matlab_node_B.X_u[11] = 0.0;
    matlab_node_B.X_u[9] = 0.0;
    matlab_node_B.X_u[12] = 0.0;
    matlab_node_B.qe_matlab[0] = ((matlab_node_B.rtb_delta_qe_idx_2 *
      matlab_node_B.dv1[3] - -matlab_node_B.X_est.qib[0] * matlab_node_B.dv1[0])
      - -matlab_node_B.X_est.qib[1] * matlab_node_B.dv1[1]) -
      -matlab_node_B.X_est.qib[2] * matlab_node_B.dv1[2];
    matlab_node_B.qe_matlab[1] = (matlab_node_B.rtb_delta_qe_idx_2 *
      matlab_node_B.dv1[0] + matlab_node_B.dv1[3] * -matlab_node_B.X_est.qib[0])
      + (-matlab_node_B.X_est.qib[1] * matlab_node_B.dv1[2] - matlab_node_B.dv1
         [1] * -matlab_node_B.X_est.qib[2]);
    matlab_node_B.qe_matlab[2] = (matlab_node_B.rtb_delta_qe_idx_2 *
      matlab_node_B.dv1[1] + matlab_node_B.dv1[3] * -matlab_node_B.X_est.qib[1])
      + (matlab_node_B.dv1[0] * -matlab_node_B.X_est.qib[2] -
         -matlab_node_B.X_est.qib[0] * matlab_node_B.dv1[2]);
    matlab_node_B.qe_matlab[3] = (matlab_node_B.rtb_delta_qe_idx_2 *
      matlab_node_B.dv1[2] + matlab_node_B.dv1[3] * -matlab_node_B.X_est.qib[2])
      + (-matlab_node_B.X_est.qib[0] * matlab_node_B.dv1[1] - matlab_node_B.dv1
         [0] * -matlab_node_B.X_est.qib[1]);
    matlab_node_B.qinv[0] = matlab_node_B.qe_matlab[1];
    matlab_node_B.qinv[1] = matlab_node_B.qe_matlab[2];
    matlab_node_B.qinv[2] = matlab_node_B.qe_matlab[3];
    matlab_node_B.qinv[3] = matlab_node_B.qe_matlab[0];
    if (matlab_node_B.qe_matlab[0] < 0.0) {
      matlab_node_B.qinv[0] = -matlab_node_B.qe_matlab[1];
      matlab_node_B.qinv[1] = -matlab_node_B.qe_matlab[2];
      matlab_node_B.qinv[2] = -matlab_node_B.qe_matlab[3];
      matlab_node_B.qinv[3] = -matlab_node_B.qe_matlab[0];
    }

    matlab_node_B.hold_timer = matlab_node_B.qinv[3] * matlab_node_B.qinv[3] *
      2.0 - 1.0;
    matlab_node_B.psi = 2.0 * matlab_node_B.qinv[3];
    for (i = 0; i < 3; i++) {
      matlab_node_B.theta = 2.0 * matlab_node_B.qinv[i];
      matlab_node_B.rotm[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
        matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.qinv[0];
      matlab_node_B.ret = 3 * i + 1;
      matlab_node_B.rotm[matlab_node_B.ret] =
        matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] *
        matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.qinv[1];
      matlab_node_B.ret = 3 * i + 2;
      matlab_node_B.rotm[matlab_node_B.ret] =
        matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] *
        matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.qinv[2];
    }

    matlab_node_B.theta = matlab_node_B.psi * 0.0;
    matlab_node_B.Cbi_c[0] = matlab_node_B.theta;
    matlab_node_B.Cbi_c[1] = matlab_node_B.psi * -matlab_node_B.qinv[2];
    matlab_node_B.Cbi_c[2] = matlab_node_B.psi * matlab_node_B.qinv[1];
    matlab_node_B.Cbi_c[3] = matlab_node_B.psi * matlab_node_B.qinv[2];
    matlab_node_B.Cbi_c[4] = matlab_node_B.theta;
    matlab_node_B.Cbi_c[5] = matlab_node_B.psi * -matlab_node_B.qinv[0];
    matlab_node_B.Cbi_c[6] = matlab_node_B.psi * -matlab_node_B.qinv[1];
    matlab_node_B.Cbi_c[7] = matlab_node_B.psi * matlab_node_B.qinv[0];
    matlab_node_B.Cbi_c[8] = matlab_node_B.theta;
    for (i = 0; i < 9; i++) {
      matlab_node_B.Cbi[i] = matlab_node_B.rotm[i] + matlab_node_B.Cbi_c[i];
    }

    matlab_node_B.theta = std::asin(std::fmax(-1.0, std::fmin(1.0,
      matlab_node_B.Cbi[6])));
    if (std::abs(std::cos(-matlab_node_B.theta)) < 1.0E-6) {
      matlab_node_B.phi = 0.0;
      matlab_node_B.psi = rt_atan2d_snf(-matlab_node_B.Cbi[1],
        matlab_node_B.Cbi[4]);
    } else {
      matlab_node_B.phi = rt_atan2d_snf(matlab_node_B.Cbi[7], matlab_node_B.Cbi
        [8]);
      matlab_node_B.psi = rt_atan2d_snf(matlab_node_B.Cbi[3], matlab_node_B.Cbi
        [0]);
    }

    matlab_node_wrapToPi(&matlab_node_B.phi);
    matlab_node_B.theta = -matlab_node_B.theta;
    matlab_node_wrapToPi(&matlab_node_B.theta);
    matlab_node_wrapToPi(&matlab_node_B.psi);
    matlab_node_B.b_x[0] = (std::abs(matlab_node_B.scale - matlab_node_B.X_u[0])
      < matlab_node_B.In1_d.tolerance.x);
    matlab_node_B.b_x[3] = (std::abs(matlab_node_B.phi) <
      matlab_node_B.In1_d.tolerance.roll);
    matlab_node_B.b_x[1] = (std::abs(matlab_node_B.absxk - matlab_node_B.X_u[1])
      < matlab_node_B.In1_d.tolerance.y);
    matlab_node_B.b_x[4] = (std::abs(matlab_node_B.theta) <
      matlab_node_B.In1_d.tolerance.pitch);
    matlab_node_B.b_x[2] = (std::abs(matlab_node_B.b_scale - matlab_node_B.X_u[2])
      < matlab_node_B.In1_d.tolerance.z);
    matlab_node_B.b_x[5] = (std::abs(matlab_node_B.psi) <
      matlab_node_B.In1_d.tolerance.yaw);
    rtb_OR1 = true;
    matlab_node_B.pos = 0;
    exitg1 = false;
    while ((!exitg1) && (matlab_node_B.pos < 6)) {
      if (!matlab_node_B.b_x[matlab_node_B.pos]) {
        rtb_OR1 = false;
        exitg1 = true;
      } else {
        matlab_node_B.pos++;
      }
    }

    if (rtb_OR1) {
      matlab_node_B.hold_timer = matlab_node_B.DigitalClock -
        matlab_node_DW.hold_timer_start_time;
    } else {
      matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
      matlab_node_B.hold_timer = 0.0;
    }

    if (matlab_node_B.hold_timer >= matlab_node_B.In1_d.hold_time) {
      rtb_cmd_status[0] = 83;
      rtb_cmd_status[1] = 85;
      rtb_cmd_status[2] = 67;
      rtb_cmd_status[3] = 67;
      matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
    } else {
      rtb_cmd_status[0] = 82;
      rtb_cmd_status[1] = 85;
      rtb_cmd_status[2] = 78;
      rtb_cmd_status[3] = 78;
    }

    for (i = 0; i < 6; i++) {
      matlab_node_DW.cmd_specific_wp[i] = matlab_node_DW.idle_wp[i];
    }
    break;

   case 1:
    matlab_nod_executeDurationTrick(matlab_node_B.In1_d.hold_time,
      matlab_node_B.cmd.trick_id, matlab_node_DW.idle_wp, matlab_node_B.X_est.Ri,
      matlab_node_B.X_est.Eul, matlab_node_B.X_est.Cib,
      &matlab_node_DW.hold_timer_start_time, matlab_node_B.DigitalClock, rtb_OR1,
      matlab_node_DW.cmd_specific_wp, rtb_cmd_status, &matlab_node_B.hold_timer,
      matlab_node_B.X_u);
    break;

   case 2:
    matlab_node_eulToQuat_c(&matlab_node_DW.idle_wp[3], matlab_node_B.dv1);
    matlab_node_B.X_u[0] = matlab_node_DW.idle_wp[0];
    matlab_node_B.X_u[1] = matlab_node_DW.idle_wp[1];
    matlab_node_B.X_u[2] = matlab_node_DW.idle_wp[2];
    matlab_node_B.X_u[3] = matlab_node_B.dv1[0];
    matlab_node_B.X_u[4] = matlab_node_B.dv1[1];
    matlab_node_B.X_u[5] = matlab_node_B.dv1[2];
    matlab_node_B.X_u[6] = matlab_node_B.dv1[3];
    matlab_node_B.X_u[7] = 0.0;
    matlab_node_B.X_u[10] = 0.0;
    matlab_node_B.X_u[8] = 0.0;
    matlab_node_B.X_u[11] = 0.0;
    matlab_node_B.X_u[9] = 0.0;
    matlab_node_B.X_u[12] = 0.0;
    matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
    rtb_cmd_status[0] = 82;
    rtb_cmd_status[1] = 85;
    rtb_cmd_status[2] = 78;
    rtb_cmd_status[3] = 78;
    matlab_node_DW.mission_is_started = false;
    break;

   default:
    matlab_node_eulToQuat_c(&matlab_node_DW.idle_wp[3], matlab_node_B.dv1);
    matlab_node_B.X_u[0] = matlab_node_DW.idle_wp[0];
    matlab_node_B.X_u[1] = matlab_node_DW.idle_wp[1];
    matlab_node_B.X_u[2] = matlab_node_DW.idle_wp[2];
    matlab_node_B.X_u[3] = matlab_node_B.dv1[0];
    matlab_node_B.X_u[4] = matlab_node_B.dv1[1];
    matlab_node_B.X_u[5] = matlab_node_B.dv1[2];
    matlab_node_B.X_u[6] = matlab_node_B.dv1[3];
    matlab_node_B.X_u[7] = 0.0;
    matlab_node_B.X_u[10] = 0.0;
    matlab_node_B.X_u[8] = 0.0;
    matlab_node_B.X_u[11] = 0.0;
    matlab_node_B.X_u[9] = 0.0;
    matlab_node_B.X_u[12] = 0.0;
    matlab_node_DW.hold_timer_start_time = matlab_node_B.DigitalClock;
    rtb_cmd_status[0] = 82;
    rtb_cmd_status[1] = 85;
    rtb_cmd_status[2] = 78;
    rtb_cmd_status[3] = 78;
    break;
  }

  // MATLAB Function: '<S5>/quatToEul'
  matlab_node_B.hold_timer = matlab_node_B.X_u[6] * matlab_node_B.X_u[6] * 2.0 -
    1.0;
  matlab_node_B.psi = 2.0 * matlab_node_B.X_u[6];
  for (i = 0; i < 3; i++) {
    matlab_node_B.theta = matlab_node_B.X_u[i + 3] * 2.0;
    matlab_node_B.rotm[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
      matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.X_u[3];
    matlab_node_B.ret = 3 * i + 1;
    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] *
      matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.X_u[4];
    matlab_node_B.ret = 3 * i + 2;
    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] *
      matlab_node_B.hold_timer + matlab_node_B.theta * matlab_node_B.X_u[5];
  }

  matlab_node_B.theta = matlab_node_B.psi * 0.0;
  matlab_node_B.Cbi_c[0] = matlab_node_B.theta;
  matlab_node_B.Cbi_c[1] = matlab_node_B.psi * -matlab_node_B.X_u[5];
  matlab_node_B.Cbi_c[2] = matlab_node_B.psi * matlab_node_B.X_u[4];
  matlab_node_B.Cbi_c[3] = matlab_node_B.psi * matlab_node_B.X_u[5];
  matlab_node_B.Cbi_c[4] = matlab_node_B.theta;
  matlab_node_B.Cbi_c[5] = matlab_node_B.psi * -matlab_node_B.X_u[3];
  matlab_node_B.Cbi_c[6] = matlab_node_B.psi * -matlab_node_B.X_u[4];
  matlab_node_B.Cbi_c[7] = matlab_node_B.psi * matlab_node_B.X_u[3];
  matlab_node_B.Cbi_c[8] = matlab_node_B.theta;
  for (i = 0; i < 9; i++) {
    matlab_node_B.Cbi[i] = matlab_node_B.rotm[i] + matlab_node_B.Cbi_c[i];
  }

  matlab_node_B.theta = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_node_B.theta)) < 1.0E-6) {
    // SignalConversion generated from: '<S14>/ SFunction ' incorporates:
    //   MATLAB Function: '<S3>/MATLAB Function'

    matlab_node_B.TmpSignalConversionAtSFunct[3] = 0.0;
    matlab_node_B.TmpSignalConversionAtSFunct[5] = rt_atan2d_snf
      (-matlab_node_B.Cbi[1], matlab_node_B.Cbi[4]);
  } else {
    // SignalConversion generated from: '<S14>/ SFunction ' incorporates:
    //   MATLAB Function: '<S3>/MATLAB Function'

    matlab_node_B.TmpSignalConversionAtSFunct[3] = rt_atan2d_snf
      (matlab_node_B.Cbi[7], matlab_node_B.Cbi[8]);
    matlab_node_B.TmpSignalConversionAtSFunct[5] = rt_atan2d_snf
      (matlab_node_B.Cbi[3], matlab_node_B.Cbi[0]);
  }

  // SignalConversion generated from: '<S14>/ SFunction ' incorporates:
  //   MATLAB Function: '<S3>/MATLAB Function'
  //   MATLAB Function: '<S5>/quatToEul'

  matlab_node_wrapToPi(&matlab_node_B.TmpSignalConversionAtSFunct[3]);
  matlab_node_B.TmpSignalConversionAtSFunct[4] = -matlab_node_B.theta;
  matlab_node_wrapToPi(&matlab_node_B.TmpSignalConversionAtSFunct[4]);
  matlab_node_wrapToPi(&matlab_node_B.TmpSignalConversionAtSFunct[5]);

  // DataTypeConversion: '<S5>/Cast1' incorporates:
  //   DataStoreRead: '<S5>/Data Store Read5'
  //   DataStoreWrite: '<S5>/Data Store Write8'

  debug_start_new_cmd_flag = matlab_node_DW.start_new_cmd_flag;

  // Outputs for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S17>/Subsystem Enable'

  // MATLAB Function: '<S17>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S10>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S5>/Unit Delay2'

  matlab_node_DW.prior_action_id_not_empty = true;
  matlab_node_B.Ri_xy_e[0] = matlab_node_B.X_u[0] - matlab_node_B.scale;
  matlab_node_B.Ri_xy_e[1] = matlab_node_B.X_u[1] - matlab_node_B.absxk;
  matlab_node_DW.UnitDelay3_DSTATE = rt_atan2d_snf(matlab_node_B.Ri_xy_e[1],
    matlab_node_B.Ri_xy_e[0]);
  matlab_node_B.DigitalClock = matlab_node_norm(matlab_node_B.Ri_xy_e);
  if (matlab_node_B.DigitalClock >= 1.0) {
    matlab_node_B.dv3[0] = 0.0;
    matlab_node_B.dv3[1] = 0.0;
    matlab_node_B.dv3[2] = matlab_node_DW.UnitDelay3_DSTATE;
    matlab_node_eulToRotm(matlab_node_B.dv3, matlab_node_B.rotm);
    matlab_node_rotmToQuat(matlab_node_B.rotm, matlab_node_B.qe_matlab);
  } else {
    matlab_node_quatToEul(&matlab_node_B.X_u[3], matlab_node_B.R_error);
    matlab_node_B.qe_matlab[0] = matlab_node_B.X_u[3];
    matlab_node_B.qe_matlab[1] = matlab_node_B.X_u[4];
    matlab_node_B.qe_matlab[2] = matlab_node_B.X_u[5];
    matlab_node_B.qe_matlab[3] = matlab_node_B.X_u[6];
  }

  matlab_node_quatToEul(matlab_node_B.qe_matlab, matlab_node_B.eps_g);
  rtb_OR1 = false;
  b_p = true;
  matlab_node_B.ret = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_node_B.ret < 16)) {
    if (matlab_node_B.s[matlab_node_B.ret] != c[matlab_node_B.ret]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_node_B.ret++;
    }
  }

  if (b_p) {
    rtb_OR1 = true;
  }

  if (rtb_OR1) {
    matlab_node_B.qe_matlab[0] = matlab_node_B.X_u[3];
    matlab_node_B.qe_matlab[1] = matlab_node_B.X_u[4];
    matlab_node_B.qe_matlab[2] = matlab_node_B.X_u[5];
    matlab_node_B.qe_matlab[3] = matlab_node_B.X_u[6];
    for (i = 0; i < 16; i++) {
      matlab_node_B.x1[i] = matlab_node_B.cmd.trick_id[i];
    }

    rtb_OR1 = false;
    b_p = true;
    matlab_node_B.pos = 0;
    exitg1 = false;
    while ((!exitg1) && (matlab_node_B.pos < 16)) {
      if (matlab_node_B.x1[matlab_node_B.pos] != d[matlab_node_B.pos]) {
        b_p = false;
        exitg1 = true;
      } else {
        matlab_node_B.pos++;
      }
    }

    if (b_p) {
      rtb_OR1 = true;
    }

    if (rtb_OR1) {
      matlab_node_quatToEul(&matlab_node_B.X_u[3], matlab_node_B.eps);
      matlab_node_B.dv3[0] = 0.0;
      matlab_node_B.dv3[1] = matlab_node_B.eps[1];
      matlab_node_B.dv3[2] = matlab_node_B.eps[2];
      matlab_node_eulToRotm(matlab_node_B.dv3, matlab_node_B.rotm);
      matlab_node_rotmToQuat(matlab_node_B.rotm, matlab_node_B.qe_matlab);
    }
  }

  matlab_node_B.hold_timer = ((matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[3] - -matlab_node_B.X_est.qib[0] *
    matlab_node_B.qe_matlab[0]) - -matlab_node_B.X_est.qib[1] *
    matlab_node_B.qe_matlab[1]) - -matlab_node_B.X_est.qib[2] *
    matlab_node_B.qe_matlab[2];
  matlab_node_B.qe_matlab_idx_1 = (matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[0] + matlab_node_B.qe_matlab[3] *
    -matlab_node_B.X_est.qib[0]) + (-matlab_node_B.X_est.qib[1] *
    matlab_node_B.qe_matlab[2] - matlab_node_B.qe_matlab[1] *
    -matlab_node_B.X_est.qib[2]);
  matlab_node_B.qe_matlab_idx_2 = (matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[1] + matlab_node_B.qe_matlab[3] *
    -matlab_node_B.X_est.qib[1]) + (matlab_node_B.qe_matlab[0] *
    -matlab_node_B.X_est.qib[2] - -matlab_node_B.X_est.qib[0] *
    matlab_node_B.qe_matlab[2]);
  matlab_node_B.qe_matlab_idx_3 = (matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[2] + matlab_node_B.qe_matlab[3] *
    -matlab_node_B.X_est.qib[2]) + (-matlab_node_B.X_est.qib[0] *
    matlab_node_B.qe_matlab[1] - matlab_node_B.qe_matlab[0] *
    -matlab_node_B.X_est.qib[1]);
  matlab_node_B.qinv[0] = matlab_node_B.qe_matlab_idx_1;
  matlab_node_B.qinv[1] = matlab_node_B.qe_matlab_idx_2;
  matlab_node_B.qinv[2] = matlab_node_B.qe_matlab_idx_3;
  matlab_node_B.qinv[3] = matlab_node_B.hold_timer;
  if (matlab_node_B.hold_timer < 0.0) {
    matlab_node_B.qinv[0] = -matlab_node_B.qe_matlab_idx_1;
    matlab_node_B.qinv[1] = -matlab_node_B.qe_matlab_idx_2;
    matlab_node_B.qinv[2] = -matlab_node_B.qe_matlab_idx_3;
    matlab_node_B.qinv[3] = -matlab_node_B.hold_timer;
  }

  matlab_node_quatToEul(matlab_node_B.qinv, matlab_node_B.eps);
  matlab_node_B.R_error[0] = std::abs(matlab_node_B.eps[0]);
  matlab_node_B.R_error[1] = std::abs(matlab_node_B.eps[1]);
  matlab_node_B.R_error[2] = std::abs(matlab_node_B.eps[2]);
  if (!std::isnan(matlab_node_B.R_error[0])) {
    matlab_node_B.ret = 1;
  } else {
    matlab_node_B.ret = 0;
    i = 2;
    exitg1 = false;
    while ((!exitg1) && (i < 4)) {
      if (!std::isnan(matlab_node_B.R_error[i - 1])) {
        matlab_node_B.ret = i;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }

  if (matlab_node_B.ret == 0) {
    matlab_node_B.hold_timer = matlab_node_B.R_error[0];
  } else {
    matlab_node_B.hold_timer = matlab_node_B.R_error[matlab_node_B.ret - 1];
    for (i = matlab_node_B.ret + 1; i < 4; i++) {
      matlab_node_B.theta = matlab_node_B.R_error[i - 1];
      if (matlab_node_B.hold_timer < matlab_node_B.theta) {
        matlab_node_B.hold_timer = matlab_node_B.theta;
      }
    }
  }

  if (matlab_node_B.hold_timer > 0.17453292519943295) {
    matlab_node_B.eps[0] = 0.0;
    matlab_node_B.eps[1] = 0.0;
    matlab_node_B.eps[2] = 0.0;
    matlab_node_B.ret = 1;
  } else if (matlab_node_B.DigitalClock >= 1.0) {
    matlab_node_B.eps[0] = matlab_node_B.DigitalClock;
    matlab_node_B.eps[1] = 0.0;
    matlab_node_B.eps[2] = matlab_node_B.X_u[2] - matlab_node_B.b_scale;
    matlab_node_B.ret = 2;
  } else {
    for (i = 0; i < 3; i++) {
      matlab_node_B.DigitalClock = 2.0 * matlab_node_B.X_est.qib[i];
      matlab_node_B.rotm[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
        matlab_node_B.b_absxk + matlab_node_B.DigitalClock *
        matlab_node_B.X_est.qib[0];
      matlab_node_B.ret = 3 * i + 1;
      matlab_node_B.rotm[matlab_node_B.ret] =
        matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk
        + matlab_node_B.DigitalClock * matlab_node_B.X_est.qib[1];
      matlab_node_B.ret = 3 * i + 2;
      matlab_node_B.rotm[matlab_node_B.ret] =
        matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk
        + matlab_node_B.DigitalClock * matlab_node_B.X_est.qib[2];
    }

    matlab_node_B.Cbi_c[0] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
    matlab_node_B.Cbi_c[1] = matlab_node_B.rtb_FilterCoefficient_h_idx_0;
    matlab_node_B.Cbi_c[2] = matlab_node_B.rtb_Filter_h_idx_0;
    matlab_node_B.Cbi_c[3] = matlab_node_B.rtb_Integrator_p_idx_0;
    matlab_node_B.Cbi_c[4] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
    matlab_node_B.Cbi_c[5] = matlab_node_B.rtb_Filter_h_idx_1;
    matlab_node_B.Cbi_c[6] = matlab_node_B.lower_voltage_index;
    matlab_node_B.Cbi_c[7] = matlab_node_B.rtb_Cbi_tmp_tmp_e;
    matlab_node_B.Cbi_c[8] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
    for (i = 0; i < 9; i++) {
      matlab_node_B.Cbi[i] = matlab_node_B.rotm[i] + matlab_node_B.Cbi_c[i];
    }

    matlab_node_B.theta = 0.0;
    matlab_node_B.DigitalClock = 0.0;
    matlab_node_B.hold_timer = 0.0;
    for (i = 0; i < 3; i++) {
      matlab_node_B.phi = matlab_node_B.X_u[i];
      matlab_node_B.theta += matlab_node_B.Cbi[3 * i] * matlab_node_B.phi;
      matlab_node_B.DigitalClock += matlab_node_B.Cbi[3 * i + 1] *
        matlab_node_B.phi;
      matlab_node_B.hold_timer += matlab_node_B.Cbi[3 * i + 2] *
        matlab_node_B.phi;
    }

    matlab_node_B.R_error[2] = matlab_node_B.hold_timer;
    matlab_node_B.R_error[1] = matlab_node_B.DigitalClock;
    matlab_node_B.R_error[0] = matlab_node_B.theta;
    for (i = 0; i < 3; i++) {
      matlab_node_B.eps[i] = matlab_node_B.R_error[i] - ((matlab_node_B.Cbi[i +
        3] * matlab_node_B.absxk + matlab_node_B.Cbi[i] * matlab_node_B.scale) +
        matlab_node_B.Cbi[i + 6] * matlab_node_B.b_scale);
    }

    matlab_node_B.ret = 3;
  }

  matlab_node_DW.UnitDelay2_DSTATE = matlab_node_B.ret;

  // Gain: '<S17>/Gain5' incorporates:
  //   DataStoreWrite: '<S17>/Data Store Write1'
  //   RelationalOperator: '<S21>/FixPt Relational Operator'
  //   UnitDelay: '<S21>/Delay Input1'
  //   UnitDelay: '<S5>/Unit Delay2'
  //
  //  Block description for '<S21>/Delay Input1':
  //
  //   Store in Global RAM

  integrator_reset = static_cast<uint8_T>((matlab_node_DW.UnitDelay2_DSTATE !=
    matlab_node_DW.DelayInput1_DSTATE) << 7);

  // MATLAB Function: '<S17>/quatInjector' incorporates:
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   UnitDelay: '<S5>/Unit Delay2'

  matlab_node_B.R_error[1] = matlab_node_B.b_t;
  matlab_node_B.R_error[2] = matlab_node_B.t;
  if ((matlab_node_DW.UnitDelay2_DSTATE == 2.0) ||
      (matlab_node_DW.UnitDelay2_DSTATE == 1.0)) {
    for (i = 0; i < 16; i++) {
      matlab_node_B.x1[i] = matlab_node_B.cmd.trick_id[i];
    }

    matlab_node_B.ret = std::memcmp(&a_0[0], &matlab_node_B.x1[0], 16);
    if (matlab_node_B.ret == 0) {
      matlab_node_B.R_error[0] = matlab_node_B.eta + 3.1;
      matlab_node_eulToQuat(matlab_node_B.R_error, matlab_node_B.qe_matlab);
    }
  }

  // End of MATLAB Function: '<S17>/quatInjector'

  // DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read6'

  if ((integrator_reset > 0) && (matlab_node_DW.DiscreteTimeIntegrator_PrevRese <=
       0)) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0;
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0;
  }

  // MATLAB Function: '<S17>/deltaQuatError' incorporates:
  //   MATLAB Function: '<S10>/discreteTimeQuatPropagation'
  //   MATLAB Function: '<S17>/guidanceLaw'
  //   MATLAB Function: '<S17>/quatPID'

  matlab_node_B.phi = ((matlab_node_B.rtb_delta_qe_idx_2 *
                        matlab_node_B.qe_matlab[3] - -matlab_node_B.X_est.qib[0]
                        * matlab_node_B.qe_matlab[0]) -
                       -matlab_node_B.X_est.qib[1] * matlab_node_B.qe_matlab[1])
    - -matlab_node_B.X_est.qib[2] * matlab_node_B.qe_matlab[2];
  matlab_node_B.eps_n = (matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[0] + matlab_node_B.qe_matlab[3] *
    -matlab_node_B.X_est.qib[0]) + (-matlab_node_B.X_est.qib[1] *
    matlab_node_B.qe_matlab[2] - matlab_node_B.qe_matlab[1] *
    -matlab_node_B.X_est.qib[2]);
  matlab_node_B.DigitalClock = matlab_node_B.eps_n;
  matlab_node_B.psi = (matlab_node_B.rtb_delta_qe_idx_2 *
                       matlab_node_B.qe_matlab[1] + matlab_node_B.qe_matlab[3] *
                       -matlab_node_B.X_est.qib[1]) + (matlab_node_B.qe_matlab[0]
    * -matlab_node_B.X_est.qib[2] - -matlab_node_B.X_est.qib[0] *
    matlab_node_B.qe_matlab[2]);
  matlab_node_B.hold_timer = matlab_node_B.psi;
  matlab_node_B.rtb_delta_qe_idx_2_tmp = (matlab_node_B.rtb_delta_qe_idx_2 *
    matlab_node_B.qe_matlab[2] + matlab_node_B.qe_matlab[3] *
    -matlab_node_B.X_est.qib[2]) + (-matlab_node_B.X_est.qib[0] *
    matlab_node_B.qe_matlab[1] - matlab_node_B.qe_matlab[0] *
    -matlab_node_B.X_est.qib[1]);
  matlab_node_B.rtb_delta_qe_idx_2 = matlab_node_B.rtb_delta_qe_idx_2_tmp;
  matlab_node_B.rtb_delta_qe_idx_3 = matlab_node_B.phi;
  if (matlab_node_B.phi < 0.0) {
    matlab_node_B.DigitalClock = -matlab_node_B.eps_n;
    matlab_node_B.hold_timer = -matlab_node_B.psi;
    matlab_node_B.rtb_delta_qe_idx_2 = -matlab_node_B.rtb_delta_qe_idx_2_tmp;
    matlab_node_B.rtb_delta_qe_idx_3 = -matlab_node_B.phi;
  }

  rtb_OR1 = false;
  if (std::isnan(matlab_node_B.rtb_delta_qe_idx_3)) {
    matlab_node_B.theta = (rtNaN);
  } else {
    matlab_node_B.theta = (matlab_node_B.rtb_delta_qe_idx_3 > 0.0);
  }

  if (matlab_node_B.theta == 0.0) {
    rtb_OR1 = true;
  }

  if (!rtb_OR1) {
    matlab_node_B.DigitalClock *= matlab_node_B.theta;
    matlab_node_B.hold_timer *= matlab_node_B.theta;
    matlab_node_B.rtb_delta_qe_idx_2 *= matlab_node_B.theta;
    matlab_node_B.rtb_delta_qe_idx_3 *= matlab_node_B.theta;
  }

  // SignalConversion generated from: '<S17>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S17>/deltaQuatError'

  matlab_node_B.qe_matlab_g[0] = 1.0 - matlab_node_B.rtb_delta_qe_idx_3;
  matlab_node_B.qe_matlab_g[1] = 0.0 - matlab_node_B.DigitalClock;
  matlab_node_B.qe_matlab_g[2] = 0.0 - matlab_node_B.hold_timer;
  matlab_node_B.qe_matlab_g[3] = 0.0 - matlab_node_B.rtb_delta_qe_idx_2;

  // DiscreteTransferFcn: '<S17>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S17>/deltaQuatError'

  matlab_node_B.qe_matlab_idx_1 = ((1.0 - matlab_node_B.rtb_delta_qe_idx_3) -
    (-matlab_node_DW.DiscreteTransferFcn_states[0])) / 1.1;
  matlab_node_B.qe_matlab_idx_2 = matlab_node_B.qe_matlab_idx_1;
  matlab_node_B.DiscreteTransferFcn[0] = 10.0 * matlab_node_B.qe_matlab_idx_1 +
    -10.0 * matlab_node_DW.DiscreteTransferFcn_states[0];
  matlab_node_B.qe_matlab_idx_1 = ((0.0 - matlab_node_B.DigitalClock) -
    (-matlab_node_DW.DiscreteTransferFcn_states[1])) / 1.1;
  matlab_node_B.qe_matlab_idx_3 = matlab_node_B.qe_matlab_idx_1;
  matlab_node_B.DiscreteTransferFcn[1] = 10.0 * matlab_node_B.qe_matlab_idx_1 +
    -10.0 * matlab_node_DW.DiscreteTransferFcn_states[1];
  matlab_node_B.qe_matlab_idx_1 = ((0.0 - matlab_node_B.hold_timer) -
    (-matlab_node_DW.DiscreteTransferFcn_states[2])) / 1.1;
  matlab_node_B.DiscreteTransferFcn_tmp_idx_2 = matlab_node_B.qe_matlab_idx_1;
  matlab_node_B.DiscreteTransferFcn[2] = 10.0 * matlab_node_B.qe_matlab_idx_1 +
    -10.0 * matlab_node_DW.DiscreteTransferFcn_states[2];
  matlab_node_B.qe_matlab_idx_1 = ((0.0 - matlab_node_B.rtb_delta_qe_idx_2) -
    (-matlab_node_DW.DiscreteTransferFcn_states[3])) / 1.1;
  matlab_node_B.DiscreteTransferFcn[3] = 10.0 * matlab_node_B.qe_matlab_idx_1 +
    -10.0 * matlab_node_DW.DiscreteTransferFcn_states[3];

  // MATLAB Function: '<S17>/quatPID' incorporates:
  //   DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
  //   Gain: '<S17>/Gain1'
  //   Gain: '<S17>/Gain2'
  //   SignalConversion generated from: '<S17>/Discrete Transfer Fcn'

  matlab_node_B.qinv[0] = matlab_node_B.eps_n;
  matlab_node_B.qinv[1] = matlab_node_B.psi;
  matlab_node_B.qinv[2] = matlab_node_B.rtb_delta_qe_idx_2_tmp;
  matlab_node_B.qinv[3] = matlab_node_B.phi;
  if (matlab_node_B.phi < 0.0) {
    matlab_node_B.qinv[0] = -matlab_node_B.eps_n;
    matlab_node_B.qinv[1] = -matlab_node_B.psi;
    matlab_node_B.qinv[2] = -matlab_node_B.rtb_delta_qe_idx_2_tmp;
    matlab_node_B.qinv[3] = -matlab_node_B.phi;
  }

  matlab_node_B.Qe1[0] = -matlab_node_B.qinv[0];
  matlab_node_B.Qe1[4] = -matlab_node_B.qinv[1];
  matlab_node_B.Qe1[8] = -matlab_node_B.qinv[2];
  matlab_node_B.Qe1[1] = matlab_node_B.qinv[3];
  matlab_node_B.Qe1[5] = -matlab_node_B.qinv[2];
  matlab_node_B.Qe1[9] = matlab_node_B.qinv[1];
  matlab_node_B.Qe1[2] = matlab_node_B.qinv[2];
  matlab_node_B.Qe1[6] = matlab_node_B.qinv[3];
  matlab_node_B.Qe1[10] = -matlab_node_B.qinv[0];
  matlab_node_B.Qe1[3] = -matlab_node_B.qinv[1];
  matlab_node_B.Qe1[7] = matlab_node_B.qinv[0];
  matlab_node_B.Qe1[11] = matlab_node_B.qinv[3];
  matlab_node_B.eps_n = 0.0;
  matlab_node_B.theta = 0.0;
  matlab_node_B.psi = 0.0;
  matlab_node_B.rtb_delta_qe_idx_2_tmp = 0.0;
  for (i = 0; i < 4; i++) {
    matlab_node_B.Qe1_b = 0.0;
    matlab_node_B.Qe1_l = 0.0;
    matlab_node_B.Qe1_h = 0.0;
    matlab_node_B.Qe1_bn = 0.0;
    for (matlab_node_B.ret = 0; matlab_node_B.ret < 3; matlab_node_B.ret++) {
      matlab_node_B.pos = matlab_node_B.ret << 2;
      matlab_node_B.phi = matlab_node_B.Qe1[matlab_node_B.pos + i];
      matlab_node_B.Qe1_b += matlab_node_B.Qe1[matlab_node_B.pos] *
        matlab_node_B.phi;
      matlab_node_B.Qe1_l += matlab_node_B.Qe1[matlab_node_B.pos + 1] *
        matlab_node_B.phi;
      matlab_node_B.Qe1_h += matlab_node_B.Qe1[matlab_node_B.pos + 2] *
        matlab_node_B.phi;
      matlab_node_B.Qe1_bn += matlab_node_B.Qe1[matlab_node_B.pos + 3] *
        matlab_node_B.phi;
    }

    matlab_node_B.ret = i << 2;
    matlab_node_B.c_a[matlab_node_B.ret + 3] = matlab_node_B.Qe1_bn;
    matlab_node_B.c_a[matlab_node_B.ret + 2] = matlab_node_B.Qe1_h;
    matlab_node_B.c_a[matlab_node_B.ret + 1] = matlab_node_B.Qe1_l;
    matlab_node_B.c_a[matlab_node_B.ret] = matlab_node_B.Qe1_b;
    matlab_node_B.dv1[i] = (matlab_node_ConstP.Gain1_Gain[i] *
      matlab_node_B.qe_matlab_g[i] + 0.0 *
      matlab_node_DW.DiscreteTimeIntegrator_DSTATE[i]) +
      matlab_node_B.DiscreteTransferFcn[i];
    matlab_node_B.phi = matlab_node_B.dv1[i];
    matlab_node_B.eps_n += matlab_node_B.c_a[matlab_node_B.ret] *
      matlab_node_B.phi;
    matlab_node_B.theta += matlab_node_B.c_a[matlab_node_B.ret + 1] *
      matlab_node_B.phi;
    matlab_node_B.psi += matlab_node_B.c_a[matlab_node_B.ret + 2] *
      matlab_node_B.phi;
    matlab_node_B.rtb_delta_qe_idx_2_tmp += matlab_node_B.c_a[matlab_node_B.ret
      + 3] * matlab_node_B.phi;
  }

  matlab_node_B.Qe1[0] = matlab_node_B.qinv[0];
  matlab_node_B.Qe1[1] = matlab_node_B.qinv[1];
  matlab_node_B.Qe1[2] = matlab_node_B.qinv[2];
  matlab_node_B.Qe1[3] = -matlab_node_B.qinv[3];
  matlab_node_B.Qe1[4] = -matlab_node_B.qinv[2];
  matlab_node_B.Qe1[5] = matlab_node_B.qinv[1];
  matlab_node_B.Qe1[6] = matlab_node_B.qinv[2];
  matlab_node_B.Qe1[7] = -matlab_node_B.qinv[3];
  matlab_node_B.Qe1[8] = -matlab_node_B.qinv[0];
  matlab_node_B.Qe1[9] = -matlab_node_B.qinv[1];
  matlab_node_B.Qe1[10] = matlab_node_B.qinv[0];
  matlab_node_B.Qe1[11] = -matlab_node_B.qinv[3];
  matlab_node_B.dv1[0] = 2.0 * matlab_node_B.eps_n;
  matlab_node_B.dv1[1] = 2.0 * matlab_node_B.theta;
  matlab_node_B.dv1[2] = 2.0 * matlab_node_B.psi;
  matlab_node_B.dv1[3] = 2.0 * matlab_node_B.rtb_delta_qe_idx_2_tmp;
  matlab_node_B.eps_n = 0.0;
  matlab_node_B.theta = 0.0;
  matlab_node_B.psi = 0.0;
  for (i = 0; i < 4; i++) {
    matlab_node_B.phi = matlab_node_B.dv1[i];
    matlab_node_B.eps_n += matlab_node_B.Qe1[3 * i] * matlab_node_B.phi;
    matlab_node_B.theta += matlab_node_B.Qe1[3 * i + 1] * matlab_node_B.phi;
    matlab_node_B.psi += matlab_node_B.Qe1[3 * i + 2] * matlab_node_B.phi;
  }

  matlab_node_B.eps_g[2] = matlab_node_B.psi;
  matlab_node_B.eps_g[1] = matlab_node_B.theta;
  matlab_node_B.eps_g[0] = matlab_node_B.eps_n;

  // DiscreteIntegrator: '<S127>/Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read1'

  if ((integrator_reset > 0) && (matlab_node_DW.Integrator_PrevResetState <= 0))
  {
    matlab_node_DW.Integrator_DSTATE[0] = 0.0;
    matlab_node_DW.Integrator_DSTATE[1] = 0.0;
    matlab_node_DW.Integrator_DSTATE[2] = 0.0;
  }

  // DiscreteIntegrator: '<S122>/Filter' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read1'

  if ((integrator_reset > 0) && (matlab_node_DW.Filter_PrevResetState <= 0)) {
    matlab_node_DW.Filter_DSTATE[0] = 0.0;
    matlab_node_DW.Filter_DSTATE[1] = 0.0;
    matlab_node_DW.Filter_DSTATE[2] = 0.0;
  }

  for (i = 0; i < 3; i++) {
    // Gain: '<S120>/Derivative Gain'
    matlab_node_B.eps_n = matlab_node_B.eps[i];

    // Gain: '<S130>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S122>/Filter'
    //   Gain: '<S120>/Derivative Gain'
    //   Sum: '<S122>/SumD'

    matlab_node_B.theta = (0.0 * matlab_node_B.eps_n -
      matlab_node_DW.Filter_DSTATE[i]) * 100.0;
    matlab_node_B.R_error[i] = matlab_node_B.theta;

    // Sum: '<S136>/Sum' incorporates:
    //   DiscreteIntegrator: '<S127>/Integrator'
    //   Gain: '<S124>/Integral Gain'
    //   Gain: '<S130>/Filter Coefficient'
    //   Gain: '<S132>/Proportional Gain'

    matlab_node_B.phi = (matlab_node_ConstP.ProportionalGain_Gain[i] *
                         matlab_node_B.eps_n +
                         matlab_node_DW.Integrator_DSTATE[i]) +
      matlab_node_B.theta;
    matlab_node_B.eul_error[i] = matlab_node_B.phi;

    // Saturate: '<S134>/Saturation'
    if (matlab_node_B.phi > 1.0) {
      // MATLAB Function: '<S17>/dRbSetpointInjector'
      matlab_node_B.dRb_u[i] = 1.0;
    } else if (matlab_node_B.phi < -1.0) {
      // MATLAB Function: '<S17>/dRbSetpointInjector'
      matlab_node_B.dRb_u[i] = -1.0;
    } else {
      // MATLAB Function: '<S17>/dRbSetpointInjector'
      matlab_node_B.dRb_u[i] = matlab_node_B.phi;
    }

    // End of Saturate: '<S134>/Saturation'

    // MATLAB Function: '<S17>/quatToRotm' incorporates:
    //   DataStoreRead: '<S17>/Data Store Read'
    //   DataStoreWrite: '<S17>/Data Store Write'
    //   Math: '<S17>/Transpose'

    matlab_node_B.theta = 2.0 * matlab_node_B.X_est.qib[i];
    matlab_node_B.rotm[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
      matlab_node_B.b_absxk + matlab_node_B.theta * matlab_node_B.X_est.qib[0];

    // Math: '<S17>/Transpose' incorporates:
    //   DataStoreRead: '<S17>/Data Store Read'
    //   DataStoreWrite: '<S17>/Data Store Write'
    //   MATLAB Function: '<S17>/quatToRotm'

    matlab_node_B.ret = 3 * i + 1;

    // MATLAB Function: '<S17>/quatToRotm' incorporates:
    //   DataStoreRead: '<S17>/Data Store Read'
    //   DataStoreWrite: '<S17>/Data Store Write'
    //   Math: '<S17>/Transpose'

    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk +
      matlab_node_B.theta * matlab_node_B.X_est.qib[1];

    // Math: '<S17>/Transpose' incorporates:
    //   DataStoreRead: '<S17>/Data Store Read'
    //   DataStoreWrite: '<S17>/Data Store Write'
    //   MATLAB Function: '<S17>/quatToRotm'

    matlab_node_B.ret = 3 * i + 2;

    // MATLAB Function: '<S17>/quatToRotm' incorporates:
    //   DataStoreRead: '<S17>/Data Store Read'
    //   DataStoreWrite: '<S17>/Data Store Write'
    //   Math: '<S17>/Transpose'

    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk +
      matlab_node_B.theta * matlab_node_B.X_est.qib[2];
  }

  // Math: '<S17>/Transpose'
  matlab_node_B.Cbi_c[0] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.Cbi_c[1] = matlab_node_B.rtb_FilterCoefficient_h_idx_0;
  matlab_node_B.Cbi_c[2] = matlab_node_B.rtb_Filter_h_idx_0;
  matlab_node_B.Cbi_c[3] = matlab_node_B.rtb_Integrator_p_idx_0;
  matlab_node_B.Cbi_c[4] = matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.Cbi_c[5] = matlab_node_B.rtb_Filter_h_idx_1;
  matlab_node_B.Cbi_c[6] = matlab_node_B.lower_voltage_index;
  matlab_node_B.Cbi_c[7] = matlab_node_B.rtb_Cbi_tmp_tmp_e;
  matlab_node_B.Cbi_c[8] = matlab_node_B.rtb_Cbi_tmp_tmp_d;

  // MATLAB Function: '<S17>/quatToRotm'
  for (i = 0; i < 9; i++) {
    matlab_node_B.Cbi[i] = matlab_node_B.rotm[i] + matlab_node_B.Cbi_c[i];
  }

  for (i = 0; i < 3; i++) {
    // Sum: '<S17>/Subtract4' incorporates:
    //   MATLAB Function: '<S10>/derivedStateEstimates'
    //   Product: '<S17>/Matrix Multiply3'

    matlab_node_B.dRb_e[i] = matlab_node_B.dRb_u[i] - ((matlab_node_B.Cbi[i + 3]
      * matlab_node_B.rtb_X_est_idx_1 + matlab_node_B.Cbi[i] *
      matlab_node_B.rtb_X_est_idx_0) + matlab_node_B.Cbi[i + 6] *
      matlab_node_B.rtb_X_est_idx_2);

    // MATLAB Function: '<S17>/rateInjector' incorporates:
    //   SignalConversion generated from: '<S17>/Bus Selector'
    //   Sum: '<S17>/Subtract'

    matlab_node_B.eps_g[i] -= matlab_node_B.X_est.wb[i];
  }

  // MATLAB Function: '<S17>/rateInjector' incorporates:
  //   DiscreteIntegrator: '<S10>/Velocity Integrator'
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S17>/trickFTListInjector'
  //   Product: '<S10>/Matrix Multiply2'

  rtb_OR1 = matlab_node_isequal(matlab_node_B.s);
  if (rtb_OR1) {
    for (i = 0; i < 16; i++) {
      matlab_node_B.x1[i] = matlab_node_B.cmd.trick_id[i];
    }

    matlab_node_B.ret = std::memcmp(&a_1[0], &matlab_node_B.x1[0], 16);
    if (matlab_node_B.ret == 0) {
      matlab_node_B.ret = 0;
    } else {
      matlab_node_B.ret = std::memcmp(&b_a_0[0], &matlab_node_B.x1[0], 16);
      if (matlab_node_B.ret == 0) {
        matlab_node_B.ret = 1;
      } else {
        matlab_node_B.ret = std::memcmp(&c_a_1[0], &matlab_node_B.x1[0], 16);
        if (matlab_node_B.ret == 0) {
          matlab_node_B.ret = 2;
        } else {
          matlab_node_B.ret = std::memcmp(&d_a_0[0], &matlab_node_B.x1[0], 16);
          if (matlab_node_B.ret == 0) {
            matlab_node_B.ret = 3;
          } else {
            matlab_node_B.ret = std::memcmp(&e_a_0[0], &matlab_node_B.x1[0], 16);
            if (matlab_node_B.ret == 0) {
              matlab_node_B.ret = 4;
            } else {
              matlab_node_B.ret = std::memcmp(&f_a[0], &matlab_node_B.x1[0], 16);
              if (matlab_node_B.ret == 0) {
                matlab_node_B.ret = 5;
              } else {
                matlab_node_B.ret = std::memcmp(&g_a[0], &matlab_node_B.x1[0],
                  16);
                if (matlab_node_B.ret == 0) {
                  matlab_node_B.ret = 6;
                } else {
                  matlab_node_B.ret = std::memcmp(&h_a[0], &matlab_node_B.x1[0],
                    16);
                  if (matlab_node_B.ret == 0) {
                    matlab_node_B.ret = 7;
                  } else {
                    matlab_node_B.ret = std::memcmp(&i_a[0], &matlab_node_B.x1[0],
                      16);
                    if (matlab_node_B.ret == 0) {
                      matlab_node_B.ret = 8;
                    } else {
                      matlab_node_B.ret = std::memcmp(&j_a[0],
                        &matlab_node_B.x1[0], 16);
                      if (matlab_node_B.ret == 0) {
                        matlab_node_B.ret = 9;
                      } else if (matlab_node_strcmp(matlab_node_B.x1)) {
                        matlab_node_B.ret = 10;
                      } else if (matlab_node_strcmp_n(matlab_node_B.x1)) {
                        matlab_node_B.ret = 11;
                      } else if (matlab_node_strcmp_nj(matlab_node_B.x1)) {
                        matlab_node_B.ret = 12;
                      } else {
                        matlab_node_B.ret = -1;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    switch (matlab_node_B.ret) {
     case 0:
      matlab_node_B.dRb_e[0] = 0.5 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 1:
      matlab_node_B.dRb_e[0] = -0.5 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 2:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = -1.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 3:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 1.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 4:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 1.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 5:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = -1.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 6:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 1.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 7:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = -1.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 8:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 1.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 9:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = -1.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 10:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 1.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 11:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = -1.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;

     case 12:
      matlab_node_B.dRb_e[0] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[0];
      matlab_node_B.eps_g[0] = 0.0 - matlab_node_B.rotm_tmp;
      matlab_node_B.dRb_e[1] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[1];
      matlab_node_B.eps_g[1] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_1;
      matlab_node_B.dRb_e[2] = 0.0 - matlab_node_DW.VelocityIntegrator_DSTATE[2];
      matlab_node_B.eps_g[2] = 0.0 - matlab_node_B.rtb_Integrator_p_idx_2;
      break;
    }
  }

  // DiscreteIntegrator: '<S72>/Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read7'

  if ((integrator_reset > 0) && (matlab_node_DW.Integrator_PrevResetState_l <= 0))
  {
    matlab_node_DW.Integrator_DSTATE_l[0] = 0.0;
    matlab_node_DW.Integrator_DSTATE_l[1] = 0.0;
    matlab_node_DW.Integrator_DSTATE_l[2] = 0.0;
  }

  // DiscreteIntegrator: '<S67>/Filter' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read7'

  if ((integrator_reset > 0) && (matlab_node_DW.Filter_PrevResetState_b <= 0)) {
    matlab_node_DW.Filter_DSTATE_e[0] = 0.0;
    matlab_node_DW.Filter_DSTATE_e[1] = 0.0;
    matlab_node_DW.Filter_DSTATE_e[2] = 0.0;
  }

  // Gain: '<S75>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S67>/Filter'
  //   Gain: '<S65>/Derivative Gain'
  //   Sum: '<S67>/SumD'

  matlab_node_B.rotm_tmp = (0.0 * matlab_node_B.eps_g[0] -
    matlab_node_DW.Filter_DSTATE_e[0]) * 100.0;
  matlab_node_B.dRb_u[0] = matlab_node_B.rotm_tmp;

  // Sum: '<S81>/Sum' incorporates:
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S65>/Derivative Gain'

  matlab_node_B.b_absxk = (matlab_node_B.eps_g[0] +
    matlab_node_DW.Integrator_DSTATE_l[0]) + matlab_node_B.rotm_tmp;
  matlab_node_B.rtb_Filter_h_idx_0 = matlab_node_B.b_absxk;

  // DeadZone: '<S64>/DeadZone'
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_B.rtb_Integrator_p_idx_0 = matlab_node_B.b_absxk - 10.0;
  } else if (matlab_node_B.b_absxk >= -10.0) {
    matlab_node_B.rtb_Integrator_p_idx_0 = 0.0;
  } else {
    matlab_node_B.rtb_Integrator_p_idx_0 = matlab_node_B.b_absxk - -10.0;
  }

  // Gain: '<S75>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S67>/Filter'
  //   Gain: '<S65>/Derivative Gain'
  //   Sum: '<S67>/SumD'

  matlab_node_B.rotm_tmp = (0.0 * matlab_node_B.eps_g[1] -
    matlab_node_DW.Filter_DSTATE_e[1]) * 100.0;
  matlab_node_B.dRb_u[1] = matlab_node_B.rotm_tmp;

  // Gain: '<S77>/Proportional Gain' incorporates:
  //   Gain: '<S65>/Derivative Gain'
  //   Gain: '<S69>/Integral Gain'

  matlab_node_B.eps_n = 5.0 * matlab_node_B.eps_g[1];
  matlab_node_B.eps_g[1] = matlab_node_B.eps_n;

  // Sum: '<S81>/Sum' incorporates:
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S77>/Proportional Gain'

  matlab_node_B.b_absxk = (matlab_node_B.eps_n +
    matlab_node_DW.Integrator_DSTATE_l[1]) + matlab_node_B.rotm_tmp;
  matlab_node_B.rtb_Filter_h_idx_1 = matlab_node_B.b_absxk;

  // DeadZone: '<S64>/DeadZone'
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_B.rtb_Integrator_p_idx_1 = matlab_node_B.b_absxk - 10.0;
  } else if (matlab_node_B.b_absxk >= -10.0) {
    matlab_node_B.rtb_Integrator_p_idx_1 = 0.0;
  } else {
    matlab_node_B.rtb_Integrator_p_idx_1 = matlab_node_B.b_absxk - -10.0;
  }

  // Gain: '<S75>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S67>/Filter'
  //   Gain: '<S65>/Derivative Gain'
  //   Sum: '<S67>/SumD'

  matlab_node_B.rotm_tmp = (0.0 * matlab_node_B.eps_g[2] -
    matlab_node_DW.Filter_DSTATE_e[2]) * 100.0;

  // Gain: '<S77>/Proportional Gain' incorporates:
  //   Gain: '<S65>/Derivative Gain'
  //   Gain: '<S69>/Integral Gain'

  matlab_node_B.eps_n = 5.0 * matlab_node_B.eps_g[2];

  // Sum: '<S81>/Sum' incorporates:
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S77>/Proportional Gain'

  matlab_node_B.b_absxk = (matlab_node_B.eps_n +
    matlab_node_DW.Integrator_DSTATE_l[2]) + matlab_node_B.rotm_tmp;

  // DeadZone: '<S64>/DeadZone'
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_B.rtb_Integrator_p_idx_2 = matlab_node_B.b_absxk - 10.0;
  } else if (matlab_node_B.b_absxk >= -10.0) {
    matlab_node_B.rtb_Integrator_p_idx_2 = 0.0;
  } else {
    matlab_node_B.rtb_Integrator_p_idx_2 = matlab_node_B.b_absxk - -10.0;
  }

  // DiscreteIntegrator: '<S182>/Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read9'

  if ((integrator_reset > 0) && (matlab_node_DW.Integrator_PrevResetState_i <= 0))
  {
    matlab_node_DW.Integrator_DSTATE_f[0] = 0.0;
    matlab_node_DW.Integrator_DSTATE_f[1] = 0.0;
    matlab_node_DW.Integrator_DSTATE_f[2] = 0.0;
  }

  // DiscreteIntegrator: '<S177>/Filter' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read9'

  if ((integrator_reset > 0) && (matlab_node_DW.Filter_PrevResetState_n <= 0)) {
    matlab_node_DW.Filter_DSTATE_k[0] = 0.0;
    matlab_node_DW.Filter_DSTATE_k[1] = 0.0;
    matlab_node_DW.Filter_DSTATE_k[2] = 0.0;
  }

  // Gain: '<S185>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S177>/Filter'
  //   Gain: '<S175>/Derivative Gain'
  //   Sum: '<S177>/SumD'

  matlab_node_B.rtb_Cbi_tmp_tmp_d = (0.0 * matlab_node_B.dRb_e[0] -
    matlab_node_DW.Filter_DSTATE_k[0]) * 100.0;
  matlab_node_B.rtb_FilterCoefficient_h_idx_0 = matlab_node_B.rtb_Cbi_tmp_tmp_d;

  // Sum: '<S191>/Sum' incorporates:
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Gain: '<S175>/Derivative Gain'
  //   Gain: '<S187>/Proportional Gain'

  matlab_node_B.phi = (60.0 * matlab_node_B.dRb_e[0] +
                       matlab_node_DW.Integrator_DSTATE_f[0]) +
    matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.IntegralGain_a[0] = matlab_node_B.phi;

  // Saturate: '<S79>/Saturation'
  if (matlab_node_B.rtb_Filter_h_idx_0 > 10.0) {
    matlab_node_B.dv3[0] = 10.0;
  } else if (matlab_node_B.rtb_Filter_h_idx_0 < -10.0) {
    matlab_node_B.dv3[0] = -10.0;
  } else {
    matlab_node_B.dv3[0] = matlab_node_B.rtb_Filter_h_idx_0;
  }

  // Saturate: '<S189>/Saturation'
  if (matlab_node_B.phi > 100.0) {
    matlab_node_B.dv4[0] = 100.0;
  } else if (matlab_node_B.phi < -100.0) {
    matlab_node_B.dv4[0] = -100.0;
  } else {
    matlab_node_B.dv4[0] = matlab_node_B.phi;
  }

  // Gain: '<S185>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S177>/Filter'
  //   Gain: '<S175>/Derivative Gain'
  //   Sum: '<S177>/SumD'

  matlab_node_B.rtb_Cbi_tmp_tmp_d = (0.0 * matlab_node_B.dRb_e[1] -
    matlab_node_DW.Filter_DSTATE_k[1]) * 100.0;
  matlab_node_B.rtb_Filter_h_idx_0 = matlab_node_B.rtb_Cbi_tmp_tmp_d;

  // Sum: '<S191>/Sum' incorporates:
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Gain: '<S175>/Derivative Gain'
  //   Gain: '<S187>/Proportional Gain'

  matlab_node_B.phi = (60.0 * matlab_node_B.dRb_e[1] +
                       matlab_node_DW.Integrator_DSTATE_f[1]) +
    matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.IntegralGain_a[1] = matlab_node_B.phi;

  // Saturate: '<S79>/Saturation'
  if (matlab_node_B.rtb_Filter_h_idx_1 > 10.0) {
    matlab_node_B.dv3[1] = 10.0;
  } else if (matlab_node_B.rtb_Filter_h_idx_1 < -10.0) {
    matlab_node_B.dv3[1] = -10.0;
  } else {
    matlab_node_B.dv3[1] = matlab_node_B.rtb_Filter_h_idx_1;
  }

  // Saturate: '<S189>/Saturation'
  if (matlab_node_B.phi > 100.0) {
    matlab_node_B.dv4[1] = 100.0;
  } else if (matlab_node_B.phi < -100.0) {
    matlab_node_B.dv4[1] = -100.0;
  } else {
    matlab_node_B.dv4[1] = matlab_node_B.phi;
  }

  // Gain: '<S185>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S177>/Filter'
  //   Gain: '<S175>/Derivative Gain'
  //   Sum: '<S177>/SumD'

  matlab_node_B.rtb_Cbi_tmp_tmp_d = (0.0 * matlab_node_B.dRb_e[2] -
    matlab_node_DW.Filter_DSTATE_k[2]) * 100.0;

  // Sum: '<S191>/Sum' incorporates:
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Gain: '<S175>/Derivative Gain'
  //   Gain: '<S187>/Proportional Gain'

  matlab_node_B.phi = (100.0 * matlab_node_B.dRb_e[2] +
                       matlab_node_DW.Integrator_DSTATE_f[2]) +
    matlab_node_B.rtb_Cbi_tmp_tmp_d;
  matlab_node_B.IntegralGain_a[2] = matlab_node_B.phi;

  // Saturate: '<S79>/Saturation' incorporates:
  //   Sum: '<S81>/Sum'

  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_B.dv3[2] = 10.0;
  } else if (matlab_node_B.b_absxk < -10.0) {
    matlab_node_B.dv3[2] = -10.0;
  } else {
    matlab_node_B.dv3[2] = matlab_node_B.b_absxk;
  }

  // Saturate: '<S189>/Saturation'
  if (matlab_node_B.phi > 100.0) {
    matlab_node_B.dv4[2] = 100.0;
  } else if (matlab_node_B.phi < -100.0) {
    matlab_node_B.dv4[2] = -100.0;
  } else {
    matlab_node_B.dv4[2] = matlab_node_B.phi;
  }

  // Product: '<S17>/Matrix Multiply' incorporates:
  //   Constant: '<S17>/Constant'

  std::memset(&matlab_node_B.pwms[0], 0, sizeof(real_T) << 3U);
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_B.dv3[i];
    for (matlab_node_B.ret = 0; matlab_node_B.ret < 8; matlab_node_B.ret++) {
      matlab_node_B.pwms[matlab_node_B.ret] +=
        matlab_node_ConstP.Constant_Value_i[(i << 3) + matlab_node_B.ret] *
        matlab_node_B.phi;
    }
  }

  // End of Product: '<S17>/Matrix Multiply'

  // Product: '<S17>/Matrix Multiply1' incorporates:
  //   Constant: '<S17>/Constant1'

  std::memset(&matlab_node_B.dv[0], 0, sizeof(real_T) << 3U);
  for (i = 0; i < 3; i++) {
    matlab_node_B.phi = matlab_node_B.dv4[i];
    for (matlab_node_B.ret = 0; matlab_node_B.ret < 8; matlab_node_B.ret++) {
      matlab_node_B.dv[matlab_node_B.ret] += matlab_node_ConstP.Constant1_Value
        [(i << 3) + matlab_node_B.ret] * matlab_node_B.phi;
    }
  }

  // End of Product: '<S17>/Matrix Multiply1'

  // MATLAB Function: '<S17>/thrusterAllocator'
  for (i = 0; i < 8; i++) {
    matlab_node_B.FT_cmd_list[i] = matlab_node_B.pwms[i] + matlab_node_B.dv[i];
  }

  // End of MATLAB Function: '<S17>/thrusterAllocator'

  // MATLAB Function: '<S17>/trickFTListInjector'
  if (rtb_OR1) {
    for (i = 0; i < 16; i++) {
      matlab_node_B.s[i] = matlab_node_B.cmd.trick_id[i];
    }

    matlab_node_B.ret = std::memcmp(&a_2[0], &matlab_node_B.s[0], 16);
    if (matlab_node_B.ret == 0) {
      matlab_node_B.ret = 0;
    } else {
      matlab_node_B.ret = std::memcmp(&b_a_1[0], &matlab_node_B.s[0], 16);
      if (matlab_node_B.ret == 0) {
        matlab_node_B.ret = 1;
      } else {
        matlab_node_B.ret = std::memcmp(&c_a_2[0], &matlab_node_B.s[0], 16);
        if (matlab_node_B.ret == 0) {
          matlab_node_B.ret = 2;
        } else {
          matlab_node_B.ret = std::memcmp(&d_a_1[0], &matlab_node_B.s[0], 16);
          if (matlab_node_B.ret == 0) {
            matlab_node_B.ret = 3;
          } else {
            matlab_node_B.ret = std::memcmp(&e_a_1[0], &matlab_node_B.s[0], 16);
            if (matlab_node_B.ret == 0) {
              matlab_node_B.ret = 4;
            } else {
              matlab_node_B.ret = std::memcmp(&f_a_0[0], &matlab_node_B.s[0], 16);
              if (matlab_node_B.ret == 0) {
                matlab_node_B.ret = 5;
              } else {
                matlab_node_B.ret = std::memcmp(&g_a_0[0], &matlab_node_B.s[0],
                  16);
                if (matlab_node_B.ret == 0) {
                  matlab_node_B.ret = 6;
                } else {
                  matlab_node_B.ret = std::memcmp(&h_a_0[0], &matlab_node_B.s[0],
                    16);
                  if (matlab_node_B.ret == 0) {
                    matlab_node_B.ret = 7;
                  } else {
                    matlab_node_B.ret = std::memcmp(&i_a_0[0], &matlab_node_B.s
                      [0], 16);
                    if (matlab_node_B.ret == 0) {
                      matlab_node_B.ret = 8;
                    } else {
                      matlab_node_B.ret = std::memcmp(&j_a_0[0],
                        &matlab_node_B.s[0], 16);
                      if (matlab_node_B.ret == 0) {
                        matlab_node_B.ret = 9;
                      } else {
                        matlab_node_B.ret = std::memcmp(&k_a[0],
                          &matlab_node_B.s[0], 16);
                        if (matlab_node_B.ret == 0) {
                          matlab_node_B.ret = 10;
                        } else {
                          matlab_node_B.ret = std::memcmp(&l_a[0],
                            &matlab_node_B.s[0], 16);
                          if (matlab_node_B.ret == 0) {
                            matlab_node_B.ret = 11;
                          } else {
                            matlab_node_B.ret = std::memcmp(&m_a[0],
                              &matlab_node_B.s[0], 16);
                            if (matlab_node_B.ret == 0) {
                              matlab_node_B.ret = 12;
                            } else {
                              matlab_node_B.ret = -1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    for (i = 0; i < 8; i++) {
      switch (matlab_node_B.ret) {
       case 0:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.forward[i];
        break;

       case 1:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.backward[i];
        break;

       case 2:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.up[i];
        break;

       case 3:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.down[i];
        break;

       case 4:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.left[i];
        break;

       case 5:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.right[i];
        break;

       case 6:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.pitchUp[i];
        break;

       case 7:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.pitchDown[i];
        break;

       case 8:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.yawRight[i];
        break;

       case 9:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.yawLeft[i];
        break;

       case 10:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.rollRight[i];
        break;

       case 11:
        matlab_node_B.FT_cmd_list[i] =
          matlab_node_ConstP.trickFTListInjector_FF_maneuver.rollLeft[i];
        break;

       case 12:
        matlab_node_B.FT_cmd_list[i] = 0.0;
        break;
      }
    }
  }

  // MATLAB Function: '<S24>/forceToPWMCalculator' incorporates:
  //   Constant: '<S17>/Constant3'

  for (i = 0; i < 8; i++) {
    matlab_node_B.pwms[i] = 1500.0;
  }

  for (matlab_node_B.pos = 0; matlab_node_B.pos < 4; matlab_node_B.pos++) {
    matlab_node_B.ret = matlab_node_B.pos << 1;
    matlab_node_B.b_absxk = matlab_node_B.FT_cmd_list[matlab_node_B.ret];
    if (std::abs(matlab_node_B.b_absxk) < 0.001) {
      matlab_node_B.pwms[matlab_node_B.ret] = 1500.0;
    } else {
      for (i = 0; i < 6; i++) {
        matlab_node_B.varargin_1_f[i] = std::abs
          (matlab_node_ConstP.forceToPWMCalculator_voltage[i] - 15.0);
      }

      matlab_node_minimum(matlab_node_B.varargin_1_f, &matlab_node_B.phi, &i);
      switch (i) {
       case 1:
        matlab_node_B.lower_voltage_index = 1.0;
        matlab_node_B.rtb_Filter_h_idx_1 = 1.0;
        break;

       case 6:
        matlab_node_B.lower_voltage_index = 6.0;
        matlab_node_B.rtb_Filter_h_idx_1 = 6.0;
        break;

       default:
        if (matlab_node_ConstP.forceToPWMCalculator_voltage[i - 1] < 15.0) {
          matlab_node_B.lower_voltage_index = i;
          matlab_node_B.rtb_Filter_h_idx_1 = static_cast<real_T>(i) + 1.0;
        } else {
          matlab_node_B.rtb_Filter_h_idx_1 = i;
          matlab_node_B.lower_voltage_index = static_cast<real_T>(i) - 1.0;
        }
        break;
      }

      if (matlab_node_B.rtb_Filter_h_idx_1 == matlab_node_B.lower_voltage_index)
      {
        force_column_size_idx_0 = 1;
        matlab_node_B.force_column_data[0] =
          matlab_node_ConstP.forceToPWMCalculator_cw_force[static_cast<int32_T>
          (matlab_node_B.lower_voltage_index) - 1];
      } else if (std::abs(matlab_node_ConstP.forceToPWMCalculator_cw_force[
                          static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1)
                          - 1] -
                          matlab_node_ConstP.forceToPWMCalculator_cw_force[
                          static_cast<int32_T>(matlab_node_B.lower_voltage_index)
                          - 1]) < 0.001) {
        force_column_size_idx_0 = 1;
        matlab_node_B.force_column_data[0] =
          matlab_node_ConstP.forceToPWMCalculator_cw_force[static_cast<int32_T>
          (matlab_node_B.lower_voltage_index) - 1];
      } else {
        matlab_node_B.theta = matlab_node_ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>(matlab_node_B.lower_voltage_index) - 1];
        matlab_node_B.phi = matlab_node_ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1] -
          matlab_node_B.theta;
        force_column_size_idx_0 = 201;
        for (i = 0; i < 201; i++) {
          matlab_node_B.rtb_Cbi_tmp_tmp_e =
            matlab_node_ConstP.forceToPWMCalculator_cw_force
            [(static_cast<int32_T>(matlab_node_B.lower_voltage_index) - 1) * 201
            + i];
          matlab_node_B.force_column_data[i] =
            (matlab_node_ConstP.forceToPWMCalculator_cw_force
             [(static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1) * 201
             + i] - matlab_node_B.rtb_Cbi_tmp_tmp_e) * (15.0 -
            matlab_node_B.theta) / matlab_node_B.phi +
            matlab_node_B.rtb_Cbi_tmp_tmp_e;
        }
      }

      for (i = 0; i < force_column_size_idx_0; i++) {
        matlab_node_B.b_x_data[i] = matlab_node_B.force_column_data[i] -
          matlab_node_B.b_absxk;
        matlab_node_B.b_varargin_1_data[i] = std::abs(matlab_node_B.b_x_data[i]);
      }

      matlab_node_minimum_d(matlab_node_B.b_varargin_1_data,
                            &force_column_size_idx_0, &matlab_node_B.b_absxk, &i);
      if ((i == 1) || (i == 2)) {
        matlab_node_B.rtb_Filter_h_idx_1 = 1.0;
        matlab_node_B.b_absxk = 1.0;
      } else if ((i == 8) || (i == 7)) {
        matlab_node_B.rtb_Filter_h_idx_1 = 8.0;
        matlab_node_B.b_absxk = 8.0;
      } else if (matlab_node_B.force_column_data[i - 1] <
                 matlab_node_B.FT_cmd_list[matlab_node_B.ret]) {
        matlab_node_B.rtb_Filter_h_idx_1 = i;
        matlab_node_B.b_absxk = static_cast<real_T>(i) + 1.0;
      } else {
        matlab_node_B.b_absxk = i;
        matlab_node_B.rtb_Filter_h_idx_1 = static_cast<real_T>(i) - 1.0;
      }

      if (matlab_node_B.b_absxk > force_column_size_idx_0) {
        matlab_node_B.b_absxk = force_column_size_idx_0;
      }

      if ((static_cast<int32_T>(matlab_node_B.b_absxk) ==
           force_column_size_idx_0) && (static_cast<real_T>
           (force_column_size_idx_0) - 1.0 == matlab_node_B.rtb_Filter_h_idx_1))
      {
        matlab_node_B.rtb_Filter_h_idx_1 = matlab_node_B.b_absxk;
      } else if ((matlab_node_B.b_absxk == 2.0) &&
                 (matlab_node_B.rtb_Filter_h_idx_1 == 1.0)) {
        matlab_node_B.b_absxk = 1.0;
      }

      if (matlab_node_B.rtb_Filter_h_idx_1 == matlab_node_B.b_absxk) {
        matlab_node_B.phi = 0.0;
      } else if (std::abs(matlab_node_B.force_column_data[static_cast<int32_T>
                          (matlab_node_B.b_absxk) - 1] -
                          matlab_node_B.force_column_data[static_cast<int32_T>
                          (matlab_node_B.rtb_Filter_h_idx_1) - 1]) < 0.001) {
        matlab_node_B.phi = 0.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.FT_cmd_list[matlab_node_B.ret] -
                             matlab_node_B.force_column_data[static_cast<int32_T>
                             (matlab_node_B.b_absxk) - 1]) /
          (matlab_node_B.force_column_data[static_cast<int32_T>
           (matlab_node_B.b_absxk) - 1] - matlab_node_B.force_column_data[
           static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1]);
      }

      matlab_node_B.rtb_Filter_h_idx_1 =
        matlab_node_ConstP.forceToPWMCalculator_cw_pwm[static_cast<int32_T>
        (matlab_node_B.rtb_Filter_h_idx_1) - 1];
      matlab_node_B.pwms[matlab_node_B.ret] = std::round
        ((matlab_node_ConstP.forceToPWMCalculator_cw_pwm[static_cast<int32_T>
          (matlab_node_B.b_absxk) - 1] - matlab_node_B.rtb_Filter_h_idx_1) *
         matlab_node_B.phi + matlab_node_B.rtb_Filter_h_idx_1);
    }
  }

  for (matlab_node_B.pos = 0; matlab_node_B.pos < 4; matlab_node_B.pos++) {
    matlab_node_B.ret = (matlab_node_B.pos << 1) + 1;
    matlab_node_B.b_absxk = matlab_node_B.FT_cmd_list[matlab_node_B.ret];
    if (std::abs(matlab_node_B.b_absxk) < 0.001) {
      matlab_node_B.pwms[matlab_node_B.ret] = 1500.0;
    } else {
      for (i = 0; i < 6; i++) {
        matlab_node_B.varargin_1_f[i] = std::abs
          (matlab_node_ConstP.forceToPWMCalculator_voltage[i] - 15.0);
      }

      matlab_node_minimum(matlab_node_B.varargin_1_f, &matlab_node_B.phi, &i);
      switch (i) {
       case 1:
        matlab_node_B.lower_voltage_index = 1.0;
        matlab_node_B.rtb_Filter_h_idx_1 = 1.0;
        break;

       case 6:
        matlab_node_B.lower_voltage_index = 6.0;
        matlab_node_B.rtb_Filter_h_idx_1 = 6.0;
        break;

       default:
        if (matlab_node_ConstP.forceToPWMCalculator_voltage[i - 1] < 15.0) {
          matlab_node_B.lower_voltage_index = i;
          matlab_node_B.rtb_Filter_h_idx_1 = static_cast<real_T>(i) + 1.0;
        } else {
          matlab_node_B.rtb_Filter_h_idx_1 = i;
          matlab_node_B.lower_voltage_index = static_cast<real_T>(i) - 1.0;
        }
        break;
      }

      if (matlab_node_B.rtb_Filter_h_idx_1 == matlab_node_B.lower_voltage_index)
      {
        force_column_size_idx_0 = 1;
        matlab_node_B.force_column_data[0] =
          matlab_node_ConstP.forceToPWMCalculator_ccw_force[static_cast<int32_T>
          (matlab_node_B.lower_voltage_index) - 1];
      } else if (std::abs(matlab_node_ConstP.forceToPWMCalculator_ccw_force[
                          static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1)
                          - 1] -
                          matlab_node_ConstP.forceToPWMCalculator_ccw_force[
                          static_cast<int32_T>(matlab_node_B.lower_voltage_index)
                          - 1]) < 0.001) {
        force_column_size_idx_0 = 1;
        matlab_node_B.force_column_data[0] =
          matlab_node_ConstP.forceToPWMCalculator_ccw_force[static_cast<int32_T>
          (matlab_node_B.lower_voltage_index) - 1];
      } else {
        matlab_node_B.theta = matlab_node_ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>(matlab_node_B.lower_voltage_index) - 1];
        matlab_node_B.phi = matlab_node_ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1] -
          matlab_node_B.theta;
        force_column_size_idx_0 = 201;
        for (i = 0; i < 201; i++) {
          matlab_node_B.rtb_Cbi_tmp_tmp_e =
            matlab_node_ConstP.forceToPWMCalculator_ccw_force
            [(static_cast<int32_T>(matlab_node_B.lower_voltage_index) - 1) * 201
            + i];
          matlab_node_B.force_column_data[i] =
            (matlab_node_ConstP.forceToPWMCalculator_ccw_force
             [(static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1) * 201
             + i] - matlab_node_B.rtb_Cbi_tmp_tmp_e) * (15.0 -
            matlab_node_B.theta) / matlab_node_B.phi +
            matlab_node_B.rtb_Cbi_tmp_tmp_e;
        }
      }

      for (i = 0; i < force_column_size_idx_0; i++) {
        matlab_node_B.b_x_data[i] = matlab_node_B.force_column_data[i] -
          matlab_node_B.b_absxk;
        matlab_node_B.b_varargin_1_data[i] = std::abs(matlab_node_B.b_x_data[i]);
      }

      matlab_node_minimum_d(matlab_node_B.b_varargin_1_data,
                            &force_column_size_idx_0, &matlab_node_B.b_absxk, &i);
      if ((i == 1) || (i == 2)) {
        matlab_node_B.rtb_Filter_h_idx_1 = 1.0;
        matlab_node_B.b_absxk = 1.0;
      } else if ((i == 8) || (i == 7)) {
        matlab_node_B.rtb_Filter_h_idx_1 = 8.0;
        matlab_node_B.b_absxk = 8.0;
      } else if (matlab_node_B.force_column_data[i - 1] <
                 matlab_node_B.FT_cmd_list[matlab_node_B.ret]) {
        matlab_node_B.rtb_Filter_h_idx_1 = i;
        matlab_node_B.b_absxk = static_cast<real_T>(i) + 1.0;
      } else {
        matlab_node_B.b_absxk = i;
        matlab_node_B.rtb_Filter_h_idx_1 = static_cast<real_T>(i) - 1.0;
      }

      if (matlab_node_B.b_absxk > force_column_size_idx_0) {
        matlab_node_B.b_absxk = force_column_size_idx_0;
      }

      if (matlab_node_B.rtb_Filter_h_idx_1 == matlab_node_B.b_absxk) {
        matlab_node_B.phi = 0.0;
      } else if (std::abs(matlab_node_B.force_column_data[static_cast<int32_T>
                          (matlab_node_B.b_absxk) - 1] -
                          matlab_node_B.force_column_data[static_cast<int32_T>
                          (matlab_node_B.rtb_Filter_h_idx_1) - 1]) < 0.001) {
        matlab_node_B.phi = 0.0;
      } else {
        matlab_node_B.phi = (matlab_node_B.FT_cmd_list[matlab_node_B.ret] -
                             matlab_node_B.force_column_data[static_cast<int32_T>
                             (matlab_node_B.b_absxk) - 1]) /
          (matlab_node_B.force_column_data[static_cast<int32_T>
           (matlab_node_B.b_absxk) - 1] - matlab_node_B.force_column_data[
           static_cast<int32_T>(matlab_node_B.rtb_Filter_h_idx_1) - 1]);
      }

      matlab_node_B.rtb_Filter_h_idx_1 =
        matlab_node_ConstP.forceToPWMCalculator_ccw_pwm[static_cast<int32_T>
        (matlab_node_B.rtb_Filter_h_idx_1) - 1];
      matlab_node_B.pwms[matlab_node_B.ret] = std::round
        ((matlab_node_ConstP.forceToPWMCalculator_ccw_pwm[static_cast<int32_T>
          (matlab_node_B.b_absxk) - 1] - matlab_node_B.rtb_Filter_h_idx_1) *
         matlab_node_B.phi + matlab_node_B.rtb_Filter_h_idx_1);
    }
  }

  for (matlab_node_B.ret = 0; matlab_node_B.ret < 8; matlab_node_B.ret++) {
    i = static_cast<int32_T>(std::fmax(1100.0, std::fmin(1900.0,
      matlab_node_B.pwms[matlab_node_B.ret])));
    matlab_node_B.pwms[matlab_node_B.ret] = i;

    // DataTypeConversion: '<S17>/Cast'
    matlab_node_B.Cast[matlab_node_B.ret] = i;
  }

  // End of MATLAB Function: '<S24>/forceToPWMCalculator'

  // MATLAB Function: '<S17>/quatToEul1'
  matlab_node_B.b_absxk = matlab_node_B.qe_matlab[3] * matlab_node_B.qe_matlab[3]
    * 2.0 - 1.0;
  matlab_node_B.psi = 2.0 * matlab_node_B.qe_matlab[3];
  for (i = 0; i < 3; i++) {
    // DeadZone: '<S119>/DeadZone' incorporates:
    //   Gain: '<S124>/Integral Gain'

    matlab_node_B.phi = matlab_node_B.eul_error[i];
    if (matlab_node_B.phi > 1.0) {
      matlab_node_B.phi--;
    } else if (matlab_node_B.phi >= -1.0) {
      matlab_node_B.phi = 0.0;
    } else {
      matlab_node_B.phi++;
    }

    // End of DeadZone: '<S119>/DeadZone'

    // Gain: '<S124>/Integral Gain'
    matlab_node_B.eul_error[i] = 0.0 * matlab_node_B.eps[i];

    // Switch: '<S117>/Switch1' incorporates:
    //   Constant: '<S117>/Clamping_zero'
    //   Constant: '<S117>/Constant'
    //   Constant: '<S117>/Constant2'
    //   Gain: '<S124>/Integral Gain'
    //   RelationalOperator: '<S117>/fix for DT propagation issue'

    if (matlab_node_B.phi > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    // Logic: '<S117>/AND3' incorporates:
    //   Constant: '<S117>/Clamping_zero'
    //   Gain: '<S124>/Integral Gain'
    //   RelationalOperator: '<S117>/Equal1'
    //   RelationalOperator: '<S117>/Relational Operator'
    //   Switch: '<S117>/Switch1'
    //   Switch: '<S117>/Switch2'

    rtb_RelationalOperator_c[i] = ((matlab_node_B.phi != 0.0) && (tmp == -1));

    // DeadZone: '<S174>/DeadZone'
    matlab_node_B.phi = matlab_node_B.IntegralGain_a[i];
    if (matlab_node_B.phi > 100.0) {
      matlab_node_B.phi -= 100.0;
    } else if (matlab_node_B.phi >= -100.0) {
      matlab_node_B.phi = 0.0;
    } else {
      matlab_node_B.phi -= -100.0;
    }

    // End of DeadZone: '<S174>/DeadZone'

    // RelationalOperator: '<S172>/Relational Operator' incorporates:
    //   Constant: '<S172>/Clamping_zero'

    rtb_RelationalOperator_b[i] = (matlab_node_B.phi != 0.0);

    // Switch: '<S172>/Switch1' incorporates:
    //   Constant: '<S172>/Clamping_zero'
    //   Constant: '<S172>/Constant'
    //   Constant: '<S172>/Constant2'
    //   RelationalOperator: '<S172>/fix for DT propagation issue'

    if (matlab_node_B.phi > 0.0) {
      rtb_Switch1[i] = 1;
    } else {
      rtb_Switch1[i] = -1;
    }

    // End of Switch: '<S172>/Switch1'

    // Gain: '<S179>/Integral Gain'
    matlab_node_B.IntegralGain_a[i] = 20.0 * matlab_node_B.dRb_e[i];

    // MATLAB Function: '<S17>/quatToEul1'
    matlab_node_B.theta = 2.0 * matlab_node_B.qe_matlab[i];
    matlab_node_B.rotm[3 * i] = matlab_node_B.rtb_Cbi_tmp_tmp[3 * i] *
      matlab_node_B.b_absxk + matlab_node_B.theta * matlab_node_B.qe_matlab[0];
    matlab_node_B.ret = 3 * i + 1;
    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk +
      matlab_node_B.theta * matlab_node_B.qe_matlab[1];
    matlab_node_B.ret = 3 * i + 2;
    matlab_node_B.rotm[matlab_node_B.ret] =
      matlab_node_B.rtb_Cbi_tmp_tmp[matlab_node_B.ret] * matlab_node_B.b_absxk +
      matlab_node_B.theta * matlab_node_B.qe_matlab[2];
  }

  // MATLAB Function: '<S17>/quatToEul1'
  matlab_node_B.theta = matlab_node_B.psi * 0.0;
  matlab_node_B.Cbi_c[0] = matlab_node_B.theta;
  matlab_node_B.Cbi_c[1] = matlab_node_B.psi * -matlab_node_B.qe_matlab[2];
  matlab_node_B.Cbi_c[2] = matlab_node_B.psi * matlab_node_B.qe_matlab[1];
  matlab_node_B.Cbi_c[3] = matlab_node_B.psi * matlab_node_B.qe_matlab[2];
  matlab_node_B.Cbi_c[4] = matlab_node_B.theta;
  matlab_node_B.Cbi_c[5] = matlab_node_B.psi * -matlab_node_B.qe_matlab[0];
  matlab_node_B.Cbi_c[6] = matlab_node_B.psi * -matlab_node_B.qe_matlab[1];
  matlab_node_B.Cbi_c[7] = matlab_node_B.psi * matlab_node_B.qe_matlab[0];
  matlab_node_B.Cbi_c[8] = matlab_node_B.theta;
  for (i = 0; i < 9; i++) {
    matlab_node_B.Cbi[i] = matlab_node_B.rotm[i] + matlab_node_B.Cbi_c[i];
  }

  matlab_node_B.theta = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_node_B.theta)) < 1.0E-6) {
    matlab_node_B.phi = 0.0;
    matlab_node_B.psi = rt_atan2d_snf(-matlab_node_B.Cbi[1], matlab_node_B.Cbi[4]);
  } else {
    matlab_node_B.phi = rt_atan2d_snf(matlab_node_B.Cbi[7], matlab_node_B.Cbi[8]);
    matlab_node_B.psi = rt_atan2d_snf(matlab_node_B.Cbi[3], matlab_node_B.Cbi[0]);
  }

  matlab_node_wrapToPi(&matlab_node_B.phi);
  matlab_node_B.theta = -matlab_node_B.theta;
  matlab_node_wrapToPi(&matlab_node_B.theta);
  matlab_node_wrapToPi(&matlab_node_B.psi);

  // Update for UnitDelay: '<S21>/Delay Input1' incorporates:
  //   UnitDelay: '<S5>/Unit Delay2'
  //
  //  Block description for '<S21>/Delay Input1':
  //
  //   Store in Global RAM

  matlab_node_DW.DelayInput1_DSTATE = matlab_node_DW.UnitDelay2_DSTATE;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read6'
  //   MATLAB Function: '<S17>/deltaQuatError'
  //
  if (integrator_reset > 0) {
    matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else {
    matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 0;
  }

  matlab_node_B.b_absxk = (1.0 - matlab_node_B.rtb_delta_qe_idx_3) * 0.01 +
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0];
  matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] = 1.0471975511965976;
  } else if (matlab_node_B.b_absxk < -1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S17>/Discrete Transfer Fcn'
  matlab_node_DW.DiscreteTransferFcn_states[0] = matlab_node_B.qe_matlab_idx_2;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S17>/deltaQuatError'

  matlab_node_B.b_absxk = (0.0 - matlab_node_B.DigitalClock) * 0.01 +
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1];
  matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] = 1.0471975511965976;
  } else if (matlab_node_B.b_absxk < -1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S17>/Discrete Transfer Fcn'
  matlab_node_DW.DiscreteTransferFcn_states[1] = matlab_node_B.qe_matlab_idx_3;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S17>/deltaQuatError'

  matlab_node_B.b_absxk = (0.0 - matlab_node_B.hold_timer) * 0.01 +
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2];
  matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] = 1.0471975511965976;
  } else if (matlab_node_B.b_absxk < -1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S17>/Discrete Transfer Fcn'
  matlab_node_DW.DiscreteTransferFcn_states[2] =
    matlab_node_B.DiscreteTransferFcn_tmp_idx_2;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S17>/deltaQuatError'

  matlab_node_B.b_absxk = (0.0 - matlab_node_B.rtb_delta_qe_idx_2) * 0.01 +
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3];
  matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] = 1.0471975511965976;
  } else if (matlab_node_B.b_absxk < -1.0471975511965976) {
    matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S17>/Discrete Transfer Fcn'
  matlab_node_DW.DiscreteTransferFcn_states[3] = matlab_node_B.qe_matlab_idx_1;

  // Update for DiscreteIntegrator: '<S127>/Integrator' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read1'
  //   DiscreteIntegrator: '<S122>/Filter'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   DiscreteIntegrator: '<S67>/Filter'
  //   DiscreteIntegrator: '<S72>/Integrator'
  //
  if (integrator_reset > 0) {
    matlab_node_DW.Integrator_PrevResetState = 1;
    matlab_node_DW.Filter_PrevResetState = 1;
    matlab_node_DW.Integrator_PrevResetState_l = 1;
    matlab_node_DW.Filter_PrevResetState_b = 1;
    matlab_node_DW.Integrator_PrevResetState_i = 1;
  } else {
    matlab_node_DW.Integrator_PrevResetState = 0;
    matlab_node_DW.Filter_PrevResetState = 0;
    matlab_node_DW.Integrator_PrevResetState_l = 0;
    matlab_node_DW.Filter_PrevResetState_b = 0;
    matlab_node_DW.Integrator_PrevResetState_i = 0;
  }

  // Switch: '<S117>/Switch' incorporates:
  //   Constant: '<S117>/Constant1'
  //   DiscreteIntegrator: '<S127>/Integrator'
  //   Gain: '<S124>/Integral Gain'
  //   Logic: '<S117>/AND3'

  if (rtb_RelationalOperator_c[0]) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.eul_error[0];
  }

  // Update for DiscreteIntegrator: '<S127>/Integrator' incorporates:
  //   Switch: '<S117>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE[0];
  matlab_node_DW.Integrator_DSTATE[0] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0) {
    matlab_node_DW.Integrator_DSTATE[0] = 1.0;
  } else if (matlab_node_B.b_absxk < -1.0) {
    matlab_node_DW.Integrator_DSTATE[0] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S122>/Filter' incorporates:
  //   Gain: '<S130>/Filter Coefficient'

  matlab_node_DW.Filter_DSTATE[0] += 0.01 * matlab_node_B.R_error[0];

  // Switch: '<S62>/Switch1' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant'
  //   Constant: '<S62>/Constant2'
  //   RelationalOperator: '<S62>/fix for DT propagation issue'

  if (matlab_node_B.rtb_Integrator_p_idx_0 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S62>/Switch2' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant3'
  //   Constant: '<S62>/Constant4'
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S69>/Integral Gain'
  //   RelationalOperator: '<S62>/fix for DT propagation issue1'

  if (matlab_node_B.eps_g[0] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S62>/Switch' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant1'
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S69>/Integral Gain'
  //   Logic: '<S62>/AND3'
  //   RelationalOperator: '<S62>/Equal1'
  //   RelationalOperator: '<S62>/Relational Operator'
  //   Switch: '<S62>/Switch1'
  //   Switch: '<S62>/Switch2'

  if ((matlab_node_B.rtb_Integrator_p_idx_0 != 0.0) && (tmp == tmp_0)) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.eps_g[0];
  }

  // Update for DiscreteIntegrator: '<S72>/Integrator' incorporates:
  //   Switch: '<S62>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE_l[0];
  matlab_node_DW.Integrator_DSTATE_l[0] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_DW.Integrator_DSTATE_l[0] = 10.0;
  } else if (matlab_node_B.b_absxk < -10.0) {
    matlab_node_DW.Integrator_DSTATE_l[0] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S67>/Filter'
  matlab_node_DW.Filter_DSTATE_e[0] += 0.01 * matlab_node_B.dRb_u[0];

  // Switch: '<S172>/Switch2' incorporates:
  //   Constant: '<S172>/Clamping_zero'
  //   Constant: '<S172>/Constant3'
  //   Constant: '<S172>/Constant4'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   RelationalOperator: '<S172>/fix for DT propagation issue1'

  if (matlab_node_B.IntegralGain_a[0] > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S172>/Switch' incorporates:
  //   Constant: '<S172>/Constant1'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Logic: '<S172>/AND3'
  //   RelationalOperator: '<S172>/Equal1'
  //   Switch: '<S172>/Switch2'

  if (rtb_RelationalOperator_b[0] && (rtb_Switch1[0] == tmp)) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.IntegralGain_a[0];
  }

  // Update for DiscreteIntegrator: '<S182>/Integrator' incorporates:
  //   Switch: '<S172>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE_f[0];
  matlab_node_DW.Integrator_DSTATE_f[0] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 100.0) {
    matlab_node_DW.Integrator_DSTATE_f[0] = 100.0;
  } else if (matlab_node_B.b_absxk < -100.0) {
    matlab_node_DW.Integrator_DSTATE_f[0] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S177>/Filter'
  matlab_node_DW.Filter_DSTATE_k[0] += 0.01 *
    matlab_node_B.rtb_FilterCoefficient_h_idx_0;

  // Switch: '<S117>/Switch' incorporates:
  //   Constant: '<S117>/Constant1'
  //   DiscreteIntegrator: '<S127>/Integrator'
  //   Gain: '<S124>/Integral Gain'
  //   Logic: '<S117>/AND3'

  if (rtb_RelationalOperator_c[1]) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.eul_error[1];
  }

  // Update for DiscreteIntegrator: '<S127>/Integrator' incorporates:
  //   Switch: '<S117>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE[1];
  matlab_node_DW.Integrator_DSTATE[1] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0) {
    matlab_node_DW.Integrator_DSTATE[1] = 1.0;
  } else if (matlab_node_B.b_absxk < -1.0) {
    matlab_node_DW.Integrator_DSTATE[1] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S122>/Filter' incorporates:
  //   Gain: '<S130>/Filter Coefficient'

  matlab_node_DW.Filter_DSTATE[1] += 0.01 * matlab_node_B.R_error[1];

  // Switch: '<S62>/Switch1' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant'
  //   Constant: '<S62>/Constant2'
  //   RelationalOperator: '<S62>/fix for DT propagation issue'

  if (matlab_node_B.rtb_Integrator_p_idx_1 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S62>/Switch2' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant3'
  //   Constant: '<S62>/Constant4'
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S69>/Integral Gain'
  //   RelationalOperator: '<S62>/fix for DT propagation issue1'

  if (matlab_node_B.eps_g[1] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S62>/Switch' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant1'
  //   DiscreteIntegrator: '<S72>/Integrator'
  //   Gain: '<S69>/Integral Gain'
  //   Logic: '<S62>/AND3'
  //   RelationalOperator: '<S62>/Equal1'
  //   RelationalOperator: '<S62>/Relational Operator'
  //   Switch: '<S62>/Switch1'
  //   Switch: '<S62>/Switch2'

  if ((matlab_node_B.rtb_Integrator_p_idx_1 != 0.0) && (tmp == tmp_0)) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.eps_g[1];
  }

  // Update for DiscreteIntegrator: '<S72>/Integrator' incorporates:
  //   Switch: '<S62>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE_l[1];
  matlab_node_DW.Integrator_DSTATE_l[1] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_DW.Integrator_DSTATE_l[1] = 10.0;
  } else if (matlab_node_B.b_absxk < -10.0) {
    matlab_node_DW.Integrator_DSTATE_l[1] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S67>/Filter'
  matlab_node_DW.Filter_DSTATE_e[1] += 0.01 * matlab_node_B.dRb_u[1];

  // Switch: '<S172>/Switch2' incorporates:
  //   Constant: '<S172>/Clamping_zero'
  //   Constant: '<S172>/Constant3'
  //   Constant: '<S172>/Constant4'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   RelationalOperator: '<S172>/fix for DT propagation issue1'

  if (matlab_node_B.IntegralGain_a[1] > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S172>/Switch' incorporates:
  //   Constant: '<S172>/Constant1'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Logic: '<S172>/AND3'
  //   RelationalOperator: '<S172>/Equal1'
  //   Switch: '<S172>/Switch2'

  if (rtb_RelationalOperator_b[1] && (rtb_Switch1[1] == tmp)) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.IntegralGain_a[1];
  }

  // Update for DiscreteIntegrator: '<S182>/Integrator' incorporates:
  //   Switch: '<S172>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE_f[1];
  matlab_node_DW.Integrator_DSTATE_f[1] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 100.0) {
    matlab_node_DW.Integrator_DSTATE_f[1] = 100.0;
  } else if (matlab_node_B.b_absxk < -100.0) {
    matlab_node_DW.Integrator_DSTATE_f[1] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S177>/Filter'
  matlab_node_DW.Filter_DSTATE_k[1] += 0.01 * matlab_node_B.rtb_Filter_h_idx_0;

  // Switch: '<S117>/Switch' incorporates:
  //   Constant: '<S117>/Constant1'
  //   DiscreteIntegrator: '<S127>/Integrator'
  //   Gain: '<S124>/Integral Gain'
  //   Logic: '<S117>/AND3'

  if (rtb_RelationalOperator_c[2]) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.eul_error[2];
  }

  // Update for DiscreteIntegrator: '<S127>/Integrator' incorporates:
  //   Switch: '<S117>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE[2];
  matlab_node_DW.Integrator_DSTATE[2] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 1.0) {
    matlab_node_DW.Integrator_DSTATE[2] = 1.0;
  } else if (matlab_node_B.b_absxk < -1.0) {
    matlab_node_DW.Integrator_DSTATE[2] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S122>/Filter' incorporates:
  //   Gain: '<S130>/Filter Coefficient'

  matlab_node_DW.Filter_DSTATE[2] += 0.01 * matlab_node_B.R_error[2];

  // Switch: '<S62>/Switch1' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant'
  //   Constant: '<S62>/Constant2'
  //   RelationalOperator: '<S62>/fix for DT propagation issue'

  if (matlab_node_B.rtb_Integrator_p_idx_2 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S62>/Switch2' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant3'
  //   Constant: '<S62>/Constant4'
  //   Gain: '<S77>/Proportional Gain'
  //   RelationalOperator: '<S62>/fix for DT propagation issue1'

  if (matlab_node_B.eps_n > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S62>/Switch' incorporates:
  //   Constant: '<S62>/Clamping_zero'
  //   Constant: '<S62>/Constant1'
  //   Logic: '<S62>/AND3'
  //   RelationalOperator: '<S62>/Equal1'
  //   RelationalOperator: '<S62>/Relational Operator'
  //   Switch: '<S62>/Switch1'
  //   Switch: '<S62>/Switch2'

  if ((matlab_node_B.rtb_Integrator_p_idx_2 != 0.0) && (tmp == tmp_0)) {
    matlab_node_B.eps_n = 0.0;
  }

  // Update for DiscreteIntegrator: '<S72>/Integrator' incorporates:
  //   Switch: '<S62>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.eps_n +
    matlab_node_DW.Integrator_DSTATE_l[2];
  matlab_node_DW.Integrator_DSTATE_l[2] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 10.0) {
    matlab_node_DW.Integrator_DSTATE_l[2] = 10.0;
  } else if (matlab_node_B.b_absxk < -10.0) {
    matlab_node_DW.Integrator_DSTATE_l[2] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S67>/Filter' incorporates:
  //   Gain: '<S75>/Filter Coefficient'

  matlab_node_DW.Filter_DSTATE_e[2] += 0.01 * matlab_node_B.rotm_tmp;

  // Switch: '<S172>/Switch2' incorporates:
  //   Constant: '<S172>/Clamping_zero'
  //   Constant: '<S172>/Constant3'
  //   Constant: '<S172>/Constant4'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   RelationalOperator: '<S172>/fix for DT propagation issue1'

  if (matlab_node_B.IntegralGain_a[2] > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S172>/Switch' incorporates:
  //   Constant: '<S172>/Constant1'
  //   DiscreteIntegrator: '<S182>/Integrator'
  //   Logic: '<S172>/AND3'
  //   RelationalOperator: '<S172>/Equal1'
  //   Switch: '<S172>/Switch2'

  if (rtb_RelationalOperator_b[2] && (rtb_Switch1[2] == tmp)) {
    matlab_node_B.phi = 0.0;
  } else {
    matlab_node_B.phi = matlab_node_B.IntegralGain_a[2];
  }

  // Update for DiscreteIntegrator: '<S182>/Integrator' incorporates:
  //   Switch: '<S172>/Switch'

  matlab_node_B.b_absxk = 0.01 * matlab_node_B.phi +
    matlab_node_DW.Integrator_DSTATE_f[2];
  matlab_node_DW.Integrator_DSTATE_f[2] = matlab_node_B.b_absxk;
  if (matlab_node_B.b_absxk > 100.0) {
    matlab_node_DW.Integrator_DSTATE_f[2] = 100.0;
  } else if (matlab_node_B.b_absxk < -100.0) {
    matlab_node_DW.Integrator_DSTATE_f[2] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S177>/Filter' incorporates:
  //   DataStoreRead: '<S17>/Data Store Read9'
  //   Gain: '<S185>/Filter Coefficient'
  //
  matlab_node_DW.Filter_DSTATE_k[2] += 0.01 * matlab_node_B.rtb_Cbi_tmp_tmp_d;
  if (integrator_reset > 0) {
    matlab_node_DW.Filter_PrevResetState_n = 1;
  } else {
    matlab_node_DW.Filter_PrevResetState_n = 0;
  }

  // End of Outputs for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // DataStoreWrite: '<S6>/Data Store Write' incorporates:
  //   MATLABSystem: '<S202>/SourceBlock'
  //
  matlab_node_DW.start_new_cmd_flag = b_varargout_1;

  // DataStoreRead: '<S6>/Data Store Read'
  rtb_OR1 = matlab_node_DW.mission_is_started;

  // MATLAB Function: '<S6>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<S6>/Data Store Write1'
  //   DataStoreWrite: '<S6>/Data Store Write2'
  //   MATLABSystem: '<S202>/SourceBlock'
  //
  if ((!matlab_node_DW.mission_is_started) && b_varargout_1) {
    matlab_node_DW.reset_dvl_pos = true;
    matlab_node_DW.mission_is_started = true;
  } else {
    matlab_node_DW.reset_dvl_pos = false;
  }

  // End of MATLAB Function: '<S6>/MATLAB Function'

  // MATLAB Function: '<S6>/statusKwdToBool' incorporates:
  //   UnitDelay: '<S6>/Unit Delay'

  fd[0] = matlab_node_DW.UnitDelay_DSTATE[0];
  fd[1] = matlab_node_DW.UnitDelay_DSTATE[1];
  fd[2] = matlab_node_DW.UnitDelay_DSTATE[2];
  fd[3] = matlab_node_DW.UnitDelay_DSTATE[3];
  matlab_node_B.ret = std::memcmp(&a[0], &fd[0], 4);
  if (matlab_node_B.ret == 0) {
    matlab_node_B.ret = 0;
  } else {
    matlab_node_B.ret = std::memcmp(&b_a[0], &fd[0], 4);
    if (matlab_node_B.ret == 0) {
      matlab_node_B.ret = 1;
    } else {
      matlab_node_B.ret = std::memcmp(&c_a_0[0], &fd[0], 4);
      if (matlab_node_B.ret == 0) {
        matlab_node_B.ret = 2;
      } else {
        matlab_node_B.ret = -1;
      }
    }
  }

  switch (matlab_node_B.ret) {
   case 0:
    matlab_node_B.result_msg.success = true;
    for (i = 0; i < 16; i++) {
      matlab_node_B.result_msg.found_object[i] = b_0[i];
    }

    matlab_node_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S6>/Subsystem' incorporates:
    //   EnablePort: '<S203>/Enable'

    // MATLABSystem: '<S207>/SinkBlock'
    Pub_matlab_node_108_269.publish(&matlab_node_B.result_msg);

    // End of Outputs for SubSystem: '<S6>/Subsystem'
    break;

   case 1:
    matlab_node_B.result_msg.success = false;
    for (i = 0; i < 16; i++) {
      matlab_node_B.result_msg.found_object[i] = b_0[i];
    }

    matlab_node_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S6>/Subsystem' incorporates:
    //   EnablePort: '<S203>/Enable'

    // MATLABSystem: '<S207>/SinkBlock'
    Pub_matlab_node_108_269.publish(&matlab_node_B.result_msg);

    // End of Outputs for SubSystem: '<S6>/Subsystem'
    break;

   case 2:
    break;
  }

  // End of MATLAB Function: '<S6>/statusKwdToBool'

  // BusCreator: '<S8>/Bus Creator3'
  for (i = 0; i < 8; i++) {
    // Switch: '<S5>/Switch' incorporates:
    //   DataStoreRead: '<S5>/Data Store Read2'
    //   DataTypeConversion: '<S17>/Cast'
    //   Logic: '<S5>/OR'

    if (matlab_node_DW.joystick_mode_enabled_flag) {
      matlab_node_B.BusCreator3.pwms[i] = 1500;
    } else {
      matlab_node_B.BusCreator3.pwms[i] = matlab_node_B.Cast[i];
    }

    // End of Switch: '<S5>/Switch'
  }

  // End of BusCreator: '<S8>/Bus Creator3'

  // MATLABSystem: '<S210>/SinkBlock'
  Pub_matlab_node_38_2.publish(&matlab_node_B.BusCreator3);

  // SignalConversion generated from: '<S14>/ SFunction ' incorporates:
  //   DataStoreRead: '<Root>/Data Store Read6'
  //   DataStoreRead: '<S5>/Data Store Read2'
  //   DataStoreWrite: '<S5>/Data Store Write6'
  //   DataTypeConversion: '<S10>/Cast'
  //   DataTypeConversion: '<S5>/Cast'
  //   DataTypeConversion: '<S6>/Cast'
  //   MATLAB Function: '<S10>/derivedStateEstimates'
  //   MATLAB Function: '<S3>/MATLAB Function'

  matlab_node_B.TmpSignalConversionAtSFunct[0] = matlab_node_B.X_u[0];
  matlab_node_B.TmpSignalConversionAtSFunct[6] = matlab_node_B.scale;
  matlab_node_B.TmpSignalConversionAtSFunct[9] = matlab_node_B.eta;
  matlab_node_B.TmpSignalConversionAtSFunct[1] = matlab_node_B.X_u[1];
  matlab_node_B.TmpSignalConversionAtSFunct[7] = matlab_node_B.absxk;
  matlab_node_B.TmpSignalConversionAtSFunct[10] = matlab_node_B.b_t;
  matlab_node_B.TmpSignalConversionAtSFunct[2] = matlab_node_B.X_u[2];
  matlab_node_B.TmpSignalConversionAtSFunct[8] = matlab_node_B.b_scale;
  matlab_node_B.TmpSignalConversionAtSFunct[11] = matlab_node_B.t;
  matlab_node_B.TmpSignalConversionAtSFunct[12] =
    matlab_node_DW.joystick_mode_enabled_flag;
  matlab_node_B.TmpSignalConversionAtSFunct[13] = rtb_OR;
  matlab_node_B.TmpSignalConversionAtSFunct[14] = rtb_OR1;
  matlab_node_B.TmpSignalConversionAtSFunct[15] = debug_start_new_cmd_flag;

  // MATLAB Function: '<S3>/MATLAB Function'
  for (i = 0; i < 256; i++) {
    matlab_node_B.temp_char[i] = '_';
  }

  matlab_node_B.eta = 1.0;
  for (matlab_node_B.ret = 0; matlab_node_B.ret < 16; matlab_node_B.ret++) {
    for (i = 0; i < 16; i++) {
      matlab_node_B.s[i] = ' ';
    }

    matlab_node_B.theta = std::abs
      (matlab_node_B.TmpSignalConversionAtSFunct[matlab_node_B.ret]);
    matlab_node_B.phi = std::floor(matlab_node_B.theta);
    if (matlab_node_B.phi < 4.294967296E+9) {
      matlab_node_B.temp = static_cast<uint32_T>(matlab_node_B.phi);
    } else {
      matlab_node_B.temp = MAX_uint32_T;
    }

    matlab_node_B.int_part = matlab_node_B.temp;
    matlab_node_B.phi = std::round((matlab_node_B.theta - static_cast<real_T>
      (matlab_node_B.temp)) * 10000.0);
    if (matlab_node_B.phi < 4.294967296E+9) {
      if (matlab_node_B.phi >= 0.0) {
        matlab_node_B.frac_part = static_cast<uint32_T>(matlab_node_B.phi);
      } else {
        matlab_node_B.frac_part = 0U;
      }
    } else {
      matlab_node_B.frac_part = MAX_uint32_T;
    }

    if (matlab_node_B.frac_part >= 10000U) {
      matlab_node_B.int_part = matlab_node_B.temp + /*MW:OvSatOk*/ 1U;
      if (matlab_node_B.temp + 1U < matlab_node_B.temp) {
        matlab_node_B.int_part = MAX_uint32_T;
      }

      matlab_node_B.frac_part = 0U;
    }

    matlab_node_B.temp = matlab_node_B.int_part;
    for (i = 0; i < 10; i++) {
      matlab_node_B.digits[9 - i] = static_cast<int8_T>(static_cast<int8_T>
        (matlab_node_B.temp - matlab_node_B.temp / 10U * 10U) + 48);
      matlab_node_B.temp /= 10U;
    }

    debug_start_new_cmd_flag = 9;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 10)) {
      if (matlab_node_B.digits[i] != '0') {
        debug_start_new_cmd_flag = i;
        exitg1 = true;
      } else {
        i++;
      }
    }

    if (matlab_node_B.int_part == 0U) {
      debug_start_new_cmd_flag = 9;
    }

    matlab_node_B.pos = 1;
    if (matlab_node_B.TmpSignalConversionAtSFunct[matlab_node_B.ret] < 0.0) {
      matlab_node_B.s[0] = '-';
      matlab_node_B.pos = 2;
    }

    force_column_size_idx_0 = -debug_start_new_cmd_flag;
    for (i = 0; i <= force_column_size_idx_0 + 9; i++) {
      matlab_node_B.s[(matlab_node_B.pos + i) - 1] =
        matlab_node_B.digits[debug_start_new_cmd_flag + i];
    }

    matlab_node_B.pos = (matlab_node_B.pos - debug_start_new_cmd_flag) + 9;
    matlab_node_B.s[matlab_node_B.pos] = '.';
    matlab_node_B.int_part = matlab_node_B.frac_part / 10U;
    fd[2] = static_cast<int8_T>(static_cast<int8_T>(matlab_node_B.int_part -
      matlab_node_B.int_part / 10U * 10U) + 48);
    matlab_node_B.int_part /= 10U;
    matlab_node_B.s[matlab_node_B.pos + 1] = static_cast<int8_T>(static_cast<
      int32_T>(matlab_node_B.int_part / 10U) + 48);
    matlab_node_B.s[matlab_node_B.pos + 2] = static_cast<int8_T>
      (static_cast<int8_T>(matlab_node_B.int_part - matlab_node_B.int_part / 10U
        * 10U) + 48);
    matlab_node_B.s[matlab_node_B.pos + 3] = fd[2];
    matlab_node_B.s[matlab_node_B.pos + 4] = static_cast<int8_T>
      (static_cast<int8_T>(matlab_node_B.frac_part - matlab_node_B.frac_part /
        10U * 10U) + 48);
    matlab_node_B.pos += 5;
    matlab_node_B.phi = (matlab_node_B.eta + static_cast<real_T>
                         (matlab_node_B.pos)) - 1.0;
    if (matlab_node_B.phi <= 256.0) {
      if (matlab_node_B.eta > matlab_node_B.phi) {
        debug_start_new_cmd_flag = 1;
      } else {
        debug_start_new_cmd_flag = static_cast<int32_T>(matlab_node_B.eta);
      }

      for (i = 0; i < matlab_node_B.pos; i++) {
        matlab_node_B.temp_char[(debug_start_new_cmd_flag + i) - 1] =
          matlab_node_B.s[i];
      }

      matlab_node_B.eta += static_cast<real_T>(matlab_node_B.pos);
    }

    if ((matlab_node_B.ret + 1 < 16) && (matlab_node_B.eta <= 256.0)) {
      matlab_node_B.temp_char[static_cast<int32_T>(matlab_node_B.eta) - 1] = ',';
      matlab_node_B.eta++;
    }
  }

  for (i = 0; i < 256; i++) {
    matlab_node_B.debug_msg.message[i] = static_cast<uint8_T>
      (matlab_node_B.temp_char[i]);
  }

  // MATLABSystem: '<S15>/SinkBlock'
  Pub_matlab_node_266_3.publish(&matlab_node_B.debug_msg);

  // Update for DiscreteIntegrator: '<S10>/Position Integrator' incorporates:
  //   MATLABSystem: '<S1>/SourceBlock'
  //
  matlab_node_DW.PositionIntegrator_IC_LOADING = 0U;
  if (b_varargout_1_1) {
    matlab_node_DW.PositionIntegrator_PrevResetSta = 1;
  } else {
    matlab_node_DW.PositionIntegrator_PrevResetSta = 0;
  }

  // Update for DiscreteIntegrator: '<S10>/Velocity Integrator'
  matlab_node_DW.VelocityIntegrator_IC_LOADING = 0U;

  // Update for DiscreteIntegrator: '<S10>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S10>/Velocity Integrator'
  //   MATLAB Function: '<S10>/derivedStateEstimates'

  matlab_node_DW.PositionIntegrator_DSTATE[0] += 0.01 *
    matlab_node_DW.VelocityIntegrator_DSTATE[0];

  // Update for DiscreteIntegrator: '<S10>/Velocity Integrator' incorporates:
  //   Sum: '<S10>/Sum'

  matlab_node_DW.VelocityIntegrator_DSTATE[0] += 0.01 *
    matlab_node_B.rtb_dvl_pos_m[0];

  // Update for DiscreteIntegrator: '<S10>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S10>/Velocity Integrator'
  //   MATLAB Function: '<S10>/derivedStateEstimates'

  matlab_node_DW.PositionIntegrator_DSTATE[1] += 0.01 *
    matlab_node_DW.VelocityIntegrator_DSTATE[1];

  // Update for DiscreteIntegrator: '<S10>/Velocity Integrator' incorporates:
  //   Sum: '<S10>/Sum'

  matlab_node_DW.VelocityIntegrator_DSTATE[1] += 0.01 *
    matlab_node_B.rtb_dvl_pos_m[1];

  // Update for DiscreteIntegrator: '<S10>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S10>/Velocity Integrator'
  //   MATLAB Function: '<S10>/derivedStateEstimates'

  matlab_node_DW.PositionIntegrator_DSTATE[2] += 0.01 *
    matlab_node_DW.VelocityIntegrator_DSTATE[2];

  // Update for DiscreteIntegrator: '<S10>/Velocity Integrator' incorporates:
  //   MATLABSystem: '<S4>/SourceBlock'
  //   Sum: '<S10>/Sum'
  //
  matlab_node_DW.VelocityIntegrator_DSTATE[2] += 0.01 *
    matlab_node_B.rtb_dvl_pos_m[2];
  if (b_varargout_1_0) {
    matlab_node_DW.VelocityIntegrator_PrevResetSta = 1;
  } else {
    matlab_node_DW.VelocityIntegrator_PrevResetSta = 0;
  }

  // Update for UnitDelay: '<S6>/Unit Delay'
  matlab_node_DW.UnitDelay_DSTATE[0] = rtb_cmd_status[0];
  matlab_node_DW.UnitDelay_DSTATE[1] = rtb_cmd_status[1];
  matlab_node_DW.UnitDelay_DSTATE[2] = rtb_cmd_status[2];
  matlab_node_DW.UnitDelay_DSTATE[3] = rtb_cmd_status[3];

  // Update absolute time
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&matlab_node_M)->Timing.clockTick0++;
}

// Model step function for TID1
void matlab_node::step1()              // Sample time: [0.5s, 0.0s]
{
  // MATLABSystem: '<S209>/SinkBlock' incorporates:
  //   Constant: '<S208>/Constant'

  Pub_matlab_node_37_150.publish(&matlab_node_ConstP.Constant_Value_e);
}

// Use this function only if you need to maintain compatibility with an existing static main program.
void matlab_node_step(matlab_node & matlab_node_Obj_In, int_T tid)
{
  switch (tid) {
   case 0 :
    matlab_node_Obj_In.step0();
    break;

   case 1 :
    matlab_node_Obj_In.step1();
    break;

   default :
    // do nothing
    break;
  }
}

// Model initialize function
void matlab_node::initialize()
{
  // Start for DataStoreMemory: '<Root>/Data Store Memory1'
  matlab_node_DW.start_new_cmd_flag = true;

  // InitializeConditions for DiscreteIntegrator: '<S10>/Position Integrator'
  matlab_node_DW.PositionIntegrator_PrevResetSta = 2;
  matlab_node_DW.PositionIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S10>/Velocity Integrator'
  matlab_node_DW.VelocityIntegrator_PrevResetSta = 2;
  matlab_node_DW.VelocityIntegrator_IC_LOADING = 1U;

  // SystemInitialize for Enabled SubSystem: '<S5>/cascaded_pid_controller_cgn'
  // InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' 
  matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S127>/Integrator'
  matlab_node_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S122>/Filter'
  matlab_node_DW.Filter_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S72>/Integrator'
  matlab_node_DW.Integrator_PrevResetState_l = 2;

  // InitializeConditions for DiscreteIntegrator: '<S67>/Filter'
  matlab_node_DW.Filter_PrevResetState_b = 2;

  // InitializeConditions for DiscreteIntegrator: '<S182>/Integrator'
  matlab_node_DW.Integrator_PrevResetState_i = 2;

  // InitializeConditions for DiscreteIntegrator: '<S177>/Filter'
  matlab_node_DW.Filter_PrevResetState_n = 2;

  // End of SystemInitialize for SubSystem: '<S5>/cascaded_pid_controller_cgn'

  // SystemInitialize for Enabled SubSystem: '<S6>/Subsystem'
  // Start for MATLABSystem: '<S207>/SinkBlock'
  matlab_node_DW.obj_o3.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_o3.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_o3.isSetupComplete = false;
  matlab_node_DW.obj_o3.isInitialized = 1;
  matlab_no_Publisher_setupImpl_g(&matlab_node_DW.obj_o3);
  matlab_node_DW.obj_o3.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S6>/Subsystem'

  // SystemInitialize for MATLAB Function: '<S10>/dvl_reset'
  matlab_node_DW.prior_flag = true;

  // Start for MATLABSystem: '<S202>/SourceBlock'
  matlab_node_DW.obj.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj.isSetupComplete = false;
  matlab_node_DW.obj.isInitialized = 1;
  matlab_Subscriber_setupImpl_gzo(&matlab_node_DW.obj);
  matlab_node_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  matlab_node_DW.obj_e3.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_e3.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_e3.isSetupComplete = false;
  matlab_node_DW.obj_e3.isInitialized = 1;
  matlab_n_Subscriber_setupImpl_g(&matlab_node_DW.obj_e3);
  matlab_node_DW.obj_e3.isSetupComplete = true;

  // Start for MATLABSystem: '<S4>/SourceBlock'
  matlab_node_DW.obj_e.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_e.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_e.isSetupComplete = false;
  matlab_node_DW.obj_e.isInitialized = 1;
  matlab__Subscriber_setupImpl_gz(&matlab_node_DW.obj_e);
  matlab_node_DW.obj_e.isSetupComplete = true;

  // Start for MATLABSystem: '<S1>/SourceBlock'
  matlab_node_DW.obj_d.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_d.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_d.isSetupComplete = false;
  matlab_node_DW.obj_d.isInitialized = 1;
  matlab_nod_Subscriber_setupImpl(&matlab_node_DW.obj_d);
  matlab_node_DW.obj_d.isSetupComplete = true;

  // Start for MATLABSystem: '<S210>/SinkBlock'
  matlab_node_DW.obj_f.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_f.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_f.isSetupComplete = false;
  matlab_node_DW.obj_f.isInitialized = 1;
  matlab__Publisher_setupImpl_gzo(&matlab_node_DW.obj_f);
  matlab_node_DW.obj_f.isSetupComplete = true;

  // Start for MATLABSystem: '<S15>/SinkBlock'
  matlab_node_DW.obj_h.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_h.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_h.isSetupComplete = false;
  matlab_node_DW.obj_h.isInitialized = 1;
  matlab_node_Publisher_setupImpl(&matlab_node_DW.obj_h);
  matlab_node_DW.obj_h.isSetupComplete = true;

  // Start for MATLABSystem: '<S209>/SinkBlock'
  matlab_node_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
  matlab_node_DW.obj_o.matlabCodegenIsDeleted = false;
  matlab_node_DW.obj_o.isSetupComplete = false;
  matlab_node_DW.obj_o.isInitialized = 1;
  matlab_n_Publisher_setupImpl_gz(&matlab_node_DW.obj_o);
  matlab_node_DW.obj_o.isSetupComplete = true;
}

// Model terminate function
void matlab_node::terminate()
{
  // Terminate for MATLABSystem: '<S202>/SourceBlock'
  if (!matlab_node_DW.obj.matlabCodegenIsDeleted) {
    matlab_node_DW.obj.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj.isInitialized == 1) &&
        matlab_node_DW.obj.isSetupComplete) {
      Sub_matlab_node_108_265.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S202>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!matlab_node_DW.obj_e3.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_e3.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_e3.isInitialized == 1) &&
        matlab_node_DW.obj_e3.isSetupComplete) {
      Sub_matlab_node_8.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!matlab_node_DW.obj_e.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_e.isInitialized == 1) &&
        matlab_node_DW.obj_e.isSetupComplete) {
      Sub_matlab_node_20.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'

  // Terminate for MATLABSystem: '<S1>/SourceBlock'
  if (!matlab_node_DW.obj_d.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_d.isInitialized == 1) &&
        matlab_node_DW.obj_d.isSetupComplete) {
      Sub_matlab_node_3.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S6>/Subsystem'
  // Terminate for MATLABSystem: '<S207>/SinkBlock'
  if (!matlab_node_DW.obj_o3.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_o3.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_o3.isInitialized == 1) &&
        matlab_node_DW.obj_o3.isSetupComplete) {
      Pub_matlab_node_108_269.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S207>/SinkBlock'
  // End of Terminate for SubSystem: '<S6>/Subsystem'

  // Terminate for MATLABSystem: '<S210>/SinkBlock'
  if (!matlab_node_DW.obj_f.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_f.isInitialized == 1) &&
        matlab_node_DW.obj_f.isSetupComplete) {
      Pub_matlab_node_38_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S210>/SinkBlock'

  // Terminate for MATLABSystem: '<S15>/SinkBlock'
  if (!matlab_node_DW.obj_h.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_h.isInitialized == 1) &&
        matlab_node_DW.obj_h.isSetupComplete) {
      Pub_matlab_node_266_3.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S15>/SinkBlock'

  // Terminate for MATLABSystem: '<S209>/SinkBlock'
  if (!matlab_node_DW.obj_o.matlabCodegenIsDeleted) {
    matlab_node_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((matlab_node_DW.obj_o.isInitialized == 1) &&
        matlab_node_DW.obj_o.isSetupComplete) {
      Pub_matlab_node_37_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S209>/SinkBlock'
}

// Constructor
matlab_node::matlab_node() :
  matlab_node_B(),
  matlab_node_DW(),
  matlab_node_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
matlab_node::~matlab_node() = default;

// Real-Time Model get method
RT_MODEL_matlab_node_T * matlab_node::getRTM()
{
  return (&matlab_node_M);
}

uint8_T &RT_MODEL_matlab_node_T::TaskCounter(int32_T idx)
{
  return (Timing.TaskCounters.TID[(idx)]);
}

boolean_T RT_MODEL_matlab_node_T::StepTask(int32_T idx) const
{
  return (Timing.TaskCounters.TID[(idx)] == 0);
}

const char_T* RT_MODEL_matlab_node_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_matlab_node_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
