//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Mission_Manager_CGN.cpp
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
#include "Mission_Manager_CGN.h"
#include "Mission_Manager_CGN_types.h"
#include "rtwtypes.h"
#include <cmath>
#include <emmintrin.h>
#include <cstring>
#include "rmw/qos_profiles.h"
#include <stddef.h>
#include "rt_defines.h"
#include "Mission_Manager_CGN_private.h"
#include "cmath"

static void rate_scheduler(RT_MODEL_Mission_Manager_CGN_T *const
  Mission_Manager_CGN_M);

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(RT_MODEL_Mission_Manager_CGN_T *const
  Mission_Manager_CGN_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (Mission_Manager_CGN_M->Timing.TaskCounters.TID[1])++;
  if ((Mission_Manager_CGN_M->Timing.TaskCounters.TID[1]) > 49) {// Sample time: [0.5s, 0.0s] 
    Mission_Manager_CGN_M->Timing.TaskCounters.TID[1] = 0;
  }
}

real_T Mission_Manager_CGN::Mission_Manager_C_rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    if (u0 > 0.0) {
      Mission_Manager_CGN_B.i2 = 1;
    } else {
      Mission_Manager_CGN_B.i2 = -1;
    }

    if (u1 > 0.0) {
      Mission_Manager_CGN_B.i3 = 1;
    } else {
      Mission_Manager_CGN_B.i3 = -1;
    }

    y = std::atan2(static_cast<real_T>(Mission_Manager_CGN_B.i2),
                   static_cast<real_T>(Mission_Manager_CGN_B.i3));
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

// Function for MATLAB Function: '<S18>/guidanceLaw'
void Mission_Manager_CGN::Mission_Manager_CGN_wrapToPi(real_T *lambda)
{
  Mission_Manager_CGN_B.trueCount = 0;
  Mission_Manager_CGN_B.b_l = ((*lambda < -3.1415926535897931) || (*lambda >
    3.1415926535897931));
  if (Mission_Manager_CGN_B.b_l) {
    for (Mission_Manager_CGN_B.i_i = 0; Mission_Manager_CGN_B.i_i < 1;
         Mission_Manager_CGN_B.i_i++) {
      Mission_Manager_CGN_B.trueCount++;
    }
  }

  if (Mission_Manager_CGN_B.trueCount - 1 >= 0) {
    if (std::isnan(*lambda + 3.1415926535897931)) {
      Mission_Manager_CGN_B.q_h = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      Mission_Manager_CGN_B.q_h = (rtNaN);
    } else {
      Mission_Manager_CGN_B.q_h = std::abs((*lambda + 3.1415926535897931) /
        6.2831853071795862);
      if (std::abs(Mission_Manager_CGN_B.q_h - std::floor
                   (Mission_Manager_CGN_B.q_h + 0.5)) > 2.2204460492503131E-16 *
          Mission_Manager_CGN_B.q_h) {
        Mission_Manager_CGN_B.q_h = std::fmod(*lambda + 3.1415926535897931,
          6.2831853071795862);
      } else {
        Mission_Manager_CGN_B.q_h = 0.0;
      }

      if (Mission_Manager_CGN_B.q_h == 0.0) {
        Mission_Manager_CGN_B.q_h = 0.0;
      } else if (Mission_Manager_CGN_B.q_h < 0.0) {
        Mission_Manager_CGN_B.q_h += 6.2831853071795862;
      }
    }

    Mission_Manager_CGN_B.varargin_1_data = Mission_Manager_CGN_B.q_h;
  }

  for (Mission_Manager_CGN_B.i_i = 0; Mission_Manager_CGN_B.i_i <
       Mission_Manager_CGN_B.trueCount; Mission_Manager_CGN_B.i_i++) {
    Mission_Manager_CGN_B.i1 = 0;
    if ((Mission_Manager_CGN_B.varargin_1_data == 0.0) && (*lambda +
         3.1415926535897931 > 0.0)) {
      Mission_Manager_CGN_B.varargin_1_data = 6.2831853071795862;
    }
  }

  if (Mission_Manager_CGN_B.b_l) {
    *lambda = Mission_Manager_CGN_B.varargin_1_data - 3.1415926535897931;
  }
}

// Function for MATLAB Function: '<S19>/commandExecuter'
void Mission_Manager_CGN::Mission_Manager_CGN_eulToQuat_k(const real_T Eul[3],
  real_T qib[4])
{
  Mission_Manager_CGN_B.eta_d = std::cos(Eul[1]);
  Mission_Manager_CGN_B.scale_l = std::sin(Eul[1]);
  Mission_Manager_CGN_B.b_t_b = std::cos(Eul[2]);
  Mission_Manager_CGN_B.rotm_tmp = std::sin(Eul[2]);
  Mission_Manager_CGN_B.eps_idx_1 = std::sin(Eul[0]);
  Mission_Manager_CGN_B.rotm_tmp_n = std::cos(Eul[0]);
  Mission_Manager_CGN_B.rotm_idx_0 = Mission_Manager_CGN_B.eta_d *
    Mission_Manager_CGN_B.b_t_b;
  Mission_Manager_CGN_B.eps_idx_2 = Mission_Manager_CGN_B.eta_d *
    Mission_Manager_CGN_B.rotm_tmp;
  Mission_Manager_CGN_B.rotm_idx_4_tmp = Mission_Manager_CGN_B.eps_idx_1 *
    Mission_Manager_CGN_B.scale_l;
  Mission_Manager_CGN_B.eps_idx_0 = Mission_Manager_CGN_B.rotm_idx_4_tmp *
    Mission_Manager_CGN_B.rotm_tmp + Mission_Manager_CGN_B.rotm_tmp_n *
    Mission_Manager_CGN_B.b_t_b;
  Mission_Manager_CGN_B.absxk_o = Mission_Manager_CGN_B.eps_idx_1 *
    Mission_Manager_CGN_B.eta_d;
  Mission_Manager_CGN_B.rotm_idx_8 = Mission_Manager_CGN_B.rotm_tmp_n *
    Mission_Manager_CGN_B.eta_d;
  Mission_Manager_CGN_B.eta_d = std::sqrt(((Mission_Manager_CGN_B.rotm_idx_0 +
    Mission_Manager_CGN_B.eps_idx_0) + Mission_Manager_CGN_B.rotm_idx_8) + 1.0) /
    2.0;
  if (Mission_Manager_CGN_B.eta_d != 0.0) {
    Mission_Manager_CGN_B.rotm_idx_0 = Mission_Manager_CGN_B.rotm_tmp_n *
      Mission_Manager_CGN_B.scale_l;
    Mission_Manager_CGN_B.rotm_idx_8 = 4.0 * Mission_Manager_CGN_B.eta_d;
    Mission_Manager_CGN_B.eps_idx_0 = (Mission_Manager_CGN_B.absxk_o -
      (Mission_Manager_CGN_B.rotm_idx_0 * Mission_Manager_CGN_B.rotm_tmp -
       Mission_Manager_CGN_B.eps_idx_1 * Mission_Manager_CGN_B.b_t_b)) /
      Mission_Manager_CGN_B.rotm_idx_8;
    Mission_Manager_CGN_B.eps_idx_1 = ((Mission_Manager_CGN_B.rotm_idx_0 *
      Mission_Manager_CGN_B.b_t_b + Mission_Manager_CGN_B.eps_idx_1 *
      Mission_Manager_CGN_B.rotm_tmp) - (-Mission_Manager_CGN_B.scale_l)) /
      Mission_Manager_CGN_B.rotm_idx_8;
    Mission_Manager_CGN_B.eps_idx_2 = (Mission_Manager_CGN_B.eps_idx_2 -
      (Mission_Manager_CGN_B.rotm_idx_4_tmp * Mission_Manager_CGN_B.b_t_b -
       Mission_Manager_CGN_B.rotm_tmp_n * Mission_Manager_CGN_B.rotm_tmp)) /
      Mission_Manager_CGN_B.rotm_idx_8;
  } else {
    Mission_Manager_CGN_B.b_t_b = (Mission_Manager_CGN_B.rotm_idx_0 + 1.0) / 2.0;
    Mission_Manager_CGN_B.x[0] = Mission_Manager_CGN_B.b_t_b;
    Mission_Manager_CGN_B.eps_idx_1 = (Mission_Manager_CGN_B.eps_idx_0 + 1.0) /
      2.0;
    Mission_Manager_CGN_B.x[1] = Mission_Manager_CGN_B.eps_idx_1;
    Mission_Manager_CGN_B.rotm_tmp = (Mission_Manager_CGN_B.rotm_idx_8 + 1.0) /
      2.0;
    Mission_Manager_CGN_B.x[2] = Mission_Manager_CGN_B.rotm_tmp;
    if (!std::isnan(Mission_Manager_CGN_B.b_t_b)) {
      Mission_Manager_CGN_B.idx = 1;
    } else {
      boolean_T exitg1;
      Mission_Manager_CGN_B.idx = 0;
      Mission_Manager_CGN_B.b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (Mission_Manager_CGN_B.b_k < 4)) {
        if (!std::isnan(Mission_Manager_CGN_B.x[Mission_Manager_CGN_B.b_k - 1]))
        {
          Mission_Manager_CGN_B.idx = Mission_Manager_CGN_B.b_k;
          exitg1 = true;
        } else {
          Mission_Manager_CGN_B.b_k++;
        }
      }
    }

    if (Mission_Manager_CGN_B.idx == 0) {
      Mission_Manager_CGN_B.b_k = 1;
    } else {
      Mission_Manager_CGN_B.eps_idx_0 =
        Mission_Manager_CGN_B.x[Mission_Manager_CGN_B.idx - 1];
      Mission_Manager_CGN_B.b_k = Mission_Manager_CGN_B.idx;
      for (Mission_Manager_CGN_B.c_k = Mission_Manager_CGN_B.idx + 1;
           Mission_Manager_CGN_B.c_k < 4; Mission_Manager_CGN_B.c_k++) {
        Mission_Manager_CGN_B.rotm_tmp_n =
          Mission_Manager_CGN_B.x[Mission_Manager_CGN_B.c_k - 1];
        if (Mission_Manager_CGN_B.eps_idx_0 < Mission_Manager_CGN_B.rotm_tmp_n)
        {
          Mission_Manager_CGN_B.eps_idx_0 = Mission_Manager_CGN_B.rotm_tmp_n;
          Mission_Manager_CGN_B.b_k = Mission_Manager_CGN_B.c_k;
        }
      }
    }

    switch (Mission_Manager_CGN_B.b_k) {
     case 1:
      Mission_Manager_CGN_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_b));
      if (std::isnan(Mission_Manager_CGN_B.eps_idx_2)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (Mission_Manager_CGN_B.eps_idx_2 < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (Mission_Manager_CGN_B.eps_idx_2 >
          0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1)) * Mission_Manager_CGN_B.rotm_tmp_n;
      if (std::isnan(-Mission_Manager_CGN_B.scale_l)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (-Mission_Manager_CGN_B.scale_l < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (-Mission_Manager_CGN_B.scale_l > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp)) * Mission_Manager_CGN_B.rotm_tmp_n;
      break;

     case 2:
      Mission_Manager_CGN_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1));
      if (std::isnan(Mission_Manager_CGN_B.eps_idx_2)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (Mission_Manager_CGN_B.eps_idx_2 < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (Mission_Manager_CGN_B.eps_idx_2 >
          0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_b)) * Mission_Manager_CGN_B.rotm_tmp_n;
      if (std::isnan(Mission_Manager_CGN_B.absxk_o)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (Mission_Manager_CGN_B.absxk_o < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (Mission_Manager_CGN_B.absxk_o > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp)) * Mission_Manager_CGN_B.rotm_tmp_n;
      break;

     default:
      Mission_Manager_CGN_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp));
      if (std::isnan(-Mission_Manager_CGN_B.scale_l)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (-Mission_Manager_CGN_B.scale_l < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (-Mission_Manager_CGN_B.scale_l > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_b)) * Mission_Manager_CGN_B.rotm_tmp_n;
      if (std::isnan(Mission_Manager_CGN_B.absxk_o)) {
        Mission_Manager_CGN_B.rotm_tmp_n = (rtNaN);
      } else if (Mission_Manager_CGN_B.absxk_o < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_n = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_n = (Mission_Manager_CGN_B.absxk_o > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1)) * Mission_Manager_CGN_B.rotm_tmp_n;
      break;
    }
  }

  Mission_Manager_CGN_B.scale_l = 3.3121686421112381E-170;
  Mission_Manager_CGN_B.absxk_o = std::abs(Mission_Manager_CGN_B.eps_idx_0);
  if (Mission_Manager_CGN_B.absxk_o > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.rotm_tmp = 1.0;
    Mission_Manager_CGN_B.scale_l = Mission_Manager_CGN_B.absxk_o;
  } else {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.absxk_o /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.rotm_tmp = Mission_Manager_CGN_B.b_t_b *
      Mission_Manager_CGN_B.b_t_b;
  }

  Mission_Manager_CGN_B.absxk_o = std::abs(Mission_Manager_CGN_B.eps_idx_1);
  if (Mission_Manager_CGN_B.absxk_o > Mission_Manager_CGN_B.scale_l) {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.scale_l /
      Mission_Manager_CGN_B.absxk_o;
    Mission_Manager_CGN_B.rotm_tmp = Mission_Manager_CGN_B.rotm_tmp *
      Mission_Manager_CGN_B.b_t_b * Mission_Manager_CGN_B.b_t_b + 1.0;
    Mission_Manager_CGN_B.scale_l = Mission_Manager_CGN_B.absxk_o;
  } else {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.absxk_o /
      Mission_Manager_CGN_B.scale_l;
    Mission_Manager_CGN_B.rotm_tmp += Mission_Manager_CGN_B.b_t_b *
      Mission_Manager_CGN_B.b_t_b;
  }

  Mission_Manager_CGN_B.absxk_o = std::abs(Mission_Manager_CGN_B.eps_idx_2);
  if (Mission_Manager_CGN_B.absxk_o > Mission_Manager_CGN_B.scale_l) {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.scale_l /
      Mission_Manager_CGN_B.absxk_o;
    Mission_Manager_CGN_B.rotm_tmp = Mission_Manager_CGN_B.rotm_tmp *
      Mission_Manager_CGN_B.b_t_b * Mission_Manager_CGN_B.b_t_b + 1.0;
    Mission_Manager_CGN_B.scale_l = Mission_Manager_CGN_B.absxk_o;
  } else {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.absxk_o /
      Mission_Manager_CGN_B.scale_l;
    Mission_Manager_CGN_B.rotm_tmp += Mission_Manager_CGN_B.b_t_b *
      Mission_Manager_CGN_B.b_t_b;
  }

  if (Mission_Manager_CGN_B.eta_d > Mission_Manager_CGN_B.scale_l) {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.scale_l /
      Mission_Manager_CGN_B.eta_d;
    Mission_Manager_CGN_B.rotm_tmp = Mission_Manager_CGN_B.rotm_tmp *
      Mission_Manager_CGN_B.b_t_b * Mission_Manager_CGN_B.b_t_b + 1.0;
    Mission_Manager_CGN_B.scale_l = Mission_Manager_CGN_B.eta_d;
  } else {
    Mission_Manager_CGN_B.b_t_b = Mission_Manager_CGN_B.eta_d /
      Mission_Manager_CGN_B.scale_l;
    Mission_Manager_CGN_B.rotm_tmp += Mission_Manager_CGN_B.b_t_b *
      Mission_Manager_CGN_B.b_t_b;
  }

  Mission_Manager_CGN_B.rotm_tmp = Mission_Manager_CGN_B.scale_l * std::sqrt
    (Mission_Manager_CGN_B.rotm_tmp);
  qib[0] = Mission_Manager_CGN_B.eps_idx_0 / Mission_Manager_CGN_B.rotm_tmp;
  qib[1] = Mission_Manager_CGN_B.eps_idx_1 / Mission_Manager_CGN_B.rotm_tmp;
  qib[2] = Mission_Manager_CGN_B.eps_idx_2 / Mission_Manager_CGN_B.rotm_tmp;
  qib[3] = Mission_Manager_CGN_B.eta_d / Mission_Manager_CGN_B.rotm_tmp;
}

// Function for MATLAB Function: '<S19>/commandExecuter'
void Mission_Manager_CGN::Mission_Ma_executeDurationTrick(real_T cmd_hold_time,
  const int8_T cmd_trick_id[16], const real_T idle_wp[6], const real_T X_Ri[3],
  const real_T X_Eul[3], const real_T X_Cib[9], real_T *hold_timer_start_time,
  real_T t, boolean_T new_cmd_reset, real_T cmd_specific_wp[6], int8_T
  cmd_status[4], real_T *hold_timer, real_T X_u[13])
{
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

  __m128d tmp;
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
  for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 16;
       Mission_Manager_CGN_B.c_ret++) {
    Mission_Manager_CGN_B.b.f1[Mission_Manager_CGN_B.c_ret] =
      rb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.c.f1[Mission_Manager_CGN_B.c_ret] =
      sb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.d.f1[Mission_Manager_CGN_B.c_ret] =
      tb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.e.f1[Mission_Manager_CGN_B.c_ret] =
      ub[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.f.f1[Mission_Manager_CGN_B.c_ret] =
      vb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.g.f1[Mission_Manager_CGN_B.c_ret] =
      wb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.h.f1[Mission_Manager_CGN_B.c_ret] =
      xb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.i.f1[Mission_Manager_CGN_B.c_ret] =
      yb[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.j.f1[Mission_Manager_CGN_B.c_ret] =
      ac[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.k.f1[Mission_Manager_CGN_B.c_ret] =
      bc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.l.f1[Mission_Manager_CGN_B.c_ret] =
      cc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.m.f1[Mission_Manager_CGN_B.c_ret] =
      dc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.n.f1[Mission_Manager_CGN_B.c_ret] =
      ec[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.o.f1[Mission_Manager_CGN_B.c_ret] =
      fc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.p.f1[Mission_Manager_CGN_B.c_ret] =
      gc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.q.f1[Mission_Manager_CGN_B.c_ret] =
      hc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.r.f1[Mission_Manager_CGN_B.c_ret] =
      ic[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.s.f1[Mission_Manager_CGN_B.c_ret] =
      jc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.u.f1[Mission_Manager_CGN_B.c_ret] =
      kc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.v.f1[Mission_Manager_CGN_B.c_ret] =
      lc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.w.f1[Mission_Manager_CGN_B.c_ret] =
      mc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.x_j.f1[Mission_Manager_CGN_B.c_ret] =
      nc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.y.f1[Mission_Manager_CGN_B.c_ret] =
      oc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.ab.f1[Mission_Manager_CGN_B.c_ret] =
      pc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.bb.f1[Mission_Manager_CGN_B.c_ret] =
      qc[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.cb.f1[Mission_Manager_CGN_B.c_ret] =
      rc[Mission_Manager_CGN_B.c_ret];
  }

  Mission_Manager_CGN_B.varargin_1[0] = Mission_Manager_CGN_B.b;
  Mission_Manager_CGN_B.varargin_1[1] = Mission_Manager_CGN_B.c;
  Mission_Manager_CGN_B.varargin_1[2] = Mission_Manager_CGN_B.d;
  Mission_Manager_CGN_B.varargin_1[3] = Mission_Manager_CGN_B.e;
  Mission_Manager_CGN_B.varargin_1[4] = Mission_Manager_CGN_B.f;
  Mission_Manager_CGN_B.varargin_1[5] = Mission_Manager_CGN_B.g;
  Mission_Manager_CGN_B.varargin_1[6] = Mission_Manager_CGN_B.h;
  Mission_Manager_CGN_B.varargin_1[7] = Mission_Manager_CGN_B.i;
  Mission_Manager_CGN_B.varargin_1[8] = Mission_Manager_CGN_B.j;
  Mission_Manager_CGN_B.varargin_1[9] = Mission_Manager_CGN_B.k;
  Mission_Manager_CGN_B.varargin_1[10] = Mission_Manager_CGN_B.l;
  Mission_Manager_CGN_B.varargin_1[11] = Mission_Manager_CGN_B.m;
  Mission_Manager_CGN_B.varargin_1[12] = Mission_Manager_CGN_B.n;
  Mission_Manager_CGN_B.varargin_2[0] = Mission_Manager_CGN_B.o;
  Mission_Manager_CGN_B.varargin_2[1] = Mission_Manager_CGN_B.p;
  Mission_Manager_CGN_B.varargin_2[2] = Mission_Manager_CGN_B.q;
  Mission_Manager_CGN_B.varargin_2[3] = Mission_Manager_CGN_B.r;
  Mission_Manager_CGN_B.varargin_2[4] = Mission_Manager_CGN_B.s;
  Mission_Manager_CGN_B.varargin_2[5] = Mission_Manager_CGN_B.u;
  Mission_Manager_CGN_B.varargin_2[6] = Mission_Manager_CGN_B.v;
  Mission_Manager_CGN_B.varargin_2[7] = Mission_Manager_CGN_B.w;
  Mission_Manager_CGN_B.varargin_2[8] = Mission_Manager_CGN_B.x_j;
  Mission_Manager_CGN_B.varargin_2[9] = Mission_Manager_CGN_B.y;
  Mission_Manager_CGN_B.varargin_2[10] = Mission_Manager_CGN_B.ab;
  Mission_Manager_CGN_B.varargin_2[11] = Mission_Manager_CGN_B.bb;
  Mission_Manager_CGN_B.varargin_2[12] = Mission_Manager_CGN_B.cb;
  for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 16;
       Mission_Manager_CGN_B.c_ret++) {
    Mission_Manager_CGN_B.b.f1[Mission_Manager_CGN_B.c_ret] =
      n_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.c.f1[Mission_Manager_CGN_B.c_ret] =
      o_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.d.f1[Mission_Manager_CGN_B.c_ret] =
      p_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.e.f1[Mission_Manager_CGN_B.c_ret] =
      q_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.f.f1[Mission_Manager_CGN_B.c_ret] =
      r_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.g.f1[Mission_Manager_CGN_B.c_ret] =
      s_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.h.f1[Mission_Manager_CGN_B.c_ret] =
      t_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.i.f1[Mission_Manager_CGN_B.c_ret] =
      u_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.j.f1[Mission_Manager_CGN_B.c_ret] =
      v_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.k.f1[Mission_Manager_CGN_B.c_ret] =
      w_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.l.f1[Mission_Manager_CGN_B.c_ret] =
      x_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.m.f1[Mission_Manager_CGN_B.c_ret] =
      y_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.n.f1[Mission_Manager_CGN_B.c_ret] =
      ab_a[Mission_Manager_CGN_B.c_ret];
    Mission_Manager_CGN_B.o.f1[Mission_Manager_CGN_B.c_ret] =
      sc[Mission_Manager_CGN_B.c_ret];
  }

  Mission_Manager_CGN_B.varargin_3[0] = Mission_Manager_CGN_B.b;
  Mission_Manager_CGN_B.varargin_3[1] = Mission_Manager_CGN_B.c;
  Mission_Manager_CGN_B.varargin_3[2] = Mission_Manager_CGN_B.d;
  Mission_Manager_CGN_B.varargin_3[3] = Mission_Manager_CGN_B.e;
  Mission_Manager_CGN_B.varargin_3[4] = Mission_Manager_CGN_B.f;
  Mission_Manager_CGN_B.varargin_3[5] = Mission_Manager_CGN_B.g;
  Mission_Manager_CGN_B.varargin_3[6] = Mission_Manager_CGN_B.h;
  Mission_Manager_CGN_B.varargin_3[7] = Mission_Manager_CGN_B.i;
  Mission_Manager_CGN_B.varargin_3[8] = Mission_Manager_CGN_B.j;
  Mission_Manager_CGN_B.varargin_3[9] = Mission_Manager_CGN_B.k;
  Mission_Manager_CGN_B.varargin_3[10] = Mission_Manager_CGN_B.l;
  Mission_Manager_CGN_B.varargin_3[11] = Mission_Manager_CGN_B.m;
  Mission_Manager_CGN_B.varargin_3[12] = Mission_Manager_CGN_B.n;
  for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 16;
       Mission_Manager_CGN_B.c_ret++) {
    Mission_Manager_CGN_B.switch_expression_d[Mission_Manager_CGN_B.c_ret] =
      cmd_trick_id[Mission_Manager_CGN_B.c_ret];
  }

  Mission_Manager_CGN_B.c_ret = 0;
  do {
    exitg3 = 0;
    if (Mission_Manager_CGN_B.c_ret < 13) {
      Mission_Manager_CGN_B.d_ret = std::memcmp
        (&Mission_Manager_CGN_B.varargin_1[Mission_Manager_CGN_B.c_ret].f1[0],
         &Mission_Manager_CGN_B.switch_expression_d[0], 16);
      if (Mission_Manager_CGN_B.d_ret == 0) {
        Mission_Manager_CGN_B.c_ret = 0;
        exitg3 = 1;
      } else {
        Mission_Manager_CGN_B.c_ret++;
      }
    } else {
      Mission_Manager_CGN_B.c_ret = 0;
      exitg3 = 2;
    }
  } while (exitg3 == 0);

  if (exitg3 == 1) {
  } else {
    do {
      exitg2 = 0;
      if (Mission_Manager_CGN_B.c_ret < 13) {
        Mission_Manager_CGN_B.d_ret = std::memcmp
          (&Mission_Manager_CGN_B.varargin_2[Mission_Manager_CGN_B.c_ret].f1[0],
           &Mission_Manager_CGN_B.switch_expression_d[0], 16);
        if (Mission_Manager_CGN_B.d_ret == 0) {
          Mission_Manager_CGN_B.c_ret = 1;
          exitg2 = 1;
        } else {
          Mission_Manager_CGN_B.c_ret++;
        }
      } else {
        Mission_Manager_CGN_B.c_ret = 0;
        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (Mission_Manager_CGN_B.c_ret < 13) {
          Mission_Manager_CGN_B.d_ret = std::memcmp
            (&Mission_Manager_CGN_B.varargin_3[Mission_Manager_CGN_B.c_ret].f1[0],
             &Mission_Manager_CGN_B.switch_expression_d[0], 16);
          if (Mission_Manager_CGN_B.d_ret == 0) {
            Mission_Manager_CGN_B.c_ret = 2;
            exitg1 = 1;
          } else {
            Mission_Manager_CGN_B.c_ret++;
          }
        } else {
          Mission_Manager_CGN_B.c_ret = std::memcmp(&Mission_Manager_CGN_B.o.f1
            [0], &Mission_Manager_CGN_B.switch_expression_d[0], 16);
          if (Mission_Manager_CGN_B.c_ret == 0) {
            Mission_Manager_CGN_B.c_ret = 3;
          } else {
            Mission_Manager_CGN_B.c_ret = -1;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  switch (Mission_Manager_CGN_B.c_ret) {
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

    for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 6;
         Mission_Manager_CGN_B.c_ret++) {
      cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
        idle_wp[Mission_Manager_CGN_B.c_ret];
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

    for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 6;
         Mission_Manager_CGN_B.c_ret++) {
      cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
        idle_wp[Mission_Manager_CGN_B.c_ret];
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

    Mission_Manager_CGN_B.c_ret = std::memcmp(&a[0],
      &Mission_Manager_CGN_B.switch_expression_d[0], 16);
    if (Mission_Manager_CGN_B.c_ret == 0) {
      Mission_Manager_CGN_B.c_ret = 0;
    } else {
      Mission_Manager_CGN_B.c_ret = std::memcmp(&b_a[0],
        &Mission_Manager_CGN_B.switch_expression_d[0], 16);
      if (Mission_Manager_CGN_B.c_ret == 0) {
        Mission_Manager_CGN_B.c_ret = 1;
      } else {
        Mission_Manager_CGN_B.c_ret = std::memcmp(&c_a[0],
          &Mission_Manager_CGN_B.switch_expression_d[0], 16);
        if (Mission_Manager_CGN_B.c_ret == 0) {
          Mission_Manager_CGN_B.c_ret = 2;
        } else {
          Mission_Manager_CGN_B.c_ret = std::memcmp(&d_a[0],
            &Mission_Manager_CGN_B.switch_expression_d[0], 16);
          if (Mission_Manager_CGN_B.c_ret == 0) {
            Mission_Manager_CGN_B.c_ret = 3;
          } else {
            Mission_Manager_CGN_B.c_ret = std::memcmp(&e_a[0],
              &Mission_Manager_CGN_B.switch_expression_d[0], 16);
            if (Mission_Manager_CGN_B.c_ret == 0) {
              Mission_Manager_CGN_B.c_ret = 4;
            } else {
              Mission_Manager_CGN_B.c_ret = std::memcmp(&f_a[0],
                &Mission_Manager_CGN_B.switch_expression_d[0], 16);
              if (Mission_Manager_CGN_B.c_ret == 0) {
                Mission_Manager_CGN_B.c_ret = 5;
              } else {
                Mission_Manager_CGN_B.c_ret = std::memcmp(&g_a[0],
                  &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                if (Mission_Manager_CGN_B.c_ret == 0) {
                  Mission_Manager_CGN_B.c_ret = 6;
                } else {
                  Mission_Manager_CGN_B.c_ret = std::memcmp(&h_a[0],
                    &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                  if (Mission_Manager_CGN_B.c_ret == 0) {
                    Mission_Manager_CGN_B.c_ret = 7;
                  } else {
                    Mission_Manager_CGN_B.c_ret = std::memcmp(&i_a[0],
                      &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                    if (Mission_Manager_CGN_B.c_ret == 0) {
                      Mission_Manager_CGN_B.c_ret = 8;
                    } else {
                      Mission_Manager_CGN_B.c_ret = std::memcmp(&j_a[0],
                        &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                      if (Mission_Manager_CGN_B.c_ret == 0) {
                        Mission_Manager_CGN_B.c_ret = 9;
                      } else {
                        Mission_Manager_CGN_B.c_ret = std::memcmp(&k_a[0],
                          &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                        if (Mission_Manager_CGN_B.c_ret == 0) {
                          Mission_Manager_CGN_B.c_ret = 10;
                        } else {
                          Mission_Manager_CGN_B.c_ret = std::memcmp(&l_a[0],
                            &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                          if (Mission_Manager_CGN_B.c_ret == 0) {
                            Mission_Manager_CGN_B.c_ret = 11;
                          } else {
                            Mission_Manager_CGN_B.c_ret = std::memcmp(&m_a[0],
                              &Mission_Manager_CGN_B.switch_expression_d[0], 16);
                            if (Mission_Manager_CGN_B.c_ret == 0) {
                              Mission_Manager_CGN_B.c_ret = 12;
                            } else {
                              Mission_Manager_CGN_B.c_ret = -1;
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

    switch (Mission_Manager_CGN_B.c_ret) {
     case 0:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), tmp), _mm_mul_pd
            (_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), _mm_set1_pd
             (1000.0))), _mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 6]), tmp)), _mm_loadu_pd
            (&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 0.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * 1000.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 0.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 1:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), tmp), _mm_mul_pd
            (_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), _mm_set1_pd
             (-1000.0))), _mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 6]), tmp)), _mm_loadu_pd
            (&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 0.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * -1000.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 0.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 2:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), _mm_set1_pd(1000.0)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), tmp)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret + 6]),
                       tmp)), _mm_loadu_pd(&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 1000.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * 0.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 0.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 3:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), _mm_set1_pd(-1000.0)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), tmp)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret + 6]),
                       tmp)), _mm_loadu_pd(&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * -1000.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * 0.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 0.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 4:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), tmp), _mm_mul_pd
            (_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), tmp)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret + 6]),
                       _mm_set1_pd(-1000.0))), _mm_loadu_pd
            (&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 0.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * 0.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * -1000.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 5:
      if (new_cmd_reset) {
        for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
             Mission_Manager_CGN_B.c_ret += 2) {
          tmp = _mm_set1_pd(0.0);
          _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret],
                        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
            (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), tmp), _mm_mul_pd
            (_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), tmp)),
            _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret + 6]),
                       _mm_set1_pd(1000.0))), _mm_loadu_pd
            (&X_Ri[Mission_Manager_CGN_B.c_ret])));
        }

        for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
             Mission_Manager_CGN_B.c_ret++) {
          cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
            ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 0.0 +
              X_Cib[Mission_Manager_CGN_B.c_ret] * 0.0) +
             X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 1000.0) +
            X_Ri[Mission_Manager_CGN_B.c_ret];
        }
      }

      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 6:
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 7:
      cmd_specific_wp[5] = X_Eul[2] + 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 8:
      cmd_specific_wp[5] = X_Eul[2] - 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 9:
      cmd_specific_wp[5] = X_Eul[0] + 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 10:
      cmd_specific_wp[5] = X_Eul[0] - 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 11:
      cmd_specific_wp[5] = X_Eul[1] + 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 12:
      cmd_specific_wp[5] = X_Eul[1] - 0.52359877559829882;
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     default:
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
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
      Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
        Mission_Manager_CGN_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = Mission_Manager_CGN_B.dv2[0];
      X_u[4] = Mission_Manager_CGN_B.dv2[1];
      X_u[5] = Mission_Manager_CGN_B.dv2[2];
      X_u[6] = Mission_Manager_CGN_B.dv2[3];
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
      for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret <= 0;
           Mission_Manager_CGN_B.c_ret += 2) {
        tmp = _mm_set1_pd(0.0);
        _mm_storeu_pd(&cmd_specific_wp[Mission_Manager_CGN_B.c_ret], _mm_add_pd
                      (_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
          (&X_Cib[Mission_Manager_CGN_B.c_ret + 3]), tmp), _mm_mul_pd
          (_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret]), _mm_set1_pd(1000.0))),
          _mm_mul_pd(_mm_loadu_pd(&X_Cib[Mission_Manager_CGN_B.c_ret + 6]), tmp)),
                       _mm_loadu_pd(&X_Ri[Mission_Manager_CGN_B.c_ret])));
      }

      for (Mission_Manager_CGN_B.c_ret = 2; Mission_Manager_CGN_B.c_ret < 3;
           Mission_Manager_CGN_B.c_ret++) {
        cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
          ((X_Cib[Mission_Manager_CGN_B.c_ret + 3] * 0.0 +
            X_Cib[Mission_Manager_CGN_B.c_ret] * 1000.0) +
           X_Cib[Mission_Manager_CGN_B.c_ret + 6] * 0.0) +
          X_Ri[Mission_Manager_CGN_B.c_ret];
      }
    }

    Mission_Manager_CGN_eulToQuat_k(&cmd_specific_wp[3],
      Mission_Manager_CGN_B.dv2);
    X_u[0] = cmd_specific_wp[0];
    X_u[1] = cmd_specific_wp[1];
    X_u[2] = cmd_specific_wp[2];
    X_u[3] = Mission_Manager_CGN_B.dv2[0];
    X_u[4] = Mission_Manager_CGN_B.dv2[1];
    X_u[5] = Mission_Manager_CGN_B.dv2[2];
    X_u[6] = Mission_Manager_CGN_B.dv2[3];
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
    for (Mission_Manager_CGN_B.c_ret = 0; Mission_Manager_CGN_B.c_ret < 6;
         Mission_Manager_CGN_B.c_ret++) {
      cmd_specific_wp[Mission_Manager_CGN_B.c_ret] =
        idle_wp[Mission_Manager_CGN_B.c_ret];
    }
    break;
  }
}

