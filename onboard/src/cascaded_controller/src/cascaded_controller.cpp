//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cascaded_controller.cpp
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
#include "cascaded_controller.h"
#include "cascaded_controller_types.h"
#include "rtwtypes.h"
#include <cmath>
#include "cascaded_controller_private.h"
#include <cstring>
#include "rmw/qos_profiles.h"
#include <stddef.h>
#include "cmath"
#include "rt_defines.h"

static void rate_scheduler(RT_MODEL_cascaded_controller_T *const
  cascaded_controller_M);

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(RT_MODEL_cascaded_controller_T *const
  cascaded_controller_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (cascaded_controller_M->Timing.TaskCounters.TID[1])++;
  if ((cascaded_controller_M->Timing.TaskCounters.TID[1]) > 49) {// Sample time: [0.5s, 0.0s] 
    cascaded_controller_M->Timing.TaskCounters.TID[1] = 0;
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

// Function for MATLAB Function: '<S13>/guidanceLaw'
void cascaded_controller::cascaded_controller_wrapToPi(real_T *lambda)
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
      cascaded_controller_B.q_j = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      cascaded_controller_B.q_j = (rtNaN);
    } else {
      cascaded_controller_B.q_j = std::abs((*lambda + 3.1415926535897931) /
        6.2831853071795862);
      if (std::abs(cascaded_controller_B.q_j - std::floor
                   (cascaded_controller_B.q_j + 0.5)) > 2.2204460492503131E-16 *
          cascaded_controller_B.q_j) {
        cascaded_controller_B.q_j = std::fmod(*lambda + 3.1415926535897931,
          6.2831853071795862);
      } else {
        cascaded_controller_B.q_j = 0.0;
      }

      if (cascaded_controller_B.q_j == 0.0) {
        cascaded_controller_B.q_j = 0.0;
      } else if (cascaded_controller_B.q_j < 0.0) {
        cascaded_controller_B.q_j += 6.2831853071795862;
      }
    }

    cascaded_controller_B.varargin_1_data = cascaded_controller_B.q_j;
  }

  for (int32_T i{0}; i < trueCount; i++) {
    if ((cascaded_controller_B.varargin_1_data == 0.0) && (*lambda +
         3.1415926535897931 > 0.0)) {
      cascaded_controller_B.varargin_1_data = 6.2831853071795862;
    }
  }

  if (tmp) {
    *lambda = cascaded_controller_B.varargin_1_data - 3.1415926535897931;
  }
}

// Function for MATLAB Function: '<S14>/commandExecuter'
void cascaded_controller::cascaded_controller_eulToQuat_m(const real_T Eul[3],
  real_T qib[4])
{
  cascaded_controller_B.eta_n = std::cos(Eul[1]);
  cascaded_controller_B.scale_b = std::sin(Eul[1]);
  cascaded_controller_B.b_t_h = std::cos(Eul[2]);
  cascaded_controller_B.rotm_tmp_b = std::sin(Eul[2]);
  cascaded_controller_B.eps_idx_1 = std::sin(Eul[0]);
  cascaded_controller_B.rotm_tmp_d = std::cos(Eul[0]);
  cascaded_controller_B.rotm_idx_0 = cascaded_controller_B.eta_n *
    cascaded_controller_B.b_t_h;
  cascaded_controller_B.eps_idx_2 = cascaded_controller_B.eta_n *
    cascaded_controller_B.rotm_tmp_b;
  cascaded_controller_B.rotm_idx_4_tmp = cascaded_controller_B.eps_idx_1 *
    cascaded_controller_B.scale_b;
  cascaded_controller_B.eps_idx_0 = cascaded_controller_B.rotm_idx_4_tmp *
    cascaded_controller_B.rotm_tmp_b + cascaded_controller_B.rotm_tmp_d *
    cascaded_controller_B.b_t_h;
  cascaded_controller_B.absxk_l = cascaded_controller_B.eps_idx_1 *
    cascaded_controller_B.eta_n;
  cascaded_controller_B.rotm_idx_8 = cascaded_controller_B.rotm_tmp_d *
    cascaded_controller_B.eta_n;
  cascaded_controller_B.eta_n = std::sqrt(((cascaded_controller_B.rotm_idx_0 +
    cascaded_controller_B.eps_idx_0) + cascaded_controller_B.rotm_idx_8) + 1.0) /
    2.0;
  if (cascaded_controller_B.eta_n != 0.0) {
    cascaded_controller_B.rotm_idx_0 = cascaded_controller_B.rotm_tmp_d *
      cascaded_controller_B.scale_b;
    cascaded_controller_B.rotm_idx_8 = 4.0 * cascaded_controller_B.eta_n;
    cascaded_controller_B.eps_idx_0 = (cascaded_controller_B.absxk_l -
      (cascaded_controller_B.rotm_idx_0 * cascaded_controller_B.rotm_tmp_b -
       cascaded_controller_B.eps_idx_1 * cascaded_controller_B.b_t_h)) /
      cascaded_controller_B.rotm_idx_8;
    cascaded_controller_B.eps_idx_1 = ((cascaded_controller_B.rotm_idx_0 *
      cascaded_controller_B.b_t_h + cascaded_controller_B.eps_idx_1 *
      cascaded_controller_B.rotm_tmp_b) - (-cascaded_controller_B.scale_b)) /
      cascaded_controller_B.rotm_idx_8;
    cascaded_controller_B.eps_idx_2 = (cascaded_controller_B.eps_idx_2 -
      (cascaded_controller_B.rotm_idx_4_tmp * cascaded_controller_B.b_t_h -
       cascaded_controller_B.rotm_tmp_d * cascaded_controller_B.rotm_tmp_b)) /
      cascaded_controller_B.rotm_idx_8;
  } else {
    int32_T b_k;
    int32_T idx;
    cascaded_controller_B.b_t_h = (cascaded_controller_B.rotm_idx_0 + 1.0) / 2.0;
    cascaded_controller_B.x[0] = cascaded_controller_B.b_t_h;
    cascaded_controller_B.eps_idx_1 = (cascaded_controller_B.eps_idx_0 + 1.0) /
      2.0;
    cascaded_controller_B.x[1] = cascaded_controller_B.eps_idx_1;
    cascaded_controller_B.rotm_tmp_b = (cascaded_controller_B.rotm_idx_8 + 1.0) /
      2.0;
    cascaded_controller_B.x[2] = cascaded_controller_B.rotm_tmp_b;
    if (!std::isnan(cascaded_controller_B.b_t_h)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(cascaded_controller_B.x[b_k - 1])) {
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
      cascaded_controller_B.eps_idx_0 = cascaded_controller_B.x[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        cascaded_controller_B.rotm_tmp_d = cascaded_controller_B.x[c_k - 1];
        if (cascaded_controller_B.eps_idx_0 < cascaded_controller_B.rotm_tmp_d)
        {
          cascaded_controller_B.eps_idx_0 = cascaded_controller_B.rotm_tmp_d;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      cascaded_controller_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_h));
      if (std::isnan(cascaded_controller_B.eps_idx_2)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (cascaded_controller_B.eps_idx_2 < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (cascaded_controller_B.eps_idx_2 >
          0.0);
      }

      cascaded_controller_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1)) * cascaded_controller_B.rotm_tmp_d;
      if (std::isnan(-cascaded_controller_B.scale_b)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (-cascaded_controller_B.scale_b < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (-cascaded_controller_B.scale_b > 0.0);
      }

      cascaded_controller_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_b)) * cascaded_controller_B.rotm_tmp_d;
      break;

     case 2:
      cascaded_controller_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1));
      if (std::isnan(cascaded_controller_B.eps_idx_2)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (cascaded_controller_B.eps_idx_2 < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (cascaded_controller_B.eps_idx_2 >
          0.0);
      }

      cascaded_controller_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_h)) * cascaded_controller_B.rotm_tmp_d;
      if (std::isnan(cascaded_controller_B.absxk_l)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (cascaded_controller_B.absxk_l < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (cascaded_controller_B.absxk_l > 0.0);
      }

      cascaded_controller_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_b)) * cascaded_controller_B.rotm_tmp_d;
      break;

     default:
      cascaded_controller_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_b));
      if (std::isnan(-cascaded_controller_B.scale_b)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (-cascaded_controller_B.scale_b < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (-cascaded_controller_B.scale_b > 0.0);
      }

      cascaded_controller_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_h)) * cascaded_controller_B.rotm_tmp_d;
      if (std::isnan(cascaded_controller_B.absxk_l)) {
        cascaded_controller_B.rotm_tmp_d = (rtNaN);
      } else if (cascaded_controller_B.absxk_l < 0.0) {
        cascaded_controller_B.rotm_tmp_d = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_d = (cascaded_controller_B.absxk_l > 0.0);
      }

      cascaded_controller_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1)) * cascaded_controller_B.rotm_tmp_d;
      break;
    }
  }

  cascaded_controller_B.scale_b = 3.3121686421112381E-170;
  cascaded_controller_B.absxk_l = std::abs(cascaded_controller_B.eps_idx_0);
  if (cascaded_controller_B.absxk_l > 3.3121686421112381E-170) {
    cascaded_controller_B.rotm_tmp_b = 1.0;
    cascaded_controller_B.scale_b = cascaded_controller_B.absxk_l;
  } else {
    cascaded_controller_B.b_t_h = cascaded_controller_B.absxk_l /
      3.3121686421112381E-170;
    cascaded_controller_B.rotm_tmp_b = cascaded_controller_B.b_t_h *
      cascaded_controller_B.b_t_h;
  }

  cascaded_controller_B.absxk_l = std::abs(cascaded_controller_B.eps_idx_1);
  if (cascaded_controller_B.absxk_l > cascaded_controller_B.scale_b) {
    cascaded_controller_B.b_t_h = cascaded_controller_B.scale_b /
      cascaded_controller_B.absxk_l;
    cascaded_controller_B.rotm_tmp_b = cascaded_controller_B.rotm_tmp_b *
      cascaded_controller_B.b_t_h * cascaded_controller_B.b_t_h + 1.0;
    cascaded_controller_B.scale_b = cascaded_controller_B.absxk_l;
  } else {
    cascaded_controller_B.b_t_h = cascaded_controller_B.absxk_l /
      cascaded_controller_B.scale_b;
    cascaded_controller_B.rotm_tmp_b += cascaded_controller_B.b_t_h *
      cascaded_controller_B.b_t_h;
  }

  cascaded_controller_B.absxk_l = std::abs(cascaded_controller_B.eps_idx_2);
  if (cascaded_controller_B.absxk_l > cascaded_controller_B.scale_b) {
    cascaded_controller_B.b_t_h = cascaded_controller_B.scale_b /
      cascaded_controller_B.absxk_l;
    cascaded_controller_B.rotm_tmp_b = cascaded_controller_B.rotm_tmp_b *
      cascaded_controller_B.b_t_h * cascaded_controller_B.b_t_h + 1.0;
    cascaded_controller_B.scale_b = cascaded_controller_B.absxk_l;
  } else {
    cascaded_controller_B.b_t_h = cascaded_controller_B.absxk_l /
      cascaded_controller_B.scale_b;
    cascaded_controller_B.rotm_tmp_b += cascaded_controller_B.b_t_h *
      cascaded_controller_B.b_t_h;
  }

  if (cascaded_controller_B.eta_n > cascaded_controller_B.scale_b) {
    cascaded_controller_B.b_t_h = cascaded_controller_B.scale_b /
      cascaded_controller_B.eta_n;
    cascaded_controller_B.rotm_tmp_b = cascaded_controller_B.rotm_tmp_b *
      cascaded_controller_B.b_t_h * cascaded_controller_B.b_t_h + 1.0;
    cascaded_controller_B.scale_b = cascaded_controller_B.eta_n;
  } else {
    cascaded_controller_B.b_t_h = cascaded_controller_B.eta_n /
      cascaded_controller_B.scale_b;
    cascaded_controller_B.rotm_tmp_b += cascaded_controller_B.b_t_h *
      cascaded_controller_B.b_t_h;
  }

  cascaded_controller_B.rotm_tmp_b = cascaded_controller_B.scale_b * std::sqrt
    (cascaded_controller_B.rotm_tmp_b);
  qib[0] = cascaded_controller_B.eps_idx_0 / cascaded_controller_B.rotm_tmp_b;
  qib[1] = cascaded_controller_B.eps_idx_1 / cascaded_controller_B.rotm_tmp_b;
  qib[2] = cascaded_controller_B.eps_idx_2 / cascaded_controller_B.rotm_tmp_b;
  qib[3] = cascaded_controller_B.eta_n / cascaded_controller_B.rotm_tmp_b;
}

// Function for MATLAB Function: '<S14>/commandExecuter'
void cascaded_controller::cascaded_c_executeDurationTrick(real_T cmd_hold_time,
  const int8_T cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3],
  const real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
  real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
  cmd_status[4], real_T *hold_timer, real_T X_u[13])
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
    cascaded_controller_B.b.f1[c_ret] = rb[c_ret];
    cascaded_controller_B.c.f1[c_ret] = sb[c_ret];
    cascaded_controller_B.d.f1[c_ret] = tb[c_ret];
    cascaded_controller_B.e.f1[c_ret] = ub[c_ret];
    cascaded_controller_B.f.f1[c_ret] = vb[c_ret];
    cascaded_controller_B.g.f1[c_ret] = wb[c_ret];
    cascaded_controller_B.h.f1[c_ret] = xb[c_ret];
    cascaded_controller_B.i.f1[c_ret] = yb[c_ret];
    cascaded_controller_B.j.f1[c_ret] = ac[c_ret];
    cascaded_controller_B.k.f1[c_ret] = bc[c_ret];
    cascaded_controller_B.l.f1[c_ret] = cc[c_ret];
    cascaded_controller_B.m.f1[c_ret] = dc[c_ret];
    cascaded_controller_B.n.f1[c_ret] = ec[c_ret];
    cascaded_controller_B.o.f1[c_ret] = fc[c_ret];
    cascaded_controller_B.p.f1[c_ret] = gc[c_ret];
    cascaded_controller_B.q.f1[c_ret] = hc[c_ret];
    cascaded_controller_B.r.f1[c_ret] = ic[c_ret];
    cascaded_controller_B.s.f1[c_ret] = jc[c_ret];
    cascaded_controller_B.u.f1[c_ret] = kc[c_ret];
    cascaded_controller_B.v.f1[c_ret] = lc[c_ret];
    cascaded_controller_B.w.f1[c_ret] = mc[c_ret];
    cascaded_controller_B.x_d.f1[c_ret] = nc[c_ret];
    cascaded_controller_B.y.f1[c_ret] = oc[c_ret];
    cascaded_controller_B.ab.f1[c_ret] = pc[c_ret];
    cascaded_controller_B.bb.f1[c_ret] = qc[c_ret];
    cascaded_controller_B.cb.f1[c_ret] = rc[c_ret];
  }

  cascaded_controller_B.varargin_1[0] = cascaded_controller_B.b;
  cascaded_controller_B.varargin_1[1] = cascaded_controller_B.c;
  cascaded_controller_B.varargin_1[2] = cascaded_controller_B.d;
  cascaded_controller_B.varargin_1[3] = cascaded_controller_B.e;
  cascaded_controller_B.varargin_1[4] = cascaded_controller_B.f;
  cascaded_controller_B.varargin_1[5] = cascaded_controller_B.g;
  cascaded_controller_B.varargin_1[6] = cascaded_controller_B.h;
  cascaded_controller_B.varargin_1[7] = cascaded_controller_B.i;
  cascaded_controller_B.varargin_1[8] = cascaded_controller_B.j;
  cascaded_controller_B.varargin_1[9] = cascaded_controller_B.k;
  cascaded_controller_B.varargin_1[10] = cascaded_controller_B.l;
  cascaded_controller_B.varargin_1[11] = cascaded_controller_B.m;
  cascaded_controller_B.varargin_1[12] = cascaded_controller_B.n;
  cascaded_controller_B.varargin_2[0] = cascaded_controller_B.o;
  cascaded_controller_B.varargin_2[1] = cascaded_controller_B.p;
  cascaded_controller_B.varargin_2[2] = cascaded_controller_B.q;
  cascaded_controller_B.varargin_2[3] = cascaded_controller_B.r;
  cascaded_controller_B.varargin_2[4] = cascaded_controller_B.s;
  cascaded_controller_B.varargin_2[5] = cascaded_controller_B.u;
  cascaded_controller_B.varargin_2[6] = cascaded_controller_B.v;
  cascaded_controller_B.varargin_2[7] = cascaded_controller_B.w;
  cascaded_controller_B.varargin_2[8] = cascaded_controller_B.x_d;
  cascaded_controller_B.varargin_2[9] = cascaded_controller_B.y;
  cascaded_controller_B.varargin_2[10] = cascaded_controller_B.ab;
  cascaded_controller_B.varargin_2[11] = cascaded_controller_B.bb;
  cascaded_controller_B.varargin_2[12] = cascaded_controller_B.cb;
  for (c_ret = 0; c_ret < 16; c_ret++) {
    cascaded_controller_B.b.f1[c_ret] = n_a[c_ret];
    cascaded_controller_B.c.f1[c_ret] = o_a[c_ret];
    cascaded_controller_B.d.f1[c_ret] = p_a[c_ret];
    cascaded_controller_B.e.f1[c_ret] = q_a[c_ret];
    cascaded_controller_B.f.f1[c_ret] = r_a[c_ret];
    cascaded_controller_B.g.f1[c_ret] = s_a[c_ret];
    cascaded_controller_B.h.f1[c_ret] = t_a[c_ret];
    cascaded_controller_B.i.f1[c_ret] = u_a[c_ret];
    cascaded_controller_B.j.f1[c_ret] = v_a[c_ret];
    cascaded_controller_B.k.f1[c_ret] = w_a[c_ret];
    cascaded_controller_B.l.f1[c_ret] = x_a[c_ret];
    cascaded_controller_B.m.f1[c_ret] = y_a[c_ret];
    cascaded_controller_B.n.f1[c_ret] = ab_a[c_ret];
    cascaded_controller_B.o.f1[c_ret] = sc[c_ret];
  }

  cascaded_controller_B.varargin_3[0] = cascaded_controller_B.b;
  cascaded_controller_B.varargin_3[1] = cascaded_controller_B.c;
  cascaded_controller_B.varargin_3[2] = cascaded_controller_B.d;
  cascaded_controller_B.varargin_3[3] = cascaded_controller_B.e;
  cascaded_controller_B.varargin_3[4] = cascaded_controller_B.f;
  cascaded_controller_B.varargin_3[5] = cascaded_controller_B.g;
  cascaded_controller_B.varargin_3[6] = cascaded_controller_B.h;
  cascaded_controller_B.varargin_3[7] = cascaded_controller_B.i;
  cascaded_controller_B.varargin_3[8] = cascaded_controller_B.j;
  cascaded_controller_B.varargin_3[9] = cascaded_controller_B.k;
  cascaded_controller_B.varargin_3[10] = cascaded_controller_B.l;
  cascaded_controller_B.varargin_3[11] = cascaded_controller_B.m;
  cascaded_controller_B.varargin_3[12] = cascaded_controller_B.n;
  for (c_ret = 0; c_ret < 16; c_ret++) {
    cascaded_controller_B.switch_expression_g[c_ret] = cmd_trick_id[c_ret];
  }

  c_ret = 0;
  do {
    exitg3 = 0;
    if (c_ret < 13) {
      d_ret = std::memcmp(&cascaded_controller_B.varargin_1[c_ret].f1[0],
                          &cascaded_controller_B.switch_expression_g[0], 16);
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
        d_ret = std::memcmp(&cascaded_controller_B.varargin_2[c_ret].f1[0],
                            &cascaded_controller_B.switch_expression_g[0], 16);
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
          d_ret = std::memcmp(&cascaded_controller_B.varargin_3[c_ret].f1[0],
                              &cascaded_controller_B.switch_expression_g[0], 16);
          if (d_ret == 0) {
            c_ret = 2;
            exitg1 = 1;
          } else {
            c_ret++;
          }
        } else {
          c_ret = std::memcmp(&cascaded_controller_B.o.f1[0],
                              &cascaded_controller_B.switch_expression_g[0], 16);
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

    c_ret = std::memcmp(&a[0], &cascaded_controller_B.switch_expression_g[0], 16);
    if (c_ret == 0) {
      c_ret = 0;
    } else {
      c_ret = std::memcmp(&b_a[0], &cascaded_controller_B.switch_expression_g[0],
                          16);
      if (c_ret == 0) {
        c_ret = 1;
      } else {
        c_ret = std::memcmp(&c_a[0], &cascaded_controller_B.switch_expression_g
                            [0], 16);
        if (c_ret == 0) {
          c_ret = 2;
        } else {
          c_ret = std::memcmp(&d_a[0],
                              &cascaded_controller_B.switch_expression_g[0], 16);
          if (c_ret == 0) {
            c_ret = 3;
          } else {
            c_ret = std::memcmp(&e_a[0],
                                &cascaded_controller_B.switch_expression_g[0],
                                16);
            if (c_ret == 0) {
              c_ret = 4;
            } else {
              c_ret = std::memcmp(&f_a[0],
                                  &cascaded_controller_B.switch_expression_g[0],
                                  16);
              if (c_ret == 0) {
                c_ret = 5;
              } else {
                c_ret = std::memcmp(&g_a[0],
                                    &cascaded_controller_B.switch_expression_g[0],
                                    16);
                if (c_ret == 0) {
                  c_ret = 6;
                } else {
                  c_ret = std::memcmp(&h_a[0],
                                      &cascaded_controller_B.switch_expression_g[
                                      0], 16);
                  if (c_ret == 0) {
                    c_ret = 7;
                  } else {
                    c_ret = std::memcmp(&i_a[0],
                                        &cascaded_controller_B.switch_expression_g
                                        [0], 16);
                    if (c_ret == 0) {
                      c_ret = 8;
                    } else {
                      c_ret = std::memcmp(&j_a[0],
                                          &cascaded_controller_B.switch_expression_g
                                          [0], 16);
                      if (c_ret == 0) {
                        c_ret = 9;
                      } else {
                        c_ret = std::memcmp(&k_a[0],
                                            &cascaded_controller_B.switch_expression_g
                                            [0], 16);
                        if (c_ret == 0) {
                          c_ret = 10;
                        } else {
                          c_ret = std::memcmp(&l_a[0],
                                              &cascaded_controller_B.switch_expression_g
                                              [0], 16);
                          if (c_ret == 0) {
                            c_ret = 11;
                          } else {
                            c_ret = std::memcmp(&m_a[0],
                                                &cascaded_controller_B.switch_expression_g
                                                [0], 16);
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 6:
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 7:
      cmd_specific_wp[5] = X_Eul[2] + 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 8:
      cmd_specific_wp[5] = X_Eul[2] - 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 9:
      cmd_specific_wp[5] = X_Eul[0] + 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 10:
      cmd_specific_wp[5] = X_Eul[0] - 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 11:
      cmd_specific_wp[5] = X_Eul[1] + 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 12:
      cmd_specific_wp[5] = X_Eul[1] - 0.52359877559829882;
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     default:
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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
      cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
        cascaded_controller_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = cascaded_controller_B.dv2[0];
      X_u[4] = cascaded_controller_B.dv2[1];
      X_u[5] = cascaded_controller_B.dv2[2];
      X_u[6] = cascaded_controller_B.dv2[3];
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

    cascaded_controller_eulToQuat_m(&cmd_specific_wp[3],
      cascaded_controller_B.dv2);
    X_u[0] = cmd_specific_wp[0];
    X_u[1] = cmd_specific_wp[1];
    X_u[2] = cmd_specific_wp[2];
    X_u[3] = cascaded_controller_B.dv2[0];
    X_u[4] = cascaded_controller_B.dv2[1];
    X_u[5] = cascaded_controller_B.dv2[2];
    X_u[6] = cascaded_controller_B.dv2[3];
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

// Function for MATLAB Function: '<S13>/guidanceLaw'
real_T cascaded_controller::cascaded_controller_norm(const real_T x[2])
{
  real_T absxk;
  real_T t;
  real_T y;
  cascaded_controller_B.scale_ax = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    cascaded_controller_B.scale_ax = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > cascaded_controller_B.scale_ax) {
    t = cascaded_controller_B.scale_ax / absxk;
    y = y * t * t + 1.0;
    cascaded_controller_B.scale_ax = absxk;
  } else {
    t = absxk / cascaded_controller_B.scale_ax;
    y += t * t;
  }

  return cascaded_controller_B.scale_ax * std::sqrt(y);
}

// Function for MATLAB Function: '<S13>/guidanceLaw'
void cascaded_controller::cascaded_controller_quatToEul(const real_T qib[4],
  real_T Eul[3])
{
  int32_T i;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  cascaded_controller_B.a_e = qib[3] * qib[3] * 2.0 - 1.0;
  cascaded_controller_B.b_a_b = 2.0 * qib[3];
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.a_tmp = 2.0 * qib[i];
    cascaded_controller_B.a[3 * i] = cascaded_controller_B.a_tmp * qib[0] +
      cascaded_controller_B.a_e * static_cast<real_T>(b[i]);
    cascaded_controller_B.a[3 * i + 1] = static_cast<real_T>(b[i + 3]) *
      cascaded_controller_B.a_e + cascaded_controller_B.a_tmp * qib[1];
    cascaded_controller_B.a[3 * i + 2] = static_cast<real_T>(b[i + 6]) *
      cascaded_controller_B.a_e + cascaded_controller_B.a_tmp * qib[2];
  }

  cascaded_controller_B.a_e = cascaded_controller_B.b_a_b * 0.0;
  cascaded_controller_B.b_a[0] = cascaded_controller_B.a_e;
  cascaded_controller_B.b_a[1] = cascaded_controller_B.b_a_b * -qib[2];
  cascaded_controller_B.b_a[2] = cascaded_controller_B.b_a_b * qib[1];
  cascaded_controller_B.b_a[3] = cascaded_controller_B.b_a_b * qib[2];
  cascaded_controller_B.b_a[4] = cascaded_controller_B.a_e;
  cascaded_controller_B.b_a[5] = cascaded_controller_B.b_a_b * -qib[0];
  cascaded_controller_B.b_a[6] = cascaded_controller_B.b_a_b * -qib[1];
  cascaded_controller_B.b_a[7] = cascaded_controller_B.b_a_b * qib[0];
  cascaded_controller_B.b_a[8] = cascaded_controller_B.a_e;
  for (i = 0; i < 9; i++) {
    cascaded_controller_B.Cbi_p[i] = cascaded_controller_B.a[i] +
      cascaded_controller_B.b_a[i];
  }

  cascaded_controller_B.b_a_b = std::asin(std::fmax(-1.0, std::fmin(1.0,
    cascaded_controller_B.Cbi_p[6])));
  if (std::abs(std::cos(-cascaded_controller_B.b_a_b)) < 1.0E-6) {
    Eul[0] = 0.0;
    Eul[2] = rt_atan2d_snf(-cascaded_controller_B.Cbi_p[1],
      cascaded_controller_B.Cbi_p[4]);
  } else {
    Eul[0] = rt_atan2d_snf(cascaded_controller_B.Cbi_p[7],
      cascaded_controller_B.Cbi_p[8]);
    Eul[2] = rt_atan2d_snf(cascaded_controller_B.Cbi_p[3],
      cascaded_controller_B.Cbi_p[0]);
  }

  cascaded_controller_wrapToPi(&Eul[0]);
  Eul[1] = -cascaded_controller_B.b_a_b;
  cascaded_controller_wrapToPi(&Eul[1]);
  cascaded_controller_wrapToPi(&Eul[2]);
}

// Function for MATLAB Function: '<S13>/guidanceLaw'
void cascaded_controller::cascaded_controller_eulToRotm(const real_T Eul[3],
  real_T rotm[9])
{
  real_T rotm_tmp;
  real_T rotm_tmp_0;
  cascaded_controller_B.rotm_tmp_p = std::cos(Eul[1]);
  cascaded_controller_B.rotm_tmp_a = std::sin(Eul[1]);
  cascaded_controller_B.rotm_tmp_e = std::cos(Eul[2]);
  rotm_tmp = std::sin(Eul[2]);
  rotm[0] = cascaded_controller_B.rotm_tmp_p * cascaded_controller_B.rotm_tmp_e;
  rotm[3] = cascaded_controller_B.rotm_tmp_p * rotm_tmp;
  rotm[6] = -cascaded_controller_B.rotm_tmp_a;
  rotm_tmp_0 = 0.0 * cascaded_controller_B.rotm_tmp_a;
  rotm[1] = rotm_tmp_0 * cascaded_controller_B.rotm_tmp_e - rotm_tmp;
  rotm[4] = rotm_tmp_0 * rotm_tmp + cascaded_controller_B.rotm_tmp_e;
  rotm[7] = 0.0 * cascaded_controller_B.rotm_tmp_p;
  rotm[2] = cascaded_controller_B.rotm_tmp_a * cascaded_controller_B.rotm_tmp_e
    + 0.0 * rotm_tmp;
  rotm[5] = cascaded_controller_B.rotm_tmp_a * rotm_tmp - 0.0 *
    cascaded_controller_B.rotm_tmp_e;
  rotm[8] = cascaded_controller_B.rotm_tmp_p;
}

// Function for MATLAB Function: '<S13>/guidanceLaw'
void cascaded_controller::cascaded_controller_rotmToQuat(const real_T rotm[9],
  real_T qib[4])
{
  real_T eps_idx_2;
  cascaded_controller_B.eta_m = std::sqrt(((rotm[0] + rotm[4]) + rotm[8]) + 1.0)
    / 2.0;
  if (cascaded_controller_B.eta_m != 0.0) {
    eps_idx_2 = 4.0 * cascaded_controller_B.eta_m;
    cascaded_controller_B.eps_idx_0_c = (rotm[7] - rotm[5]) / eps_idx_2;
    cascaded_controller_B.eps_idx_1_p = (rotm[2] - rotm[6]) / eps_idx_2;
    eps_idx_2 = (rotm[3] - rotm[1]) / eps_idx_2;
  } else {
    int32_T b_k;
    int32_T idx;
    cascaded_controller_B.eps_idx_0_c = (rotm[0] + 1.0) / 2.0;
    cascaded_controller_B.x_n[0] = cascaded_controller_B.eps_idx_0_c;
    cascaded_controller_B.eps_idx_1_p = (rotm[4] + 1.0) / 2.0;
    cascaded_controller_B.x_n[1] = cascaded_controller_B.eps_idx_1_p;
    eps_idx_2 = (rotm[8] + 1.0) / 2.0;
    cascaded_controller_B.x_n[2] = eps_idx_2;
    if (!std::isnan(cascaded_controller_B.eps_idx_0_c)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(cascaded_controller_B.x_n[b_k - 1])) {
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
      cascaded_controller_B.scale_j = cascaded_controller_B.x_n[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        cascaded_controller_B.absxk_h = cascaded_controller_B.x_n[c_k - 1];
        if (cascaded_controller_B.scale_j < cascaded_controller_B.absxk_h) {
          cascaded_controller_B.scale_j = cascaded_controller_B.absxk_h;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      cascaded_controller_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_0_c));
      if (std::isnan(rotm[3])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[3] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[3] > 0.0);
      }

      cascaded_controller_B.eps_idx_1_p = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_p)) * cascaded_controller_B.scale_j;
      if (std::isnan(rotm[6])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[6] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[6] > 0.0);
      }

      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2)) *
        cascaded_controller_B.scale_j;
      break;

     case 2:
      cascaded_controller_B.eps_idx_1_p = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_p));
      if (std::isnan(rotm[3])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[3] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[3] > 0.0);
      }

      cascaded_controller_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_0_c)) * cascaded_controller_B.scale_j;
      if (std::isnan(rotm[7])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[7] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[7] > 0.0);
      }

      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2)) *
        cascaded_controller_B.scale_j;
      break;

     default:
      eps_idx_2 = std::sqrt(std::fmax(0.0, eps_idx_2));
      if (std::isnan(rotm[6])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[6] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[6] > 0.0);
      }

      cascaded_controller_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_0_c)) * cascaded_controller_B.scale_j;
      if (std::isnan(rotm[7])) {
        cascaded_controller_B.scale_j = (rtNaN);
      } else if (rotm[7] < 0.0) {
        cascaded_controller_B.scale_j = -1.0;
      } else {
        cascaded_controller_B.scale_j = (rotm[7] > 0.0);
      }

      cascaded_controller_B.eps_idx_1_p = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_p)) * cascaded_controller_B.scale_j;
      break;
    }
  }

  cascaded_controller_B.scale_j = 3.3121686421112381E-170;
  cascaded_controller_B.absxk_h = std::abs(cascaded_controller_B.eps_idx_0_c);
  if (cascaded_controller_B.absxk_h > 3.3121686421112381E-170) {
    cascaded_controller_B.y_m = 1.0;
    cascaded_controller_B.scale_j = cascaded_controller_B.absxk_h;
  } else {
    cascaded_controller_B.b_t_c = cascaded_controller_B.absxk_h /
      3.3121686421112381E-170;
    cascaded_controller_B.y_m = cascaded_controller_B.b_t_c *
      cascaded_controller_B.b_t_c;
  }

  cascaded_controller_B.absxk_h = std::abs(cascaded_controller_B.eps_idx_1_p);
  if (cascaded_controller_B.absxk_h > cascaded_controller_B.scale_j) {
    cascaded_controller_B.b_t_c = cascaded_controller_B.scale_j /
      cascaded_controller_B.absxk_h;
    cascaded_controller_B.y_m = cascaded_controller_B.y_m *
      cascaded_controller_B.b_t_c * cascaded_controller_B.b_t_c + 1.0;
    cascaded_controller_B.scale_j = cascaded_controller_B.absxk_h;
  } else {
    cascaded_controller_B.b_t_c = cascaded_controller_B.absxk_h /
      cascaded_controller_B.scale_j;
    cascaded_controller_B.y_m += cascaded_controller_B.b_t_c *
      cascaded_controller_B.b_t_c;
  }

  cascaded_controller_B.absxk_h = std::abs(eps_idx_2);
  if (cascaded_controller_B.absxk_h > cascaded_controller_B.scale_j) {
    cascaded_controller_B.b_t_c = cascaded_controller_B.scale_j /
      cascaded_controller_B.absxk_h;
    cascaded_controller_B.y_m = cascaded_controller_B.y_m *
      cascaded_controller_B.b_t_c * cascaded_controller_B.b_t_c + 1.0;
    cascaded_controller_B.scale_j = cascaded_controller_B.absxk_h;
  } else {
    cascaded_controller_B.b_t_c = cascaded_controller_B.absxk_h /
      cascaded_controller_B.scale_j;
    cascaded_controller_B.y_m += cascaded_controller_B.b_t_c *
      cascaded_controller_B.b_t_c;
  }

  if (cascaded_controller_B.eta_m > cascaded_controller_B.scale_j) {
    cascaded_controller_B.b_t_c = cascaded_controller_B.scale_j /
      cascaded_controller_B.eta_m;
    cascaded_controller_B.y_m = cascaded_controller_B.y_m *
      cascaded_controller_B.b_t_c * cascaded_controller_B.b_t_c + 1.0;
    cascaded_controller_B.scale_j = cascaded_controller_B.eta_m;
  } else {
    cascaded_controller_B.b_t_c = cascaded_controller_B.eta_m /
      cascaded_controller_B.scale_j;
    cascaded_controller_B.y_m += cascaded_controller_B.b_t_c *
      cascaded_controller_B.b_t_c;
  }

  cascaded_controller_B.y_m = cascaded_controller_B.scale_j * std::sqrt
    (cascaded_controller_B.y_m);
  qib[0] = cascaded_controller_B.eps_idx_0_c / cascaded_controller_B.y_m;
  qib[1] = cascaded_controller_B.eps_idx_1_p / cascaded_controller_B.y_m;
  qib[2] = eps_idx_2 / cascaded_controller_B.y_m;
  qib[3] = cascaded_controller_B.eta_m / cascaded_controller_B.y_m;
}

// Function for MATLAB Function: '<S13>/quatInjector'
void cascaded_controller::cascaded_controller_eulToQuat(const real_T Eul[3],
  real_T qib[4])
{
  real_T rotm_idx_4_tmp;
  cascaded_controller_B.eta_f = std::cos(Eul[1]);
  cascaded_controller_B.scale_a = std::sin(Eul[1]);
  cascaded_controller_B.b_t_j = std::cos(Eul[2]);
  cascaded_controller_B.rotm_tmp_o = std::sin(Eul[2]);
  cascaded_controller_B.eps_idx_1_o = std::sin(Eul[0]);
  cascaded_controller_B.rotm_tmp_n = std::cos(Eul[0]);
  cascaded_controller_B.rotm_idx_0_m = cascaded_controller_B.eta_f *
    cascaded_controller_B.b_t_j;
  cascaded_controller_B.eps_idx_2_n = cascaded_controller_B.eta_f *
    cascaded_controller_B.rotm_tmp_o;
  rotm_idx_4_tmp = cascaded_controller_B.eps_idx_1_o *
    cascaded_controller_B.scale_a;
  cascaded_controller_B.eps_idx_0_i = rotm_idx_4_tmp *
    cascaded_controller_B.rotm_tmp_o + cascaded_controller_B.rotm_tmp_n *
    cascaded_controller_B.b_t_j;
  cascaded_controller_B.absxk_j = cascaded_controller_B.eps_idx_1_o *
    cascaded_controller_B.eta_f;
  cascaded_controller_B.rotm_idx_8_c = cascaded_controller_B.rotm_tmp_n *
    cascaded_controller_B.eta_f;
  cascaded_controller_B.eta_f = std::sqrt(((cascaded_controller_B.rotm_idx_0_m +
    cascaded_controller_B.eps_idx_0_i) + cascaded_controller_B.rotm_idx_8_c) +
    1.0) / 2.0;
  if (cascaded_controller_B.eta_f != 0.0) {
    cascaded_controller_B.rotm_idx_0_m = cascaded_controller_B.rotm_tmp_n *
      cascaded_controller_B.scale_a;
    cascaded_controller_B.rotm_idx_8_c = 4.0 * cascaded_controller_B.eta_f;
    cascaded_controller_B.eps_idx_0_i = (cascaded_controller_B.absxk_j -
      (cascaded_controller_B.rotm_idx_0_m * cascaded_controller_B.rotm_tmp_o -
       cascaded_controller_B.eps_idx_1_o * cascaded_controller_B.b_t_j)) /
      cascaded_controller_B.rotm_idx_8_c;
    cascaded_controller_B.eps_idx_1_o = ((cascaded_controller_B.rotm_idx_0_m *
      cascaded_controller_B.b_t_j + cascaded_controller_B.eps_idx_1_o *
      cascaded_controller_B.rotm_tmp_o) - (-cascaded_controller_B.scale_a)) /
      cascaded_controller_B.rotm_idx_8_c;
    cascaded_controller_B.eps_idx_2_n = (cascaded_controller_B.eps_idx_2_n -
      (rotm_idx_4_tmp * cascaded_controller_B.b_t_j -
       cascaded_controller_B.rotm_tmp_n * cascaded_controller_B.rotm_tmp_o)) /
      cascaded_controller_B.rotm_idx_8_c;
  } else {
    int32_T b_k;
    int32_T idx;
    cascaded_controller_B.b_t_j = (cascaded_controller_B.rotm_idx_0_m + 1.0) /
      2.0;
    cascaded_controller_B.x_m[0] = cascaded_controller_B.b_t_j;
    cascaded_controller_B.eps_idx_1_o = (cascaded_controller_B.eps_idx_0_i + 1.0)
      / 2.0;
    cascaded_controller_B.x_m[1] = cascaded_controller_B.eps_idx_1_o;
    cascaded_controller_B.rotm_tmp_o = (cascaded_controller_B.rotm_idx_8_c + 1.0)
      / 2.0;
    cascaded_controller_B.x_m[2] = cascaded_controller_B.rotm_tmp_o;
    if (!std::isnan(cascaded_controller_B.b_t_j)) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(cascaded_controller_B.x_m[b_k - 1])) {
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
      cascaded_controller_B.eps_idx_0_i = cascaded_controller_B.x_m[idx - 1];
      b_k = idx;
      for (int32_T c_k{idx + 1}; c_k < 4; c_k++) {
        cascaded_controller_B.rotm_tmp_n = cascaded_controller_B.x_m[c_k - 1];
        if (cascaded_controller_B.eps_idx_0_i < cascaded_controller_B.rotm_tmp_n)
        {
          cascaded_controller_B.eps_idx_0_i = cascaded_controller_B.rotm_tmp_n;
          b_k = c_k;
        }
      }
    }

    switch (b_k) {
     case 1:
      cascaded_controller_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_j));
      if (std::isnan(cascaded_controller_B.eps_idx_2_n)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (cascaded_controller_B.eps_idx_2_n < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (cascaded_controller_B.eps_idx_2_n >
          0.0);
      }

      cascaded_controller_B.eps_idx_1_o = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_o)) * cascaded_controller_B.rotm_tmp_n;
      if (std::isnan(-cascaded_controller_B.scale_a)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (-cascaded_controller_B.scale_a < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (-cascaded_controller_B.scale_a > 0.0);
      }

      cascaded_controller_B.eps_idx_2_n = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_o)) * cascaded_controller_B.rotm_tmp_n;
      break;

     case 2:
      cascaded_controller_B.eps_idx_1_o = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_o));
      if (std::isnan(cascaded_controller_B.eps_idx_2_n)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (cascaded_controller_B.eps_idx_2_n < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (cascaded_controller_B.eps_idx_2_n >
          0.0);
      }

      cascaded_controller_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_j)) * cascaded_controller_B.rotm_tmp_n;
      if (std::isnan(cascaded_controller_B.absxk_j)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (cascaded_controller_B.absxk_j < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (cascaded_controller_B.absxk_j > 0.0);
      }

      cascaded_controller_B.eps_idx_2_n = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_o)) * cascaded_controller_B.rotm_tmp_n;
      break;

     default:
      cascaded_controller_B.eps_idx_2_n = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rotm_tmp_o));
      if (std::isnan(-cascaded_controller_B.scale_a)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (-cascaded_controller_B.scale_a < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (-cascaded_controller_B.scale_a > 0.0);
      }

      cascaded_controller_B.eps_idx_0_i = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.b_t_j)) * cascaded_controller_B.rotm_tmp_n;
      if (std::isnan(cascaded_controller_B.absxk_j)) {
        cascaded_controller_B.rotm_tmp_n = (rtNaN);
      } else if (cascaded_controller_B.absxk_j < 0.0) {
        cascaded_controller_B.rotm_tmp_n = -1.0;
      } else {
        cascaded_controller_B.rotm_tmp_n = (cascaded_controller_B.absxk_j > 0.0);
      }

      cascaded_controller_B.eps_idx_1_o = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.eps_idx_1_o)) * cascaded_controller_B.rotm_tmp_n;
      break;
    }
  }

  cascaded_controller_B.scale_a = 3.3121686421112381E-170;
  cascaded_controller_B.absxk_j = std::abs(cascaded_controller_B.eps_idx_0_i);
  if (cascaded_controller_B.absxk_j > 3.3121686421112381E-170) {
    cascaded_controller_B.rotm_tmp_o = 1.0;
    cascaded_controller_B.scale_a = cascaded_controller_B.absxk_j;
  } else {
    cascaded_controller_B.b_t_j = cascaded_controller_B.absxk_j /
      3.3121686421112381E-170;
    cascaded_controller_B.rotm_tmp_o = cascaded_controller_B.b_t_j *
      cascaded_controller_B.b_t_j;
  }

  cascaded_controller_B.absxk_j = std::abs(cascaded_controller_B.eps_idx_1_o);
  if (cascaded_controller_B.absxk_j > cascaded_controller_B.scale_a) {
    cascaded_controller_B.b_t_j = cascaded_controller_B.scale_a /
      cascaded_controller_B.absxk_j;
    cascaded_controller_B.rotm_tmp_o = cascaded_controller_B.rotm_tmp_o *
      cascaded_controller_B.b_t_j * cascaded_controller_B.b_t_j + 1.0;
    cascaded_controller_B.scale_a = cascaded_controller_B.absxk_j;
  } else {
    cascaded_controller_B.b_t_j = cascaded_controller_B.absxk_j /
      cascaded_controller_B.scale_a;
    cascaded_controller_B.rotm_tmp_o += cascaded_controller_B.b_t_j *
      cascaded_controller_B.b_t_j;
  }

  cascaded_controller_B.absxk_j = std::abs(cascaded_controller_B.eps_idx_2_n);
  if (cascaded_controller_B.absxk_j > cascaded_controller_B.scale_a) {
    cascaded_controller_B.b_t_j = cascaded_controller_B.scale_a /
      cascaded_controller_B.absxk_j;
    cascaded_controller_B.rotm_tmp_o = cascaded_controller_B.rotm_tmp_o *
      cascaded_controller_B.b_t_j * cascaded_controller_B.b_t_j + 1.0;
    cascaded_controller_B.scale_a = cascaded_controller_B.absxk_j;
  } else {
    cascaded_controller_B.b_t_j = cascaded_controller_B.absxk_j /
      cascaded_controller_B.scale_a;
    cascaded_controller_B.rotm_tmp_o += cascaded_controller_B.b_t_j *
      cascaded_controller_B.b_t_j;
  }

  if (cascaded_controller_B.eta_f > cascaded_controller_B.scale_a) {
    cascaded_controller_B.b_t_j = cascaded_controller_B.scale_a /
      cascaded_controller_B.eta_f;
    cascaded_controller_B.rotm_tmp_o = cascaded_controller_B.rotm_tmp_o *
      cascaded_controller_B.b_t_j * cascaded_controller_B.b_t_j + 1.0;
    cascaded_controller_B.scale_a = cascaded_controller_B.eta_f;
  } else {
    cascaded_controller_B.b_t_j = cascaded_controller_B.eta_f /
      cascaded_controller_B.scale_a;
    cascaded_controller_B.rotm_tmp_o += cascaded_controller_B.b_t_j *
      cascaded_controller_B.b_t_j;
  }

  cascaded_controller_B.rotm_tmp_o = cascaded_controller_B.scale_a * std::sqrt
    (cascaded_controller_B.rotm_tmp_o);
  qib[0] = cascaded_controller_B.eps_idx_0_i / cascaded_controller_B.rotm_tmp_o;
  qib[1] = cascaded_controller_B.eps_idx_1_o / cascaded_controller_B.rotm_tmp_o;
  qib[2] = cascaded_controller_B.eps_idx_2_n / cascaded_controller_B.rotm_tmp_o;
  qib[3] = cascaded_controller_B.eta_f / cascaded_controller_B.rotm_tmp_o;
}

// Function for MATLAB Function: '<S13>/rateInjector'
boolean_T cascaded_controller::cascaded_controller_isequal(const char_T
  varargin_1[16])
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