// Function for MATLAB Function: '<S18>/guidanceLaw'
real_T Mission_Manager_CGN::Mission_Manager_CGN_norm(const real_T x[2])
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  scale = 3.3121686421112381E-170;
  absxk = std::abs(x[0]);
  if (absxk > 3.3121686421112381E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    y = t * t;
  }

  absxk = std::abs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * std::sqrt(y);
}

// Function for MATLAB Function: '<S18>/guidanceLaw'
void Mission_Manager_CGN::Mission_Manager_CGN_quatToEul(const real_T qib[4],
  real_T Eul[3])
{
  __m128d tmp;
  __m128d tmp_0;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  Mission_Manager_CGN_B.a_b = qib[3] * qib[3] * 2.0 - 1.0;
  Mission_Manager_CGN_B.b_a_l = 2.0 * qib[3];
  for (Mission_Manager_CGN_B.i_as = 0; Mission_Manager_CGN_B.i_as < 3;
       Mission_Manager_CGN_B.i_as++) {
    Mission_Manager_CGN_B.a[3 * Mission_Manager_CGN_B.i_as] = 2.0 *
      qib[Mission_Manager_CGN_B.i_as] * qib[0] + Mission_Manager_CGN_B.a_b *
      static_cast<real_T>(b[Mission_Manager_CGN_B.i_as]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.a[3 * Mission_Manager_CGN_B.i_as + 1],
                  _mm_add_pd(_mm_mul_pd(_mm_set_pd(static_cast<real_T>
      (b[Mission_Manager_CGN_B.i_as + 6]), static_cast<real_T>
      (b[Mission_Manager_CGN_B.i_as + 3])), _mm_set1_pd
      (Mission_Manager_CGN_B.a_b)), _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(2.0),
      _mm_set1_pd(qib[Mission_Manager_CGN_B.i_as])), _mm_loadu_pd(&qib[1]))));
  }

  Mission_Manager_CGN_B.a_b = Mission_Manager_CGN_B.b_a_l * 0.0;
  Mission_Manager_CGN_B.b_a[0] = Mission_Manager_CGN_B.a_b;
  tmp_0 = _mm_set1_pd(Mission_Manager_CGN_B.b_a_l);
  _mm_storeu_pd(&Mission_Manager_CGN_B.b_a[1], _mm_mul_pd(tmp_0, _mm_set_pd(qib
    [1], -qib[2])));
  Mission_Manager_CGN_B.b_a[3] = Mission_Manager_CGN_B.b_a_l * qib[2];
  Mission_Manager_CGN_B.b_a[4] = Mission_Manager_CGN_B.a_b;
  _mm_storeu_pd(&Mission_Manager_CGN_B.b_a[5], _mm_mul_pd(tmp_0, _mm_set_pd
    (-qib[1], -qib[0])));
  Mission_Manager_CGN_B.b_a[7] = Mission_Manager_CGN_B.b_a_l * qib[0];
  Mission_Manager_CGN_B.b_a[8] = Mission_Manager_CGN_B.a_b;
  for (Mission_Manager_CGN_B.i_as = 0; Mission_Manager_CGN_B.i_as <= 6;
       Mission_Manager_CGN_B.i_as += 2) {
    tmp_0 = _mm_loadu_pd(&Mission_Manager_CGN_B.a[Mission_Manager_CGN_B.i_as]);
    tmp = _mm_loadu_pd(&Mission_Manager_CGN_B.b_a[Mission_Manager_CGN_B.i_as]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_p[Mission_Manager_CGN_B.i_as],
                  _mm_add_pd(tmp_0, tmp));
  }

  for (Mission_Manager_CGN_B.i_as = 8; Mission_Manager_CGN_B.i_as < 9;
       Mission_Manager_CGN_B.i_as++) {
    Mission_Manager_CGN_B.Cbi_p[Mission_Manager_CGN_B.i_as] =
      Mission_Manager_CGN_B.a[Mission_Manager_CGN_B.i_as] +
      Mission_Manager_CGN_B.b_a[Mission_Manager_CGN_B.i_as];
  }

  Mission_Manager_CGN_B.b_a_l = std::asin(std::fmax(-1.0, std::fmin(1.0,
    Mission_Manager_CGN_B.Cbi_p[6])));
  if (std::abs(std::cos(-Mission_Manager_CGN_B.b_a_l)) < 1.0E-6) {
    Eul[0] = 0.0;
    Eul[2] = Mission_Manager_C_rt_atan2d_snf(-Mission_Manager_CGN_B.Cbi_p[1],
      Mission_Manager_CGN_B.Cbi_p[4]);
  } else {
    Eul[0] = Mission_Manager_C_rt_atan2d_snf(Mission_Manager_CGN_B.Cbi_p[7],
      Mission_Manager_CGN_B.Cbi_p[8]);
    Eul[2] = Mission_Manager_C_rt_atan2d_snf(Mission_Manager_CGN_B.Cbi_p[3],
      Mission_Manager_CGN_B.Cbi_p[0]);
  }

  Mission_Manager_CGN_wrapToPi(&Eul[0]);
  Eul[1] = -Mission_Manager_CGN_B.b_a_l;
  Mission_Manager_CGN_wrapToPi(&Eul[1]);
  Mission_Manager_CGN_wrapToPi(&Eul[2]);
}

// Function for MATLAB Function: '<S18>/guidanceLaw'
void Mission_Manager_CGN::Mission_Manager_CGN_eulToRotm(const real_T Eul[3],
  real_T rotm[9])
{
  Mission_Manager_CGN_B.rotm_tmp_c = std::cos(Eul[1]);
  Mission_Manager_CGN_B.rotm_tmp_ct = std::sin(Eul[1]);
  Mission_Manager_CGN_B.rotm_tmp_p = std::cos(Eul[2]);
  Mission_Manager_CGN_B.rotm_tmp_p5 = std::sin(Eul[2]);
  rotm[0] = Mission_Manager_CGN_B.rotm_tmp_c * Mission_Manager_CGN_B.rotm_tmp_p;
  rotm[3] = Mission_Manager_CGN_B.rotm_tmp_c * Mission_Manager_CGN_B.rotm_tmp_p5;
  rotm[6] = -Mission_Manager_CGN_B.rotm_tmp_ct;
  Mission_Manager_CGN_B.rotm_tmp_a = 0.0 * Mission_Manager_CGN_B.rotm_tmp_ct;
  rotm[1] = Mission_Manager_CGN_B.rotm_tmp_a * Mission_Manager_CGN_B.rotm_tmp_p
    - Mission_Manager_CGN_B.rotm_tmp_p5;
  rotm[4] = Mission_Manager_CGN_B.rotm_tmp_a * Mission_Manager_CGN_B.rotm_tmp_p5
    + Mission_Manager_CGN_B.rotm_tmp_p;
  rotm[7] = 0.0 * Mission_Manager_CGN_B.rotm_tmp_c;
  rotm[2] = Mission_Manager_CGN_B.rotm_tmp_ct * Mission_Manager_CGN_B.rotm_tmp_p
    + 0.0 * Mission_Manager_CGN_B.rotm_tmp_p5;
  rotm[5] = Mission_Manager_CGN_B.rotm_tmp_ct *
    Mission_Manager_CGN_B.rotm_tmp_p5 - 0.0 * Mission_Manager_CGN_B.rotm_tmp_p;
  rotm[8] = Mission_Manager_CGN_B.rotm_tmp_c;
}

// Function for MATLAB Function: '<S18>/guidanceLaw'
void Mission_Manager_CGN::Mission_Manager_CGN_rotmToQuat(const real_T rotm[9],
  real_T qib[4])
{
  Mission_Manager_CGN_B.eta_o = std::sqrt(((rotm[0] + rotm[4]) + rotm[8]) + 1.0)
    / 2.0;
  if (Mission_Manager_CGN_B.eta_o != 0.0) {
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv10[0], _mm_div_pd(_mm_sub_pd
      (_mm_set_pd(rotm[2], rotm[7]), _mm_loadu_pd(&rotm[5])), _mm_mul_pd
      (_mm_set1_pd(4.0), _mm_set1_pd(Mission_Manager_CGN_B.eta_o))));
    Mission_Manager_CGN_B.eps_idx_0_m = Mission_Manager_CGN_B.dv10[0];
    Mission_Manager_CGN_B.eps_idx_1_ja = Mission_Manager_CGN_B.dv10[1];
    Mission_Manager_CGN_B.eps_idx_2_h = (rotm[3] - rotm[1]) / (4.0 *
      Mission_Manager_CGN_B.eta_o);
  } else {
    _mm_storeu_pd(&Mission_Manager_CGN_B.x_n[0], _mm_div_pd(_mm_add_pd
      (_mm_set_pd(rotm[4], rotm[0]), _mm_set1_pd(1.0)), _mm_set1_pd(2.0)));
    Mission_Manager_CGN_B.eps_idx_2_h = (rotm[8] + 1.0) / 2.0;
    Mission_Manager_CGN_B.x_n[2] = Mission_Manager_CGN_B.eps_idx_2_h;
    if (!std::isnan(Mission_Manager_CGN_B.x_n[0])) {
      Mission_Manager_CGN_B.idx_i = 1;
    } else {
      boolean_T exitg1;
      Mission_Manager_CGN_B.idx_i = 0;
      Mission_Manager_CGN_B.b_k_f = 2;
      exitg1 = false;
      while ((!exitg1) && (Mission_Manager_CGN_B.b_k_f < 4)) {
        if (!std::isnan(Mission_Manager_CGN_B.x_n[Mission_Manager_CGN_B.b_k_f -
                        1])) {
          Mission_Manager_CGN_B.idx_i = Mission_Manager_CGN_B.b_k_f;
          exitg1 = true;
        } else {
          Mission_Manager_CGN_B.b_k_f++;
        }
      }
    }

    if (Mission_Manager_CGN_B.idx_i == 0) {
      Mission_Manager_CGN_B.b_k_f = 1;
    } else {
      Mission_Manager_CGN_B.eps_idx_0_m =
        Mission_Manager_CGN_B.x_n[Mission_Manager_CGN_B.idx_i - 1];
      Mission_Manager_CGN_B.b_k_f = Mission_Manager_CGN_B.idx_i;
      for (Mission_Manager_CGN_B.c_k_i = Mission_Manager_CGN_B.idx_i + 1;
           Mission_Manager_CGN_B.c_k_i < 4; Mission_Manager_CGN_B.c_k_i++) {
        Mission_Manager_CGN_B.eps_idx_1_ja =
          Mission_Manager_CGN_B.x_n[Mission_Manager_CGN_B.c_k_i - 1];
        if (Mission_Manager_CGN_B.eps_idx_0_m <
            Mission_Manager_CGN_B.eps_idx_1_ja) {
          Mission_Manager_CGN_B.eps_idx_0_m = Mission_Manager_CGN_B.eps_idx_1_ja;
          Mission_Manager_CGN_B.b_k_f = Mission_Manager_CGN_B.c_k_i;
        }
      }
    }

    switch (Mission_Manager_CGN_B.b_k_f) {
     case 1:
      Mission_Manager_CGN_B.eps_idx_0_m = std::sqrt(std::fmax(0.0, (rotm[0] +
        1.0) / 2.0));
      if (std::isnan(rotm[3])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[3] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[3] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1_ja = std::sqrt(std::fmax(0.0, (rotm[4] +
        1.0) / 2.0)) * Mission_Manager_CGN_B.scale_m;
      if (std::isnan(rotm[6])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[6] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[6] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2_h = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_2_h)) * Mission_Manager_CGN_B.scale_m;
      break;

     case 2:
      Mission_Manager_CGN_B.eps_idx_1_ja = std::sqrt(std::fmax(0.0, (rotm[4] +
        1.0) / 2.0));
      if (std::isnan(rotm[3])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[3] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[3] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0_m = std::sqrt(std::fmax(0.0, (rotm[0] +
        1.0) / 2.0)) * Mission_Manager_CGN_B.scale_m;
      if (std::isnan(rotm[7])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[7] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[7] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2_h = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_2_h)) * Mission_Manager_CGN_B.scale_m;
      break;

     default:
      Mission_Manager_CGN_B.eps_idx_2_h = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_2_h));
      if (std::isnan(rotm[6])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[6] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[6] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0_m = std::sqrt(std::fmax(0.0, (rotm[0] +
        1.0) / 2.0)) * Mission_Manager_CGN_B.scale_m;
      if (std::isnan(rotm[7])) {
        Mission_Manager_CGN_B.scale_m = (rtNaN);
      } else if (rotm[7] < 0.0) {
        Mission_Manager_CGN_B.scale_m = -1.0;
      } else {
        Mission_Manager_CGN_B.scale_m = (rotm[7] > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1_ja = std::sqrt(std::fmax(0.0, (rotm[4] +
        1.0) / 2.0)) * Mission_Manager_CGN_B.scale_m;
      break;
    }
  }

  Mission_Manager_CGN_B.scale_m = 3.3121686421112381E-170;
  Mission_Manager_CGN_B.absxk_c = std::abs(Mission_Manager_CGN_B.eps_idx_0_m);
  if (Mission_Manager_CGN_B.absxk_c > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.y_n = 1.0;
    Mission_Manager_CGN_B.scale_m = Mission_Manager_CGN_B.absxk_c;
  } else {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.absxk_c /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.y_n = Mission_Manager_CGN_B.b_t_m *
      Mission_Manager_CGN_B.b_t_m;
  }

  Mission_Manager_CGN_B.absxk_c = std::abs(Mission_Manager_CGN_B.eps_idx_1_ja);
  if (Mission_Manager_CGN_B.absxk_c > Mission_Manager_CGN_B.scale_m) {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.scale_m /
      Mission_Manager_CGN_B.absxk_c;
    Mission_Manager_CGN_B.y_n = Mission_Manager_CGN_B.y_n *
      Mission_Manager_CGN_B.b_t_m * Mission_Manager_CGN_B.b_t_m + 1.0;
    Mission_Manager_CGN_B.scale_m = Mission_Manager_CGN_B.absxk_c;
  } else {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.absxk_c /
      Mission_Manager_CGN_B.scale_m;
    Mission_Manager_CGN_B.y_n += Mission_Manager_CGN_B.b_t_m *
      Mission_Manager_CGN_B.b_t_m;
  }

  Mission_Manager_CGN_B.absxk_c = std::abs(Mission_Manager_CGN_B.eps_idx_2_h);
  if (Mission_Manager_CGN_B.absxk_c > Mission_Manager_CGN_B.scale_m) {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.scale_m /
      Mission_Manager_CGN_B.absxk_c;
    Mission_Manager_CGN_B.y_n = Mission_Manager_CGN_B.y_n *
      Mission_Manager_CGN_B.b_t_m * Mission_Manager_CGN_B.b_t_m + 1.0;
    Mission_Manager_CGN_B.scale_m = Mission_Manager_CGN_B.absxk_c;
  } else {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.absxk_c /
      Mission_Manager_CGN_B.scale_m;
    Mission_Manager_CGN_B.y_n += Mission_Manager_CGN_B.b_t_m *
      Mission_Manager_CGN_B.b_t_m;
  }

  if (Mission_Manager_CGN_B.eta_o > Mission_Manager_CGN_B.scale_m) {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.scale_m /
      Mission_Manager_CGN_B.eta_o;
    Mission_Manager_CGN_B.y_n = Mission_Manager_CGN_B.y_n *
      Mission_Manager_CGN_B.b_t_m * Mission_Manager_CGN_B.b_t_m + 1.0;
    Mission_Manager_CGN_B.scale_m = Mission_Manager_CGN_B.eta_o;
  } else {
    Mission_Manager_CGN_B.b_t_m = Mission_Manager_CGN_B.eta_o /
      Mission_Manager_CGN_B.scale_m;
    Mission_Manager_CGN_B.y_n += Mission_Manager_CGN_B.b_t_m *
      Mission_Manager_CGN_B.b_t_m;
  }

  Mission_Manager_CGN_B.y_n = Mission_Manager_CGN_B.scale_m * std::sqrt
    (Mission_Manager_CGN_B.y_n);
  qib[0] = Mission_Manager_CGN_B.eps_idx_0_m / Mission_Manager_CGN_B.y_n;
  qib[1] = Mission_Manager_CGN_B.eps_idx_1_ja / Mission_Manager_CGN_B.y_n;
  qib[2] = Mission_Manager_CGN_B.eps_idx_2_h / Mission_Manager_CGN_B.y_n;
  qib[3] = Mission_Manager_CGN_B.eta_o / Mission_Manager_CGN_B.y_n;
}

// Function for MATLAB Function: '<S18>/quatInjector'
void Mission_Manager_CGN::Mission_Manager_CGN_eulToQuat(const real_T Eul[3],
  real_T qib[4])
{
  Mission_Manager_CGN_B.eta_b = std::cos(Eul[1]);
  Mission_Manager_CGN_B.scale_d = std::sin(Eul[1]);
  Mission_Manager_CGN_B.b_t_bj = std::cos(Eul[2]);
  Mission_Manager_CGN_B.rotm_tmp_j = std::sin(Eul[2]);
  Mission_Manager_CGN_B.eps_idx_1_j = std::sin(Eul[0]);
  Mission_Manager_CGN_B.rotm_tmp_f = std::cos(Eul[0]);
  Mission_Manager_CGN_B.rotm_idx_0_o = Mission_Manager_CGN_B.eta_b *
    Mission_Manager_CGN_B.b_t_bj;
  Mission_Manager_CGN_B.eps_idx_2_j = Mission_Manager_CGN_B.eta_b *
    Mission_Manager_CGN_B.rotm_tmp_j;
  Mission_Manager_CGN_B.rotm_idx_4_tmp_i = Mission_Manager_CGN_B.eps_idx_1_j *
    Mission_Manager_CGN_B.scale_d;
  Mission_Manager_CGN_B.eps_idx_0_a = Mission_Manager_CGN_B.rotm_idx_4_tmp_i *
    Mission_Manager_CGN_B.rotm_tmp_j + Mission_Manager_CGN_B.rotm_tmp_f *
    Mission_Manager_CGN_B.b_t_bj;
  Mission_Manager_CGN_B.absxk_e = Mission_Manager_CGN_B.eps_idx_1_j *
    Mission_Manager_CGN_B.eta_b;
  Mission_Manager_CGN_B.rotm_idx_8_n = Mission_Manager_CGN_B.rotm_tmp_f *
    Mission_Manager_CGN_B.eta_b;
  Mission_Manager_CGN_B.eta_b = std::sqrt(((Mission_Manager_CGN_B.rotm_idx_0_o +
    Mission_Manager_CGN_B.eps_idx_0_a) + Mission_Manager_CGN_B.rotm_idx_8_n) +
    1.0) / 2.0;
  if (Mission_Manager_CGN_B.eta_b != 0.0) {
    Mission_Manager_CGN_B.rotm_idx_0_o = Mission_Manager_CGN_B.rotm_tmp_f *
      Mission_Manager_CGN_B.scale_d;
    Mission_Manager_CGN_B.rotm_idx_8_n = 4.0 * Mission_Manager_CGN_B.eta_b;
    Mission_Manager_CGN_B.eps_idx_0_a = (Mission_Manager_CGN_B.absxk_e -
      (Mission_Manager_CGN_B.rotm_idx_0_o * Mission_Manager_CGN_B.rotm_tmp_j -
       Mission_Manager_CGN_B.eps_idx_1_j * Mission_Manager_CGN_B.b_t_bj)) /
      Mission_Manager_CGN_B.rotm_idx_8_n;
    Mission_Manager_CGN_B.eps_idx_1_j = ((Mission_Manager_CGN_B.rotm_idx_0_o *
      Mission_Manager_CGN_B.b_t_bj + Mission_Manager_CGN_B.eps_idx_1_j *
      Mission_Manager_CGN_B.rotm_tmp_j) - (-Mission_Manager_CGN_B.scale_d)) /
      Mission_Manager_CGN_B.rotm_idx_8_n;
    Mission_Manager_CGN_B.eps_idx_2_j = (Mission_Manager_CGN_B.eps_idx_2_j -
      (Mission_Manager_CGN_B.rotm_idx_4_tmp_i * Mission_Manager_CGN_B.b_t_bj -
       Mission_Manager_CGN_B.rotm_tmp_f * Mission_Manager_CGN_B.rotm_tmp_j)) /
      Mission_Manager_CGN_B.rotm_idx_8_n;
  } else {
    Mission_Manager_CGN_B.b_t_bj = (Mission_Manager_CGN_B.rotm_idx_0_o + 1.0) /
      2.0;
    Mission_Manager_CGN_B.x_m[0] = Mission_Manager_CGN_B.b_t_bj;
    Mission_Manager_CGN_B.eps_idx_1_j = (Mission_Manager_CGN_B.eps_idx_0_a + 1.0)
      / 2.0;
    Mission_Manager_CGN_B.x_m[1] = Mission_Manager_CGN_B.eps_idx_1_j;
    Mission_Manager_CGN_B.rotm_tmp_j = (Mission_Manager_CGN_B.rotm_idx_8_n + 1.0)
      / 2.0;
    Mission_Manager_CGN_B.x_m[2] = Mission_Manager_CGN_B.rotm_tmp_j;
    if (!std::isnan(Mission_Manager_CGN_B.b_t_bj)) {
      Mission_Manager_CGN_B.idx_l = 1;
    } else {
      boolean_T exitg1;
      Mission_Manager_CGN_B.idx_l = 0;
      Mission_Manager_CGN_B.b_k_o = 2;
      exitg1 = false;
      while ((!exitg1) && (Mission_Manager_CGN_B.b_k_o < 4)) {
        if (!std::isnan(Mission_Manager_CGN_B.x_m[Mission_Manager_CGN_B.b_k_o -
                        1])) {
          Mission_Manager_CGN_B.idx_l = Mission_Manager_CGN_B.b_k_o;
          exitg1 = true;
        } else {
          Mission_Manager_CGN_B.b_k_o++;
        }
      }
    }

    if (Mission_Manager_CGN_B.idx_l == 0) {
      Mission_Manager_CGN_B.b_k_o = 1;
    } else {
      Mission_Manager_CGN_B.eps_idx_0_a =
        Mission_Manager_CGN_B.x_m[Mission_Manager_CGN_B.idx_l - 1];
      Mission_Manager_CGN_B.b_k_o = Mission_Manager_CGN_B.idx_l;
      for (Mission_Manager_CGN_B.c_k_o = Mission_Manager_CGN_B.idx_l + 1;
           Mission_Manager_CGN_B.c_k_o < 4; Mission_Manager_CGN_B.c_k_o++) {
        Mission_Manager_CGN_B.rotm_tmp_f =
          Mission_Manager_CGN_B.x_m[Mission_Manager_CGN_B.c_k_o - 1];
        if (Mission_Manager_CGN_B.eps_idx_0_a < Mission_Manager_CGN_B.rotm_tmp_f)
        {
          Mission_Manager_CGN_B.eps_idx_0_a = Mission_Manager_CGN_B.rotm_tmp_f;
          Mission_Manager_CGN_B.b_k_o = Mission_Manager_CGN_B.c_k_o;
        }
      }
    }

    switch (Mission_Manager_CGN_B.b_k_o) {
     case 1:
      Mission_Manager_CGN_B.eps_idx_0_a = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_bj));
      if (std::isnan(Mission_Manager_CGN_B.eps_idx_2_j)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (Mission_Manager_CGN_B.eps_idx_2_j < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (Mission_Manager_CGN_B.eps_idx_2_j >
          0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1_j)) * Mission_Manager_CGN_B.rotm_tmp_f;
      if (std::isnan(-Mission_Manager_CGN_B.scale_d)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (-Mission_Manager_CGN_B.scale_d < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (-Mission_Manager_CGN_B.scale_d > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp_j)) * Mission_Manager_CGN_B.rotm_tmp_f;
      break;

     case 2:
      Mission_Manager_CGN_B.eps_idx_1_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1_j));
      if (std::isnan(Mission_Manager_CGN_B.eps_idx_2_j)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (Mission_Manager_CGN_B.eps_idx_2_j < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (Mission_Manager_CGN_B.eps_idx_2_j >
          0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0_a = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_bj)) * Mission_Manager_CGN_B.rotm_tmp_f;
      if (std::isnan(Mission_Manager_CGN_B.absxk_e)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (Mission_Manager_CGN_B.absxk_e < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (Mission_Manager_CGN_B.absxk_e > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_2_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp_j)) * Mission_Manager_CGN_B.rotm_tmp_f;
      break;

     default:
      Mission_Manager_CGN_B.eps_idx_2_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.rotm_tmp_j));
      if (std::isnan(-Mission_Manager_CGN_B.scale_d)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (-Mission_Manager_CGN_B.scale_d < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (-Mission_Manager_CGN_B.scale_d > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_0_a = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.b_t_bj)) * Mission_Manager_CGN_B.rotm_tmp_f;
      if (std::isnan(Mission_Manager_CGN_B.absxk_e)) {
        Mission_Manager_CGN_B.rotm_tmp_f = (rtNaN);
      } else if (Mission_Manager_CGN_B.absxk_e < 0.0) {
        Mission_Manager_CGN_B.rotm_tmp_f = -1.0;
      } else {
        Mission_Manager_CGN_B.rotm_tmp_f = (Mission_Manager_CGN_B.absxk_e > 0.0);
      }

      Mission_Manager_CGN_B.eps_idx_1_j = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.eps_idx_1_j)) * Mission_Manager_CGN_B.rotm_tmp_f;
      break;
    }
  }

  Mission_Manager_CGN_B.scale_d = 3.3121686421112381E-170;
  Mission_Manager_CGN_B.absxk_e = std::abs(Mission_Manager_CGN_B.eps_idx_0_a);
  if (Mission_Manager_CGN_B.absxk_e > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.rotm_tmp_j = 1.0;
    Mission_Manager_CGN_B.scale_d = Mission_Manager_CGN_B.absxk_e;
  } else {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.absxk_e /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.rotm_tmp_j = Mission_Manager_CGN_B.b_t_bj *
      Mission_Manager_CGN_B.b_t_bj;
  }

  Mission_Manager_CGN_B.absxk_e = std::abs(Mission_Manager_CGN_B.eps_idx_1_j);
  if (Mission_Manager_CGN_B.absxk_e > Mission_Manager_CGN_B.scale_d) {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.scale_d /
      Mission_Manager_CGN_B.absxk_e;
    Mission_Manager_CGN_B.rotm_tmp_j = Mission_Manager_CGN_B.rotm_tmp_j *
      Mission_Manager_CGN_B.b_t_bj * Mission_Manager_CGN_B.b_t_bj + 1.0;
    Mission_Manager_CGN_B.scale_d = Mission_Manager_CGN_B.absxk_e;
  } else {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.absxk_e /
      Mission_Manager_CGN_B.scale_d;
    Mission_Manager_CGN_B.rotm_tmp_j += Mission_Manager_CGN_B.b_t_bj *
      Mission_Manager_CGN_B.b_t_bj;
  }

  Mission_Manager_CGN_B.absxk_e = std::abs(Mission_Manager_CGN_B.eps_idx_2_j);
  if (Mission_Manager_CGN_B.absxk_e > Mission_Manager_CGN_B.scale_d) {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.scale_d /
      Mission_Manager_CGN_B.absxk_e;
    Mission_Manager_CGN_B.rotm_tmp_j = Mission_Manager_CGN_B.rotm_tmp_j *
      Mission_Manager_CGN_B.b_t_bj * Mission_Manager_CGN_B.b_t_bj + 1.0;
    Mission_Manager_CGN_B.scale_d = Mission_Manager_CGN_B.absxk_e;
  } else {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.absxk_e /
      Mission_Manager_CGN_B.scale_d;
    Mission_Manager_CGN_B.rotm_tmp_j += Mission_Manager_CGN_B.b_t_bj *
      Mission_Manager_CGN_B.b_t_bj;
  }

  if (Mission_Manager_CGN_B.eta_b > Mission_Manager_CGN_B.scale_d) {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.scale_d /
      Mission_Manager_CGN_B.eta_b;
    Mission_Manager_CGN_B.rotm_tmp_j = Mission_Manager_CGN_B.rotm_tmp_j *
      Mission_Manager_CGN_B.b_t_bj * Mission_Manager_CGN_B.b_t_bj + 1.0;
    Mission_Manager_CGN_B.scale_d = Mission_Manager_CGN_B.eta_b;
  } else {
    Mission_Manager_CGN_B.b_t_bj = Mission_Manager_CGN_B.eta_b /
      Mission_Manager_CGN_B.scale_d;
    Mission_Manager_CGN_B.rotm_tmp_j += Mission_Manager_CGN_B.b_t_bj *
      Mission_Manager_CGN_B.b_t_bj;
  }

  Mission_Manager_CGN_B.rotm_tmp_j = Mission_Manager_CGN_B.scale_d * std::sqrt
    (Mission_Manager_CGN_B.rotm_tmp_j);
  qib[0] = Mission_Manager_CGN_B.eps_idx_0_a / Mission_Manager_CGN_B.rotm_tmp_j;
  qib[1] = Mission_Manager_CGN_B.eps_idx_1_j / Mission_Manager_CGN_B.rotm_tmp_j;
  qib[2] = Mission_Manager_CGN_B.eps_idx_2_j / Mission_Manager_CGN_B.rotm_tmp_j;
  qib[3] = Mission_Manager_CGN_B.eta_b / Mission_Manager_CGN_B.rotm_tmp_j;
}

// Function for MATLAB Function: '<S18>/rateInjector'
boolean_T Mission_Manager_CGN::Mission_Manager_CGN_isequal(const char_T
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

// Function for MATLAB Function: '<S18>/rateInjector'
boolean_T Mission_Manager_CGN::Mission_Manager_CGN_strcmp(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S18>/rateInjector'
boolean_T Mission_Manager_CGN::Mission_Manager_CGN_strcmp_j(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S18>/rateInjector'
boolean_T Mission_Manager_CGN::Mission_Manager_CGN_strcmp_jy(const char_T b[16])
{
  int32_T ret;
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  ret = std::memcmp(&b_a[0], &b[0], 16);
  return ret == 0;
}

// Function for MATLAB Function: '<S24>/forceToPWMCalculator'
void Mission_Manager_CGN::Mission_Manager_CGN_minimum(const real_T x[6], real_T *
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

// Function for MATLAB Function: '<S24>/forceToPWMCalculator'
void Mission_Manager_CGN::Mission_Manager_CGN_minimum_m(const real_T x_data[],
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

void Mission_Manager_CGN::Mission_Man_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[16]{ "/command_result" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[16];
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
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Mission_Manager_CGN_286_7.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

void Mission_Manager_CGN::Mission_Ma_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[13]{ "/command_msg" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[13];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S10>/SourceBlock'
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
  for (int32_T i{0}; i < 13; i++) {
    // Start for MATLABSystem: '<S10>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_Mission_Manager_CGN_286_284.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void Mission_Manager_CGN::Mission_Subscriber_setupImpl_be(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
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
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S3>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_Mission_Manager_CGN_293.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void Mission_Manager_CGN::Missio_Subscriber_setupImpl_bea(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[17]{ "/velocity_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[17];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S6>/SourceBlock'
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
    // Start for MATLABSystem: '<S6>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_Mission_Manager_CGN_305.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void Mission_Manager_CGN::Mission__Subscriber_setupImpl_b(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[18]{ "/dead_reck_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[18];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S2>/SourceBlock'
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
    // Start for MATLABSystem: '<S2>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_Mission_Manager_CGN_288.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void Mission_Manager_CGN::Mission__Publisher_setupImpl_be(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S208>/SinkBlock'
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
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S208>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Mission_Manager_CGN_323_2.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

void Mission_Manager_CGN::Mission_M_Publisher_setupImpl_b(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[16];
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
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_Mission_Manager_CGN_322_150.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

// Model step function
void Mission_Manager_CGN::step()
{
  static const char_T a[4]{ 'S', 'U', 'C', 'C' };

  static const char_T b_a[4]{ 'F', 'A', 'I', 'L' };

  static const char_T c_a[4]{ 'R', 'U', 'N', 'N' };

  static const char_T c_a_0[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o',
    'r', 'l', 'd', '_', 'w', 'p', '_' };

  static const char_T d_a[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

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

  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  __m128d tmp_2;
  __m128d tmp_3;
  __m128d tmp_4;
  __m128d tmp_5;
  __m128d tmp_6;
  static const uint8_T b[16]{ 112U, 108U, 97U, 99U, 101U, 104U, 111U, 108U, 100U,
    101U, 114U, 95U, 95U, 95U, 95U, 95U };

  static const int8_T b_0[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const char_T c[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  static const char_T d[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  boolean_T exitg1;

  // MATLABSystem: '<S10>/SourceBlock'
  Mission_Manager_CGN_B.b_varargout_1 =
    Sub_Mission_Manager_CGN_286_284.getLatestMessage
    (&Mission_Manager_CGN_B.rtb_SourceBlock_o2_i_k);

  // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S14>/Enable'

  // Start for MATLABSystem: '<S10>/SourceBlock'
  if (Mission_Manager_CGN_B.b_varargout_1) {
    // SignalConversion generated from: '<S14>/In1'
    Mission_Manager_CGN_B.In1_j = Mission_Manager_CGN_B.rtb_SourceBlock_o2_i_k;
  }

  // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'

  // MATLAB Function: '<S1>/cmdMsgToCmdBus'
  for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 16;
       Mission_Manager_CGN_B.i_a++) {
    Mission_Manager_CGN_B.integrator_reset =
      Mission_Manager_CGN_B.In1_j.command_id[Mission_Manager_CGN_B.i_a];
    if (Mission_Manager_CGN_B.integrator_reset > 127) {
      Mission_Manager_CGN_B.integrator_reset = 127U;
    }

    Mission_Manager_CGN_B.cmd.cmd_id[Mission_Manager_CGN_B.i_a] =
      static_cast<int8_T>(Mission_Manager_CGN_B.integrator_reset);
    Mission_Manager_CGN_B.integrator_reset =
      Mission_Manager_CGN_B.In1_j.trick[Mission_Manager_CGN_B.i_a];
    if (Mission_Manager_CGN_B.integrator_reset > 127) {
      Mission_Manager_CGN_B.integrator_reset = 127U;
    }

    Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.i_a] = static_cast<
      int8_T>(Mission_Manager_CGN_B.integrator_reset);
  }

  // MATLAB Function: '<S1>/statusKwdToBool' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  Mission_Manager_CGN_B.switch_expression_e[0] =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[0];
  Mission_Manager_CGN_B.switch_expression_e[1] =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[1];
  Mission_Manager_CGN_B.switch_expression_e[2] =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[2];
  Mission_Manager_CGN_B.switch_expression_e[3] =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[3];
  Mission_Manager_CGN_B.i_a = std::memcmp(&a[0],
    &Mission_Manager_CGN_B.switch_expression_e[0], 4);
  if (Mission_Manager_CGN_B.i_a == 0) {
    Mission_Manager_CGN_B.b_index = 0;
  } else {
    Mission_Manager_CGN_B.i_a = std::memcmp(&b_a[0],
      &Mission_Manager_CGN_B.switch_expression_e[0], 4);
    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.b_index = 1;
    } else {
      Mission_Manager_CGN_B.i_a = std::memcmp(&c_a[0],
        &Mission_Manager_CGN_B.switch_expression_e[0], 4);
      if (Mission_Manager_CGN_B.i_a == 0) {
        Mission_Manager_CGN_B.b_index = 2;
      } else {
        Mission_Manager_CGN_B.b_index = -1;
      }
    }
  }

  switch (Mission_Manager_CGN_B.b_index) {
   case 0:
    Mission_Manager_CGN_B.result_msg.success = true;
    for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 16;
         Mission_Manager_CGN_B.i_a++) {
      Mission_Manager_CGN_B.result_msg.found_object[Mission_Manager_CGN_B.i_a] =
        b[Mission_Manager_CGN_B.i_a];
    }

    Mission_Manager_CGN_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S11>/Enable'

    // MATLABSystem: '<S15>/SinkBlock'
    Pub_Mission_Manager_CGN_286_7.publish(&Mission_Manager_CGN_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 1:
    Mission_Manager_CGN_B.result_msg.success = false;
    for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 16;
         Mission_Manager_CGN_B.i_a++) {
      Mission_Manager_CGN_B.result_msg.found_object[Mission_Manager_CGN_B.i_a] =
        b[Mission_Manager_CGN_B.i_a];
    }

    Mission_Manager_CGN_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S11>/Enable'

    // MATLABSystem: '<S15>/SinkBlock'
    Pub_Mission_Manager_CGN_286_7.publish(&Mission_Manager_CGN_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 2:
    break;
  }

  // End of MATLAB Function: '<S1>/statusKwdToBool'

  // DigitalClock: '<S19>/Digital Clock'
  Mission_Manager_CGN_B.DigitalClock = (((&Mission_Manager_CGN_M)
    ->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S3>/SourceBlock'
  Mission_Manager_CGN_B.b_varargout_1_g =
    Sub_Mission_Manager_CGN_293.getLatestMessage
    (&Mission_Manager_CGN_B.rtb_SourceBlock_o2_o_c);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S17>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (Mission_Manager_CGN_B.b_varargout_1_g) {
    // SignalConversion generated from: '<S17>/In1'
    Mission_Manager_CGN_B.In1_i = Mission_Manager_CGN_B.rtb_SourceBlock_o2_o_c;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // MATLABSystem: '<S6>/SourceBlock'
  Mission_Manager_CGN_B.b_varargout_1_g =
    Sub_Mission_Manager_CGN_305.getLatestMessage
    (&Mission_Manager_CGN_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S205>/Enable'

  // Start for MATLABSystem: '<S6>/SourceBlock'
  if (Mission_Manager_CGN_B.b_varargout_1_g) {
    // SignalConversion generated from: '<S205>/In1'
    Mission_Manager_CGN_B.In1 = Mission_Manager_CGN_B.rtb_SourceBlock_o2_m;
  }

  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'

  // MATLABSystem: '<S2>/SourceBlock'
  Mission_Manager_CGN_B.b_varargout_1_c =
    Sub_Mission_Manager_CGN_288.getLatestMessage
    (&Mission_Manager_CGN_B.rtb_SourceBlock_o2_d_c);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S16>/Enable'

  // Start for MATLABSystem: '<S2>/SourceBlock'
  if (Mission_Manager_CGN_B.b_varargout_1_c) {
    // SignalConversion generated from: '<S16>/In1'
    Mission_Manager_CGN_B.In1_c = Mission_Manager_CGN_B.rtb_SourceBlock_o2_d_c;
  }

  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  Mission_Manager_CGN_B.eul_error[0] = Mission_Manager_CGN_B.In1_c.angle.x *
    0.017453292519943295;
  Mission_Manager_CGN_B.eul_error[1] = Mission_Manager_CGN_B.In1_c.angle.y *
    0.017453292519943295;
  Mission_Manager_CGN_B.eul_error[2] = Mission_Manager_CGN_B.In1_c.angle.z *
    0.017453292519943295;

  // MATLAB Function: '<S5>/eulToQuat'
  Mission_Manager_CGN_B.eta = std::cos(Mission_Manager_CGN_B.eul_error[1]);
  Mission_Manager_CGN_B.t = std::sin(Mission_Manager_CGN_B.eul_error[1]);
  Mission_Manager_CGN_B.scale = std::cos(Mission_Manager_CGN_B.eul_error[2]);
  Mission_Manager_CGN_B.b_t = std::sin(Mission_Manager_CGN_B.eul_error[2]);
  Mission_Manager_CGN_B.absxk = std::sin(Mission_Manager_CGN_B.eul_error[0]);
  Mission_Manager_CGN_B.b_scale = std::cos(Mission_Manager_CGN_B.eul_error[0]);
  Mission_Manager_CGN_B.rotm[0] = Mission_Manager_CGN_B.eta *
    Mission_Manager_CGN_B.scale;
  Mission_Manager_CGN_B.rotm[3] = Mission_Manager_CGN_B.eta *
    Mission_Manager_CGN_B.b_t;
  Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_B.rotm[4] = Mission_Manager_CGN_B.b_absxk *
    Mission_Manager_CGN_B.b_t + Mission_Manager_CGN_B.b_scale *
    Mission_Manager_CGN_B.scale;
  Mission_Manager_CGN_B.rotm[7] = Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.eta;
  Mission_Manager_CGN_B.rotm[8] = Mission_Manager_CGN_B.b_scale *
    Mission_Manager_CGN_B.eta;
  Mission_Manager_CGN_B.eta = std::sqrt(((Mission_Manager_CGN_B.rotm[0] +
    Mission_Manager_CGN_B.rotm[4]) + Mission_Manager_CGN_B.rotm[8]) + 1.0) / 2.0;
  if (Mission_Manager_CGN_B.eta != 0.0) {
    Mission_Manager_CGN_B.psi = Mission_Manager_CGN_B.b_scale *
      Mission_Manager_CGN_B.t;
    Mission_Manager_CGN_B.phi = 4.0 * Mission_Manager_CGN_B.eta;
    Mission_Manager_CGN_B.eps[0] = (Mission_Manager_CGN_B.rotm[7] -
      (Mission_Manager_CGN_B.psi * Mission_Manager_CGN_B.b_t -
       Mission_Manager_CGN_B.absxk * Mission_Manager_CGN_B.scale)) /
      Mission_Manager_CGN_B.phi;
    Mission_Manager_CGN_B.eps[1] = ((Mission_Manager_CGN_B.psi *
      Mission_Manager_CGN_B.scale + Mission_Manager_CGN_B.absxk *
      Mission_Manager_CGN_B.b_t) - (-Mission_Manager_CGN_B.t)) /
      Mission_Manager_CGN_B.phi;
    Mission_Manager_CGN_B.eps[2] = (Mission_Manager_CGN_B.rotm[3] -
      (Mission_Manager_CGN_B.b_absxk * Mission_Manager_CGN_B.scale -
       Mission_Manager_CGN_B.b_scale * Mission_Manager_CGN_B.b_t)) /
      Mission_Manager_CGN_B.phi;
  } else {
    _mm_storeu_pd(&Mission_Manager_CGN_B.eul_error[0], _mm_div_pd(_mm_add_pd
      (_mm_set_pd(Mission_Manager_CGN_B.rotm[4], Mission_Manager_CGN_B.rotm[0]),
       _mm_set1_pd(1.0)), _mm_set1_pd(2.0)));
    Mission_Manager_CGN_B.scale = (Mission_Manager_CGN_B.rotm[8] + 1.0) / 2.0;
    Mission_Manager_CGN_B.eul_error[2] = Mission_Manager_CGN_B.scale;
    if (!std::isnan(Mission_Manager_CGN_B.eul_error[0])) {
      Mission_Manager_CGN_B.i_a = 1;
    } else {
      Mission_Manager_CGN_B.i_a = 0;
      Mission_Manager_CGN_B.b_index = 2;
      exitg1 = false;
      while ((!exitg1) && (Mission_Manager_CGN_B.b_index < 4)) {
        if (!std::isnan
            (Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.b_index - 1]))
        {
          Mission_Manager_CGN_B.i_a = Mission_Manager_CGN_B.b_index;
          exitg1 = true;
        } else {
          Mission_Manager_CGN_B.b_index++;
        }
      }
    }

    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.iindx = 1;
    } else {
      Mission_Manager_CGN_B.b_absxk =
        Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.i_a - 1];
      Mission_Manager_CGN_B.iindx = Mission_Manager_CGN_B.i_a;
      for (Mission_Manager_CGN_B.b_index = Mission_Manager_CGN_B.i_a + 1;
           Mission_Manager_CGN_B.b_index < 4; Mission_Manager_CGN_B.b_index++) {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
          Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.b_index - 1];
        if (Mission_Manager_CGN_B.b_absxk <
            Mission_Manager_CGN_B.rtb_Filter_h_idx_1) {
          Mission_Manager_CGN_B.b_absxk =
            Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
          Mission_Manager_CGN_B.iindx = Mission_Manager_CGN_B.b_index;
        }
      }
    }

    switch (Mission_Manager_CGN_B.iindx) {
     case 1:
      Mission_Manager_CGN_B.eps[0] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[0] + 1.0) / 2.0));
      if (std::isnan(Mission_Manager_CGN_B.rotm[3])) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (Mission_Manager_CGN_B.rotm[3] < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (Mission_Manager_CGN_B.rotm[3]
          > 0.0);
      }

      Mission_Manager_CGN_B.eps[1] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[4] + 1.0) / 2.0)) *
        Mission_Manager_CGN_B.lower_force_index;
      if (std::isnan(-Mission_Manager_CGN_B.t)) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (-Mission_Manager_CGN_B.t < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (-Mission_Manager_CGN_B.t >
          0.0);
      }

      Mission_Manager_CGN_B.eps[2] = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.scale)) * Mission_Manager_CGN_B.lower_force_index;
      break;

     case 2:
      Mission_Manager_CGN_B.eps[1] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[4] + 1.0) / 2.0));
      if (std::isnan(Mission_Manager_CGN_B.rotm[3])) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (Mission_Manager_CGN_B.rotm[3] < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (Mission_Manager_CGN_B.rotm[3]
          > 0.0);
      }

      Mission_Manager_CGN_B.eps[0] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[0] + 1.0) / 2.0)) *
        Mission_Manager_CGN_B.lower_force_index;
      if (std::isnan(Mission_Manager_CGN_B.rotm[7])) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (Mission_Manager_CGN_B.rotm[7] < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (Mission_Manager_CGN_B.rotm[7]
          > 0.0);
      }

      Mission_Manager_CGN_B.eps[2] = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.scale)) * Mission_Manager_CGN_B.lower_force_index;
      break;

     default:
      Mission_Manager_CGN_B.eps[2] = std::sqrt(std::fmax(0.0,
        Mission_Manager_CGN_B.scale));
      if (std::isnan(-Mission_Manager_CGN_B.t)) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (-Mission_Manager_CGN_B.t < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (-Mission_Manager_CGN_B.t >
          0.0);
      }

      Mission_Manager_CGN_B.eps[0] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[0] + 1.0) / 2.0)) *
        Mission_Manager_CGN_B.lower_force_index;
      if (std::isnan(Mission_Manager_CGN_B.rotm[7])) {
        Mission_Manager_CGN_B.lower_force_index = (rtNaN);
      } else if (Mission_Manager_CGN_B.rotm[7] < 0.0) {
        Mission_Manager_CGN_B.lower_force_index = -1.0;
      } else {
        Mission_Manager_CGN_B.lower_force_index = (Mission_Manager_CGN_B.rotm[7]
          > 0.0);
      }

      Mission_Manager_CGN_B.eps[1] = std::sqrt(std::fmax(0.0,
        (Mission_Manager_CGN_B.rotm[4] + 1.0) / 2.0)) *
        Mission_Manager_CGN_B.lower_force_index;
      break;
    }
  }

  Mission_Manager_CGN_B.scale = 3.3121686421112381E-170;
  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.eps[0]);
  if (Mission_Manager_CGN_B.absxk > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.t = 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.absxk /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.eps[1]);
  if (Mission_Manager_CGN_B.absxk > Mission_Manager_CGN_B.scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.scale /
      Mission_Manager_CGN_B.absxk;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.absxk /
      Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.eps[2]);
  if (Mission_Manager_CGN_B.absxk > Mission_Manager_CGN_B.scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.scale /
      Mission_Manager_CGN_B.absxk;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.absxk /
      Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  if (Mission_Manager_CGN_B.eta > Mission_Manager_CGN_B.scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.scale /
      Mission_Manager_CGN_B.eta;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.eta;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.eta /
      Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.scale * std::sqrt
    (Mission_Manager_CGN_B.t);

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  Mission_Manager_CGN_B.dv3[0] =
    Mission_Manager_CGN_B.In1_i.imu_fusion.angular_velocity.x;
  Mission_Manager_CGN_B.dv3[1] =
    Mission_Manager_CGN_B.In1_i.imu_fusion.angular_velocity.y;
  Mission_Manager_CGN_B.dv3[2] =
    Mission_Manager_CGN_B.In1_i.imu_fusion.angular_velocity.z;

  // Product: '<S5>/Matrix Multiply2' incorporates:
  //   Constant: '<S5>/Constant1'

  Mission_Manager_CGN_B.absxk = 0.0;
  Mission_Manager_CGN_B.b_scale = 0.0;
  Mission_Manager_CGN_B.b_t = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_add_pd(_mm_mul_pd
      (_mm_loadu_pd(&Mission_Manager_CGN_ConstP.Constant1_Value_n[3 *
                    Mission_Manager_CGN_B.iindx]), _mm_set1_pd
       (Mission_Manager_CGN_B.dv3[Mission_Manager_CGN_B.iindx])), _mm_set_pd
      (Mission_Manager_CGN_B.b_scale, Mission_Manager_CGN_B.absxk)));
    Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.b_t += Mission_Manager_CGN_ConstP.Constant1_Value_n[3 *
      Mission_Manager_CGN_B.iindx + 2] *
      Mission_Manager_CGN_B.dv3[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.X_est.wb[2] = Mission_Manager_CGN_B.b_t;
  Mission_Manager_CGN_B.X_est.wb[1] = Mission_Manager_CGN_B.b_scale;
  Mission_Manager_CGN_B.X_est.wb[0] = Mission_Manager_CGN_B.absxk;

  // MATLAB Function: '<S5>/discreteTimeQuatPropagation' incorporates:
  //   MATLAB Function: '<S5>/eulToQuat'
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S5>/Matrix Multiply2'
  //
  if (!Mission_Manager_CGN_DW.qk_not_empty) {
    Mission_Manager_CGN_DW.qk[0] = 0.0;
    Mission_Manager_CGN_DW.qk[1] = 0.0;
    Mission_Manager_CGN_DW.qk[2] = 0.0;
    Mission_Manager_CGN_DW.qk[3] = 1.0;
    Mission_Manager_CGN_DW.qk_not_empty = true;
  }

  if (Mission_Manager_CGN_B.b_varargout_1_c) {
    tmp_5 = _mm_div_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.eps[0]), _mm_set1_pd
                       (Mission_Manager_CGN_B.t));
    _mm_storeu_pd(&Mission_Manager_CGN_DW.qk[0], tmp_5);
    Mission_Manager_CGN_DW.qk[2] = Mission_Manager_CGN_B.eps[2] /
      Mission_Manager_CGN_B.t;
    Mission_Manager_CGN_DW.qk[3] = Mission_Manager_CGN_B.eta /
      Mission_Manager_CGN_B.t;
  }

  Mission_Manager_CGN_B.scale = 3.3121686421112381E-170;
  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.absxk);
  if (Mission_Manager_CGN_B.absxk > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.eta = 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.absxk /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.t;
  }

  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.b_scale);
  if (Mission_Manager_CGN_B.absxk > Mission_Manager_CGN_B.scale) {
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.scale /
      Mission_Manager_CGN_B.absxk;
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.eta *
      Mission_Manager_CGN_B.t * Mission_Manager_CGN_B.t + 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.absxk /
      Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_B.eta += Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.t;
  }

  Mission_Manager_CGN_B.absxk = std::abs(Mission_Manager_CGN_B.b_t);
  if (Mission_Manager_CGN_B.absxk > Mission_Manager_CGN_B.scale) {
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.scale /
      Mission_Manager_CGN_B.absxk;
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.eta *
      Mission_Manager_CGN_B.t * Mission_Manager_CGN_B.t + 1.0;
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.absxk;
  } else {
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.absxk /
      Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_B.eta += Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.t;
  }

  Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.scale * std::sqrt
    (Mission_Manager_CGN_B.eta);
  if (Mission_Manager_CGN_B.eta > 1.0E-10) {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = std::sin(0.5 *
      Mission_Manager_CGN_B.eta * 0.01) / Mission_Manager_CGN_B.eta;
    tmp_5 = _mm_mul_pd(_mm_set1_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1),
                       _mm_loadu_pd(&Mission_Manager_CGN_B.X_est.wb[0]));
    _mm_storeu_pd(&Mission_Manager_CGN_B.eps[0], tmp_5);
    Mission_Manager_CGN_B.eps[2] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1 *
      Mission_Manager_CGN_B.b_t;
  } else {
    tmp_5 = _mm_mul_pd(_mm_set1_pd(0.005), _mm_loadu_pd
                       (&Mission_Manager_CGN_B.X_est.wb[0]));
    _mm_storeu_pd(&Mission_Manager_CGN_B.eps[0], tmp_5);
    Mission_Manager_CGN_B.eps[2] = 0.005 * Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_B.eta = std::cos(0.5 * Mission_Manager_CGN_B.eta * 0.01);
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 9;
       Mission_Manager_CGN_B.iindx++) {
    // MATLAB Function: '<S5>/quatToRotm' incorporates:
    //   MATLAB Function: '<S5>/derivedStateEstimates'

    Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx] =
      b_0[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[0] = 0.0;
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3] = -Mission_Manager_CGN_B.eps[2];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[6] = Mission_Manager_CGN_B.eps[1];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[1] = Mission_Manager_CGN_B.eps[2];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[4] = 0.0;
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[7] = -Mission_Manager_CGN_B.eps[0];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[2] = -Mission_Manager_CGN_B.eps[1];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[5] = Mission_Manager_CGN_B.eps[0];
  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[8] = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    tmp_5 = _mm_sub_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.rotm[3 *
      Mission_Manager_CGN_B.iindx]), _mm_set1_pd(Mission_Manager_CGN_B.eta)),
                       _mm_loadu_pd(&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 *
      Mission_Manager_CGN_B.iindx]));
    Mission_Manager_CGN_B.loop_ub = Mission_Manager_CGN_B.iindx << 2;
    _mm_storeu_pd(&Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub],
                  tmp_5);
    Mission_Manager_CGN_B.i_a = 3 * Mission_Manager_CGN_B.iindx + 2;
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub + 2] =
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.i_a] *
      Mission_Manager_CGN_B.eta -
      Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.i_a];
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.iindx + 12] =
      Mission_Manager_CGN_B.eps[Mission_Manager_CGN_B.iindx];
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub + 3] =
      -Mission_Manager_CGN_B.eps[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.c_a[15] = Mission_Manager_CGN_B.eta;
  Mission_Manager_CGN_B.t = 0.0;
  Mission_Manager_CGN_B.eta = 0.0;
  Mission_Manager_CGN_B.scale = 0.0;
  Mission_Manager_CGN_B.absxk = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 4;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.loop_ub = Mission_Manager_CGN_B.iindx << 2;
    tmp_5 = _mm_set1_pd(Mission_Manager_CGN_DW.qk[Mission_Manager_CGN_B.iindx]);
    tmp_4 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub]), tmp_5),
                       _mm_set_pd(Mission_Manager_CGN_B.eta,
      Mission_Manager_CGN_B.t));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_4);
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.dv9[1];
    tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub + 2]), tmp_5),
                       _mm_set_pd(Mission_Manager_CGN_B.absxk,
      Mission_Manager_CGN_B.scale));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_5);
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_B.dv9[1];
  }

  Mission_Manager_CGN_B.b_scale = 3.3121686421112381E-170;
  Mission_Manager_CGN_DW.qk[0] = Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_B.b_absxk = std::abs(Mission_Manager_CGN_DW.qk[0]);
  if (Mission_Manager_CGN_B.b_absxk > 3.3121686421112381E-170) {
    Mission_Manager_CGN_B.t = 1.0;
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.b_absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_absxk /
      3.3121686421112381E-170;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_DW.qk[1] = Mission_Manager_CGN_B.eta;
  Mission_Manager_CGN_B.b_absxk = std::abs(Mission_Manager_CGN_DW.qk[1]);
  if (Mission_Manager_CGN_B.b_absxk > Mission_Manager_CGN_B.b_scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_scale /
      Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.b_absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_absxk /
      Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_DW.qk[2] = Mission_Manager_CGN_B.scale;
  Mission_Manager_CGN_B.b_absxk = std::abs(Mission_Manager_CGN_DW.qk[2]);
  if (Mission_Manager_CGN_B.b_absxk > Mission_Manager_CGN_B.b_scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_scale /
      Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.b_absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_absxk /
      Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_DW.qk[3] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.b_absxk = std::abs(Mission_Manager_CGN_DW.qk[3]);
  if (Mission_Manager_CGN_B.b_absxk > Mission_Manager_CGN_B.b_scale) {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_scale /
      Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.t *
      Mission_Manager_CGN_B.b_t * Mission_Manager_CGN_B.b_t + 1.0;
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.b_absxk;
  } else {
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.b_absxk /
      Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_B.t += Mission_Manager_CGN_B.b_t *
      Mission_Manager_CGN_B.b_t;
  }

  Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.b_scale * std::sqrt
    (Mission_Manager_CGN_B.t);
  Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_DW.qk[0] /
    Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_DW.qk[0] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.X_est.qib[0] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_DW.qk[1] /
    Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_DW.qk[1] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.X_est.qib[1] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_DW.qk[2] /
    Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_DW.qk[2] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.X_est.qib[2] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.absxk = Mission_Manager_CGN_DW.qk[3] /
    Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_DW.qk[3] = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.X_est.qib[3] = Mission_Manager_CGN_B.absxk;

  // MATLAB Function: '<S5>/quatToRotm' incorporates:
  //   MATLAB Function: '<S18>/guidanceLaw'
  //   MATLAB Function: '<S18>/quatToRotm'
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'
  //   Math: '<S5>/Transpose'

  Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.absxk * 2.0 - 1.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 2.0 * Mission_Manager_CGN_B.absxk;

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.rtb_Cbi_tmp[3 * Mission_Manager_CGN_B.iindx] = 2.0 *
      Mission_Manager_CGN_B.X_est.qib[0] *
      Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.iindx];

    // Math: '<S5>/Transpose' incorporates:
    //   MATLAB Function: '<S19>/commandExecuter'
    //   Math: '<S18>/Transpose'

    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 * Mission_Manager_CGN_B.iindx] =
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx];
    Mission_Manager_CGN_B.i_a = 3 * Mission_Manager_CGN_B.iindx + 1;
    Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.i_a] = 2.0 *
      Mission_Manager_CGN_B.X_est.qib[1] *
      Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.iindx];

    // Math: '<S5>/Transpose' incorporates:
    //   MATLAB Function: '<S19>/commandExecuter'
    //   Math: '<S18>/Transpose'

    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx + 3];
    Mission_Manager_CGN_B.i_a = 3 * Mission_Manager_CGN_B.iindx + 2;
    Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.i_a] = 2.0 *
      Mission_Manager_CGN_B.X_est.qib[2] *
      Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.iindx];

    // Math: '<S5>/Transpose' incorporates:
    //   MATLAB Function: '<S19>/commandExecuter'
    //   Math: '<S18>/Transpose'

    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx + 6];
  }

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    tmp_5 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 * Mission_Manager_CGN_B.iindx]),
      _mm_set1_pd(Mission_Manager_CGN_B.eta)), _mm_set_pd
                       (Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.iindx
                        + 3],
                        Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.iindx]));
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi[3 * Mission_Manager_CGN_B.iindx],
                  tmp_5);

    // Math: '<S5>/Transpose'
    Mission_Manager_CGN_B.i_a = 3 * Mission_Manager_CGN_B.iindx + 2;
    Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.i_a] *
      Mission_Manager_CGN_B.eta +
      Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.iindx + 6];
  }

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d =
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 * 0.0;

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'

  // Math: '<S5>/Transpose' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/quatToRotm'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_b[0] =
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // MATLAB Function: '<S5>/quatToRotm'
  tmp_5 = _mm_set1_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1);
  tmp_4 = _mm_mul_pd(tmp_5, _mm_set_pd(Mission_Manager_CGN_B.X_est.qib[1],
    -Mission_Manager_CGN_B.X_est.qib[2]));

  // Math: '<S5>/Transpose'
  _mm_storeu_pd(&Mission_Manager_CGN_B.rtb_Cbi_tmp_b[1], tmp_4);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S5>/quatToRotm' incorporates:
  //   MATLAB Function: '<S18>/guidanceLaw'
  //   MATLAB Function: '<S18>/quatToRotm'
  //   MATLAB Function: '<S5>/derivedStateEstimates'

  Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 =
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 * Mission_Manager_CGN_B.X_est.qib[2];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'

  // Math: '<S5>/Transpose' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/quatToRotm'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_b[3] =
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_1;
  Mission_Manager_CGN_B.rtb_Cbi_tmp_b[4] =
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // MATLAB Function: '<S5>/quatToRotm'
  tmp_6 = _mm_set_pd(-Mission_Manager_CGN_B.X_est.qib[1],
                     -Mission_Manager_CGN_B.X_est.qib[0]);
  tmp_5 = _mm_mul_pd(tmp_5, tmp_6);

  // Math: '<S5>/Transpose'
  _mm_storeu_pd(&Mission_Manager_CGN_B.rtb_Cbi_tmp_b[5], tmp_5);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S5>/quatToRotm' incorporates:
  //   MATLAB Function: '<S18>/guidanceLaw'
  //   MATLAB Function: '<S18>/quatToRotm'
  //   MATLAB Function: '<S5>/derivedStateEstimates'

  Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 =
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 * Mission_Manager_CGN_B.X_est.qib[0];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'

  // Math: '<S5>/Transpose' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/quatToRotm'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_b[7] =
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_2;
  Mission_Manager_CGN_B.rtb_Cbi_tmp_b[8] =
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
       Mission_Manager_CGN_B.iindx += 2) {
    tmp_2 = _mm_loadu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx]);
    tmp_3 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_b[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx],
                  _mm_add_pd(tmp_2, tmp_3));
  }

  for (Mission_Manager_CGN_B.iindx = 8; Mission_Manager_CGN_B.iindx < 9;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx] =
      Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx] +
      Mission_Manager_CGN_B.rtb_Cbi_tmp_b[Mission_Manager_CGN_B.iindx];
  }

  // MATLAB Function: '<S5>/dvl_reset' incorporates:
  //   DataStoreRead: '<S5>/Data Store Read3'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'

  if (Mission_Manager_CGN_DW.prior_flag &&
      (!Mission_Manager_CGN_DW.joystick_mode_enabled_flag)) {
    Mission_Manager_CGN_DW.offset[0] = Mission_Manager_CGN_B.In1_c.position.x;
    Mission_Manager_CGN_DW.offset[1] = Mission_Manager_CGN_B.In1_c.position.y;
    Mission_Manager_CGN_DW.offset[2] = Mission_Manager_CGN_B.In1_c.position.z;
  }

  Mission_Manager_CGN_DW.prior_flag =
    Mission_Manager_CGN_DW.joystick_mode_enabled_flag;
  Mission_Manager_CGN_B.rtb_dvl_pos_g[0] =
    Mission_Manager_CGN_B.In1_c.position.x - Mission_Manager_CGN_DW.offset[0];
  Mission_Manager_CGN_B.rtb_dvl_pos_g[1] =
    Mission_Manager_CGN_B.In1_c.position.y - Mission_Manager_CGN_DW.offset[1];
  Mission_Manager_CGN_B.rtb_dvl_pos_g[2] =
    Mission_Manager_CGN_B.In1_c.position.z - Mission_Manager_CGN_DW.offset[2];

  // End of MATLAB Function: '<S5>/dvl_reset'

  // Product: '<S5>/Matrix Multiply3' incorporates:
  //   Math: '<S5>/Transpose'

  Mission_Manager_CGN_B.phi = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.Cbi_c[3 *
      Mission_Manager_CGN_B.iindx]), _mm_set1_pd
      (Mission_Manager_CGN_B.rtb_dvl_pos_g[Mission_Manager_CGN_B.iindx])),
                       _mm_set_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1,
      Mission_Manager_CGN_B.phi));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.phi = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.rtb_Filter_h_idx_0 += Mission_Manager_CGN_B.Cbi_c[3 *
      Mission_Manager_CGN_B.iindx + 2] *
      Mission_Manager_CGN_B.rtb_dvl_pos_g[Mission_Manager_CGN_B.iindx];
  }

  // DiscreteIntegrator: '<S5>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S5>/Matrix Multiply3'
  //
  if (Mission_Manager_CGN_DW.PositionIntegrator_IC_LOADING != 0) {
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[0] =
      Mission_Manager_CGN_B.phi;
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[1] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[2] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
  }

  if (Mission_Manager_CGN_B.b_varargout_1_c &&
      (Mission_Manager_CGN_DW.PositionIntegrator_PrevResetSta <= 0)) {
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[0] =
      Mission_Manager_CGN_B.phi;
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[1] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[2] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
  }

  // DiscreteIntegrator: '<S5>/Velocity Integrator' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLABSystem: '<S6>/SourceBlock'
  //
  if (Mission_Manager_CGN_DW.VelocityIntegrator_IC_LOADING != 0) {
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0] =
      Mission_Manager_CGN_B.In1.velocity_data.x;
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1] =
      Mission_Manager_CGN_B.In1.velocity_data.y;
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2] =
      Mission_Manager_CGN_B.In1.velocity_data.z;
  }

  if (Mission_Manager_CGN_B.b_varargout_1_g &&
      (Mission_Manager_CGN_DW.VelocityIntegrator_PrevResetSta <= 0)) {
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0] =
      Mission_Manager_CGN_B.In1.velocity_data.x;
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1] =
      Mission_Manager_CGN_B.In1.velocity_data.y;
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2] =
      Mission_Manager_CGN_B.In1.velocity_data.z;
  }

  // Product: '<S5>/Matrix Multiply' incorporates:
  //   Constant: '<S5>/Constant'
  //   Math: '<S5>/Transpose'

  Mission_Manager_CGN_B.t = 0.0;
  Mission_Manager_CGN_B.scale = 0.0;
  Mission_Manager_CGN_B.b_t = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.Cbi_c[3 *
      Mission_Manager_CGN_B.iindx]), _mm_set1_pd
      (Mission_Manager_CGN_ConstP.Constant_Value_n[Mission_Manager_CGN_B.iindx])),
                       _mm_set_pd(Mission_Manager_CGN_B.scale,
      Mission_Manager_CGN_B.t));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.b_t += Mission_Manager_CGN_B.Cbi_c[3 *
      Mission_Manager_CGN_B.iindx + 2] *
      Mission_Manager_CGN_ConstP.Constant_Value_n[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.eul_error[2] = Mission_Manager_CGN_B.b_t;
  Mission_Manager_CGN_B.eul_error[1] = Mission_Manager_CGN_B.scale;
  Mission_Manager_CGN_B.eul_error[0] = Mission_Manager_CGN_B.t;

  // End of Product: '<S5>/Matrix Multiply'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  Mission_Manager_CGN_B.t =
    Mission_Manager_CGN_B.In1_i.imu_fusion.linear_acceleration.y;
  Mission_Manager_CGN_B.scale =
    Mission_Manager_CGN_B.In1_i.imu_fusion.linear_acceleration.x;
  Mission_Manager_CGN_B.b_t =
    Mission_Manager_CGN_B.In1_i.imu_fusion.linear_acceleration.z;

  // Sum: '<S5>/Sum' incorporates:
  //   Constant: '<S5>/Constant1'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   Product: '<S5>/Matrix Multiply1'

  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 0;
       Mission_Manager_CGN_B.iindx += 2) {
    tmp_2 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd
      (&Mission_Manager_CGN_B.rtb_dvl_pos_g[Mission_Manager_CGN_B.iindx],
       _mm_sub_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd
           (&Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx
            + 3]), _mm_set1_pd(Mission_Manager_CGN_B.t)), _mm_mul_pd
          (_mm_loadu_pd
           (&Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx]),
           _mm_set1_pd(Mission_Manager_CGN_B.scale))), _mm_mul_pd(_mm_loadu_pd
          (&Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx
           + 6]), _mm_set1_pd(Mission_Manager_CGN_B.b_t))), tmp_2));
  }

  for (Mission_Manager_CGN_B.iindx = 2; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.rtb_dvl_pos_g[Mission_Manager_CGN_B.iindx] =
      ((Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx
        + 3] * Mission_Manager_CGN_B.t +
        Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx]
        * Mission_Manager_CGN_B.scale) +
       Mission_Manager_CGN_ConstP.Constant1_Value_n[Mission_Manager_CGN_B.iindx
       + 6] * Mission_Manager_CGN_B.b_t) -
      Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.iindx];
  }

  // End of Sum: '<S5>/Sum'

  // MATLAB Function: '<S5>/derivedStateEstimates'
  Mission_Manager_CGN_B.Cbi_c[0] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_4);

  // MATLAB Function: '<S5>/derivedStateEstimates'
  Mission_Manager_CGN_B.Cbi_c[3] = Mission_Manager_CGN_B.dv9[0];
  Mission_Manager_CGN_B.Cbi_c[6] = Mission_Manager_CGN_B.dv9[1];
  Mission_Manager_CGN_B.Cbi_c[1] = Mission_Manager_CGN_B.rtb_Integrator_f_idx_1;
  Mission_Manager_CGN_B.Cbi_c[4] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_5);

  // MATLAB Function: '<S5>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S5>/Position Integrator'
  //   DiscreteIntegrator: '<S5>/Velocity Integrator'

  Mission_Manager_CGN_B.Cbi_c[7] = Mission_Manager_CGN_B.dv9[0];
  Mission_Manager_CGN_B.Cbi_c[2] = Mission_Manager_CGN_B.dv9[1];
  Mission_Manager_CGN_B.Cbi_c[5] = Mission_Manager_CGN_B.rtb_Integrator_f_idx_2;
  Mission_Manager_CGN_B.Cbi_c[8] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
       Mission_Manager_CGN_B.iindx += 2) {
    tmp_2 = _mm_loadu_pd(&Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx]);
    tmp_3 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.iindx]);
    tmp_1 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.X_est.Cib[Mission_Manager_CGN_B.iindx],
                  _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd
      (Mission_Manager_CGN_B.eta), tmp_2), tmp_3), tmp_1));
    tmp_2 = _mm_loadu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx]);
    tmp_3 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_b[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx],
                  _mm_add_pd(tmp_2, tmp_3));
  }

  for (Mission_Manager_CGN_B.iindx = 8; Mission_Manager_CGN_B.iindx < 9;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.X_est.Cib[Mission_Manager_CGN_B.iindx] =
      (Mission_Manager_CGN_B.eta *
       Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx] +
       Mission_Manager_CGN_B.rtb_Cbi_tmp[Mission_Manager_CGN_B.iindx]) +
      Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx];
    Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx] +=
      Mission_Manager_CGN_B.rtb_Cbi_tmp_b[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.b_absxk = std::asin(std::fmax(-1.0, std::fmin(1.0,
    Mission_Manager_CGN_B.Cbi[6])));
  if (std::abs(std::cos(-Mission_Manager_CGN_B.b_absxk)) < 1.0E-6) {
    Mission_Manager_CGN_B.t = 0.0;
    Mission_Manager_CGN_B.psi = Mission_Manager_C_rt_atan2d_snf
      (-Mission_Manager_CGN_B.Cbi[1], Mission_Manager_CGN_B.Cbi[4]);
  } else {
    Mission_Manager_CGN_B.t = Mission_Manager_C_rt_atan2d_snf
      (Mission_Manager_CGN_B.Cbi[7], Mission_Manager_CGN_B.Cbi[8]);
    Mission_Manager_CGN_B.psi = Mission_Manager_C_rt_atan2d_snf
      (Mission_Manager_CGN_B.Cbi[3], Mission_Manager_CGN_B.Cbi[0]);
  }

  Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.t);
  Mission_Manager_CGN_B.b_absxk = -Mission_Manager_CGN_B.b_absxk;
  Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.b_absxk);
  Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.psi);
  Mission_Manager_CGN_B.scale = 0.0;
  Mission_Manager_CGN_B.b_t = 0.0;
  Mission_Manager_CGN_B.b_scale = 0.0;
  Mission_Manager_CGN_B.X_est.Eul[0] = Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_B.X_est.Eul[1] = Mission_Manager_CGN_B.b_absxk;
  Mission_Manager_CGN_B.X_est.Eul[2] = Mission_Manager_CGN_B.psi;
  Mission_Manager_CGN_B.rtb_X_est_idx_0 = 0.0;
  Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0 = 0.0;
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.X_est.Cib
      [3 * Mission_Manager_CGN_B.iindx]), _mm_set1_pd
      (Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[Mission_Manager_CGN_B.iindx])),
                       _mm_set_pd(Mission_Manager_CGN_B.b_t,
      Mission_Manager_CGN_B.scale));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.dv9[1];
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_add_pd(_mm_mul_pd
      (_mm_set_pd(Mission_Manager_CGN_B.X_est.Cib[3 *
                  Mission_Manager_CGN_B.iindx], Mission_Manager_CGN_B.X_est.Cib
                  [3 * Mission_Manager_CGN_B.iindx + 2]), _mm_set_pd
       (Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[Mission_Manager_CGN_B.iindx],
        Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[Mission_Manager_CGN_B.iindx])),
      _mm_set_pd(Mission_Manager_CGN_B.rtb_X_est_idx_0,
                 Mission_Manager_CGN_B.b_scale)));
    Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_X_est_idx_0 = Mission_Manager_CGN_B.dv9[1];
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.X_est.Cib
      [3 * Mission_Manager_CGN_B.iindx + 1]), _mm_set1_pd
      (Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[Mission_Manager_CGN_B.iindx])),
                       _mm_set_pd(Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0,
      Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0 =
      Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 = Mission_Manager_CGN_B.dv9[1];
  }

  Mission_Manager_CGN_B.X_est.Ri[0] = Mission_Manager_CGN_B.scale;
  Mission_Manager_CGN_B.X_est.Ri[1] = Mission_Manager_CGN_B.b_t;
  Mission_Manager_CGN_B.X_est.Ri[2] = Mission_Manager_CGN_B.b_scale;

  // MATLAB Function: '<S19>/commandExecuter' incorporates:
  //   MATLAB Function: '<S1>/cmdMsgToCmdBus'
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'
  //   MATLABSystem: '<S10>/SourceBlock'
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'
  //
  if (!Mission_Manager_CGN_DW.hold_timer_start_time_not_empty) {
    Mission_Manager_CGN_DW.hold_timer_start_time =
      Mission_Manager_CGN_B.DigitalClock;
    Mission_Manager_CGN_DW.hold_timer_start_time_not_empty = true;
  }

  if (!Mission_Manager_CGN_DW.idle_wp_not_empty) {
    Mission_Manager_CGN_DW.idle_wp[0] = Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_DW.idle_wp[1] = Mission_Manager_CGN_B.b_t;
    Mission_Manager_CGN_DW.idle_wp[2] = Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_DW.idle_wp[3] = 0.0;
    Mission_Manager_CGN_DW.idle_wp[4] = 0.0;
    Mission_Manager_CGN_DW.idle_wp[5] = Mission_Manager_CGN_B.psi;
    Mission_Manager_CGN_DW.idle_wp_not_empty = true;
  }

  if (!Mission_Manager_CGN_DW.cmd_specific_wp_not_empty) {
    for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 6;
         Mission_Manager_CGN_B.i_a++) {
      Mission_Manager_CGN_DW.cmd_specific_wp[Mission_Manager_CGN_B.i_a] =
        Mission_Manager_CGN_DW.idle_wp[Mission_Manager_CGN_B.i_a];
    }

    Mission_Manager_CGN_DW.cmd_specific_wp_not_empty = true;
  }

  if ((Mission_Manager_CGN_DW.UnitDelay_DSTATE == 2.0) &&
      (Mission_Manager_CGN_DW.prior_action_id != 2.0)) {
    Mission_Manager_CGN_DW.idle_wp[5] = Mission_Manager_CGN_DW.UnitDelay1_DSTATE;
  }

  Mission_Manager_CGN_DW.prior_action_id =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE;
  if (Mission_Manager_CGN_B.b_varargout_1) {
    Mission_Manager_CGN_DW.idle_wp[0] = Mission_Manager_CGN_B.scale;
    Mission_Manager_CGN_DW.idle_wp[1] = Mission_Manager_CGN_B.b_t;
    Mission_Manager_CGN_DW.idle_wp[2] = Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_DW.idle_wp[3] = 0.0;
    Mission_Manager_CGN_DW.idle_wp[4] = 0.0;
    Mission_Manager_CGN_DW.idle_wp[5] = Mission_Manager_CGN_B.psi;
    Mission_Manager_CGN_DW.hold_timer_start_time =
      Mission_Manager_CGN_B.DigitalClock;
    Mission_Manager_CGN_DW.prior_action_id = 0.0;
    Mission_Manager_CGN_B.varargin_2_p[16] = '\x00';
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.varargin_2_p[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.cmd_id[Mission_Manager_CGN_B.iindx];
      Mission_Manager_CGN_B.varargin_3_l[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.varargin_3_l[16] = '\x00';
    std::printf("%.2f: Working on command %s with trick %s.\n",
                Mission_Manager_CGN_B.DigitalClock,
                &Mission_Manager_CGN_B.varargin_2_p[0],
                &Mission_Manager_CGN_B.varargin_3_l[0]);
    std::fflush(stdout);
  }

  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.switch_expression[Mission_Manager_CGN_B.iindx] =
      Mission_Manager_CGN_B.cmd.cmd_id[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.i_a = std::memcmp(&c_a_0[0],
    &Mission_Manager_CGN_B.switch_expression[0], 16);
  if (Mission_Manager_CGN_B.i_a == 0) {
    Mission_Manager_CGN_B.b_index = 0;
  } else {
    Mission_Manager_CGN_B.i_a = std::memcmp(&d_a[0],
      &Mission_Manager_CGN_B.switch_expression[0], 16);
    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.b_index = 1;
    } else {
      Mission_Manager_CGN_B.b_index = -1;
    }
  }

  switch (Mission_Manager_CGN_B.b_index) {
   case 0:
    Mission_Manager_CGN_B.dv3[0] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.roll) *
      Mission_Manager_CGN_DW.idle_wp[3] +
      Mission_Manager_CGN_B.In1_j.waypoint.roll * static_cast<real_T>
      (Mission_Manager_CGN_B.In1_j.waypoint_mask.roll);
    Mission_Manager_CGN_B.X_u[0] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.x) *
      Mission_Manager_CGN_DW.idle_wp[0] + Mission_Manager_CGN_B.In1_j.waypoint.x
      * static_cast<real_T>(Mission_Manager_CGN_B.In1_j.waypoint_mask.x);
    Mission_Manager_CGN_B.dv3[1] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.pitch) *
      Mission_Manager_CGN_DW.idle_wp[4] +
      Mission_Manager_CGN_B.In1_j.waypoint.pitch * static_cast<real_T>
      (Mission_Manager_CGN_B.In1_j.waypoint_mask.pitch);
    Mission_Manager_CGN_B.X_u[1] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.y) *
      Mission_Manager_CGN_DW.idle_wp[1] + Mission_Manager_CGN_B.In1_j.waypoint.y
      * static_cast<real_T>(Mission_Manager_CGN_B.In1_j.waypoint_mask.y);
    Mission_Manager_CGN_B.dv3[2] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.yaw) *
      Mission_Manager_CGN_DW.idle_wp[5] +
      Mission_Manager_CGN_B.In1_j.waypoint.yaw * static_cast<real_T>
      (Mission_Manager_CGN_B.In1_j.waypoint_mask.yaw);
    Mission_Manager_CGN_B.X_u[2] = static_cast<real_T>
      (!Mission_Manager_CGN_B.In1_j.waypoint_mask.z) *
      Mission_Manager_CGN_DW.idle_wp[2] + Mission_Manager_CGN_B.In1_j.waypoint.z
      * static_cast<real_T>(Mission_Manager_CGN_B.In1_j.waypoint_mask.z);
    Mission_Manager_CGN_eulToQuat_k(Mission_Manager_CGN_B.dv3,
      Mission_Manager_CGN_B.dv1);
    Mission_Manager_CGN_B.X_u[3] = Mission_Manager_CGN_B.dv1[0];
    Mission_Manager_CGN_B.X_u[4] = Mission_Manager_CGN_B.dv1[1];
    Mission_Manager_CGN_B.X_u[5] = Mission_Manager_CGN_B.dv1[2];
    Mission_Manager_CGN_B.X_u[6] = Mission_Manager_CGN_B.dv1[3];
    Mission_Manager_CGN_B.X_u[7] = 0.0;
    Mission_Manager_CGN_B.X_u[10] = 0.0;
    Mission_Manager_CGN_B.X_u[8] = 0.0;
    Mission_Manager_CGN_B.X_u[11] = 0.0;
    Mission_Manager_CGN_B.X_u[9] = 0.0;
    Mission_Manager_CGN_B.X_u[12] = 0.0;
    Mission_Manager_CGN_B.b_absxk = ((Mission_Manager_CGN_B.absxk *
      Mission_Manager_CGN_B.dv1[3] - -Mission_Manager_CGN_B.X_est.qib[0] *
      Mission_Manager_CGN_B.dv1[0]) - -Mission_Manager_CGN_B.X_est.qib[1] *
      Mission_Manager_CGN_B.dv1[1]) - -Mission_Manager_CGN_B.X_est.qib[2] *
      Mission_Manager_CGN_B.dv1[2];
    tmp_2 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd
      (Mission_Manager_CGN_B.absxk), _mm_loadu_pd(&Mission_Manager_CGN_B.dv1[0])),
      _mm_mul_pd(_mm_set1_pd(Mission_Manager_CGN_B.dv1[3]), tmp_6)), _mm_sub_pd
                       (_mm_mul_pd(_mm_set_pd(Mission_Manager_CGN_B.dv1[0],
      -Mission_Manager_CGN_B.X_est.qib[1]), _mm_set_pd
      (-Mission_Manager_CGN_B.X_est.qib[2], Mission_Manager_CGN_B.dv1[2])),
                        _mm_mul_pd(_mm_set_pd(-Mission_Manager_CGN_B.X_est.qib[0],
      Mission_Manager_CGN_B.dv1[1]), _mm_set_pd(Mission_Manager_CGN_B.dv1[2],
      -Mission_Manager_CGN_B.X_est.qib[2]))));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.psi = (Mission_Manager_CGN_B.absxk *
      Mission_Manager_CGN_B.dv1[2] + Mission_Manager_CGN_B.dv1[3] *
      -Mission_Manager_CGN_B.X_est.qib[2]) + (-Mission_Manager_CGN_B.X_est.qib[0]
      * Mission_Manager_CGN_B.dv1[1] - Mission_Manager_CGN_B.dv1[0] *
      -Mission_Manager_CGN_B.X_est.qib[1]);
    Mission_Manager_CGN_B.qinv[0] = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.qinv[1] = Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.qinv[2] = Mission_Manager_CGN_B.psi;
    Mission_Manager_CGN_B.qinv[3] = Mission_Manager_CGN_B.b_absxk;
    if (Mission_Manager_CGN_B.b_absxk < 0.0) {
      Mission_Manager_CGN_B.qinv[0] = -Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.qinv[1] = -Mission_Manager_CGN_B.dv9[1];
      Mission_Manager_CGN_B.qinv[2] = -Mission_Manager_CGN_B.psi;
      Mission_Manager_CGN_B.qinv[3] = -Mission_Manager_CGN_B.b_absxk;
    }

    Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.qinv[3] *
      Mission_Manager_CGN_B.qinv[3] * 2.0 - 1.0;
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 2.0 * Mission_Manager_CGN_B.qinv
      [3];
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
         Mission_Manager_CGN_B.iindx++) {
      tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 * Mission_Manager_CGN_B.iindx]),
        _mm_set1_pd(Mission_Manager_CGN_B.b_absxk)), _mm_mul_pd(_mm_mul_pd
        (_mm_set1_pd(2.0), _mm_set1_pd
         (Mission_Manager_CGN_B.qinv[Mission_Manager_CGN_B.iindx])),
        _mm_loadu_pd(&Mission_Manager_CGN_B.qinv[0])));
      _mm_storeu_pd(&Mission_Manager_CGN_B.rotm[3 * Mission_Manager_CGN_B.iindx],
                    tmp_2);
      Mission_Manager_CGN_B.b_index = 3 * Mission_Manager_CGN_B.iindx + 2;
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.b_index] = 2.0 *
        Mission_Manager_CGN_B.qinv[Mission_Manager_CGN_B.iindx] *
        Mission_Manager_CGN_B.qinv[2] +
        Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.b_index] *
        Mission_Manager_CGN_B.b_absxk;
    }

    Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.rtb_Filter_h_idx_1 *
      0.0;
    Mission_Manager_CGN_B.Cbi_c[0] = Mission_Manager_CGN_B.b_absxk;
    tmp_2 = _mm_set1_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1);
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[1], _mm_mul_pd(tmp_2, _mm_set_pd
      (Mission_Manager_CGN_B.qinv[1], -Mission_Manager_CGN_B.qinv[2])));
    Mission_Manager_CGN_B.Cbi_c[3] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1 *
      Mission_Manager_CGN_B.qinv[2];
    Mission_Manager_CGN_B.Cbi_c[4] = Mission_Manager_CGN_B.b_absxk;
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[5], _mm_mul_pd(tmp_2, _mm_set_pd(
      -Mission_Manager_CGN_B.qinv[1], -Mission_Manager_CGN_B.qinv[0])));
    Mission_Manager_CGN_B.Cbi_c[7] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1 *
      Mission_Manager_CGN_B.qinv[0];
    Mission_Manager_CGN_B.Cbi_c[8] = Mission_Manager_CGN_B.b_absxk;
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
         Mission_Manager_CGN_B.iindx += 2) {
      tmp_2 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx]);
      tmp_3 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx]);
      _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx],
                    _mm_add_pd(tmp_2, tmp_3));
    }

    for (Mission_Manager_CGN_B.iindx = 8; Mission_Manager_CGN_B.iindx < 9;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx] +
        Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.b_absxk = std::asin(std::fmax(-1.0, std::fmin(1.0,
      Mission_Manager_CGN_B.Cbi[6])));
    if (std::abs(std::cos(-Mission_Manager_CGN_B.b_absxk)) < 1.0E-6) {
      Mission_Manager_CGN_B.phi = 0.0;
      Mission_Manager_CGN_B.psi = Mission_Manager_C_rt_atan2d_snf
        (-Mission_Manager_CGN_B.Cbi[1], Mission_Manager_CGN_B.Cbi[4]);
    } else {
      Mission_Manager_CGN_B.phi = Mission_Manager_C_rt_atan2d_snf
        (Mission_Manager_CGN_B.Cbi[7], Mission_Manager_CGN_B.Cbi[8]);
      Mission_Manager_CGN_B.psi = Mission_Manager_C_rt_atan2d_snf
        (Mission_Manager_CGN_B.Cbi[3], Mission_Manager_CGN_B.Cbi[0]);
    }

    Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.phi);
    Mission_Manager_CGN_B.b_absxk = -Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.b_absxk);
    Mission_Manager_CGN_wrapToPi(&Mission_Manager_CGN_B.psi);
    Mission_Manager_CGN_B.b_x[0] = (std::abs(Mission_Manager_CGN_B.scale -
      Mission_Manager_CGN_B.X_u[0]) < Mission_Manager_CGN_B.In1_j.tolerance.x);
    Mission_Manager_CGN_B.b_x[3] = (std::abs(Mission_Manager_CGN_B.phi) <
      Mission_Manager_CGN_B.In1_j.tolerance.roll);
    Mission_Manager_CGN_B.b_x[1] = (std::abs(Mission_Manager_CGN_B.b_t -
      Mission_Manager_CGN_B.X_u[1]) < Mission_Manager_CGN_B.In1_j.tolerance.y);
    Mission_Manager_CGN_B.b_x[4] = (std::abs(Mission_Manager_CGN_B.b_absxk) <
      Mission_Manager_CGN_B.In1_j.tolerance.pitch);
    Mission_Manager_CGN_B.b_x[2] = (std::abs(Mission_Manager_CGN_B.b_scale -
      Mission_Manager_CGN_B.X_u[2]) < Mission_Manager_CGN_B.In1_j.tolerance.z);
    Mission_Manager_CGN_B.b_x[5] = (std::abs(Mission_Manager_CGN_B.psi) <
      Mission_Manager_CGN_B.In1_j.tolerance.yaw);
    Mission_Manager_CGN_B.b_varargout_1 = true;
    Mission_Manager_CGN_B.b_index = 0;
    exitg1 = false;
    while ((!exitg1) && (Mission_Manager_CGN_B.b_index < 6)) {
      if (!Mission_Manager_CGN_B.b_x[Mission_Manager_CGN_B.b_index]) {
        Mission_Manager_CGN_B.b_varargout_1 = false;
        exitg1 = true;
      } else {
        Mission_Manager_CGN_B.b_index++;
      }
    }

    if (Mission_Manager_CGN_B.b_varargout_1) {
      Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.DigitalClock -
        Mission_Manager_CGN_DW.hold_timer_start_time;
    } else {
      Mission_Manager_CGN_DW.hold_timer_start_time =
        Mission_Manager_CGN_B.DigitalClock;
      Mission_Manager_CGN_B.b_absxk = 0.0;
    }

    if (Mission_Manager_CGN_B.b_absxk >= Mission_Manager_CGN_B.In1_j.hold_time)
    {
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[0] = 83;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[1] = 85;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[2] = 67;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[3] = 67;
      Mission_Manager_CGN_DW.hold_timer_start_time =
        Mission_Manager_CGN_B.DigitalClock;
    } else {
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[0] = 82;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[1] = 85;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[2] = 78;
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[3] = 78;
    }

    for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 6;
         Mission_Manager_CGN_B.i_a++) {
      Mission_Manager_CGN_DW.cmd_specific_wp[Mission_Manager_CGN_B.i_a] =
        Mission_Manager_CGN_DW.idle_wp[Mission_Manager_CGN_B.i_a];
    }
    break;

   case 1:
    Mission_Ma_executeDurationTrick(Mission_Manager_CGN_B.In1_j.hold_time,
      Mission_Manager_CGN_B.cmd.trick_id, Mission_Manager_CGN_DW.idle_wp,
      Mission_Manager_CGN_B.X_est.Ri, Mission_Manager_CGN_B.X_est.Eul,
      Mission_Manager_CGN_B.X_est.Cib,
      &Mission_Manager_CGN_DW.hold_timer_start_time,
      Mission_Manager_CGN_B.DigitalClock, Mission_Manager_CGN_B.b_varargout_1,
      Mission_Manager_CGN_DW.cmd_specific_wp,
      Mission_Manager_CGN_DW.UnitDelay_DSTATE_g, &Mission_Manager_CGN_B.b_absxk,
      Mission_Manager_CGN_B.X_u);
    break;

   default:
    Mission_Manager_CGN_eulToQuat_k(&Mission_Manager_CGN_DW.idle_wp[3],
      Mission_Manager_CGN_B.dv1);
    Mission_Manager_CGN_B.X_u[0] = Mission_Manager_CGN_DW.idle_wp[0];
    Mission_Manager_CGN_B.X_u[1] = Mission_Manager_CGN_DW.idle_wp[1];
    Mission_Manager_CGN_B.X_u[2] = Mission_Manager_CGN_DW.idle_wp[2];
    Mission_Manager_CGN_B.X_u[3] = Mission_Manager_CGN_B.dv1[0];
    Mission_Manager_CGN_B.X_u[4] = Mission_Manager_CGN_B.dv1[1];
    Mission_Manager_CGN_B.X_u[5] = Mission_Manager_CGN_B.dv1[2];
    Mission_Manager_CGN_B.X_u[6] = Mission_Manager_CGN_B.dv1[3];
    Mission_Manager_CGN_B.X_u[7] = 0.0;
    Mission_Manager_CGN_B.X_u[10] = 0.0;
    Mission_Manager_CGN_B.X_u[8] = 0.0;
    Mission_Manager_CGN_B.X_u[11] = 0.0;
    Mission_Manager_CGN_B.X_u[9] = 0.0;
    Mission_Manager_CGN_B.X_u[12] = 0.0;
    Mission_Manager_CGN_DW.hold_timer_start_time =
      Mission_Manager_CGN_B.DigitalClock;
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[0] = 82;
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[1] = 85;
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[2] = 78;
    Mission_Manager_CGN_DW.UnitDelay_DSTATE_g[3] = 78;
    break;
  }

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S18>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'

  Mission_Manager_CGN_DW.prior_action_id_not_empty = true;
  tmp_2 = _mm_sub_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.X_u[0]), _mm_set_pd
                     (Mission_Manager_CGN_B.b_t, Mission_Manager_CGN_B.scale));
  _mm_storeu_pd(&Mission_Manager_CGN_B.Ri_xy_e[0], tmp_2);
  Mission_Manager_CGN_DW.UnitDelay1_DSTATE = Mission_Manager_C_rt_atan2d_snf
    (Mission_Manager_CGN_B.Ri_xy_e[1], Mission_Manager_CGN_B.Ri_xy_e[0]);
  Mission_Manager_CGN_B.DigitalClock = Mission_Manager_CGN_norm
    (Mission_Manager_CGN_B.Ri_xy_e);
  if (Mission_Manager_CGN_B.DigitalClock >= 1.0) {
    Mission_Manager_CGN_B.dv3[0] = 0.0;
    Mission_Manager_CGN_B.dv3[1] = 0.0;
    Mission_Manager_CGN_B.dv3[2] = Mission_Manager_CGN_DW.UnitDelay1_DSTATE;
    Mission_Manager_CGN_eulToRotm(Mission_Manager_CGN_B.dv3,
      Mission_Manager_CGN_B.rotm);
    Mission_Manager_CGN_rotmToQuat(Mission_Manager_CGN_B.rotm,
      Mission_Manager_CGN_B.qib_int_u);
  } else {
    Mission_Manager_CGN_quatToEul(&Mission_Manager_CGN_B.X_u[3],
      Mission_Manager_CGN_B.R_error);
    Mission_Manager_CGN_B.qib_int_u[0] = Mission_Manager_CGN_B.X_u[3];
    Mission_Manager_CGN_B.qib_int_u[1] = Mission_Manager_CGN_B.X_u[4];
    Mission_Manager_CGN_B.qib_int_u[2] = Mission_Manager_CGN_B.X_u[5];
    Mission_Manager_CGN_B.qib_int_u[3] = Mission_Manager_CGN_B.X_u[6];
  }

  Mission_Manager_CGN_quatToEul(Mission_Manager_CGN_B.qib_int_u,
    Mission_Manager_CGN_B.eps_g);
  Mission_Manager_CGN_B.b_varargout_1 = false;
  Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 = true;
  Mission_Manager_CGN_B.i_a = 0;
  exitg1 = false;
  while ((!exitg1) && (Mission_Manager_CGN_B.i_a < 16)) {
    if (Mission_Manager_CGN_B.switch_expression[Mission_Manager_CGN_B.i_a] !=
        c[Mission_Manager_CGN_B.i_a]) {
      Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 = false;
      exitg1 = true;
    } else {
      Mission_Manager_CGN_B.i_a++;
    }
  }

  if (Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0) {
    Mission_Manager_CGN_B.b_varargout_1 = true;
  }

  if (Mission_Manager_CGN_B.b_varargout_1) {
    Mission_Manager_CGN_B.qib_int_u[0] = Mission_Manager_CGN_B.X_u[3];
    Mission_Manager_CGN_B.qib_int_u[1] = Mission_Manager_CGN_B.X_u[4];
    Mission_Manager_CGN_B.qib_int_u[2] = Mission_Manager_CGN_B.X_u[5];
    Mission_Manager_CGN_B.qib_int_u[3] = Mission_Manager_CGN_B.X_u[6];
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.x1[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.b_varargout_1 = false;
    Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 = true;
    Mission_Manager_CGN_B.b_index = 0;
    exitg1 = false;
    while ((!exitg1) && (Mission_Manager_CGN_B.b_index < 16)) {
      if (Mission_Manager_CGN_B.x1[Mission_Manager_CGN_B.b_index] !=
          d[Mission_Manager_CGN_B.b_index]) {
        Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 = false;
        exitg1 = true;
      } else {
        Mission_Manager_CGN_B.b_index++;
      }
    }

    if (Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0) {
      Mission_Manager_CGN_B.b_varargout_1 = true;
    }

    if (Mission_Manager_CGN_B.b_varargout_1) {
      Mission_Manager_CGN_quatToEul(&Mission_Manager_CGN_B.X_u[3],
        Mission_Manager_CGN_B.eps);
      Mission_Manager_CGN_B.dv3[0] = 0.0;
      Mission_Manager_CGN_B.dv3[1] = Mission_Manager_CGN_B.eps[1];
      Mission_Manager_CGN_B.dv3[2] = Mission_Manager_CGN_B.eps[2];
      Mission_Manager_CGN_eulToRotm(Mission_Manager_CGN_B.dv3,
        Mission_Manager_CGN_B.rotm);
      Mission_Manager_CGN_rotmToQuat(Mission_Manager_CGN_B.rotm,
        Mission_Manager_CGN_B.qib_int_u);
    }
  }

  Mission_Manager_CGN_B.b_absxk = ((Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.qib_int_u[3] - -Mission_Manager_CGN_B.X_est.qib[0] *
    Mission_Manager_CGN_B.qib_int_u[0]) - -Mission_Manager_CGN_B.X_est.qib[1] *
    Mission_Manager_CGN_B.qib_int_u[1]) - -Mission_Manager_CGN_B.X_est.qib[2] *
    Mission_Manager_CGN_B.qib_int_u[2];

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'

  // MATLAB Function: '<S5>/discreteTimeQuatPropagation'
  tmp_2 = _mm_set1_pd(Mission_Manager_CGN_B.absxk);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S18>/guidanceLaw'
  tmp_3 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2, _mm_loadu_pd
    (&Mission_Manager_CGN_B.qib_int_u[0])), _mm_mul_pd(_mm_set1_pd
    (Mission_Manager_CGN_B.qib_int_u[3]), tmp_6)), _mm_sub_pd(_mm_mul_pd
    (_mm_set_pd(Mission_Manager_CGN_B.qib_int_u[0],
                -Mission_Manager_CGN_B.X_est.qib[1]), _mm_set_pd
     (-Mission_Manager_CGN_B.X_est.qib[2], Mission_Manager_CGN_B.qib_int_u[2])),
    _mm_mul_pd(_mm_set_pd(-Mission_Manager_CGN_B.X_est.qib[0],
    Mission_Manager_CGN_B.qib_int_u[1]), _mm_set_pd
               (Mission_Manager_CGN_B.qib_int_u[2],
                -Mission_Manager_CGN_B.X_est.qib[2]))));

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_3);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S18>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S4>/Unit Delay'

  Mission_Manager_CGN_B.psi = (Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.qib_int_u[2] + Mission_Manager_CGN_B.qib_int_u[3] *
    -Mission_Manager_CGN_B.X_est.qib[2]) + (-Mission_Manager_CGN_B.X_est.qib[0] *
    Mission_Manager_CGN_B.qib_int_u[1] - Mission_Manager_CGN_B.qib_int_u[0] *
    -Mission_Manager_CGN_B.X_est.qib[1]);
  Mission_Manager_CGN_B.qinv[0] = Mission_Manager_CGN_B.dv9[0];
  Mission_Manager_CGN_B.qinv[1] = Mission_Manager_CGN_B.dv9[1];
  Mission_Manager_CGN_B.qinv[2] = Mission_Manager_CGN_B.psi;
  Mission_Manager_CGN_B.qinv[3] = Mission_Manager_CGN_B.b_absxk;
  if (Mission_Manager_CGN_B.b_absxk < 0.0) {
    Mission_Manager_CGN_B.qinv[0] = -Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.qinv[1] = -Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.qinv[2] = -Mission_Manager_CGN_B.psi;
    Mission_Manager_CGN_B.qinv[3] = -Mission_Manager_CGN_B.b_absxk;
  }

  Mission_Manager_CGN_quatToEul(Mission_Manager_CGN_B.qinv,
    Mission_Manager_CGN_B.eps);
  Mission_Manager_CGN_B.R_error[0] = std::abs(Mission_Manager_CGN_B.eps[0]);
  Mission_Manager_CGN_B.R_error[1] = std::abs(Mission_Manager_CGN_B.eps[1]);
  Mission_Manager_CGN_B.R_error[2] = std::abs(Mission_Manager_CGN_B.eps[2]);
  if (!std::isnan(Mission_Manager_CGN_B.R_error[0])) {
    Mission_Manager_CGN_B.i_a = 1;
  } else {
    Mission_Manager_CGN_B.i_a = 0;
    Mission_Manager_CGN_B.iindx = 2;
    exitg1 = false;
    while ((!exitg1) && (Mission_Manager_CGN_B.iindx < 4)) {
      if (!std::isnan(Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.iindx
                      - 1])) {
        Mission_Manager_CGN_B.i_a = Mission_Manager_CGN_B.iindx;
        exitg1 = true;
      } else {
        Mission_Manager_CGN_B.iindx++;
      }
    }
  }

  if (Mission_Manager_CGN_B.i_a == 0) {
    Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.R_error[0];
  } else {
    Mission_Manager_CGN_B.b_absxk =
      Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.i_a - 1];
    for (Mission_Manager_CGN_B.iindx = Mission_Manager_CGN_B.i_a + 1;
         Mission_Manager_CGN_B.iindx < 4; Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
        Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.iindx - 1];
      if (Mission_Manager_CGN_B.b_absxk <
          Mission_Manager_CGN_B.rtb_Filter_h_idx_1) {
        Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
      }
    }
  }

  if (Mission_Manager_CGN_B.b_absxk > 0.17453292519943295) {
    Mission_Manager_CGN_B.eps[0] = 0.0;
    Mission_Manager_CGN_B.eps[1] = 0.0;
    Mission_Manager_CGN_B.eps[2] = 0.0;
    Mission_Manager_CGN_B.i_a = 1;
  } else if (Mission_Manager_CGN_B.DigitalClock >= 1.0) {
    Mission_Manager_CGN_B.eps[0] = Mission_Manager_CGN_B.DigitalClock;
    Mission_Manager_CGN_B.eps[1] = 0.0;
    Mission_Manager_CGN_B.eps[2] = Mission_Manager_CGN_B.X_u[2] -
      Mission_Manager_CGN_B.b_scale;
    Mission_Manager_CGN_B.i_a = 2;
  } else {
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
         Mission_Manager_CGN_B.iindx++) {
      tmp_3 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 * Mission_Manager_CGN_B.iindx]),
        _mm_set1_pd(Mission_Manager_CGN_B.eta)), _mm_mul_pd(_mm_mul_pd
        (_mm_set1_pd(2.0), _mm_set1_pd
         (Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.iindx])),
        _mm_loadu_pd(&Mission_Manager_CGN_B.X_est.qib[0])));
      _mm_storeu_pd(&Mission_Manager_CGN_B.rotm[3 * Mission_Manager_CGN_B.iindx],
                    tmp_3);
      Mission_Manager_CGN_B.i_a = 3 * Mission_Manager_CGN_B.iindx + 2;
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.i_a] = 2.0 *
        Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.iindx] *
        Mission_Manager_CGN_B.X_est.qib[2] +
        Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.i_a] *
        Mission_Manager_CGN_B.eta;
    }

    Mission_Manager_CGN_B.Cbi_c[0] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[1], tmp_4);
    Mission_Manager_CGN_B.Cbi_c[3] =
      Mission_Manager_CGN_B.rtb_Integrator_f_idx_1;
    Mission_Manager_CGN_B.Cbi_c[4] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
    _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[5], tmp_5);
    Mission_Manager_CGN_B.Cbi_c[7] =
      Mission_Manager_CGN_B.rtb_Integrator_f_idx_2;
    Mission_Manager_CGN_B.Cbi_c[8] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
         Mission_Manager_CGN_B.iindx += 2) {
      tmp_3 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx]);
      tmp_1 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx]);
      _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx],
                    _mm_add_pd(tmp_3, tmp_1));
    }

    for (Mission_Manager_CGN_B.iindx = 8; Mission_Manager_CGN_B.iindx < 9;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx] +
        Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
    Mission_Manager_CGN_B.DigitalClock = 0.0;
    Mission_Manager_CGN_B.b_absxk = 0.0;
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
         Mission_Manager_CGN_B.iindx++) {
      tmp_3 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.Cbi[3 *
        Mission_Manager_CGN_B.iindx]), _mm_set1_pd
        (Mission_Manager_CGN_B.X_u[Mission_Manager_CGN_B.iindx])), _mm_set_pd
                         (Mission_Manager_CGN_B.DigitalClock,
                          Mission_Manager_CGN_B.rtb_Filter_h_idx_1));
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_3);
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.DigitalClock = Mission_Manager_CGN_B.dv9[1];
      Mission_Manager_CGN_B.b_absxk += Mission_Manager_CGN_B.Cbi[3 *
        Mission_Manager_CGN_B.iindx + 2] *
        Mission_Manager_CGN_B.X_u[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.R_error[2] = Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.R_error[1] = Mission_Manager_CGN_B.DigitalClock;
    Mission_Manager_CGN_B.R_error[0] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 0;
         Mission_Manager_CGN_B.iindx += 2) {
      tmp_3 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx + 3]);
      tmp_1 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx]);
      tmp = _mm_loadu_pd(&Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx
                         + 6]);
      tmp_0 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.iindx]);
      _mm_storeu_pd(&Mission_Manager_CGN_B.eps[Mission_Manager_CGN_B.iindx],
                    _mm_sub_pd(tmp_0, _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_3,
        _mm_set1_pd(Mission_Manager_CGN_B.b_t)), _mm_mul_pd(tmp_1, _mm_set1_pd
        (Mission_Manager_CGN_B.scale))), _mm_mul_pd(tmp, _mm_set1_pd
        (Mission_Manager_CGN_B.b_scale)))));
    }

    for (Mission_Manager_CGN_B.iindx = 2; Mission_Manager_CGN_B.iindx < 3;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.eps[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.iindx] -
        ((Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx + 3] *
          Mission_Manager_CGN_B.b_t +
          Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx] *
          Mission_Manager_CGN_B.scale) +
         Mission_Manager_CGN_B.Cbi[Mission_Manager_CGN_B.iindx + 6] *
         Mission_Manager_CGN_B.b_scale);
    }

    Mission_Manager_CGN_B.i_a = 3;
  }

  Mission_Manager_CGN_DW.UnitDelay_DSTATE = Mission_Manager_CGN_B.i_a;

  // Gain: '<S18>/Gain5' incorporates:
  //   DataStoreWrite: '<S18>/Data Store Write1'
  //   RelationalOperator: '<S21>/FixPt Relational Operator'
  //   UnitDelay: '<S21>/Delay Input1'
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S21>/Delay Input1':
  //
  //   Store in Global RAM

  Mission_Manager_CGN_B.integrator_reset = static_cast<uint8_T>
    ((Mission_Manager_CGN_DW.UnitDelay_DSTATE !=
      Mission_Manager_CGN_DW.DelayInput1_DSTATE) << 7);

  // MATLAB Function: '<S18>/quatInjector' incorporates:
  //   MATLAB Function: '<S5>/derivedStateEstimates'
  //   UnitDelay: '<S4>/Unit Delay'

  if ((Mission_Manager_CGN_DW.UnitDelay_DSTATE == 2.0) ||
      (Mission_Manager_CGN_DW.UnitDelay_DSTATE == 1.0)) {
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.x1[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.i_a = std::memcmp(&a_0[0], &Mission_Manager_CGN_B.x1[0],
      16);
    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.X_est.Eul[0] = Mission_Manager_CGN_B.t + 3.1;
      Mission_Manager_CGN_eulToQuat(Mission_Manager_CGN_B.X_est.Eul,
        Mission_Manager_CGN_B.qib_int_u);
    }
  }

  // End of MATLAB Function: '<S18>/quatInjector'

  // DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read6'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0;
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0;
  }

  // MATLAB Function: '<S18>/deltaQuatError' incorporates:
  //   MATLAB Function: '<S18>/guidanceLaw'
  //   MATLAB Function: '<S18>/quatPID'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'

  Mission_Manager_CGN_B.phi = ((Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.qib_int_u[3] - -Mission_Manager_CGN_B.X_est.qib[0] *
    Mission_Manager_CGN_B.qib_int_u[0]) - -Mission_Manager_CGN_B.X_est.qib[1] *
    Mission_Manager_CGN_B.qib_int_u[1]) - -Mission_Manager_CGN_B.X_est.qib[2] *
    Mission_Manager_CGN_B.qib_int_u[2];
  tmp_6 = _mm_mul_pd(_mm_set1_pd(Mission_Manager_CGN_B.qib_int_u[3]), tmp_6);
  tmp_3 = _mm_sub_pd(_mm_mul_pd(_mm_set_pd(Mission_Manager_CGN_B.qib_int_u[0],
    -Mission_Manager_CGN_B.X_est.qib[1]), _mm_set_pd
    (-Mission_Manager_CGN_B.X_est.qib[2], Mission_Manager_CGN_B.qib_int_u[2])),
                     _mm_mul_pd(_mm_set_pd(-Mission_Manager_CGN_B.X_est.qib[0],
    Mission_Manager_CGN_B.qib_int_u[1]), _mm_set_pd
    (Mission_Manager_CGN_B.qib_int_u[2], -Mission_Manager_CGN_B.X_est.qib[2])));
  tmp_1 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2, _mm_loadu_pd
    (&Mission_Manager_CGN_B.qib_int_u[0])), tmp_6), tmp_3);

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_1);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S18>/deltaQuatError' incorporates:
  //   MATLAB Function: '<S18>/guidanceLaw'
  //   MATLAB Function: '<S18>/quatPID'
  //   MATLAB Function: '<S5>/discreteTimeQuatPropagation'

  Mission_Manager_CGN_B.DigitalClock = Mission_Manager_CGN_B.dv9[0];
  Mission_Manager_CGN_B.t = Mission_Manager_CGN_B.dv9[1];
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = (Mission_Manager_CGN_B.absxk *
    Mission_Manager_CGN_B.qib_int_u[2] + Mission_Manager_CGN_B.qib_int_u[3] *
    -Mission_Manager_CGN_B.X_est.qib[2]) + (-Mission_Manager_CGN_B.X_est.qib[0] *
    Mission_Manager_CGN_B.qib_int_u[1] - Mission_Manager_CGN_B.qib_int_u[0] *
    -Mission_Manager_CGN_B.X_est.qib[1]);
  Mission_Manager_CGN_B.scale = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
  Mission_Manager_CGN_B.b_t = Mission_Manager_CGN_B.phi;
  if (Mission_Manager_CGN_B.phi < 0.0) {
    Mission_Manager_CGN_B.DigitalClock = -((Mission_Manager_CGN_B.absxk *
      Mission_Manager_CGN_B.qib_int_u[0] + Mission_Manager_CGN_B.qib_int_u[3] *
      -Mission_Manager_CGN_B.X_est.qib[0]) + (-Mission_Manager_CGN_B.X_est.qib[1]
      * Mission_Manager_CGN_B.qib_int_u[2] - Mission_Manager_CGN_B.qib_int_u[1] *
      -Mission_Manager_CGN_B.X_est.qib[2]));
    Mission_Manager_CGN_B.t = -((Mission_Manager_CGN_B.absxk *
      Mission_Manager_CGN_B.qib_int_u[1] + Mission_Manager_CGN_B.qib_int_u[3] *
      -Mission_Manager_CGN_B.X_est.qib[1]) + (Mission_Manager_CGN_B.qib_int_u[0]
      * -Mission_Manager_CGN_B.X_est.qib[2] - -Mission_Manager_CGN_B.X_est.qib[0]
      * Mission_Manager_CGN_B.qib_int_u[2]));
    Mission_Manager_CGN_B.scale = -Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    Mission_Manager_CGN_B.b_t = -Mission_Manager_CGN_B.phi;
  }

  Mission_Manager_CGN_B.b_varargout_1 = false;
  if (std::isnan(Mission_Manager_CGN_B.b_t)) {
    Mission_Manager_CGN_B.b_absxk = (rtNaN);
  } else {
    Mission_Manager_CGN_B.b_absxk = (Mission_Manager_CGN_B.b_t > 0.0);
  }

  if (Mission_Manager_CGN_B.b_absxk == 0.0) {
    Mission_Manager_CGN_B.b_varargout_1 = true;
  }

  if (!Mission_Manager_CGN_B.b_varargout_1) {
    Mission_Manager_CGN_B.DigitalClock *= Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.t *= Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.scale *= Mission_Manager_CGN_B.b_absxk;
    Mission_Manager_CGN_B.b_t *= Mission_Manager_CGN_B.b_absxk;
  }

  // SignalConversion generated from: '<S18>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S18>/deltaQuatError'

  Mission_Manager_CGN_B.qe_matlab[0] = 1.0 - Mission_Manager_CGN_B.b_t;
  Mission_Manager_CGN_B.qe_matlab[1] = 0.0 - Mission_Manager_CGN_B.DigitalClock;
  Mission_Manager_CGN_B.qe_matlab[2] = 0.0 - Mission_Manager_CGN_B.t;
  Mission_Manager_CGN_B.qe_matlab[3] = 0.0 - Mission_Manager_CGN_B.scale;

  // DiscreteTransferFcn: '<S18>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S18>/deltaQuatError'

  Mission_Manager_CGN_B.absxk = ((1.0 - Mission_Manager_CGN_B.b_t) -
    (-Mission_Manager_CGN_DW.DiscreteTransferFcn_states[0])) / 1.1;
  Mission_Manager_CGN_B.b_scale = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.DiscreteTransferFcn[0] = 10.0 *
    Mission_Manager_CGN_B.absxk + -10.0 *
    Mission_Manager_CGN_DW.DiscreteTransferFcn_states[0];
  Mission_Manager_CGN_B.absxk = ((0.0 - Mission_Manager_CGN_B.DigitalClock) -
    (-Mission_Manager_CGN_DW.DiscreteTransferFcn_states[1])) / 1.1;
  Mission_Manager_CGN_B.b_absxk = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.DiscreteTransferFcn[1] = 10.0 *
    Mission_Manager_CGN_B.absxk + -10.0 *
    Mission_Manager_CGN_DW.DiscreteTransferFcn_states[1];
  Mission_Manager_CGN_B.absxk = ((0.0 - Mission_Manager_CGN_B.t) -
    (-Mission_Manager_CGN_DW.DiscreteTransferFcn_states[2])) / 1.1;
  Mission_Manager_CGN_B.psi = Mission_Manager_CGN_B.absxk;
  Mission_Manager_CGN_B.DiscreteTransferFcn[2] = 10.0 *
    Mission_Manager_CGN_B.absxk + -10.0 *
    Mission_Manager_CGN_DW.DiscreteTransferFcn_states[2];
  Mission_Manager_CGN_B.absxk = ((0.0 - Mission_Manager_CGN_B.scale) -
    (-Mission_Manager_CGN_DW.DiscreteTransferFcn_states[3])) / 1.1;
  Mission_Manager_CGN_B.DiscreteTransferFcn[3] = 10.0 *
    Mission_Manager_CGN_B.absxk + -10.0 *
    Mission_Manager_CGN_DW.DiscreteTransferFcn_states[3];

  // MATLAB Function: '<S18>/deltaQuatError'
  tmp_6 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2, _mm_loadu_pd
    (&Mission_Manager_CGN_B.qib_int_u[0])), tmp_6), tmp_3);

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_6);

  // Outputs for Enabled SubSystem: '<S4>/cascaded_pid_controller' incorporates:
  //   EnablePort: '<S18>/Subsystem Enable'

  // MATLAB Function: '<S18>/quatPID' incorporates:
  //   DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
  //   Gain: '<S18>/Gain1'
  //   Gain: '<S18>/Gain2'
  //   SignalConversion generated from: '<S18>/Discrete Transfer Fcn'

  Mission_Manager_CGN_B.qinv[0] = Mission_Manager_CGN_B.dv9[0];
  Mission_Manager_CGN_B.qinv[1] = Mission_Manager_CGN_B.dv9[1];
  Mission_Manager_CGN_B.qinv[2] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
  Mission_Manager_CGN_B.qinv[3] = Mission_Manager_CGN_B.phi;
  if (Mission_Manager_CGN_B.phi < 0.0) {
    Mission_Manager_CGN_B.qinv[0] = -Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.qinv[1] = -Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.qinv[2] = -Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    Mission_Manager_CGN_B.qinv[3] = -Mission_Manager_CGN_B.phi;
  }

  Mission_Manager_CGN_B.Qe1[0] = -Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[4] = -Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[8] = -Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[1] = Mission_Manager_CGN_B.qinv[3];
  Mission_Manager_CGN_B.Qe1[5] = -Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[9] = Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[2] = Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[6] = Mission_Manager_CGN_B.qinv[3];
  Mission_Manager_CGN_B.Qe1[10] = -Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[3] = -Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[7] = Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[11] = Mission_Manager_CGN_B.qinv[3];
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 4;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.phi = 0.0;
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
    Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = 0.0;
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 = 0.0;
    for (Mission_Manager_CGN_B.loop_ub = 0; Mission_Manager_CGN_B.loop_ub < 3;
         Mission_Manager_CGN_B.loop_ub++) {
      Mission_Manager_CGN_B.i_a = Mission_Manager_CGN_B.loop_ub << 2;
      tmp_6 = _mm_set1_pd(Mission_Manager_CGN_B.Qe1[Mission_Manager_CGN_B.i_a +
                          Mission_Manager_CGN_B.iindx]);
      tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_B.Qe1[Mission_Manager_CGN_B.i_a]), tmp_6),
                         _mm_set_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1,
        Mission_Manager_CGN_B.phi));
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
      Mission_Manager_CGN_B.phi = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[1];
      tmp_6 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_B.Qe1[Mission_Manager_CGN_B.i_a + 2]), tmp_6),
                         _mm_set_pd
                         (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1,
                          Mission_Manager_CGN_B.rtb_Filter_h_idx_0));
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_6);
      Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 =
        Mission_Manager_CGN_B.dv9[1];
    }

    Mission_Manager_CGN_B.i_a = Mission_Manager_CGN_B.iindx << 2;
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.i_a + 3] =
      Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1;
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.i_a + 2] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.i_a + 1] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.phi;
    Mission_Manager_CGN_B.dv1[Mission_Manager_CGN_B.iindx] =
      (Mission_Manager_CGN_ConstP.Gain1_Gain[Mission_Manager_CGN_B.iindx] *
       Mission_Manager_CGN_B.qe_matlab[Mission_Manager_CGN_B.iindx] + 0.0 *
       Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[Mission_Manager_CGN_B.iindx])
      + Mission_Manager_CGN_B.DiscreteTransferFcn[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.phi = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = 0.0;
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 4;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.loop_ub = Mission_Manager_CGN_B.iindx << 2;
    tmp_6 = _mm_set1_pd(Mission_Manager_CGN_B.dv1[Mission_Manager_CGN_B.iindx]);
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub]), tmp_6),
                       _mm_set_pd(Mission_Manager_CGN_B.rtb_Filter_h_idx_1,
      Mission_Manager_CGN_B.phi));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.phi = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[1];
    tmp_6 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.c_a[Mission_Manager_CGN_B.loop_ub + 2]), tmp_6),
                       _mm_set_pd(Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1,
      Mission_Manager_CGN_B.rtb_Filter_h_idx_0));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_6);
    Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 = Mission_Manager_CGN_B.dv9[1];
  }

  Mission_Manager_CGN_B.qib_int_u[3] =
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1;
  Mission_Manager_CGN_B.qib_int_u[2] = Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
  Mission_Manager_CGN_B.qib_int_u[1] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
  Mission_Manager_CGN_B.qib_int_u[0] = Mission_Manager_CGN_B.phi;
  Mission_Manager_CGN_B.Qe1[0] = Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[1] = Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[2] = Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[3] = -Mission_Manager_CGN_B.qinv[3];
  Mission_Manager_CGN_B.Qe1[4] = -Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[5] = Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[6] = Mission_Manager_CGN_B.qinv[2];
  Mission_Manager_CGN_B.Qe1[7] = -Mission_Manager_CGN_B.qinv[3];
  Mission_Manager_CGN_B.Qe1[8] = -Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[9] = -Mission_Manager_CGN_B.qinv[1];
  Mission_Manager_CGN_B.Qe1[10] = Mission_Manager_CGN_B.qinv[0];
  Mission_Manager_CGN_B.Qe1[11] = -Mission_Manager_CGN_B.qinv[3];
  tmp_6 = _mm_set1_pd(2.0);
  tmp_2 = _mm_mul_pd(tmp_6, _mm_loadu_pd(&Mission_Manager_CGN_B.qib_int_u[0]));
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv1[0], tmp_2);
  tmp_2 = _mm_mul_pd(tmp_6, _mm_loadu_pd(&Mission_Manager_CGN_B.qib_int_u[2]));
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv1[2], tmp_2);
  Mission_Manager_CGN_B.phi = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = 0.0;
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 4;
       Mission_Manager_CGN_B.iindx++) {
    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Mission_Manager_CGN_B.Qe1[3 *
      Mission_Manager_CGN_B.iindx]), _mm_set1_pd
      (Mission_Manager_CGN_B.dv1[Mission_Manager_CGN_B.iindx])), _mm_set_pd
                       (Mission_Manager_CGN_B.rtb_Filter_h_idx_1,
                        Mission_Manager_CGN_B.phi));
    _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], tmp_2);
    Mission_Manager_CGN_B.phi = Mission_Manager_CGN_B.dv9[0];
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[1];
    Mission_Manager_CGN_B.rtb_Filter_h_idx_0 += Mission_Manager_CGN_B.Qe1[3 *
      Mission_Manager_CGN_B.iindx + 2] *
      Mission_Manager_CGN_B.dv1[Mission_Manager_CGN_B.iindx];
  }

  Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
  Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
  Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.phi;

  // DiscreteIntegrator: '<S126>/Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read1'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Integrator_PrevResetState <= 0)) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[0] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE[1] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE[2] = 0.0;
  }

  // DiscreteIntegrator: '<S121>/Filter' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read1'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Filter_PrevResetState <= 0)) {
    Mission_Manager_CGN_DW.Filter_DSTATE[0] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE[1] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE[2] = 0.0;
  }

  for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 3;
       Mission_Manager_CGN_B.i_a++) {
    // Gain: '<S119>/Derivative Gain'
    Mission_Manager_CGN_B.phi =
      Mission_Manager_CGN_B.eps[Mission_Manager_CGN_B.i_a];

    // Gain: '<S129>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S121>/Filter'
    //   Gain: '<S119>/Derivative Gain'
    //   Sum: '<S121>/SumD'

    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = (0.0 * Mission_Manager_CGN_B.phi
      - Mission_Manager_CGN_DW.Filter_DSTATE[Mission_Manager_CGN_B.i_a]) * 100.0;
    Mission_Manager_CGN_B.R_error[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1;

    // Sum: '<S135>/Sum' incorporates:
    //   DiscreteIntegrator: '<S126>/Integrator'
    //   Gain: '<S123>/Integral Gain'
    //   Gain: '<S129>/Filter Coefficient'
    //   Gain: '<S131>/Proportional Gain'

    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 +=
      Mission_Manager_CGN_ConstP.ProportionalGain_Gain[Mission_Manager_CGN_B.i_a]
      * Mission_Manager_CGN_B.phi +
      Mission_Manager_CGN_DW.Integrator_DSTATE[Mission_Manager_CGN_B.i_a];
    Mission_Manager_CGN_B.eul_error[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1;

    // Saturate: '<S133>/Saturation'
    if (Mission_Manager_CGN_B.rtb_Filter_h_idx_1 > 1.0) {
      // MATLAB Function: '<S18>/dRbSetpointInjector'
      Mission_Manager_CGN_B.dRb_u[Mission_Manager_CGN_B.i_a] = 1.0;
    } else if (Mission_Manager_CGN_B.rtb_Filter_h_idx_1 < -1.0) {
      // MATLAB Function: '<S18>/dRbSetpointInjector'
      Mission_Manager_CGN_B.dRb_u[Mission_Manager_CGN_B.i_a] = -1.0;
    } else {
      // MATLAB Function: '<S18>/dRbSetpointInjector'
      Mission_Manager_CGN_B.dRb_u[Mission_Manager_CGN_B.i_a] =
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
    }

    // End of Saturate: '<S133>/Saturation'

    // Math: '<S18>/Transpose' incorporates:
    //   DataStoreRead: '<S18>/Data Store Read'
    //   DataStoreWrite: '<S18>/Data Store Write'
    //   MATLAB Function: '<S18>/quatToRotm'

    tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[3 * Mission_Manager_CGN_B.i_a]),
      _mm_set1_pd(Mission_Manager_CGN_B.eta)), _mm_mul_pd(_mm_mul_pd(tmp_6,
      _mm_set1_pd(Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.i_a])),
      _mm_loadu_pd(&Mission_Manager_CGN_B.X_est.qib[0])));

    // MATLAB Function: '<S18>/quatToRotm'
    _mm_storeu_pd(&Mission_Manager_CGN_B.rotm[3 * Mission_Manager_CGN_B.i_a],
                  tmp_2);

    // Math: '<S18>/Transpose' incorporates:
    //   DataStoreRead: '<S18>/Data Store Read'
    //   DataStoreWrite: '<S18>/Data Store Write'
    //   MATLAB Function: '<S18>/quatToRotm'

    Mission_Manager_CGN_B.b_index = 3 * Mission_Manager_CGN_B.i_a + 2;

    // MATLAB Function: '<S18>/quatToRotm' incorporates:
    //   DataStoreRead: '<S18>/Data Store Read'
    //   DataStoreWrite: '<S18>/Data Store Write'
    //   Math: '<S18>/Transpose'

    Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.b_index] = 2.0 *
      Mission_Manager_CGN_B.X_est.qib[Mission_Manager_CGN_B.i_a] *
      Mission_Manager_CGN_B.X_est.qib[2] +
      Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.b_index] *
      Mission_Manager_CGN_B.eta;
  }

  // Math: '<S18>/Transpose'
  Mission_Manager_CGN_B.Cbi_c[0] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[1], tmp_4);
  Mission_Manager_CGN_B.Cbi_c[3] = Mission_Manager_CGN_B.rtb_Integrator_f_idx_1;
  Mission_Manager_CGN_B.Cbi_c[4] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  _mm_storeu_pd(&Mission_Manager_CGN_B.Cbi_c[5], tmp_5);
  Mission_Manager_CGN_B.Cbi_c[7] = Mission_Manager_CGN_B.rtb_Integrator_f_idx_2;
  Mission_Manager_CGN_B.Cbi_c[8] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // MATLAB Function: '<S18>/quatToRotm'
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
       Mission_Manager_CGN_B.iindx += 2) {
    tmp_5 = _mm_loadu_pd(&Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx]);
    tmp_4 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx],
       _mm_add_pd(tmp_5, tmp_4));
  }

  for (Mission_Manager_CGN_B.iindx = 8; Mission_Manager_CGN_B.iindx < 9;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx] =
      Mission_Manager_CGN_B.rotm[Mission_Manager_CGN_B.iindx] +
      Mission_Manager_CGN_B.Cbi_c[Mission_Manager_CGN_B.iindx];
  }

  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 0;
       Mission_Manager_CGN_B.iindx += 2) {
    // Sum: '<S18>/Subtract4' incorporates:
    //   MATLAB Function: '<S5>/derivedStateEstimates'
    //   Product: '<S18>/Matrix Multiply3'

    tmp_5 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx + 3]);
    tmp_4 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx]);
    tmp_6 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx + 6]);
    tmp_2 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.dRb_u[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.dRb_e[Mission_Manager_CGN_B.iindx],
                  _mm_sub_pd(tmp_2, _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_5,
      _mm_set1_pd(Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0)),
      _mm_mul_pd(tmp_4, _mm_set1_pd(Mission_Manager_CGN_B.rtb_X_est_idx_0))),
      _mm_mul_pd(tmp_6, _mm_set1_pd
                 (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0)))));

    // Sum: '<S18>/Subtract' incorporates:
    //   DataStoreWrite: '<S18>/Data Store Write4'
    //   Product: '<S18>/Matrix Multiply3'
    //   Sum: '<S18>/Subtract4'

    tmp_5 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.eps_g[Mission_Manager_CGN_B.iindx]);
    tmp_4 = _mm_loadu_pd
      (&Mission_Manager_CGN_B.X_est.wb[Mission_Manager_CGN_B.iindx]);

    // MATLAB Function: '<S18>/rateInjector' incorporates:
    //   Product: '<S18>/Matrix Multiply3'
    //   Sum: '<S18>/Subtract'
    //   Sum: '<S18>/Subtract4'

    _mm_storeu_pd(&Mission_Manager_CGN_B.eps_g[Mission_Manager_CGN_B.iindx],
                  _mm_sub_pd(tmp_5, tmp_4));
  }

  for (Mission_Manager_CGN_B.iindx = 2; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    // Sum: '<S18>/Subtract4' incorporates:
    //   MATLAB Function: '<S5>/derivedStateEstimates'
    //   Product: '<S18>/Matrix Multiply3'

    Mission_Manager_CGN_B.dRb_e[Mission_Manager_CGN_B.iindx] =
      Mission_Manager_CGN_B.dRb_u[Mission_Manager_CGN_B.iindx] -
      ((Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx + 3] *
        Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0 +
        Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx] *
        Mission_Manager_CGN_B.rtb_X_est_idx_0) +
       Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp[Mission_Manager_CGN_B.iindx + 6] *
       Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0);

    // MATLAB Function: '<S18>/rateInjector' incorporates:
    //   DataStoreWrite: '<S18>/Data Store Write4'
    //   Sum: '<S18>/Subtract'

    Mission_Manager_CGN_B.eps_g[Mission_Manager_CGN_B.iindx] -=
      Mission_Manager_CGN_B.X_est.wb[Mission_Manager_CGN_B.iindx];
  }

  // MATLAB Function: '<S18>/rateInjector' incorporates:
  //   DiscreteIntegrator: '<S5>/Velocity Integrator'
  //   MATLAB Function: '<S18>/trickFTListInjector'
  //   MATLAB Function: '<S5>/derivedStateEstimates'

  Mission_Manager_CGN_B.b_varargout_1 = Mission_Manager_CGN_isequal
    (Mission_Manager_CGN_B.switch_expression);
  if (Mission_Manager_CGN_B.b_varargout_1) {
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.x1[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.i_a = std::memcmp(&a_1[0], &Mission_Manager_CGN_B.x1[0],
      16);
    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.b_index = 0;
    } else {
      Mission_Manager_CGN_B.i_a = std::memcmp(&b_a_0[0],
        &Mission_Manager_CGN_B.x1[0], 16);
      if (Mission_Manager_CGN_B.i_a == 0) {
        Mission_Manager_CGN_B.b_index = 1;
      } else {
        Mission_Manager_CGN_B.i_a = std::memcmp(&c_a_1[0],
          &Mission_Manager_CGN_B.x1[0], 16);
        if (Mission_Manager_CGN_B.i_a == 0) {
          Mission_Manager_CGN_B.b_index = 2;
        } else {
          Mission_Manager_CGN_B.i_a = std::memcmp(&d_a_0[0],
            &Mission_Manager_CGN_B.x1[0], 16);
          if (Mission_Manager_CGN_B.i_a == 0) {
            Mission_Manager_CGN_B.b_index = 3;
          } else {
            Mission_Manager_CGN_B.i_a = std::memcmp(&e_a[0],
              &Mission_Manager_CGN_B.x1[0], 16);
            if (Mission_Manager_CGN_B.i_a == 0) {
              Mission_Manager_CGN_B.b_index = 4;
            } else {
              Mission_Manager_CGN_B.i_a = std::memcmp(&f_a[0],
                &Mission_Manager_CGN_B.x1[0], 16);
              if (Mission_Manager_CGN_B.i_a == 0) {
                Mission_Manager_CGN_B.b_index = 5;
              } else {
                Mission_Manager_CGN_B.i_a = std::memcmp(&g_a[0],
                  &Mission_Manager_CGN_B.x1[0], 16);
                if (Mission_Manager_CGN_B.i_a == 0) {
                  Mission_Manager_CGN_B.b_index = 6;
                } else {
                  Mission_Manager_CGN_B.i_a = std::memcmp(&h_a[0],
                    &Mission_Manager_CGN_B.x1[0], 16);
                  if (Mission_Manager_CGN_B.i_a == 0) {
                    Mission_Manager_CGN_B.b_index = 7;
                  } else {
                    Mission_Manager_CGN_B.i_a = std::memcmp(&i_a[0],
                      &Mission_Manager_CGN_B.x1[0], 16);
                    if (Mission_Manager_CGN_B.i_a == 0) {
                      Mission_Manager_CGN_B.b_index = 8;
                    } else {
                      Mission_Manager_CGN_B.i_a = std::memcmp(&j_a[0],
                        &Mission_Manager_CGN_B.x1[0], 16);
                      if (Mission_Manager_CGN_B.i_a == 0) {
                        Mission_Manager_CGN_B.b_index = 9;
                      } else if (Mission_Manager_CGN_strcmp
                                 (Mission_Manager_CGN_B.x1)) {
                        Mission_Manager_CGN_B.b_index = 10;
                      } else if (Mission_Manager_CGN_strcmp_j
                                 (Mission_Manager_CGN_B.x1)) {
                        Mission_Manager_CGN_B.b_index = 11;
                      } else if (Mission_Manager_CGN_strcmp_jy
                                 (Mission_Manager_CGN_B.x1)) {
                        Mission_Manager_CGN_B.b_index = 12;
                      } else {
                        Mission_Manager_CGN_B.b_index = -1;
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

    switch (Mission_Manager_CGN_B.b_index) {
     case 0:
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        0.5), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[0],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 1:
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        -0.5), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[0],
                          Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 2:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        -1.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[2],
                          Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 3:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        1.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[2],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 4:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        1.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[1],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 5:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(0.0,
        -1.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[1],
                          Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 6:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[1],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 7:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(-1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[1],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 8:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[2],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 9:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(-1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[2],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 10:
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[0],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 11:
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd(-1.0,
        0.0), _mm_set_pd(Mission_Manager_CGN_B.X_est.wb[0],
                         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;

     case 12:
      tmp_5 = _mm_set1_pd(0.0);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[0],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));
      Mission_Manager_CGN_B.dRb_e[0] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[0] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[1],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));
      Mission_Manager_CGN_B.dRb_e[1] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.dv9[1];
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(tmp_5, _mm_set_pd
        (Mission_Manager_CGN_B.X_est.wb[2],
         Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2])));
      Mission_Manager_CGN_B.dRb_e[2] = Mission_Manager_CGN_B.dv9[0];
      Mission_Manager_CGN_B.eps_g[2] = Mission_Manager_CGN_B.dv9[1];
      break;
    }
  }

  // DiscreteIntegrator: '<S71>/Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read7'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Integrator_PrevResetState_i <= 0)) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[0] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[1] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[2] = 0.0;
  }

  // DiscreteIntegrator: '<S66>/Filter' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read7'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Filter_PrevResetState_g <= 0)) {
    Mission_Manager_CGN_DW.Filter_DSTATE_g[0] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE_g[1] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE_g[2] = 0.0;
  }

  // Gain: '<S74>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S66>/Filter'
  //   Gain: '<S64>/Derivative Gain'
  //   Sum: '<S66>/SumD'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d = (0.0 * Mission_Manager_CGN_B.eps_g[0]
    - Mission_Manager_CGN_DW.Filter_DSTATE_g[0]) * 100.0;
  Mission_Manager_CGN_B.dRb_u[0] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // Sum: '<S80>/Sum' incorporates:
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S64>/Derivative Gain'

  Mission_Manager_CGN_B.eta = (Mission_Manager_CGN_B.eps_g[0] +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[0]) +
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_0 = Mission_Manager_CGN_B.eta;

  // DeadZone: '<S63>/DeadZone'
  if (Mission_Manager_CGN_B.eta > 10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_0 = Mission_Manager_CGN_B.eta -
      10.0;
  } else if (Mission_Manager_CGN_B.eta >= -10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_0 = 0.0;
  } else {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_0 = Mission_Manager_CGN_B.eta -
      -10.0;
  }

  // Gain: '<S74>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S66>/Filter'
  //   Gain: '<S64>/Derivative Gain'
  //   Sum: '<S66>/SumD'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d = (0.0 * Mission_Manager_CGN_B.eps_g[1]
    - Mission_Manager_CGN_DW.Filter_DSTATE_g[1]) * 100.0;
  Mission_Manager_CGN_B.dRb_u[1] = Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // Gain: '<S76>/Proportional Gain' incorporates:
  //   Gain: '<S64>/Derivative Gain'
  //   Gain: '<S68>/Integral Gain'

  Mission_Manager_CGN_B.phi = 5.0 * Mission_Manager_CGN_B.eps_g[1];
  Mission_Manager_CGN_B.eps_g[1] = Mission_Manager_CGN_B.phi;

  // Sum: '<S80>/Sum' incorporates:
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S76>/Proportional Gain'

  Mission_Manager_CGN_B.eta = (Mission_Manager_CGN_B.phi +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[1]) +
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.eta;

  // DeadZone: '<S63>/DeadZone'
  if (Mission_Manager_CGN_B.eta > 10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 = Mission_Manager_CGN_B.eta -
      10.0;
  } else if (Mission_Manager_CGN_B.eta >= -10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 = 0.0;
  } else {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 = Mission_Manager_CGN_B.eta -
      -10.0;
  }

  // Gain: '<S74>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S66>/Filter'
  //   Gain: '<S64>/Derivative Gain'
  //   Sum: '<S66>/SumD'

  Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d = (0.0 * Mission_Manager_CGN_B.eps_g[2]
    - Mission_Manager_CGN_DW.Filter_DSTATE_g[2]) * 100.0;

  // Gain: '<S76>/Proportional Gain' incorporates:
  //   Gain: '<S64>/Derivative Gain'
  //   Gain: '<S68>/Integral Gain'

  Mission_Manager_CGN_B.phi = 5.0 * Mission_Manager_CGN_B.eps_g[2];

  // Sum: '<S80>/Sum' incorporates:
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S76>/Proportional Gain'

  Mission_Manager_CGN_B.eta = (Mission_Manager_CGN_B.phi +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[2]) +
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // DeadZone: '<S63>/DeadZone'
  if (Mission_Manager_CGN_B.eta > 10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 = Mission_Manager_CGN_B.eta -
      10.0;
  } else if (Mission_Manager_CGN_B.eta >= -10.0) {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 = 0.0;
  } else {
    Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 = Mission_Manager_CGN_B.eta -
      -10.0;
  }

  // DiscreteIntegrator: '<S181>/Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read9'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Integrator_PrevResetState_a <= 0)) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[0] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[1] = 0.0;
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[2] = 0.0;
  }

  // DiscreteIntegrator: '<S176>/Filter' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read9'

  if ((Mission_Manager_CGN_B.integrator_reset > 0) &&
      (Mission_Manager_CGN_DW.Filter_PrevResetState_l <= 0)) {
    Mission_Manager_CGN_DW.Filter_DSTATE_m[0] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE_m[1] = 0.0;
    Mission_Manager_CGN_DW.Filter_DSTATE_m[2] = 0.0;
  }

  // Gain: '<S184>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S176>/Filter'
  //   Gain: '<S174>/Derivative Gain'
  //   Sum: '<S176>/SumD'

  Mission_Manager_CGN_B.rtb_X_est_idx_0 = (0.0 * Mission_Manager_CGN_B.dRb_e[0]
    - Mission_Manager_CGN_DW.Filter_DSTATE_m[0]) * 100.0;
  Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0 =
    Mission_Manager_CGN_B.rtb_X_est_idx_0;

  // Sum: '<S190>/Sum' incorporates:
  //   DiscreteIntegrator: '<S181>/Integrator'
  //   Gain: '<S174>/Derivative Gain'
  //   Gain: '<S186>/Proportional Gain'

  Mission_Manager_CGN_B.rtb_IntegralGain_b_l = (60.0 *
    Mission_Manager_CGN_B.dRb_e[0] + Mission_Manager_CGN_DW.Integrator_DSTATE_b
    [0]) + Mission_Manager_CGN_B.rtb_X_est_idx_0;
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 =
    Mission_Manager_CGN_B.rtb_IntegralGain_b_l;

  // Saturate: '<S78>/Saturation'
  if (Mission_Manager_CGN_B.rtb_Filter_h_idx_0 > 10.0) {
    Mission_Manager_CGN_B.dv3[0] = 10.0;
  } else if (Mission_Manager_CGN_B.rtb_Filter_h_idx_0 < -10.0) {
    Mission_Manager_CGN_B.dv3[0] = -10.0;
  } else {
    Mission_Manager_CGN_B.dv3[0] = Mission_Manager_CGN_B.rtb_Filter_h_idx_0;
  }

  // Saturate: '<S188>/Saturation'
  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l > 100.0) {
    Mission_Manager_CGN_B.dv4[0] = 100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l < -100.0) {
    Mission_Manager_CGN_B.dv4[0] = -100.0;
  } else {
    Mission_Manager_CGN_B.dv4[0] = Mission_Manager_CGN_B.rtb_IntegralGain_b_l;
  }

  // Gain: '<S184>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S176>/Filter'
  //   Gain: '<S174>/Derivative Gain'
  //   Sum: '<S176>/SumD'

  Mission_Manager_CGN_B.rtb_X_est_idx_0 = (0.0 * Mission_Manager_CGN_B.dRb_e[1]
    - Mission_Manager_CGN_DW.Filter_DSTATE_m[1]) * 100.0;
  Mission_Manager_CGN_B.rtb_Filter_h_idx_0 =
    Mission_Manager_CGN_B.rtb_X_est_idx_0;

  // Sum: '<S190>/Sum' incorporates:
  //   DiscreteIntegrator: '<S181>/Integrator'
  //   Gain: '<S174>/Derivative Gain'
  //   Gain: '<S186>/Proportional Gain'

  Mission_Manager_CGN_B.rtb_IntegralGain_b_l = (60.0 *
    Mission_Manager_CGN_B.dRb_e[1] + Mission_Manager_CGN_DW.Integrator_DSTATE_b
    [1]) + Mission_Manager_CGN_B.rtb_X_est_idx_0;
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 =
    Mission_Manager_CGN_B.rtb_IntegralGain_b_l;

  // Saturate: '<S78>/Saturation'
  if (Mission_Manager_CGN_B.rtb_Filter_h_idx_1 > 10.0) {
    Mission_Manager_CGN_B.dv3[1] = 10.0;
  } else if (Mission_Manager_CGN_B.rtb_Filter_h_idx_1 < -10.0) {
    Mission_Manager_CGN_B.dv3[1] = -10.0;
  } else {
    Mission_Manager_CGN_B.dv3[1] = Mission_Manager_CGN_B.rtb_Filter_h_idx_1;
  }

  // Saturate: '<S188>/Saturation'
  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l > 100.0) {
    Mission_Manager_CGN_B.dv4[1] = 100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l < -100.0) {
    Mission_Manager_CGN_B.dv4[1] = -100.0;
  } else {
    Mission_Manager_CGN_B.dv4[1] = Mission_Manager_CGN_B.rtb_IntegralGain_b_l;
  }

  // Gain: '<S184>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S176>/Filter'
  //   Gain: '<S174>/Derivative Gain'
  //   Sum: '<S176>/SumD'

  Mission_Manager_CGN_B.rtb_X_est_idx_0 = (0.0 * Mission_Manager_CGN_B.dRb_e[2]
    - Mission_Manager_CGN_DW.Filter_DSTATE_m[2]) * 100.0;

  // Sum: '<S190>/Sum' incorporates:
  //   DiscreteIntegrator: '<S181>/Integrator'
  //   Gain: '<S174>/Derivative Gain'
  //   Gain: '<S186>/Proportional Gain'

  Mission_Manager_CGN_B.rtb_IntegralGain_b_l = (100.0 *
    Mission_Manager_CGN_B.dRb_e[2] + Mission_Manager_CGN_DW.Integrator_DSTATE_b
    [2]) + Mission_Manager_CGN_B.rtb_X_est_idx_0;

  // Saturate: '<S78>/Saturation' incorporates:
  //   Sum: '<S80>/Sum'

  if (Mission_Manager_CGN_B.eta > 10.0) {
    Mission_Manager_CGN_B.dv3[2] = 10.0;
  } else if (Mission_Manager_CGN_B.eta < -10.0) {
    Mission_Manager_CGN_B.dv3[2] = -10.0;
  } else {
    Mission_Manager_CGN_B.dv3[2] = Mission_Manager_CGN_B.eta;
  }

  // Saturate: '<S188>/Saturation'
  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l > 100.0) {
    Mission_Manager_CGN_B.dv4[2] = 100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l < -100.0) {
    Mission_Manager_CGN_B.dv4[2] = -100.0;
  } else {
    Mission_Manager_CGN_B.dv4[2] = Mission_Manager_CGN_B.rtb_IntegralGain_b_l;
  }

  // Product: '<S18>/Matrix Multiply' incorporates:
  //   Constant: '<S18>/Constant'

  std::memset(&Mission_Manager_CGN_B.pwms[0], 0, sizeof(real_T) << 3U);
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.lower_force_index =
      Mission_Manager_CGN_B.dv3[Mission_Manager_CGN_B.iindx];
    for (Mission_Manager_CGN_B.loop_ub = 0; Mission_Manager_CGN_B.loop_ub <= 6;
         Mission_Manager_CGN_B.loop_ub += 2) {
      tmp_5 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.loop_ub]);
      _mm_storeu_pd(&Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.loop_ub],
                    _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_ConstP.Constant_Value_e
         [(Mission_Manager_CGN_B.iindx << 3) + Mission_Manager_CGN_B.loop_ub]),
        _mm_set1_pd(Mission_Manager_CGN_B.lower_force_index)), tmp_5));
    }
  }

  // End of Product: '<S18>/Matrix Multiply'

  // Product: '<S18>/Matrix Multiply1' incorporates:
  //   Constant: '<S18>/Constant1'

  std::memset(&Mission_Manager_CGN_B.dv[0], 0, sizeof(real_T) << 3U);
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 3;
       Mission_Manager_CGN_B.iindx++) {
    Mission_Manager_CGN_B.lower_force_index =
      Mission_Manager_CGN_B.dv4[Mission_Manager_CGN_B.iindx];
    for (Mission_Manager_CGN_B.loop_ub = 0; Mission_Manager_CGN_B.loop_ub <= 6;
         Mission_Manager_CGN_B.loop_ub += 2) {
      tmp_5 = _mm_loadu_pd
        (&Mission_Manager_CGN_B.dv[Mission_Manager_CGN_B.loop_ub]);
      _mm_storeu_pd(&Mission_Manager_CGN_B.dv[Mission_Manager_CGN_B.loop_ub],
                    _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Mission_Manager_CGN_ConstP.Constant1_Value
         [(Mission_Manager_CGN_B.iindx << 3) + Mission_Manager_CGN_B.loop_ub]),
        _mm_set1_pd(Mission_Manager_CGN_B.lower_force_index)), tmp_5));
    }
  }

  // End of Product: '<S18>/Matrix Multiply1'

  // MATLAB Function: '<S18>/thrusterAllocator'
  for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 6;
       Mission_Manager_CGN_B.iindx += 2) {
    tmp_5 = _mm_loadu_pd(&Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.iindx]);
    tmp_4 = _mm_loadu_pd(&Mission_Manager_CGN_B.dv[Mission_Manager_CGN_B.iindx]);
    _mm_storeu_pd(&Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.iindx],
                  _mm_add_pd(tmp_5, tmp_4));
  }

  // End of MATLAB Function: '<S18>/thrusterAllocator'

  // MATLAB Function: '<S18>/trickFTListInjector'
  if (Mission_Manager_CGN_B.b_varargout_1) {
    for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx < 16;
         Mission_Manager_CGN_B.iindx++) {
      Mission_Manager_CGN_B.switch_expression[Mission_Manager_CGN_B.iindx] =
        Mission_Manager_CGN_B.cmd.trick_id[Mission_Manager_CGN_B.iindx];
    }

    Mission_Manager_CGN_B.i_a = std::memcmp(&a_2[0],
      &Mission_Manager_CGN_B.switch_expression[0], 16);
    if (Mission_Manager_CGN_B.i_a == 0) {
      Mission_Manager_CGN_B.b_index = 0;
    } else {
      Mission_Manager_CGN_B.i_a = std::memcmp(&b_a_1[0],
        &Mission_Manager_CGN_B.switch_expression[0], 16);
      if (Mission_Manager_CGN_B.i_a == 0) {
        Mission_Manager_CGN_B.b_index = 1;
      } else {
        Mission_Manager_CGN_B.i_a = std::memcmp(&c_a_2[0],
          &Mission_Manager_CGN_B.switch_expression[0], 16);
        if (Mission_Manager_CGN_B.i_a == 0) {
          Mission_Manager_CGN_B.b_index = 2;
        } else {
          Mission_Manager_CGN_B.i_a = std::memcmp(&d_a_1[0],
            &Mission_Manager_CGN_B.switch_expression[0], 16);
          if (Mission_Manager_CGN_B.i_a == 0) {
            Mission_Manager_CGN_B.b_index = 3;
          } else {
            Mission_Manager_CGN_B.i_a = std::memcmp(&e_a_0[0],
              &Mission_Manager_CGN_B.switch_expression[0], 16);
            if (Mission_Manager_CGN_B.i_a == 0) {
              Mission_Manager_CGN_B.b_index = 4;
            } else {
              Mission_Manager_CGN_B.i_a = std::memcmp(&f_a_0[0],
                &Mission_Manager_CGN_B.switch_expression[0], 16);
              if (Mission_Manager_CGN_B.i_a == 0) {
                Mission_Manager_CGN_B.b_index = 5;
              } else {
                Mission_Manager_CGN_B.i_a = std::memcmp(&g_a_0[0],
                  &Mission_Manager_CGN_B.switch_expression[0], 16);
                if (Mission_Manager_CGN_B.i_a == 0) {
                  Mission_Manager_CGN_B.b_index = 6;
                } else {
                  Mission_Manager_CGN_B.i_a = std::memcmp(&h_a_0[0],
                    &Mission_Manager_CGN_B.switch_expression[0], 16);
                  if (Mission_Manager_CGN_B.i_a == 0) {
                    Mission_Manager_CGN_B.b_index = 7;
                  } else {
                    Mission_Manager_CGN_B.i_a = std::memcmp(&i_a_0[0],
                      &Mission_Manager_CGN_B.switch_expression[0], 16);
                    if (Mission_Manager_CGN_B.i_a == 0) {
                      Mission_Manager_CGN_B.b_index = 8;
                    } else {
                      Mission_Manager_CGN_B.i_a = std::memcmp(&j_a_0[0],
                        &Mission_Manager_CGN_B.switch_expression[0], 16);
                      if (Mission_Manager_CGN_B.i_a == 0) {
                        Mission_Manager_CGN_B.b_index = 9;
                      } else {
                        Mission_Manager_CGN_B.i_a = std::memcmp(&k_a[0],
                          &Mission_Manager_CGN_B.switch_expression[0], 16);
                        if (Mission_Manager_CGN_B.i_a == 0) {
                          Mission_Manager_CGN_B.b_index = 10;
                        } else {
                          Mission_Manager_CGN_B.i_a = std::memcmp(&l_a[0],
                            &Mission_Manager_CGN_B.switch_expression[0], 16);
                          if (Mission_Manager_CGN_B.i_a == 0) {
                            Mission_Manager_CGN_B.b_index = 11;
                          } else {
                            Mission_Manager_CGN_B.i_a = std::memcmp(&m_a[0],
                              &Mission_Manager_CGN_B.switch_expression[0], 16);
                            if (Mission_Manager_CGN_B.i_a == 0) {
                              Mission_Manager_CGN_B.b_index = 12;
                            } else {
                              Mission_Manager_CGN_B.b_index = -1;
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

    for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 8;
         Mission_Manager_CGN_B.i_a++) {
      switch (Mission_Manager_CGN_B.b_index) {
       case 0:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.forward[Mission_Manager_CGN_B.i_a];
        break;

       case 1:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.backward[Mission_Manager_CGN_B.i_a];
        break;

       case 2:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.up[Mission_Manager_CGN_B.i_a];
        break;

       case 3:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.down[Mission_Manager_CGN_B.i_a];
        break;

       case 4:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.left[Mission_Manager_CGN_B.i_a];
        break;

       case 5:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.right[Mission_Manager_CGN_B.i_a];
        break;

       case 6:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.pitchUp[Mission_Manager_CGN_B.i_a];
        break;

       case 7:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.pitchDown[Mission_Manager_CGN_B.i_a];
        break;

       case 8:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.yawRight[Mission_Manager_CGN_B.i_a];
        break;

       case 9:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.yawLeft[Mission_Manager_CGN_B.i_a];
        break;

       case 10:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.rollRight[Mission_Manager_CGN_B.i_a];
        break;

       case 11:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] =
          Mission_Manager_CGN_ConstP.trickFTListInjector_FF_maneuver.rollLeft[Mission_Manager_CGN_B.i_a];
        break;

       case 12:
        Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] = 0.0;
        break;
      }
    }
  }

  // MATLAB Function: '<S24>/forceToPWMCalculator' incorporates:
  //   Constant: '<S18>/Constant3'

  for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 8;
       Mission_Manager_CGN_B.i_a++) {
    Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] = 1500.0;
  }

  for (Mission_Manager_CGN_B.b_index = 0; Mission_Manager_CGN_B.b_index < 4;
       Mission_Manager_CGN_B.b_index++) {
    Mission_Manager_CGN_B.i_a = Mission_Manager_CGN_B.b_index << 1;
    Mission_Manager_CGN_B.rtb_FT_cmd_list_g =
      Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a];
    if (std::abs(Mission_Manager_CGN_B.rtb_FT_cmd_list_g) < 0.001) {
      Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] = 1500.0;
    } else {
      for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 4;
           Mission_Manager_CGN_B.iindx += 2) {
        _mm_storeu_pd(&Mission_Manager_CGN_B.dv8[0], _mm_sub_pd(_mm_loadu_pd
          (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage[Mission_Manager_CGN_B.iindx]),
          _mm_set1_pd(15.0)));
        Mission_Manager_CGN_B.dv7[0] = std::abs(Mission_Manager_CGN_B.dv8[0]);
        Mission_Manager_CGN_B.dv7[1] = std::abs(Mission_Manager_CGN_B.dv8[1]);
        tmp_5 = _mm_loadu_pd(&Mission_Manager_CGN_B.dv7[0]);
        _mm_storeu_pd
          (&Mission_Manager_CGN_B.varargin_1_f[Mission_Manager_CGN_B.iindx],
           tmp_5);
      }

      Mission_Manager_CGN_minimum(Mission_Manager_CGN_B.varargin_1_f,
        &Mission_Manager_CGN_B.eta, &Mission_Manager_CGN_B.iindx);
      switch (Mission_Manager_CGN_B.iindx) {
       case 1:
        Mission_Manager_CGN_B.lower_voltage_index = 1.0;
        Mission_Manager_CGN_B.upper_voltage_index = 1.0;
        break;

       case 6:
        Mission_Manager_CGN_B.lower_voltage_index = 6.0;
        Mission_Manager_CGN_B.upper_voltage_index = 6.0;
        break;

       default:
        if (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage[Mission_Manager_CGN_B.iindx
            - 1] < 15.0) {
          Mission_Manager_CGN_B.lower_voltage_index =
            Mission_Manager_CGN_B.iindx;
          Mission_Manager_CGN_B.upper_voltage_index = static_cast<real_T>
            (Mission_Manager_CGN_B.iindx) + 1.0;
        } else {
          Mission_Manager_CGN_B.upper_voltage_index =
            Mission_Manager_CGN_B.iindx;
          Mission_Manager_CGN_B.lower_voltage_index = static_cast<real_T>
            (Mission_Manager_CGN_B.iindx) - 1.0;
        }
        break;
      }

      if (Mission_Manager_CGN_B.upper_voltage_index ==
          Mission_Manager_CGN_B.lower_voltage_index) {
        Mission_Manager_CGN_B.force_column_size_idx_0 = 1;
        Mission_Manager_CGN_B.force_column_data[0] =
          Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[static_cast<
          int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index)
                  - 1] -
                  Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index)
                  - 1]) < 0.001) {
        Mission_Manager_CGN_B.force_column_size_idx_0 = 1;
        Mission_Manager_CGN_B.force_column_data[0] =
          Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force
          [static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1];
      } else {
        _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd
          (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage
           [static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index) - 1],
           15.0), _mm_set1_pd
          (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage
           [static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1])));
        Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.dv9[0];
        Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.dv9[1];
        Mission_Manager_CGN_B.force_column_size_idx_0 = 201;
        for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 198;
             Mission_Manager_CGN_B.iindx += 2) {
          Mission_Manager_CGN_B.loop_ub = (static_cast<int32_T>
            (Mission_Manager_CGN_B.lower_voltage_index) - 1) * 201 +
            Mission_Manager_CGN_B.iindx;
          tmp_5 = _mm_loadu_pd
            (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[Mission_Manager_CGN_B.loop_ub]);
          _mm_storeu_pd
            (&Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx],
             _mm_add_pd(_mm_div_pd(_mm_mul_pd(_mm_sub_pd(_mm_loadu_pd
                 (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[(
                   static_cast<int32_T>
                   (Mission_Manager_CGN_B.upper_voltage_index) - 1) * 201 +
                  Mission_Manager_CGN_B.iindx]), tmp_5), _mm_set1_pd
                (Mission_Manager_CGN_B.eta)), _mm_set1_pd
               (Mission_Manager_CGN_B.lower_force_index)), tmp_5));
        }

        for (Mission_Manager_CGN_B.iindx = 200; Mission_Manager_CGN_B.iindx <
             201; Mission_Manager_CGN_B.iindx++) {
          Mission_Manager_CGN_B.force_column_tmp =
            Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[(
            static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1)
            * 201 + Mission_Manager_CGN_B.iindx];
          Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx] =
            (Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_force[(
              static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index) -
              1) * 201 + Mission_Manager_CGN_B.iindx] -
             Mission_Manager_CGN_B.force_column_tmp) * Mission_Manager_CGN_B.eta
            / Mission_Manager_CGN_B.lower_force_index +
            Mission_Manager_CGN_B.force_column_tmp;
        }
      }

      Mission_Manager_CGN_B.loop_ub =
        (Mission_Manager_CGN_B.force_column_size_idx_0 / 2) << 1;
      Mission_Manager_CGN_B.vectorUB = Mission_Manager_CGN_B.loop_ub - 2;
      for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <=
           Mission_Manager_CGN_B.vectorUB; Mission_Manager_CGN_B.iindx += 2) {
        tmp_5 = _mm_loadu_pd
          (&Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx]);
        _mm_storeu_pd
          (&Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.iindx],
           _mm_sub_pd(tmp_5, _mm_set1_pd(Mission_Manager_CGN_B.rtb_FT_cmd_list_g)));
      }

      for (Mission_Manager_CGN_B.iindx = Mission_Manager_CGN_B.loop_ub;
           Mission_Manager_CGN_B.iindx <
           Mission_Manager_CGN_B.force_column_size_idx_0;
           Mission_Manager_CGN_B.iindx++) {
        Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.iindx] =
          Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx] -
          Mission_Manager_CGN_B.rtb_FT_cmd_list_g;
      }

      Mission_Manager_CGN_B.b_varargin_1_size =
        Mission_Manager_CGN_B.force_column_size_idx_0;
      for (Mission_Manager_CGN_B.loop_ub = 0; Mission_Manager_CGN_B.loop_ub <
           Mission_Manager_CGN_B.force_column_size_idx_0;
           Mission_Manager_CGN_B.loop_ub++) {
        Mission_Manager_CGN_B.b_varargin_1_data[Mission_Manager_CGN_B.loop_ub] =
          std::abs(Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.loop_ub]);
      }

      Mission_Manager_CGN_minimum_m(Mission_Manager_CGN_B.b_varargin_1_data,
        &Mission_Manager_CGN_B.b_varargin_1_size, &Mission_Manager_CGN_B.eta,
        &Mission_Manager_CGN_B.iindx);
      if ((Mission_Manager_CGN_B.iindx == 1) || (Mission_Manager_CGN_B.iindx ==
           2)) {
        Mission_Manager_CGN_B.lower_force_index = 1.0;
        Mission_Manager_CGN_B.eta = 1.0;
      } else if ((Mission_Manager_CGN_B.iindx == 8) ||
                 (Mission_Manager_CGN_B.iindx == 7)) {
        Mission_Manager_CGN_B.lower_force_index = 8.0;
        Mission_Manager_CGN_B.eta = 8.0;
      } else if
          (Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx -
           1] < Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a]) {
        Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.iindx;
        Mission_Manager_CGN_B.eta = static_cast<real_T>
          (Mission_Manager_CGN_B.iindx) + 1.0;
      } else {
        Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.iindx;
        Mission_Manager_CGN_B.lower_force_index = static_cast<real_T>
          (Mission_Manager_CGN_B.iindx) - 1.0;
      }

      if (Mission_Manager_CGN_B.eta >
          Mission_Manager_CGN_B.force_column_size_idx_0) {
        Mission_Manager_CGN_B.eta =
          Mission_Manager_CGN_B.force_column_size_idx_0;
      }

      if ((static_cast<int32_T>(Mission_Manager_CGN_B.eta) ==
           Mission_Manager_CGN_B.force_column_size_idx_0) && (static_cast<real_T>
           (Mission_Manager_CGN_B.force_column_size_idx_0) - 1.0 ==
           Mission_Manager_CGN_B.lower_force_index)) {
        Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.eta;
      } else if ((Mission_Manager_CGN_B.eta == 2.0) &&
                 (Mission_Manager_CGN_B.lower_force_index == 1.0)) {
        Mission_Manager_CGN_B.eta = 1.0;
      }

      if (Mission_Manager_CGN_B.lower_force_index == Mission_Manager_CGN_B.eta)
      {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
      } else if (std::abs(Mission_Manager_CGN_B.force_column_data
                          [static_cast<int32_T>(Mission_Manager_CGN_B.eta) - 1]
                          - Mission_Manager_CGN_B.force_column_data[static_cast<
                          int32_T>(Mission_Manager_CGN_B.lower_force_index) - 1])
                 < 0.001) {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
      } else {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
          (Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] -
           Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.eta) - 1]) /
          (Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.eta) - 1] -
           Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.lower_force_index) - 1]);
      }

      Mission_Manager_CGN_B.lower_force_index =
        Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_pwm
        [static_cast<int32_T>(Mission_Manager_CGN_B.lower_force_index) - 1];
      Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] = std::round
        ((Mission_Manager_CGN_ConstP.forceToPWMCalculator_cw_pwm[static_cast<
          int32_T>(Mission_Manager_CGN_B.eta) - 1] -
          Mission_Manager_CGN_B.lower_force_index) *
         Mission_Manager_CGN_B.rtb_Filter_h_idx_1 +
         Mission_Manager_CGN_B.lower_force_index);
    }
  }

  for (Mission_Manager_CGN_B.b_index = 0; Mission_Manager_CGN_B.b_index < 4;
       Mission_Manager_CGN_B.b_index++) {
    Mission_Manager_CGN_B.i_a = (Mission_Manager_CGN_B.b_index << 1) + 1;
    Mission_Manager_CGN_B.rtb_FT_cmd_list_g =
      Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a];
    if (std::abs(Mission_Manager_CGN_B.rtb_FT_cmd_list_g) < 0.001) {
      Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] = 1500.0;
    } else {
      for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 4;
           Mission_Manager_CGN_B.iindx += 2) {
        _mm_storeu_pd(&Mission_Manager_CGN_B.dv6[0], _mm_sub_pd(_mm_loadu_pd
          (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage[Mission_Manager_CGN_B.iindx]),
          _mm_set1_pd(15.0)));
        Mission_Manager_CGN_B.dv5[0] = std::abs(Mission_Manager_CGN_B.dv6[0]);
        Mission_Manager_CGN_B.dv5[1] = std::abs(Mission_Manager_CGN_B.dv6[1]);
        tmp_5 = _mm_loadu_pd(&Mission_Manager_CGN_B.dv5[0]);
        _mm_storeu_pd
          (&Mission_Manager_CGN_B.varargin_1_f[Mission_Manager_CGN_B.iindx],
           tmp_5);
      }

      Mission_Manager_CGN_minimum(Mission_Manager_CGN_B.varargin_1_f,
        &Mission_Manager_CGN_B.eta, &Mission_Manager_CGN_B.iindx);
      switch (Mission_Manager_CGN_B.iindx) {
       case 1:
        Mission_Manager_CGN_B.lower_voltage_index = 1.0;
        Mission_Manager_CGN_B.upper_voltage_index = 1.0;
        break;

       case 6:
        Mission_Manager_CGN_B.lower_voltage_index = 6.0;
        Mission_Manager_CGN_B.upper_voltage_index = 6.0;
        break;

       default:
        if (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage[Mission_Manager_CGN_B.iindx
            - 1] < 15.0) {
          Mission_Manager_CGN_B.lower_voltage_index =
            Mission_Manager_CGN_B.iindx;
          Mission_Manager_CGN_B.upper_voltage_index = static_cast<real_T>
            (Mission_Manager_CGN_B.iindx) + 1.0;
        } else {
          Mission_Manager_CGN_B.upper_voltage_index =
            Mission_Manager_CGN_B.iindx;
          Mission_Manager_CGN_B.lower_voltage_index = static_cast<real_T>
            (Mission_Manager_CGN_B.iindx) - 1.0;
        }
        break;
      }

      if (Mission_Manager_CGN_B.upper_voltage_index ==
          Mission_Manager_CGN_B.lower_voltage_index) {
        Mission_Manager_CGN_B.force_column_size_idx_0 = 1;
        Mission_Manager_CGN_B.force_column_data[0] =
          Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[static_cast<
          int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index)
                  - 1] -
                  Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index)
                  - 1]) < 0.001) {
        Mission_Manager_CGN_B.force_column_size_idx_0 = 1;
        Mission_Manager_CGN_B.force_column_data[0] =
          Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[static_cast<
          int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1];
      } else {
        _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_sub_pd(_mm_set_pd
          (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage
           [static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index) - 1],
           15.0), _mm_set1_pd
          (Mission_Manager_CGN_ConstP.forceToPWMCalculator_voltage
           [static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1])));
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.dv9[0];
        Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.dv9[1];
        Mission_Manager_CGN_B.force_column_size_idx_0 = 201;
        for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <= 198;
             Mission_Manager_CGN_B.iindx += 2) {
          Mission_Manager_CGN_B.loop_ub = (static_cast<int32_T>
            (Mission_Manager_CGN_B.lower_voltage_index) - 1) * 201 +
            Mission_Manager_CGN_B.iindx;
          tmp_5 = _mm_loadu_pd
            (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[Mission_Manager_CGN_B.loop_ub]);
          _mm_storeu_pd
            (&Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx],
             _mm_add_pd(_mm_div_pd(_mm_mul_pd(_mm_sub_pd(_mm_loadu_pd
                 (&Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[(
                   static_cast<int32_T>
                   (Mission_Manager_CGN_B.upper_voltage_index) - 1) * 201 +
                  Mission_Manager_CGN_B.iindx]), tmp_5), _mm_set1_pd
                (Mission_Manager_CGN_B.rtb_Filter_h_idx_1)), _mm_set1_pd
               (Mission_Manager_CGN_B.lower_force_index)), tmp_5));
        }

        for (Mission_Manager_CGN_B.iindx = 200; Mission_Manager_CGN_B.iindx <
             201; Mission_Manager_CGN_B.iindx++) {
          Mission_Manager_CGN_B.force_column_tmp =
            Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[(
            static_cast<int32_T>(Mission_Manager_CGN_B.lower_voltage_index) - 1)
            * 201 + Mission_Manager_CGN_B.iindx];
          Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx] =
            (Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_force[(
              static_cast<int32_T>(Mission_Manager_CGN_B.upper_voltage_index) -
              1) * 201 + Mission_Manager_CGN_B.iindx] -
             Mission_Manager_CGN_B.force_column_tmp) *
            Mission_Manager_CGN_B.rtb_Filter_h_idx_1 /
            Mission_Manager_CGN_B.lower_force_index +
            Mission_Manager_CGN_B.force_column_tmp;
        }
      }

      Mission_Manager_CGN_B.loop_ub =
        (Mission_Manager_CGN_B.force_column_size_idx_0 / 2) << 1;
      Mission_Manager_CGN_B.vectorUB = Mission_Manager_CGN_B.loop_ub - 2;
      for (Mission_Manager_CGN_B.iindx = 0; Mission_Manager_CGN_B.iindx <=
           Mission_Manager_CGN_B.vectorUB; Mission_Manager_CGN_B.iindx += 2) {
        tmp_5 = _mm_loadu_pd
          (&Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx]);
        _mm_storeu_pd
          (&Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.iindx],
           _mm_sub_pd(tmp_5, _mm_set1_pd(Mission_Manager_CGN_B.rtb_FT_cmd_list_g)));
      }

      for (Mission_Manager_CGN_B.iindx = Mission_Manager_CGN_B.loop_ub;
           Mission_Manager_CGN_B.iindx <
           Mission_Manager_CGN_B.force_column_size_idx_0;
           Mission_Manager_CGN_B.iindx++) {
        Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.iindx] =
          Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx] -
          Mission_Manager_CGN_B.rtb_FT_cmd_list_g;
      }

      Mission_Manager_CGN_B.b_varargin_1_size =
        Mission_Manager_CGN_B.force_column_size_idx_0;
      for (Mission_Manager_CGN_B.loop_ub = 0; Mission_Manager_CGN_B.loop_ub <
           Mission_Manager_CGN_B.force_column_size_idx_0;
           Mission_Manager_CGN_B.loop_ub++) {
        Mission_Manager_CGN_B.b_varargin_1_data[Mission_Manager_CGN_B.loop_ub] =
          std::abs(Mission_Manager_CGN_B.b_x_data[Mission_Manager_CGN_B.loop_ub]);
      }

      Mission_Manager_CGN_minimum_m(Mission_Manager_CGN_B.b_varargin_1_data,
        &Mission_Manager_CGN_B.b_varargin_1_size, &Mission_Manager_CGN_B.eta,
        &Mission_Manager_CGN_B.iindx);
      if ((Mission_Manager_CGN_B.iindx == 1) || (Mission_Manager_CGN_B.iindx ==
           2)) {
        Mission_Manager_CGN_B.lower_force_index = 1.0;
        Mission_Manager_CGN_B.eta = 1.0;
      } else if ((Mission_Manager_CGN_B.iindx == 8) ||
                 (Mission_Manager_CGN_B.iindx == 7)) {
        Mission_Manager_CGN_B.lower_force_index = 8.0;
        Mission_Manager_CGN_B.eta = 8.0;
      } else if
          (Mission_Manager_CGN_B.force_column_data[Mission_Manager_CGN_B.iindx -
           1] < Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a]) {
        Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.iindx;
        Mission_Manager_CGN_B.eta = static_cast<real_T>
          (Mission_Manager_CGN_B.iindx) + 1.0;
      } else {
        Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.iindx;
        Mission_Manager_CGN_B.lower_force_index = static_cast<real_T>
          (Mission_Manager_CGN_B.iindx) - 1.0;
      }

      if (Mission_Manager_CGN_B.eta >
          Mission_Manager_CGN_B.force_column_size_idx_0) {
        Mission_Manager_CGN_B.eta =
          Mission_Manager_CGN_B.force_column_size_idx_0;
      }

      if (Mission_Manager_CGN_B.lower_force_index == Mission_Manager_CGN_B.eta)
      {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
      } else if (std::abs(Mission_Manager_CGN_B.force_column_data
                          [static_cast<int32_T>(Mission_Manager_CGN_B.eta) - 1]
                          - Mission_Manager_CGN_B.force_column_data[static_cast<
                          int32_T>(Mission_Manager_CGN_B.lower_force_index) - 1])
                 < 0.001) {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
      } else {
        Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
          (Mission_Manager_CGN_B.FT_cmd_list[Mission_Manager_CGN_B.i_a] -
           Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.eta) - 1]) /
          (Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.eta) - 1] -
           Mission_Manager_CGN_B.force_column_data[static_cast<int32_T>
           (Mission_Manager_CGN_B.lower_force_index) - 1]);
      }

      Mission_Manager_CGN_B.lower_force_index =
        Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_pwm
        [static_cast<int32_T>(Mission_Manager_CGN_B.lower_force_index) - 1];
      Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] = std::round
        ((Mission_Manager_CGN_ConstP.forceToPWMCalculator_ccw_pwm
          [static_cast<int32_T>(Mission_Manager_CGN_B.eta) - 1] -
          Mission_Manager_CGN_B.lower_force_index) *
         Mission_Manager_CGN_B.rtb_Filter_h_idx_1 +
         Mission_Manager_CGN_B.lower_force_index);
    }
  }

  for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 8;
       Mission_Manager_CGN_B.i_a++) {
    Mission_Manager_CGN_B.b_index = static_cast<int32_T>(std::fmax(1100.0, std::
      fmin(1900.0, Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a])));
    Mission_Manager_CGN_B.pwms[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.b_index;

    // DataTypeConversion: '<S18>/Cast'
    Mission_Manager_CGN_B.Cast[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.b_index;
  }

  // End of MATLAB Function: '<S24>/forceToPWMCalculator'

  // DeadZone: '<S118>/DeadZone' incorporates:
  //   Gain: '<S123>/Integral Gain'

  if (Mission_Manager_CGN_B.eul_error[0] > 1.0) {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.eul_error[0]
      - 1.0;

    // Switch: '<S116>/Switch1' incorporates:
    //   Constant: '<S116>/Constant'

    Mission_Manager_CGN_B.i4 = 1;
  } else {
    if (Mission_Manager_CGN_B.eul_error[0] >= -1.0) {
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
    } else {
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
        Mission_Manager_CGN_B.eul_error[0] - -1.0;
    }

    // Switch: '<S116>/Switch1' incorporates:
    //   Constant: '<S116>/Constant2'

    Mission_Manager_CGN_B.i4 = -1;
  }

  // Logic: '<S116>/AND3' incorporates:
  //   Constant: '<S116>/Clamping_zero'
  //   Gain: '<S123>/Integral Gain'
  //   RelationalOperator: '<S116>/Equal1'
  //   RelationalOperator: '<S116>/Relational Operator'
  //   Switch: '<S116>/Switch1'
  //   Switch: '<S116>/Switch2'

  Mission_Manager_CGN_B.b_varargout_1 =
    ((Mission_Manager_CGN_B.rtb_Filter_h_idx_1 != 0.0) &&
     (Mission_Manager_CGN_B.i4 == -1));

  // DeadZone: '<S173>/DeadZone'
  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 > 100.0) {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 -
      100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 >= -100.0) {
    Mission_Manager_CGN_B.eta = 0.0;
  } else {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 -
      -100.0;
  }

  // RelationalOperator: '<S171>/Relational Operator' incorporates:
  //   Constant: '<S171>/Clamping_zero'

  Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 =
    (Mission_Manager_CGN_B.eta != 0.0);

  // Switch: '<S171>/Switch1' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant'
  //   Constant: '<S171>/Constant2'
  //   RelationalOperator: '<S171>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.eta > 0.0) {
    Mission_Manager_CGN_B.rtb_Switch1_idx_0 = 1;
  } else {
    Mission_Manager_CGN_B.rtb_Switch1_idx_0 = -1;
  }

  // Gain: '<S178>/Integral Gain'
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 = 20.0 *
    Mission_Manager_CGN_B.dRb_e[0];

  // DeadZone: '<S118>/DeadZone' incorporates:
  //   Gain: '<S123>/Integral Gain'

  if (Mission_Manager_CGN_B.eul_error[1] > 1.0) {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.eul_error[1]
      - 1.0;

    // Switch: '<S116>/Switch1' incorporates:
    //   Constant: '<S116>/Constant'

    Mission_Manager_CGN_B.i4 = 1;
  } else {
    if (Mission_Manager_CGN_B.eul_error[1] >= -1.0) {
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
    } else {
      Mission_Manager_CGN_B.rtb_Filter_h_idx_1 =
        Mission_Manager_CGN_B.eul_error[1] - -1.0;
    }

    // Switch: '<S116>/Switch1' incorporates:
    //   Constant: '<S116>/Constant2'

    Mission_Manager_CGN_B.i4 = -1;
  }

  // Logic: '<S116>/AND3' incorporates:
  //   Constant: '<S116>/Clamping_zero'
  //   Gain: '<S123>/Integral Gain'
  //   RelationalOperator: '<S116>/Equal1'
  //   RelationalOperator: '<S116>/Relational Operator'
  //   Switch: '<S116>/Switch1'
  //   Switch: '<S116>/Switch2'

  Mission_Manager_CGN_B.rtb_RelationalOperator_o_o =
    ((Mission_Manager_CGN_B.rtb_Filter_h_idx_1 != 0.0) &&
     (Mission_Manager_CGN_B.i4 == -1));

  // DeadZone: '<S173>/DeadZone'
  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 > 100.0) {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 -
      100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 >= -100.0) {
    Mission_Manager_CGN_B.eta = 0.0;
  } else {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 -
      -100.0;
  }

  // RelationalOperator: '<S171>/Relational Operator' incorporates:
  //   Constant: '<S171>/Clamping_zero'

  Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_1 =
    (Mission_Manager_CGN_B.eta != 0.0);

  // Switch: '<S171>/Switch1' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant'
  //   Constant: '<S171>/Constant2'
  //   RelationalOperator: '<S171>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.eta > 0.0) {
    Mission_Manager_CGN_B.rtb_Switch1_idx_1 = 1;
  } else {
    Mission_Manager_CGN_B.rtb_Switch1_idx_1 = -1;
  }

  // Gain: '<S178>/Integral Gain'
  Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 = 20.0 *
    Mission_Manager_CGN_B.dRb_e[1];

  // DeadZone: '<S118>/DeadZone' incorporates:
  //   Gain: '<S123>/Integral Gain'

  if (Mission_Manager_CGN_B.eul_error[2] > 1.0) {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.eul_error[2]
      - 1.0;
  } else if (Mission_Manager_CGN_B.eul_error[2] >= -1.0) {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = 0.0;
  } else {
    Mission_Manager_CGN_B.rtb_Filter_h_idx_1 = Mission_Manager_CGN_B.eul_error[2]
      - -1.0;
  }

  // DeadZone: '<S173>/DeadZone' incorporates:
  //   Sum: '<S190>/Sum'

  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l > 100.0) {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_l -
      100.0;
  } else if (Mission_Manager_CGN_B.rtb_IntegralGain_b_l >= -100.0) {
    Mission_Manager_CGN_B.eta = 0.0;
  } else {
    Mission_Manager_CGN_B.eta = Mission_Manager_CGN_B.rtb_IntegralGain_b_l -
      -100.0;
  }

  // RelationalOperator: '<S171>/Relational Operator' incorporates:
  //   Constant: '<S171>/Clamping_zero'

  Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_2 =
    (Mission_Manager_CGN_B.eta != 0.0);

  // Switch: '<S171>/Switch1' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant'
  //   Constant: '<S171>/Constant2'
  //   RelationalOperator: '<S171>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.eta > 0.0) {
    Mission_Manager_CGN_B.rtb_Switch1_f = 1;
  } else {
    Mission_Manager_CGN_B.rtb_Switch1_f = -1;
  }

  // Gain: '<S178>/Integral Gain'
  Mission_Manager_CGN_B.eta = 20.0 * Mission_Manager_CGN_B.dRb_e[2];

  // Update for UnitDelay: '<S21>/Delay Input1' incorporates:
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S21>/Delay Input1':
  //
  //   Store in Global RAM

  Mission_Manager_CGN_DW.DelayInput1_DSTATE =
    Mission_Manager_CGN_DW.UnitDelay_DSTATE;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read6'
  //   MATLAB Function: '<S18>/deltaQuatError'
  //
  if (Mission_Manager_CGN_B.integrator_reset > 0) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_PrevRese = 0;
  }

  Mission_Manager_CGN_B.b_t = (1.0 - Mission_Manager_CGN_B.b_t) * 0.01 +
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[0];
  Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[0] =
    Mission_Manager_CGN_B.b_t;
  if (Mission_Manager_CGN_B.b_t > 1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[0] = 1.0471975511965976;
  } else if (Mission_Manager_CGN_B.b_t < -1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[0] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S18>/Discrete Transfer Fcn'
  Mission_Manager_CGN_DW.DiscreteTransferFcn_states[0] =
    Mission_Manager_CGN_B.b_scale;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S18>/deltaQuatError'

  Mission_Manager_CGN_B.b_t = (0.0 - Mission_Manager_CGN_B.DigitalClock) * 0.01
    + Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[1];
  Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[1] =
    Mission_Manager_CGN_B.b_t;
  if (Mission_Manager_CGN_B.b_t > 1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[1] = 1.0471975511965976;
  } else if (Mission_Manager_CGN_B.b_t < -1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[1] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S18>/Discrete Transfer Fcn'
  Mission_Manager_CGN_DW.DiscreteTransferFcn_states[1] =
    Mission_Manager_CGN_B.b_absxk;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S18>/deltaQuatError'

  Mission_Manager_CGN_B.b_t = (0.0 - Mission_Manager_CGN_B.t) * 0.01 +
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[2];
  Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[2] =
    Mission_Manager_CGN_B.b_t;
  if (Mission_Manager_CGN_B.b_t > 1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[2] = 1.0471975511965976;
  } else if (Mission_Manager_CGN_B.b_t < -1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[2] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S18>/Discrete Transfer Fcn'
  Mission_Manager_CGN_DW.DiscreteTransferFcn_states[2] =
    Mission_Manager_CGN_B.psi;

  // Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S18>/deltaQuatError'

  Mission_Manager_CGN_B.b_t = (0.0 - Mission_Manager_CGN_B.scale) * 0.01 +
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[3];
  Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[3] =
    Mission_Manager_CGN_B.b_t;
  if (Mission_Manager_CGN_B.b_t > 1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[3] = 1.0471975511965976;
  } else if (Mission_Manager_CGN_B.b_t < -1.0471975511965976) {
    Mission_Manager_CGN_DW.DiscreteTimeIntegrator_DSTATE[3] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S18>/Discrete Transfer Fcn'
  Mission_Manager_CGN_DW.DiscreteTransferFcn_states[3] =
    Mission_Manager_CGN_B.absxk;

  // Update for DiscreteIntegrator: '<S126>/Integrator' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read1'
  //   DiscreteIntegrator: '<S121>/Filter'
  //   DiscreteIntegrator: '<S181>/Integrator'
  //   DiscreteIntegrator: '<S66>/Filter'
  //   DiscreteIntegrator: '<S71>/Integrator'
  //
  if (Mission_Manager_CGN_B.integrator_reset > 0) {
    Mission_Manager_CGN_DW.Integrator_PrevResetState = 1;
    Mission_Manager_CGN_DW.Filter_PrevResetState = 1;
    Mission_Manager_CGN_DW.Integrator_PrevResetState_i = 1;
    Mission_Manager_CGN_DW.Filter_PrevResetState_g = 1;
    Mission_Manager_CGN_DW.Integrator_PrevResetState_a = 1;
  } else {
    Mission_Manager_CGN_DW.Integrator_PrevResetState = 0;
    Mission_Manager_CGN_DW.Filter_PrevResetState = 0;
    Mission_Manager_CGN_DW.Integrator_PrevResetState_i = 0;
    Mission_Manager_CGN_DW.Filter_PrevResetState_g = 0;
    Mission_Manager_CGN_DW.Integrator_PrevResetState_a = 0;
  }

  // Switch: '<S116>/Switch' incorporates:
  //   Constant: '<S116>/Constant1'
  //   Gain: '<S123>/Integral Gain'
  //   Logic: '<S116>/AND3'

  if (Mission_Manager_CGN_B.b_varargout_1) {
    Mission_Manager_CGN_B.lower_force_index = 0.0;
  } else {
    Mission_Manager_CGN_B.lower_force_index = 0.0 * Mission_Manager_CGN_B.eps[0];
  }

  // Update for DiscreteIntegrator: '<S126>/Integrator' incorporates:
  //   Switch: '<S116>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.lower_force_index +
    Mission_Manager_CGN_DW.Integrator_DSTATE[0];
  Mission_Manager_CGN_DW.Integrator_DSTATE[0] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[0] = 1.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[0] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S121>/Filter' incorporates:
  //   Gain: '<S129>/Filter Coefficient'

  Mission_Manager_CGN_DW.Filter_DSTATE[0] += 0.01 *
    Mission_Manager_CGN_B.R_error[0];

  // Switch: '<S61>/Switch1' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant'
  //   Constant: '<S61>/Constant2'
  //   RelationalOperator: '<S61>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.rtb_Integrator_f_idx_0 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S61>/Switch2' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant3'
  //   Constant: '<S61>/Constant4'
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S68>/Integral Gain'
  //   RelationalOperator: '<S61>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.eps_g[0] > 0.0) {
    Mission_Manager_CGN_B.i5 = 1;
  } else {
    Mission_Manager_CGN_B.i5 = -1;
  }

  // Switch: '<S61>/Switch' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant1'
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S68>/Integral Gain'
  //   Logic: '<S61>/AND3'
  //   RelationalOperator: '<S61>/Equal1'
  //   RelationalOperator: '<S61>/Relational Operator'
  //   Switch: '<S61>/Switch1'
  //   Switch: '<S61>/Switch2'

  if ((Mission_Manager_CGN_B.rtb_Integrator_f_idx_0 != 0.0) &&
      (Mission_Manager_CGN_B.i4 == Mission_Manager_CGN_B.i5)) {
    Mission_Manager_CGN_B.lower_force_index = 0.0;
  } else {
    Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.eps_g[0];
  }

  // Update for DiscreteIntegrator: '<S71>/Integrator' incorporates:
  //   Switch: '<S61>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.lower_force_index +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[0];
  Mission_Manager_CGN_DW.Integrator_DSTATE_c[0] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[0] = 10.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[0] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S66>/Filter'
  Mission_Manager_CGN_DW.Filter_DSTATE_g[0] += 0.01 *
    Mission_Manager_CGN_B.dRb_u[0];

  // Switch: '<S171>/Switch2' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant3'
  //   Constant: '<S171>/Constant4'
  //   RelationalOperator: '<S171>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S171>/Switch' incorporates:
  //   Constant: '<S171>/Constant1'
  //   Logic: '<S171>/AND3'
  //   RelationalOperator: '<S171>/Equal1'
  //   Switch: '<S171>/Switch2'

  if (Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_0 &&
      (Mission_Manager_CGN_B.rtb_Switch1_idx_0 == Mission_Manager_CGN_B.i4)) {
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S181>/Integrator' incorporates:
  //   Switch: '<S171>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_0 +
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[0];
  Mission_Manager_CGN_DW.Integrator_DSTATE_b[0] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[0] = 100.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[0] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Filter'
  Mission_Manager_CGN_DW.Filter_DSTATE_m[0] += 0.01 *
    Mission_Manager_CGN_B.rtb_FilterCoefficient_g_idx_0;

  // Switch: '<S116>/Switch' incorporates:
  //   Constant: '<S116>/Constant1'
  //   Gain: '<S123>/Integral Gain'
  //   Logic: '<S116>/AND3'

  if (Mission_Manager_CGN_B.rtb_RelationalOperator_o_o) {
    Mission_Manager_CGN_B.lower_force_index = 0.0;
  } else {
    Mission_Manager_CGN_B.lower_force_index = 0.0 * Mission_Manager_CGN_B.eps[1];
  }

  // Update for DiscreteIntegrator: '<S126>/Integrator' incorporates:
  //   Switch: '<S116>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.lower_force_index +
    Mission_Manager_CGN_DW.Integrator_DSTATE[1];
  Mission_Manager_CGN_DW.Integrator_DSTATE[1] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[1] = 1.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[1] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S121>/Filter' incorporates:
  //   Gain: '<S129>/Filter Coefficient'

  Mission_Manager_CGN_DW.Filter_DSTATE[1] += 0.01 *
    Mission_Manager_CGN_B.R_error[1];

  // Switch: '<S61>/Switch1' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant'
  //   Constant: '<S61>/Constant2'
  //   RelationalOperator: '<S61>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S61>/Switch2' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant3'
  //   Constant: '<S61>/Constant4'
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S68>/Integral Gain'
  //   RelationalOperator: '<S61>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.eps_g[1] > 0.0) {
    Mission_Manager_CGN_B.i5 = 1;
  } else {
    Mission_Manager_CGN_B.i5 = -1;
  }

  // Switch: '<S61>/Switch' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant1'
  //   DiscreteIntegrator: '<S71>/Integrator'
  //   Gain: '<S68>/Integral Gain'
  //   Logic: '<S61>/AND3'
  //   RelationalOperator: '<S61>/Equal1'
  //   RelationalOperator: '<S61>/Relational Operator'
  //   Switch: '<S61>/Switch1'
  //   Switch: '<S61>/Switch2'

  if ((Mission_Manager_CGN_B.rtb_Integrator_f_idx_1 != 0.0) &&
      (Mission_Manager_CGN_B.i4 == Mission_Manager_CGN_B.i5)) {
    Mission_Manager_CGN_B.lower_force_index = 0.0;
  } else {
    Mission_Manager_CGN_B.lower_force_index = Mission_Manager_CGN_B.eps_g[1];
  }

  // Update for DiscreteIntegrator: '<S71>/Integrator' incorporates:
  //   Switch: '<S61>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.lower_force_index +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[1];
  Mission_Manager_CGN_DW.Integrator_DSTATE_c[1] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[1] = 10.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[1] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S66>/Filter'
  Mission_Manager_CGN_DW.Filter_DSTATE_g[1] += 0.01 *
    Mission_Manager_CGN_B.dRb_u[1];

  // Switch: '<S171>/Switch2' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant3'
  //   Constant: '<S171>/Constant4'
  //   RelationalOperator: '<S171>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S171>/Switch' incorporates:
  //   Constant: '<S171>/Constant1'
  //   Logic: '<S171>/AND3'
  //   RelationalOperator: '<S171>/Equal1'
  //   Switch: '<S171>/Switch2'

  if (Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_1 &&
      (Mission_Manager_CGN_B.rtb_Switch1_idx_1 == Mission_Manager_CGN_B.i4)) {
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 = 0.0;
  }

  // Update for DiscreteIntegrator: '<S181>/Integrator' incorporates:
  //   Switch: '<S171>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.rtb_IntegralGain_b_idx_1 +
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[1];
  Mission_Manager_CGN_DW.Integrator_DSTATE_b[1] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[1] = 100.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[1] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Filter'
  Mission_Manager_CGN_DW.Filter_DSTATE_m[1] += 0.01 *
    Mission_Manager_CGN_B.rtb_Filter_h_idx_0;

  // Switch: '<S116>/Switch1' incorporates:
  //   Constant: '<S116>/Clamping_zero'
  //   Constant: '<S116>/Constant'
  //   Constant: '<S116>/Constant2'
  //   Gain: '<S123>/Integral Gain'
  //   RelationalOperator: '<S116>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.rtb_Filter_h_idx_1 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S116>/Switch' incorporates:
  //   Constant: '<S116>/Clamping_zero'
  //   Constant: '<S116>/Constant1'
  //   Gain: '<S123>/Integral Gain'
  //   Logic: '<S116>/AND3'
  //   RelationalOperator: '<S116>/Equal1'
  //   RelationalOperator: '<S116>/Relational Operator'
  //   Switch: '<S116>/Switch1'
  //   Switch: '<S116>/Switch2'

  if ((Mission_Manager_CGN_B.rtb_Filter_h_idx_1 != 0.0) &&
      (Mission_Manager_CGN_B.i4 == -1)) {
    Mission_Manager_CGN_B.lower_force_index = 0.0;
  } else {
    Mission_Manager_CGN_B.lower_force_index = 0.0 * Mission_Manager_CGN_B.eps[2];
  }

  // Update for DiscreteIntegrator: '<S126>/Integrator' incorporates:
  //   Switch: '<S116>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 *
    Mission_Manager_CGN_B.lower_force_index +
    Mission_Manager_CGN_DW.Integrator_DSTATE[2];
  Mission_Manager_CGN_DW.Integrator_DSTATE[2] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[2] = 1.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -1.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE[2] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S121>/Filter' incorporates:
  //   Gain: '<S129>/Filter Coefficient'

  Mission_Manager_CGN_DW.Filter_DSTATE[2] += 0.01 *
    Mission_Manager_CGN_B.R_error[2];

  // Switch: '<S61>/Switch1' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant'
  //   Constant: '<S61>/Constant2'
  //   RelationalOperator: '<S61>/fix for DT propagation issue'

  if (Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S61>/Switch2' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant3'
  //   Constant: '<S61>/Constant4'
  //   Gain: '<S76>/Proportional Gain'
  //   RelationalOperator: '<S61>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.phi > 0.0) {
    Mission_Manager_CGN_B.i5 = 1;
  } else {
    Mission_Manager_CGN_B.i5 = -1;
  }

  // Switch: '<S61>/Switch' incorporates:
  //   Constant: '<S61>/Clamping_zero'
  //   Constant: '<S61>/Constant1'
  //   Logic: '<S61>/AND3'
  //   RelationalOperator: '<S61>/Equal1'
  //   RelationalOperator: '<S61>/Relational Operator'
  //   Switch: '<S61>/Switch1'
  //   Switch: '<S61>/Switch2'

  if ((Mission_Manager_CGN_B.rtb_Integrator_f_idx_2 != 0.0) &&
      (Mission_Manager_CGN_B.i4 == Mission_Manager_CGN_B.i5)) {
    Mission_Manager_CGN_B.phi = 0.0;
  }

  // Update for DiscreteIntegrator: '<S71>/Integrator' incorporates:
  //   Switch: '<S61>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 * Mission_Manager_CGN_B.phi +
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[2];
  Mission_Manager_CGN_DW.Integrator_DSTATE_c[2] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[2] = 10.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -10.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_c[2] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S66>/Filter' incorporates:
  //   Gain: '<S74>/Filter Coefficient'

  Mission_Manager_CGN_DW.Filter_DSTATE_g[2] += 0.01 *
    Mission_Manager_CGN_B.rtb_Cbi_tmp_tmp_d;

  // Switch: '<S171>/Switch2' incorporates:
  //   Constant: '<S171>/Clamping_zero'
  //   Constant: '<S171>/Constant3'
  //   Constant: '<S171>/Constant4'
  //   Gain: '<S178>/Integral Gain'
  //   RelationalOperator: '<S171>/fix for DT propagation issue1'

  if (Mission_Manager_CGN_B.eta > 0.0) {
    Mission_Manager_CGN_B.i4 = 1;
  } else {
    Mission_Manager_CGN_B.i4 = -1;
  }

  // Switch: '<S171>/Switch' incorporates:
  //   Constant: '<S171>/Constant1'
  //   Logic: '<S171>/AND3'
  //   RelationalOperator: '<S171>/Equal1'
  //   Switch: '<S171>/Switch1'
  //   Switch: '<S171>/Switch2'

  if (Mission_Manager_CGN_B.rtb_RelationalOperator_f_idx_2 &&
      (Mission_Manager_CGN_B.rtb_Switch1_f == Mission_Manager_CGN_B.i4)) {
    Mission_Manager_CGN_B.eta = 0.0;
  }

  // Update for DiscreteIntegrator: '<S181>/Integrator' incorporates:
  //   Switch: '<S171>/Switch'

  Mission_Manager_CGN_B.DigitalClock = 0.01 * Mission_Manager_CGN_B.eta +
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[2];
  Mission_Manager_CGN_DW.Integrator_DSTATE_b[2] =
    Mission_Manager_CGN_B.DigitalClock;
  if (Mission_Manager_CGN_B.DigitalClock > 100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[2] = 100.0;
  } else if (Mission_Manager_CGN_B.DigitalClock < -100.0) {
    Mission_Manager_CGN_DW.Integrator_DSTATE_b[2] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S176>/Filter' incorporates:
  //   DataStoreRead: '<S18>/Data Store Read9'
  //   Gain: '<S184>/Filter Coefficient'
  //
  Mission_Manager_CGN_DW.Filter_DSTATE_m[2] += 0.01 *
    Mission_Manager_CGN_B.rtb_X_est_idx_0;
  if (Mission_Manager_CGN_B.integrator_reset > 0) {
    Mission_Manager_CGN_DW.Filter_PrevResetState_l = 1;
  } else {
    Mission_Manager_CGN_DW.Filter_PrevResetState_l = 0;
  }

  // End of Outputs for SubSystem: '<S4>/cascaded_pid_controller'

  // BusCreator: '<S8>/Bus Creator3'
  for (Mission_Manager_CGN_B.i_a = 0; Mission_Manager_CGN_B.i_a < 8;
       Mission_Manager_CGN_B.i_a++) {
    Mission_Manager_CGN_B.BusCreator3.pwms[Mission_Manager_CGN_B.i_a] =
      Mission_Manager_CGN_B.Cast[Mission_Manager_CGN_B.i_a];
  }

  // End of BusCreator: '<S8>/Bus Creator3'

  // MATLABSystem: '<S208>/SinkBlock'
  Pub_Mission_Manager_CGN_323_2.publish(&Mission_Manager_CGN_B.BusCreator3);
  if ((&Mission_Manager_CGN_M)->Timing.TaskCounters.TID[1] == 0) {
    // MATLABSystem: '<S207>/SinkBlock' incorporates:
    //   Constant: '<S206>/Constant'

    Pub_Mission_Manager_CGN_322_150.publish
      (&Mission_Manager_CGN_ConstP.Constant_Value);
  }

  // Update for DiscreteIntegrator: '<S5>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //
  Mission_Manager_CGN_DW.PositionIntegrator_IC_LOADING = 0U;
  if (Mission_Manager_CGN_B.b_varargout_1_c) {
    Mission_Manager_CGN_DW.PositionIntegrator_PrevResetSta = 1;
  } else {
    Mission_Manager_CGN_DW.PositionIntegrator_PrevResetSta = 0;
  }

  // Update for DiscreteIntegrator: '<S5>/Velocity Integrator'
  Mission_Manager_CGN_DW.VelocityIntegrator_IC_LOADING = 0U;

  // Update for DiscreteIntegrator: '<S5>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S5>/Velocity Integrator'
  //   MATLAB Function: '<S5>/derivedStateEstimates'

  Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[0] += 0.01 *
    Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0];

  // Update for DiscreteIntegrator: '<S5>/Velocity Integrator'
  tmp_5 = _mm_set1_pd(0.01);

  // MATLAB Function: '<S5>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S5>/Position Integrator'
  //   DiscreteIntegrator: '<S5>/Velocity Integrator'
  //   Sum: '<S5>/Sum'
  //
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_add_pd(_mm_mul_pd(tmp_5,
    _mm_set_pd(Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1],
               Mission_Manager_CGN_B.rtb_dvl_pos_g[0])), _mm_set_pd
    (Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[1],
     Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0])));

  // Update for DiscreteIntegrator: '<S5>/Velocity Integrator'
  Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[0] =
    Mission_Manager_CGN_B.dv9[0];

  // Update for DiscreteIntegrator: '<S5>/Position Integrator'
  Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[1] =
    Mission_Manager_CGN_B.dv9[1];

  // MATLAB Function: '<S5>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S5>/Position Integrator'
  //   DiscreteIntegrator: '<S5>/Velocity Integrator'
  //   Sum: '<S5>/Sum'
  //
  _mm_storeu_pd(&Mission_Manager_CGN_B.dv9[0], _mm_add_pd(_mm_mul_pd(tmp_5,
    _mm_set_pd(Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2],
               Mission_Manager_CGN_B.rtb_dvl_pos_g[1])), _mm_set_pd
    (Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[2],
     Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1])));

  // Update for DiscreteIntegrator: '<S5>/Velocity Integrator'
  Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[1] =
    Mission_Manager_CGN_B.dv9[0];

  // Update for DiscreteIntegrator: '<S5>/Position Integrator'
  Mission_Manager_CGN_DW.PositionIntegrator_DSTATE[2] =
    Mission_Manager_CGN_B.dv9[1];

  // Update for DiscreteIntegrator: '<S5>/Velocity Integrator' incorporates:
  //   MATLABSystem: '<S6>/SourceBlock'
  //   Sum: '<S5>/Sum'
  //
  Mission_Manager_CGN_DW.VelocityIntegrator_DSTATE[2] += 0.01 *
    Mission_Manager_CGN_B.rtb_dvl_pos_g[2];
  if (Mission_Manager_CGN_B.b_varargout_1_g) {
    Mission_Manager_CGN_DW.VelocityIntegrator_PrevResetSta = 1;
  } else {
    Mission_Manager_CGN_DW.VelocityIntegrator_PrevResetSta = 0;
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&Mission_Manager_CGN_M)->Timing.clockTick0++;
  rate_scheduler((&Mission_Manager_CGN_M));
}