// Function for MATLAB Function: '<S13>/rateInjector'
boolean_T cascaded_controller::cascaded_controller_strcmp(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S13>/rateInjector'
boolean_T cascaded_controller::cascaded_controller_strcmp_a(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S13>/rateInjector'
boolean_T cascaded_controller::cascaded_controller_strcmp_ax(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S19>/forceToPWMCalculator'
void cascaded_controller::cascaded_controller_minimum(const real_T x[6], real_T *
  ex, int32_T *idx)
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

// Function for MATLAB Function: '<S19>/forceToPWMCalculator'
void cascaded_controller::cascaded_controller_minimum_c(const real_T x_data[],
  const int32_T *x_size, real_T *ex, int32_T *idx)
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

void cascaded_controller::cascaded_co_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/command_result" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S201>/SinkBlock'
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
    // Start for MATLABSystem: '<S201>/SinkBlock'
    cascaded_controller_B.b_zeroDelimTopic_d[i] = b_zeroDelimTopic[i];
  }

  Pub_cascaded_controller_108_8.createPublisher
    (&cascaded_controller_B.b_zeroDelimTopic_d[0], qos_profile);
}

void cascaded_controller::cascad_Subscriber_setupImpl_dsx(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[13]{ "/command_msg" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[13];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S196>/SourceBlock'
  cascaded_controller_B.deadline.sec = 0.0;
  cascaded_controller_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 cascaded_controller_B.deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 13; i++) {
    // Start for MATLABSystem: '<S196>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_cascaded_controller_108_4.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void cascaded_controller::cascaded_Subscriber_setupImpl_d(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  cascaded_controller_B.deadline_d.sec = 0.0;
  cascaded_controller_B.deadline_d.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 cascaded_controller_B.deadline_d, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S2>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_cascaded_controller_8.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void cascaded_controller::cascade_Subscriber_setupImpl_ds(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[17]{ "/velocity_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S3>/SourceBlock'
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
    // Start for MATLABSystem: '<S3>/SourceBlock'
    cascaded_controller_B.b_zeroDelimTopic_j[i] = b_zeroDelimTopic[i];
  }

  Sub_cascaded_controller_20.createSubscriber
    (&cascaded_controller_B.b_zeroDelimTopic_j[0], qos_profile);
}

void cascaded_controller::cascaded_c_Subscriber_setupImpl(const
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
    cascaded_controller_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Sub_cascaded_controller_3.createSubscriber
    (&cascaded_controller_B.b_zeroDelimTopic[0], qos_profile);
}

void cascaded_controller::cascaded_Publisher_setupImpl_ds(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S204>/SinkBlock'
  cascaded_controller_B.deadline_l.sec = 0.0;
  cascaded_controller_B.deadline_l.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 cascaded_controller_B.deadline_l, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S204>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_cascaded_controller_38_2.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void cascaded_controller::cascaded__Publisher_setupImpl_d(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S203>/SinkBlock'
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
    // Start for MATLABSystem: '<S203>/SinkBlock'
    cascaded_controller_B.b_zeroDelimTopic_l[i] = b_zeroDelimTopic[i];
  }

  Pub_cascaded_controller_37_150.createPublisher
    (&cascaded_controller_B.b_zeroDelimTopic_l[0], qos_profile);
}

// Model step function
void cascaded_controller::step()
{
  int32_T b_k;
  boolean_T tf;
  static const char_T c_a[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o', 'r',
    'l', 'd', '_', 'w', 'p', '_' };

  static const char_T d_a[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  char_T switch_expression[4];
  static const char_T a[4]{ 'S', 'U', 'C', 'C' };

  static const char_T b_a[4]{ 'F', 'A', 'I', 'L' };

  static const char_T c_a_0[4]{ 'R', 'U', 'N', 'N' };

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

  static const char_T e_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h', 't',
    '_', '_', '_', '_', '_', '_' };

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

  static const char_T e_a_0[16]{ 'f', 'f', '_', 'r', 'i', 'g', 'h', 't', '_',
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

  int32_T c_a_tmp;
  int32_T i;
  int8_T rtb_cmd_status[4];
  int8_T rtb_Switch1_0;
  int8_T rtb_Switch1_idx_0;
  int8_T rtb_Switch1_idx_1;
  int8_T tmp;
  int8_T tmp_0;
  uint8_T integrator_reset;
  boolean_T rtb_RelationalOperator_f_0;
  boolean_T rtb_RelationalOperator_g_idx_0;
  boolean_T rtb_RelationalOperator_g_idx_1;
  boolean_T rtb_RelationalOperator_g_idx_2;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const char_T c[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  static const char_T d[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  static const uint8_T b_0[16]{ 112U, 108U, 97U, 99U, 101U, 104U, 111U, 108U,
    100U, 101U, 114U, 95U, 95U, 95U, 95U, 95U };

  int32_T force_column_size_idx_0;
  boolean_T exitg1;

  // DigitalClock: '<S14>/Digital Clock'
  cascaded_controller_B.DigitalClock = (((&cascaded_controller_M)
    ->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S196>/SourceBlock'
  b_varargout_1 = Sub_cascaded_controller_108_4.getLatestMessage
    (&cascaded_controller_B.rtb_SourceBlock_o2_p_k);

  // Outputs for Enabled SubSystem: '<S196>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S200>/Enable'

  // Start for MATLABSystem: '<S196>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S200>/In1'
    cascaded_controller_B.In1_n = cascaded_controller_B.rtb_SourceBlock_o2_p_k;
  }

  // End of Outputs for SubSystem: '<S196>/Enabled Subsystem'

  // MATLAB Function: '<S5>/cmdMsgToCmdBus'
  for (i = 0; i < 16; i++) {
    integrator_reset = cascaded_controller_B.In1_n.command_id[i];
    if (integrator_reset > 127) {
      integrator_reset = 127U;
    }

    cascaded_controller_B.cmd.cmd_id[i] = static_cast<int8_T>(integrator_reset);
    integrator_reset = cascaded_controller_B.In1_n.trick[i];
    if (integrator_reset > 127) {
      integrator_reset = 127U;
    }

    cascaded_controller_B.cmd.trick_id[i] = static_cast<int8_T>(integrator_reset);
  }

  // MATLABSystem: '<S2>/SourceBlock'
  b_varargout_1_0 = Sub_cascaded_controller_8.getLatestMessage
    (&cascaded_controller_B.rtb_SourceBlock_o2_k_c);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S11>/Enable'

  // Start for MATLABSystem: '<S2>/SourceBlock'
  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S11>/In1'
    cascaded_controller_B.In1_k = cascaded_controller_B.rtb_SourceBlock_o2_k_c;
  }

  // End of Start for MATLABSystem: '<S2>/SourceBlock'
  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1_0 = Sub_cascaded_controller_20.getLatestMessage
    (&cascaded_controller_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S12>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (b_varargout_1_0) {
    // SignalConversion generated from: '<S12>/In1'
    cascaded_controller_B.In1 = cascaded_controller_B.rtb_SourceBlock_o2_m;
  }

  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // MATLABSystem: '<S1>/SourceBlock'
  b_varargout_1_1 = Sub_cascaded_controller_3.getLatestMessage
    (&cascaded_controller_B.rtb_SourceBlock_o2_g_c);

  // Outputs for Enabled SubSystem: '<S1>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S10>/Enable'

  // Start for MATLABSystem: '<S1>/SourceBlock'
  if (b_varargout_1_1) {
    // SignalConversion generated from: '<S10>/In1'
    cascaded_controller_B.In1_a = cascaded_controller_B.rtb_SourceBlock_o2_g_c;
  }

  // End of Outputs for SubSystem: '<S1>/Enabled Subsystem'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  cascaded_controller_B.eul_error[0] = cascaded_controller_B.In1_a.angle.x *
    0.017453292519943295;
  cascaded_controller_B.eul_error[1] = cascaded_controller_B.In1_a.angle.y *
    0.017453292519943295;
  cascaded_controller_B.eul_error[2] = cascaded_controller_B.In1_a.angle.z *
    0.017453292519943295;

  // MATLAB Function: '<S9>/eulToQuat'
  cascaded_controller_B.eta = std::cos(cascaded_controller_B.eul_error[1]);
  cascaded_controller_B.rotm_tmp = std::sin(cascaded_controller_B.eul_error[1]);
  cascaded_controller_B.rtb_Integrator_o_idx_1 = std::cos
    (cascaded_controller_B.eul_error[2]);
  cascaded_controller_B.rtb_Integrator_o_idx_2 = std::sin
    (cascaded_controller_B.eul_error[2]);
  cascaded_controller_B.b_t = std::sin(cascaded_controller_B.eul_error[0]);
  cascaded_controller_B.rtb_delta_qe_idx_2 = std::cos
    (cascaded_controller_B.eul_error[0]);
  cascaded_controller_B.rotm[0] = cascaded_controller_B.eta *
    cascaded_controller_B.rtb_Integrator_o_idx_1;
  cascaded_controller_B.rotm[3] = cascaded_controller_B.eta *
    cascaded_controller_B.rtb_Integrator_o_idx_2;
  cascaded_controller_B.scale = cascaded_controller_B.b_t *
    cascaded_controller_B.rotm_tmp;
  cascaded_controller_B.rotm[4] = cascaded_controller_B.scale *
    cascaded_controller_B.rtb_Integrator_o_idx_2 +
    cascaded_controller_B.rtb_delta_qe_idx_2 *
    cascaded_controller_B.rtb_Integrator_o_idx_1;
  cascaded_controller_B.rotm[7] = cascaded_controller_B.b_t *
    cascaded_controller_B.eta;
  cascaded_controller_B.rotm[8] = cascaded_controller_B.rtb_delta_qe_idx_2 *
    cascaded_controller_B.eta;
  cascaded_controller_B.eta = std::sqrt(((cascaded_controller_B.rotm[0] +
    cascaded_controller_B.rotm[4]) + cascaded_controller_B.rotm[8]) + 1.0) / 2.0;
  if (cascaded_controller_B.eta != 0.0) {
    cascaded_controller_B.absxk = cascaded_controller_B.rtb_delta_qe_idx_2 *
      cascaded_controller_B.rotm_tmp;
    cascaded_controller_B.b_scale = 4.0 * cascaded_controller_B.eta;
    cascaded_controller_B.eps[0] = (cascaded_controller_B.rotm[7] -
      (cascaded_controller_B.absxk *
       cascaded_controller_B.rtb_Integrator_o_idx_2 - cascaded_controller_B.b_t *
       cascaded_controller_B.rtb_Integrator_o_idx_1)) /
      cascaded_controller_B.b_scale;
    cascaded_controller_B.eps[1] = ((cascaded_controller_B.absxk *
      cascaded_controller_B.rtb_Integrator_o_idx_1 + cascaded_controller_B.b_t *
      cascaded_controller_B.rtb_Integrator_o_idx_2) -
      (-cascaded_controller_B.rotm_tmp)) / cascaded_controller_B.b_scale;
    cascaded_controller_B.eps[2] = (cascaded_controller_B.rotm[3] -
      (cascaded_controller_B.scale *
       cascaded_controller_B.rtb_Integrator_o_idx_1 -
       cascaded_controller_B.rtb_delta_qe_idx_2 *
       cascaded_controller_B.rtb_Integrator_o_idx_2)) /
      cascaded_controller_B.b_scale;
  } else {
    cascaded_controller_B.rtb_Integrator_o_idx_1 = (cascaded_controller_B.rotm[0]
      + 1.0) / 2.0;
    cascaded_controller_B.eul_error[0] =
      cascaded_controller_B.rtb_Integrator_o_idx_1;
    cascaded_controller_B.rtb_Integrator_o_idx_2 = (cascaded_controller_B.rotm[4]
      + 1.0) / 2.0;
    cascaded_controller_B.eul_error[1] =
      cascaded_controller_B.rtb_Integrator_o_idx_2;
    cascaded_controller_B.rtb_delta_qe_idx_2 = (cascaded_controller_B.rotm[8] +
      1.0) / 2.0;
    cascaded_controller_B.eul_error[2] =
      cascaded_controller_B.rtb_delta_qe_idx_2;
    if (!std::isnan(cascaded_controller_B.rtb_Integrator_o_idx_1)) {
      i = 1;
    } else {
      i = 0;
      b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (b_k < 4)) {
        if (!std::isnan(cascaded_controller_B.eul_error[b_k - 1])) {
          i = b_k;
          exitg1 = true;
        } else {
          b_k++;
        }
      }
    }

    if (i == 0) {
      cascaded_controller_B.iindx = 1;
    } else {
      cascaded_controller_B.b_t = cascaded_controller_B.eul_error[i - 1];
      cascaded_controller_B.iindx = i;
      for (b_k = i + 1; b_k < 4; b_k++) {
        cascaded_controller_B.psi = cascaded_controller_B.eul_error[b_k - 1];
        if (cascaded_controller_B.b_t < cascaded_controller_B.psi) {
          cascaded_controller_B.b_t = cascaded_controller_B.psi;
          cascaded_controller_B.iindx = b_k;
        }
      }
    }

    switch (cascaded_controller_B.iindx) {
     case 1:
      cascaded_controller_B.eps[0] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_1));
      if (std::isnan(cascaded_controller_B.rotm[3])) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (cascaded_controller_B.rotm[3] < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (cascaded_controller_B.rotm[3] > 0.0);
      }

      cascaded_controller_B.eps[1] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_2)) *
        cascaded_controller_B.b_t;
      if (std::isnan(-cascaded_controller_B.rotm_tmp)) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (-cascaded_controller_B.rotm_tmp < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (-cascaded_controller_B.rotm_tmp > 0.0);
      }

      cascaded_controller_B.eps[2] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_delta_qe_idx_2)) * cascaded_controller_B.b_t;
      break;

     case 2:
      cascaded_controller_B.eps[1] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_2));
      if (std::isnan(cascaded_controller_B.rotm[3])) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (cascaded_controller_B.rotm[3] < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (cascaded_controller_B.rotm[3] > 0.0);
      }

      cascaded_controller_B.eps[0] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_1)) *
        cascaded_controller_B.b_t;
      if (std::isnan(cascaded_controller_B.rotm[7])) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (cascaded_controller_B.rotm[7] < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (cascaded_controller_B.rotm[7] > 0.0);
      }

      cascaded_controller_B.eps[2] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_delta_qe_idx_2)) * cascaded_controller_B.b_t;
      break;

     default:
      cascaded_controller_B.eps[2] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_delta_qe_idx_2));
      if (std::isnan(-cascaded_controller_B.rotm_tmp)) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (-cascaded_controller_B.rotm_tmp < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (-cascaded_controller_B.rotm_tmp > 0.0);
      }

      cascaded_controller_B.eps[0] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_1)) *
        cascaded_controller_B.b_t;
      if (std::isnan(cascaded_controller_B.rotm[7])) {
        cascaded_controller_B.b_t = (rtNaN);
      } else if (cascaded_controller_B.rotm[7] < 0.0) {
        cascaded_controller_B.b_t = -1.0;
      } else {
        cascaded_controller_B.b_t = (cascaded_controller_B.rotm[7] > 0.0);
      }

      cascaded_controller_B.eps[1] = std::sqrt(std::fmax(0.0,
        cascaded_controller_B.rtb_Integrator_o_idx_2)) *
        cascaded_controller_B.b_t;
      break;
    }
  }

  cascaded_controller_B.scale = 3.3121686421112381E-170;
  cascaded_controller_B.absxk = std::abs(cascaded_controller_B.eps[0]);
  if (cascaded_controller_B.absxk > 3.3121686421112381E-170) {
    cascaded_controller_B.rtb_delta_qe_idx_2 = 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      3.3121686421112381E-170;
    cascaded_controller_B.rtb_delta_qe_idx_2 = cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.absxk = std::abs(cascaded_controller_B.eps[1]);
  if (cascaded_controller_B.absxk > cascaded_controller_B.scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.scale /
      cascaded_controller_B.absxk;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      cascaded_controller_B.scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.absxk = std::abs(cascaded_controller_B.eps[2]);
  if (cascaded_controller_B.absxk > cascaded_controller_B.scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.scale /
      cascaded_controller_B.absxk;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      cascaded_controller_B.scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  if (cascaded_controller_B.eta > cascaded_controller_B.scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.scale /
      cascaded_controller_B.eta;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.eta;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.eta /
      cascaded_controller_B.scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.rtb_delta_qe_idx_2 = cascaded_controller_B.scale * std::
    sqrt(cascaded_controller_B.rtb_delta_qe_idx_2);

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  cascaded_controller_B.dv3[0] =
    cascaded_controller_B.In1_k.imu_fusion.angular_velocity.x;
  cascaded_controller_B.dv3[1] =
    cascaded_controller_B.In1_k.imu_fusion.angular_velocity.y;
  cascaded_controller_B.dv3[2] =
    cascaded_controller_B.In1_k.imu_fusion.angular_velocity.z;

  // Product: '<S9>/Matrix Multiply2' incorporates:
  //   Constant: '<S9>/Constant1'

  cascaded_controller_B.rotm_tmp = 0.0;
  cascaded_controller_B.rtb_Integrator_o_idx_1 = 0.0;
  cascaded_controller_B.rtb_Integrator_o_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t = cascaded_controller_B.dv3[i];
    cascaded_controller_B.rotm_tmp +=
      cascaded_controller_ConstP.Constant1_Value_l[3 * i] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_Integrator_o_idx_1 +=
      cascaded_controller_ConstP.Constant1_Value_l[3 * i + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_Integrator_o_idx_2 +=
      cascaded_controller_ConstP.Constant1_Value_l[3 * i + 2] *
      cascaded_controller_B.b_t;
  }

  // MATLAB Function: '<S9>/discreteTimeQuatPropagation' incorporates:
  //   MATLAB Function: '<S9>/eulToQuat'
  //   MATLABSystem: '<S1>/SourceBlock'
  //   Product: '<S9>/Matrix Multiply2'
  //
  if (!cascaded_controller_DW.qk_not_empty) {
    cascaded_controller_DW.qk[0] = 0.0;
    cascaded_controller_DW.qk[1] = 0.0;
    cascaded_controller_DW.qk[2] = 0.0;
    cascaded_controller_DW.qk[3] = 1.0;
    cascaded_controller_DW.qk_not_empty = true;
  }

  if (b_varargout_1_1) {
    cascaded_controller_DW.qk[0] = cascaded_controller_B.eps[0] /
      cascaded_controller_B.rtb_delta_qe_idx_2;
    cascaded_controller_DW.qk[1] = cascaded_controller_B.eps[1] /
      cascaded_controller_B.rtb_delta_qe_idx_2;
    cascaded_controller_DW.qk[2] = cascaded_controller_B.eps[2] /
      cascaded_controller_B.rtb_delta_qe_idx_2;
    cascaded_controller_DW.qk[3] = cascaded_controller_B.eta /
      cascaded_controller_B.rtb_delta_qe_idx_2;
  }

  cascaded_controller_B.scale = 3.3121686421112381E-170;
  cascaded_controller_B.absxk = std::abs(cascaded_controller_B.rotm_tmp);
  if (cascaded_controller_B.absxk > 3.3121686421112381E-170) {
    cascaded_controller_B.eta = 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      3.3121686421112381E-170;
    cascaded_controller_B.eta = cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.absxk = std::abs
    (cascaded_controller_B.rtb_Integrator_o_idx_1);
  if (cascaded_controller_B.absxk > cascaded_controller_B.scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.scale /
      cascaded_controller_B.absxk;
    cascaded_controller_B.eta = cascaded_controller_B.eta *
      cascaded_controller_B.b_t * cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      cascaded_controller_B.scale;
    cascaded_controller_B.eta += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.absxk = std::abs
    (cascaded_controller_B.rtb_Integrator_o_idx_2);
  if (cascaded_controller_B.absxk > cascaded_controller_B.scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.scale /
      cascaded_controller_B.absxk;
    cascaded_controller_B.eta = cascaded_controller_B.eta *
      cascaded_controller_B.b_t * cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.scale = cascaded_controller_B.absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.absxk /
      cascaded_controller_B.scale;
    cascaded_controller_B.eta += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.eta = cascaded_controller_B.scale * std::sqrt
    (cascaded_controller_B.eta);
  if (cascaded_controller_B.eta > 1.0E-10) {
    cascaded_controller_B.b_t = std::sin(0.5 * cascaded_controller_B.eta * 0.01)
      / cascaded_controller_B.eta;
    cascaded_controller_B.eps[0] = cascaded_controller_B.b_t *
      cascaded_controller_B.rotm_tmp;
    cascaded_controller_B.eps[1] = cascaded_controller_B.b_t *
      cascaded_controller_B.rtb_Integrator_o_idx_1;
    cascaded_controller_B.eps[2] = cascaded_controller_B.b_t *
      cascaded_controller_B.rtb_Integrator_o_idx_2;
  } else {
    cascaded_controller_B.eps[0] = 0.005 * cascaded_controller_B.rotm_tmp;
    cascaded_controller_B.eps[1] = 0.005 *
      cascaded_controller_B.rtb_Integrator_o_idx_1;
    cascaded_controller_B.eps[2] = 0.005 *
      cascaded_controller_B.rtb_Integrator_o_idx_2;
  }

  cascaded_controller_B.b_t = std::cos(0.5 * cascaded_controller_B.eta * 0.01);
  for (i = 0; i < 9; i++) {
    // MATLAB Function: '<S9>/quatToRotm' incorporates:
    //   MATLAB Function: '<S9>/derivedStateEstimates'

    cascaded_controller_B.rotm[i] = b[i];
  }

  cascaded_controller_B.rtb_Cbi_tmp_tmp[0] = 0.0;
  cascaded_controller_B.rtb_Cbi_tmp_tmp[3] = -cascaded_controller_B.eps[2];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[6] = cascaded_controller_B.eps[1];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[1] = cascaded_controller_B.eps[2];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[4] = 0.0;
  cascaded_controller_B.rtb_Cbi_tmp_tmp[7] = -cascaded_controller_B.eps[0];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[2] = -cascaded_controller_B.eps[1];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[5] = cascaded_controller_B.eps[0];
  cascaded_controller_B.rtb_Cbi_tmp_tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    c_a_tmp = i << 2;
    cascaded_controller_B.c_a[c_a_tmp] = cascaded_controller_B.rotm[3 * i] *
      cascaded_controller_B.b_t - cascaded_controller_B.rtb_Cbi_tmp_tmp[3 * i];
    b_k = 3 * i + 1;
    cascaded_controller_B.c_a[c_a_tmp + 1] = cascaded_controller_B.rotm[b_k] *
      cascaded_controller_B.b_t - cascaded_controller_B.rtb_Cbi_tmp_tmp[b_k];
    b_k = 3 * i + 2;
    cascaded_controller_B.c_a[c_a_tmp + 2] = cascaded_controller_B.rotm[b_k] *
      cascaded_controller_B.b_t - cascaded_controller_B.rtb_Cbi_tmp_tmp[b_k];
    cascaded_controller_B.phi = cascaded_controller_B.eps[i];
    cascaded_controller_B.c_a[i + 12] = cascaded_controller_B.phi;
    cascaded_controller_B.c_a[c_a_tmp + 3] = -cascaded_controller_B.phi;
  }

  cascaded_controller_B.c_a[15] = cascaded_controller_B.b_t;
  cascaded_controller_B.rtb_delta_qe_idx_2 = 0.0;
  cascaded_controller_B.eta = 0.0;
  cascaded_controller_B.scale = 0.0;
  cascaded_controller_B.absxk = 0.0;
  for (i = 0; i < 4; i++) {
    cascaded_controller_B.b_t = cascaded_controller_DW.qk[i];
    c_a_tmp = i << 2;
    cascaded_controller_B.rtb_delta_qe_idx_2 +=
      cascaded_controller_B.c_a[c_a_tmp] * cascaded_controller_B.b_t;
    cascaded_controller_B.eta += cascaded_controller_B.c_a[c_a_tmp + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.scale += cascaded_controller_B.c_a[c_a_tmp + 2] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.absxk += cascaded_controller_B.c_a[c_a_tmp + 3] *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.b_scale = 3.3121686421112381E-170;
  cascaded_controller_DW.qk[0] = cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_B.b_absxk = std::abs(cascaded_controller_DW.qk[0]);
  if (cascaded_controller_B.b_absxk > 3.3121686421112381E-170) {
    cascaded_controller_B.rtb_delta_qe_idx_2 = 1.0;
    cascaded_controller_B.b_scale = cascaded_controller_B.b_absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.b_absxk /
      3.3121686421112381E-170;
    cascaded_controller_B.rtb_delta_qe_idx_2 = cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_DW.qk[1] = cascaded_controller_B.eta;
  cascaded_controller_B.b_absxk = std::abs(cascaded_controller_DW.qk[1]);
  if (cascaded_controller_B.b_absxk > cascaded_controller_B.b_scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.b_scale /
      cascaded_controller_B.b_absxk;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.b_scale = cascaded_controller_B.b_absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.b_absxk /
      cascaded_controller_B.b_scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_DW.qk[2] = cascaded_controller_B.scale;
  cascaded_controller_B.b_absxk = std::abs(cascaded_controller_DW.qk[2]);
  if (cascaded_controller_B.b_absxk > cascaded_controller_B.b_scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.b_scale /
      cascaded_controller_B.b_absxk;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.b_scale = cascaded_controller_B.b_absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.b_absxk /
      cascaded_controller_B.b_scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_DW.qk[3] = cascaded_controller_B.absxk;
  cascaded_controller_B.b_absxk = std::abs(cascaded_controller_DW.qk[3]);
  if (cascaded_controller_B.b_absxk > cascaded_controller_B.b_scale) {
    cascaded_controller_B.b_t = cascaded_controller_B.b_scale /
      cascaded_controller_B.b_absxk;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      cascaded_controller_B.rtb_delta_qe_idx_2 * cascaded_controller_B.b_t *
      cascaded_controller_B.b_t + 1.0;
    cascaded_controller_B.b_scale = cascaded_controller_B.b_absxk;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.b_absxk /
      cascaded_controller_B.b_scale;
    cascaded_controller_B.rtb_delta_qe_idx_2 += cascaded_controller_B.b_t *
      cascaded_controller_B.b_t;
  }

  cascaded_controller_B.rtb_delta_qe_idx_2 = cascaded_controller_B.b_scale * std::
    sqrt(cascaded_controller_B.rtb_delta_qe_idx_2);
  cascaded_controller_B.qe_matlab_idx_3 = cascaded_controller_DW.qk[0] /
    cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_DW.qk[0] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.X_est.qib[0] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.qe_matlab_idx_3 = cascaded_controller_DW.qk[1] /
    cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_DW.qk[1] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.X_est.qib[1] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.qe_matlab_idx_3 = cascaded_controller_DW.qk[2] /
    cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_DW.qk[2] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.X_est.qib[2] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.qe_matlab_idx_3 = cascaded_controller_DW.qk[3] /
    cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_DW.qk[3] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.X_est.qib[3] = cascaded_controller_B.qe_matlab_idx_3;

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/discreteTimeQuatPropagation'
  //   Math: '<S9>/Transpose'

  cascaded_controller_B.a_o = cascaded_controller_B.qe_matlab_idx_3 *
    cascaded_controller_B.qe_matlab_idx_3 * 2.0 - 1.0;
  cascaded_controller_B.b_t = 2.0 * cascaded_controller_B.qe_matlab_idx_3;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  for (i = 0; i < 3; i++) {
    cascaded_controller_B.rtb_Cbi_tmp[3 * i] = 2.0 *
      cascaded_controller_B.X_est.qib[0] * cascaded_controller_B.X_est.qib[i];

    // Math: '<S9>/Transpose' incorporates:
    //   MATLAB Function: '<S14>/commandExecuter'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.rtb_Cbi_tmp_tmp[3 * i] = cascaded_controller_B.rotm[i];
    c_a_tmp = 3 * i + 1;
    cascaded_controller_B.rtb_Cbi_tmp[c_a_tmp] = 2.0 *
      cascaded_controller_B.X_est.qib[1] * cascaded_controller_B.X_est.qib[i];

    // Math: '<S9>/Transpose' incorporates:
    //   MATLAB Function: '<S14>/commandExecuter'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] =
      cascaded_controller_B.rotm[i + 3];
    c_a_tmp = 3 * i + 2;
    cascaded_controller_B.rtb_Cbi_tmp[c_a_tmp] = 2.0 *
      cascaded_controller_B.X_est.qib[2] * cascaded_controller_B.X_est.qib[i];

    // Math: '<S9>/Transpose' incorporates:
    //   MATLAB Function: '<S14>/commandExecuter'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] =
      cascaded_controller_B.rotm[i + 6];
  }

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.Cbi[3 * i] = cascaded_controller_B.rtb_Cbi_tmp_tmp[3 *
      i] * cascaded_controller_B.a_o + cascaded_controller_B.rtb_Cbi_tmp[i];

    // Math: '<S9>/Transpose'
    c_a_tmp = 3 * i + 1;
    cascaded_controller_B.Cbi[c_a_tmp] =
      cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] * cascaded_controller_B.a_o
      + cascaded_controller_B.rtb_Cbi_tmp[i + 3];

    // Math: '<S9>/Transpose'
    c_a_tmp = 3 * i + 2;
    cascaded_controller_B.Cbi[c_a_tmp] =
      cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] * cascaded_controller_B.a_o
      + cascaded_controller_B.rtb_Cbi_tmp[i + 6];
  }

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  cascaded_controller_B.eta = cascaded_controller_B.b_t * 0.0;

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[0] = cascaded_controller_B.eta;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.rtb_delta_qe_idx_2 = cascaded_controller_B.b_t *
    -cascaded_controller_B.X_est.qib[2];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[1] =
    cascaded_controller_B.rtb_delta_qe_idx_2;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.scale = cascaded_controller_B.b_t *
    cascaded_controller_B.X_est.qib[1];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[2] = cascaded_controller_B.scale;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.absxk = cascaded_controller_B.b_t *
    cascaded_controller_B.X_est.qib[2];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[3] = cascaded_controller_B.absxk;
  cascaded_controller_B.rtb_Cbi_tmp_b[4] = cascaded_controller_B.eta;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.b_scale = cascaded_controller_B.b_t *
    -cascaded_controller_B.X_est.qib[0];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[5] = cascaded_controller_B.b_scale;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.b_absxk = cascaded_controller_B.b_t *
    -cascaded_controller_B.X_est.qib[1];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[6] = cascaded_controller_B.b_absxk;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S9>/quatToRotm' incorporates:
  //   MATLAB Function: '<S13>/guidanceLaw'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2 =
    cascaded_controller_B.b_t * cascaded_controller_B.X_est.qib[0];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // Math: '<S9>/Transpose' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/quatToRotm'

  cascaded_controller_B.rtb_Cbi_tmp_b[7] =
    cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2;
  cascaded_controller_B.rtb_Cbi_tmp_b[8] = cascaded_controller_B.eta;
  for (i = 0; i < 9; i++) {
    cascaded_controller_B.Cbi_c[i] = cascaded_controller_B.Cbi[i] +
      cascaded_controller_B.rtb_Cbi_tmp_b[i];
  }

  // MATLAB Function: '<S9>/dvl_reset' incorporates:
  //   DataStoreRead: '<S9>/Data Store Read3'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'

  if (cascaded_controller_DW.prior_flag &&
      (!cascaded_controller_DW.start_new_mission_flag)) {
    cascaded_controller_DW.offset[0] = cascaded_controller_B.In1_a.position.x;
    cascaded_controller_DW.offset[1] = cascaded_controller_B.In1_a.position.y;
    cascaded_controller_DW.offset[2] = cascaded_controller_B.In1_a.position.z;
  }

  cascaded_controller_DW.prior_flag =
    cascaded_controller_DW.start_new_mission_flag;
  cascaded_controller_B.rtb_dvl_pos_g[0] =
    cascaded_controller_B.In1_a.position.x - cascaded_controller_DW.offset[0];
  cascaded_controller_B.rtb_dvl_pos_g[1] =
    cascaded_controller_B.In1_a.position.y - cascaded_controller_DW.offset[1];
  cascaded_controller_B.rtb_dvl_pos_g[2] =
    cascaded_controller_B.In1_a.position.z - cascaded_controller_DW.offset[2];

  // End of MATLAB Function: '<S9>/dvl_reset'

  // Product: '<S9>/Matrix Multiply3' incorporates:
  //   Math: '<S9>/Transpose'

  cascaded_controller_B.phi = 0.0;
  cascaded_controller_B.psi = 0.0;
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t = cascaded_controller_B.rtb_dvl_pos_g[i];
    cascaded_controller_B.phi += cascaded_controller_B.Cbi_c[3 * i] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.psi += cascaded_controller_B.Cbi_c[3 * i + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 +=
      cascaded_controller_B.Cbi_c[3 * i + 2] * cascaded_controller_B.b_t;
  }

  // DiscreteIntegrator: '<S9>/Position Integrator' incorporates:
  //   MATLABSystem: '<S1>/SourceBlock'
  //   Product: '<S9>/Matrix Multiply3'
  //
  if (cascaded_controller_DW.PositionIntegrator_IC_LOADING != 0) {
    cascaded_controller_DW.PositionIntegrator_DSTATE[0] =
      cascaded_controller_B.phi;
    cascaded_controller_DW.PositionIntegrator_DSTATE[1] =
      cascaded_controller_B.psi;
    cascaded_controller_DW.PositionIntegrator_DSTATE[2] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  }

  if (b_varargout_1_1 && (cascaded_controller_DW.PositionIntegrator_PrevResetSta
       <= 0)) {
    cascaded_controller_DW.PositionIntegrator_DSTATE[0] =
      cascaded_controller_B.phi;
    cascaded_controller_DW.PositionIntegrator_DSTATE[1] =
      cascaded_controller_B.psi;
    cascaded_controller_DW.PositionIntegrator_DSTATE[2] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  }

  // DiscreteIntegrator: '<S9>/Velocity Integrator' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLABSystem: '<S3>/SourceBlock'
  //
  if (cascaded_controller_DW.VelocityIntegrator_IC_LOADING != 0) {
    cascaded_controller_DW.VelocityIntegrator_DSTATE[0] =
      cascaded_controller_B.In1.velocity_data.x;
    cascaded_controller_DW.VelocityIntegrator_DSTATE[1] =
      cascaded_controller_B.In1.velocity_data.y;
    cascaded_controller_DW.VelocityIntegrator_DSTATE[2] =
      cascaded_controller_B.In1.velocity_data.z;
  }

  if (b_varargout_1_0 && (cascaded_controller_DW.VelocityIntegrator_PrevResetSta
       <= 0)) {
    cascaded_controller_DW.VelocityIntegrator_DSTATE[0] =
      cascaded_controller_B.In1.velocity_data.x;
    cascaded_controller_DW.VelocityIntegrator_DSTATE[1] =
      cascaded_controller_B.In1.velocity_data.y;
    cascaded_controller_DW.VelocityIntegrator_DSTATE[2] =
      cascaded_controller_B.In1.velocity_data.z;
  }

  // Product: '<S9>/Matrix Multiply' incorporates:
  //   Constant: '<S9>/Constant'
  //   Math: '<S9>/Transpose'

  cascaded_controller_B.phi = 0.0;
  cascaded_controller_B.psi = 0.0;
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t = cascaded_controller_ConstP.Constant_Value_m[i];
    cascaded_controller_B.phi += cascaded_controller_B.Cbi_c[3 * i] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.psi += cascaded_controller_B.Cbi_c[3 * i + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 +=
      cascaded_controller_B.Cbi_c[3 * i + 2] * cascaded_controller_B.b_t;
  }

  cascaded_controller_B.eul_error[2] =
    cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  cascaded_controller_B.eul_error[1] = cascaded_controller_B.psi;
  cascaded_controller_B.eul_error[0] = cascaded_controller_B.phi;

  // End of Product: '<S9>/Matrix Multiply'

  // Sum: '<S9>/Sum' incorporates:
  //   Constant: '<S9>/Constant1'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   Product: '<S9>/Matrix Multiply1'

  for (i = 0; i < 3; i++) {
    cascaded_controller_B.rtb_dvl_pos_g[i] =
      ((cascaded_controller_ConstP.Constant1_Value_l[i + 3] *
        cascaded_controller_B.In1_k.imu_fusion.linear_acceleration.y +
        cascaded_controller_ConstP.Constant1_Value_l[i] *
        cascaded_controller_B.In1_k.imu_fusion.linear_acceleration.x) +
       cascaded_controller_ConstP.Constant1_Value_l[i + 6] *
       cascaded_controller_B.In1_k.imu_fusion.linear_acceleration.z) -
      cascaded_controller_B.eul_error[i];
  }

  // End of Sum: '<S9>/Sum'

  // MATLAB Function: '<S9>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S9>/Position Integrator'

  cascaded_controller_B.Cbi_c[0] = cascaded_controller_B.eta;
  cascaded_controller_B.Cbi_c[3] = cascaded_controller_B.rtb_delta_qe_idx_2;
  cascaded_controller_B.Cbi_c[6] = cascaded_controller_B.scale;
  cascaded_controller_B.Cbi_c[1] = cascaded_controller_B.absxk;
  cascaded_controller_B.Cbi_c[4] = cascaded_controller_B.eta;
  cascaded_controller_B.Cbi_c[7] = cascaded_controller_B.b_scale;
  cascaded_controller_B.Cbi_c[2] = cascaded_controller_B.b_absxk;
  cascaded_controller_B.Cbi_c[5] =
    cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2;
  cascaded_controller_B.Cbi_c[8] = cascaded_controller_B.eta;
  for (i = 0; i < 9; i++) {
    cascaded_controller_B.X_est.Cib[i] = (cascaded_controller_B.a_o *
      cascaded_controller_B.rotm[i] + cascaded_controller_B.rtb_Cbi_tmp[i]) +
      cascaded_controller_B.Cbi_c[i];
    cascaded_controller_B.Cbi[i] += cascaded_controller_B.rtb_Cbi_tmp_b[i];
  }

  cascaded_controller_B.b_t = std::asin(std::fmax(-1.0, std::fmin(1.0,
    cascaded_controller_B.Cbi[6])));
  if (std::abs(std::cos(-cascaded_controller_B.b_t)) < 1.0E-6) {
    cascaded_controller_B.phi = 0.0;
    cascaded_controller_B.psi = rt_atan2d_snf(-cascaded_controller_B.Cbi[1],
      cascaded_controller_B.Cbi[4]);
  } else {
    cascaded_controller_B.phi = rt_atan2d_snf(cascaded_controller_B.Cbi[7],
      cascaded_controller_B.Cbi[8]);
    cascaded_controller_B.psi = rt_atan2d_snf(cascaded_controller_B.Cbi[3],
      cascaded_controller_B.Cbi[0]);
  }

  cascaded_controller_wrapToPi(&cascaded_controller_B.phi);
  cascaded_controller_B.theta = -cascaded_controller_B.b_t;
  cascaded_controller_wrapToPi(&cascaded_controller_B.theta);
  cascaded_controller_wrapToPi(&cascaded_controller_B.psi);
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
  cascaded_controller_B.rtb_Filter_l_idx_0 = 0.0;
  cascaded_controller_B.rtb_IntegralGain_c_idx_1 = 0.0;
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t =
      cascaded_controller_DW.PositionIntegrator_DSTATE[i];
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 +=
      cascaded_controller_B.X_est.Cib[3 * i] * cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_Filter_l_idx_0 += cascaded_controller_B.X_est.Cib
      [3 * i + 1] * cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_IntegralGain_c_idx_1 +=
      cascaded_controller_B.X_est.Cib[3 * i + 2] * cascaded_controller_B.b_t;
  }

  cascaded_controller_B.X_est.Eul[0] = cascaded_controller_B.phi;
  cascaded_controller_B.X_est.Eul[1] = cascaded_controller_B.theta;
  cascaded_controller_B.X_est.Eul[2] = cascaded_controller_B.psi;
  cascaded_controller_B.X_est.Ri[0] =
    cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  cascaded_controller_B.X_est.Ri[1] = cascaded_controller_B.rtb_Filter_l_idx_0;
  cascaded_controller_B.X_est.Ri[2] =
    cascaded_controller_B.rtb_IntegralGain_c_idx_1;

  // MATLAB Function: '<S14>/commandExecuter' incorporates:
  //   DataStoreRead: '<S4>/Data Store Read'
  //   MATLAB Function: '<S5>/cmdMsgToCmdBus'
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'

  if (!cascaded_controller_DW.hold_timer_start_time_not_empty) {
    cascaded_controller_DW.hold_timer_start_time =
      cascaded_controller_B.DigitalClock;
    cascaded_controller_DW.hold_timer_start_time_not_empty = true;
  }

  if (!cascaded_controller_DW.idle_wp_not_empty) {
    cascaded_controller_DW.idle_wp[0] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0;
    cascaded_controller_DW.idle_wp[1] = cascaded_controller_B.rtb_Filter_l_idx_0;
    cascaded_controller_DW.idle_wp[2] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_1;
    cascaded_controller_DW.idle_wp[3] = 0.0;
    cascaded_controller_DW.idle_wp[4] = 0.0;
    cascaded_controller_DW.idle_wp[5] = cascaded_controller_B.psi;
    cascaded_controller_DW.idle_wp_not_empty = true;
  }

  if (!cascaded_controller_DW.cmd_specific_wp_not_empty) {
    for (i = 0; i < 6; i++) {
      cascaded_controller_DW.cmd_specific_wp[i] =
        cascaded_controller_DW.idle_wp[i];
    }

    cascaded_controller_DW.cmd_specific_wp_not_empty = true;
  }

  if ((cascaded_controller_DW.UnitDelay_DSTATE == 2.0) &&
      (cascaded_controller_DW.prior_action_id != 2.0)) {
    cascaded_controller_DW.idle_wp[5] = cascaded_controller_DW.UnitDelay1_DSTATE;
  }

  cascaded_controller_DW.prior_action_id =
    cascaded_controller_DW.UnitDelay_DSTATE;
  if (cascaded_controller_DW.start_new_cmd_flag) {
    cascaded_controller_DW.idle_wp[0] = 0.0;
    cascaded_controller_DW.idle_wp[1] = 0.0;
    cascaded_controller_DW.idle_wp[2] = 0.0;
    cascaded_controller_DW.idle_wp[3] = 0.0;
    cascaded_controller_DW.idle_wp[4] = 0.0;
    cascaded_controller_DW.idle_wp[5] = cascaded_controller_B.psi;
    cascaded_controller_DW.hold_timer_start_time =
      cascaded_controller_B.DigitalClock;
    cascaded_controller_DW.prior_action_id = 0.0;
    cascaded_controller_B.varargin_2_p[16] = '\x00';
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.varargin_2_p[i] = cascaded_controller_B.cmd.cmd_id[i];
      cascaded_controller_B.varargin_3_l[i] =
        cascaded_controller_B.cmd.trick_id[i];
    }

    cascaded_controller_B.varargin_3_l[16] = '\x00';
    std::printf("%.2f: Working on command %s with trick %s.\n",
                cascaded_controller_B.DigitalClock,
                &cascaded_controller_B.varargin_2_p[0],
                &cascaded_controller_B.varargin_3_l[0]);
    std::fflush(stdout);
  }

  for (i = 0; i < 16; i++) {
    cascaded_controller_B.switch_expression[i] =
      cascaded_controller_B.cmd.cmd_id[i];
  }

  i = std::memcmp(&c_a[0], &cascaded_controller_B.switch_expression[0], 16);
  if (i == 0) {
    c_a_tmp = 0;
  } else {
    i = std::memcmp(&d_a[0], &cascaded_controller_B.switch_expression[0], 16);
    if (i == 0) {
      c_a_tmp = 1;
    } else {
      c_a_tmp = -1;
    }
  }

  switch (c_a_tmp) {
   case 0:
    cascaded_controller_B.dv3[0] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.roll) *
      cascaded_controller_DW.idle_wp[3] +
      cascaded_controller_B.In1_n.waypoint.roll * static_cast<real_T>
      (cascaded_controller_B.In1_n.waypoint_mask.roll);
    cascaded_controller_B.X_u[0] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.x) *
      cascaded_controller_DW.idle_wp[0] + cascaded_controller_B.In1_n.waypoint.x
      * static_cast<real_T>(cascaded_controller_B.In1_n.waypoint_mask.x);
    cascaded_controller_B.dv3[1] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.pitch) *
      cascaded_controller_DW.idle_wp[4] +
      cascaded_controller_B.In1_n.waypoint.pitch * static_cast<real_T>
      (cascaded_controller_B.In1_n.waypoint_mask.pitch);
    cascaded_controller_B.X_u[1] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.y) *
      cascaded_controller_DW.idle_wp[1] + cascaded_controller_B.In1_n.waypoint.y
      * static_cast<real_T>(cascaded_controller_B.In1_n.waypoint_mask.y);
    cascaded_controller_B.dv3[2] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.yaw) *
      cascaded_controller_DW.idle_wp[5] +
      cascaded_controller_B.In1_n.waypoint.yaw * static_cast<real_T>
      (cascaded_controller_B.In1_n.waypoint_mask.yaw);
    cascaded_controller_B.X_u[2] = static_cast<real_T>
      (!cascaded_controller_B.In1_n.waypoint_mask.z) *
      cascaded_controller_DW.idle_wp[2] + cascaded_controller_B.In1_n.waypoint.z
      * static_cast<real_T>(cascaded_controller_B.In1_n.waypoint_mask.z);
    cascaded_controller_eulToQuat_m(cascaded_controller_B.dv3,
      cascaded_controller_B.dv1);
    cascaded_controller_B.X_u[3] = cascaded_controller_B.dv1[0];
    cascaded_controller_B.X_u[4] = cascaded_controller_B.dv1[1];
    cascaded_controller_B.X_u[5] = cascaded_controller_B.dv1[2];
    cascaded_controller_B.X_u[6] = cascaded_controller_B.dv1[3];
    cascaded_controller_B.X_u[7] = 0.0;
    cascaded_controller_B.X_u[10] = 0.0;
    cascaded_controller_B.X_u[8] = 0.0;
    cascaded_controller_B.X_u[11] = 0.0;
    cascaded_controller_B.X_u[9] = 0.0;
    cascaded_controller_B.X_u[12] = 0.0;
    cascaded_controller_B.qe_matlab[0] = ((cascaded_controller_B.qe_matlab_idx_3
      * cascaded_controller_B.dv1[3] - -cascaded_controller_B.X_est.qib[0] *
      cascaded_controller_B.dv1[0]) - -cascaded_controller_B.X_est.qib[1] *
      cascaded_controller_B.dv1[1]) - -cascaded_controller_B.X_est.qib[2] *
      cascaded_controller_B.dv1[2];
    cascaded_controller_B.qe_matlab[1] = (cascaded_controller_B.qe_matlab_idx_3 *
      cascaded_controller_B.dv1[0] + cascaded_controller_B.dv1[3] *
      -cascaded_controller_B.X_est.qib[0]) + (-cascaded_controller_B.X_est.qib[1]
      * cascaded_controller_B.dv1[2] - cascaded_controller_B.dv1[1] *
      -cascaded_controller_B.X_est.qib[2]);
    cascaded_controller_B.qe_matlab[2] = (cascaded_controller_B.qe_matlab_idx_3 *
      cascaded_controller_B.dv1[1] + cascaded_controller_B.dv1[3] *
      -cascaded_controller_B.X_est.qib[1]) + (cascaded_controller_B.dv1[0] *
      -cascaded_controller_B.X_est.qib[2] - -cascaded_controller_B.X_est.qib[0] *
      cascaded_controller_B.dv1[2]);
    cascaded_controller_B.qe_matlab[3] = (cascaded_controller_B.qe_matlab_idx_3 *
      cascaded_controller_B.dv1[2] + cascaded_controller_B.dv1[3] *
      -cascaded_controller_B.X_est.qib[2]) + (-cascaded_controller_B.X_est.qib[0]
      * cascaded_controller_B.dv1[1] - cascaded_controller_B.dv1[0] *
      -cascaded_controller_B.X_est.qib[1]);
    cascaded_controller_B.qinv[0] = cascaded_controller_B.qe_matlab[1];
    cascaded_controller_B.qinv[1] = cascaded_controller_B.qe_matlab[2];
    cascaded_controller_B.qinv[2] = cascaded_controller_B.qe_matlab[3];
    cascaded_controller_B.qinv[3] = cascaded_controller_B.qe_matlab[0];
    if (cascaded_controller_B.qe_matlab[0] < 0.0) {
      cascaded_controller_B.qinv[0] = -cascaded_controller_B.qe_matlab[1];
      cascaded_controller_B.qinv[1] = -cascaded_controller_B.qe_matlab[2];
      cascaded_controller_B.qinv[2] = -cascaded_controller_B.qe_matlab[3];
      cascaded_controller_B.qinv[3] = -cascaded_controller_B.qe_matlab[0];
    }

    cascaded_controller_B.theta = cascaded_controller_B.qinv[3] *
      cascaded_controller_B.qinv[3] * 2.0 - 1.0;
    cascaded_controller_B.b_t = 2.0 * cascaded_controller_B.qinv[3];
    for (i = 0; i < 3; i++) {
      cascaded_controller_B.psi = 2.0 * cascaded_controller_B.qinv[i];
      cascaded_controller_B.rotm[3 * i] = cascaded_controller_B.rtb_Cbi_tmp_tmp
        [3 * i] * cascaded_controller_B.theta + cascaded_controller_B.psi *
        cascaded_controller_B.qinv[0];
      c_a_tmp = 3 * i + 1;
      cascaded_controller_B.rotm[c_a_tmp] =
        cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] *
        cascaded_controller_B.theta + cascaded_controller_B.psi *
        cascaded_controller_B.qinv[1];
      c_a_tmp = 3 * i + 2;
      cascaded_controller_B.rotm[c_a_tmp] =
        cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] *
        cascaded_controller_B.theta + cascaded_controller_B.psi *
        cascaded_controller_B.qinv[2];
    }

    cascaded_controller_B.psi = cascaded_controller_B.b_t * 0.0;
    cascaded_controller_B.Cbi_c[0] = cascaded_controller_B.psi;
    cascaded_controller_B.Cbi_c[1] = cascaded_controller_B.b_t *
      -cascaded_controller_B.qinv[2];
    cascaded_controller_B.Cbi_c[2] = cascaded_controller_B.b_t *
      cascaded_controller_B.qinv[1];
    cascaded_controller_B.Cbi_c[3] = cascaded_controller_B.b_t *
      cascaded_controller_B.qinv[2];
    cascaded_controller_B.Cbi_c[4] = cascaded_controller_B.psi;
    cascaded_controller_B.Cbi_c[5] = cascaded_controller_B.b_t *
      -cascaded_controller_B.qinv[0];
    cascaded_controller_B.Cbi_c[6] = cascaded_controller_B.b_t *
      -cascaded_controller_B.qinv[1];
    cascaded_controller_B.Cbi_c[7] = cascaded_controller_B.b_t *
      cascaded_controller_B.qinv[0];
    cascaded_controller_B.Cbi_c[8] = cascaded_controller_B.psi;
    for (i = 0; i < 9; i++) {
      cascaded_controller_B.Cbi[i] = cascaded_controller_B.rotm[i] +
        cascaded_controller_B.Cbi_c[i];
    }

    cascaded_controller_B.b_t = std::asin(std::fmax(-1.0, std::fmin(1.0,
      cascaded_controller_B.Cbi[6])));
    if (std::abs(std::cos(-cascaded_controller_B.b_t)) < 1.0E-6) {
      cascaded_controller_B.phi_b = 0.0;
      cascaded_controller_B.psi = rt_atan2d_snf(-cascaded_controller_B.Cbi[1],
        cascaded_controller_B.Cbi[4]);
    } else {
      cascaded_controller_B.phi_b = rt_atan2d_snf(cascaded_controller_B.Cbi[7],
        cascaded_controller_B.Cbi[8]);
      cascaded_controller_B.psi = rt_atan2d_snf(cascaded_controller_B.Cbi[3],
        cascaded_controller_B.Cbi[0]);
    }

    cascaded_controller_wrapToPi(&cascaded_controller_B.phi_b);
    cascaded_controller_B.theta = -cascaded_controller_B.b_t;
    cascaded_controller_wrapToPi(&cascaded_controller_B.theta);
    cascaded_controller_wrapToPi(&cascaded_controller_B.psi);
    cascaded_controller_B.b_x[0] = (std::abs
      (cascaded_controller_B.rtb_IntegralGain_c_idx_0 -
       cascaded_controller_B.X_u[0]) < cascaded_controller_B.In1_n.tolerance.x);
    cascaded_controller_B.b_x[3] = (std::abs(cascaded_controller_B.phi_b) <
      cascaded_controller_B.In1_n.tolerance.roll);
    cascaded_controller_B.b_x[1] = (std::abs
      (cascaded_controller_B.rtb_Filter_l_idx_0 - cascaded_controller_B.X_u[1]) <
      cascaded_controller_B.In1_n.tolerance.y);
    cascaded_controller_B.b_x[4] = (std::abs(cascaded_controller_B.theta) <
      cascaded_controller_B.In1_n.tolerance.pitch);
    cascaded_controller_B.b_x[2] = (std::abs
      (cascaded_controller_B.rtb_IntegralGain_c_idx_1 -
       cascaded_controller_B.X_u[2]) < cascaded_controller_B.In1_n.tolerance.z);
    cascaded_controller_B.b_x[5] = (std::abs(cascaded_controller_B.psi) <
      cascaded_controller_B.In1_n.tolerance.yaw);
    tf = true;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k < 6)) {
      if (!cascaded_controller_B.b_x[b_k]) {
        tf = false;
        exitg1 = true;
      } else {
        b_k++;
      }
    }

    if (tf) {
      cascaded_controller_B.b_t = cascaded_controller_B.DigitalClock -
        cascaded_controller_DW.hold_timer_start_time;
    } else {
      cascaded_controller_DW.hold_timer_start_time =
        cascaded_controller_B.DigitalClock;
      cascaded_controller_B.b_t = 0.0;
    }

    if (cascaded_controller_B.b_t >= cascaded_controller_B.In1_n.hold_time) {
      rtb_cmd_status[0] = 83;
      rtb_cmd_status[1] = 85;
      rtb_cmd_status[2] = 67;
      rtb_cmd_status[3] = 67;
      cascaded_controller_DW.hold_timer_start_time =
        cascaded_controller_B.DigitalClock;
    } else {
      rtb_cmd_status[0] = 82;
      rtb_cmd_status[1] = 85;
      rtb_cmd_status[2] = 78;
      rtb_cmd_status[3] = 78;
    }

    for (i = 0; i < 6; i++) {
      cascaded_controller_DW.cmd_specific_wp[i] =
        cascaded_controller_DW.idle_wp[i];
    }
    break;

   case 1:
    cascaded_c_executeDurationTrick(cascaded_controller_B.In1_n.hold_time,
      cascaded_controller_B.cmd.trick_id, cascaded_controller_DW.idle_wp,
      cascaded_controller_B.X_est.Ri, cascaded_controller_B.X_est.Eul,
      cascaded_controller_B.X_est.Cib,
      &cascaded_controller_DW.hold_timer_start_time,
      cascaded_controller_B.DigitalClock,
      cascaded_controller_DW.start_new_cmd_flag,
      cascaded_controller_DW.cmd_specific_wp, rtb_cmd_status,
      &cascaded_controller_B.b_t, cascaded_controller_B.X_u);
    break;

   default:
    cascaded_controller_eulToQuat_m(&cascaded_controller_DW.idle_wp[3],
      cascaded_controller_B.dv1);
    cascaded_controller_B.X_u[0] = cascaded_controller_DW.idle_wp[0];
    cascaded_controller_B.X_u[1] = cascaded_controller_DW.idle_wp[1];
    cascaded_controller_B.X_u[2] = cascaded_controller_DW.idle_wp[2];
    cascaded_controller_B.X_u[3] = cascaded_controller_B.dv1[0];
    cascaded_controller_B.X_u[4] = cascaded_controller_B.dv1[1];
    cascaded_controller_B.X_u[5] = cascaded_controller_B.dv1[2];
    cascaded_controller_B.X_u[6] = cascaded_controller_B.dv1[3];
    cascaded_controller_B.X_u[7] = 0.0;
    cascaded_controller_B.X_u[10] = 0.0;
    cascaded_controller_B.X_u[8] = 0.0;
    cascaded_controller_B.X_u[11] = 0.0;
    cascaded_controller_B.X_u[9] = 0.0;
    cascaded_controller_B.X_u[12] = 0.0;
    cascaded_controller_DW.hold_timer_start_time =
      cascaded_controller_B.DigitalClock;
    rtb_cmd_status[0] = 82;
    rtb_cmd_status[1] = 85;
    rtb_cmd_status[2] = 78;
    rtb_cmd_status[3] = 78;
    break;
  }

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn' incorporates:
  //   EnablePort: '<S13>/Subsystem Enable'

  // MATLAB Function: '<S13>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   MATLAB Function: '<S9>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S4>/Unit Delay'

  cascaded_controller_DW.prior_action_id_not_empty = true;
  cascaded_controller_B.Ri_xy_e[0] = cascaded_controller_B.X_u[0] -
    cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  cascaded_controller_B.Ri_xy_e[1] = cascaded_controller_B.X_u[1] -
    cascaded_controller_B.rtb_Filter_l_idx_0;
  cascaded_controller_DW.UnitDelay1_DSTATE = rt_atan2d_snf
    (cascaded_controller_B.Ri_xy_e[1], cascaded_controller_B.Ri_xy_e[0]);
  cascaded_controller_B.DigitalClock = cascaded_controller_norm
    (cascaded_controller_B.Ri_xy_e);
  if (cascaded_controller_B.DigitalClock >= 1.0) {
    cascaded_controller_B.dv3[0] = 0.0;
    cascaded_controller_B.dv3[1] = 0.0;
    cascaded_controller_B.dv3[2] = cascaded_controller_DW.UnitDelay1_DSTATE;
    cascaded_controller_eulToRotm(cascaded_controller_B.dv3,
      cascaded_controller_B.rotm);
    cascaded_controller_rotmToQuat(cascaded_controller_B.rotm,
      cascaded_controller_B.qe_matlab);
  } else {
    cascaded_controller_quatToEul(&cascaded_controller_B.X_u[3],
      cascaded_controller_B.R_error);
    cascaded_controller_B.qe_matlab[0] = cascaded_controller_B.X_u[3];
    cascaded_controller_B.qe_matlab[1] = cascaded_controller_B.X_u[4];
    cascaded_controller_B.qe_matlab[2] = cascaded_controller_B.X_u[5];
    cascaded_controller_B.qe_matlab[3] = cascaded_controller_B.X_u[6];
  }

  cascaded_controller_quatToEul(cascaded_controller_B.qe_matlab,
    cascaded_controller_B.eps_g);
  tf = false;
  rtb_RelationalOperator_g_idx_0 = true;
  c_a_tmp = 0;
  exitg1 = false;
  while ((!exitg1) && (c_a_tmp < 16)) {
    if (cascaded_controller_B.switch_expression[c_a_tmp] != c[c_a_tmp]) {
      rtb_RelationalOperator_g_idx_0 = false;
      exitg1 = true;
    } else {
      c_a_tmp++;
    }
  }

  if (rtb_RelationalOperator_g_idx_0) {
    tf = true;
  }

  if (tf) {
    cascaded_controller_B.qe_matlab[0] = cascaded_controller_B.X_u[3];
    cascaded_controller_B.qe_matlab[1] = cascaded_controller_B.X_u[4];
    cascaded_controller_B.qe_matlab[2] = cascaded_controller_B.X_u[5];
    cascaded_controller_B.qe_matlab[3] = cascaded_controller_B.X_u[6];
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.x1[i] = cascaded_controller_B.cmd.trick_id[i];
    }

    tf = false;
    rtb_RelationalOperator_g_idx_0 = true;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k < 16)) {
      if (cascaded_controller_B.x1[b_k] != d[b_k]) {
        rtb_RelationalOperator_g_idx_0 = false;
        exitg1 = true;
      } else {
        b_k++;
      }
    }

    if (rtb_RelationalOperator_g_idx_0) {
      tf = true;
    }

    if (tf) {
      cascaded_controller_quatToEul(&cascaded_controller_B.X_u[3],
        cascaded_controller_B.eps);
      cascaded_controller_B.dv3[0] = 0.0;
      cascaded_controller_B.dv3[1] = cascaded_controller_B.eps[1];
      cascaded_controller_B.dv3[2] = cascaded_controller_B.eps[2];
      cascaded_controller_eulToRotm(cascaded_controller_B.dv3,
        cascaded_controller_B.rotm);
      cascaded_controller_rotmToQuat(cascaded_controller_B.rotm,
        cascaded_controller_B.qe_matlab);
    }
  }

  cascaded_controller_B.b_t = ((cascaded_controller_B.qe_matlab_idx_3 *
    cascaded_controller_B.qe_matlab[3] - -cascaded_controller_B.X_est.qib[0] *
    cascaded_controller_B.qe_matlab[0]) - -cascaded_controller_B.X_est.qib[1] *
    cascaded_controller_B.qe_matlab[1]) - -cascaded_controller_B.X_est.qib[2] *
    cascaded_controller_B.qe_matlab[2];
  cascaded_controller_B.psi = (cascaded_controller_B.qe_matlab_idx_3 *
    cascaded_controller_B.qe_matlab[0] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_B.X_est.qib[0]) + (-cascaded_controller_B.X_est.qib[1] *
    cascaded_controller_B.qe_matlab[2] - cascaded_controller_B.qe_matlab[1] *
    -cascaded_controller_B.X_est.qib[2]);
  cascaded_controller_B.theta = (cascaded_controller_B.qe_matlab_idx_3 *
    cascaded_controller_B.qe_matlab[1] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_B.X_est.qib[1]) + (cascaded_controller_B.qe_matlab[0] *
    -cascaded_controller_B.X_est.qib[2] - -cascaded_controller_B.X_est.qib[0] *
    cascaded_controller_B.qe_matlab[2]);
  cascaded_controller_B.qe_matlab_idx_3 = (cascaded_controller_B.qe_matlab_idx_3
    * cascaded_controller_B.qe_matlab[2] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_B.X_est.qib[2]) + (-cascaded_controller_B.X_est.qib[0] *
    cascaded_controller_B.qe_matlab[1] - cascaded_controller_B.qe_matlab[0] *
    -cascaded_controller_B.X_est.qib[1]);
  cascaded_controller_B.qinv[0] = cascaded_controller_B.psi;
  cascaded_controller_B.qinv[1] = cascaded_controller_B.theta;
  cascaded_controller_B.qinv[2] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.qinv[3] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t < 0.0) {
    cascaded_controller_B.qinv[0] = -cascaded_controller_B.psi;
    cascaded_controller_B.qinv[1] = -cascaded_controller_B.theta;
    cascaded_controller_B.qinv[2] = -cascaded_controller_B.qe_matlab_idx_3;
    cascaded_controller_B.qinv[3] = -cascaded_controller_B.b_t;
  }

  cascaded_controller_quatToEul(cascaded_controller_B.qinv,
    cascaded_controller_B.eps);
  cascaded_controller_B.R_error[0] = std::abs(cascaded_controller_B.eps[0]);
  cascaded_controller_B.R_error[1] = std::abs(cascaded_controller_B.eps[1]);
  cascaded_controller_B.R_error[2] = std::abs(cascaded_controller_B.eps[2]);
  if (!std::isnan(cascaded_controller_B.R_error[0])) {
    i = 1;
  } else {
    i = 0;
    cascaded_controller_B.iindx = 2;
    exitg1 = false;
    while ((!exitg1) && (cascaded_controller_B.iindx < 4)) {
      if (!std::isnan(cascaded_controller_B.R_error[cascaded_controller_B.iindx
                      - 1])) {
        i = cascaded_controller_B.iindx;
        exitg1 = true;
      } else {
        cascaded_controller_B.iindx++;
      }
    }
  }

  if (i == 0) {
    cascaded_controller_B.b_t = cascaded_controller_B.R_error[0];
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.R_error[i - 1];
    for (cascaded_controller_B.iindx = i + 1; cascaded_controller_B.iindx < 4;
         cascaded_controller_B.iindx++) {
      cascaded_controller_B.psi =
        cascaded_controller_B.R_error[cascaded_controller_B.iindx - 1];
      if (cascaded_controller_B.b_t < cascaded_controller_B.psi) {
        cascaded_controller_B.b_t = cascaded_controller_B.psi;
      }
    }
  }

  if (cascaded_controller_B.b_t > 0.17453292519943295) {
    cascaded_controller_B.eps[0] = 0.0;
    cascaded_controller_B.eps[1] = 0.0;
    cascaded_controller_B.eps[2] = 0.0;
    i = 1;
  } else if (cascaded_controller_B.DigitalClock >= 1.0) {
    cascaded_controller_B.eps[0] = cascaded_controller_B.DigitalClock;
    cascaded_controller_B.eps[1] = 0.0;
    cascaded_controller_B.eps[2] = cascaded_controller_B.X_u[2] -
      cascaded_controller_B.rtb_IntegralGain_c_idx_1;
    i = 2;
  } else {
    for (i = 0; i < 3; i++) {
      cascaded_controller_B.b_t = 2.0 * cascaded_controller_B.X_est.qib[i];
      cascaded_controller_B.rotm[3 * i] = cascaded_controller_B.rtb_Cbi_tmp_tmp
        [3 * i] * cascaded_controller_B.a_o + cascaded_controller_B.b_t *
        cascaded_controller_B.X_est.qib[0];
      c_a_tmp = 3 * i + 1;
      cascaded_controller_B.rotm[c_a_tmp] =
        cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] *
        cascaded_controller_B.a_o + cascaded_controller_B.b_t *
        cascaded_controller_B.X_est.qib[1];
      c_a_tmp = 3 * i + 2;
      cascaded_controller_B.rotm[c_a_tmp] =
        cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] *
        cascaded_controller_B.a_o + cascaded_controller_B.b_t *
        cascaded_controller_B.X_est.qib[2];
    }

    cascaded_controller_B.Cbi_c[0] = cascaded_controller_B.eta;
    cascaded_controller_B.Cbi_c[1] = cascaded_controller_B.rtb_delta_qe_idx_2;
    cascaded_controller_B.Cbi_c[2] = cascaded_controller_B.scale;
    cascaded_controller_B.Cbi_c[3] = cascaded_controller_B.absxk;
    cascaded_controller_B.Cbi_c[4] = cascaded_controller_B.eta;
    cascaded_controller_B.Cbi_c[5] = cascaded_controller_B.b_scale;
    cascaded_controller_B.Cbi_c[6] = cascaded_controller_B.b_absxk;
    cascaded_controller_B.Cbi_c[7] =
      cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2;
    cascaded_controller_B.Cbi_c[8] = cascaded_controller_B.eta;
    for (i = 0; i < 9; i++) {
      cascaded_controller_B.Cbi[i] = cascaded_controller_B.rotm[i] +
        cascaded_controller_B.Cbi_c[i];
    }

    cascaded_controller_B.psi = 0.0;
    cascaded_controller_B.DigitalClock = 0.0;
    cascaded_controller_B.eta = 0.0;
    for (i = 0; i < 3; i++) {
      cascaded_controller_B.b_t = cascaded_controller_B.X_u[i];
      cascaded_controller_B.psi += cascaded_controller_B.Cbi[3 * i] *
        cascaded_controller_B.b_t;
      cascaded_controller_B.DigitalClock += cascaded_controller_B.Cbi[3 * i + 1]
        * cascaded_controller_B.b_t;
      cascaded_controller_B.eta += cascaded_controller_B.Cbi[3 * i + 2] *
        cascaded_controller_B.b_t;
    }

    cascaded_controller_B.R_error[2] = cascaded_controller_B.eta;
    cascaded_controller_B.R_error[1] = cascaded_controller_B.DigitalClock;
    cascaded_controller_B.R_error[0] = cascaded_controller_B.psi;
    for (i = 0; i < 3; i++) {
      cascaded_controller_B.eps[i] = cascaded_controller_B.R_error[i] -
        ((cascaded_controller_B.Cbi[i + 3] *
          cascaded_controller_B.rtb_Filter_l_idx_0 + cascaded_controller_B.Cbi[i]
          * cascaded_controller_B.rtb_IntegralGain_c_idx_0) +
         cascaded_controller_B.Cbi[i + 6] *
         cascaded_controller_B.rtb_IntegralGain_c_idx_1);
    }

    i = 3;
  }

  cascaded_controller_DW.UnitDelay_DSTATE = i;

  // Gain: '<S13>/Gain5' incorporates:
  //   DataStoreWrite: '<S13>/Data Store Write1'
  //   RelationalOperator: '<S16>/FixPt Relational Operator'
  //   UnitDelay: '<S16>/Delay Input1'
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S16>/Delay Input1':
  //
  //   Store in Global RAM

  integrator_reset = static_cast<uint8_T>
    ((cascaded_controller_DW.UnitDelay_DSTATE !=
      cascaded_controller_DW.DelayInput1_DSTATE) << 7);

  // MATLAB Function: '<S13>/quatInjector' incorporates:
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   UnitDelay: '<S4>/Unit Delay'

  if ((cascaded_controller_DW.UnitDelay_DSTATE == 2.0) ||
      (cascaded_controller_DW.UnitDelay_DSTATE == 1.0)) {
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.x1[i] = cascaded_controller_B.cmd.trick_id[i];
    }

    i = std::memcmp(&a_0[0], &cascaded_controller_B.x1[0], 16);
    if (i == 0) {
      cascaded_controller_B.X_est.Eul[0] = cascaded_controller_B.phi + 3.1;
      cascaded_controller_eulToQuat(cascaded_controller_B.X_est.Eul,
        cascaded_controller_B.qe_matlab);
    }
  }

  // End of MATLAB Function: '<S13>/quatInjector'

  // DiscreteIntegrator: '<S18>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read6'

  if ((integrator_reset > 0) &&
      (cascaded_controller_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0;
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0;
  }

  // MATLAB Function: '<S13>/deltaQuatError' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read5'
  //   MATLAB Function: '<S13>/quatPID'

  cascaded_controller_B.phi = ((cascaded_controller_DW.qib[3] *
    cascaded_controller_B.qe_matlab[3] - -cascaded_controller_DW.qib[0] *
    cascaded_controller_B.qe_matlab[0]) - -cascaded_controller_DW.qib[1] *
    cascaded_controller_B.qe_matlab[1]) - -cascaded_controller_DW.qib[2] *
    cascaded_controller_B.qe_matlab[2];
  cascaded_controller_B.a_o = (cascaded_controller_B.qe_matlab[0] *
    cascaded_controller_DW.qib[3] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_DW.qib[0]) + (-cascaded_controller_DW.qib[1] *
    cascaded_controller_B.qe_matlab[2] - cascaded_controller_B.qe_matlab[1] *
    -cascaded_controller_DW.qib[2]);
  cascaded_controller_B.DigitalClock = cascaded_controller_B.a_o;
  cascaded_controller_B.psi = (cascaded_controller_B.qe_matlab[1] *
    cascaded_controller_DW.qib[3] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_DW.qib[1]) + (cascaded_controller_B.qe_matlab[0] *
    -cascaded_controller_DW.qib[2] - -cascaded_controller_DW.qib[0] *
    cascaded_controller_B.qe_matlab[2]);
  cascaded_controller_B.eta = cascaded_controller_B.psi;
  cascaded_controller_B.qe_matlab_idx_3 = (cascaded_controller_B.qe_matlab[2] *
    cascaded_controller_DW.qib[3] + cascaded_controller_B.qe_matlab[3] *
    -cascaded_controller_DW.qib[2]) + (-cascaded_controller_DW.qib[0] *
    cascaded_controller_B.qe_matlab[1] - cascaded_controller_B.qe_matlab[0] *
    -cascaded_controller_DW.qib[1]);
  cascaded_controller_B.rtb_delta_qe_idx_2 =
    cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.scale = cascaded_controller_B.phi;
  if (cascaded_controller_B.phi < 0.0) {
    cascaded_controller_B.DigitalClock = -cascaded_controller_B.a_o;
    cascaded_controller_B.eta = -cascaded_controller_B.psi;
    cascaded_controller_B.rtb_delta_qe_idx_2 =
      -cascaded_controller_B.qe_matlab_idx_3;
    cascaded_controller_B.scale = -cascaded_controller_B.phi;
  }

  tf = false;
  if (std::isnan(cascaded_controller_B.scale)) {
    cascaded_controller_B.b_t = (rtNaN);
  } else {
    cascaded_controller_B.b_t = (cascaded_controller_B.scale > 0.0);
  }

  if (cascaded_controller_B.b_t == 0.0) {
    tf = true;
  }

  if (!tf) {
    cascaded_controller_B.DigitalClock *= cascaded_controller_B.b_t;
    cascaded_controller_B.eta *= cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_delta_qe_idx_2 *= cascaded_controller_B.b_t;
    cascaded_controller_B.scale *= cascaded_controller_B.b_t;
  }

  // SignalConversion generated from: '<S13>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S13>/deltaQuatError'

  cascaded_controller_B.qe_matlab[0] = 1.0 - cascaded_controller_B.scale;
  cascaded_controller_B.qe_matlab[1] = 0.0 - cascaded_controller_B.DigitalClock;
  cascaded_controller_B.qe_matlab[2] = 0.0 - cascaded_controller_B.eta;
  cascaded_controller_B.qe_matlab[3] = 0.0 -
    cascaded_controller_B.rtb_delta_qe_idx_2;

  // DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S13>/deltaQuatError'

  cascaded_controller_B.absxk = ((1.0 - cascaded_controller_B.scale) -
    (-cascaded_controller_DW.DiscreteTransferFcn_states[0])) / 1.1;
  cascaded_controller_B.b_scale = cascaded_controller_B.absxk;
  cascaded_controller_B.DiscreteTransferFcn[0] = 10.0 *
    cascaded_controller_B.absxk + -10.0 *
    cascaded_controller_DW.DiscreteTransferFcn_states[0];
  cascaded_controller_B.absxk = ((0.0 - cascaded_controller_B.DigitalClock) -
    (-cascaded_controller_DW.DiscreteTransferFcn_states[1])) / 1.1;
  cascaded_controller_B.b_absxk = cascaded_controller_B.absxk;
  cascaded_controller_B.DiscreteTransferFcn[1] = 10.0 *
    cascaded_controller_B.absxk + -10.0 *
    cascaded_controller_DW.DiscreteTransferFcn_states[1];
  cascaded_controller_B.absxk = ((0.0 - cascaded_controller_B.eta) -
    (-cascaded_controller_DW.DiscreteTransferFcn_states[2])) / 1.1;
  cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2 =
    cascaded_controller_B.absxk;
  cascaded_controller_B.DiscreteTransferFcn[2] = 10.0 *
    cascaded_controller_B.absxk + -10.0 *
    cascaded_controller_DW.DiscreteTransferFcn_states[2];
  cascaded_controller_B.absxk = ((0.0 - cascaded_controller_B.rtb_delta_qe_idx_2)
    - (-cascaded_controller_DW.DiscreteTransferFcn_states[3])) / 1.1;
  cascaded_controller_B.DiscreteTransferFcn[3] = 10.0 *
    cascaded_controller_B.absxk + -10.0 *
    cascaded_controller_DW.DiscreteTransferFcn_states[3];

  // MATLAB Function: '<S13>/quatPID' incorporates:
  //   DiscreteIntegrator: '<S18>/Discrete-Time Integrator'
  //   Gain: '<S13>/Gain1'
  //   Gain: '<S13>/Gain2'
  //   SignalConversion generated from: '<S13>/Discrete Transfer Fcn'

  cascaded_controller_B.qinv[0] = cascaded_controller_B.a_o;
  cascaded_controller_B.qinv[1] = cascaded_controller_B.psi;
  cascaded_controller_B.qinv[2] = cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.qinv[3] = cascaded_controller_B.phi;
  if (cascaded_controller_B.phi < 0.0) {
    cascaded_controller_B.qinv[0] = -cascaded_controller_B.a_o;
    cascaded_controller_B.qinv[1] = -cascaded_controller_B.psi;
    cascaded_controller_B.qinv[2] = -cascaded_controller_B.qe_matlab_idx_3;
    cascaded_controller_B.qinv[3] = -cascaded_controller_B.phi;
  }

  cascaded_controller_B.Qe1[0] = -cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[4] = -cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[8] = -cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[1] = cascaded_controller_B.qinv[3];
  cascaded_controller_B.Qe1[5] = -cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[9] = cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[2] = cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[6] = cascaded_controller_B.qinv[3];
  cascaded_controller_B.Qe1[10] = -cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[3] = -cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[7] = cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[11] = cascaded_controller_B.qinv[3];
  cascaded_controller_B.phi = 0.0;
  cascaded_controller_B.a_o = 0.0;
  cascaded_controller_B.psi = 0.0;
  cascaded_controller_B.qe_matlab_idx_3 = 0.0;
  for (i = 0; i < 4; i++) {
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
    cascaded_controller_B.rtb_Filter_l_idx_0 = 0.0;
    cascaded_controller_B.rtb_IntegralGain_c_idx_1 = 0.0;
    cascaded_controller_B.theta = 0.0;
    for (c_a_tmp = 0; c_a_tmp < 3; c_a_tmp++) {
      b_k = c_a_tmp << 2;
      cascaded_controller_B.b_t = cascaded_controller_B.Qe1[b_k + i];
      cascaded_controller_B.rtb_IntegralGain_c_idx_0 +=
        cascaded_controller_B.Qe1[b_k] * cascaded_controller_B.b_t;
      cascaded_controller_B.rtb_Filter_l_idx_0 += cascaded_controller_B.Qe1[b_k
        + 1] * cascaded_controller_B.b_t;
      cascaded_controller_B.rtb_IntegralGain_c_idx_1 +=
        cascaded_controller_B.Qe1[b_k + 2] * cascaded_controller_B.b_t;
      cascaded_controller_B.theta += cascaded_controller_B.Qe1[b_k + 3] *
        cascaded_controller_B.b_t;
    }

    c_a_tmp = i << 2;
    cascaded_controller_B.c_a[c_a_tmp + 3] = cascaded_controller_B.theta;
    cascaded_controller_B.c_a[c_a_tmp + 2] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_1;
    cascaded_controller_B.c_a[c_a_tmp + 1] =
      cascaded_controller_B.rtb_Filter_l_idx_0;
    cascaded_controller_B.c_a[c_a_tmp] =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0;
    cascaded_controller_B.dv1[i] = (cascaded_controller_ConstP.Gain1_Gain[i] *
      cascaded_controller_B.qe_matlab[i] + 0.0 *
      cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[i]) +
      cascaded_controller_B.DiscreteTransferFcn[i];
    cascaded_controller_B.b_t = cascaded_controller_B.dv1[i];
    cascaded_controller_B.phi += cascaded_controller_B.c_a[c_a_tmp] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.a_o += cascaded_controller_B.c_a[c_a_tmp + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.psi += cascaded_controller_B.c_a[c_a_tmp + 2] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.qe_matlab_idx_3 += cascaded_controller_B.c_a[c_a_tmp +
      3] * cascaded_controller_B.b_t;
  }

  cascaded_controller_B.Qe1[0] = cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[1] = cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[2] = cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[3] = -cascaded_controller_B.qinv[3];
  cascaded_controller_B.Qe1[4] = -cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[5] = cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[6] = cascaded_controller_B.qinv[2];
  cascaded_controller_B.Qe1[7] = -cascaded_controller_B.qinv[3];
  cascaded_controller_B.Qe1[8] = -cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[9] = -cascaded_controller_B.qinv[1];
  cascaded_controller_B.Qe1[10] = cascaded_controller_B.qinv[0];
  cascaded_controller_B.Qe1[11] = -cascaded_controller_B.qinv[3];
  cascaded_controller_B.dv1[0] = 2.0 * cascaded_controller_B.phi;
  cascaded_controller_B.dv1[1] = 2.0 * cascaded_controller_B.a_o;
  cascaded_controller_B.dv1[2] = 2.0 * cascaded_controller_B.psi;
  cascaded_controller_B.dv1[3] = 2.0 * cascaded_controller_B.qe_matlab_idx_3;
  cascaded_controller_B.phi = 0.0;
  cascaded_controller_B.psi = 0.0;
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
  for (i = 0; i < 4; i++) {
    cascaded_controller_B.b_t = cascaded_controller_B.dv1[i];
    cascaded_controller_B.phi += cascaded_controller_B.Qe1[3 * i] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.psi += cascaded_controller_B.Qe1[3 * i + 1] *
      cascaded_controller_B.b_t;
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 += cascaded_controller_B.Qe1
      [3 * i + 2] * cascaded_controller_B.b_t;
  }

  cascaded_controller_B.eps_g[2] =
    cascaded_controller_B.rtb_IntegralGain_c_idx_0;
  cascaded_controller_B.eps_g[1] = cascaded_controller_B.psi;
  cascaded_controller_B.eps_g[0] = cascaded_controller_B.phi;

  // DiscreteIntegrator: '<S121>/Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read1'

  if ((integrator_reset > 0) &&
      (cascaded_controller_DW.Integrator_PrevResetState <= 0)) {
    cascaded_controller_DW.Integrator_DSTATE[0] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE[1] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE[2] = 0.0;
  }

  // DiscreteIntegrator: '<S116>/Filter' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read1'

  if ((integrator_reset > 0) && (cascaded_controller_DW.Filter_PrevResetState <=
       0)) {
    cascaded_controller_DW.Filter_DSTATE[0] = 0.0;
    cascaded_controller_DW.Filter_DSTATE[1] = 0.0;
    cascaded_controller_DW.Filter_DSTATE[2] = 0.0;
  }

  // MATLAB Function: '<S13>/quatToRotm' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read'

  cascaded_controller_B.a_o = cascaded_controller_DW.qib[3] *
    cascaded_controller_DW.qib[3] * 2.0 - 1.0;
  cascaded_controller_B.b_t = 2.0 * cascaded_controller_DW.qib[3];
  for (i = 0; i < 3; i++) {
    // Gain: '<S114>/Derivative Gain'
    cascaded_controller_B.phi = cascaded_controller_B.eps[i];

    // Gain: '<S124>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S116>/Filter'
    //   Gain: '<S114>/Derivative Gain'
    //   Sum: '<S116>/SumD'

    cascaded_controller_B.psi = (0.0 * cascaded_controller_B.phi -
      cascaded_controller_DW.Filter_DSTATE[i]) * 100.0;
    cascaded_controller_B.R_error[i] = cascaded_controller_B.psi;

    // Sum: '<S130>/Sum' incorporates:
    //   DiscreteIntegrator: '<S121>/Integrator'
    //   Gain: '<S118>/Integral Gain'
    //   Gain: '<S124>/Filter Coefficient'
    //   Gain: '<S126>/Proportional Gain'

    cascaded_controller_B.psi +=
      cascaded_controller_ConstP.ProportionalGain_Gain[i] *
      cascaded_controller_B.phi + cascaded_controller_DW.Integrator_DSTATE[i];
    cascaded_controller_B.eul_error[i] = cascaded_controller_B.psi;

    // Saturate: '<S128>/Saturation'
    if (cascaded_controller_B.psi > 1.0) {
      // MATLAB Function: '<S13>/dRbSetpointInjector'
      cascaded_controller_B.dRb_u[i] = 1.0;
    } else if (cascaded_controller_B.psi < -1.0) {
      // MATLAB Function: '<S13>/dRbSetpointInjector'
      cascaded_controller_B.dRb_u[i] = -1.0;
    } else {
      // MATLAB Function: '<S13>/dRbSetpointInjector'
      cascaded_controller_B.dRb_u[i] = cascaded_controller_B.psi;
    }

    // End of Saturate: '<S128>/Saturation'

    // MATLAB Function: '<S13>/quatToRotm' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.psi = 2.0 * cascaded_controller_DW.qib[i];
    cascaded_controller_B.rotm[3 * i] = cascaded_controller_B.rtb_Cbi_tmp_tmp[3 *
      i] * cascaded_controller_B.a_o + cascaded_controller_B.psi *
      cascaded_controller_DW.qib[0];

    // Math: '<S13>/Transpose' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read'
    //   MATLAB Function: '<S13>/quatToRotm'

    c_a_tmp = 3 * i + 1;

    // MATLAB Function: '<S13>/quatToRotm' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.rotm[c_a_tmp] =
      cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] * cascaded_controller_B.a_o
      + cascaded_controller_B.psi * cascaded_controller_DW.qib[1];

    // Math: '<S13>/Transpose' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read'
    //   MATLAB Function: '<S13>/quatToRotm'

    c_a_tmp = 3 * i + 2;

    // MATLAB Function: '<S13>/quatToRotm' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read'
    //   Math: '<S13>/Transpose'

    cascaded_controller_B.rotm[c_a_tmp] =
      cascaded_controller_B.rtb_Cbi_tmp_tmp[c_a_tmp] * cascaded_controller_B.a_o
      + cascaded_controller_B.psi * cascaded_controller_DW.qib[2];
  }

  // MATLAB Function: '<S13>/quatToRotm'
  cascaded_controller_B.psi = cascaded_controller_B.b_t * 0.0;

  // Math: '<S13>/Transpose' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read'
  //   MATLAB Function: '<S13>/quatToRotm'

  cascaded_controller_B.Cbi_c[0] = cascaded_controller_B.psi;
  cascaded_controller_B.Cbi_c[1] = cascaded_controller_B.b_t *
    -cascaded_controller_DW.qib[2];
  cascaded_controller_B.Cbi_c[2] = cascaded_controller_B.b_t *
    cascaded_controller_DW.qib[1];
  cascaded_controller_B.Cbi_c[3] = cascaded_controller_B.b_t *
    cascaded_controller_DW.qib[2];
  cascaded_controller_B.Cbi_c[4] = cascaded_controller_B.psi;
  cascaded_controller_B.Cbi_c[5] = cascaded_controller_B.b_t *
    -cascaded_controller_DW.qib[0];
  cascaded_controller_B.Cbi_c[6] = cascaded_controller_B.b_t *
    -cascaded_controller_DW.qib[1];
  cascaded_controller_B.Cbi_c[7] = cascaded_controller_B.b_t *
    cascaded_controller_DW.qib[0];
  cascaded_controller_B.Cbi_c[8] = cascaded_controller_B.psi;

  // MATLAB Function: '<S13>/quatToRotm'
  for (i = 0; i < 9; i++) {
    cascaded_controller_B.rtb_Cbi_tmp_tmp[i] = cascaded_controller_B.rotm[i] +
      cascaded_controller_B.Cbi_c[i];
  }

  // Product: '<S13>/Matrix Multiply3' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read4'

  cascaded_controller_B.b_t = cascaded_controller_DW.dRi[1];
  cascaded_controller_B.phi = cascaded_controller_DW.dRi[0];
  cascaded_controller_B.a_o = cascaded_controller_DW.dRi[2];
  for (i = 0; i < 3; i++) {
    // Sum: '<S13>/Subtract4' incorporates:
    //   Product: '<S13>/Matrix Multiply3'

    cascaded_controller_B.dRb_e[i] = cascaded_controller_B.dRb_u[i] -
      ((cascaded_controller_B.rtb_Cbi_tmp_tmp[i + 3] * cascaded_controller_B.b_t
        + cascaded_controller_B.rtb_Cbi_tmp_tmp[i] * cascaded_controller_B.phi)
       + cascaded_controller_B.rtb_Cbi_tmp_tmp[i + 6] *
       cascaded_controller_B.a_o);

    // MATLAB Function: '<S13>/rateInjector' incorporates:
    //   DataStoreRead: '<S13>/Data Store Read3'
    //   Sum: '<S13>/Subtract'

    cascaded_controller_B.eps_g[i] -= cascaded_controller_DW.wb[i];
  }

  // MATLAB Function: '<S13>/rateInjector' incorporates:
  //   DiscreteIntegrator: '<S9>/Velocity Integrator'
  //   MATLAB Function: '<S13>/trickFTListInjector'
  //   MATLAB Function: '<S9>/derivedStateEstimates'
  //   Product: '<S9>/Matrix Multiply2'

  tf = cascaded_controller_isequal(cascaded_controller_B.switch_expression);
  if (tf) {
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.x1[i] = cascaded_controller_B.cmd.trick_id[i];
    }

    i = std::memcmp(&a_1[0], &cascaded_controller_B.x1[0], 16);
    if (i == 0) {
      c_a_tmp = 0;
    } else {
      i = std::memcmp(&b_a_0[0], &cascaded_controller_B.x1[0], 16);
      if (i == 0) {
        c_a_tmp = 1;
      } else {
        i = std::memcmp(&c_a_1[0], &cascaded_controller_B.x1[0], 16);
        if (i == 0) {
          c_a_tmp = 2;
        } else {
          i = std::memcmp(&d_a_0[0], &cascaded_controller_B.x1[0], 16);
          if (i == 0) {
            c_a_tmp = 3;
          } else {
            i = std::memcmp(&e_a[0], &cascaded_controller_B.x1[0], 16);
            if (i == 0) {
              c_a_tmp = 4;
            } else {
              i = std::memcmp(&f_a[0], &cascaded_controller_B.x1[0], 16);
              if (i == 0) {
                c_a_tmp = 5;
              } else {
                i = std::memcmp(&g_a[0], &cascaded_controller_B.x1[0], 16);
                if (i == 0) {
                  c_a_tmp = 6;
                } else {
                  i = std::memcmp(&h_a[0], &cascaded_controller_B.x1[0], 16);
                  if (i == 0) {
                    c_a_tmp = 7;
                  } else {
                    i = std::memcmp(&i_a[0], &cascaded_controller_B.x1[0], 16);
                    if (i == 0) {
                      c_a_tmp = 8;
                    } else {
                      i = std::memcmp(&j_a[0], &cascaded_controller_B.x1[0], 16);
                      if (i == 0) {
                        c_a_tmp = 9;
                      } else if (cascaded_controller_strcmp
                                 (cascaded_controller_B.x1)) {
                        c_a_tmp = 10;
                      } else if (cascaded_controller_strcmp_a
                                 (cascaded_controller_B.x1)) {
                        c_a_tmp = 11;
                      } else if (cascaded_controller_strcmp_ax
                                 (cascaded_controller_B.x1)) {
                        c_a_tmp = 12;
                      } else {
                        c_a_tmp = -1;
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

    switch (c_a_tmp) {
     case 0:
      cascaded_controller_B.dRb_e[0] = 0.5 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 1:
      cascaded_controller_B.dRb_e[0] = -0.5 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 2:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = -1.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 3:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 1.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 4:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 1.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 5:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = -1.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 6:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 1.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 7:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = -1.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 8:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 1.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 9:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = -1.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 10:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 1.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 11:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = -1.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;

     case 12:
      cascaded_controller_B.dRb_e[0] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[0];
      cascaded_controller_B.eps_g[0] = 0.0 - cascaded_controller_B.rotm_tmp;
      cascaded_controller_B.dRb_e[1] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[1];
      cascaded_controller_B.eps_g[1] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_1;
      cascaded_controller_B.dRb_e[2] = 0.0 -
        cascaded_controller_DW.VelocityIntegrator_DSTATE[2];
      cascaded_controller_B.eps_g[2] = 0.0 -
        cascaded_controller_B.rtb_Integrator_o_idx_2;
      break;
    }
  }

  // DiscreteIntegrator: '<S66>/Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read7'

  if ((integrator_reset > 0) &&
      (cascaded_controller_DW.Integrator_PrevResetState_h <= 0)) {
    cascaded_controller_DW.Integrator_DSTATE_f[0] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE_f[1] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE_f[2] = 0.0;
  }

  // DiscreteIntegrator: '<S61>/Filter' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read7'

  if ((integrator_reset > 0) && (cascaded_controller_DW.Filter_PrevResetState_e <=
       0)) {
    cascaded_controller_DW.Filter_DSTATE_l[0] = 0.0;
    cascaded_controller_DW.Filter_DSTATE_l[1] = 0.0;
    cascaded_controller_DW.Filter_DSTATE_l[2] = 0.0;
  }

  // Gain: '<S69>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S61>/Filter'
  //   Gain: '<S59>/Derivative Gain'
  //   Sum: '<S61>/SumD'

  cascaded_controller_B.rotm_tmp = (0.0 * cascaded_controller_B.eps_g[0] -
    cascaded_controller_DW.Filter_DSTATE_l[0]) * 100.0;
  cascaded_controller_B.dRb_u[0] = cascaded_controller_B.rotm_tmp;

  // Sum: '<S75>/Sum' incorporates:
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S59>/Derivative Gain'

  cascaded_controller_B.b_t = (cascaded_controller_B.eps_g[0] +
    cascaded_controller_DW.Integrator_DSTATE_f[0]) +
    cascaded_controller_B.rotm_tmp;
  cascaded_controller_B.rtb_Filter_l_idx_0 = cascaded_controller_B.b_t;

  // DeadZone: '<S58>/DeadZone'
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_B.theta = cascaded_controller_B.b_t - 10.0;
  } else if (cascaded_controller_B.b_t >= -10.0) {
    cascaded_controller_B.theta = 0.0;
  } else {
    cascaded_controller_B.theta = cascaded_controller_B.b_t - -10.0;
  }

  // Gain: '<S69>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S61>/Filter'
  //   Gain: '<S59>/Derivative Gain'
  //   Sum: '<S61>/SumD'

  cascaded_controller_B.rotm_tmp = (0.0 * cascaded_controller_B.eps_g[1] -
    cascaded_controller_DW.Filter_DSTATE_l[1]) * 100.0;
  cascaded_controller_B.dRb_u[1] = cascaded_controller_B.rotm_tmp;

  // Gain: '<S71>/Proportional Gain' incorporates:
  //   Gain: '<S59>/Derivative Gain'
  //   Gain: '<S63>/Integral Gain'

  cascaded_controller_B.phi = 5.0 * cascaded_controller_B.eps_g[1];
  cascaded_controller_B.eps_g[1] = cascaded_controller_B.phi;

  // Sum: '<S75>/Sum' incorporates:
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S71>/Proportional Gain'

  cascaded_controller_B.b_t = (cascaded_controller_B.phi +
    cascaded_controller_DW.Integrator_DSTATE_f[1]) +
    cascaded_controller_B.rotm_tmp;
  cascaded_controller_B.psi = cascaded_controller_B.b_t;

  // DeadZone: '<S58>/DeadZone'
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_B.rtb_Integrator_o_idx_1 = cascaded_controller_B.b_t -
      10.0;
  } else if (cascaded_controller_B.b_t >= -10.0) {
    cascaded_controller_B.rtb_Integrator_o_idx_1 = 0.0;
  } else {
    cascaded_controller_B.rtb_Integrator_o_idx_1 = cascaded_controller_B.b_t -
      -10.0;
  }

  // Gain: '<S69>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S61>/Filter'
  //   Gain: '<S59>/Derivative Gain'
  //   Sum: '<S61>/SumD'

  cascaded_controller_B.rotm_tmp = (0.0 * cascaded_controller_B.eps_g[2] -
    cascaded_controller_DW.Filter_DSTATE_l[2]) * 100.0;

  // Gain: '<S71>/Proportional Gain' incorporates:
  //   Gain: '<S59>/Derivative Gain'
  //   Gain: '<S63>/Integral Gain'

  cascaded_controller_B.phi = 5.0 * cascaded_controller_B.eps_g[2];

  // Sum: '<S75>/Sum' incorporates:
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S71>/Proportional Gain'

  cascaded_controller_B.b_t = (cascaded_controller_B.phi +
    cascaded_controller_DW.Integrator_DSTATE_f[2]) +
    cascaded_controller_B.rotm_tmp;

  // DeadZone: '<S58>/DeadZone'
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_B.rtb_Integrator_o_idx_2 = cascaded_controller_B.b_t -
      10.0;
  } else if (cascaded_controller_B.b_t >= -10.0) {
    cascaded_controller_B.rtb_Integrator_o_idx_2 = 0.0;
  } else {
    cascaded_controller_B.rtb_Integrator_o_idx_2 = cascaded_controller_B.b_t -
      -10.0;
  }

  // DiscreteIntegrator: '<S176>/Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read9'

  if ((integrator_reset > 0) &&
      (cascaded_controller_DW.Integrator_PrevResetState_d <= 0)) {
    cascaded_controller_DW.Integrator_DSTATE_l[0] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE_l[1] = 0.0;
    cascaded_controller_DW.Integrator_DSTATE_l[2] = 0.0;
  }

  // DiscreteIntegrator: '<S171>/Filter' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read9'

  if ((integrator_reset > 0) && (cascaded_controller_DW.Filter_PrevResetState_a <=
       0)) {
    cascaded_controller_DW.Filter_DSTATE_k[0] = 0.0;
    cascaded_controller_DW.Filter_DSTATE_k[1] = 0.0;
    cascaded_controller_DW.Filter_DSTATE_k[2] = 0.0;
  }

  // Gain: '<S179>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S171>/Filter'
  //   Gain: '<S169>/Derivative Gain'
  //   Sum: '<S171>/SumD'

  cascaded_controller_B.a_o = (0.0 * cascaded_controller_B.dRb_e[0] -
    cascaded_controller_DW.Filter_DSTATE_k[0]) * 100.0;
  cascaded_controller_B.qe_matlab_idx_3 = cascaded_controller_B.a_o;

  // Sum: '<S185>/Sum' incorporates:
  //   DiscreteIntegrator: '<S176>/Integrator'
  //   Gain: '<S169>/Derivative Gain'
  //   Gain: '<S181>/Proportional Gain'

  cascaded_controller_B.phi_b = (60.0 * cascaded_controller_B.dRb_e[0] +
    cascaded_controller_DW.Integrator_DSTATE_l[0]) + cascaded_controller_B.a_o;
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = cascaded_controller_B.phi_b;

  // Saturate: '<S73>/Saturation'
  if (cascaded_controller_B.rtb_Filter_l_idx_0 > 10.0) {
    cascaded_controller_B.dv3[0] = 10.0;
  } else if (cascaded_controller_B.rtb_Filter_l_idx_0 < -10.0) {
    cascaded_controller_B.dv3[0] = -10.0;
  } else {
    cascaded_controller_B.dv3[0] = cascaded_controller_B.rtb_Filter_l_idx_0;
  }

  // Saturate: '<S183>/Saturation'
  if (cascaded_controller_B.phi_b > 100.0) {
    cascaded_controller_B.dv4[0] = 100.0;
  } else if (cascaded_controller_B.phi_b < -100.0) {
    cascaded_controller_B.dv4[0] = -100.0;
  } else {
    cascaded_controller_B.dv4[0] = cascaded_controller_B.phi_b;
  }

  // Gain: '<S179>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S171>/Filter'
  //   Gain: '<S169>/Derivative Gain'
  //   Sum: '<S171>/SumD'

  cascaded_controller_B.a_o = (0.0 * cascaded_controller_B.dRb_e[1] -
    cascaded_controller_DW.Filter_DSTATE_k[1]) * 100.0;
  cascaded_controller_B.rtb_Filter_l_idx_0 = cascaded_controller_B.a_o;

  // Sum: '<S185>/Sum' incorporates:
  //   DiscreteIntegrator: '<S176>/Integrator'
  //   Gain: '<S169>/Derivative Gain'
  //   Gain: '<S181>/Proportional Gain'

  cascaded_controller_B.phi_b = (60.0 * cascaded_controller_B.dRb_e[1] +
    cascaded_controller_DW.Integrator_DSTATE_l[1]) + cascaded_controller_B.a_o;
  cascaded_controller_B.rtb_IntegralGain_c_idx_1 = cascaded_controller_B.phi_b;

  // Saturate: '<S73>/Saturation'
  if (cascaded_controller_B.psi > 10.0) {
    cascaded_controller_B.dv3[1] = 10.0;
  } else if (cascaded_controller_B.psi < -10.0) {
    cascaded_controller_B.dv3[1] = -10.0;
  } else {
    cascaded_controller_B.dv3[1] = cascaded_controller_B.psi;
  }

  // Saturate: '<S183>/Saturation'
  if (cascaded_controller_B.phi_b > 100.0) {
    cascaded_controller_B.dv4[1] = 100.0;
  } else if (cascaded_controller_B.phi_b < -100.0) {
    cascaded_controller_B.dv4[1] = -100.0;
  } else {
    cascaded_controller_B.dv4[1] = cascaded_controller_B.phi_b;
  }

  // Gain: '<S179>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S171>/Filter'
  //   Gain: '<S169>/Derivative Gain'
  //   Sum: '<S171>/SumD'

  cascaded_controller_B.a_o = (0.0 * cascaded_controller_B.dRb_e[2] -
    cascaded_controller_DW.Filter_DSTATE_k[2]) * 100.0;

  // Sum: '<S185>/Sum' incorporates:
  //   DiscreteIntegrator: '<S176>/Integrator'
  //   Gain: '<S169>/Derivative Gain'
  //   Gain: '<S181>/Proportional Gain'

  cascaded_controller_B.phi_b = (100.0 * cascaded_controller_B.dRb_e[2] +
    cascaded_controller_DW.Integrator_DSTATE_l[2]) + cascaded_controller_B.a_o;

  // Saturate: '<S73>/Saturation' incorporates:
  //   Sum: '<S75>/Sum'

  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_B.dv3[2] = 10.0;
  } else if (cascaded_controller_B.b_t < -10.0) {
    cascaded_controller_B.dv3[2] = -10.0;
  } else {
    cascaded_controller_B.dv3[2] = cascaded_controller_B.b_t;
  }

  // Saturate: '<S183>/Saturation'
  if (cascaded_controller_B.phi_b > 100.0) {
    cascaded_controller_B.dv4[2] = 100.0;
  } else if (cascaded_controller_B.phi_b < -100.0) {
    cascaded_controller_B.dv4[2] = -100.0;
  } else {
    cascaded_controller_B.dv4[2] = cascaded_controller_B.phi_b;
  }

  // Product: '<S13>/Matrix Multiply' incorporates:
  //   Constant: '<S13>/Constant'

  std::memset(&cascaded_controller_B.pwms[0], 0, sizeof(real_T) << 3U);
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t = cascaded_controller_B.dv3[i];
    for (c_a_tmp = 0; c_a_tmp < 8; c_a_tmp++) {
      cascaded_controller_B.pwms[c_a_tmp] +=
        cascaded_controller_ConstP.Constant_Value_n[(i << 3) + c_a_tmp] *
        cascaded_controller_B.b_t;
    }
  }

  // End of Product: '<S13>/Matrix Multiply'

  // Product: '<S13>/Matrix Multiply1' incorporates:
  //   Constant: '<S13>/Constant1'

  std::memset(&cascaded_controller_B.dv[0], 0, sizeof(real_T) << 3U);
  for (i = 0; i < 3; i++) {
    cascaded_controller_B.b_t = cascaded_controller_B.dv4[i];
    for (c_a_tmp = 0; c_a_tmp < 8; c_a_tmp++) {
      cascaded_controller_B.dv[c_a_tmp] +=
        cascaded_controller_ConstP.Constant1_Value[(i << 3) + c_a_tmp] *
        cascaded_controller_B.b_t;
    }
  }

  // End of Product: '<S13>/Matrix Multiply1'

  // MATLAB Function: '<S13>/thrusterAllocator'
  for (i = 0; i < 8; i++) {
    cascaded_controller_B.FT_cmd_list[i] = cascaded_controller_B.pwms[i] +
      cascaded_controller_B.dv[i];
  }

  // End of MATLAB Function: '<S13>/thrusterAllocator'

  // MATLAB Function: '<S13>/trickFTListInjector'
  if (tf) {
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.switch_expression[i] =
        cascaded_controller_B.cmd.trick_id[i];
    }

    i = std::memcmp(&a_2[0], &cascaded_controller_B.switch_expression[0], 16);
    if (i == 0) {
      c_a_tmp = 0;
    } else {
      i = std::memcmp(&b_a_1[0], &cascaded_controller_B.switch_expression[0], 16);
      if (i == 0) {
        c_a_tmp = 1;
      } else {
        i = std::memcmp(&c_a_2[0], &cascaded_controller_B.switch_expression[0],
                        16);
        if (i == 0) {
          c_a_tmp = 2;
        } else {
          i = std::memcmp(&d_a_1[0], &cascaded_controller_B.switch_expression[0],
                          16);
          if (i == 0) {
            c_a_tmp = 3;
          } else {
            i = std::memcmp(&e_a_0[0], &cascaded_controller_B.switch_expression
                            [0], 16);
            if (i == 0) {
              c_a_tmp = 4;
            } else {
              i = std::memcmp(&f_a_0[0],
                              &cascaded_controller_B.switch_expression[0], 16);
              if (i == 0) {
                c_a_tmp = 5;
              } else {
                i = std::memcmp(&g_a_0[0],
                                &cascaded_controller_B.switch_expression[0], 16);
                if (i == 0) {
                  c_a_tmp = 6;
                } else {
                  i = std::memcmp(&h_a_0[0],
                                  &cascaded_controller_B.switch_expression[0],
                                  16);
                  if (i == 0) {
                    c_a_tmp = 7;
                  } else {
                    i = std::memcmp(&i_a_0[0],
                                    &cascaded_controller_B.switch_expression[0],
                                    16);
                    if (i == 0) {
                      c_a_tmp = 8;
                    } else {
                      i = std::memcmp(&j_a_0[0],
                                      &cascaded_controller_B.switch_expression[0],
                                      16);
                      if (i == 0) {
                        c_a_tmp = 9;
                      } else {
                        i = std::memcmp(&k_a[0],
                                        &cascaded_controller_B.switch_expression[
                                        0], 16);
                        if (i == 0) {
                          c_a_tmp = 10;
                        } else {
                          i = std::memcmp(&l_a[0],
                                          &cascaded_controller_B.switch_expression
                                          [0], 16);
                          if (i == 0) {
                            c_a_tmp = 11;
                          } else {
                            i = std::memcmp(&m_a[0],
                                            &cascaded_controller_B.switch_expression
                                            [0], 16);
                            if (i == 0) {
                              c_a_tmp = 12;
                            } else {
                              c_a_tmp = -1;
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
      switch (c_a_tmp) {
       case 0:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.forward[i];
        break;

       case 1:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.backward[i];
        break;

       case 2:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.up[i];
        break;

       case 3:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.down[i];
        break;

       case 4:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.left[i];
        break;

       case 5:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.right[i];
        break;

       case 6:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.pitchUp[i];
        break;

       case 7:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.pitchDown[i];
        break;

       case 8:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.yawRight[i];
        break;

       case 9:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.yawLeft[i];
        break;

       case 10:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.rollRight[i];
        break;

       case 11:
        cascaded_controller_B.FT_cmd_list[i] =
          cascaded_controller_ConstP.trickFTListInjector_FF_maneuver.rollLeft[i];
        break;

       case 12:
        cascaded_controller_B.FT_cmd_list[i] = 0.0;
        break;
      }
    }
  }

  // MATLAB Function: '<S19>/forceToPWMCalculator' incorporates:
  //   Constant: '<S13>/Constant3'

  for (i = 0; i < 8; i++) {
    cascaded_controller_B.pwms[i] = 1500.0;
  }

  for (b_k = 0; b_k < 4; b_k++) {
    c_a_tmp = b_k << 1;
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.FT_cmd_list[c_a_tmp];
    if (std::abs(cascaded_controller_B.lower_force_index) < 0.001) {
      cascaded_controller_B.pwms[c_a_tmp] = 1500.0;
    } else {
      for (cascaded_controller_B.iindx = 0; cascaded_controller_B.iindx < 6;
           cascaded_controller_B.iindx++) {
        cascaded_controller_B.varargin_1_f[cascaded_controller_B.iindx] = std::
          abs
          (cascaded_controller_ConstP.forceToPWMCalculator_voltage[cascaded_controller_B.iindx]
           - 15.0);
      }

      cascaded_controller_minimum(cascaded_controller_B.varargin_1_f,
        &cascaded_controller_B.b_t, &cascaded_controller_B.iindx);
      switch (cascaded_controller_B.iindx) {
       case 1:
        cascaded_controller_B.lower_voltage_index = 1.0;
        cascaded_controller_B.upper_voltage_index = 1.0;
        break;

       case 6:
        cascaded_controller_B.lower_voltage_index = 6.0;
        cascaded_controller_B.upper_voltage_index = 6.0;
        break;

       default:
        if (cascaded_controller_ConstP.forceToPWMCalculator_voltage[cascaded_controller_B.iindx
            - 1] < 15.0) {
          cascaded_controller_B.lower_voltage_index =
            cascaded_controller_B.iindx;
          cascaded_controller_B.upper_voltage_index = static_cast<real_T>
            (cascaded_controller_B.iindx) + 1.0;
        } else {
          cascaded_controller_B.upper_voltage_index =
            cascaded_controller_B.iindx;
          cascaded_controller_B.lower_voltage_index = static_cast<real_T>
            (cascaded_controller_B.iindx) - 1.0;
        }
        break;
      }

      if (cascaded_controller_B.upper_voltage_index ==
          cascaded_controller_B.lower_voltage_index) {
        force_column_size_idx_0 = 1;
        cascaded_controller_B.force_column_data[0] =
          cascaded_controller_ConstP.forceToPWMCalculator_cw_force
          [static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (cascaded_controller_ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>(cascaded_controller_B.upper_voltage_index)
                  - 1] -
                  cascaded_controller_ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>(cascaded_controller_B.lower_voltage_index)
                  - 1]) < 0.001) {
        force_column_size_idx_0 = 1;
        cascaded_controller_B.force_column_data[0] =
          cascaded_controller_ConstP.forceToPWMCalculator_cw_force
          [static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
      } else {
        cascaded_controller_B.psi =
          cascaded_controller_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
        cascaded_controller_B.b_t =
          cascaded_controller_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(cascaded_controller_B.upper_voltage_index) - 1]
          - cascaded_controller_B.psi;
        force_column_size_idx_0 = 201;
        for (i = 0; i < 201; i++) {
          cascaded_controller_B.force_column_tmp =
            cascaded_controller_ConstP.forceToPWMCalculator_cw_force[(
            static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1)
            * 201 + i];
          cascaded_controller_B.force_column_data[i] =
            (cascaded_controller_ConstP.forceToPWMCalculator_cw_force[(
              static_cast<int32_T>(cascaded_controller_B.upper_voltage_index) -
              1) * 201 + i] - cascaded_controller_B.force_column_tmp) * (15.0 -
            cascaded_controller_B.psi) / cascaded_controller_B.b_t +
            cascaded_controller_B.force_column_tmp;
        }
      }

      for (cascaded_controller_B.iindx = 0; cascaded_controller_B.iindx <
           force_column_size_idx_0; cascaded_controller_B.iindx++) {
        cascaded_controller_B.b_x_data[cascaded_controller_B.iindx] =
          cascaded_controller_B.force_column_data[cascaded_controller_B.iindx] -
          cascaded_controller_B.lower_force_index;
        cascaded_controller_B.b_varargin_1_data[cascaded_controller_B.iindx] =
          std::abs(cascaded_controller_B.b_x_data[cascaded_controller_B.iindx]);
      }

      cascaded_controller_minimum_c(cascaded_controller_B.b_varargin_1_data,
        &force_column_size_idx_0, &cascaded_controller_B.b_t, &i);
      if ((i == 1) || (i == 2)) {
        cascaded_controller_B.lower_force_index = 1.0;
        cascaded_controller_B.b_t = 1.0;
      } else if ((i == 8) || (i == 7)) {
        cascaded_controller_B.lower_force_index = 8.0;
        cascaded_controller_B.b_t = 8.0;
      } else if (cascaded_controller_B.force_column_data[i - 1] <
                 cascaded_controller_B.FT_cmd_list[c_a_tmp]) {
        cascaded_controller_B.lower_force_index = i;
        cascaded_controller_B.b_t = static_cast<real_T>(i) + 1.0;
      } else {
        cascaded_controller_B.b_t = i;
        cascaded_controller_B.lower_force_index = static_cast<real_T>(i) - 1.0;
      }

      if (cascaded_controller_B.b_t > force_column_size_idx_0) {
        cascaded_controller_B.b_t = force_column_size_idx_0;
      }

      if ((static_cast<int32_T>(cascaded_controller_B.b_t) ==
           force_column_size_idx_0) && (static_cast<real_T>
           (force_column_size_idx_0) - 1.0 ==
           cascaded_controller_B.lower_force_index)) {
        cascaded_controller_B.lower_force_index = cascaded_controller_B.b_t;
      } else if ((cascaded_controller_B.b_t == 2.0) &&
                 (cascaded_controller_B.lower_force_index == 1.0)) {
        cascaded_controller_B.b_t = 1.0;
      }

      if (cascaded_controller_B.lower_force_index == cascaded_controller_B.b_t)
      {
        cascaded_controller_B.psi = 0.0;
      } else if (std::abs(cascaded_controller_B.force_column_data
                          [static_cast<int32_T>(cascaded_controller_B.b_t) - 1]
                          - cascaded_controller_B.force_column_data[static_cast<
                          int32_T>(cascaded_controller_B.lower_force_index) - 1])
                 < 0.001) {
        cascaded_controller_B.psi = 0.0;
      } else {
        cascaded_controller_B.psi = (cascaded_controller_B.FT_cmd_list[c_a_tmp]
          - cascaded_controller_B.force_column_data[static_cast<int32_T>
          (cascaded_controller_B.b_t) - 1]) /
          (cascaded_controller_B.force_column_data[static_cast<int32_T>
           (cascaded_controller_B.b_t) - 1] -
           cascaded_controller_B.force_column_data[static_cast<int32_T>
           (cascaded_controller_B.lower_force_index) - 1]);
      }

      cascaded_controller_B.lower_force_index =
        cascaded_controller_ConstP.forceToPWMCalculator_cw_pwm
        [static_cast<int32_T>(cascaded_controller_B.lower_force_index) - 1];
      cascaded_controller_B.pwms[c_a_tmp] = std::round
        ((cascaded_controller_ConstP.forceToPWMCalculator_cw_pwm[static_cast<
          int32_T>(cascaded_controller_B.b_t) - 1] -
          cascaded_controller_B.lower_force_index) * cascaded_controller_B.psi +
         cascaded_controller_B.lower_force_index);
    }
  }

  for (b_k = 0; b_k < 4; b_k++) {
    c_a_tmp = (b_k << 1) + 1;
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.FT_cmd_list[c_a_tmp];
    if (std::abs(cascaded_controller_B.lower_force_index) < 0.001) {
      cascaded_controller_B.pwms[c_a_tmp] = 1500.0;
    } else {
      for (cascaded_controller_B.iindx = 0; cascaded_controller_B.iindx < 6;
           cascaded_controller_B.iindx++) {
        cascaded_controller_B.varargin_1_f[cascaded_controller_B.iindx] = std::
          abs
          (cascaded_controller_ConstP.forceToPWMCalculator_voltage[cascaded_controller_B.iindx]
           - 15.0);
      }

      cascaded_controller_minimum(cascaded_controller_B.varargin_1_f,
        &cascaded_controller_B.b_t, &i);
      switch (i) {
       case 1:
        cascaded_controller_B.lower_voltage_index = 1.0;
        cascaded_controller_B.upper_voltage_index = 1.0;
        break;

       case 6:
        cascaded_controller_B.lower_voltage_index = 6.0;
        cascaded_controller_B.upper_voltage_index = 6.0;
        break;

       default:
        if (cascaded_controller_ConstP.forceToPWMCalculator_voltage[i - 1] <
            15.0) {
          cascaded_controller_B.lower_voltage_index = i;
          cascaded_controller_B.upper_voltage_index = static_cast<real_T>(i) +
            1.0;
        } else {
          cascaded_controller_B.upper_voltage_index = i;
          cascaded_controller_B.lower_voltage_index = static_cast<real_T>(i) -
            1.0;
        }
        break;
      }

      if (cascaded_controller_B.upper_voltage_index ==
          cascaded_controller_B.lower_voltage_index) {
        force_column_size_idx_0 = 1;
        cascaded_controller_B.force_column_data[0] =
          cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[static_cast<
          int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(cascaded_controller_B.upper_voltage_index)
                  - 1] -
                  cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(cascaded_controller_B.lower_voltage_index)
                  - 1]) < 0.001) {
        force_column_size_idx_0 = 1;
        cascaded_controller_B.force_column_data[0] =
          cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[static_cast<
          int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
      } else {
        cascaded_controller_B.psi =
          cascaded_controller_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1];
        cascaded_controller_B.b_t =
          cascaded_controller_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(cascaded_controller_B.upper_voltage_index) - 1]
          - cascaded_controller_B.psi;
        force_column_size_idx_0 = 201;
        for (i = 0; i < 201; i++) {
          cascaded_controller_B.force_column_tmp =
            cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[(
            static_cast<int32_T>(cascaded_controller_B.lower_voltage_index) - 1)
            * 201 + i];
          cascaded_controller_B.force_column_data[i] =
            (cascaded_controller_ConstP.forceToPWMCalculator_ccw_force[(
              static_cast<int32_T>(cascaded_controller_B.upper_voltage_index) -
              1) * 201 + i] - cascaded_controller_B.force_column_tmp) * (15.0 -
            cascaded_controller_B.psi) / cascaded_controller_B.b_t +
            cascaded_controller_B.force_column_tmp;
        }
      }

      for (cascaded_controller_B.iindx = 0; cascaded_controller_B.iindx <
           force_column_size_idx_0; cascaded_controller_B.iindx++) {
        cascaded_controller_B.b_x_data[cascaded_controller_B.iindx] =
          cascaded_controller_B.force_column_data[cascaded_controller_B.iindx] -
          cascaded_controller_B.lower_force_index;
        cascaded_controller_B.b_varargin_1_data[cascaded_controller_B.iindx] =
          std::abs(cascaded_controller_B.b_x_data[cascaded_controller_B.iindx]);
      }

      cascaded_controller_minimum_c(cascaded_controller_B.b_varargin_1_data,
        &force_column_size_idx_0, &cascaded_controller_B.b_t, &i);
      if ((i == 1) || (i == 2)) {
        cascaded_controller_B.lower_force_index = 1.0;
        cascaded_controller_B.b_t = 1.0;
      } else if ((i == 8) || (i == 7)) {
        cascaded_controller_B.lower_force_index = 8.0;
        cascaded_controller_B.b_t = 8.0;
      } else if (cascaded_controller_B.force_column_data[i - 1] <
                 cascaded_controller_B.FT_cmd_list[c_a_tmp]) {
        cascaded_controller_B.lower_force_index = i;
        cascaded_controller_B.b_t = static_cast<real_T>(i) + 1.0;
      } else {
        cascaded_controller_B.b_t = i;
        cascaded_controller_B.lower_force_index = static_cast<real_T>(i) - 1.0;
      }

      if (cascaded_controller_B.b_t > force_column_size_idx_0) {
        cascaded_controller_B.b_t = force_column_size_idx_0;
      }

      if (cascaded_controller_B.lower_force_index == cascaded_controller_B.b_t)
      {
        cascaded_controller_B.psi = 0.0;
      } else if (std::abs(cascaded_controller_B.force_column_data
                          [static_cast<int32_T>(cascaded_controller_B.b_t) - 1]
                          - cascaded_controller_B.force_column_data[static_cast<
                          int32_T>(cascaded_controller_B.lower_force_index) - 1])
                 < 0.001) {
        cascaded_controller_B.psi = 0.0;
      } else {
        cascaded_controller_B.psi = (cascaded_controller_B.FT_cmd_list[c_a_tmp]
          - cascaded_controller_B.force_column_data[static_cast<int32_T>
          (cascaded_controller_B.b_t) - 1]) /
          (cascaded_controller_B.force_column_data[static_cast<int32_T>
           (cascaded_controller_B.b_t) - 1] -
           cascaded_controller_B.force_column_data[static_cast<int32_T>
           (cascaded_controller_B.lower_force_index) - 1]);
      }

      cascaded_controller_B.lower_force_index =
        cascaded_controller_ConstP.forceToPWMCalculator_ccw_pwm
        [static_cast<int32_T>(cascaded_controller_B.lower_force_index) - 1];
      cascaded_controller_B.pwms[c_a_tmp] = std::round
        ((cascaded_controller_ConstP.forceToPWMCalculator_ccw_pwm
          [static_cast<int32_T>(cascaded_controller_B.b_t) - 1] -
          cascaded_controller_B.lower_force_index) * cascaded_controller_B.psi +
         cascaded_controller_B.lower_force_index);
    }
  }

  for (i = 0; i < 8; i++) {
    c_a_tmp = static_cast<int32_T>(std::fmax(1100.0, std::fmin(1900.0,
      cascaded_controller_B.pwms[i])));
    cascaded_controller_B.pwms[i] = c_a_tmp;

    // DataTypeConversion: '<S13>/Cast'
    cascaded_controller_B.Cast[i] = c_a_tmp;
  }

  // End of MATLAB Function: '<S19>/forceToPWMCalculator'

  // DeadZone: '<S113>/DeadZone' incorporates:
  //   Gain: '<S118>/Integral Gain'

  if (cascaded_controller_B.eul_error[0] > 1.0) {
    cascaded_controller_B.psi = cascaded_controller_B.eul_error[0] - 1.0;

    // Switch: '<S111>/Switch1' incorporates:
    //   Constant: '<S111>/Constant'

    tmp = 1;
  } else {
    if (cascaded_controller_B.eul_error[0] >= -1.0) {
      cascaded_controller_B.psi = 0.0;
    } else {
      cascaded_controller_B.psi = cascaded_controller_B.eul_error[0] - -1.0;
    }

    // Switch: '<S111>/Switch1' incorporates:
    //   Constant: '<S111>/Constant2'

    tmp = -1;
  }

  // Logic: '<S111>/AND3' incorporates:
  //   Constant: '<S111>/Clamping_zero'
  //   Gain: '<S118>/Integral Gain'
  //   RelationalOperator: '<S111>/Equal1'
  //   RelationalOperator: '<S111>/Relational Operator'
  //   Switch: '<S111>/Switch1'
  //   Switch: '<S111>/Switch2'

  tf = ((cascaded_controller_B.psi != 0.0) && (tmp == -1));

  // DeadZone: '<S168>/DeadZone'
  if (cascaded_controller_B.rtb_IntegralGain_c_idx_0 > 100.0) {
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0 - 100.0;
  } else if (cascaded_controller_B.rtb_IntegralGain_c_idx_0 >= -100.0) {
    cascaded_controller_B.lower_force_index = 0.0;
  } else {
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.rtb_IntegralGain_c_idx_0 - -100.0;
  }

  // RelationalOperator: '<S166>/Relational Operator' incorporates:
  //   Constant: '<S166>/Clamping_zero'

  rtb_RelationalOperator_g_idx_0 = (cascaded_controller_B.lower_force_index !=
    0.0);

  // Switch: '<S166>/Switch1' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant'
  //   Constant: '<S166>/Constant2'
  //   RelationalOperator: '<S166>/fix for DT propagation issue'

  if (cascaded_controller_B.lower_force_index > 0.0) {
    rtb_Switch1_idx_0 = 1;
  } else {
    rtb_Switch1_idx_0 = -1;
  }

  // Gain: '<S173>/Integral Gain'
  cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 20.0 *
    cascaded_controller_B.dRb_e[0];

  // DeadZone: '<S113>/DeadZone' incorporates:
  //   Gain: '<S118>/Integral Gain'

  if (cascaded_controller_B.eul_error[1] > 1.0) {
    cascaded_controller_B.psi = cascaded_controller_B.eul_error[1] - 1.0;

    // Switch: '<S111>/Switch1' incorporates:
    //   Constant: '<S111>/Constant'

    tmp = 1;
  } else {
    if (cascaded_controller_B.eul_error[1] >= -1.0) {
      cascaded_controller_B.psi = 0.0;
    } else {
      cascaded_controller_B.psi = cascaded_controller_B.eul_error[1] - -1.0;
    }

    // Switch: '<S111>/Switch1' incorporates:
    //   Constant: '<S111>/Constant2'

    tmp = -1;
  }

  // Logic: '<S111>/AND3' incorporates:
  //   Constant: '<S111>/Clamping_zero'
  //   Gain: '<S118>/Integral Gain'
  //   RelationalOperator: '<S111>/Equal1'
  //   RelationalOperator: '<S111>/Relational Operator'
  //   Switch: '<S111>/Switch1'
  //   Switch: '<S111>/Switch2'

  rtb_RelationalOperator_f_0 = ((cascaded_controller_B.psi != 0.0) && (tmp == -1));

  // DeadZone: '<S168>/DeadZone'
  if (cascaded_controller_B.rtb_IntegralGain_c_idx_1 > 100.0) {
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.rtb_IntegralGain_c_idx_1 - 100.0;
  } else if (cascaded_controller_B.rtb_IntegralGain_c_idx_1 >= -100.0) {
    cascaded_controller_B.lower_force_index = 0.0;
  } else {
    cascaded_controller_B.lower_force_index =
      cascaded_controller_B.rtb_IntegralGain_c_idx_1 - -100.0;
  }

  // RelationalOperator: '<S166>/Relational Operator' incorporates:
  //   Constant: '<S166>/Clamping_zero'

  rtb_RelationalOperator_g_idx_1 = (cascaded_controller_B.lower_force_index !=
    0.0);

  // Switch: '<S166>/Switch1' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant'
  //   Constant: '<S166>/Constant2'
  //   RelationalOperator: '<S166>/fix for DT propagation issue'

  if (cascaded_controller_B.lower_force_index > 0.0) {
    rtb_Switch1_idx_1 = 1;
  } else {
    rtb_Switch1_idx_1 = -1;
  }

  // Gain: '<S173>/Integral Gain'
  cascaded_controller_B.rtb_IntegralGain_c_idx_1 = 20.0 *
    cascaded_controller_B.dRb_e[1];

  // DeadZone: '<S113>/DeadZone' incorporates:
  //   Gain: '<S118>/Integral Gain'

  if (cascaded_controller_B.eul_error[2] > 1.0) {
    cascaded_controller_B.psi = cascaded_controller_B.eul_error[2] - 1.0;
  } else if (cascaded_controller_B.eul_error[2] >= -1.0) {
    cascaded_controller_B.psi = 0.0;
  } else {
    cascaded_controller_B.psi = cascaded_controller_B.eul_error[2] - -1.0;
  }

  // DeadZone: '<S168>/DeadZone' incorporates:
  //   Sum: '<S185>/Sum'

  if (cascaded_controller_B.phi_b > 100.0) {
    cascaded_controller_B.lower_force_index = cascaded_controller_B.phi_b -
      100.0;
  } else if (cascaded_controller_B.phi_b >= -100.0) {
    cascaded_controller_B.lower_force_index = 0.0;
  } else {
    cascaded_controller_B.lower_force_index = cascaded_controller_B.phi_b -
      -100.0;
  }

  // RelationalOperator: '<S166>/Relational Operator' incorporates:
  //   Constant: '<S166>/Clamping_zero'

  rtb_RelationalOperator_g_idx_2 = (cascaded_controller_B.lower_force_index !=
    0.0);

  // Switch: '<S166>/Switch1' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant'
  //   Constant: '<S166>/Constant2'
  //   RelationalOperator: '<S166>/fix for DT propagation issue'

  if (cascaded_controller_B.lower_force_index > 0.0) {
    rtb_Switch1_0 = 1;
  } else {
    rtb_Switch1_0 = -1;
  }

  // Gain: '<S173>/Integral Gain'
  cascaded_controller_B.lower_force_index = 20.0 * cascaded_controller_B.dRb_e[2];

  // Update for UnitDelay: '<S16>/Delay Input1' incorporates:
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S16>/Delay Input1':
  //
  //   Store in Global RAM

  cascaded_controller_DW.DelayInput1_DSTATE =
    cascaded_controller_DW.UnitDelay_DSTATE;

  // Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read6'
  //   MATLAB Function: '<S13>/deltaQuatError'
  //
  if (integrator_reset > 0) {
    cascaded_controller_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else {
    cascaded_controller_DW.DiscreteTimeIntegrator_PrevRese = 0;
  }

  cascaded_controller_B.b_t = (1.0 - cascaded_controller_B.scale) * 0.01 +
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[0];
  cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[0] =
    cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[0] = 1.0471975511965976;
  } else if (cascaded_controller_B.b_t < -1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[0] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn'
  cascaded_controller_DW.DiscreteTransferFcn_states[0] =
    cascaded_controller_B.b_scale;

  // Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S13>/deltaQuatError'

  cascaded_controller_B.b_t = (0.0 - cascaded_controller_B.DigitalClock) * 0.01
    + cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[1];
  cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[1] =
    cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[1] = 1.0471975511965976;
  } else if (cascaded_controller_B.b_t < -1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[1] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn'
  cascaded_controller_DW.DiscreteTransferFcn_states[1] =
    cascaded_controller_B.b_absxk;

  // Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S13>/deltaQuatError'

  cascaded_controller_B.b_t = (0.0 - cascaded_controller_B.eta) * 0.01 +
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[2];
  cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[2] =
    cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[2] = 1.0471975511965976;
  } else if (cascaded_controller_B.b_t < -1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[2] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn'
  cascaded_controller_DW.DiscreteTransferFcn_states[2] =
    cascaded_controller_B.DiscreteTransferFcn_tmp_idx_2;

  // Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S13>/deltaQuatError'

  cascaded_controller_B.b_t = (0.0 - cascaded_controller_B.rtb_delta_qe_idx_2) *
    0.01 + cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[3];
  cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[3] =
    cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[3] = 1.0471975511965976;
  } else if (cascaded_controller_B.b_t < -1.0471975511965976) {
    cascaded_controller_DW.DiscreteTimeIntegrator_DSTATE[3] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S13>/Discrete Transfer Fcn'
  cascaded_controller_DW.DiscreteTransferFcn_states[3] =
    cascaded_controller_B.absxk;

  // Update for DiscreteIntegrator: '<S121>/Integrator' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read1'
  //   DiscreteIntegrator: '<S116>/Filter'
  //   DiscreteIntegrator: '<S176>/Integrator'
  //   DiscreteIntegrator: '<S61>/Filter'
  //   DiscreteIntegrator: '<S66>/Integrator'
  //
  if (integrator_reset > 0) {
    cascaded_controller_DW.Integrator_PrevResetState = 1;
    cascaded_controller_DW.Filter_PrevResetState = 1;
    cascaded_controller_DW.Integrator_PrevResetState_h = 1;
    cascaded_controller_DW.Filter_PrevResetState_e = 1;
    cascaded_controller_DW.Integrator_PrevResetState_d = 1;
  } else {
    cascaded_controller_DW.Integrator_PrevResetState = 0;
    cascaded_controller_DW.Filter_PrevResetState = 0;
    cascaded_controller_DW.Integrator_PrevResetState_h = 0;
    cascaded_controller_DW.Filter_PrevResetState_e = 0;
    cascaded_controller_DW.Integrator_PrevResetState_d = 0;
  }

  // Switch: '<S111>/Switch' incorporates:
  //   Constant: '<S111>/Constant1'
  //   Gain: '<S118>/Integral Gain'
  //   Logic: '<S111>/AND3'

  if (tf) {
    cascaded_controller_B.b_t = 0.0;
  } else {
    cascaded_controller_B.b_t = 0.0 * cascaded_controller_B.eps[0];
  }

  // Update for DiscreteIntegrator: '<S121>/Integrator' incorporates:
  //   Switch: '<S111>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.b_t +
    cascaded_controller_DW.Integrator_DSTATE[0];
  cascaded_controller_DW.Integrator_DSTATE[0] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0) {
    cascaded_controller_DW.Integrator_DSTATE[0] = 1.0;
  } else if (cascaded_controller_B.b_t < -1.0) {
    cascaded_controller_DW.Integrator_DSTATE[0] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S116>/Filter' incorporates:
  //   Gain: '<S124>/Filter Coefficient'

  cascaded_controller_DW.Filter_DSTATE[0] += 0.01 *
    cascaded_controller_B.R_error[0];

  // Switch: '<S56>/Switch1' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant'
  //   Constant: '<S56>/Constant2'
  //   RelationalOperator: '<S56>/fix for DT propagation issue'

  if (cascaded_controller_B.theta > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S56>/Switch2' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant3'
  //   Constant: '<S56>/Constant4'
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S63>/Integral Gain'
  //   RelationalOperator: '<S56>/fix for DT propagation issue1'

  if (cascaded_controller_B.eps_g[0] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S56>/Switch' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant1'
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S63>/Integral Gain'
  //   Logic: '<S56>/AND3'
  //   RelationalOperator: '<S56>/Equal1'
  //   RelationalOperator: '<S56>/Relational Operator'
  //   Switch: '<S56>/Switch1'
  //   Switch: '<S56>/Switch2'

  if ((cascaded_controller_B.theta != 0.0) && (tmp == tmp_0)) {
    cascaded_controller_B.b_t = 0.0;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.eps_g[0];
  }

  // Update for DiscreteIntegrator: '<S66>/Integrator' incorporates:
  //   Switch: '<S56>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.b_t +
    cascaded_controller_DW.Integrator_DSTATE_f[0];
  cascaded_controller_DW.Integrator_DSTATE_f[0] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[0] = 10.0;
  } else if (cascaded_controller_B.b_t < -10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[0] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S61>/Filter'
  cascaded_controller_DW.Filter_DSTATE_l[0] += 0.01 *
    cascaded_controller_B.dRb_u[0];

  // Switch: '<S166>/Switch2' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant3'
  //   Constant: '<S166>/Constant4'
  //   RelationalOperator: '<S166>/fix for DT propagation issue1'

  if (cascaded_controller_B.rtb_IntegralGain_c_idx_0 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S166>/Switch' incorporates:
  //   Constant: '<S166>/Constant1'
  //   Logic: '<S166>/AND3'
  //   RelationalOperator: '<S166>/Equal1'
  //   Switch: '<S166>/Switch2'

  if (rtb_RelationalOperator_g_idx_0 && (rtb_Switch1_idx_0 == tmp)) {
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Integrator' incorporates:
  //   Switch: '<S166>/Switch'

  cascaded_controller_B.b_t = 0.01 *
    cascaded_controller_B.rtb_IntegralGain_c_idx_0 +
    cascaded_controller_DW.Integrator_DSTATE_l[0];
  cascaded_controller_DW.Integrator_DSTATE_l[0] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[0] = 100.0;
  } else if (cascaded_controller_B.b_t < -100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[0] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S171>/Filter'
  cascaded_controller_DW.Filter_DSTATE_k[0] += 0.01 *
    cascaded_controller_B.qe_matlab_idx_3;

  // Switch: '<S111>/Switch' incorporates:
  //   Constant: '<S111>/Constant1'
  //   Gain: '<S118>/Integral Gain'
  //   Logic: '<S111>/AND3'

  if (rtb_RelationalOperator_f_0) {
    cascaded_controller_B.b_t = 0.0;
  } else {
    cascaded_controller_B.b_t = 0.0 * cascaded_controller_B.eps[1];
  }

  // Update for DiscreteIntegrator: '<S121>/Integrator' incorporates:
  //   Switch: '<S111>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.b_t +
    cascaded_controller_DW.Integrator_DSTATE[1];
  cascaded_controller_DW.Integrator_DSTATE[1] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0) {
    cascaded_controller_DW.Integrator_DSTATE[1] = 1.0;
  } else if (cascaded_controller_B.b_t < -1.0) {
    cascaded_controller_DW.Integrator_DSTATE[1] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S116>/Filter' incorporates:
  //   Gain: '<S124>/Filter Coefficient'

  cascaded_controller_DW.Filter_DSTATE[1] += 0.01 *
    cascaded_controller_B.R_error[1];

  // Switch: '<S56>/Switch1' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant'
  //   Constant: '<S56>/Constant2'
  //   RelationalOperator: '<S56>/fix for DT propagation issue'

  if (cascaded_controller_B.rtb_Integrator_o_idx_1 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S56>/Switch2' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant3'
  //   Constant: '<S56>/Constant4'
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S63>/Integral Gain'
  //   RelationalOperator: '<S56>/fix for DT propagation issue1'

  if (cascaded_controller_B.eps_g[1] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S56>/Switch' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant1'
  //   DiscreteIntegrator: '<S66>/Integrator'
  //   Gain: '<S63>/Integral Gain'
  //   Logic: '<S56>/AND3'
  //   RelationalOperator: '<S56>/Equal1'
  //   RelationalOperator: '<S56>/Relational Operator'
  //   Switch: '<S56>/Switch1'
  //   Switch: '<S56>/Switch2'

  if ((cascaded_controller_B.rtb_Integrator_o_idx_1 != 0.0) && (tmp == tmp_0)) {
    cascaded_controller_B.b_t = 0.0;
  } else {
    cascaded_controller_B.b_t = cascaded_controller_B.eps_g[1];
  }

  // Update for DiscreteIntegrator: '<S66>/Integrator' incorporates:
  //   Switch: '<S56>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.b_t +
    cascaded_controller_DW.Integrator_DSTATE_f[1];
  cascaded_controller_DW.Integrator_DSTATE_f[1] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[1] = 10.0;
  } else if (cascaded_controller_B.b_t < -10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[1] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S61>/Filter'
  cascaded_controller_DW.Filter_DSTATE_l[1] += 0.01 *
    cascaded_controller_B.dRb_u[1];

  // Switch: '<S166>/Switch2' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant3'
  //   Constant: '<S166>/Constant4'
  //   RelationalOperator: '<S166>/fix for DT propagation issue1'

  if (cascaded_controller_B.rtb_IntegralGain_c_idx_1 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S166>/Switch' incorporates:
  //   Constant: '<S166>/Constant1'
  //   Logic: '<S166>/AND3'
  //   RelationalOperator: '<S166>/Equal1'
  //   Switch: '<S166>/Switch2'

  if (rtb_RelationalOperator_g_idx_1 && (rtb_Switch1_idx_1 == tmp)) {
    cascaded_controller_B.rtb_IntegralGain_c_idx_1 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Integrator' incorporates:
  //   Switch: '<S166>/Switch'

  cascaded_controller_B.b_t = 0.01 *
    cascaded_controller_B.rtb_IntegralGain_c_idx_1 +
    cascaded_controller_DW.Integrator_DSTATE_l[1];
  cascaded_controller_DW.Integrator_DSTATE_l[1] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[1] = 100.0;
  } else if (cascaded_controller_B.b_t < -100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[1] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S171>/Filter'
  cascaded_controller_DW.Filter_DSTATE_k[1] += 0.01 *
    cascaded_controller_B.rtb_Filter_l_idx_0;

  // Switch: '<S111>/Switch1' incorporates:
  //   Constant: '<S111>/Clamping_zero'
  //   Constant: '<S111>/Constant'
  //   Constant: '<S111>/Constant2'
  //   Gain: '<S118>/Integral Gain'
  //   RelationalOperator: '<S111>/fix for DT propagation issue'

  if (cascaded_controller_B.psi > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S111>/Switch' incorporates:
  //   Constant: '<S111>/Clamping_zero'
  //   Constant: '<S111>/Constant1'
  //   Gain: '<S118>/Integral Gain'
  //   Logic: '<S111>/AND3'
  //   RelationalOperator: '<S111>/Equal1'
  //   RelationalOperator: '<S111>/Relational Operator'
  //   Switch: '<S111>/Switch1'
  //   Switch: '<S111>/Switch2'

  if ((cascaded_controller_B.psi != 0.0) && (tmp == -1)) {
    cascaded_controller_B.b_t = 0.0;
  } else {
    cascaded_controller_B.b_t = 0.0 * cascaded_controller_B.eps[2];
  }

  // Update for DiscreteIntegrator: '<S121>/Integrator' incorporates:
  //   Switch: '<S111>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.b_t +
    cascaded_controller_DW.Integrator_DSTATE[2];
  cascaded_controller_DW.Integrator_DSTATE[2] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 1.0) {
    cascaded_controller_DW.Integrator_DSTATE[2] = 1.0;
  } else if (cascaded_controller_B.b_t < -1.0) {
    cascaded_controller_DW.Integrator_DSTATE[2] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S116>/Filter' incorporates:
  //   Gain: '<S124>/Filter Coefficient'

  cascaded_controller_DW.Filter_DSTATE[2] += 0.01 *
    cascaded_controller_B.R_error[2];

  // Switch: '<S56>/Switch1' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant'
  //   Constant: '<S56>/Constant2'
  //   RelationalOperator: '<S56>/fix for DT propagation issue'

  if (cascaded_controller_B.rtb_Integrator_o_idx_2 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S56>/Switch2' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant3'
  //   Constant: '<S56>/Constant4'
  //   Gain: '<S71>/Proportional Gain'
  //   RelationalOperator: '<S56>/fix for DT propagation issue1'

  if (cascaded_controller_B.phi > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S56>/Switch' incorporates:
  //   Constant: '<S56>/Clamping_zero'
  //   Constant: '<S56>/Constant1'
  //   Logic: '<S56>/AND3'
  //   RelationalOperator: '<S56>/Equal1'
  //   RelationalOperator: '<S56>/Relational Operator'
  //   Switch: '<S56>/Switch1'
  //   Switch: '<S56>/Switch2'

  if ((cascaded_controller_B.rtb_Integrator_o_idx_2 != 0.0) && (tmp == tmp_0)) {
    cascaded_controller_B.phi = 0.0;
  }

  // Update for DiscreteIntegrator: '<S66>/Integrator' incorporates:
  //   Switch: '<S56>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.phi +
    cascaded_controller_DW.Integrator_DSTATE_f[2];
  cascaded_controller_DW.Integrator_DSTATE_f[2] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[2] = 10.0;
  } else if (cascaded_controller_B.b_t < -10.0) {
    cascaded_controller_DW.Integrator_DSTATE_f[2] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S61>/Filter' incorporates:
  //   Gain: '<S69>/Filter Coefficient'

  cascaded_controller_DW.Filter_DSTATE_l[2] += 0.01 *
    cascaded_controller_B.rotm_tmp;

  // Switch: '<S166>/Switch2' incorporates:
  //   Constant: '<S166>/Clamping_zero'
  //   Constant: '<S166>/Constant3'
  //   Constant: '<S166>/Constant4'
  //   Gain: '<S173>/Integral Gain'
  //   RelationalOperator: '<S166>/fix for DT propagation issue1'

  if (cascaded_controller_B.lower_force_index > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S166>/Switch' incorporates:
  //   Constant: '<S166>/Constant1'
  //   Logic: '<S166>/AND3'
  //   RelationalOperator: '<S166>/Equal1'
  //   Switch: '<S166>/Switch1'
  //   Switch: '<S166>/Switch2'

  if (rtb_RelationalOperator_g_idx_2 && (rtb_Switch1_0 == tmp)) {
    cascaded_controller_B.lower_force_index = 0.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Integrator' incorporates:
  //   Switch: '<S166>/Switch'

  cascaded_controller_B.b_t = 0.01 * cascaded_controller_B.lower_force_index +
    cascaded_controller_DW.Integrator_DSTATE_l[2];
  cascaded_controller_DW.Integrator_DSTATE_l[2] = cascaded_controller_B.b_t;
  if (cascaded_controller_B.b_t > 100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[2] = 100.0;
  } else if (cascaded_controller_B.b_t < -100.0) {
    cascaded_controller_DW.Integrator_DSTATE_l[2] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S171>/Filter' incorporates:
  //   DataStoreRead: '<S13>/Data Store Read9'
  //   Gain: '<S179>/Filter Coefficient'
  //
  cascaded_controller_DW.Filter_DSTATE_k[2] += 0.01 * cascaded_controller_B.a_o;
  if (integrator_reset > 0) {
    cascaded_controller_DW.Filter_PrevResetState_a = 1;
  } else {
    cascaded_controller_DW.Filter_PrevResetState_a = 0;
  }

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // DataStoreWrite: '<S5>/Data Store Write' incorporates:
  //   MATLABSystem: '<S196>/SourceBlock'
  //
  cascaded_controller_DW.start_new_cmd_flag = b_varargout_1;

  // MATLAB Function: '<S5>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<S5>/Data Store Write1'
  //   MATLABSystem: '<S196>/SourceBlock'
  //
  cascaded_controller_DW.start_new_mission_flag_a = ((!b_varargout_1) &&
    cascaded_controller_DW.start_new_mission_flag_a);
  cascaded_controller_DW.start_new_mission_flag =
    cascaded_controller_DW.start_new_mission_flag_a;

  // MATLAB Function: '<S5>/statusKwdToBool' incorporates:
  //   UnitDelay: '<S5>/Unit Delay'

  switch_expression[0] = cascaded_controller_DW.UnitDelay_DSTATE_k[0];
  switch_expression[1] = cascaded_controller_DW.UnitDelay_DSTATE_k[1];
  switch_expression[2] = cascaded_controller_DW.UnitDelay_DSTATE_k[2];
  switch_expression[3] = cascaded_controller_DW.UnitDelay_DSTATE_k[3];
  i = std::memcmp(&a[0], &switch_expression[0], 4);
  if (i == 0) {
    c_a_tmp = 0;
  } else {
    i = std::memcmp(&b_a[0], &switch_expression[0], 4);
    if (i == 0) {
      c_a_tmp = 1;
    } else {
      i = std::memcmp(&c_a_0[0], &switch_expression[0], 4);
      if (i == 0) {
        c_a_tmp = 2;
      } else {
        c_a_tmp = -1;
      }
    }
  }

  switch (c_a_tmp) {
   case 0:
    cascaded_controller_B.result_msg.success = true;
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.result_msg.found_object[i] = b_0[i];
    }

    cascaded_controller_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S5>/Subsystem' incorporates:
    //   EnablePort: '<S197>/Enable'

    // MATLABSystem: '<S201>/SinkBlock'
    Pub_cascaded_controller_108_8.publish(&cascaded_controller_B.result_msg);

    // End of Outputs for SubSystem: '<S5>/Subsystem'
    break;

   case 1:
    cascaded_controller_B.result_msg.success = false;
    for (i = 0; i < 16; i++) {
      cascaded_controller_B.result_msg.found_object[i] = b_0[i];
    }

    cascaded_controller_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S5>/Subsystem' incorporates:
    //   EnablePort: '<S197>/Enable'

    // MATLABSystem: '<S201>/SinkBlock'
    Pub_cascaded_controller_108_8.publish(&cascaded_controller_B.result_msg);

    // End of Outputs for SubSystem: '<S5>/Subsystem'
    break;

   case 2:
    break;
  }

  // End of MATLAB Function: '<S5>/statusKwdToBool'

  // BusCreator: '<S7>/Bus Creator3'
  for (i = 0; i < 8; i++) {
    cascaded_controller_B.BusCreator3.pwms[i] = cascaded_controller_B.Cast[i];
  }

  // End of BusCreator: '<S7>/Bus Creator3'

  // MATLABSystem: '<S204>/SinkBlock'
  Pub_cascaded_controller_38_2.publish(&cascaded_controller_B.BusCreator3);
  if ((&cascaded_controller_M)->Timing.TaskCounters.TID[1] == 0) {
    // MATLABSystem: '<S203>/SinkBlock' incorporates:
    //   Constant: '<S202>/Constant'

    Pub_cascaded_controller_37_150.publish
      (&cascaded_controller_ConstP.Constant_Value);
  }

  // Update for DiscreteIntegrator: '<S9>/Position Integrator' incorporates:
  //   MATLABSystem: '<S1>/SourceBlock'
  //
  cascaded_controller_DW.PositionIntegrator_IC_LOADING = 0U;
  if (b_varargout_1_1) {
    cascaded_controller_DW.PositionIntegrator_PrevResetSta = 1;
  } else {
    cascaded_controller_DW.PositionIntegrator_PrevResetSta = 0;
  }

  // Update for DiscreteIntegrator: '<S9>/Velocity Integrator'
  cascaded_controller_DW.VelocityIntegrator_IC_LOADING = 0U;

  // Update for DiscreteIntegrator: '<S9>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S9>/Velocity Integrator'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_DW.PositionIntegrator_DSTATE[0] += 0.01 *
    cascaded_controller_DW.VelocityIntegrator_DSTATE[0];

  // Update for DiscreteIntegrator: '<S9>/Velocity Integrator' incorporates:
  //   Sum: '<S9>/Sum'

  cascaded_controller_DW.VelocityIntegrator_DSTATE[0] += 0.01 *
    cascaded_controller_B.rtb_dvl_pos_g[0];

  // Update for DiscreteIntegrator: '<S9>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S9>/Velocity Integrator'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_DW.PositionIntegrator_DSTATE[1] += 0.01 *
    cascaded_controller_DW.VelocityIntegrator_DSTATE[1];

  // Update for DiscreteIntegrator: '<S9>/Velocity Integrator' incorporates:
  //   Sum: '<S9>/Sum'

  cascaded_controller_DW.VelocityIntegrator_DSTATE[1] += 0.01 *
    cascaded_controller_B.rtb_dvl_pos_g[1];

  // Update for DiscreteIntegrator: '<S9>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S9>/Velocity Integrator'
  //   MATLAB Function: '<S9>/derivedStateEstimates'

  cascaded_controller_DW.PositionIntegrator_DSTATE[2] += 0.01 *
    cascaded_controller_DW.VelocityIntegrator_DSTATE[2];

  // Update for DiscreteIntegrator: '<S9>/Velocity Integrator' incorporates:
  //   MATLABSystem: '<S3>/SourceBlock'
  //   Sum: '<S9>/Sum'
  //
  cascaded_controller_DW.VelocityIntegrator_DSTATE[2] += 0.01 *
    cascaded_controller_B.rtb_dvl_pos_g[2];
  if (b_varargout_1_0) {
    cascaded_controller_DW.VelocityIntegrator_PrevResetSta = 1;
  } else {
    cascaded_controller_DW.VelocityIntegrator_PrevResetSta = 0;
  }

  // Update for UnitDelay: '<S5>/Unit Delay'
  cascaded_controller_DW.UnitDelay_DSTATE_k[0] = rtb_cmd_status[0];
  cascaded_controller_DW.UnitDelay_DSTATE_k[1] = rtb_cmd_status[1];
  cascaded_controller_DW.UnitDelay_DSTATE_k[2] = rtb_cmd_status[2];
  cascaded_controller_DW.UnitDelay_DSTATE_k[3] = rtb_cmd_status[3];

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&cascaded_controller_M)->Timing.clockTick0++;
  rate_scheduler((&cascaded_controller_M));
}

// Model initialize function
void cascaded_controller::initialize()
{
  // Start for DataStoreMemory: '<Root>/Data Store Memory'
  cascaded_controller_DW.start_new_mission_flag = true;

  // InitializeConditions for DiscreteIntegrator: '<S9>/Position Integrator'
  cascaded_controller_DW.PositionIntegrator_PrevResetSta = 2;
  cascaded_controller_DW.PositionIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S9>/Velocity Integrator'
  cascaded_controller_DW.VelocityIntegrator_PrevResetSta = 2;
  cascaded_controller_DW.VelocityIntegrator_IC_LOADING = 1U;

  // SystemInitialize for MATLAB Function: '<S9>/dvl_reset'
  cascaded_controller_DW.prior_flag = true;

  // SystemInitialize for Enabled SubSystem: '<S4>/cascaded_pid_controller_cgn'
  // Start for DataStoreMemory: '<S13>/Data Store Memory2'
  cascaded_controller_DW.qib[0] = 0.0;
  cascaded_controller_DW.qib[1] = 0.0;
  cascaded_controller_DW.qib[2] = 0.0;
  cascaded_controller_DW.qib[3] = 1.0;

  // InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator' 
  cascaded_controller_DW.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S121>/Integrator'
  cascaded_controller_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S116>/Filter'
  cascaded_controller_DW.Filter_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S66>/Integrator'
  cascaded_controller_DW.Integrator_PrevResetState_h = 2;

  // InitializeConditions for DiscreteIntegrator: '<S61>/Filter'
  cascaded_controller_DW.Filter_PrevResetState_e = 2;

  // InitializeConditions for DiscreteIntegrator: '<S176>/Integrator'
  cascaded_controller_DW.Integrator_PrevResetState_d = 2;

  // InitializeConditions for DiscreteIntegrator: '<S171>/Filter'
  cascaded_controller_DW.Filter_PrevResetState_a = 2;

  // End of SystemInitialize for SubSystem: '<S4>/cascaded_pid_controller_cgn'

  // SystemInitialize for MATLAB Function: '<S5>/MATLAB Function'
  cascaded_controller_DW.start_new_mission_flag_a = true;

  // SystemInitialize for Enabled SubSystem: '<S5>/Subsystem'
  // Start for MATLABSystem: '<S201>/SinkBlock'
  cascaded_controller_DW.obj_i.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_i.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_i.isSetupComplete = false;
  cascaded_controller_DW.obj_i.isInitialized = 1;
  cascaded_co_Publisher_setupImpl(&cascaded_controller_DW.obj_i);
  cascaded_controller_DW.obj_i.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S5>/Subsystem'

  // Start for MATLABSystem: '<S196>/SourceBlock'
  cascaded_controller_DW.obj.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj.isSetupComplete = false;
  cascaded_controller_DW.obj.isInitialized = 1;
  cascad_Subscriber_setupImpl_dsx(&cascaded_controller_DW.obj);
  cascaded_controller_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  cascaded_controller_DW.obj_e3.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_e3.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_e3.isSetupComplete = false;
  cascaded_controller_DW.obj_e3.isInitialized = 1;
  cascaded_Subscriber_setupImpl_d(&cascaded_controller_DW.obj_e3);
  cascaded_controller_DW.obj_e3.isSetupComplete = true;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  cascaded_controller_DW.obj_e.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_e.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_e.isSetupComplete = false;
  cascaded_controller_DW.obj_e.isInitialized = 1;
  cascade_Subscriber_setupImpl_ds(&cascaded_controller_DW.obj_e);
  cascaded_controller_DW.obj_e.isSetupComplete = true;

  // Start for MATLABSystem: '<S1>/SourceBlock'
  cascaded_controller_DW.obj_d.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_d.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_d.isSetupComplete = false;
  cascaded_controller_DW.obj_d.isInitialized = 1;
  cascaded_c_Subscriber_setupImpl(&cascaded_controller_DW.obj_d);
  cascaded_controller_DW.obj_d.isSetupComplete = true;

  // Start for MATLABSystem: '<S204>/SinkBlock'
  cascaded_controller_DW.obj_f.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_f.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_f.isSetupComplete = false;
  cascaded_controller_DW.obj_f.isInitialized = 1;
  cascaded_Publisher_setupImpl_ds(&cascaded_controller_DW.obj_f);
  cascaded_controller_DW.obj_f.isSetupComplete = true;

  // Start for MATLABSystem: '<S203>/SinkBlock'
  cascaded_controller_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
  cascaded_controller_DW.obj_o.matlabCodegenIsDeleted = false;
  cascaded_controller_DW.obj_o.isSetupComplete = false;
  cascaded_controller_DW.obj_o.isInitialized = 1;
  cascaded__Publisher_setupImpl_d(&cascaded_controller_DW.obj_o);
  cascaded_controller_DW.obj_o.isSetupComplete = true;
}

// Model terminate function
void cascaded_controller::terminate()
{
  // Terminate for MATLABSystem: '<S196>/SourceBlock'
  if (!cascaded_controller_DW.obj.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj.isInitialized == 1) &&
        cascaded_controller_DW.obj.isSetupComplete) {
      Sub_cascaded_controller_108_4.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S196>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!cascaded_controller_DW.obj_e3.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_e3.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_e3.isInitialized == 1) &&
        cascaded_controller_DW.obj_e3.isSetupComplete) {
      Sub_cascaded_controller_8.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!cascaded_controller_DW.obj_e.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_e.isInitialized == 1) &&
        cascaded_controller_DW.obj_e.isSetupComplete) {
      Sub_cascaded_controller_20.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S1>/SourceBlock'
  if (!cascaded_controller_DW.obj_d.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_d.isInitialized == 1) &&
        cascaded_controller_DW.obj_d.isSetupComplete) {
      Sub_cascaded_controller_3.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S5>/Subsystem'
  // Terminate for MATLABSystem: '<S201>/SinkBlock'
  if (!cascaded_controller_DW.obj_i.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_i.isInitialized == 1) &&
        cascaded_controller_DW.obj_i.isSetupComplete) {
      Pub_cascaded_controller_108_8.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S201>/SinkBlock'
  // End of Terminate for SubSystem: '<S5>/Subsystem'

  // Terminate for MATLABSystem: '<S204>/SinkBlock'
  if (!cascaded_controller_DW.obj_f.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_f.isInitialized == 1) &&
        cascaded_controller_DW.obj_f.isSetupComplete) {
      Pub_cascaded_controller_38_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S204>/SinkBlock'

  // Terminate for MATLABSystem: '<S203>/SinkBlock'
  if (!cascaded_controller_DW.obj_o.matlabCodegenIsDeleted) {
    cascaded_controller_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((cascaded_controller_DW.obj_o.isInitialized == 1) &&
        cascaded_controller_DW.obj_o.isSetupComplete) {
      Pub_cascaded_controller_37_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S203>/SinkBlock'
}

// Constructor
cascaded_controller::cascaded_controller() :
  cascaded_controller_B(),
  cascaded_controller_DW(),
  cascaded_controller_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
cascaded_controller::~cascaded_controller() = default;

// Real-Time Model get method
RT_MODEL_cascaded_controller_T * cascaded_controller::getRTM()
{
  return (&cascaded_controller_M);
}

const char_T* RT_MODEL_cascaded_controller_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_cascaded_controller_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