// Model initialize function
void Mission_Manager_CGN::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S5>/Position Integrator'
  Mission_Manager_CGN_DW.PositionIntegrator_PrevResetSta = 2;
  Mission_Manager_CGN_DW.PositionIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S5>/Velocity Integrator'
  Mission_Manager_CGN_DW.VelocityIntegrator_PrevResetSta = 2;
  Mission_Manager_CGN_DW.VelocityIntegrator_IC_LOADING = 1U;

  // SystemInitialize for Enabled SubSystem: '<S1>/Subsystem'
  // Start for MATLABSystem: '<S15>/SinkBlock'
  Mission_Manager_CGN_DW.obj_op.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_op.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_op.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_op.isInitialized = 1;
  Mission_Man_Publisher_setupImpl(&Mission_Manager_CGN_DW.obj_op);
  Mission_Manager_CGN_DW.obj_op.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S1>/Subsystem'

  // SystemInitialize for MATLAB Function: '<S5>/dvl_reset'
  Mission_Manager_CGN_DW.prior_flag = true;

  // SystemInitialize for Enabled SubSystem: '<S4>/cascaded_pid_controller'
  // InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' 
  Mission_Manager_CGN_DW.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S126>/Integrator'
  Mission_Manager_CGN_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S121>/Filter'
  Mission_Manager_CGN_DW.Filter_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S71>/Integrator'
  Mission_Manager_CGN_DW.Integrator_PrevResetState_i = 2;

  // InitializeConditions for DiscreteIntegrator: '<S66>/Filter'
  Mission_Manager_CGN_DW.Filter_PrevResetState_g = 2;

  // InitializeConditions for DiscreteIntegrator: '<S181>/Integrator'
  Mission_Manager_CGN_DW.Integrator_PrevResetState_a = 2;

  // InitializeConditions for DiscreteIntegrator: '<S176>/Filter'
  Mission_Manager_CGN_DW.Filter_PrevResetState_l = 2;

  // End of SystemInitialize for SubSystem: '<S4>/cascaded_pid_controller'

  // Start for MATLABSystem: '<S10>/SourceBlock'
  Mission_Manager_CGN_DW.obj_m.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_m.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_m.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_m.isInitialized = 1;
  Mission_Ma_Subscriber_setupImpl(&Mission_Manager_CGN_DW.obj_m);
  Mission_Manager_CGN_DW.obj_m.isSetupComplete = true;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  Mission_Manager_CGN_DW.obj_p.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_p.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_p.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_p.isInitialized = 1;
  Mission_Subscriber_setupImpl_be(&Mission_Manager_CGN_DW.obj_p);
  Mission_Manager_CGN_DW.obj_p.isSetupComplete = true;

  // Start for MATLABSystem: '<S6>/SourceBlock'
  Mission_Manager_CGN_DW.obj.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj.isInitialized = 1;
  Missio_Subscriber_setupImpl_bea(&Mission_Manager_CGN_DW.obj);
  Mission_Manager_CGN_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  Mission_Manager_CGN_DW.obj_b.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_b.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_b.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_b.isInitialized = 1;
  Mission__Subscriber_setupImpl_b(&Mission_Manager_CGN_DW.obj_b);
  Mission_Manager_CGN_DW.obj_b.isSetupComplete = true;

  // Start for MATLABSystem: '<S208>/SinkBlock'
  Mission_Manager_CGN_DW.obj_j.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_j.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_j.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_j.isInitialized = 1;
  Mission__Publisher_setupImpl_be(&Mission_Manager_CGN_DW.obj_j);
  Mission_Manager_CGN_DW.obj_j.isSetupComplete = true;

  // Start for MATLABSystem: '<S207>/SinkBlock'
  Mission_Manager_CGN_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
  Mission_Manager_CGN_DW.obj_o.matlabCodegenIsDeleted = false;
  Mission_Manager_CGN_DW.obj_o.isSetupComplete = false;
  Mission_Manager_CGN_DW.obj_o.isInitialized = 1;
  Mission_M_Publisher_setupImpl_b(&Mission_Manager_CGN_DW.obj_o);
  Mission_Manager_CGN_DW.obj_o.isSetupComplete = true;
}

// Model terminate function
void Mission_Manager_CGN::terminate()
{
  // Terminate for MATLABSystem: '<S10>/SourceBlock'
  if (!Mission_Manager_CGN_DW.obj_m.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_m.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_m.isSetupComplete) {
      Sub_Mission_Manager_CGN_286_284.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S10>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S1>/Subsystem'
  // Terminate for MATLABSystem: '<S15>/SinkBlock'
  if (!Mission_Manager_CGN_DW.obj_op.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_op.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_op.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_op.isSetupComplete) {
      Pub_Mission_Manager_CGN_286_7.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S15>/SinkBlock'
  // End of Terminate for SubSystem: '<S1>/Subsystem'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!Mission_Manager_CGN_DW.obj_p.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_p.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_p.isSetupComplete) {
      Sub_Mission_Manager_CGN_293.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  if (!Mission_Manager_CGN_DW.obj.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj.isSetupComplete) {
      Sub_Mission_Manager_CGN_305.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S6>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!Mission_Manager_CGN_DW.obj_b.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_b.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_b.isSetupComplete) {
      Sub_Mission_Manager_CGN_288.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S208>/SinkBlock'
  if (!Mission_Manager_CGN_DW.obj_j.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_j.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_j.isSetupComplete) {
      Pub_Mission_Manager_CGN_323_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S208>/SinkBlock'

  // Terminate for MATLABSystem: '<S207>/SinkBlock'
  if (!Mission_Manager_CGN_DW.obj_o.matlabCodegenIsDeleted) {
    Mission_Manager_CGN_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((Mission_Manager_CGN_DW.obj_o.isInitialized == 1) &&
        Mission_Manager_CGN_DW.obj_o.isSetupComplete) {
      Pub_Mission_Manager_CGN_322_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S207>/SinkBlock'
}

// Constructor
Mission_Manager_CGN::Mission_Manager_CGN() :
  Mission_Manager_CGN_B(),
  Mission_Manager_CGN_DW(),
  Mission_Manager_CGN_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Mission_Manager_CGN::~Mission_Manager_CGN() = default;

// Real-Time Model get method
RT_MODEL_Mission_Manager_CGN_T * Mission_Manager_CGN::getRTM()
{
  return (&Mission_Manager_CGN_M);
}

const char_T* RT_MODEL_Mission_Manager_CGN_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_Mission_Manager_CGN_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
