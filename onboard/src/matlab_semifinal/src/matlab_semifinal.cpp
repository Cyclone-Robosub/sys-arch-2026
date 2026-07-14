//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_semifinal.cpp
//
// Code generated for Simulink model 'matlab_semifinal'.
//
// Model version                  : 1.15
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jul 14 08:59:23 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "matlab_semifinal.h"
#include "rtwtypes.h"
#include "matlab_semifinal_types.h"
#include <cmath>
#include "matlab_semifinal_private.h"
#include <cstring>
#include "rmw/qos_profiles.h"
#include <stddef.h>
#include "rt_defines.h"
#include "cmath"

static void rate_monotonic_scheduler(RT_MODEL_matlab_semifinal_T *const
  matlab_semifinal_M);

//
// Set which subrates need to run this base step (base rate always runs).
// This function must be called prior to calling the model step function
// in order to remember which rates need to run this base step.  The
// buffering of events allows for overlapping preemption.
//
void matlab_semifinal_SetEventsForThisBaseStep(boolean_T *eventFlags,
  RT_MODEL_matlab_semifinal_T *const matlab_semifinal_M)
{
  // Task runs when its counter is zero, computed via rtmStepTask macro
  eventFlags[1] = ((boolean_T)matlab_semifinal_M->StepTask(1));
}

//
//         This function updates active task flag for each subrate
//         and rate transition flags for tasks that exchange data.
//         The function assumes rate-monotonic multitasking scheduler.
//         The function must be called at model base rate so that
//         the generated code self-manages all its subrates and rate
//         transition flags.
//
static void rate_monotonic_scheduler(RT_MODEL_matlab_semifinal_T *const
  matlab_semifinal_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (matlab_semifinal_M->Timing.TaskCounters.TID[1])++;
  if ((matlab_semifinal_M->Timing.TaskCounters.TID[1]) > 49) {// Sample time: [0.5s, 0.0s] 
    matlab_semifinal_M->Timing.TaskCounters.TID[1] = 0;
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

// Function for MATLAB Function: '<S25>/quatToEul'
void matlab_semifinal::matlab_semifinal_wrapToPi(real_T *lambda)
{
  real_T q;
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
      q = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      q = (rtNaN);
    } else {
      q = std::abs((*lambda + 3.1415926535897931) / 6.2831853071795862);
      if (std::abs(q - std::floor(q + 0.5)) > 2.2204460492503131E-16 * q) {
        q = std::fmod(*lambda + 3.1415926535897931, 6.2831853071795862);
      } else {
        q = 0.0;
      }

      if (q == 0.0) {
        q = 0.0;
      } else if (q < 0.0) {
        q += 6.2831853071795862;
      }
    }
  }

  for (int32_T i{0}; i < trueCount; i++) {
    if ((q == 0.0) && (*lambda + 3.1415926535897931 > 0.0)) {
      q = 6.2831853071795862;
    }
  }

  if (tmp) {
    *lambda = q - 3.1415926535897931;
  }
}

//
// Output and update for atomic system:
//    '<S25>/quatToEul'
//    '<S25>/quatToEul1'
//
void matlab_semifinal::matlab_semifinal_quatToEul(const real_T rtu_qib_u[4],
  real_T rty_Eul_u[3], B_quatToEul_matlab_semifinal_T *localB)
{
  real_T a_tmp;
  real_T b_a;
  real_T psi;
  int32_T i;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  psi = rtu_qib_u[3] * rtu_qib_u[3] * 2.0 - 1.0;
  b_a = 2.0 * rtu_qib_u[3];
  for (i = 0; i < 3; i++) {
    a_tmp = 2.0 * rtu_qib_u[i];
    localB->a[3 * i] = a_tmp * rtu_qib_u[0] + psi * static_cast<real_T>(b[i]);
    localB->a[3 * i + 1] = static_cast<real_T>(b[i + 3]) * psi + a_tmp *
      rtu_qib_u[1];
    localB->a[3 * i + 2] = static_cast<real_T>(b[i + 6]) * psi + a_tmp *
      rtu_qib_u[2];
  }

  psi = b_a * 0.0;
  localB->b_a[0] = psi;
  localB->b_a[1] = b_a * -rtu_qib_u[2];
  localB->b_a[2] = b_a * rtu_qib_u[1];
  localB->b_a[3] = b_a * rtu_qib_u[2];
  localB->b_a[4] = psi;
  localB->b_a[5] = b_a * -rtu_qib_u[0];
  localB->b_a[6] = b_a * -rtu_qib_u[1];
  localB->b_a[7] = b_a * rtu_qib_u[0];
  localB->b_a[8] = psi;
  for (i = 0; i < 9; i++) {
    localB->Cbi[i] = localB->a[i] + localB->b_a[i];
  }

  b_a = std::asin(std::fmax(-1.0, std::fmin(1.0, localB->Cbi[6])));
  if (std::abs(std::cos(-b_a)) < 1.0E-6) {
    rty_Eul_u[0] = 0.0;
    psi = rt_atan2d_snf(-localB->Cbi[1], localB->Cbi[4]);
  } else {
    rty_Eul_u[0] = rt_atan2d_snf(localB->Cbi[7], localB->Cbi[8]);
    psi = rt_atan2d_snf(localB->Cbi[3], localB->Cbi[0]);
  }

  matlab_semifinal_wrapToPi(&rty_Eul_u[0]);
  rty_Eul_u[1] = -b_a;
  matlab_semifinal_wrapToPi(&rty_Eul_u[1]);
  matlab_semifinal_wrapToPi(&psi);
  rty_Eul_u[2] = psi;
}

real_T matlab_semifinal::matlab_semifinal_rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    if (u0 > 0.0) {
      matlab_semifinal_B.i1 = 1;
    } else {
      matlab_semifinal_B.i1 = -1;
    }

    if (u1 > 0.0) {
      matlab_semifinal_B.i2 = 1;
    } else {
      matlab_semifinal_B.i2 = -1;
    }

    y = std::atan2(static_cast<real_T>(matlab_semifinal_B.i1),
                   static_cast<real_T>(matlab_semifinal_B.i2));
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

// Function for MATLAB Function: '<S25>/guidanceLaw'
void matlab_semifinal::matlab_semifinal_wrapToPi_k(real_T *lambda)
{
  boolean_T tmp;
  matlab_semifinal_B.trueCount = 0;
  tmp = ((*lambda < -3.1415926535897931) || (*lambda > 3.1415926535897931));
  if (tmp) {
    for (matlab_semifinal_B.i_i = 0; matlab_semifinal_B.i_i < 1;
         matlab_semifinal_B.i_i++) {
      matlab_semifinal_B.trueCount++;
    }
  }

  if (matlab_semifinal_B.trueCount - 1 >= 0) {
    if (std::isnan(*lambda + 3.1415926535897931)) {
      matlab_semifinal_B.q_o = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      matlab_semifinal_B.q_o = (rtNaN);
    } else {
      matlab_semifinal_B.q_o = std::abs((*lambda + 3.1415926535897931) /
        6.2831853071795862);
      if (std::abs(matlab_semifinal_B.q_o - std::floor(matlab_semifinal_B.q_o +
            0.5)) > 2.2204460492503131E-16 * matlab_semifinal_B.q_o) {
        matlab_semifinal_B.q_o = std::fmod(*lambda + 3.1415926535897931,
          6.2831853071795862);
      } else {
        matlab_semifinal_B.q_o = 0.0;
      }

      if (matlab_semifinal_B.q_o == 0.0) {
        matlab_semifinal_B.q_o = 0.0;
      } else if (matlab_semifinal_B.q_o < 0.0) {
        matlab_semifinal_B.q_o += 6.2831853071795862;
      }
    }

    matlab_semifinal_B.varargin_1_data = matlab_semifinal_B.q_o;
  }

  for (matlab_semifinal_B.i_i = 0; matlab_semifinal_B.i_i <
       matlab_semifinal_B.trueCount; matlab_semifinal_B.i_i++) {
    matlab_semifinal_B.i_f = 0;
    if ((matlab_semifinal_B.varargin_1_data == 0.0) && (*lambda +
         3.1415926535897931 > 0.0)) {
      matlab_semifinal_B.varargin_1_data = 6.2831853071795862;
    }
  }

  if (tmp) {
    *lambda = matlab_semifinal_B.varargin_1_data - 3.1415926535897931;
  }
}

// Function for MATLAB Function: '<S26>/commandExecuter'
void matlab_semifinal::matlab_semifinal_eulToQuat_o(const real_T Eul[3], real_T
  qib[4])
{
  matlab_semifinal_B.eta_a = std::cos(Eul[1]);
  matlab_semifinal_B.scale_j = std::sin(Eul[1]);
  matlab_semifinal_B.b_t_o = std::cos(Eul[2]);
  matlab_semifinal_B.rotm_tmp_n = std::sin(Eul[2]);
  matlab_semifinal_B.eps_idx_1 = std::sin(Eul[0]);
  matlab_semifinal_B.rotm_tmp_i = std::cos(Eul[0]);
  matlab_semifinal_B.rotm_idx_0 = matlab_semifinal_B.eta_a *
    matlab_semifinal_B.b_t_o;
  matlab_semifinal_B.eps_idx_2 = matlab_semifinal_B.eta_a *
    matlab_semifinal_B.rotm_tmp_n;
  matlab_semifinal_B.rotm_idx_4_tmp = matlab_semifinal_B.eps_idx_1 *
    matlab_semifinal_B.scale_j;
  matlab_semifinal_B.eps_idx_0 = matlab_semifinal_B.rotm_idx_4_tmp *
    matlab_semifinal_B.rotm_tmp_n + matlab_semifinal_B.rotm_tmp_i *
    matlab_semifinal_B.b_t_o;
  matlab_semifinal_B.absxk_j = matlab_semifinal_B.eps_idx_1 *
    matlab_semifinal_B.eta_a;
  matlab_semifinal_B.rotm_idx_8 = matlab_semifinal_B.rotm_tmp_i *
    matlab_semifinal_B.eta_a;
  matlab_semifinal_B.eta_a = std::sqrt(((matlab_semifinal_B.rotm_idx_0 +
    matlab_semifinal_B.eps_idx_0) + matlab_semifinal_B.rotm_idx_8) + 1.0) / 2.0;
  if (matlab_semifinal_B.eta_a != 0.0) {
    matlab_semifinal_B.rotm_idx_0 = matlab_semifinal_B.rotm_tmp_i *
      matlab_semifinal_B.scale_j;
    matlab_semifinal_B.rotm_idx_8 = 4.0 * matlab_semifinal_B.eta_a;
    matlab_semifinal_B.eps_idx_0 = (matlab_semifinal_B.absxk_j -
      (matlab_semifinal_B.rotm_idx_0 * matlab_semifinal_B.rotm_tmp_n -
       matlab_semifinal_B.eps_idx_1 * matlab_semifinal_B.b_t_o)) /
      matlab_semifinal_B.rotm_idx_8;
    matlab_semifinal_B.eps_idx_1 = ((matlab_semifinal_B.rotm_idx_0 *
      matlab_semifinal_B.b_t_o + matlab_semifinal_B.eps_idx_1 *
      matlab_semifinal_B.rotm_tmp_n) - (-matlab_semifinal_B.scale_j)) /
      matlab_semifinal_B.rotm_idx_8;
    matlab_semifinal_B.eps_idx_2 = (matlab_semifinal_B.eps_idx_2 -
      (matlab_semifinal_B.rotm_idx_4_tmp * matlab_semifinal_B.b_t_o -
       matlab_semifinal_B.rotm_tmp_i * matlab_semifinal_B.rotm_tmp_n)) /
      matlab_semifinal_B.rotm_idx_8;
  } else {
    matlab_semifinal_B.b_t_o = (matlab_semifinal_B.rotm_idx_0 + 1.0) / 2.0;
    matlab_semifinal_B.x[0] = matlab_semifinal_B.b_t_o;
    matlab_semifinal_B.eps_idx_1 = (matlab_semifinal_B.eps_idx_0 + 1.0) / 2.0;
    matlab_semifinal_B.x[1] = matlab_semifinal_B.eps_idx_1;
    matlab_semifinal_B.rotm_tmp_n = (matlab_semifinal_B.rotm_idx_8 + 1.0) / 2.0;
    matlab_semifinal_B.x[2] = matlab_semifinal_B.rotm_tmp_n;
    if (!std::isnan(matlab_semifinal_B.b_t_o)) {
      matlab_semifinal_B.idx_i = 1;
    } else {
      boolean_T exitg1;
      matlab_semifinal_B.idx_i = 0;
      matlab_semifinal_B.b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (matlab_semifinal_B.b_k < 4)) {
        if (!std::isnan(matlab_semifinal_B.x[matlab_semifinal_B.b_k - 1])) {
          matlab_semifinal_B.idx_i = matlab_semifinal_B.b_k;
          exitg1 = true;
        } else {
          matlab_semifinal_B.b_k++;
        }
      }
    }

    if (matlab_semifinal_B.idx_i == 0) {
      matlab_semifinal_B.b_k = 1;
    } else {
      matlab_semifinal_B.eps_idx_0 =
        matlab_semifinal_B.x[matlab_semifinal_B.idx_i - 1];
      matlab_semifinal_B.b_k = matlab_semifinal_B.idx_i;
      for (matlab_semifinal_B.c_k = matlab_semifinal_B.idx_i + 1;
           matlab_semifinal_B.c_k < 4; matlab_semifinal_B.c_k++) {
        matlab_semifinal_B.rotm_tmp_i =
          matlab_semifinal_B.x[matlab_semifinal_B.c_k - 1];
        if (matlab_semifinal_B.eps_idx_0 < matlab_semifinal_B.rotm_tmp_i) {
          matlab_semifinal_B.eps_idx_0 = matlab_semifinal_B.rotm_tmp_i;
          matlab_semifinal_B.b_k = matlab_semifinal_B.c_k;
        }
      }
    }

    switch (matlab_semifinal_B.b_k) {
     case 1:
      matlab_semifinal_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_o));
      if (std::isnan(matlab_semifinal_B.eps_idx_2)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (matlab_semifinal_B.eps_idx_2 < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (matlab_semifinal_B.eps_idx_2 > 0.0);
      }

      matlab_semifinal_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1)) * matlab_semifinal_B.rotm_tmp_i;
      if (std::isnan(-matlab_semifinal_B.scale_j)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (-matlab_semifinal_B.scale_j < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (-matlab_semifinal_B.scale_j > 0.0);
      }

      matlab_semifinal_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_n)) * matlab_semifinal_B.rotm_tmp_i;
      break;

     case 2:
      matlab_semifinal_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1));
      if (std::isnan(matlab_semifinal_B.eps_idx_2)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (matlab_semifinal_B.eps_idx_2 < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (matlab_semifinal_B.eps_idx_2 > 0.0);
      }

      matlab_semifinal_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_o)) * matlab_semifinal_B.rotm_tmp_i;
      if (std::isnan(matlab_semifinal_B.absxk_j)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (matlab_semifinal_B.absxk_j < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (matlab_semifinal_B.absxk_j > 0.0);
      }

      matlab_semifinal_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_n)) * matlab_semifinal_B.rotm_tmp_i;
      break;

     default:
      matlab_semifinal_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_n));
      if (std::isnan(-matlab_semifinal_B.scale_j)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (-matlab_semifinal_B.scale_j < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (-matlab_semifinal_B.scale_j > 0.0);
      }

      matlab_semifinal_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_o)) * matlab_semifinal_B.rotm_tmp_i;
      if (std::isnan(matlab_semifinal_B.absxk_j)) {
        matlab_semifinal_B.rotm_tmp_i = (rtNaN);
      } else if (matlab_semifinal_B.absxk_j < 0.0) {
        matlab_semifinal_B.rotm_tmp_i = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_i = (matlab_semifinal_B.absxk_j > 0.0);
      }

      matlab_semifinal_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1)) * matlab_semifinal_B.rotm_tmp_i;
      break;
    }
  }

  matlab_semifinal_B.scale_j = 3.3121686421112381E-170;
  matlab_semifinal_B.absxk_j = std::abs(matlab_semifinal_B.eps_idx_0);
  if (matlab_semifinal_B.absxk_j > 3.3121686421112381E-170) {
    matlab_semifinal_B.rotm_tmp_n = 1.0;
    matlab_semifinal_B.scale_j = matlab_semifinal_B.absxk_j;
  } else {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.absxk_j /
      3.3121686421112381E-170;
    matlab_semifinal_B.rotm_tmp_n = matlab_semifinal_B.b_t_o *
      matlab_semifinal_B.b_t_o;
  }

  matlab_semifinal_B.absxk_j = std::abs(matlab_semifinal_B.eps_idx_1);
  if (matlab_semifinal_B.absxk_j > matlab_semifinal_B.scale_j) {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.scale_j /
      matlab_semifinal_B.absxk_j;
    matlab_semifinal_B.rotm_tmp_n = matlab_semifinal_B.rotm_tmp_n *
      matlab_semifinal_B.b_t_o * matlab_semifinal_B.b_t_o + 1.0;
    matlab_semifinal_B.scale_j = matlab_semifinal_B.absxk_j;
  } else {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.absxk_j /
      matlab_semifinal_B.scale_j;
    matlab_semifinal_B.rotm_tmp_n += matlab_semifinal_B.b_t_o *
      matlab_semifinal_B.b_t_o;
  }

  matlab_semifinal_B.absxk_j = std::abs(matlab_semifinal_B.eps_idx_2);
  if (matlab_semifinal_B.absxk_j > matlab_semifinal_B.scale_j) {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.scale_j /
      matlab_semifinal_B.absxk_j;
    matlab_semifinal_B.rotm_tmp_n = matlab_semifinal_B.rotm_tmp_n *
      matlab_semifinal_B.b_t_o * matlab_semifinal_B.b_t_o + 1.0;
    matlab_semifinal_B.scale_j = matlab_semifinal_B.absxk_j;
  } else {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.absxk_j /
      matlab_semifinal_B.scale_j;
    matlab_semifinal_B.rotm_tmp_n += matlab_semifinal_B.b_t_o *
      matlab_semifinal_B.b_t_o;
  }

  if (matlab_semifinal_B.eta_a > matlab_semifinal_B.scale_j) {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.scale_j /
      matlab_semifinal_B.eta_a;
    matlab_semifinal_B.rotm_tmp_n = matlab_semifinal_B.rotm_tmp_n *
      matlab_semifinal_B.b_t_o * matlab_semifinal_B.b_t_o + 1.0;
    matlab_semifinal_B.scale_j = matlab_semifinal_B.eta_a;
  } else {
    matlab_semifinal_B.b_t_o = matlab_semifinal_B.eta_a /
      matlab_semifinal_B.scale_j;
    matlab_semifinal_B.rotm_tmp_n += matlab_semifinal_B.b_t_o *
      matlab_semifinal_B.b_t_o;
  }

  matlab_semifinal_B.rotm_tmp_n = matlab_semifinal_B.scale_j * std::sqrt
    (matlab_semifinal_B.rotm_tmp_n);
  qib[0] = matlab_semifinal_B.eps_idx_0 / matlab_semifinal_B.rotm_tmp_n;
  qib[1] = matlab_semifinal_B.eps_idx_1 / matlab_semifinal_B.rotm_tmp_n;
  qib[2] = matlab_semifinal_B.eps_idx_2 / matlab_semifinal_B.rotm_tmp_n;
  qib[3] = matlab_semifinal_B.eta_a / matlab_semifinal_B.rotm_tmp_n;
}

// Function for MATLAB Function: '<S26>/commandExecuter'
boolean_T matlab_semifinal::matlab_semifinal_withinWPTol(const real_T X_Ri[3],
  const real_T X_qib[4], const real_T X_u[13], const real_T cmd_wp_tol[6])
{
  boolean_T tf;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  boolean_T exitg1;
  matlab_semifinal_B.qe_matlab_idx_0 = ((X_qib[3] * X_u[6] - -X_qib[0] * X_u[3])
    - -X_qib[1] * X_u[4]) - -X_qib[2] * X_u[5];
  matlab_semifinal_B.qe_matlab_idx_1 = (X_qib[3] * X_u[3] + X_u[6] * -X_qib[0])
    + (-X_qib[1] * X_u[5] - X_u[4] * -X_qib[2]);
  matlab_semifinal_B.qe_matlab_idx_2 = (X_qib[3] * X_u[4] + X_u[6] * -X_qib[1])
    + (X_u[3] * -X_qib[2] - -X_qib[0] * X_u[5]);
  matlab_semifinal_B.qe_matlab_idx_3 = (X_qib[3] * X_u[5] + X_u[6] * -X_qib[2])
    + (-X_qib[0] * X_u[4] - X_u[3] * -X_qib[1]);
  matlab_semifinal_B.qinv_m[0] = matlab_semifinal_B.qe_matlab_idx_1;
  matlab_semifinal_B.qinv_m[1] = matlab_semifinal_B.qe_matlab_idx_2;
  matlab_semifinal_B.qinv_m[2] = matlab_semifinal_B.qe_matlab_idx_3;
  matlab_semifinal_B.qinv_m[3] = matlab_semifinal_B.qe_matlab_idx_0;
  if (matlab_semifinal_B.qe_matlab_idx_0 < 0.0) {
    matlab_semifinal_B.qinv_m[0] = -matlab_semifinal_B.qe_matlab_idx_1;
    matlab_semifinal_B.qinv_m[1] = -matlab_semifinal_B.qe_matlab_idx_2;
    matlab_semifinal_B.qinv_m[2] = -matlab_semifinal_B.qe_matlab_idx_3;
    matlab_semifinal_B.qinv_m[3] = -matlab_semifinal_B.qe_matlab_idx_0;
  }

  matlab_semifinal_B.qe_matlab_idx_1 = matlab_semifinal_B.qinv_m[3] *
    matlab_semifinal_B.qinv_m[3] * 2.0 - 1.0;
  matlab_semifinal_B.qe_matlab_idx_0 = 2.0 * matlab_semifinal_B.qinv_m[3];
  for (matlab_semifinal_B.c_k_f = 0; matlab_semifinal_B.c_k_f < 3;
       matlab_semifinal_B.c_k_f++) {
    matlab_semifinal_B.qe_matlab_idx_2 = 2.0 *
      matlab_semifinal_B.qinv_m[matlab_semifinal_B.c_k_f];
    matlab_semifinal_B.a[3 * matlab_semifinal_B.c_k_f] =
      matlab_semifinal_B.qe_matlab_idx_2 * matlab_semifinal_B.qinv_m[0] +
      matlab_semifinal_B.qe_matlab_idx_1 * static_cast<real_T>
      (b[matlab_semifinal_B.c_k_f]);
    matlab_semifinal_B.a[3 * matlab_semifinal_B.c_k_f + 1] = static_cast<real_T>
      (b[matlab_semifinal_B.c_k_f + 3]) * matlab_semifinal_B.qe_matlab_idx_1 +
      matlab_semifinal_B.qe_matlab_idx_2 * matlab_semifinal_B.qinv_m[1];
    matlab_semifinal_B.a[3 * matlab_semifinal_B.c_k_f + 2] = static_cast<real_T>
      (b[matlab_semifinal_B.c_k_f + 6]) * matlab_semifinal_B.qe_matlab_idx_1 +
      matlab_semifinal_B.qe_matlab_idx_2 * matlab_semifinal_B.qinv_m[2];
  }

  matlab_semifinal_B.qe_matlab_idx_1 = matlab_semifinal_B.qe_matlab_idx_0 * 0.0;
  matlab_semifinal_B.b_a[0] = matlab_semifinal_B.qe_matlab_idx_1;
  matlab_semifinal_B.b_a[1] = matlab_semifinal_B.qe_matlab_idx_0 *
    -matlab_semifinal_B.qinv_m[2];
  matlab_semifinal_B.b_a[2] = matlab_semifinal_B.qe_matlab_idx_0 *
    matlab_semifinal_B.qinv_m[1];
  matlab_semifinal_B.b_a[3] = matlab_semifinal_B.qe_matlab_idx_0 *
    matlab_semifinal_B.qinv_m[2];
  matlab_semifinal_B.b_a[4] = matlab_semifinal_B.qe_matlab_idx_1;
  matlab_semifinal_B.b_a[5] = matlab_semifinal_B.qe_matlab_idx_0 *
    -matlab_semifinal_B.qinv_m[0];
  matlab_semifinal_B.b_a[6] = matlab_semifinal_B.qe_matlab_idx_0 *
    -matlab_semifinal_B.qinv_m[1];
  matlab_semifinal_B.b_a[7] = matlab_semifinal_B.qe_matlab_idx_0 *
    matlab_semifinal_B.qinv_m[0];
  matlab_semifinal_B.b_a[8] = matlab_semifinal_B.qe_matlab_idx_1;
  for (matlab_semifinal_B.c_k_f = 0; matlab_semifinal_B.c_k_f < 9;
       matlab_semifinal_B.c_k_f++) {
    matlab_semifinal_B.Cbi_p[matlab_semifinal_B.c_k_f] =
      matlab_semifinal_B.a[matlab_semifinal_B.c_k_f] +
      matlab_semifinal_B.b_a[matlab_semifinal_B.c_k_f];
  }

  matlab_semifinal_B.qe_matlab_idx_2 = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_semifinal_B.Cbi_p[6])));
  if (std::abs(std::cos(-matlab_semifinal_B.qe_matlab_idx_2)) < 1.0E-6) {
    matlab_semifinal_B.qe_matlab_idx_0 = 0.0;
    matlab_semifinal_B.qe_matlab_idx_1 = matlab_semifinal_rt_atan2d_snf
      (-matlab_semifinal_B.Cbi_p[1], matlab_semifinal_B.Cbi_p[4]);
  } else {
    matlab_semifinal_B.qe_matlab_idx_0 = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi_p[7], matlab_semifinal_B.Cbi_p[8]);
    matlab_semifinal_B.qe_matlab_idx_1 = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi_p[3], matlab_semifinal_B.Cbi_p[0]);
  }

  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.qe_matlab_idx_0);
  matlab_semifinal_B.qe_matlab_idx_2 = -matlab_semifinal_B.qe_matlab_idx_2;
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.qe_matlab_idx_2);
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.qe_matlab_idx_1);
  matlab_semifinal_B.R_error[0] = std::abs(X_Ri[0] - X_u[0]);
  matlab_semifinal_B.R_error[3] = std::abs(matlab_semifinal_B.qe_matlab_idx_0);
  matlab_semifinal_B.R_error[1] = std::abs(X_Ri[1] - X_u[1]);
  matlab_semifinal_B.R_error[4] = std::abs(matlab_semifinal_B.qe_matlab_idx_2);
  matlab_semifinal_B.R_error[2] = std::abs(X_Ri[2] - X_u[2]);
  matlab_semifinal_B.R_error[5] = std::abs(matlab_semifinal_B.qe_matlab_idx_1);
  for (matlab_semifinal_B.c_k_f = 0; matlab_semifinal_B.c_k_f < 6;
       matlab_semifinal_B.c_k_f++) {
    matlab_semifinal_B.b_x[matlab_semifinal_B.c_k_f] =
      (matlab_semifinal_B.R_error[matlab_semifinal_B.c_k_f] <
       cmd_wp_tol[matlab_semifinal_B.c_k_f]);
  }

  tf = true;
  matlab_semifinal_B.c_k_f = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.c_k_f < 6)) {
    if (!matlab_semifinal_B.b_x[matlab_semifinal_B.c_k_f]) {
      tf = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.c_k_f++;
    }
  }

  return tf;
}

// Function for MATLAB Function: '<S26>/commandExecuter'
void matlab_semifinal::matlab_sem_executeDurationTrick(real_T cmd_hold_time,
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

  static const char_T sb[16]{ 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a', 'r', 'd',
    '_', '_', '_', '_', '_', '_' };

  static const char_T tb[16]{ 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w', 'a', 'r',
    'd', '_', '_', '_', '_', '_' };

  static const char_T ub[16]{ 'f', 'f', '_', 'u', 'p', '_', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T vb[16]{ 'f', 'f', '_', 'd', 'o', 'w', 'n', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T wb[16]{ 'f', 'f', '_', 'r', 'i', 'g', 'h', 't', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T xb[16]{ 'f', 'f', '_', 'l', 'e', 'f', 't', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T yb[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'U', 'p',
    '_', '_', '_', '_', '_', '_' };

  static const char_T ac[16]{ 'f', 'f', '_', 'p', 'i', 't', 'c', 'h', 'D', 'o',
    'w', 'n', '_', '_', '_', '_' };

  static const char_T bc[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i', 'g', 'h',
    't', '_', '_', '_', '_', '_' };

  static const char_T cc[16]{ 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e', 'f', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T dc[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R', 'i', 'g',
    'h', 't', '_', '_', '_', '_' };

  static const char_T ec[16]{ 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L', 'e', 'f',
    't', '_', '_', '_', '_', '_' };

  static const char_T fc[16]{ 'f', 'f', '_', 's', 't', 'o', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T gc[16]{ 'd', 'r', 'o', 'p', 'p', 'e', 'r', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T hc[16]{ 'r', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T ic[16]{ 'r', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w',
    'a', 'r', 'd', '_', '_', '_' };

  static const char_T jc[16]{ 'r', 's', 'f', 'f', '_', 'u', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T kc[16]{ 'r', 's', 'f', 'f', '_', 'd', 'o', 'w', 'n', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T lc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'i', 'g', 'h', 't',
    '_', '_', '_', '_', '_', '_' };

  static const char_T mc[16]{ 'r', 's', 'f', 'f', '_', 'l', 'e', 'f', 't', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T nc[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'U', 'p', '_', '_', '_', '_' };

  static const char_T oc[16]{ 'r', 's', 'f', 'f', '_', 'p', 'i', 't', 'c', 'h',
    'D', 'o', 'w', 'n', '_', '_' };

  static const char_T pc[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'R', 'i',
    'g', 'h', 't', '_', '_', '_' };

  static const char_T qc[16]{ 'r', 's', 'f', 'f', '_', 'y', 'a', 'w', 'L', 'e',
    'f', 't', '_', '_', '_', '_' };

  static const char_T rc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  static const char_T sc[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  static const char_T tc[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
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

  static const char_T uc[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 16;
       matlab_semifinal_B.c_ret++) {
    matlab_semifinal_B.b.f1[matlab_semifinal_B.c_ret] =
      sb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.c.f1[matlab_semifinal_B.c_ret] =
      tb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.d.f1[matlab_semifinal_B.c_ret] =
      ub[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.e.f1[matlab_semifinal_B.c_ret] =
      vb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.f.f1[matlab_semifinal_B.c_ret] =
      wb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.g.f1[matlab_semifinal_B.c_ret] =
      xb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.h.f1[matlab_semifinal_B.c_ret] =
      yb[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.i.f1[matlab_semifinal_B.c_ret] =
      ac[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.j.f1[matlab_semifinal_B.c_ret] =
      bc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.k.f1[matlab_semifinal_B.c_ret] =
      cc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.l.f1[matlab_semifinal_B.c_ret] =
      dc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.m.f1[matlab_semifinal_B.c_ret] =
      ec[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.n.f1[matlab_semifinal_B.c_ret] =
      fc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.o.f1[matlab_semifinal_B.c_ret] =
      gc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.p.f1[matlab_semifinal_B.c_ret] =
      hc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.q.f1[matlab_semifinal_B.c_ret] =
      ic[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.r.f1[matlab_semifinal_B.c_ret] =
      jc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.s_d.f1[matlab_semifinal_B.c_ret] =
      kc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.u.f1[matlab_semifinal_B.c_ret] =
      lc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.v.f1[matlab_semifinal_B.c_ret] =
      mc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.w.f1[matlab_semifinal_B.c_ret] =
      nc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.x_d.f1[matlab_semifinal_B.c_ret] =
      oc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.y.f1[matlab_semifinal_B.c_ret] =
      pc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.ab.f1[matlab_semifinal_B.c_ret] =
      qc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.bb.f1[matlab_semifinal_B.c_ret] =
      rc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.cb.f1[matlab_semifinal_B.c_ret] =
      sc[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.db.f1[matlab_semifinal_B.c_ret] =
      tc[matlab_semifinal_B.c_ret];
  }

  matlab_semifinal_B.varargin_1[0] = matlab_semifinal_B.b;
  matlab_semifinal_B.varargin_1[1] = matlab_semifinal_B.c;
  matlab_semifinal_B.varargin_1[2] = matlab_semifinal_B.d;
  matlab_semifinal_B.varargin_1[3] = matlab_semifinal_B.e;
  matlab_semifinal_B.varargin_1[4] = matlab_semifinal_B.f;
  matlab_semifinal_B.varargin_1[5] = matlab_semifinal_B.g;
  matlab_semifinal_B.varargin_1[6] = matlab_semifinal_B.h;
  matlab_semifinal_B.varargin_1[7] = matlab_semifinal_B.i;
  matlab_semifinal_B.varargin_1[8] = matlab_semifinal_B.j;
  matlab_semifinal_B.varargin_1[9] = matlab_semifinal_B.k;
  matlab_semifinal_B.varargin_1[10] = matlab_semifinal_B.l;
  matlab_semifinal_B.varargin_1[11] = matlab_semifinal_B.m;
  matlab_semifinal_B.varargin_1[12] = matlab_semifinal_B.n;
  matlab_semifinal_B.varargin_1[13] = matlab_semifinal_B.o;
  matlab_semifinal_B.varargin_2[0] = matlab_semifinal_B.p;
  matlab_semifinal_B.varargin_2[1] = matlab_semifinal_B.q;
  matlab_semifinal_B.varargin_2[2] = matlab_semifinal_B.r;
  matlab_semifinal_B.varargin_2[3] = matlab_semifinal_B.s_d;
  matlab_semifinal_B.varargin_2[4] = matlab_semifinal_B.u;
  matlab_semifinal_B.varargin_2[5] = matlab_semifinal_B.v;
  matlab_semifinal_B.varargin_2[6] = matlab_semifinal_B.w;
  matlab_semifinal_B.varargin_2[7] = matlab_semifinal_B.x_d;
  matlab_semifinal_B.varargin_2[8] = matlab_semifinal_B.y;
  matlab_semifinal_B.varargin_2[9] = matlab_semifinal_B.ab;
  matlab_semifinal_B.varargin_2[10] = matlab_semifinal_B.bb;
  matlab_semifinal_B.varargin_2[11] = matlab_semifinal_B.cb;
  matlab_semifinal_B.varargin_2[12] = matlab_semifinal_B.db;
  for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 16;
       matlab_semifinal_B.c_ret++) {
    matlab_semifinal_B.b.f1[matlab_semifinal_B.c_ret] =
      n_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.c.f1[matlab_semifinal_B.c_ret] =
      o_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.d.f1[matlab_semifinal_B.c_ret] =
      p_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.e.f1[matlab_semifinal_B.c_ret] =
      q_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.f.f1[matlab_semifinal_B.c_ret] =
      r_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.g.f1[matlab_semifinal_B.c_ret] =
      s_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.h.f1[matlab_semifinal_B.c_ret] =
      t_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.i.f1[matlab_semifinal_B.c_ret] =
      u_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.j.f1[matlab_semifinal_B.c_ret] =
      v_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.k.f1[matlab_semifinal_B.c_ret] =
      w_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.l.f1[matlab_semifinal_B.c_ret] =
      x_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.m.f1[matlab_semifinal_B.c_ret] =
      y_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.n.f1[matlab_semifinal_B.c_ret] =
      ab_a[matlab_semifinal_B.c_ret];
    matlab_semifinal_B.o.f1[matlab_semifinal_B.c_ret] =
      uc[matlab_semifinal_B.c_ret];
  }

  matlab_semifinal_B.varargin_3[0] = matlab_semifinal_B.b;
  matlab_semifinal_B.varargin_3[1] = matlab_semifinal_B.c;
  matlab_semifinal_B.varargin_3[2] = matlab_semifinal_B.d;
  matlab_semifinal_B.varargin_3[3] = matlab_semifinal_B.e;
  matlab_semifinal_B.varargin_3[4] = matlab_semifinal_B.f;
  matlab_semifinal_B.varargin_3[5] = matlab_semifinal_B.g;
  matlab_semifinal_B.varargin_3[6] = matlab_semifinal_B.h;
  matlab_semifinal_B.varargin_3[7] = matlab_semifinal_B.i;
  matlab_semifinal_B.varargin_3[8] = matlab_semifinal_B.j;
  matlab_semifinal_B.varargin_3[9] = matlab_semifinal_B.k;
  matlab_semifinal_B.varargin_3[10] = matlab_semifinal_B.l;
  matlab_semifinal_B.varargin_3[11] = matlab_semifinal_B.m;
  matlab_semifinal_B.varargin_3[12] = matlab_semifinal_B.n;
  for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 16;
       matlab_semifinal_B.c_ret++) {
    matlab_semifinal_B.switch_expression[matlab_semifinal_B.c_ret] =
      cmd_trick_id[matlab_semifinal_B.c_ret];
  }

  matlab_semifinal_B.c_ret = 0;
  do {
    exitg3 = 0;
    if (matlab_semifinal_B.c_ret < 14) {
      matlab_semifinal_B.d_ret = std::memcmp
        (&matlab_semifinal_B.varargin_1[matlab_semifinal_B.c_ret].f1[0],
         &matlab_semifinal_B.switch_expression[0], 16);
      if (matlab_semifinal_B.d_ret == 0) {
        matlab_semifinal_B.c_ret = 0;
        exitg3 = 1;
      } else {
        matlab_semifinal_B.c_ret++;
      }
    } else {
      matlab_semifinal_B.c_ret = 0;
      exitg3 = 2;
    }
  } while (exitg3 == 0);

  if (exitg3 == 1) {
  } else {
    do {
      exitg2 = 0;
      if (matlab_semifinal_B.c_ret < 13) {
        matlab_semifinal_B.d_ret = std::memcmp
          (&matlab_semifinal_B.varargin_2[matlab_semifinal_B.c_ret].f1[0],
           &matlab_semifinal_B.switch_expression[0], 16);
        if (matlab_semifinal_B.d_ret == 0) {
          matlab_semifinal_B.c_ret = 1;
          exitg2 = 1;
        } else {
          matlab_semifinal_B.c_ret++;
        }
      } else {
        matlab_semifinal_B.c_ret = 0;
        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (matlab_semifinal_B.c_ret < 13) {
          matlab_semifinal_B.d_ret = std::memcmp
            (&matlab_semifinal_B.varargin_3[matlab_semifinal_B.c_ret].f1[0],
             &matlab_semifinal_B.switch_expression[0], 16);
          if (matlab_semifinal_B.d_ret == 0) {
            matlab_semifinal_B.c_ret = 2;
            exitg1 = 1;
          } else {
            matlab_semifinal_B.c_ret++;
          }
        } else {
          matlab_semifinal_B.c_ret = std::memcmp(&matlab_semifinal_B.o.f1[0],
            &matlab_semifinal_B.switch_expression[0], 16);
          if (matlab_semifinal_B.c_ret == 0) {
            matlab_semifinal_B.c_ret = 3;
          } else {
            matlab_semifinal_B.c_ret = -1;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  switch (matlab_semifinal_B.c_ret) {
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

    for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 6;
         matlab_semifinal_B.c_ret++) {
      cmd_specific_wp[matlab_semifinal_B.c_ret] =
        idle_wp[matlab_semifinal_B.c_ret];
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

    for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 6;
         matlab_semifinal_B.c_ret++) {
      cmd_specific_wp[matlab_semifinal_B.c_ret] =
        idle_wp[matlab_semifinal_B.c_ret];
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

    matlab_semifinal_B.c_ret = std::memcmp(&a[0],
      &matlab_semifinal_B.switch_expression[0], 16);
    if (matlab_semifinal_B.c_ret == 0) {
      matlab_semifinal_B.c_ret = 0;
    } else {
      matlab_semifinal_B.c_ret = std::memcmp(&b_a[0],
        &matlab_semifinal_B.switch_expression[0], 16);
      if (matlab_semifinal_B.c_ret == 0) {
        matlab_semifinal_B.c_ret = 1;
      } else {
        matlab_semifinal_B.c_ret = std::memcmp(&c_a[0],
          &matlab_semifinal_B.switch_expression[0], 16);
        if (matlab_semifinal_B.c_ret == 0) {
          matlab_semifinal_B.c_ret = 2;
        } else {
          matlab_semifinal_B.c_ret = std::memcmp(&d_a[0],
            &matlab_semifinal_B.switch_expression[0], 16);
          if (matlab_semifinal_B.c_ret == 0) {
            matlab_semifinal_B.c_ret = 3;
          } else {
            matlab_semifinal_B.c_ret = std::memcmp(&e_a[0],
              &matlab_semifinal_B.switch_expression[0], 16);
            if (matlab_semifinal_B.c_ret == 0) {
              matlab_semifinal_B.c_ret = 4;
            } else {
              matlab_semifinal_B.c_ret = std::memcmp(&f_a[0],
                &matlab_semifinal_B.switch_expression[0], 16);
              if (matlab_semifinal_B.c_ret == 0) {
                matlab_semifinal_B.c_ret = 5;
              } else {
                matlab_semifinal_B.c_ret = std::memcmp(&g_a[0],
                  &matlab_semifinal_B.switch_expression[0], 16);
                if (matlab_semifinal_B.c_ret == 0) {
                  matlab_semifinal_B.c_ret = 6;
                } else {
                  matlab_semifinal_B.c_ret = std::memcmp(&h_a[0],
                    &matlab_semifinal_B.switch_expression[0], 16);
                  if (matlab_semifinal_B.c_ret == 0) {
                    matlab_semifinal_B.c_ret = 7;
                  } else {
                    matlab_semifinal_B.c_ret = std::memcmp(&i_a[0],
                      &matlab_semifinal_B.switch_expression[0], 16);
                    if (matlab_semifinal_B.c_ret == 0) {
                      matlab_semifinal_B.c_ret = 8;
                    } else {
                      matlab_semifinal_B.c_ret = std::memcmp(&j_a[0],
                        &matlab_semifinal_B.switch_expression[0], 16);
                      if (matlab_semifinal_B.c_ret == 0) {
                        matlab_semifinal_B.c_ret = 9;
                      } else {
                        matlab_semifinal_B.c_ret = std::memcmp(&k_a[0],
                          &matlab_semifinal_B.switch_expression[0], 16);
                        if (matlab_semifinal_B.c_ret == 0) {
                          matlab_semifinal_B.c_ret = 10;
                        } else {
                          matlab_semifinal_B.c_ret = std::memcmp(&l_a[0],
                            &matlab_semifinal_B.switch_expression[0], 16);
                          if (matlab_semifinal_B.c_ret == 0) {
                            matlab_semifinal_B.c_ret = 11;
                          } else {
                            matlab_semifinal_B.c_ret = std::memcmp(&m_a[0],
                              &matlab_semifinal_B.switch_expression[0], 16);
                            if (matlab_semifinal_B.c_ret == 0) {
                              matlab_semifinal_B.c_ret = 12;
                            } else {
                              matlab_semifinal_B.c_ret = -1;
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

    switch (matlab_semifinal_B.c_ret) {
     case 0:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * 0.0 +
              X_Cib[matlab_semifinal_B.c_ret] * 1000.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * 0.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 1:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * 0.0 +
              X_Cib[matlab_semifinal_B.c_ret] * -1000.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * 0.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 2:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * 1000.0 +
              X_Cib[matlab_semifinal_B.c_ret] * 0.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * 0.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 3:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * -1000.0 +
              X_Cib[matlab_semifinal_B.c_ret] * 0.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * 0.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 4:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * 0.0 +
              X_Cib[matlab_semifinal_B.c_ret] * 0.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * -1000.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 5:
      if (new_cmd_reset) {
        for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
             matlab_semifinal_B.c_ret++) {
          cmd_specific_wp[matlab_semifinal_B.c_ret] =
            ((X_Cib[matlab_semifinal_B.c_ret + 3] * 0.0 +
              X_Cib[matlab_semifinal_B.c_ret] * 0.0) +
             X_Cib[matlab_semifinal_B.c_ret + 6] * 1000.0) +
            X_Ri[matlab_semifinal_B.c_ret];
        }
      }

      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 6:
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 7:
      cmd_specific_wp[5] = X_Eul[2] + 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 8:
      cmd_specific_wp[5] = X_Eul[2] - 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 9:
      cmd_specific_wp[5] = X_Eul[0] + 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 10:
      cmd_specific_wp[5] = X_Eul[0] - 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 11:
      cmd_specific_wp[5] = X_Eul[1] + 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 12:
      cmd_specific_wp[5] = X_Eul[1] - 0.52359877559829882;
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     default:
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
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
      matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = matlab_semifinal_B.dv2[0];
      X_u[4] = matlab_semifinal_B.dv2[1];
      X_u[5] = matlab_semifinal_B.dv2[2];
      X_u[6] = matlab_semifinal_B.dv2[3];
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
      for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 3;
           matlab_semifinal_B.c_ret++) {
        cmd_specific_wp[matlab_semifinal_B.c_ret] =
          ((X_Cib[matlab_semifinal_B.c_ret + 3] * 0.0 +
            X_Cib[matlab_semifinal_B.c_ret] * 1000.0) +
           X_Cib[matlab_semifinal_B.c_ret + 6] * 0.0) +
          X_Ri[matlab_semifinal_B.c_ret];
      }
    }

    matlab_semifinal_eulToQuat_o(&cmd_specific_wp[3], matlab_semifinal_B.dv2);
    X_u[0] = cmd_specific_wp[0];
    X_u[1] = cmd_specific_wp[1];
    X_u[2] = cmd_specific_wp[2];
    X_u[3] = matlab_semifinal_B.dv2[0];
    X_u[4] = matlab_semifinal_B.dv2[1];
    X_u[5] = matlab_semifinal_B.dv2[2];
    X_u[6] = matlab_semifinal_B.dv2[3];
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
    for (matlab_semifinal_B.c_ret = 0; matlab_semifinal_B.c_ret < 6;
         matlab_semifinal_B.c_ret++) {
      cmd_specific_wp[matlab_semifinal_B.c_ret] =
        idle_wp[matlab_semifinal_B.c_ret];
    }
    break;
  }
}

// Function for MATLAB Function: '<S25>/guidanceLaw'
real_T matlab_semifinal::matlab_semifinal_norm(const real_T x[2])
{
  real_T y;
  matlab_semifinal_B.scale_e = 3.3121686421112381E-170;
  matlab_semifinal_B.absxk_a = std::abs(x[0]);
  if (matlab_semifinal_B.absxk_a > 3.3121686421112381E-170) {
    y = 1.0;
    matlab_semifinal_B.scale_e = matlab_semifinal_B.absxk_a;
  } else {
    matlab_semifinal_B.t_a = matlab_semifinal_B.absxk_a /
      3.3121686421112381E-170;
    y = matlab_semifinal_B.t_a * matlab_semifinal_B.t_a;
  }

  matlab_semifinal_B.absxk_a = std::abs(x[1]);
  if (matlab_semifinal_B.absxk_a > matlab_semifinal_B.scale_e) {
    matlab_semifinal_B.t_a = matlab_semifinal_B.scale_e /
      matlab_semifinal_B.absxk_a;
    y = y * matlab_semifinal_B.t_a * matlab_semifinal_B.t_a + 1.0;
    matlab_semifinal_B.scale_e = matlab_semifinal_B.absxk_a;
  } else {
    matlab_semifinal_B.t_a = matlab_semifinal_B.absxk_a /
      matlab_semifinal_B.scale_e;
    y += matlab_semifinal_B.t_a * matlab_semifinal_B.t_a;
  }

  return matlab_semifinal_B.scale_e * std::sqrt(y);
}

// Function for MATLAB Function: '<S25>/quatInjector'
void matlab_semifinal::matlab_semifinal_eulToQuat(const real_T Eul[3], real_T
  qib[4])
{
  matlab_semifinal_B.eta_n = std::cos(Eul[1]);
  matlab_semifinal_B.scale_m = std::sin(Eul[1]);
  matlab_semifinal_B.b_t_m = std::cos(Eul[2]);
  matlab_semifinal_B.rotm_tmp_m = std::sin(Eul[2]);
  matlab_semifinal_B.eps_idx_1_c = std::sin(Eul[0]);
  matlab_semifinal_B.rotm_tmp_j = std::cos(Eul[0]);
  matlab_semifinal_B.rotm_idx_0_p = matlab_semifinal_B.eta_n *
    matlab_semifinal_B.b_t_m;
  matlab_semifinal_B.eps_idx_2_c = matlab_semifinal_B.eta_n *
    matlab_semifinal_B.rotm_tmp_m;
  matlab_semifinal_B.rotm_idx_4_tmp_a = matlab_semifinal_B.eps_idx_1_c *
    matlab_semifinal_B.scale_m;
  matlab_semifinal_B.eps_idx_0_h = matlab_semifinal_B.rotm_idx_4_tmp_a *
    matlab_semifinal_B.rotm_tmp_m + matlab_semifinal_B.rotm_tmp_j *
    matlab_semifinal_B.b_t_m;
  matlab_semifinal_B.absxk_c = matlab_semifinal_B.eps_idx_1_c *
    matlab_semifinal_B.eta_n;
  matlab_semifinal_B.rotm_idx_8_p = matlab_semifinal_B.rotm_tmp_j *
    matlab_semifinal_B.eta_n;
  matlab_semifinal_B.eta_n = std::sqrt(((matlab_semifinal_B.rotm_idx_0_p +
    matlab_semifinal_B.eps_idx_0_h) + matlab_semifinal_B.rotm_idx_8_p) + 1.0) /
    2.0;
  if (matlab_semifinal_B.eta_n != 0.0) {
    matlab_semifinal_B.rotm_idx_0_p = matlab_semifinal_B.rotm_tmp_j *
      matlab_semifinal_B.scale_m;
    matlab_semifinal_B.rotm_idx_8_p = 4.0 * matlab_semifinal_B.eta_n;
    matlab_semifinal_B.eps_idx_0_h = (matlab_semifinal_B.absxk_c -
      (matlab_semifinal_B.rotm_idx_0_p * matlab_semifinal_B.rotm_tmp_m -
       matlab_semifinal_B.eps_idx_1_c * matlab_semifinal_B.b_t_m)) /
      matlab_semifinal_B.rotm_idx_8_p;
    matlab_semifinal_B.eps_idx_1_c = ((matlab_semifinal_B.rotm_idx_0_p *
      matlab_semifinal_B.b_t_m + matlab_semifinal_B.eps_idx_1_c *
      matlab_semifinal_B.rotm_tmp_m) - (-matlab_semifinal_B.scale_m)) /
      matlab_semifinal_B.rotm_idx_8_p;
    matlab_semifinal_B.eps_idx_2_c = (matlab_semifinal_B.eps_idx_2_c -
      (matlab_semifinal_B.rotm_idx_4_tmp_a * matlab_semifinal_B.b_t_m -
       matlab_semifinal_B.rotm_tmp_j * matlab_semifinal_B.rotm_tmp_m)) /
      matlab_semifinal_B.rotm_idx_8_p;
  } else {
    matlab_semifinal_B.b_t_m = (matlab_semifinal_B.rotm_idx_0_p + 1.0) / 2.0;
    matlab_semifinal_B.x_j[0] = matlab_semifinal_B.b_t_m;
    matlab_semifinal_B.eps_idx_1_c = (matlab_semifinal_B.eps_idx_0_h + 1.0) /
      2.0;
    matlab_semifinal_B.x_j[1] = matlab_semifinal_B.eps_idx_1_c;
    matlab_semifinal_B.rotm_tmp_m = (matlab_semifinal_B.rotm_idx_8_p + 1.0) /
      2.0;
    matlab_semifinal_B.x_j[2] = matlab_semifinal_B.rotm_tmp_m;
    if (!std::isnan(matlab_semifinal_B.b_t_m)) {
      matlab_semifinal_B.idx_g = 1;
    } else {
      boolean_T exitg1;
      matlab_semifinal_B.idx_g = 0;
      matlab_semifinal_B.b_k_c = 2;
      exitg1 = false;
      while ((!exitg1) && (matlab_semifinal_B.b_k_c < 4)) {
        if (!std::isnan(matlab_semifinal_B.x_j[matlab_semifinal_B.b_k_c - 1])) {
          matlab_semifinal_B.idx_g = matlab_semifinal_B.b_k_c;
          exitg1 = true;
        } else {
          matlab_semifinal_B.b_k_c++;
        }
      }
    }

    if (matlab_semifinal_B.idx_g == 0) {
      matlab_semifinal_B.b_k_c = 1;
    } else {
      matlab_semifinal_B.eps_idx_0_h =
        matlab_semifinal_B.x_j[matlab_semifinal_B.idx_g - 1];
      matlab_semifinal_B.b_k_c = matlab_semifinal_B.idx_g;
      for (matlab_semifinal_B.c_k_o = matlab_semifinal_B.idx_g + 1;
           matlab_semifinal_B.c_k_o < 4; matlab_semifinal_B.c_k_o++) {
        matlab_semifinal_B.rotm_tmp_j =
          matlab_semifinal_B.x_j[matlab_semifinal_B.c_k_o - 1];
        if (matlab_semifinal_B.eps_idx_0_h < matlab_semifinal_B.rotm_tmp_j) {
          matlab_semifinal_B.eps_idx_0_h = matlab_semifinal_B.rotm_tmp_j;
          matlab_semifinal_B.b_k_c = matlab_semifinal_B.c_k_o;
        }
      }
    }

    switch (matlab_semifinal_B.b_k_c) {
     case 1:
      matlab_semifinal_B.eps_idx_0_h = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_m));
      if (std::isnan(matlab_semifinal_B.eps_idx_2_c)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (matlab_semifinal_B.eps_idx_2_c < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (matlab_semifinal_B.eps_idx_2_c > 0.0);
      }

      matlab_semifinal_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1_c)) * matlab_semifinal_B.rotm_tmp_j;
      if (std::isnan(-matlab_semifinal_B.scale_m)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (-matlab_semifinal_B.scale_m < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (-matlab_semifinal_B.scale_m > 0.0);
      }

      matlab_semifinal_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_m)) * matlab_semifinal_B.rotm_tmp_j;
      break;

     case 2:
      matlab_semifinal_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1_c));
      if (std::isnan(matlab_semifinal_B.eps_idx_2_c)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (matlab_semifinal_B.eps_idx_2_c < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (matlab_semifinal_B.eps_idx_2_c > 0.0);
      }

      matlab_semifinal_B.eps_idx_0_h = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_m)) * matlab_semifinal_B.rotm_tmp_j;
      if (std::isnan(matlab_semifinal_B.absxk_c)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (matlab_semifinal_B.absxk_c < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (matlab_semifinal_B.absxk_c > 0.0);
      }

      matlab_semifinal_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_m)) * matlab_semifinal_B.rotm_tmp_j;
      break;

     default:
      matlab_semifinal_B.eps_idx_2_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.rotm_tmp_m));
      if (std::isnan(-matlab_semifinal_B.scale_m)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (-matlab_semifinal_B.scale_m < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (-matlab_semifinal_B.scale_m > 0.0);
      }

      matlab_semifinal_B.eps_idx_0_h = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_t_m)) * matlab_semifinal_B.rotm_tmp_j;
      if (std::isnan(matlab_semifinal_B.absxk_c)) {
        matlab_semifinal_B.rotm_tmp_j = (rtNaN);
      } else if (matlab_semifinal_B.absxk_c < 0.0) {
        matlab_semifinal_B.rotm_tmp_j = -1.0;
      } else {
        matlab_semifinal_B.rotm_tmp_j = (matlab_semifinal_B.absxk_c > 0.0);
      }

      matlab_semifinal_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.eps_idx_1_c)) * matlab_semifinal_B.rotm_tmp_j;
      break;
    }
  }

  matlab_semifinal_B.scale_m = 3.3121686421112381E-170;
  matlab_semifinal_B.absxk_c = std::abs(matlab_semifinal_B.eps_idx_0_h);
  if (matlab_semifinal_B.absxk_c > 3.3121686421112381E-170) {
    matlab_semifinal_B.rotm_tmp_m = 1.0;
    matlab_semifinal_B.scale_m = matlab_semifinal_B.absxk_c;
  } else {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.absxk_c /
      3.3121686421112381E-170;
    matlab_semifinal_B.rotm_tmp_m = matlab_semifinal_B.b_t_m *
      matlab_semifinal_B.b_t_m;
  }

  matlab_semifinal_B.absxk_c = std::abs(matlab_semifinal_B.eps_idx_1_c);
  if (matlab_semifinal_B.absxk_c > matlab_semifinal_B.scale_m) {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.scale_m /
      matlab_semifinal_B.absxk_c;
    matlab_semifinal_B.rotm_tmp_m = matlab_semifinal_B.rotm_tmp_m *
      matlab_semifinal_B.b_t_m * matlab_semifinal_B.b_t_m + 1.0;
    matlab_semifinal_B.scale_m = matlab_semifinal_B.absxk_c;
  } else {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.absxk_c /
      matlab_semifinal_B.scale_m;
    matlab_semifinal_B.rotm_tmp_m += matlab_semifinal_B.b_t_m *
      matlab_semifinal_B.b_t_m;
  }

  matlab_semifinal_B.absxk_c = std::abs(matlab_semifinal_B.eps_idx_2_c);
  if (matlab_semifinal_B.absxk_c > matlab_semifinal_B.scale_m) {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.scale_m /
      matlab_semifinal_B.absxk_c;
    matlab_semifinal_B.rotm_tmp_m = matlab_semifinal_B.rotm_tmp_m *
      matlab_semifinal_B.b_t_m * matlab_semifinal_B.b_t_m + 1.0;
    matlab_semifinal_B.scale_m = matlab_semifinal_B.absxk_c;
  } else {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.absxk_c /
      matlab_semifinal_B.scale_m;
    matlab_semifinal_B.rotm_tmp_m += matlab_semifinal_B.b_t_m *
      matlab_semifinal_B.b_t_m;
  }

  if (matlab_semifinal_B.eta_n > matlab_semifinal_B.scale_m) {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.scale_m /
      matlab_semifinal_B.eta_n;
    matlab_semifinal_B.rotm_tmp_m = matlab_semifinal_B.rotm_tmp_m *
      matlab_semifinal_B.b_t_m * matlab_semifinal_B.b_t_m + 1.0;
    matlab_semifinal_B.scale_m = matlab_semifinal_B.eta_n;
  } else {
    matlab_semifinal_B.b_t_m = matlab_semifinal_B.eta_n /
      matlab_semifinal_B.scale_m;
    matlab_semifinal_B.rotm_tmp_m += matlab_semifinal_B.b_t_m *
      matlab_semifinal_B.b_t_m;
  }

  matlab_semifinal_B.rotm_tmp_m = matlab_semifinal_B.scale_m * std::sqrt
    (matlab_semifinal_B.rotm_tmp_m);
  qib[0] = matlab_semifinal_B.eps_idx_0_h / matlab_semifinal_B.rotm_tmp_m;
  qib[1] = matlab_semifinal_B.eps_idx_1_c / matlab_semifinal_B.rotm_tmp_m;
  qib[2] = matlab_semifinal_B.eps_idx_2_c / matlab_semifinal_B.rotm_tmp_m;
  qib[3] = matlab_semifinal_B.eta_n / matlab_semifinal_B.rotm_tmp_m;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal(const char_T varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_h = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_h < 16)) {
    if (varargin_1[matlab_semifinal_B.k_h] != b[matlab_semifinal_B.k_h]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_h++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T matlab_semifinal::matlab_semifinal_strcmp(const char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  matlab_semifinal_B.ret_mc = std::memcmp(&b_a[0], &b[0], 16);
  return matlab_semifinal_B.ret_mc == 0;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T matlab_semifinal::matlab_semifinal_strcmp_b(const char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  matlab_semifinal_B.ret_m = std::memcmp(&b_a[0], &b[0], 16);
  return matlab_semifinal_B.ret_m == 0;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T matlab_semifinal::matlab_semifinal_strcmp_b5(const char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  matlab_semifinal_B.ret_h = std::memcmp(&b_a[0], &b[0], 16);
  return matlab_semifinal_B.ret_h == 0;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal_hj(const char_T varargin_1
  [16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'i', 'd', 'l', 'e', '_', '_', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_o4 = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_o4 < 16)) {
    if (varargin_1[matlab_semifinal_B.k_o4] != b[matlab_semifinal_B.k_o4]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_o4++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal_hj4(const char_T
  varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o', 'r',
    'l', 'd', '_', 'w', 'p', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_e = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_e < 16)) {
    if (varargin_1[matlab_semifinal_B.k_e] != b[matlab_semifinal_B.k_e]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_e++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal_hj43(const char_T
  varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'p', '_',
    's', 'e', 'e', 'k', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_p = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_p < 16)) {
    if (varargin_1[matlab_semifinal_B.k_p] != b[matlab_semifinal_B.k_p]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_p++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal_hj43r(const char_T
  varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 't', 'r', 'a', 'c', 'k', '_', 'o', 'b', 'j', '_',
    'w', 'p', '_', '_', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_f = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_f < 16)) {
    if (varargin_1[matlab_semifinal_B.k_f] != b[matlab_semifinal_B.k_f]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_f++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_isequal_hj43rz(const char_T
  varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'i', 's', 't', 'a', 'n', 'c', 'e', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  matlab_semifinal_B.k_c = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_c < 16)) {
    if (varargin_1[matlab_semifinal_B.k_c] != b[matlab_semifinal_B.k_c]) {
      b_p = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_c++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_strcmp_l(const char_T b[16])
{
  static const char_T b_a[16]{ 'f', 'f', '_', 's', 't', 'o', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  matlab_semifinal_B.ret_l = std::memcmp(&b_a[0], &b[0], 16);
  return matlab_semifinal_B.ret_l == 0;
}

// Function for MATLAB Function: '<S25>/trickFTListInjector'
boolean_T matlab_semifinal::matlab_semifinal_strcmp_lp(const char_T b[16])
{
  static const char_T b_a[16]{ 'd', 'r', 'o', 'p', 'p', 'e', 'r', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  matlab_semifinal_B.ret = std::memcmp(&b_a[0], &b[0], 16);
  return matlab_semifinal_B.ret == 0;
}

// Function for MATLAB Function: '<S34>/forceToPWMCalculator'
void matlab_semifinal::matlab_semifinal_minimum(const real_T x[6], real_T *ex,
  int32_T *idx)
{
  if (!std::isnan(x[0])) {
    matlab_semifinal_B.b_idx_m = 1;
  } else {
    boolean_T exitg1;
    matlab_semifinal_B.b_idx_m = 0;
    matlab_semifinal_B.k_m = 2;
    exitg1 = false;
    while ((!exitg1) && (matlab_semifinal_B.k_m < 7)) {
      if (!std::isnan(x[matlab_semifinal_B.k_m - 1])) {
        matlab_semifinal_B.b_idx_m = matlab_semifinal_B.k_m;
        exitg1 = true;
      } else {
        matlab_semifinal_B.k_m++;
      }
    }
  }

  if (matlab_semifinal_B.b_idx_m == 0) {
    *ex = x[0];
    *idx = 1;
  } else {
    *ex = x[matlab_semifinal_B.b_idx_m - 1];
    *idx = matlab_semifinal_B.b_idx_m;
    for (matlab_semifinal_B.k_m = matlab_semifinal_B.b_idx_m + 1;
         matlab_semifinal_B.k_m < 7; matlab_semifinal_B.k_m++) {
      matlab_semifinal_B.x_l = x[matlab_semifinal_B.k_m - 1];
      if (*ex > matlab_semifinal_B.x_l) {
        *ex = matlab_semifinal_B.x_l;
        *idx = matlab_semifinal_B.k_m;
      }
    }
  }
}

// Function for MATLAB Function: '<S34>/forceToPWMCalculator'
void matlab_semifinal::matlab_semifinal_minimum_g(const real_T x_data[], const
  int32_T *x_size, real_T *ex, int32_T *idx)
{
  matlab_semifinal_B.last = *x_size;
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
    if (!std::isnan(x_data[0])) {
      matlab_semifinal_B.b_idx = 1;
    } else {
      boolean_T exitg1;
      matlab_semifinal_B.b_idx = 0;
      matlab_semifinal_B.k_l = 2;
      exitg1 = false;
      while ((!exitg1) && (matlab_semifinal_B.k_l <= matlab_semifinal_B.last)) {
        if (!std::isnan(x_data[matlab_semifinal_B.k_l - 1])) {
          matlab_semifinal_B.b_idx = matlab_semifinal_B.k_l;
          exitg1 = true;
        } else {
          matlab_semifinal_B.k_l++;
        }
      }
    }

    if (matlab_semifinal_B.b_idx == 0) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[matlab_semifinal_B.b_idx - 1];
      *idx = matlab_semifinal_B.b_idx;
      for (matlab_semifinal_B.k_l = matlab_semifinal_B.b_idx + 1;
           matlab_semifinal_B.k_l <= matlab_semifinal_B.last;
           matlab_semifinal_B.k_l++) {
        matlab_semifinal_B.x_i = x_data[matlab_semifinal_B.k_l - 1];
        if (*ex > matlab_semifinal_B.x_i) {
          *ex = matlab_semifinal_B.x_i;
          *idx = matlab_semifinal_B.k_l;
        }
      }
    }
  }
}

void matlab_semifinal::matlab_semi_Publisher_setupImpl(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/command_result" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S22>/SinkBlock'
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
    // Start for MATLABSystem: '<S22>/SinkBlock'
    matlab_semifinal_B.b_zeroDelimTopic_b[i] = b_zeroDelimTopic[i];
  }

  Pub_matlab_semifinal_549_7.createPublisher
    (&matlab_semifinal_B.b_zeroDelimTopic_b[0], qos_profile);
}

void matlab_semifinal::matlab_se_Publisher_setupImpl_m(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[17]{ "/manipulator_cmd" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S160>/SinkBlock'
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
    // Start for MATLABSystem: '<S160>/SinkBlock'
    matlab_semifinal_B.b_zeroDelimTopic_l[i] = b_zeroDelimTopic[i];
  }

  Pub_matlab_semifinal_588_262_826_2.createPublisher
    (&matlab_semifinal_B.b_zeroDelimTopic_l[0], qos_profile);
}

void matlab_semifinal::matl_Subscriber_setupImpl_mj3b3(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ps5_controller" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S231>/SourceBlock'
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
    // Start for MATLABSystem: '<S231>/SourceBlock'
    matlab_semifinal_B.b_zeroDelimTopic_o[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_semifinal_618.createSubscriber
    (&matlab_semifinal_B.b_zeroDelimTopic_o[0], qos_profile);
}

void matlab_semifinal::matlab__Subscriber_setupImpl_mj(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  matlab_semifinal_B.deadline_b.sec = 0.0;
  matlab_semifinal_B.deadline_b.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 matlab_semifinal_B.deadline_b, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S3>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_matlab_semifinal_587.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_semifinal::matlab_Subscriber_setupImpl_mj3(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[17]{ "/velocity_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S8>/SourceBlock'
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
    // Start for MATLABSystem: '<S8>/SourceBlock'
    matlab_semifinal_B.b_zeroDelimTopic_g[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_semifinal_602.createSubscriber
    (&matlab_semifinal_B.b_zeroDelimTopic_g[0], qos_profile);
}

void matlab_semifinal::matlab_s_Subscriber_setupImpl_m(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[18]{ "/dead_reck_report" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
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
    matlab_semifinal_B.b_zeroDelimTopic_d[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_semifinal_552.createSubscriber
    (&matlab_semifinal_B.b_zeroDelimTopic_d[0], qos_profile);
}

void matlab_semifinal::matlab_sem_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[13]{ "/command_msg" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[13];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S17>/SourceBlock'
  matlab_semifinal_B.deadline_n.sec = 0.0;
  matlab_semifinal_B.deadline_n.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 matlab_semifinal_B.deadline_n, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 13; i++) {
    // Start for MATLABSystem: '<S17>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_matlab_semifinal_549_284.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void matlab_semifinal::matla_Subscriber_setupImpl_mj3b(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[18]{ "/matlab_pos_reset" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S228>/SourceBlock'
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
    // Start for MATLABSystem: '<S228>/SourceBlock'
    matlab_semifinal_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Sub_matlab_semifinal_606.createSubscriber
    (&matlab_semifinal_B.b_zeroDelimTopic[0], qos_profile);
}

void matlab_semifinal::matlab_Publisher_setupImpl_mj3b(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S236>/SinkBlock'
  matlab_semifinal_B.deadline_l.sec = 0.0;
  matlab_semifinal_B.deadline_l.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 matlab_semifinal_B.deadline_l, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S236>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_matlab_semifinal_626_2.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_semifinal::matlab_s_Publisher_setupImpl_mj(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[14]{ "/matlab_debug" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[14];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S226>/SinkBlock'
  matlab_semifinal_B.deadline.sec = 0.0;
  matlab_semifinal_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 matlab_semifinal_B.deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 14; i++) {
    // Start for MATLABSystem: '<S226>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_matlab_semifinal_594_3.createPublisher(&b_zeroDelimTopic[0], qos_profile);
}

void matlab_semifinal::matlab__Publisher_setupImpl_mj3(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S235>/SinkBlock'
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
    // Start for MATLABSystem: '<S235>/SinkBlock'
    matlab_semifinal_B.b_zeroDelimTopic_lx[i] = b_zeroDelimTopic[i];
  }

  Pub_matlab_semifinal_625_150.createPublisher
    (&matlab_semifinal_B.b_zeroDelimTopic_lx[0], qos_profile);
}

// Model step function for TID0
void matlab_semifinal::step0()         // Sample time: [0.01s, 0.0s]
{
  static const char_T a[4]{ 'S', 'U', 'C', 'C' };

  static const char_T b_a[4]{ 'F', 'A', 'I', 'L' };

  static const char_T c_a[4]{ 'R', 'U', 'N', 'N' };

  static const char_T a_0[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o', 'r',
    'l', 'd', '_', 'w', 'p', '_' };

  static const char_T b_a_0[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_',
    't', 'r', 'i', 'c', 'k', '_', '_' };

  static const char_T c_a_0[16]{ 'd', 'i', 's', 't', 'a', 'n', 'c', 'e', '_',
    't', 'r', 'i', 'c', 'k', '_', '_' };

  static const char_T d_a[16]{ 'i', 'd', 'l', 'e', '_', '_', '_', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  static const char_T a_1[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  static const char_T a_2[16]{ 'r', 's', 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a',
    'r', 'd', '_', '_', '_', '_' };

  static const char_T b_a_1[16]{ 'r', 's', 'f', 'f', '_', 'b', 'a', 'c', 'k',
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

  static const char_T a_3[16]{ 'f', 'f', '_', 'f', 'o', 'r', 'w', 'a', 'r', 'd',
    '_', '_', '_', '_', '_', '_' };

  static const char_T b_a_2[16]{ 'f', 'f', '_', 'b', 'a', 'c', 'k', 'w', 'a',
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

  SL_Bus_std_msgs_UInt8 rtb_trigger_msg;
  int8_T tmp_0;
  int8_T tmp_1;
  uint8_T tmp;
  boolean_T reset_dvl_pos;
  boolean_T reset_pids;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const int8_T b_0[16]{ 100, 117, 114, 97, 116, 105, 111, 110, 95, 116,
    114, 105, 99, 107, 95, 95 };

  static const uint8_T b_1[16]{ 112U, 108U, 97U, 99U, 101U, 104U, 111U, 108U,
    100U, 101U, 114U, 95U, 95U, 95U, 95U, 95U };

  static const char_T c[16]{ 'd', 'i', 's', 't', 'a', 'n', 'c', 'e', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  static const char_T d[16]{ 'd', 'r', 'v', '_', 't', 'o', '_', 'w', 'o', 'r',
    'l', 'd', '_', 'w', 'p', '_' };

  static const char_T e[16]{ 'b', 'a', 'r', 'r', 'e', 'l', '_', 'r', 'o', 'l',
    'l', '_', '_', '_', '_', '_' };

  boolean_T exitg1;
  boolean_T guard1;

  {                                    // Sample time: [0.01s, 0.0s]
    rate_monotonic_scheduler((&matlab_semifinal_M));
  }

  // MATLABSystem: '<S231>/SourceBlock'
  matlab_semifinal_B.b_varargout_1 = Sub_matlab_semifinal_618.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_e_g);

  // Outputs for Enabled SubSystem: '<S231>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S232>/Enable'

  // Start for MATLABSystem: '<S231>/SourceBlock'
  if (matlab_semifinal_B.b_varargout_1) {
    // SignalConversion generated from: '<S232>/In1'
    matlab_semifinal_B.In1_k = matlab_semifinal_B.rtb_SourceBlock_o2_e_g;
  }

  // End of Start for MATLABSystem: '<S231>/SourceBlock'
  // End of Outputs for SubSystem: '<S231>/Enabled Subsystem'

  // MATLAB Function: '<Root>/joystick_mode_manager' incorporates:
  //   MATLAB Function: '<S11>/MATLAB Function'

  if (!matlab_semifinal_DW.joystick_flag_not_empty) {
    matlab_semifinal_DW.joystick_flag = false;
    matlab_semifinal_DW.joystick_flag_not_empty = true;
  }

  if (!matlab_semifinal_DW.prior_joystick_flag_not_empty) {
    matlab_semifinal_DW.prior_joystick_flag = false;
    matlab_semifinal_DW.prior_joystick_flag_not_empty = true;
  }

  if (!matlab_semifinal_DW.do_mission_file_flag_not_empty) {
    matlab_semifinal_DW.do_mission_file_flag = true;
    matlab_semifinal_DW.do_mission_file_flag_not_empty = true;
  }

  if (!matlab_semifinal_DW.prior_do_mission_file_flag_not_) {
    matlab_semifinal_DW.prior_do_mission_file_flag = true;
    matlab_semifinal_DW.prior_do_mission_file_flag_not_ = true;
  }

  if (matlab_semifinal_B.In1_k.circle_button) {
    matlab_semifinal_DW.joystick_flag =
      ((!matlab_semifinal_DW.prior_joystick_flag) ||
       matlab_semifinal_DW.joystick_flag);
    matlab_semifinal_DW.joystick_flag =
      ((!matlab_semifinal_DW.prior_joystick_flag) &&
       matlab_semifinal_DW.joystick_flag);
  } else {
    matlab_semifinal_DW.prior_joystick_flag = matlab_semifinal_DW.joystick_flag;
  }

  if (matlab_semifinal_B.In1_k.cross_button) {
    matlab_semifinal_DW.do_mission_file_flag =
      ((!matlab_semifinal_DW.prior_do_mission_file_flag) ||
       matlab_semifinal_DW.do_mission_file_flag);
  }

  if (matlab_semifinal_B.In1_k.circle_button) {
    matlab_semifinal_DW.do_mission_file_flag =
      ((!matlab_semifinal_DW.prior_do_mission_file_flag) &&
       matlab_semifinal_DW.do_mission_file_flag);
  } else {
    matlab_semifinal_DW.prior_do_mission_file_flag =
      matlab_semifinal_DW.do_mission_file_flag;
  }

  // MATLABSystem: '<S3>/SourceBlock'
  matlab_semifinal_B.b_varargout_1 = Sub_matlab_semifinal_587.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_k_c);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S24>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (matlab_semifinal_B.b_varargout_1) {
    // SignalConversion generated from: '<S24>/In1'
    matlab_semifinal_B.In1_g = matlab_semifinal_B.rtb_SourceBlock_o2_k_c;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // MATLABSystem: '<S8>/SourceBlock'
  matlab_semifinal_B.b_varargout_1 = Sub_matlab_semifinal_602.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_mb);

  // Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S227>/Enable'

  // Start for MATLABSystem: '<S8>/SourceBlock'
  if (matlab_semifinal_B.b_varargout_1) {
    // SignalConversion generated from: '<S227>/In1'
    matlab_semifinal_B.In1 = matlab_semifinal_B.rtb_SourceBlock_o2_mb;
  }

  // End of Outputs for SubSystem: '<S8>/Enabled Subsystem'

  // MATLABSystem: '<S2>/SourceBlock'
  matlab_semifinal_B.b_varargout_1_h = Sub_matlab_semifinal_552.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_j_c);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S23>/Enable'

  // Start for MATLABSystem: '<S2>/SourceBlock'
  if (matlab_semifinal_B.b_varargout_1_h) {
    // SignalConversion generated from: '<S23>/In1'
    matlab_semifinal_B.In1_c = matlab_semifinal_B.rtb_SourceBlock_o2_j_c;
  }

  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  matlab_semifinal_B.dRb_u[0] = matlab_semifinal_B.In1_c.angle.x *
    0.017453292519943295;
  matlab_semifinal_B.dRb_u[1] = matlab_semifinal_B.In1_c.angle.y *
    0.017453292519943295;
  matlab_semifinal_B.dRb_u[2] = matlab_semifinal_B.In1_c.angle.z *
    0.017453292519943295;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o] =
      b[matlab_semifinal_B.i_o];
  }

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<Root>/Data Store Write1'

  matlab_semifinal_B.db6 = (static_cast<int32_T>
    (matlab_semifinal_B.rtb_sensors_dvl_cov[0]) + static_cast<int32_T>
    (matlab_semifinal_B.rtb_sensors_dvl_cov[4])) + static_cast<int32_T>
    (matlab_semifinal_B.rtb_sensors_dvl_cov[8]);

  // MATLABSystem: '<S17>/SourceBlock'
  matlab_semifinal_B.b_varargout_1_c =
    Sub_matlab_semifinal_549_284.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_p_k);

  // DataStoreRead: '<S1>/Data Store Read'
  matlab_semifinal_B.DataStoreRead_n = matlab_semifinal_DW.mission_is_started;

  // MATLAB Function: '<S1>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<S1>/Data Store Write1'
  //   DataStoreWrite: '<S1>/Data Store Write2'
  //   MATLABSystem: '<S17>/SourceBlock'
  //
  if ((!matlab_semifinal_DW.mission_is_started) &&
      matlab_semifinal_B.b_varargout_1_c) {
    reset_dvl_pos = true;
    matlab_semifinal_DW.mission_is_started = true;
  } else {
    reset_dvl_pos = false;
  }

  // End of MATLAB Function: '<S1>/MATLAB Function'

  // Outputs for Enabled SubSystem: '<S17>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S21>/Enable'

  // Start for MATLABSystem: '<S17>/SourceBlock'
  if (matlab_semifinal_B.b_varargout_1_c) {
    // SignalConversion generated from: '<S21>/In1'
    matlab_semifinal_B.In1_h = matlab_semifinal_B.rtb_SourceBlock_o2_p_k;
  }

  // End of Outputs for SubSystem: '<S17>/Enabled Subsystem'

  // MATLAB Function: '<S1>/cmdMsgToCmdBus'
  matlab_semifinal_B.cmd.wp_tol[0] = matlab_semifinal_B.In1_h.tolerance.x;
  matlab_semifinal_B.cmd.wp_tol[1] = matlab_semifinal_B.In1_h.tolerance.y;
  matlab_semifinal_B.cmd.wp_tol[2] = matlab_semifinal_B.In1_h.tolerance.z;
  matlab_semifinal_B.cmd.wp_tol[3] = matlab_semifinal_B.In1_h.tolerance.roll;
  matlab_semifinal_B.cmd.wp_tol[4] = matlab_semifinal_B.In1_h.tolerance.pitch;
  matlab_semifinal_B.cmd.wp_tol[5] = matlab_semifinal_B.In1_h.tolerance.yaw;
  matlab_semifinal_B.cmd.hold_time = matlab_semifinal_B.In1_h.hold_time;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
       matlab_semifinal_B.i_o++) {
    tmp = matlab_semifinal_B.In1_h.command_id[matlab_semifinal_B.i_o];
    if (tmp > 127) {
      tmp = 127U;
    }

    matlab_semifinal_B.cmd.cmd_id[matlab_semifinal_B.i_o] = static_cast<int8_T>
      (tmp);
    tmp = matlab_semifinal_B.In1_h.trick[matlab_semifinal_B.i_o];
    if (tmp > 127) {
      tmp = 127U;
    }

    matlab_semifinal_B.cmd.trick_id[matlab_semifinal_B.i_o] = static_cast<int8_T>
      (tmp);
  }

  matlab_semifinal_B.new_waypoint_latch = false;
  matlab_semifinal_B.dropper_trigger = true;
  matlab_semifinal_B.k_o = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_o < 16)) {
    if (matlab_semifinal_B.cmd.cmd_id[matlab_semifinal_B.k_o] !=
        b_0[matlab_semifinal_B.k_o]) {
      matlab_semifinal_B.dropper_trigger = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_o++;
    }
  }

  if (matlab_semifinal_B.dropper_trigger) {
    matlab_semifinal_B.new_waypoint_latch = true;
  }

  if (matlab_semifinal_B.new_waypoint_latch) {
    matlab_semifinal_B.cmd.hold_time = matlab_semifinal_B.In1_h.duration;
  }

  // MATLAB Function: '<S1>/statusKwdToBool' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  matlab_semifinal_B.fd[0] = matlab_semifinal_DW.UnitDelay_DSTATE_f[0];
  matlab_semifinal_B.fd[1] = matlab_semifinal_DW.UnitDelay_DSTATE_f[1];
  matlab_semifinal_B.fd[2] = matlab_semifinal_DW.UnitDelay_DSTATE_f[2];
  matlab_semifinal_B.fd[3] = matlab_semifinal_DW.UnitDelay_DSTATE_f[3];
  matlab_semifinal_B.i_o = std::memcmp(&a[0], &matlab_semifinal_B.fd[0], 4);
  if (matlab_semifinal_B.i_o == 0) {
    matlab_semifinal_B.i_o = 0;
  } else {
    matlab_semifinal_B.i_o = std::memcmp(&b_a[0], &matlab_semifinal_B.fd[0], 4);
    if (matlab_semifinal_B.i_o == 0) {
      matlab_semifinal_B.i_o = 1;
    } else {
      matlab_semifinal_B.i_o = std::memcmp(&c_a[0], &matlab_semifinal_B.fd[0], 4);
      if (matlab_semifinal_B.i_o == 0) {
        matlab_semifinal_B.i_o = 2;
      } else {
        matlab_semifinal_B.i_o = -1;
      }
    }
  }

  switch (matlab_semifinal_B.i_o) {
   case 0:
    matlab_semifinal_B.result_msg.success = true;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.result_msg.found_object[matlab_semifinal_B.i_o] =
        b_1[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S18>/Enable'

    // MATLABSystem: '<S22>/SinkBlock'
    Pub_matlab_semifinal_549_7.publish(&matlab_semifinal_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 1:
    matlab_semifinal_B.result_msg.success = false;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.result_msg.found_object[matlab_semifinal_B.i_o] =
        b_1[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.result_msg.reached_waypoint_without_detection = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S18>/Enable'

    // MATLABSystem: '<S22>/SinkBlock'
    Pub_matlab_semifinal_549_7.publish(&matlab_semifinal_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 2:
    break;
  }

  // End of MATLAB Function: '<S1>/statusKwdToBool'

  // DigitalClock: '<S26>/Digital Clock' incorporates:
  //   DigitalClock: '<Root>/Digital Clock'

  matlab_semifinal_B.idx = (((&matlab_semifinal_M)->Timing.clockTick0) * 0.01);

  // MATLAB Function: '<S6>/eulToQuat'
  matlab_semifinal_B.rotm_tmp = std::cos(matlab_semifinal_B.dRb_u[1]);
  matlab_semifinal_B.norm_w = std::sin(matlab_semifinal_B.dRb_u[1]);
  matlab_semifinal_B.t = std::cos(matlab_semifinal_B.dRb_u[2]);
  matlab_semifinal_B.theta = std::sin(matlab_semifinal_B.dRb_u[2]);
  matlab_semifinal_B.b_scale = std::sin(matlab_semifinal_B.dRb_u[0]);
  matlab_semifinal_B.b_absxk = std::cos(matlab_semifinal_B.dRb_u[0]);
  matlab_semifinal_B.Cbi[0] = matlab_semifinal_B.rotm_tmp * matlab_semifinal_B.t;
  matlab_semifinal_B.Cbi[3] = matlab_semifinal_B.rotm_tmp *
    matlab_semifinal_B.theta;
  matlab_semifinal_B.theta_b = matlab_semifinal_B.b_scale *
    matlab_semifinal_B.norm_w;
  matlab_semifinal_B.Cbi[4] = matlab_semifinal_B.theta_b *
    matlab_semifinal_B.theta + matlab_semifinal_B.b_absxk * matlab_semifinal_B.t;
  matlab_semifinal_B.Cbi[7] = matlab_semifinal_B.b_scale *
    matlab_semifinal_B.rotm_tmp;
  matlab_semifinal_B.Cbi[8] = matlab_semifinal_B.b_absxk *
    matlab_semifinal_B.rotm_tmp;
  matlab_semifinal_B.eta = std::sqrt(((matlab_semifinal_B.Cbi[0] +
    matlab_semifinal_B.Cbi[4]) + matlab_semifinal_B.Cbi[8]) + 1.0) / 2.0;
  if (matlab_semifinal_B.eta != 0.0) {
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.b_absxk *
      matlab_semifinal_B.norm_w;
    matlab_semifinal_B.scale = 4.0 * matlab_semifinal_B.eta;
    matlab_semifinal_B.eps[0] = (matlab_semifinal_B.Cbi[7] -
      (matlab_semifinal_B.eps_tmp * matlab_semifinal_B.theta -
       matlab_semifinal_B.b_scale * matlab_semifinal_B.t)) /
      matlab_semifinal_B.scale;
    matlab_semifinal_B.eps[1] = ((matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.t + matlab_semifinal_B.b_scale *
      matlab_semifinal_B.theta) - (-matlab_semifinal_B.norm_w)) /
      matlab_semifinal_B.scale;
    matlab_semifinal_B.eps[2] = (matlab_semifinal_B.Cbi[3] -
      (matlab_semifinal_B.theta_b * matlab_semifinal_B.t -
       matlab_semifinal_B.b_absxk * matlab_semifinal_B.theta)) /
      matlab_semifinal_B.scale;
  } else {
    matlab_semifinal_B.t = (matlab_semifinal_B.Cbi[0] + 1.0) / 2.0;
    matlab_semifinal_B.dRb_u[0] = matlab_semifinal_B.t;
    matlab_semifinal_B.theta = (matlab_semifinal_B.Cbi[4] + 1.0) / 2.0;
    matlab_semifinal_B.dRb_u[1] = matlab_semifinal_B.theta;
    matlab_semifinal_B.b_scale = (matlab_semifinal_B.Cbi[8] + 1.0) / 2.0;
    matlab_semifinal_B.dRb_u[2] = matlab_semifinal_B.b_scale;
    if (!std::isnan(matlab_semifinal_B.t)) {
      matlab_semifinal_B.k_o = 1;
    } else {
      matlab_semifinal_B.k_o = 0;
      matlab_semifinal_B.pos = 2;
      exitg1 = false;
      while ((!exitg1) && (matlab_semifinal_B.pos < 4)) {
        if (!std::isnan(matlab_semifinal_B.dRb_u[matlab_semifinal_B.pos - 1])) {
          matlab_semifinal_B.k_o = matlab_semifinal_B.pos;
          exitg1 = true;
        } else {
          matlab_semifinal_B.pos++;
        }
      }
    }

    if (matlab_semifinal_B.k_o == 0) {
      matlab_semifinal_B.i_o = 1;
    } else {
      matlab_semifinal_B.absxk = matlab_semifinal_B.dRb_u[matlab_semifinal_B.k_o
        - 1];
      matlab_semifinal_B.i_o = matlab_semifinal_B.k_o;
      for (matlab_semifinal_B.pos = matlab_semifinal_B.k_o + 1;
           matlab_semifinal_B.pos < 4; matlab_semifinal_B.pos++) {
        matlab_semifinal_B.rtb_dRb_u_d =
          matlab_semifinal_B.dRb_u[matlab_semifinal_B.pos - 1];
        if (matlab_semifinal_B.absxk < matlab_semifinal_B.rtb_dRb_u_d) {
          matlab_semifinal_B.absxk = matlab_semifinal_B.rtb_dRb_u_d;
          matlab_semifinal_B.i_o = matlab_semifinal_B.pos;
        }
      }
    }

    switch (matlab_semifinal_B.i_o) {
     case 1:
      matlab_semifinal_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_semifinal_B.t));
      if (std::isnan(matlab_semifinal_B.Cbi[3])) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (matlab_semifinal_B.Cbi[3] < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (matlab_semifinal_B.Cbi[3] > 0.0);
      }

      matlab_semifinal_B.eps[1] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.theta)) * matlab_semifinal_B.b_t;
      if (std::isnan(-matlab_semifinal_B.norm_w)) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (-matlab_semifinal_B.norm_w < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (-matlab_semifinal_B.norm_w > 0.0);
      }

      matlab_semifinal_B.eps[2] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_scale)) * matlab_semifinal_B.b_t;
      break;

     case 2:
      matlab_semifinal_B.eps[1] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.theta));
      if (std::isnan(matlab_semifinal_B.Cbi[3])) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (matlab_semifinal_B.Cbi[3] < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (matlab_semifinal_B.Cbi[3] > 0.0);
      }

      matlab_semifinal_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_semifinal_B.t))
        * matlab_semifinal_B.b_t;
      if (std::isnan(matlab_semifinal_B.Cbi[7])) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (matlab_semifinal_B.Cbi[7] < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (matlab_semifinal_B.Cbi[7] > 0.0);
      }

      matlab_semifinal_B.eps[2] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_scale)) * matlab_semifinal_B.b_t;
      break;

     default:
      matlab_semifinal_B.eps[2] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.b_scale));
      if (std::isnan(-matlab_semifinal_B.norm_w)) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (-matlab_semifinal_B.norm_w < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (-matlab_semifinal_B.norm_w > 0.0);
      }

      matlab_semifinal_B.eps[0] = std::sqrt(std::fmax(0.0, matlab_semifinal_B.t))
        * matlab_semifinal_B.b_t;
      if (std::isnan(matlab_semifinal_B.Cbi[7])) {
        matlab_semifinal_B.b_t = (rtNaN);
      } else if (matlab_semifinal_B.Cbi[7] < 0.0) {
        matlab_semifinal_B.b_t = -1.0;
      } else {
        matlab_semifinal_B.b_t = (matlab_semifinal_B.Cbi[7] > 0.0);
      }

      matlab_semifinal_B.eps[1] = std::sqrt(std::fmax(0.0,
        matlab_semifinal_B.theta)) * matlab_semifinal_B.b_t;
      break;
    }
  }

  matlab_semifinal_B.scale = 3.3121686421112381E-170;
  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps[0]);
  if (matlab_semifinal_B.absxk > 3.3121686421112381E-170) {
    matlab_semifinal_B.eps_tmp = 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.absxk / 3.3121686421112381E-170;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.b_t * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps[1]);
  if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.scale / matlab_semifinal_B.absxk;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.absxk / matlab_semifinal_B.scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps[2]);
  if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.scale / matlab_semifinal_B.absxk;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.absxk / matlab_semifinal_B.scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  if (matlab_semifinal_B.eta > matlab_semifinal_B.scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.scale / matlab_semifinal_B.eta;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.eta;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.eta / matlab_semifinal_B.scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.eps_tmp = matlab_semifinal_B.scale * std::sqrt
    (matlab_semifinal_B.eps_tmp);

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  matlab_semifinal_B.dv3[0] =
    matlab_semifinal_B.In1_g.imu_fusion.angular_velocity.x;
  matlab_semifinal_B.dv3[1] =
    matlab_semifinal_B.In1_g.imu_fusion.angular_velocity.y;
  matlab_semifinal_B.dv3[2] =
    matlab_semifinal_B.In1_g.imu_fusion.angular_velocity.z;

  // Product: '<S6>/Matrix Multiply2' incorporates:
  //   Constant: '<S6>/Constant1'

  matlab_semifinal_B.rtb_dRb_u_d = 0.0;
  matlab_semifinal_B.rtb_X_est_wb = 0.0;
  matlab_semifinal_B.rtb_X_est_wb_j = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.dv3[matlab_semifinal_B.i_o];
    matlab_semifinal_B.rtb_dRb_u_d += matlab_semifinal_ConstP.Constant1_Value_h
      [3 * matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.rtb_X_est_wb +=
      matlab_semifinal_ConstP.Constant1_Value_h[3 * matlab_semifinal_B.i_o + 1] *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.rtb_X_est_wb_j +=
      matlab_semifinal_ConstP.Constant1_Value_h[3 * matlab_semifinal_B.i_o + 2] *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.X_est.wb[2] = matlab_semifinal_B.rtb_X_est_wb_j;
  matlab_semifinal_B.X_est.wb[1] = matlab_semifinal_B.rtb_X_est_wb;
  matlab_semifinal_B.X_est.wb[0] = matlab_semifinal_B.rtb_dRb_u_d;

  // MATLAB Function: '<S6>/discreteTimeQuatPropagation' incorporates:
  //   MATLAB Function: '<S6>/eulToQuat'
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S6>/Matrix Multiply2'
  //
  if (!matlab_semifinal_DW.qk_not_empty) {
    matlab_semifinal_DW.qk[0] = 0.0;
    matlab_semifinal_DW.qk[1] = 0.0;
    matlab_semifinal_DW.qk[2] = 0.0;
    matlab_semifinal_DW.qk[3] = 1.0;
    matlab_semifinal_DW.qk_not_empty = true;
  }

  if (matlab_semifinal_B.b_varargout_1_h) {
    matlab_semifinal_DW.qk[0] = matlab_semifinal_B.eps[0] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_DW.qk[1] = matlab_semifinal_B.eps[1] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_DW.qk[2] = matlab_semifinal_B.eps[2] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_DW.qk[3] = matlab_semifinal_B.eta /
      matlab_semifinal_B.eps_tmp;
  }

  matlab_semifinal_B.scale = 3.3121686421112381E-170;
  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.rtb_dRb_u_d);
  if (matlab_semifinal_B.absxk > 3.3121686421112381E-170) {
    matlab_semifinal_B.norm_w = 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.t = matlab_semifinal_B.absxk / 3.3121686421112381E-170;
    matlab_semifinal_B.norm_w = matlab_semifinal_B.t * matlab_semifinal_B.t;
  }

  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.rtb_X_est_wb);
  if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
    matlab_semifinal_B.t = matlab_semifinal_B.scale / matlab_semifinal_B.absxk;
    matlab_semifinal_B.norm_w = matlab_semifinal_B.norm_w * matlab_semifinal_B.t
      * matlab_semifinal_B.t + 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.t = matlab_semifinal_B.absxk / matlab_semifinal_B.scale;
    matlab_semifinal_B.norm_w += matlab_semifinal_B.t * matlab_semifinal_B.t;
  }

  matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.rtb_X_est_wb_j);
  if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
    matlab_semifinal_B.t = matlab_semifinal_B.scale / matlab_semifinal_B.absxk;
    matlab_semifinal_B.norm_w = matlab_semifinal_B.norm_w * matlab_semifinal_B.t
      * matlab_semifinal_B.t + 1.0;
    matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
  } else {
    matlab_semifinal_B.t = matlab_semifinal_B.absxk / matlab_semifinal_B.scale;
    matlab_semifinal_B.norm_w += matlab_semifinal_B.t * matlab_semifinal_B.t;
  }

  matlab_semifinal_B.norm_w = matlab_semifinal_B.scale * std::sqrt
    (matlab_semifinal_B.norm_w);
  if (matlab_semifinal_B.norm_w > 1.0E-10) {
    matlab_semifinal_B.b_a_h = std::sin(0.5 * matlab_semifinal_B.norm_w * 0.01) /
      matlab_semifinal_B.norm_w;
    matlab_semifinal_B.eps[0] = matlab_semifinal_B.b_a_h *
      matlab_semifinal_B.rtb_dRb_u_d;
    matlab_semifinal_B.eps[1] = matlab_semifinal_B.b_a_h *
      matlab_semifinal_B.rtb_X_est_wb;
    matlab_semifinal_B.eps[2] = matlab_semifinal_B.b_a_h *
      matlab_semifinal_B.rtb_X_est_wb_j;
  } else {
    matlab_semifinal_B.eps[0] = 0.005 * matlab_semifinal_B.rtb_dRb_u_d;
    matlab_semifinal_B.eps[1] = 0.005 * matlab_semifinal_B.rtb_X_est_wb;
    matlab_semifinal_B.eps[2] = 0.005 * matlab_semifinal_B.rtb_X_est_wb_j;
  }

  matlab_semifinal_B.norm_w = std::cos(0.5 * matlab_semifinal_B.norm_w * 0.01);
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    // MATLAB Function: '<S6>/quatToRotm' incorporates:
    //   MATLAB Function: '<S6>/derivedStateEstimates'

    matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o] =
      b[matlab_semifinal_B.i_o];
  }

  matlab_semifinal_B.rtb_Cbi_tmp[0] = 0.0;
  matlab_semifinal_B.rtb_Cbi_tmp[3] = -matlab_semifinal_B.eps[2];
  matlab_semifinal_B.rtb_Cbi_tmp[6] = matlab_semifinal_B.eps[1];
  matlab_semifinal_B.rtb_Cbi_tmp[1] = matlab_semifinal_B.eps[2];
  matlab_semifinal_B.rtb_Cbi_tmp[4] = 0.0;
  matlab_semifinal_B.rtb_Cbi_tmp[7] = -matlab_semifinal_B.eps[0];
  matlab_semifinal_B.rtb_Cbi_tmp[2] = -matlab_semifinal_B.eps[1];
  matlab_semifinal_B.rtb_Cbi_tmp[5] = matlab_semifinal_B.eps[0];
  matlab_semifinal_B.rtb_Cbi_tmp[8] = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.k_o = matlab_semifinal_B.i_o << 2;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.qk_plus_1_tmp[3 * matlab_semifinal_B.i_o] *
      matlab_semifinal_B.norm_w - matlab_semifinal_B.rtb_Cbi_tmp[3 *
      matlab_semifinal_B.i_o];
    matlab_semifinal_B.pos = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 1] =
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.pos] *
      matlab_semifinal_B.norm_w -
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.pos];
    matlab_semifinal_B.pos = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 2] =
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.pos] *
      matlab_semifinal_B.norm_w -
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.pos];
    matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[matlab_semifinal_B.i_o];
    matlab_semifinal_B.c_a[matlab_semifinal_B.i_o + 12] =
      matlab_semifinal_B.b_a_h;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 3] =
      -matlab_semifinal_B.b_a_h;
  }

  matlab_semifinal_B.c_a[15] = matlab_semifinal_B.norm_w;
  matlab_semifinal_B.b_absxk = 0.0;
  matlab_semifinal_B.norm_w = 0.0;
  matlab_semifinal_B.t = 0.0;
  matlab_semifinal_B.theta = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 4;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t = matlab_semifinal_DW.qk[matlab_semifinal_B.i_o];
    matlab_semifinal_B.k_o = matlab_semifinal_B.i_o << 2;
    matlab_semifinal_B.b_absxk += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o]
      * matlab_semifinal_B.b_t;
    matlab_semifinal_B.norm_w += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o +
      1] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.t += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 2] *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.theta += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o +
      3] * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.b_scale = 3.3121686421112381E-170;
  matlab_semifinal_DW.qk[0] = matlab_semifinal_B.b_absxk;
  matlab_semifinal_B.b_absxk = std::abs(matlab_semifinal_DW.qk[0]);
  if (matlab_semifinal_B.b_absxk > 3.3121686421112381E-170) {
    matlab_semifinal_B.eps_tmp = 1.0;
    matlab_semifinal_B.b_scale = matlab_semifinal_B.b_absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_absxk /
      3.3121686421112381E-170;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.b_t * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_DW.qk[1] = matlab_semifinal_B.norm_w;
  matlab_semifinal_B.b_absxk = std::abs(matlab_semifinal_DW.qk[1]);
  if (matlab_semifinal_B.b_absxk > matlab_semifinal_B.b_scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_scale /
      matlab_semifinal_B.b_absxk;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.b_scale = matlab_semifinal_B.b_absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_absxk /
      matlab_semifinal_B.b_scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_DW.qk[2] = matlab_semifinal_B.t;
  matlab_semifinal_B.b_absxk = std::abs(matlab_semifinal_DW.qk[2]);
  if (matlab_semifinal_B.b_absxk > matlab_semifinal_B.b_scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_scale /
      matlab_semifinal_B.b_absxk;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.b_scale = matlab_semifinal_B.b_absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_absxk /
      matlab_semifinal_B.b_scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_DW.qk[3] = matlab_semifinal_B.theta;
  matlab_semifinal_B.b_absxk = std::abs(matlab_semifinal_DW.qk[3]);
  if (matlab_semifinal_B.b_absxk > matlab_semifinal_B.b_scale) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_scale /
      matlab_semifinal_B.b_absxk;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
    matlab_semifinal_B.b_scale = matlab_semifinal_B.b_absxk;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.b_absxk /
      matlab_semifinal_B.b_scale;
    matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.eps_tmp = matlab_semifinal_B.b_scale * std::sqrt
    (matlab_semifinal_B.eps_tmp);
  matlab_semifinal_B.rtb_delta_qe_idx_2 = matlab_semifinal_DW.qk[0] /
    matlab_semifinal_B.eps_tmp;
  matlab_semifinal_DW.qk[0] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.X_est.qib[0] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.rtb_delta_qe_idx_2 = matlab_semifinal_DW.qk[1] /
    matlab_semifinal_B.eps_tmp;
  matlab_semifinal_DW.qk[1] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.X_est.qib[1] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.rtb_delta_qe_idx_2 = matlab_semifinal_DW.qk[2] /
    matlab_semifinal_B.eps_tmp;
  matlab_semifinal_DW.qk[2] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.X_est.qib[2] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.rtb_delta_qe_idx_2 = matlab_semifinal_DW.qk[3] /
    matlab_semifinal_B.eps_tmp;
  matlab_semifinal_DW.qk[3] = matlab_semifinal_B.rtb_delta_qe_idx_2;
  matlab_semifinal_B.X_est.qib[3] = matlab_semifinal_B.rtb_delta_qe_idx_2;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'
  //   Math: '<S6>/Transpose'

  matlab_semifinal_B.rtb_DeadZone_p_idx_1 =
    matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.rtb_delta_qe_idx_2 * 2.0 - 1.0;
  matlab_semifinal_B.b_a_h = 2.0 * matlab_semifinal_B.rtb_delta_qe_idx_2;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.rtb_Cbi_tmp[3 * matlab_semifinal_B.i_o] = 2.0 *
      matlab_semifinal_B.X_est.qib[0] *
      matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] =
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o] = 2.0 *
      matlab_semifinal_B.X_est.qib[1] *
      matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o + 3];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o] = 2.0 *
      matlab_semifinal_B.X_est.qib[2] *
      matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o + 6];
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.Cbi[3 * matlab_semifinal_B.i_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.i_o];

    // Math: '<S6>/Transpose'
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.i_o + 3];

    // Math: '<S6>/Transpose'
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.i_o + 6];
  }

  matlab_semifinal_B.rtb_Cbi_tmp_tmp = matlab_semifinal_B.b_a_h * 0.0;

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0 = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_est.qib[2];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[1] =
    matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1 = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_est.qib[1];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[2] =
    matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_Eul_idx_1 = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_est.qib[2];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[3] = matlab_semifinal_B.rtb_Eul_idx_1;
  matlab_semifinal_B.rtb_Cbi_tmp_b[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_Eul_idx_0 = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_est.qib[0];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[5] = matlab_semifinal_B.rtb_Eul_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_DeadZone_p_idx_0 = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_est.qib[1];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[6] = matlab_semifinal_B.rtb_DeadZone_p_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_B.rtb_Cbi_tmp_tmp_f = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_est.qib[0];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  matlab_semifinal_B.rtb_Cbi_tmp_b[7] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
  matlab_semifinal_B.rtb_Cbi_tmp_b[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] +
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o];
  }

  // MATLABSystem: '<S228>/SourceBlock'
  reset_pids = Sub_matlab_semifinal_606.getLatestMessage
    (&matlab_semifinal_B.rtb_SourceBlock_o2_m_k);

  // Outputs for Enabled SubSystem: '<S228>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S229>/Enable'

  // Start for MATLABSystem: '<S228>/SourceBlock'
  if (reset_pids) {
    // SignalConversion generated from: '<S229>/In1'
    matlab_semifinal_B.In1_j = matlab_semifinal_B.rtb_SourceBlock_o2_m_k;
  }

  // End of Outputs for SubSystem: '<S228>/Enabled Subsystem'

  // Logic: '<S6>/OR' incorporates:
  //   DataStoreRead: '<S6>/Data Store Read1'
  //   Logic: '<S9>/AND'
  //   MATLABSystem: '<S228>/SourceBlock'
  //
  reset_dvl_pos = (reset_dvl_pos || (reset_pids && matlab_semifinal_B.In1_j.data));

  // MATLAB Function: '<S6>/dvl_reset' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'

  if (matlab_semifinal_DW.prior_flag && (!reset_dvl_pos)) {
    matlab_semifinal_DW.offset[0] = matlab_semifinal_B.In1_c.position.x;
    matlab_semifinal_DW.offset[1] = matlab_semifinal_B.In1_c.position.y;
    matlab_semifinal_DW.offset[2] = matlab_semifinal_B.In1_c.position.z;
  }

  matlab_semifinal_DW.prior_flag = reset_dvl_pos;
  matlab_semifinal_B.rtb_dvl_pos_l[0] = matlab_semifinal_B.In1_c.position.x -
    matlab_semifinal_DW.offset[0];
  matlab_semifinal_B.rtb_dvl_pos_l[1] = matlab_semifinal_B.In1_c.position.y -
    matlab_semifinal_DW.offset[1];
  matlab_semifinal_B.rtb_dvl_pos_l[2] = matlab_semifinal_B.In1_c.position.z -
    matlab_semifinal_DW.offset[2];

  // End of MATLAB Function: '<S6>/dvl_reset'

  // Product: '<S6>/Matrix Multiply3' incorporates:
  //   Math: '<S6>/Transpose'

  matlab_semifinal_B.b_a_h = 0.0;
  matlab_semifinal_B.eps_b = 0.0;
  matlab_semifinal_B.lower_voltage_index = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t =
      matlab_semifinal_B.rtb_dvl_pos_l[matlab_semifinal_B.i_o];
    matlab_semifinal_B.b_a_h += matlab_semifinal_B.Cbi_c[3 *
      matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.eps_b += matlab_semifinal_B.Cbi_c[3 *
      matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.lower_voltage_index += matlab_semifinal_B.Cbi_c[3 *
      matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.eps[2] = matlab_semifinal_B.lower_voltage_index;
  matlab_semifinal_B.eps[1] = matlab_semifinal_B.eps_b;

  // DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S6>/Matrix Multiply3'
  //
  if (matlab_semifinal_DW.PositionIntegrator_IC_LOADING != 0) {
    matlab_semifinal_DW.PositionIntegrator_DSTATE[0] = matlab_semifinal_B.b_a_h;
    matlab_semifinal_DW.PositionIntegrator_DSTATE[1] = matlab_semifinal_B.eps_b;
    matlab_semifinal_DW.PositionIntegrator_DSTATE[2] =
      matlab_semifinal_B.lower_voltage_index;
  }

  if (matlab_semifinal_B.b_varargout_1_h &&
      (matlab_semifinal_DW.PositionIntegrator_PrevResetSta <= 0)) {
    matlab_semifinal_DW.PositionIntegrator_DSTATE[0] = matlab_semifinal_B.b_a_h;
    matlab_semifinal_DW.PositionIntegrator_DSTATE[1] = matlab_semifinal_B.eps_b;
    matlab_semifinal_DW.PositionIntegrator_DSTATE[2] =
      matlab_semifinal_B.lower_voltage_index;
  }

  // DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLABSystem: '<S8>/SourceBlock'
  //
  if (matlab_semifinal_DW.VelocityIntegrator_IC_LOADING != 0) {
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[0] =
      matlab_semifinal_B.In1.velocity_data.x;
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[1] =
      matlab_semifinal_B.In1.velocity_data.y;
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[2] =
      matlab_semifinal_B.In1.velocity_data.z;
  }

  if (matlab_semifinal_B.b_varargout_1 &&
      (matlab_semifinal_DW.VelocityIntegrator_PrevResetSta <= 0)) {
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[0] =
      matlab_semifinal_B.In1.velocity_data.x;
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[1] =
      matlab_semifinal_B.In1.velocity_data.y;
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[2] =
      matlab_semifinal_B.In1.velocity_data.z;
  }

  // Product: '<S6>/Matrix Multiply' incorporates:
  //   Constant: '<S6>/Constant'
  //   Math: '<S6>/Transpose'

  matlab_semifinal_B.norm_w = 0.0;
  matlab_semifinal_B.t = 0.0;
  matlab_semifinal_B.theta = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t =
      matlab_semifinal_ConstP.Constant_Value_l0[matlab_semifinal_B.i_o];
    matlab_semifinal_B.norm_w += matlab_semifinal_B.Cbi_c[3 *
      matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.t += matlab_semifinal_B.Cbi_c[3 * matlab_semifinal_B.i_o
      + 1] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.theta += matlab_semifinal_B.Cbi_c[3 *
      matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.theta;
  matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.t;
  matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.norm_w;

  // End of Product: '<S6>/Matrix Multiply'

  // Sum: '<S6>/Sum' incorporates:
  //   Constant: '<S6>/Constant1'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   Product: '<S6>/Matrix Multiply1'

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.rtb_dvl_pos_l[matlab_semifinal_B.i_o] =
      ((matlab_semifinal_ConstP.Constant1_Value_h[matlab_semifinal_B.i_o + 3] *
        matlab_semifinal_B.In1_g.imu_fusion.linear_acceleration.y +
        matlab_semifinal_ConstP.Constant1_Value_h[matlab_semifinal_B.i_o] *
        matlab_semifinal_B.In1_g.imu_fusion.linear_acceleration.x) +
       matlab_semifinal_ConstP.Constant1_Value_h[matlab_semifinal_B.i_o + 6] *
       matlab_semifinal_B.In1_g.imu_fusion.linear_acceleration.z) -
      matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o];
  }

  // End of Sum: '<S6>/Sum'

  // MATLAB Function: '<S6>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S6>/Position Integrator'
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'

  matlab_semifinal_B.Cbi_c[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.Cbi_c[3] = matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;
  matlab_semifinal_B.Cbi_c[6] = matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;
  matlab_semifinal_B.Cbi_c[1] = matlab_semifinal_B.rtb_Eul_idx_1;
  matlab_semifinal_B.Cbi_c[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.Cbi_c[7] = matlab_semifinal_B.rtb_Eul_idx_0;
  matlab_semifinal_B.Cbi_c[2] = matlab_semifinal_B.rtb_DeadZone_p_idx_0;
  matlab_semifinal_B.Cbi_c[5] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
  matlab_semifinal_B.Cbi_c[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.X_est.Cib[matlab_semifinal_B.i_o] =
      (matlab_semifinal_B.rtb_DeadZone_p_idx_1 *
       matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o] +
       matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.i_o]) +
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o];
    matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] +=
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o];
  }

  matlab_semifinal_B.theta_b = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_semifinal_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_semifinal_B.theta_b)) < 1.0E-6) {
    matlab_semifinal_B.norm_w = 0.0;
    matlab_semifinal_B.t = matlab_semifinal_rt_atan2d_snf
      (-matlab_semifinal_B.Cbi[1], matlab_semifinal_B.Cbi[4]);
  } else {
    matlab_semifinal_B.norm_w = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[7], matlab_semifinal_B.Cbi[8]);
    matlab_semifinal_B.t = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[3], matlab_semifinal_B.Cbi[0]);
  }

  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.norm_w);
  matlab_semifinal_B.theta = -matlab_semifinal_B.theta_b;
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.theta);
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.t);
  matlab_semifinal_B.b_scale = 0.0;
  matlab_semifinal_B.b_absxk = 0.0;
  matlab_semifinal_B.rotm_tmp = 0.0;
  matlab_semifinal_B.X_est.Eul[0] = matlab_semifinal_B.norm_w;
  matlab_semifinal_B.X_est.Eul[1] = matlab_semifinal_B.theta;
  matlab_semifinal_B.X_est.Eul[2] = matlab_semifinal_B.t;
  matlab_semifinal_B.phi = 0.0;
  matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 0.0;
  matlab_semifinal_B.upper_voltage_index = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t =
      matlab_semifinal_DW.PositionIntegrator_DSTATE[matlab_semifinal_B.i_o];
    matlab_semifinal_B.eta = matlab_semifinal_B.X_est.Cib[3 *
      matlab_semifinal_B.i_o];
    matlab_semifinal_B.b_scale += matlab_semifinal_B.eta *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.rtb_delta_qe_idx_1 = matlab_semifinal_B.X_est.Cib[3 *
      matlab_semifinal_B.i_o + 1];
    matlab_semifinal_B.b_absxk += matlab_semifinal_B.rtb_delta_qe_idx_1 *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.X_est.Cib[3 *
      matlab_semifinal_B.i_o + 2];
    matlab_semifinal_B.rotm_tmp += matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.b_t =
      matlab_semifinal_DW.VelocityIntegrator_DSTATE[matlab_semifinal_B.i_o];
    matlab_semifinal_B.phi += matlab_semifinal_B.eta * matlab_semifinal_B.b_t;
    matlab_semifinal_B.rtb_DeadZone_p_idx_2 +=
      matlab_semifinal_B.rtb_delta_qe_idx_1 * matlab_semifinal_B.b_t;
    matlab_semifinal_B.upper_voltage_index += matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.X_est.Ri[0] = matlab_semifinal_B.b_scale;
  matlab_semifinal_B.X_est.Ri[1] = matlab_semifinal_B.b_absxk;
  matlab_semifinal_B.X_est.Ri[2] = matlab_semifinal_B.rotm_tmp;

  // Logic: '<S4>/OR1' incorporates:
  //   DataStoreWrite: '<S4>/Data Store Write1'
  //   MATLAB Function: '<Root>/joystick_mode_manager'
  //   MATLABSystem: '<S17>/SourceBlock'
  //
  reset_pids = (matlab_semifinal_B.b_varargout_1_c ||
                matlab_semifinal_DW.joystick_flag);

  // MATLAB Function: '<S26>/commandExecuter' incorporates:
  //   DataStoreWrite: '<S26>/Data Store Write'
  //   DataStoreWrite: '<S4>/Data Store Write1'
  //   DigitalClock: '<S26>/Digital Clock'
  //   DiscreteIntegrator: '<S6>/Position Integrator'
  //   MATLAB Function: '<S1>/cmdMsgToCmdBus'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'

  if (!matlab_semifinal_DW.hold_timer_start_time_not_empty) {
    matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
    matlab_semifinal_DW.hold_timer_start_time_not_empty = true;
  }

  if (!matlab_semifinal_DW.idle_wp_not_empty) {
    matlab_semifinal_DW.idle_wp[0] = matlab_semifinal_B.b_scale;
    matlab_semifinal_DW.idle_wp[1] = matlab_semifinal_B.b_absxk;
    matlab_semifinal_DW.idle_wp[2] = matlab_semifinal_B.rotm_tmp;
    matlab_semifinal_DW.idle_wp[3] = 0.0;
    matlab_semifinal_DW.idle_wp[4] = 0.0;
    matlab_semifinal_DW.idle_wp[5] = matlab_semifinal_B.t;
    matlab_semifinal_DW.idle_wp_not_empty = true;
  }

  if (!matlab_semifinal_DW.cmd_specific_wp_not_empty) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 6;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_DW.cmd_specific_wp[matlab_semifinal_B.i_o] =
        matlab_semifinal_DW.idle_wp[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_DW.cmd_specific_wp_not_empty = true;
  }

  if ((matlab_semifinal_DW.UnitDelay_DSTATE == 2.0) &&
      (matlab_semifinal_DW.prior_action_id != 2.0)) {
    matlab_semifinal_DW.idle_wp[5] = matlab_semifinal_DW.UnitDelay1_DSTATE;
  }

  matlab_semifinal_DW.prior_action_id = matlab_semifinal_DW.UnitDelay_DSTATE;
  if (reset_pids) {
    matlab_semifinal_DW.idle_wp[0] = 0.0;
    matlab_semifinal_DW.idle_wp[1] = 0.0;
    matlab_semifinal_DW.idle_wp[2] = 0.0;
    matlab_semifinal_DW.idle_wp[3] = 0.0;
    matlab_semifinal_DW.idle_wp[4] = 0.0;
    matlab_semifinal_DW.idle_wp[5] = matlab_semifinal_B.t;
    matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
    matlab_semifinal_DW.prior_action_id = 0.0;
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.s[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.cmd.cmd_id[matlab_semifinal_B.i_o];
  }

  matlab_semifinal_B.i_o = std::memcmp(&a_0[0], &matlab_semifinal_B.s[0], 16);
  if (matlab_semifinal_B.i_o == 0) {
    matlab_semifinal_B.i_o = 0;
  } else {
    matlab_semifinal_B.i_o = std::memcmp(&b_a_0[0], &matlab_semifinal_B.s[0], 16);
    if (matlab_semifinal_B.i_o == 0) {
      matlab_semifinal_B.i_o = 1;
    } else {
      matlab_semifinal_B.i_o = std::memcmp(&c_a_0[0], &matlab_semifinal_B.s[0],
        16);
      if (matlab_semifinal_B.i_o == 0) {
        matlab_semifinal_B.i_o = 2;
      } else {
        matlab_semifinal_B.i_o = std::memcmp(&d_a[0], &matlab_semifinal_B.s[0],
          16);
        if (matlab_semifinal_B.i_o == 0) {
          matlab_semifinal_B.i_o = 3;
        } else {
          matlab_semifinal_B.i_o = -1;
        }
      }
    }
  }

  switch (matlab_semifinal_B.i_o) {
   case 0:
    matlab_semifinal_B.dv3[0] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.roll) *
      matlab_semifinal_DW.idle_wp[3] + matlab_semifinal_B.In1_h.waypoint.roll *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.roll);
    matlab_semifinal_B.X_u[0] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.x) * matlab_semifinal_DW.idle_wp
      [0] + matlab_semifinal_B.In1_h.waypoint.x * static_cast<real_T>
      (matlab_semifinal_B.In1_h.waypoint_mask.x);
    matlab_semifinal_B.dv3[1] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.pitch) *
      matlab_semifinal_DW.idle_wp[4] + matlab_semifinal_B.In1_h.waypoint.pitch *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.pitch);
    matlab_semifinal_B.X_u[1] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.y) * matlab_semifinal_DW.idle_wp
      [1] + matlab_semifinal_B.In1_h.waypoint.y * static_cast<real_T>
      (matlab_semifinal_B.In1_h.waypoint_mask.y);
    matlab_semifinal_B.dv3[2] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.yaw) *
      matlab_semifinal_DW.idle_wp[5] + matlab_semifinal_B.In1_h.waypoint.yaw *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.yaw);
    matlab_semifinal_B.X_u[2] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.z) * matlab_semifinal_DW.idle_wp
      [2] + matlab_semifinal_B.In1_h.waypoint.z * static_cast<real_T>
      (matlab_semifinal_B.In1_h.waypoint_mask.z);
    matlab_semifinal_eulToQuat_o(matlab_semifinal_B.dv3, matlab_semifinal_B.dv1);
    matlab_semifinal_B.X_u[3] = matlab_semifinal_B.dv1[0];
    matlab_semifinal_B.X_u[4] = matlab_semifinal_B.dv1[1];
    matlab_semifinal_B.X_u[5] = matlab_semifinal_B.dv1[2];
    matlab_semifinal_B.X_u[6] = matlab_semifinal_B.dv1[3];
    matlab_semifinal_B.X_u[7] = 0.0;
    matlab_semifinal_B.X_u[10] = 0.0;
    matlab_semifinal_B.X_u[8] = 0.0;
    matlab_semifinal_B.X_u[11] = 0.0;
    matlab_semifinal_B.X_u[9] = 0.0;
    matlab_semifinal_B.X_u[12] = 0.0;
    if (matlab_semifinal_withinWPTol(matlab_semifinal_B.X_est.Ri,
         matlab_semifinal_B.X_est.qib, matlab_semifinal_B.X_u,
         matlab_semifinal_B.cmd.wp_tol)) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.idx -
        matlab_semifinal_DW.hold_timer_start_time;
    } else {
      matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
      matlab_semifinal_B.b_t = 0.0;
    }

    if (matlab_semifinal_B.b_t >= matlab_semifinal_B.cmd.hold_time) {
      matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 83;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 67;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 67;
      matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
    } else {
      matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 82;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 78;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 78;
    }

    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 6;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_DW.cmd_specific_wp[matlab_semifinal_B.i_o] =
        matlab_semifinal_DW.idle_wp[matlab_semifinal_B.i_o];
    }
    break;

   case 1:
    matlab_sem_executeDurationTrick(matlab_semifinal_B.cmd.hold_time,
      matlab_semifinal_B.cmd.trick_id, matlab_semifinal_DW.idle_wp,
      matlab_semifinal_B.X_est.Ri, matlab_semifinal_B.X_est.Eul,
      matlab_semifinal_B.X_est.Cib, &matlab_semifinal_DW.hold_timer_start_time,
      matlab_semifinal_B.idx, reset_pids, matlab_semifinal_DW.cmd_specific_wp,
      matlab_semifinal_DW.UnitDelay_DSTATE_f, &matlab_semifinal_B.b_t,
      matlab_semifinal_B.X_u);
    break;

   case 2:
    if (!matlab_semifinal_DW.wp_defined_latch) {
      matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.In1_h.waypoint.x +
        matlab_semifinal_DW.PositionIntegrator_DSTATE[0];
      matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.In1_h.waypoint.y +
        matlab_semifinal_DW.PositionIntegrator_DSTATE[1];
      matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.In1_h.waypoint.z +
        matlab_semifinal_DW.PositionIntegrator_DSTATE[2];
      matlab_semifinal_B.eta = 0.0;
      matlab_semifinal_B.rtb_delta_qe_idx_1 = 0.0;
      matlab_semifinal_B.eps_tmp = 0.0;
      for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
           matlab_semifinal_B.i_o++) {
        matlab_semifinal_B.b_t = matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o];
        matlab_semifinal_B.eta += matlab_semifinal_B.X_est.Cib[3 *
          matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
        matlab_semifinal_B.rtb_delta_qe_idx_1 += matlab_semifinal_B.X_est.Cib[3 *
          matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
        matlab_semifinal_B.eps_tmp += matlab_semifinal_B.X_est.Cib[3 *
          matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
      }

      matlab_semifinal_DW.body_relative_wp[2] = matlab_semifinal_B.eps_tmp;
      matlab_semifinal_DW.body_relative_wp[1] =
        matlab_semifinal_B.rtb_delta_qe_idx_1;
      matlab_semifinal_DW.body_relative_wp[0] = matlab_semifinal_B.eta;
      matlab_semifinal_DW.wp_defined_latch = true;
    }

    matlab_semifinal_B.dv3[0] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.roll) *
      matlab_semifinal_DW.idle_wp[3] + matlab_semifinal_B.In1_h.waypoint.roll *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.roll);
    matlab_semifinal_B.dv3[1] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.pitch) *
      matlab_semifinal_DW.idle_wp[4] + matlab_semifinal_B.In1_h.waypoint.pitch *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.pitch);
    matlab_semifinal_B.dv3[2] = static_cast<real_T>
      (!matlab_semifinal_B.In1_h.waypoint_mask.yaw) *
      matlab_semifinal_DW.idle_wp[5] + matlab_semifinal_B.In1_h.waypoint.yaw *
      static_cast<real_T>(matlab_semifinal_B.In1_h.waypoint_mask.yaw);
    matlab_semifinal_eulToQuat_o(matlab_semifinal_B.dv3, matlab_semifinal_B.dv1);
    matlab_semifinal_B.X_u[0] = matlab_semifinal_DW.body_relative_wp[0];
    matlab_semifinal_B.X_u[1] = matlab_semifinal_DW.body_relative_wp[1];
    matlab_semifinal_B.X_u[2] = matlab_semifinal_DW.body_relative_wp[2];
    matlab_semifinal_B.X_u[3] = matlab_semifinal_B.dv1[0];
    matlab_semifinal_B.X_u[4] = matlab_semifinal_B.dv1[1];
    matlab_semifinal_B.X_u[5] = matlab_semifinal_B.dv1[2];
    matlab_semifinal_B.X_u[6] = matlab_semifinal_B.dv1[3];
    matlab_semifinal_B.X_u[7] = 0.0;
    matlab_semifinal_B.X_u[10] = 0.0;
    matlab_semifinal_B.X_u[8] = 0.0;
    matlab_semifinal_B.X_u[11] = 0.0;
    matlab_semifinal_B.X_u[9] = 0.0;
    matlab_semifinal_B.X_u[12] = 0.0;
    if (matlab_semifinal_withinWPTol(matlab_semifinal_B.X_est.Ri,
         matlab_semifinal_B.X_est.qib, matlab_semifinal_B.X_u,
         matlab_semifinal_B.cmd.wp_tol)) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.idx -
        matlab_semifinal_DW.hold_timer_start_time;
    } else {
      matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
      matlab_semifinal_B.b_t = 0.0;
    }

    if (matlab_semifinal_B.b_t >= matlab_semifinal_B.cmd.hold_time) {
      matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 83;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 67;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 67;
      matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
      matlab_semifinal_DW.wp_defined_latch = false;
    } else {
      matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 82;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 78;
      matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 78;
    }
    break;

   case 3:
    matlab_semifinal_eulToQuat_o(&matlab_semifinal_DW.idle_wp[3],
      matlab_semifinal_B.dv1);
    matlab_semifinal_B.X_u[0] = matlab_semifinal_DW.idle_wp[0];
    matlab_semifinal_B.X_u[1] = matlab_semifinal_DW.idle_wp[1];
    matlab_semifinal_B.X_u[2] = matlab_semifinal_DW.idle_wp[2];
    matlab_semifinal_B.X_u[3] = matlab_semifinal_B.dv1[0];
    matlab_semifinal_B.X_u[4] = matlab_semifinal_B.dv1[1];
    matlab_semifinal_B.X_u[5] = matlab_semifinal_B.dv1[2];
    matlab_semifinal_B.X_u[6] = matlab_semifinal_B.dv1[3];
    matlab_semifinal_B.X_u[7] = 0.0;
    matlab_semifinal_B.X_u[10] = 0.0;
    matlab_semifinal_B.X_u[8] = 0.0;
    matlab_semifinal_B.X_u[11] = 0.0;
    matlab_semifinal_B.X_u[9] = 0.0;
    matlab_semifinal_B.X_u[12] = 0.0;
    matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 82;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 78;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 78;
    matlab_semifinal_DW.mission_is_started = false;
    break;

   default:
    matlab_semifinal_eulToQuat_o(&matlab_semifinal_DW.idle_wp[3],
      matlab_semifinal_B.dv1);
    matlab_semifinal_B.X_u[0] = matlab_semifinal_DW.idle_wp[0];
    matlab_semifinal_B.X_u[1] = matlab_semifinal_DW.idle_wp[1];
    matlab_semifinal_B.X_u[2] = matlab_semifinal_DW.idle_wp[2];
    matlab_semifinal_B.X_u[3] = matlab_semifinal_B.dv1[0];
    matlab_semifinal_B.X_u[4] = matlab_semifinal_B.dv1[1];
    matlab_semifinal_B.X_u[5] = matlab_semifinal_B.dv1[2];
    matlab_semifinal_B.X_u[6] = matlab_semifinal_B.dv1[3];
    matlab_semifinal_B.X_u[7] = 0.0;
    matlab_semifinal_B.X_u[10] = 0.0;
    matlab_semifinal_B.X_u[8] = 0.0;
    matlab_semifinal_B.X_u[11] = 0.0;
    matlab_semifinal_B.X_u[9] = 0.0;
    matlab_semifinal_B.X_u[12] = 0.0;
    matlab_semifinal_DW.hold_timer_start_time = matlab_semifinal_B.idx;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[0] = 82;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[1] = 85;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[2] = 78;
    matlab_semifinal_DW.UnitDelay_DSTATE_f[3] = 78;
    break;
  }

  // End of MATLAB Function: '<S26>/commandExecuter'

  // MATLAB Function: '<S4>/quatToEul' incorporates:
  //   MATLAB Function: '<S26>/quatToEul'

  matlab_semifinal_B.b_t = matlab_semifinal_B.X_u[6] * matlab_semifinal_B.X_u[6]
    * 2.0 - 1.0;
  matlab_semifinal_B.b_a_h = 2.0 * matlab_semifinal_B.X_u[6];
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.b_t *
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o];
  }

  matlab_semifinal_B.b_t = matlab_semifinal_B.b_a_h * 0.0;
  matlab_semifinal_B.rtb_Cbi_tmp[0] = matlab_semifinal_B.b_t;
  matlab_semifinal_B.rtb_Cbi_tmp[1] = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_u[5];
  matlab_semifinal_B.rtb_Cbi_tmp[2] = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_u[4];
  matlab_semifinal_B.rtb_Cbi_tmp[3] = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_u[5];
  matlab_semifinal_B.rtb_Cbi_tmp[4] = matlab_semifinal_B.b_t;
  matlab_semifinal_B.rtb_Cbi_tmp[5] = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_u[3];
  matlab_semifinal_B.rtb_Cbi_tmp[6] = matlab_semifinal_B.b_a_h *
    -matlab_semifinal_B.X_u[4];
  matlab_semifinal_B.rtb_Cbi_tmp[7] = matlab_semifinal_B.b_a_h *
    matlab_semifinal_B.X_u[3];
  matlab_semifinal_B.rtb_Cbi_tmp[8] = matlab_semifinal_B.b_t;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.theta_b = matlab_semifinal_B.X_u[matlab_semifinal_B.i_o +
      3] * 2.0;
    matlab_semifinal_B.Cbi[3 * matlab_semifinal_B.i_o] =
      (matlab_semifinal_B.theta_b * matlab_semifinal_B.X_u[3] +
       matlab_semifinal_B.qk_plus_1_tmp[3 * matlab_semifinal_B.i_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[3 * matlab_semifinal_B.i_o];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] = (matlab_semifinal_B.theta_b
      * matlab_semifinal_B.X_u[4] +
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.k_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] = (matlab_semifinal_B.theta_b
      * matlab_semifinal_B.X_u[5] +
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.k_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o];
  }

  matlab_semifinal_B.theta_b = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_semifinal_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_semifinal_B.theta_b)) < 1.0E-6) {
    // SignalConversion generated from: '<S225>/ SFunction ' incorporates:
    //   MATLAB Function: '<S7>/MATLAB Function'

    matlab_semifinal_B.TmpSignalConversionAtSFunct[3] = 0.0;
    matlab_semifinal_B.TmpSignalConversionAtSFunct[5] =
      matlab_semifinal_rt_atan2d_snf(-matlab_semifinal_B.Cbi[1],
      matlab_semifinal_B.Cbi[4]);
  } else {
    // SignalConversion generated from: '<S225>/ SFunction ' incorporates:
    //   MATLAB Function: '<S7>/MATLAB Function'

    matlab_semifinal_B.TmpSignalConversionAtSFunct[3] =
      matlab_semifinal_rt_atan2d_snf(matlab_semifinal_B.Cbi[7],
      matlab_semifinal_B.Cbi[8]);
    matlab_semifinal_B.TmpSignalConversionAtSFunct[5] =
      matlab_semifinal_rt_atan2d_snf(matlab_semifinal_B.Cbi[3],
      matlab_semifinal_B.Cbi[0]);
  }

  // SignalConversion generated from: '<S225>/ SFunction ' incorporates:
  //   MATLAB Function: '<S4>/quatToEul'
  //   MATLAB Function: '<S7>/MATLAB Function'

  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.TmpSignalConversionAtSFunct[3]);
  matlab_semifinal_B.TmpSignalConversionAtSFunct[4] =
    -matlab_semifinal_B.theta_b;
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.TmpSignalConversionAtSFunct[4]);
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.TmpSignalConversionAtSFunct[5]);

  // MATLAB Function: '<S25>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'

  if (!matlab_semifinal_DW.prior_action_id_not_empty) {
    matlab_semifinal_DW.prior_action_id_n = matlab_semifinal_DW.action_id;
    matlab_semifinal_DW.prior_action_id_not_empty = true;
  }

  matlab_semifinal_B.new_waypoint_latch = false;
  matlab_semifinal_B.dropper_trigger = true;
  matlab_semifinal_B.k_o = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.k_o < 3)) {
    if (!(matlab_semifinal_DW.prior_Ri_u[matlab_semifinal_B.k_o] ==
          matlab_semifinal_B.X_u[matlab_semifinal_B.k_o])) {
      matlab_semifinal_B.dropper_trigger = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.k_o++;
    }
  }

  if (matlab_semifinal_B.dropper_trigger) {
    matlab_semifinal_B.new_waypoint_latch = true;
  }

  if (!matlab_semifinal_B.new_waypoint_latch) {
    matlab_semifinal_B.new_waypoint_latch = true;
    matlab_semifinal_DW.prior_Ri_u[0] = matlab_semifinal_B.X_u[0];
    matlab_semifinal_DW.prior_Ri_u[1] = matlab_semifinal_B.X_u[1];
    matlab_semifinal_DW.prior_Ri_u[2] = matlab_semifinal_B.X_u[2];
  } else {
    matlab_semifinal_B.new_waypoint_latch = false;
    matlab_semifinal_DW.prior_Ri_u[0] = matlab_semifinal_B.X_u[0];
    matlab_semifinal_DW.prior_Ri_u[1] = matlab_semifinal_B.X_u[1];
    matlab_semifinal_DW.prior_Ri_u[2] = matlab_semifinal_B.X_u[2];
  }

  matlab_semifinal_B.Ri_xy_e[0] = matlab_semifinal_B.X_u[0] -
    matlab_semifinal_B.b_scale;
  matlab_semifinal_B.Ri_xy_e[1] = matlab_semifinal_B.X_u[1] -
    matlab_semifinal_B.b_absxk;
  matlab_semifinal_B.b_t = matlab_semifinal_rt_atan2d_snf
    (matlab_semifinal_B.Ri_xy_e[1], matlab_semifinal_B.Ri_xy_e[0]);
  if (matlab_semifinal_B.new_waypoint_latch) {
    matlab_semifinal_DW.persistant_yaw_target = matlab_semifinal_B.b_t;
  } else if (matlab_semifinal_DW.action_id !=
             matlab_semifinal_DW.prior_action_id_n) {
    matlab_semifinal_DW.persistant_yaw_target = matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.rtb_delta_qe_idx_1 = matlab_semifinal_norm
    (matlab_semifinal_B.Ri_xy_e);
  if (matlab_semifinal_B.rtb_delta_qe_idx_1 >= 0.5) {
    matlab_semifinal_B.theta_b = std::sin
      (matlab_semifinal_DW.persistant_yaw_target);
    matlab_semifinal_B.eps_tmp = std::cos
      (matlab_semifinal_DW.persistant_yaw_target);
    matlab_semifinal_B.b_t = std::sin(matlab_semifinal_DW.persistant_yaw_target);
    matlab_semifinal_B.absxk = 0.0 * matlab_semifinal_B.theta_b;
    matlab_semifinal_B.Cbi[4] = matlab_semifinal_B.absxk +
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_B.eta = std::sqrt(((std::cos
      (matlab_semifinal_DW.persistant_yaw_target) + matlab_semifinal_B.Cbi[4]) +
      1.0) + 1.0) / 2.0;
    if (matlab_semifinal_B.eta != 0.0) {
      matlab_semifinal_B.eps_tmp *= 0.0;
      matlab_semifinal_B.scale = 4.0 * matlab_semifinal_B.eta;
      matlab_semifinal_B.eps_n[0] = (0.0 - (matlab_semifinal_B.absxk -
        matlab_semifinal_B.eps_tmp)) / matlab_semifinal_B.scale;
      matlab_semifinal_B.eps_n[1] = (matlab_semifinal_B.eps_tmp +
        matlab_semifinal_B.absxk) / matlab_semifinal_B.scale;
      matlab_semifinal_B.eps_n[2] = (matlab_semifinal_B.b_t -
        (matlab_semifinal_B.eps_tmp - matlab_semifinal_B.theta_b)) /
        matlab_semifinal_B.scale;
    } else {
      matlab_semifinal_B.eps_tmp = (std::cos
        (matlab_semifinal_DW.persistant_yaw_target) + 1.0) / 2.0;
      matlab_semifinal_B.eps[0] = matlab_semifinal_B.eps_tmp;
      matlab_semifinal_B.scale = (matlab_semifinal_B.Cbi[4] + 1.0) / 2.0;
      matlab_semifinal_B.eps[1] = matlab_semifinal_B.scale;
      matlab_semifinal_B.eps[2] = 1.0;
      if (!std::isnan(matlab_semifinal_B.eps_tmp)) {
        matlab_semifinal_B.k_o = 1;
      } else {
        matlab_semifinal_B.k_o = 0;
        matlab_semifinal_B.pos = 2;
        exitg1 = false;
        while ((!exitg1) && (matlab_semifinal_B.pos < 4)) {
          if (!std::isnan(matlab_semifinal_B.eps[matlab_semifinal_B.pos - 1])) {
            matlab_semifinal_B.k_o = matlab_semifinal_B.pos;
            exitg1 = true;
          } else {
            matlab_semifinal_B.pos++;
          }
        }
      }

      if (matlab_semifinal_B.k_o == 0) {
        matlab_semifinal_B.i_o = 1;
      } else {
        matlab_semifinal_B.absxk = matlab_semifinal_B.eps[matlab_semifinal_B.k_o
          - 1];
        matlab_semifinal_B.i_o = matlab_semifinal_B.k_o;
        for (matlab_semifinal_B.d_k = matlab_semifinal_B.k_o + 1;
             matlab_semifinal_B.d_k < 4; matlab_semifinal_B.d_k++) {
          matlab_semifinal_B.b_a_h =
            matlab_semifinal_B.eps[matlab_semifinal_B.d_k - 1];
          if (matlab_semifinal_B.absxk < matlab_semifinal_B.b_a_h) {
            matlab_semifinal_B.absxk = matlab_semifinal_B.b_a_h;
            matlab_semifinal_B.i_o = matlab_semifinal_B.d_k;
          }
        }
      }

      switch (matlab_semifinal_B.i_o) {
       case 1:
        matlab_semifinal_B.eps_n[0] = std::sqrt(std::fmax(0.0,
          matlab_semifinal_B.eps_tmp));
        if (std::isnan(matlab_semifinal_B.b_t)) {
          matlab_semifinal_B.b_t = (rtNaN);
        } else if (matlab_semifinal_B.b_t < 0.0) {
          matlab_semifinal_B.b_t = -1.0;
        } else {
          matlab_semifinal_B.b_t = (matlab_semifinal_B.b_t > 0.0);
        }

        matlab_semifinal_B.eps_n[1] = std::sqrt(std::fmax(0.0,
          matlab_semifinal_B.scale)) * matlab_semifinal_B.b_t;
        matlab_semifinal_B.eps_n[2] = 0.0;
        break;

       case 2:
        matlab_semifinal_B.eps_n[1] = std::sqrt(std::fmax(0.0,
          matlab_semifinal_B.scale));
        if (std::isnan(matlab_semifinal_B.b_t)) {
          matlab_semifinal_B.b_t = (rtNaN);
        } else if (matlab_semifinal_B.b_t < 0.0) {
          matlab_semifinal_B.b_t = -1.0;
        } else {
          matlab_semifinal_B.b_t = (matlab_semifinal_B.b_t > 0.0);
        }

        matlab_semifinal_B.eps_n[0] = std::sqrt(std::fmax(0.0,
          matlab_semifinal_B.eps_tmp)) * matlab_semifinal_B.b_t;
        matlab_semifinal_B.eps_n[2] = 0.0;
        break;

       default:
        matlab_semifinal_B.eps_n[2] = 1.0;
        matlab_semifinal_B.eps_n[0] = 0.0;
        matlab_semifinal_B.eps_n[1] = 0.0;
        break;
      }
    }

    matlab_semifinal_B.scale = 3.3121686421112381E-170;
    matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps_n[0]);
    if (matlab_semifinal_B.absxk > 3.3121686421112381E-170) {
      matlab_semifinal_B.eps_tmp = 1.0;
      matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
    } else {
      matlab_semifinal_B.b_t = matlab_semifinal_B.absxk /
        3.3121686421112381E-170;
      matlab_semifinal_B.eps_tmp = matlab_semifinal_B.b_t *
        matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps_n[1]);
    if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.scale /
        matlab_semifinal_B.absxk;
      matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
        matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
      matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
    } else {
      matlab_semifinal_B.b_t = matlab_semifinal_B.absxk /
        matlab_semifinal_B.scale;
      matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
        matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.absxk = std::abs(matlab_semifinal_B.eps_n[2]);
    if (matlab_semifinal_B.absxk > matlab_semifinal_B.scale) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.scale /
        matlab_semifinal_B.absxk;
      matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
        matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
      matlab_semifinal_B.scale = matlab_semifinal_B.absxk;
    } else {
      matlab_semifinal_B.b_t = matlab_semifinal_B.absxk /
        matlab_semifinal_B.scale;
      matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
        matlab_semifinal_B.b_t;
    }

    if (matlab_semifinal_B.eta > matlab_semifinal_B.scale) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.scale / matlab_semifinal_B.eta;
      matlab_semifinal_B.eps_tmp = matlab_semifinal_B.eps_tmp *
        matlab_semifinal_B.b_t * matlab_semifinal_B.b_t + 1.0;
      matlab_semifinal_B.scale = matlab_semifinal_B.eta;
    } else {
      matlab_semifinal_B.b_t = matlab_semifinal_B.eta / matlab_semifinal_B.scale;
      matlab_semifinal_B.eps_tmp += matlab_semifinal_B.b_t *
        matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.eps_tmp = matlab_semifinal_B.scale * std::sqrt
      (matlab_semifinal_B.eps_tmp);
    matlab_semifinal_B.qib_int_u[0] = matlab_semifinal_B.eps_n[0] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_B.qib_int_u[1] = matlab_semifinal_B.eps_n[1] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_B.qib_int_u[2] = matlab_semifinal_B.eps_n[2] /
      matlab_semifinal_B.eps_tmp;
    matlab_semifinal_B.qib_int_u[3] = matlab_semifinal_B.eta /
      matlab_semifinal_B.eps_tmp;
  } else {
    matlab_semifinal_B.qib_int_u[0] = matlab_semifinal_B.X_u[3];
    matlab_semifinal_B.qib_int_u[1] = matlab_semifinal_B.X_u[4];
    matlab_semifinal_B.qib_int_u[2] = matlab_semifinal_B.X_u[5];
    matlab_semifinal_B.qib_int_u[3] = matlab_semifinal_B.X_u[6];
  }

  matlab_semifinal_B.qe_matlab[0] = ((matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qib_int_u[3] - -matlab_semifinal_B.X_est.qib[0] *
    matlab_semifinal_B.qib_int_u[0]) - -matlab_semifinal_B.X_est.qib[1] *
    matlab_semifinal_B.qib_int_u[1]) - -matlab_semifinal_B.X_est.qib[2] *
    matlab_semifinal_B.qib_int_u[2];
  matlab_semifinal_B.qe_matlab[1] = (matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qib_int_u[0] + matlab_semifinal_B.qib_int_u[3] *
    -matlab_semifinal_B.X_est.qib[0]) + (-matlab_semifinal_B.X_est.qib[1] *
    matlab_semifinal_B.qib_int_u[2] - matlab_semifinal_B.qib_int_u[1] *
    -matlab_semifinal_B.X_est.qib[2]);
  matlab_semifinal_B.qe_matlab[2] = (matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qib_int_u[1] + matlab_semifinal_B.qib_int_u[3] *
    -matlab_semifinal_B.X_est.qib[1]) + (matlab_semifinal_B.qib_int_u[0] *
    -matlab_semifinal_B.X_est.qib[2] - -matlab_semifinal_B.X_est.qib[0] *
    matlab_semifinal_B.qib_int_u[2]);
  matlab_semifinal_B.qe_matlab[3] = (matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qib_int_u[2] + matlab_semifinal_B.qib_int_u[3] *
    -matlab_semifinal_B.X_est.qib[2]) + (-matlab_semifinal_B.X_est.qib[0] *
    matlab_semifinal_B.qib_int_u[1] - matlab_semifinal_B.qib_int_u[0] *
    -matlab_semifinal_B.X_est.qib[1]);
  matlab_semifinal_B.qinv[0] = matlab_semifinal_B.qe_matlab[1];
  matlab_semifinal_B.qinv[1] = matlab_semifinal_B.qe_matlab[2];
  matlab_semifinal_B.qinv[2] = matlab_semifinal_B.qe_matlab[3];
  matlab_semifinal_B.qinv[3] = matlab_semifinal_B.qe_matlab[0];
  if (matlab_semifinal_B.qe_matlab[0] < 0.0) {
    matlab_semifinal_B.qinv[0] = -matlab_semifinal_B.qe_matlab[1];
    matlab_semifinal_B.qinv[1] = -matlab_semifinal_B.qe_matlab[2];
    matlab_semifinal_B.qinv[2] = -matlab_semifinal_B.qe_matlab[3];
    matlab_semifinal_B.qinv[3] = -matlab_semifinal_B.qe_matlab[0];
  }

  matlab_semifinal_B.eta = matlab_semifinal_B.qinv[3] * matlab_semifinal_B.qinv
    [3] * 2.0 - 1.0;
  matlab_semifinal_B.b_t = 2.0 * matlab_semifinal_B.qinv[3];
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.eps_tmp = 2.0 *
      matlab_semifinal_B.qinv[matlab_semifinal_B.i_o];
    matlab_semifinal_B.Cbi_c[3 * matlab_semifinal_B.i_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
      matlab_semifinal_B.eta + matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.qinv[0];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.eta + matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.qinv[1];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.eta + matlab_semifinal_B.eps_tmp *
      matlab_semifinal_B.qinv[2];
  }

  matlab_semifinal_B.eta = matlab_semifinal_B.b_t * 0.0;
  matlab_semifinal_B.rtb_Cbi_tmp_b[0] = matlab_semifinal_B.eta;
  matlab_semifinal_B.rtb_Cbi_tmp_b[1] = matlab_semifinal_B.b_t *
    -matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.rtb_Cbi_tmp_b[2] = matlab_semifinal_B.b_t *
    matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.rtb_Cbi_tmp_b[3] = matlab_semifinal_B.b_t *
    matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.rtb_Cbi_tmp_b[4] = matlab_semifinal_B.eta;
  matlab_semifinal_B.rtb_Cbi_tmp_b[5] = matlab_semifinal_B.b_t *
    -matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.rtb_Cbi_tmp_b[6] = matlab_semifinal_B.b_t *
    -matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.rtb_Cbi_tmp_b[7] = matlab_semifinal_B.b_t *
    matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.rtb_Cbi_tmp_b[8] = matlab_semifinal_B.eta;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o] +
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o];
  }

  matlab_semifinal_B.theta_b = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_semifinal_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_semifinal_B.theta_b)) < 1.0E-6) {
    matlab_semifinal_B.eps[0] = 0.0;
    matlab_semifinal_B.b_t = matlab_semifinal_rt_atan2d_snf
      (-matlab_semifinal_B.Cbi[1], matlab_semifinal_B.Cbi[4]);
  } else {
    matlab_semifinal_B.eps[0] = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[7], matlab_semifinal_B.Cbi[8]);
    matlab_semifinal_B.b_t = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[3], matlab_semifinal_B.Cbi[0]);
  }

  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.eps[0]);
  matlab_semifinal_B.theta_b = -matlab_semifinal_B.theta_b;
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.theta_b);
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.b_t);
  matlab_semifinal_B.eps[1] = matlab_semifinal_B.theta_b;
  matlab_semifinal_B.eps[2] = matlab_semifinal_B.b_t;
  matlab_semifinal_B.new_waypoint_latch = false;
  matlab_semifinal_B.dropper_trigger = true;
  matlab_semifinal_B.i_o = 0;
  exitg1 = false;
  while ((!exitg1) && (matlab_semifinal_B.i_o < 16)) {
    if (matlab_semifinal_B.s[matlab_semifinal_B.i_o] != c[matlab_semifinal_B.i_o])
    {
      matlab_semifinal_B.dropper_trigger = false;
      exitg1 = true;
    } else {
      matlab_semifinal_B.i_o++;
    }
  }

  if (matlab_semifinal_B.dropper_trigger) {
    matlab_semifinal_B.new_waypoint_latch = true;
  }

  guard1 = false;
  if (matlab_semifinal_B.new_waypoint_latch) {
    guard1 = true;
  } else {
    matlab_semifinal_B.new_waypoint_latch = false;
    matlab_semifinal_B.dropper_trigger = true;
    matlab_semifinal_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (matlab_semifinal_B.i_o < 16)) {
      if (matlab_semifinal_B.s[matlab_semifinal_B.i_o] !=
          d[matlab_semifinal_B.i_o]) {
        matlab_semifinal_B.dropper_trigger = false;
        exitg1 = true;
      } else {
        matlab_semifinal_B.i_o++;
      }
    }

    if (matlab_semifinal_B.dropper_trigger) {
      matlab_semifinal_B.new_waypoint_latch = true;
    }

    if (matlab_semifinal_B.new_waypoint_latch) {
      guard1 = true;
    }
  }

  if (guard1) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.x1[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.cmd.trick_id[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.new_waypoint_latch = false;
    matlab_semifinal_B.dropper_trigger = true;
    matlab_semifinal_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (matlab_semifinal_B.i_o < 16)) {
      if (matlab_semifinal_B.x1[matlab_semifinal_B.i_o] !=
          e[matlab_semifinal_B.i_o]) {
        matlab_semifinal_B.dropper_trigger = false;
        exitg1 = true;
      } else {
        matlab_semifinal_B.i_o++;
      }
    }

    if (matlab_semifinal_B.dropper_trigger) {
      matlab_semifinal_B.new_waypoint_latch = true;
    }

    if (matlab_semifinal_B.new_waypoint_latch) {
      matlab_semifinal_B.eps[0] = 0.0;
      matlab_semifinal_B.eps[1] = matlab_semifinal_B.theta_b;
      matlab_semifinal_B.eps[2] = matlab_semifinal_B.b_t;
    }
  }

  matlab_semifinal_B.Rb_u[0] = std::abs(matlab_semifinal_B.eps[0]);
  matlab_semifinal_B.Rb_u[1] = std::abs(matlab_semifinal_B.eps[1]);
  matlab_semifinal_B.Rb_u[2] = std::abs(matlab_semifinal_B.eps[2]);
  if (!std::isnan(matlab_semifinal_B.Rb_u[0])) {
    matlab_semifinal_B.i_o = 1;
  } else {
    matlab_semifinal_B.i_o = 0;
    matlab_semifinal_B.k_o = 2;
    exitg1 = false;
    while ((!exitg1) && (matlab_semifinal_B.k_o < 4)) {
      if (!std::isnan(matlab_semifinal_B.Rb_u[matlab_semifinal_B.k_o - 1])) {
        matlab_semifinal_B.i_o = matlab_semifinal_B.k_o;
        exitg1 = true;
      } else {
        matlab_semifinal_B.k_o++;
      }
    }
  }

  if (matlab_semifinal_B.i_o == 0) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.Rb_u[0];
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o - 1];
    for (matlab_semifinal_B.k_o = matlab_semifinal_B.i_o + 1;
         matlab_semifinal_B.k_o < 4; matlab_semifinal_B.k_o++) {
      matlab_semifinal_B.lower_voltage_index =
        matlab_semifinal_B.Rb_u[matlab_semifinal_B.k_o - 1];
      if (matlab_semifinal_B.b_t < matlab_semifinal_B.lower_voltage_index) {
        matlab_semifinal_B.b_t = matlab_semifinal_B.lower_voltage_index;
      }
    }
  }

  if (matlab_semifinal_B.b_t > 0.17453292519943295) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = 2.0 *
        matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];
      matlab_semifinal_B.rtb_Cbi_tmp_b[3 * matlab_semifinal_B.i_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[0];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[1];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[2];
    }

    matlab_semifinal_B.Cbi_c[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.Cbi_c[1] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;
    matlab_semifinal_B.Cbi_c[2] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;
    matlab_semifinal_B.Cbi_c[3] = matlab_semifinal_B.rtb_Eul_idx_1;
    matlab_semifinal_B.Cbi_c[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.Cbi_c[5] = matlab_semifinal_B.rtb_Eul_idx_0;
    matlab_semifinal_B.Cbi_c[6] = matlab_semifinal_B.rtb_DeadZone_p_idx_0;
    matlab_semifinal_B.Cbi_c[7] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
    matlab_semifinal_B.Cbi_c[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o] +
        matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.lower_voltage_index = 0.0;
    matlab_semifinal_B.eta = 0.0;
    matlab_semifinal_B.rtb_delta_qe_idx_1 = 0.0;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.X_u[matlab_semifinal_B.i_o];
      matlab_semifinal_B.lower_voltage_index += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.eta += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.rtb_delta_qe_idx_1 += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.rtb_delta_qe_idx_1;
    matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.eta;
    matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.lower_voltage_index;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.eps[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o] -
        ((matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 3] *
          matlab_semifinal_B.b_absxk +
          matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] *
          matlab_semifinal_B.b_scale) +
         matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 6] *
         matlab_semifinal_B.rotm_tmp);
    }

    matlab_semifinal_B.eps_n[0] = 0.0;
    matlab_semifinal_B.eps_n[1] = 0.0;
    matlab_semifinal_B.eps_n[2] = matlab_semifinal_B.eps[2];
    matlab_semifinal_DW.action_id = 1.0;
  } else if (matlab_semifinal_B.rtb_delta_qe_idx_1 >= 0.5) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = 2.0 *
        matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];
      matlab_semifinal_B.Cbi_c[3 * matlab_semifinal_B.i_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[0];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[1];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[2];
    }

    matlab_semifinal_B.rtb_Cbi_tmp_b[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.rtb_Cbi_tmp_b[1] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[2] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;
    matlab_semifinal_B.rtb_Cbi_tmp_b[3] = matlab_semifinal_B.rtb_Eul_idx_1;
    matlab_semifinal_B.rtb_Cbi_tmp_b[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.rtb_Cbi_tmp_b[5] = matlab_semifinal_B.rtb_Eul_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[6] =
      matlab_semifinal_B.rtb_DeadZone_p_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[7] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
    matlab_semifinal_B.rtb_Cbi_tmp_b[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o] +
        matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.lower_voltage_index = 0.0;
    matlab_semifinal_B.eta = 0.0;
    matlab_semifinal_B.rtb_delta_qe_idx_1 = 0.0;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.X_u[matlab_semifinal_B.i_o];
      matlab_semifinal_B.lower_voltage_index += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.eta += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.rtb_delta_qe_idx_1 += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.rtb_delta_qe_idx_1;
    matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.eta;
    matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.lower_voltage_index;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.eps_n[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o] -
        ((matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 3] *
          matlab_semifinal_B.b_absxk +
          matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] *
          matlab_semifinal_B.b_scale) +
         matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 6] *
         matlab_semifinal_B.rotm_tmp);
    }

    matlab_semifinal_DW.action_id = 2.0;
  } else {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = 2.0 *
        matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];
      matlab_semifinal_B.Cbi_c[3 * matlab_semifinal_B.i_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[0];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[1];
      matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.k_o] =
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
        matlab_semifinal_B.X_est.qib[2];
    }

    matlab_semifinal_B.rtb_Cbi_tmp_b[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.rtb_Cbi_tmp_b[1] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[2] =
      matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;
    matlab_semifinal_B.rtb_Cbi_tmp_b[3] = matlab_semifinal_B.rtb_Eul_idx_1;
    matlab_semifinal_B.rtb_Cbi_tmp_b[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    matlab_semifinal_B.rtb_Cbi_tmp_b[5] = matlab_semifinal_B.rtb_Eul_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[6] =
      matlab_semifinal_B.rtb_DeadZone_p_idx_0;
    matlab_semifinal_B.rtb_Cbi_tmp_b[7] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
    matlab_semifinal_B.rtb_Cbi_tmp_b[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o] +
        matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.lower_voltage_index = 0.0;
    matlab_semifinal_B.eta = 0.0;
    matlab_semifinal_B.rtb_delta_qe_idx_1 = 0.0;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.b_t = matlab_semifinal_B.X_u[matlab_semifinal_B.i_o];
      matlab_semifinal_B.lower_voltage_index += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.eta += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.rtb_delta_qe_idx_1 += matlab_semifinal_B.Cbi[3 *
        matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.rtb_delta_qe_idx_1;
    matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.eta;
    matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.lower_voltage_index;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.eps_n[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o] -
        ((matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 3] *
          matlab_semifinal_B.b_absxk +
          matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o] *
          matlab_semifinal_B.b_scale) +
         matlab_semifinal_B.Cbi[matlab_semifinal_B.i_o + 6] *
         matlab_semifinal_B.rotm_tmp);
    }

    matlab_semifinal_DW.action_id = 3.0;
  }

  matlab_semifinal_DW.UnitDelay_DSTATE = matlab_semifinal_DW.action_id;
  matlab_semifinal_DW.UnitDelay1_DSTATE =
    matlab_semifinal_DW.persistant_yaw_target;
  matlab_semifinal_DW.prior_action_id_n = matlab_semifinal_DW.action_id;

  // Logic: '<S25>/OR' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read8'
  //   DataStoreWrite: '<S25>/Data Store Write1'
  //   RelationalOperator: '<S29>/FixPt Relational Operator'
  //   UnitDelay: '<S29>/Delay Input1'
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S29>/Delay Input1':
  //
  //   Store in Global RAM

  reset_pids = (((matlab_semifinal_DW.UnitDelay_DSTATE !=
                  matlab_semifinal_DW.DelayInput1_DSTATE) << 7 != 0) ||
                reset_pids);

  // MATLAB Function: '<S25>/quatInjector' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   UnitDelay: '<S4>/Unit Delay'

  matlab_semifinal_B.Rb_u[1] = matlab_semifinal_B.theta;
  matlab_semifinal_B.Rb_u[2] = matlab_semifinal_B.t;
  if ((matlab_semifinal_DW.UnitDelay_DSTATE == 2.0) ||
      (matlab_semifinal_DW.UnitDelay_DSTATE == 1.0)) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.x1[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.cmd.trick_id[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.i_o = std::memcmp(&a_1[0], &matlab_semifinal_B.x1[0], 16);
    if (matlab_semifinal_B.i_o == 0) {
      matlab_semifinal_B.Rb_u[0] = matlab_semifinal_B.norm_w + 3.1;
      matlab_semifinal_eulToQuat(matlab_semifinal_B.Rb_u,
        matlab_semifinal_B.qe_matlab);
    } else {
      matlab_semifinal_B.qe_matlab[0] = matlab_semifinal_B.qib_int_u[0];
      matlab_semifinal_B.qe_matlab[1] = matlab_semifinal_B.qib_int_u[1];
      matlab_semifinal_B.qe_matlab[2] = matlab_semifinal_B.qib_int_u[2];
      matlab_semifinal_B.qe_matlab[3] = matlab_semifinal_B.qib_int_u[3];
    }
  } else {
    matlab_semifinal_B.qe_matlab[0] = matlab_semifinal_B.qib_int_u[0];
    matlab_semifinal_B.qe_matlab[1] = matlab_semifinal_B.qib_int_u[1];
    matlab_semifinal_B.qe_matlab[2] = matlab_semifinal_B.qib_int_u[2];
    matlab_semifinal_B.qe_matlab[3] = matlab_semifinal_B.qib_int_u[3];
  }

  // End of MATLAB Function: '<S25>/quatInjector'

  // DiscreteIntegrator: '<S32>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'

  if (reset_pids && (matlab_semifinal_DW.DiscreteTimeIntegrator_PrevRese <= 0))
  {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0;
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0;
  }

  // MATLAB Function: '<S25>/deltaQuatError' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatPID'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'

  matlab_semifinal_B.b_t = ((matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qe_matlab[3] - -matlab_semifinal_B.X_est.qib[0] *
    matlab_semifinal_B.qe_matlab[0]) - -matlab_semifinal_B.X_est.qib[1] *
    matlab_semifinal_B.qe_matlab[1]) - -matlab_semifinal_B.X_est.qib[2] *
    matlab_semifinal_B.qe_matlab[2];
  matlab_semifinal_B.b_a_h = (matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qe_matlab[0] + matlab_semifinal_B.qe_matlab[3] *
    -matlab_semifinal_B.X_est.qib[0]) + (-matlab_semifinal_B.X_est.qib[1] *
    matlab_semifinal_B.qe_matlab[2] - matlab_semifinal_B.qe_matlab[1] *
    -matlab_semifinal_B.X_est.qib[2]);
  matlab_semifinal_B.eta = matlab_semifinal_B.b_a_h;
  matlab_semifinal_B.lower_voltage_index =
    (matlab_semifinal_B.rtb_delta_qe_idx_2 * matlab_semifinal_B.qe_matlab[1] +
     matlab_semifinal_B.qe_matlab[3] * -matlab_semifinal_B.X_est.qib[1]) +
    (matlab_semifinal_B.qe_matlab[0] * -matlab_semifinal_B.X_est.qib[2] -
     -matlab_semifinal_B.X_est.qib[0] * matlab_semifinal_B.qe_matlab[2]);
  matlab_semifinal_B.rtb_delta_qe_idx_1 = matlab_semifinal_B.lower_voltage_index;
  matlab_semifinal_B.eps_b = (matlab_semifinal_B.rtb_delta_qe_idx_2 *
    matlab_semifinal_B.qe_matlab[2] + matlab_semifinal_B.qe_matlab[3] *
    -matlab_semifinal_B.X_est.qib[2]) + (-matlab_semifinal_B.X_est.qib[0] *
    matlab_semifinal_B.qe_matlab[1] - matlab_semifinal_B.qe_matlab[0] *
    -matlab_semifinal_B.X_est.qib[1]);
  matlab_semifinal_B.rtb_delta_qe_idx_2 = matlab_semifinal_B.eps_b;
  matlab_semifinal_B.rtb_delta_qe_idx_3 = matlab_semifinal_B.b_t;
  if (matlab_semifinal_B.b_t < 0.0) {
    matlab_semifinal_B.eta = -matlab_semifinal_B.b_a_h;
    matlab_semifinal_B.rtb_delta_qe_idx_1 =
      -matlab_semifinal_B.lower_voltage_index;
    matlab_semifinal_B.rtb_delta_qe_idx_2 = -matlab_semifinal_B.eps_b;
    matlab_semifinal_B.rtb_delta_qe_idx_3 = -matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.new_waypoint_latch = false;
  if (std::isnan(matlab_semifinal_B.rtb_delta_qe_idx_3)) {
    matlab_semifinal_B.theta_b = (rtNaN);
  } else {
    matlab_semifinal_B.theta_b = (matlab_semifinal_B.rtb_delta_qe_idx_3 > 0.0);
  }

  if (matlab_semifinal_B.theta_b == 0.0) {
    matlab_semifinal_B.new_waypoint_latch = true;
  }

  if (!matlab_semifinal_B.new_waypoint_latch) {
    matlab_semifinal_B.eta *= matlab_semifinal_B.theta_b;
    matlab_semifinal_B.rtb_delta_qe_idx_1 *= matlab_semifinal_B.theta_b;
    matlab_semifinal_B.rtb_delta_qe_idx_2 *= matlab_semifinal_B.theta_b;
    matlab_semifinal_B.rtb_delta_qe_idx_3 *= matlab_semifinal_B.theta_b;
  }

  // SignalConversion generated from: '<S25>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_B.qe_matlab_g[0] = 1.0 -
    matlab_semifinal_B.rtb_delta_qe_idx_3;
  matlab_semifinal_B.qe_matlab_g[1] = 0.0 - matlab_semifinal_B.eta;
  matlab_semifinal_B.qe_matlab_g[2] = 0.0 -
    matlab_semifinal_B.rtb_delta_qe_idx_1;
  matlab_semifinal_B.qe_matlab_g[3] = 0.0 -
    matlab_semifinal_B.rtb_delta_qe_idx_2;

  // DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_B.eps_tmp = ((1.0 - matlab_semifinal_B.rtb_delta_qe_idx_3) -
    (-matlab_semifinal_DW.DiscreteTransferFcn_states[0])) / 1.1;
  matlab_semifinal_B.scale = matlab_semifinal_B.eps_tmp;
  matlab_semifinal_B.DiscreteTransferFcn[0] = 10.0 * matlab_semifinal_B.eps_tmp
    + -10.0 * matlab_semifinal_DW.DiscreteTransferFcn_states[0];
  matlab_semifinal_B.eps_tmp = ((0.0 - matlab_semifinal_B.eta) -
    (-matlab_semifinal_DW.DiscreteTransferFcn_states[1])) / 1.1;
  matlab_semifinal_B.absxk = matlab_semifinal_B.eps_tmp;
  matlab_semifinal_B.DiscreteTransferFcn[1] = 10.0 * matlab_semifinal_B.eps_tmp
    + -10.0 * matlab_semifinal_DW.DiscreteTransferFcn_states[1];
  matlab_semifinal_B.eps_tmp = ((0.0 - matlab_semifinal_B.rtb_delta_qe_idx_1) -
    (-matlab_semifinal_DW.DiscreteTransferFcn_states[2])) / 1.1;
  matlab_semifinal_B.DiscreteTransferFcn_tmp_idx_2 = matlab_semifinal_B.eps_tmp;
  matlab_semifinal_B.DiscreteTransferFcn[2] = 10.0 * matlab_semifinal_B.eps_tmp
    + -10.0 * matlab_semifinal_DW.DiscreteTransferFcn_states[2];
  matlab_semifinal_B.eps_tmp = ((0.0 - matlab_semifinal_B.rtb_delta_qe_idx_2) -
    (-matlab_semifinal_DW.DiscreteTransferFcn_states[3])) / 1.1;
  matlab_semifinal_B.DiscreteTransferFcn[3] = 10.0 * matlab_semifinal_B.eps_tmp
    + -10.0 * matlab_semifinal_DW.DiscreteTransferFcn_states[3];

  // MATLAB Function: '<S25>/quatPID' incorporates:
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'
  //   Gain: '<S25>/Gain1'
  //   Gain: '<S25>/Gain2'
  //   SignalConversion generated from: '<S25>/Discrete Transfer Fcn'

  matlab_semifinal_B.qinv[0] = matlab_semifinal_B.b_a_h;
  matlab_semifinal_B.qinv[1] = matlab_semifinal_B.lower_voltage_index;
  matlab_semifinal_B.qinv[2] = matlab_semifinal_B.eps_b;
  matlab_semifinal_B.qinv[3] = matlab_semifinal_B.b_t;
  if (matlab_semifinal_B.b_t < 0.0) {
    matlab_semifinal_B.qinv[0] = -matlab_semifinal_B.b_a_h;
    matlab_semifinal_B.qinv[1] = -matlab_semifinal_B.lower_voltage_index;
    matlab_semifinal_B.qinv[2] = -matlab_semifinal_B.eps_b;
    matlab_semifinal_B.qinv[3] = -matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.Qe1[0] = -matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[4] = -matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[8] = -matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[1] = matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.Qe1[5] = -matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[9] = matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[2] = matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[6] = matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.Qe1[10] = -matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[3] = -matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[7] = matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[11] = matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.b_a_h = 0.0;
  matlab_semifinal_B.lower_voltage_index = 0.0;
  matlab_semifinal_B.eps_b = 0.0;
  matlab_semifinal_B.theta_b = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 4;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.pwms_horiz_idx_1 = 0.0;
    matlab_semifinal_B.pwms_horiz_idx_2 = 0.0;
    matlab_semifinal_B.pwms_horiz_idx_3 = 0.0;
    matlab_semifinal_B.Qe1_e = 0.0;
    for (matlab_semifinal_B.k_o = 0; matlab_semifinal_B.k_o < 3;
         matlab_semifinal_B.k_o++) {
      matlab_semifinal_B.pos = matlab_semifinal_B.k_o << 2;
      matlab_semifinal_B.b_t = matlab_semifinal_B.Qe1[matlab_semifinal_B.pos +
        matlab_semifinal_B.i_o];
      matlab_semifinal_B.pwms_horiz_idx_1 +=
        matlab_semifinal_B.Qe1[matlab_semifinal_B.pos] * matlab_semifinal_B.b_t;
      matlab_semifinal_B.pwms_horiz_idx_2 +=
        matlab_semifinal_B.Qe1[matlab_semifinal_B.pos + 1] *
        matlab_semifinal_B.b_t;
      matlab_semifinal_B.pwms_horiz_idx_3 +=
        matlab_semifinal_B.Qe1[matlab_semifinal_B.pos + 2] *
        matlab_semifinal_B.b_t;
      matlab_semifinal_B.Qe1_e += matlab_semifinal_B.Qe1[matlab_semifinal_B.pos
        + 3] * matlab_semifinal_B.b_t;
    }

    matlab_semifinal_B.k_o = matlab_semifinal_B.i_o << 2;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 3] =
      matlab_semifinal_B.Qe1_e;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 2] =
      matlab_semifinal_B.pwms_horiz_idx_3;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 1] =
      matlab_semifinal_B.pwms_horiz_idx_2;
    matlab_semifinal_B.c_a[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.pwms_horiz_idx_1;
    matlab_semifinal_B.dv1[matlab_semifinal_B.i_o] =
      (matlab_semifinal_ConstP.Gain1_Gain[matlab_semifinal_B.i_o] *
       matlab_semifinal_B.qe_matlab_g[matlab_semifinal_B.i_o] + 0.0 *
       matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[matlab_semifinal_B.i_o])
      + matlab_semifinal_B.DiscreteTransferFcn[matlab_semifinal_B.i_o];
    matlab_semifinal_B.b_t = matlab_semifinal_B.dv1[matlab_semifinal_B.i_o];
    matlab_semifinal_B.b_a_h += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.lower_voltage_index +=
      matlab_semifinal_B.c_a[matlab_semifinal_B.k_o + 1] *
      matlab_semifinal_B.b_t;
    matlab_semifinal_B.eps_b += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o +
      2] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.theta_b += matlab_semifinal_B.c_a[matlab_semifinal_B.k_o
      + 3] * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.Qe1[0] = matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[1] = matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[2] = matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[3] = -matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.Qe1[4] = -matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[5] = matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[6] = matlab_semifinal_B.qinv[2];
  matlab_semifinal_B.Qe1[7] = -matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.Qe1[8] = -matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[9] = -matlab_semifinal_B.qinv[1];
  matlab_semifinal_B.Qe1[10] = matlab_semifinal_B.qinv[0];
  matlab_semifinal_B.Qe1[11] = -matlab_semifinal_B.qinv[3];
  matlab_semifinal_B.dv1[0] = 2.0 * matlab_semifinal_B.b_a_h;
  matlab_semifinal_B.dv1[1] = 2.0 * matlab_semifinal_B.lower_voltage_index;
  matlab_semifinal_B.dv1[2] = 2.0 * matlab_semifinal_B.eps_b;
  matlab_semifinal_B.dv1[3] = 2.0 * matlab_semifinal_B.theta_b;
  matlab_semifinal_B.b_a_h = 0.0;
  matlab_semifinal_B.eps_b = 0.0;
  matlab_semifinal_B.lower_voltage_index = 0.0;
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 4;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.dv1[matlab_semifinal_B.i_o];
    matlab_semifinal_B.b_a_h += matlab_semifinal_B.Qe1[3 *
      matlab_semifinal_B.i_o] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.eps_b += matlab_semifinal_B.Qe1[3 *
      matlab_semifinal_B.i_o + 1] * matlab_semifinal_B.b_t;
    matlab_semifinal_B.lower_voltage_index += matlab_semifinal_B.Qe1[3 *
      matlab_semifinal_B.i_o + 2] * matlab_semifinal_B.b_t;
  }

  matlab_semifinal_B.eps_p[2] = matlab_semifinal_B.lower_voltage_index;
  matlab_semifinal_B.eps_p[1] = matlab_semifinal_B.eps_b;
  matlab_semifinal_B.eps_p[0] = matlab_semifinal_B.b_a_h;

  // DiscreteIntegrator: '<S139>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read1'

  if (reset_pids && (matlab_semifinal_DW.Integrator_PrevResetState <= 0)) {
    matlab_semifinal_DW.Integrator_DSTATE[0] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE[1] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE[2] = 0.0;
  }

  // DiscreteIntegrator: '<S134>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read1'

  if (reset_pids && (matlab_semifinal_DW.Filter_PrevResetState <= 0)) {
    matlab_semifinal_DW.Filter_DSTATE[0] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE[1] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE[2] = 0.0;
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    // Gain: '<S132>/Derivative Gain'
    matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps_n[matlab_semifinal_B.i_o];

    // Gain: '<S142>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S134>/Filter'
    //   Gain: '<S132>/Derivative Gain'
    //   Sum: '<S134>/SumD'

    matlab_semifinal_B.lower_voltage_index = (0.0 * matlab_semifinal_B.b_a_h -
      matlab_semifinal_DW.Filter_DSTATE[matlab_semifinal_B.i_o]) * 100.0;
    matlab_semifinal_B.Rb_u[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.lower_voltage_index;

    // Sum: '<S148>/Sum' incorporates:
    //   DeadZone: '<S131>/DeadZone'
    //   DiscreteIntegrator: '<S139>/Integrator'
    //   Gain: '<S142>/Filter Coefficient'
    //   Gain: '<S144>/Proportional Gain'

    matlab_semifinal_B.b_a_h =
      (matlab_semifinal_ConstP.ProportionalGain_Gain[matlab_semifinal_B.i_o] *
       matlab_semifinal_B.b_a_h +
       matlab_semifinal_DW.Integrator_DSTATE[matlab_semifinal_B.i_o]) +
      matlab_semifinal_B.lower_voltage_index;
    matlab_semifinal_B.eps[matlab_semifinal_B.i_o] = matlab_semifinal_B.b_a_h;

    // Saturate: '<S146>/Saturation'
    if (matlab_semifinal_B.b_a_h > 1.0) {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      matlab_semifinal_B.dRb_u[matlab_semifinal_B.i_o] = 1.0;
    } else if (matlab_semifinal_B.b_a_h < -1.0) {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      matlab_semifinal_B.dRb_u[matlab_semifinal_B.i_o] = -1.0;
    } else {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      matlab_semifinal_B.dRb_u[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.b_a_h;
    }

    // End of Saturate: '<S146>/Saturation'

    // MATLAB Function: '<S25>/quatToRotm' incorporates:
    //   DataStoreRead: '<S25>/Data Store Read'
    //   DataStoreWrite: '<S25>/Data Store Write'
    //   Math: '<S25>/Transpose'

    matlab_semifinal_B.b_t = 2.0 *
      matlab_semifinal_B.X_est.qib[matlab_semifinal_B.i_o];
    matlab_semifinal_B.rtb_Cbi_tmp_b[3 * matlab_semifinal_B.i_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[3 * matlab_semifinal_B.i_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
      matlab_semifinal_B.X_est.qib[0];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
      matlab_semifinal_B.X_est.qib[1];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.k_o] =
      matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.k_o] *
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 + matlab_semifinal_B.b_t *
      matlab_semifinal_B.X_est.qib[2];
  }

  // Math: '<S25>/Transpose'
  matlab_semifinal_B.Cbi_c[0] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.Cbi_c[1] = matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;
  matlab_semifinal_B.Cbi_c[2] = matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;
  matlab_semifinal_B.Cbi_c[3] = matlab_semifinal_B.rtb_Eul_idx_1;
  matlab_semifinal_B.Cbi_c[4] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.Cbi_c[5] = matlab_semifinal_B.rtb_Eul_idx_0;
  matlab_semifinal_B.Cbi_c[6] = matlab_semifinal_B.rtb_DeadZone_p_idx_0;
  matlab_semifinal_B.Cbi_c[7] = matlab_semifinal_B.rtb_Cbi_tmp_tmp_f;
  matlab_semifinal_B.Cbi_c[8] = matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // MATLAB Function: '<S25>/quatToRotm'
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 9;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.rtb_Cbi_tmp_b[matlab_semifinal_B.i_o] +
      matlab_semifinal_B.Cbi_c[matlab_semifinal_B.i_o];
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    // Sum: '<S25>/Subtract4' incorporates:
    //   MATLAB Function: '<S6>/derivedStateEstimates'
    //   Product: '<S25>/Matrix Multiply3'

    matlab_semifinal_B.dRb_e[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.dRb_u[matlab_semifinal_B.i_o] -
      ((matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o + 3] *
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 +
        matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o] *
        matlab_semifinal_B.phi) +
       matlab_semifinal_B.rtb_sensors_dvl_cov[matlab_semifinal_B.i_o + 6] *
       matlab_semifinal_B.upper_voltage_index);

    // MATLAB Function: '<S25>/rateInjector' incorporates:
    //   SignalConversion generated from: '<S25>/Bus Selector'
    //   Sum: '<S25>/Subtract'

    matlab_semifinal_B.eps_p[matlab_semifinal_B.i_o] -=
      matlab_semifinal_B.X_est.wb[matlab_semifinal_B.i_o];
  }

  // MATLAB Function: '<S25>/rateInjector' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S25>/trickFTListInjector'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   Product: '<S6>/Matrix Multiply2'

  matlab_semifinal_B.new_waypoint_latch = matlab_semifinal_isequal
    (matlab_semifinal_B.s);
  if (matlab_semifinal_B.new_waypoint_latch) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.x1[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.cmd.trick_id[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.i_o = std::memcmp(&a_2[0], &matlab_semifinal_B.x1[0], 16);
    if (matlab_semifinal_B.i_o == 0) {
      matlab_semifinal_B.i_o = 0;
    } else {
      matlab_semifinal_B.i_o = std::memcmp(&b_a_1[0], &matlab_semifinal_B.x1[0],
        16);
      if (matlab_semifinal_B.i_o == 0) {
        matlab_semifinal_B.i_o = 1;
      } else {
        matlab_semifinal_B.i_o = std::memcmp(&c_a_1[0], &matlab_semifinal_B.x1[0],
          16);
        if (matlab_semifinal_B.i_o == 0) {
          matlab_semifinal_B.i_o = 2;
        } else {
          matlab_semifinal_B.i_o = std::memcmp(&d_a_0[0],
            &matlab_semifinal_B.x1[0], 16);
          if (matlab_semifinal_B.i_o == 0) {
            matlab_semifinal_B.i_o = 3;
          } else {
            matlab_semifinal_B.i_o = std::memcmp(&e_a[0],
              &matlab_semifinal_B.x1[0], 16);
            if (matlab_semifinal_B.i_o == 0) {
              matlab_semifinal_B.i_o = 4;
            } else {
              matlab_semifinal_B.i_o = std::memcmp(&f_a[0],
                &matlab_semifinal_B.x1[0], 16);
              if (matlab_semifinal_B.i_o == 0) {
                matlab_semifinal_B.i_o = 5;
              } else {
                matlab_semifinal_B.i_o = std::memcmp(&g_a[0],
                  &matlab_semifinal_B.x1[0], 16);
                if (matlab_semifinal_B.i_o == 0) {
                  matlab_semifinal_B.i_o = 6;
                } else {
                  matlab_semifinal_B.i_o = std::memcmp(&h_a[0],
                    &matlab_semifinal_B.x1[0], 16);
                  if (matlab_semifinal_B.i_o == 0) {
                    matlab_semifinal_B.i_o = 7;
                  } else {
                    matlab_semifinal_B.i_o = std::memcmp(&i_a[0],
                      &matlab_semifinal_B.x1[0], 16);
                    if (matlab_semifinal_B.i_o == 0) {
                      matlab_semifinal_B.i_o = 8;
                    } else {
                      matlab_semifinal_B.i_o = std::memcmp(&j_a[0],
                        &matlab_semifinal_B.x1[0], 16);
                      if (matlab_semifinal_B.i_o == 0) {
                        matlab_semifinal_B.i_o = 9;
                      } else if (matlab_semifinal_strcmp(matlab_semifinal_B.x1))
                      {
                        matlab_semifinal_B.i_o = 10;
                      } else if (matlab_semifinal_strcmp_b(matlab_semifinal_B.x1))
                      {
                        matlab_semifinal_B.i_o = 11;
                      } else if (matlab_semifinal_strcmp_b5
                                 (matlab_semifinal_B.x1)) {
                        matlab_semifinal_B.i_o = 12;
                      } else {
                        matlab_semifinal_B.i_o = -1;
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

    switch (matlab_semifinal_B.i_o) {
     case 0:
      matlab_semifinal_B.dRb_e[0] = 0.5 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 1:
      matlab_semifinal_B.dRb_e[0] = -0.5 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 2:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = -1.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 3:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 1.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 4:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 1.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 5:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = -1.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 6:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 1.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 7:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = -1.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 8:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 1.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 9:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = -1.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 10:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 1.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 11:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = -1.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;

     case 12:
      matlab_semifinal_B.dRb_e[0] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];
      matlab_semifinal_B.eps_p[0] = 0.0 - matlab_semifinal_B.rtb_dRb_u_d;
      matlab_semifinal_B.dRb_e[1] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];
      matlab_semifinal_B.eps_p[1] = 0.0 - matlab_semifinal_B.rtb_X_est_wb;
      matlab_semifinal_B.dRb_e[2] = 0.0 -
        matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];
      matlab_semifinal_B.eps_p[2] = 0.0 - matlab_semifinal_B.rtb_X_est_wb_j;
      break;
    }
  }

  // DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read7'

  if (reset_pids && (matlab_semifinal_DW.Integrator_PrevResetState_d <= 0)) {
    matlab_semifinal_DW.Integrator_DSTATE_m[0] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE_m[1] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE_m[2] = 0.0;
  }

  // DiscreteIntegrator: '<S78>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read7'

  if (reset_pids && (matlab_semifinal_DW.Filter_PrevResetState_g <= 0)) {
    matlab_semifinal_DW.Filter_DSTATE_d[0] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE_d[1] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE_d[2] = 0.0;
  }

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S76>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  matlab_semifinal_B.rtb_dRb_u_d = (0.0 * matlab_semifinal_B.eps_p[0] -
    matlab_semifinal_DW.Filter_DSTATE_d[0]) * 100.0;
  matlab_semifinal_B.dRb_u[0] = matlab_semifinal_B.rtb_dRb_u_d;

  // Sum: '<S92>/Sum' incorporates:
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S76>/Derivative Gain'

  matlab_semifinal_B.rtb_DeadZone_p_idx_0 = (matlab_semifinal_B.eps_p[0] +
    matlab_semifinal_DW.Integrator_DSTATE_m[0]) + matlab_semifinal_B.rtb_dRb_u_d;

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S76>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  matlab_semifinal_B.rtb_dRb_u_d = (0.0 * matlab_semifinal_B.eps_p[1] -
    matlab_semifinal_DW.Filter_DSTATE_d[1]) * 100.0;
  matlab_semifinal_B.dRb_u[1] = matlab_semifinal_B.rtb_dRb_u_d;

  // Gain: '<S88>/Proportional Gain' incorporates:
  //   Gain: '<S76>/Derivative Gain'
  //   Gain: '<S80>/Integral Gain'

  matlab_semifinal_B.rtb_X_est_wb = 5.0 * matlab_semifinal_B.eps_p[1];

  // Sum: '<S92>/Sum' incorporates:
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S88>/Proportional Gain'

  matlab_semifinal_B.rtb_DeadZone_p_idx_1 = (matlab_semifinal_B.rtb_X_est_wb +
    matlab_semifinal_DW.Integrator_DSTATE_m[1]) + matlab_semifinal_B.rtb_dRb_u_d;

  // Gain: '<S86>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S78>/Filter'
  //   Gain: '<S76>/Derivative Gain'
  //   Sum: '<S78>/SumD'

  matlab_semifinal_B.rtb_dRb_u_d = (0.0 * matlab_semifinal_B.eps_p[2] -
    matlab_semifinal_DW.Filter_DSTATE_d[2]) * 100.0;

  // Gain: '<S88>/Proportional Gain' incorporates:
  //   Gain: '<S76>/Derivative Gain'
  //   Gain: '<S80>/Integral Gain'

  matlab_semifinal_B.rtb_X_est_wb_j = 5.0 * matlab_semifinal_B.eps_p[2];

  // Sum: '<S92>/Sum' incorporates:
  //   DiscreteIntegrator: '<S83>/Integrator'
  //   Gain: '<S88>/Proportional Gain'

  matlab_semifinal_B.rtb_DeadZone_p_idx_2 = (matlab_semifinal_B.rtb_X_est_wb_j +
    matlab_semifinal_DW.Integrator_DSTATE_m[2]) + matlab_semifinal_B.rtb_dRb_u_d;

  // DiscreteIntegrator: '<S198>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read9'

  if (reset_pids && (matlab_semifinal_DW.Integrator_PrevResetState_p <= 0)) {
    matlab_semifinal_DW.Integrator_DSTATE_d[0] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE_d[1] = 0.0;
    matlab_semifinal_DW.Integrator_DSTATE_d[2] = 0.0;
  }

  // DiscreteIntegrator: '<S193>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read9'

  if (reset_pids && (matlab_semifinal_DW.Filter_PrevResetState_k <= 0)) {
    matlab_semifinal_DW.Filter_DSTATE_c[0] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE_c[1] = 0.0;
    matlab_semifinal_DW.Filter_DSTATE_c[2] = 0.0;
  }

  // Gain: '<S201>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S193>/Filter'
  //   Gain: '<S191>/Derivative Gain'
  //   Sum: '<S193>/SumD'

  matlab_semifinal_B.rtb_Cbi_tmp_tmp = (0.0 * matlab_semifinal_B.dRb_e[0] -
    matlab_semifinal_DW.Filter_DSTATE_c[0]) * 100.0;
  matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0 =
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // Sum: '<S207>/Sum' incorporates:
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   Gain: '<S191>/Derivative Gain'
  //   Gain: '<S203>/Proportional Gain'

  matlab_semifinal_B.phi = (60.0 * matlab_semifinal_B.dRb_e[0] +
    matlab_semifinal_DW.Integrator_DSTATE_d[0]) +
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.rtb_Eul_idx_0 = matlab_semifinal_B.phi;

  // Saturate: '<S90>/Saturation'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 > 10.0) {
    matlab_semifinal_B.dv3[0] = 10.0;
  } else if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 < -10.0) {
    matlab_semifinal_B.dv3[0] = -10.0;
  } else {
    matlab_semifinal_B.dv3[0] = matlab_semifinal_B.rtb_DeadZone_p_idx_0;
  }

  // Saturate: '<S205>/Saturation'
  if (matlab_semifinal_B.phi > 100.0) {
    matlab_semifinal_B.dv4[0] = 100.0;
  } else if (matlab_semifinal_B.phi < -100.0) {
    matlab_semifinal_B.dv4[0] = -100.0;
  } else {
    matlab_semifinal_B.dv4[0] = matlab_semifinal_B.phi;
  }

  // Gain: '<S201>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S193>/Filter'
  //   Gain: '<S191>/Derivative Gain'
  //   Sum: '<S193>/SumD'

  matlab_semifinal_B.rtb_Cbi_tmp_tmp = (0.0 * matlab_semifinal_B.dRb_e[1] -
    matlab_semifinal_DW.Filter_DSTATE_c[1]) * 100.0;
  matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1 =
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // Sum: '<S207>/Sum' incorporates:
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   Gain: '<S191>/Derivative Gain'
  //   Gain: '<S203>/Proportional Gain'

  matlab_semifinal_B.phi = (60.0 * matlab_semifinal_B.dRb_e[1] +
    matlab_semifinal_DW.Integrator_DSTATE_d[1]) +
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_B.rtb_Eul_idx_1 = matlab_semifinal_B.phi;

  // Saturate: '<S90>/Saturation'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 > 10.0) {
    matlab_semifinal_B.dv3[1] = 10.0;
  } else if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 < -10.0) {
    matlab_semifinal_B.dv3[1] = -10.0;
  } else {
    matlab_semifinal_B.dv3[1] = matlab_semifinal_B.rtb_DeadZone_p_idx_1;
  }

  // Saturate: '<S205>/Saturation'
  if (matlab_semifinal_B.phi > 100.0) {
    matlab_semifinal_B.dv4[1] = 100.0;
  } else if (matlab_semifinal_B.phi < -100.0) {
    matlab_semifinal_B.dv4[1] = -100.0;
  } else {
    matlab_semifinal_B.dv4[1] = matlab_semifinal_B.phi;
  }

  // Gain: '<S201>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S193>/Filter'
  //   Gain: '<S191>/Derivative Gain'
  //   Sum: '<S193>/SumD'

  matlab_semifinal_B.rtb_Cbi_tmp_tmp = (0.0 * matlab_semifinal_B.dRb_e[2] -
    matlab_semifinal_DW.Filter_DSTATE_c[2]) * 100.0;

  // Sum: '<S207>/Sum' incorporates:
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   Gain: '<S191>/Derivative Gain'
  //   Gain: '<S203>/Proportional Gain'

  matlab_semifinal_B.phi = (100.0 * matlab_semifinal_B.dRb_e[2] +
    matlab_semifinal_DW.Integrator_DSTATE_d[2]) +
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;

  // Saturate: '<S90>/Saturation'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_2 > 10.0) {
    matlab_semifinal_B.dv3[2] = 10.0;
  } else if (matlab_semifinal_B.rtb_DeadZone_p_idx_2 < -10.0) {
    matlab_semifinal_B.dv3[2] = -10.0;
  } else {
    matlab_semifinal_B.dv3[2] = matlab_semifinal_B.rtb_DeadZone_p_idx_2;
  }

  // Saturate: '<S205>/Saturation'
  if (matlab_semifinal_B.phi > 100.0) {
    matlab_semifinal_B.dv4[2] = 100.0;
  } else if (matlab_semifinal_B.phi < -100.0) {
    matlab_semifinal_B.dv4[2] = -100.0;
  } else {
    matlab_semifinal_B.dv4[2] = matlab_semifinal_B.phi;
  }

  // Product: '<S25>/Matrix Multiply' incorporates:
  //   Constant: '<S25>/Constant'

  std::memset(&matlab_semifinal_B.pwms[0], 0, sizeof(real_T) << 3U);
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.dv3[matlab_semifinal_B.i_o];
    for (matlab_semifinal_B.k_o = 0; matlab_semifinal_B.k_o < 8;
         matlab_semifinal_B.k_o++) {
      matlab_semifinal_B.pwms[matlab_semifinal_B.k_o] +=
        matlab_semifinal_ConstP.Constant_Value_i[(matlab_semifinal_B.i_o << 3) +
        matlab_semifinal_B.k_o] * matlab_semifinal_B.b_t;
    }
  }

  // End of Product: '<S25>/Matrix Multiply'

  // Product: '<S25>/Matrix Multiply1' incorporates:
  //   Constant: '<S25>/Constant1'

  std::memset(&matlab_semifinal_B.dv[0], 0, sizeof(real_T) << 3U);
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.b_t = matlab_semifinal_B.dv4[matlab_semifinal_B.i_o];
    for (matlab_semifinal_B.k_o = 0; matlab_semifinal_B.k_o < 8;
         matlab_semifinal_B.k_o++) {
      matlab_semifinal_B.dv[matlab_semifinal_B.k_o] +=
        matlab_semifinal_ConstP.Constant1_Value[(matlab_semifinal_B.i_o << 3) +
        matlab_semifinal_B.k_o] * matlab_semifinal_B.b_t;
    }
  }

  // End of Product: '<S25>/Matrix Multiply1'

  // MATLAB Function: '<S25>/thrusterAllocator'
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 8;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.i_o] =
      matlab_semifinal_B.pwms[matlab_semifinal_B.i_o] +
      matlab_semifinal_B.dv[matlab_semifinal_B.i_o];
  }

  // End of MATLAB Function: '<S25>/thrusterAllocator'

  // MATLAB Function: '<S25>/trickFTListInjector'
  matlab_semifinal_B.dropper_trigger = false;
  if (matlab_semifinal_B.new_waypoint_latch) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.s[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.cmd.trick_id[matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.i_o = std::memcmp(&a_3[0], &matlab_semifinal_B.s[0], 16);
    if (matlab_semifinal_B.i_o == 0) {
      matlab_semifinal_B.i_o = 0;
    } else {
      matlab_semifinal_B.i_o = std::memcmp(&b_a_2[0], &matlab_semifinal_B.s[0],
        16);
      if (matlab_semifinal_B.i_o == 0) {
        matlab_semifinal_B.i_o = 1;
      } else {
        matlab_semifinal_B.i_o = std::memcmp(&c_a_2[0], &matlab_semifinal_B.s[0],
          16);
        if (matlab_semifinal_B.i_o == 0) {
          matlab_semifinal_B.i_o = 2;
        } else {
          matlab_semifinal_B.i_o = std::memcmp(&d_a_1[0], &matlab_semifinal_B.s
            [0], 16);
          if (matlab_semifinal_B.i_o == 0) {
            matlab_semifinal_B.i_o = 3;
          } else {
            matlab_semifinal_B.i_o = std::memcmp(&e_a_0[0],
              &matlab_semifinal_B.s[0], 16);
            if (matlab_semifinal_B.i_o == 0) {
              matlab_semifinal_B.i_o = 4;
            } else {
              matlab_semifinal_B.i_o = std::memcmp(&f_a_0[0],
                &matlab_semifinal_B.s[0], 16);
              if (matlab_semifinal_B.i_o == 0) {
                matlab_semifinal_B.i_o = 5;
              } else {
                matlab_semifinal_B.i_o = std::memcmp(&g_a_0[0],
                  &matlab_semifinal_B.s[0], 16);
                if (matlab_semifinal_B.i_o == 0) {
                  matlab_semifinal_B.i_o = 6;
                } else {
                  matlab_semifinal_B.i_o = std::memcmp(&h_a_0[0],
                    &matlab_semifinal_B.s[0], 16);
                  if (matlab_semifinal_B.i_o == 0) {
                    matlab_semifinal_B.i_o = 7;
                  } else {
                    matlab_semifinal_B.i_o = std::memcmp(&i_a_0[0],
                      &matlab_semifinal_B.s[0], 16);
                    if (matlab_semifinal_B.i_o == 0) {
                      matlab_semifinal_B.i_o = 8;
                    } else {
                      matlab_semifinal_B.i_o = std::memcmp(&j_a_0[0],
                        &matlab_semifinal_B.s[0], 16);
                      if (matlab_semifinal_B.i_o == 0) {
                        matlab_semifinal_B.i_o = 9;
                      } else {
                        matlab_semifinal_B.i_o = std::memcmp(&k_a[0],
                          &matlab_semifinal_B.s[0], 16);
                        if (matlab_semifinal_B.i_o == 0) {
                          matlab_semifinal_B.i_o = 10;
                        } else {
                          matlab_semifinal_B.i_o = std::memcmp(&l_a[0],
                            &matlab_semifinal_B.s[0], 16);
                          if (matlab_semifinal_B.i_o == 0) {
                            matlab_semifinal_B.i_o = 11;
                          } else if (matlab_semifinal_strcmp_l
                                     (matlab_semifinal_B.s)) {
                            matlab_semifinal_B.i_o = 12;
                          } else if (matlab_semifinal_strcmp_lp
                                     (matlab_semifinal_B.s)) {
                            matlab_semifinal_B.i_o = 13;
                          } else {
                            matlab_semifinal_B.i_o = -1;
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

    switch (matlab_semifinal_B.i_o) {
     case 0:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.forward
                  [0], sizeof(real_T) << 3U);
      break;

     case 1:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.backward
                  [0], sizeof(real_T) << 3U);
      break;

     case 2:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.up[0],
                  sizeof(real_T) << 3U);
      break;

     case 3:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.down
                  [0], sizeof(real_T) << 3U);
      break;

     case 4:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.left
                  [0], sizeof(real_T) << 3U);
      break;

     case 5:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.right[
                  0], sizeof(real_T) << 3U);
      break;

     case 6:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.pitchUp
                  [0], sizeof(real_T) << 3U);
      break;

     case 7:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.pitchDown
                  [0], sizeof(real_T) << 3U);
      break;

     case 8:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.yawRight
                  [0], sizeof(real_T) << 3U);
      break;

     case 9:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.yawLeft
                  [0], sizeof(real_T) << 3U);
      break;

     case 10:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.rollRight
                  [0], sizeof(real_T) << 3U);
      break;

     case 11:
      std::memcpy(&matlab_semifinal_B.FT_cmd_list[0],
                  &matlab_semifinal_ConstP.trickFTListInjector_FF_maneuver.rollLeft
                  [0], sizeof(real_T) << 3U);
      break;

     case 12:
      std::memset(&matlab_semifinal_B.FT_cmd_list[0], 0, sizeof(real_T) << 3U);
      break;

     case 13:
      std::memset(&matlab_semifinal_B.FT_cmd_list[0], 0, sizeof(real_T) << 3U);
      matlab_semifinal_B.dropper_trigger = true;
      break;
    }
  } else if (matlab_semifinal_isequal_hj(matlab_semifinal_B.s)) {
    std::memset(&matlab_semifinal_B.FT_cmd_list[0], 0, sizeof(real_T) << 3U);
  } else if ((!matlab_semifinal_isequal_hj4(matlab_semifinal_B.s)) &&
             (!matlab_semifinal_isequal_hj43(matlab_semifinal_B.s)) &&
             (!matlab_semifinal_isequal_hj43r(matlab_semifinal_B.s)) &&
             (!matlab_semifinal_isequal_hj43rz(matlab_semifinal_B.s))) {
    std::memset(&matlab_semifinal_B.FT_cmd_list[0], 0, sizeof(real_T) << 3U);
  }

  // MATLAB Function: '<S33>/Dropper Magazine' incorporates:
  //   RelationalOperator: '<S101>/Compare'
  //   RelationalOperator: '<S30>/FixPt Relational Operator'
  //   UnitDelay: '<S30>/Delay Input1'
  //
  //  Block description for '<S30>/Delay Input1':
  //
  //   Store in Global RAM

  if ((static_cast<int32_T>(matlab_semifinal_B.dropper_trigger) > static_cast<
       int32_T>(matlab_semifinal_DW.DelayInput1_DSTATE_g)) &&
      (matlab_semifinal_DW.ammo > 0.0)) {
    matlab_semifinal_B.b_t = std::round(matlab_semifinal_DW.ammo);
    if (matlab_semifinal_B.b_t < 256.0) {
      rtb_trigger_msg.data = static_cast<uint8_T>(matlab_semifinal_B.b_t);
    } else {
      rtb_trigger_msg.data = MAX_uint8_T;
    }

    matlab_semifinal_DW.ammo--;

    // Outputs for Enabled SubSystem: '<S33>/Subsystem' incorporates:
    //   EnablePort: '<S159>/Enable'

    // MATLABSystem: '<S160>/SinkBlock'
    Pub_matlab_semifinal_588_262_826_2.publish(&rtb_trigger_msg);

    // End of Outputs for SubSystem: '<S33>/Subsystem'
  }

  // End of MATLAB Function: '<S33>/Dropper Magazine'

  // DeadZone: '<S75>/DeadZone'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 > 10.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 -= 10.0;

    // Switch: '<S73>/Switch1' incorporates:
    //   Constant: '<S73>/Constant'

    tmp_0 = 1;
  } else {
    if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 >= -10.0) {
      matlab_semifinal_B.rtb_DeadZone_p_idx_0 = 0.0;
    } else {
      matlab_semifinal_B.rtb_DeadZone_p_idx_0 -= -10.0;
    }

    // Switch: '<S73>/Switch1' incorporates:
    //   Constant: '<S73>/Constant2'

    tmp_0 = -1;
  }

  // Switch: '<S73>/Switch2' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant3'
  //   Constant: '<S73>/Constant4'
  //   Gain: '<S80>/Integral Gain'
  //   RelationalOperator: '<S73>/fix for DT propagation issue1'

  if (matlab_semifinal_B.eps_p[0] > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S73>/Switch' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant1'
  //   Gain: '<S80>/Integral Gain'
  //   Logic: '<S73>/AND3'
  //   RelationalOperator: '<S73>/Equal1'
  //   RelationalOperator: '<S73>/Relational Operator'
  //   Switch: '<S73>/Switch1'
  //   Switch: '<S73>/Switch2'

  if ((matlab_semifinal_B.rtb_DeadZone_p_idx_0 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.rtb_Cbi_tmp_tmp_f = 0.0;
  } else {
    matlab_semifinal_B.rtb_Cbi_tmp_tmp_f = matlab_semifinal_B.eps_p[0];
  }

  // DeadZone: '<S75>/DeadZone'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 > 10.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 =
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 - 10.0;
  } else if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 >= -10.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 = 0.0;
  } else {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 =
      matlab_semifinal_B.rtb_DeadZone_p_idx_1 - -10.0;
  }

  // Switch: '<S73>/Switch1' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant'
  //   Constant: '<S73>/Constant2'
  //   RelationalOperator: '<S73>/fix for DT propagation issue'

  if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S73>/Switch2' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant3'
  //   Constant: '<S73>/Constant4'
  //   RelationalOperator: '<S73>/fix for DT propagation issue1'

  if (matlab_semifinal_B.rtb_X_est_wb > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S73>/Switch' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant1'
  //   Logic: '<S73>/AND3'
  //   RelationalOperator: '<S73>/Equal1'
  //   RelationalOperator: '<S73>/Relational Operator'
  //   Switch: '<S73>/Switch1'
  //   Switch: '<S73>/Switch2'

  if ((matlab_semifinal_B.rtb_DeadZone_p_idx_0 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.rtb_X_est_wb = 0.0;
  }

  // DeadZone: '<S75>/DeadZone'
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_2 > 10.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 =
      matlab_semifinal_B.rtb_DeadZone_p_idx_2 - 10.0;
  } else if (matlab_semifinal_B.rtb_DeadZone_p_idx_2 >= -10.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 = 0.0;
  } else {
    matlab_semifinal_B.rtb_DeadZone_p_idx_0 =
      matlab_semifinal_B.rtb_DeadZone_p_idx_2 - -10.0;
  }

  // MATLAB Function: '<S34>/forceToPWMCalculator' incorporates:
  //   Constant: '<S25>/Constant3'

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 8;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.pwms[matlab_semifinal_B.i_o] = 1500.0;
  }

  for (matlab_semifinal_B.pos = 0; matlab_semifinal_B.pos < 4;
       matlab_semifinal_B.pos++) {
    matlab_semifinal_B.k_o = matlab_semifinal_B.pos << 1;
    matlab_semifinal_B.rtb_DeadZone_p_idx_2 =
      matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o];
    if (std::abs(matlab_semifinal_B.rtb_DeadZone_p_idx_2) < 0.001) {
      matlab_semifinal_B.pwms[matlab_semifinal_B.k_o] = 1500.0;
    } else {
      for (matlab_semifinal_B.d_k = 0; matlab_semifinal_B.d_k < 6;
           matlab_semifinal_B.d_k++) {
        matlab_semifinal_B.varargin_1_f[matlab_semifinal_B.d_k] = std::abs
          (matlab_semifinal_ConstP.forceToPWMCalculator_voltage[matlab_semifinal_B.d_k]
           - 15.0);
      }

      matlab_semifinal_minimum(matlab_semifinal_B.varargin_1_f,
        &matlab_semifinal_B.rtb_DeadZone_p_idx_1, &matlab_semifinal_B.i_o);
      switch (matlab_semifinal_B.i_o) {
       case 1:
        matlab_semifinal_B.lower_voltage_index = 1.0;
        matlab_semifinal_B.upper_voltage_index = 1.0;
        break;

       case 6:
        matlab_semifinal_B.lower_voltage_index = 6.0;
        matlab_semifinal_B.upper_voltage_index = 6.0;
        break;

       default:
        if (matlab_semifinal_ConstP.forceToPWMCalculator_voltage[matlab_semifinal_B.i_o
            - 1] < 15.0) {
          matlab_semifinal_B.lower_voltage_index = matlab_semifinal_B.i_o;
          matlab_semifinal_B.upper_voltage_index = static_cast<real_T>
            (matlab_semifinal_B.i_o) + 1.0;
        } else {
          matlab_semifinal_B.upper_voltage_index = matlab_semifinal_B.i_o;
          matlab_semifinal_B.lower_voltage_index = static_cast<real_T>
            (matlab_semifinal_B.i_o) - 1.0;
        }
        break;
      }

      if (matlab_semifinal_B.upper_voltage_index ==
          matlab_semifinal_B.lower_voltage_index) {
        matlab_semifinal_B.force_column_size_idx_0 = 1;
        matlab_semifinal_B.force_column_data[0] =
          matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[static_cast<
          int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
      } else if (std::abs(matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[
                          static_cast<int32_T>
                          (matlab_semifinal_B.upper_voltage_index) - 1] -
                          matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[
                          static_cast<int32_T>
                          (matlab_semifinal_B.lower_voltage_index) - 1]) < 0.001)
      {
        matlab_semifinal_B.force_column_size_idx_0 = 1;
        matlab_semifinal_B.force_column_data[0] =
          matlab_semifinal_ConstP.forceToPWMCalculator_cw_force
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
      } else {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 15.0 -
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
        matlab_semifinal_B.b_t =
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.upper_voltage_index) - 1] -
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
        matlab_semifinal_B.force_column_size_idx_0 = 201;
        for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 201;
             matlab_semifinal_B.i_o++) {
          matlab_semifinal_B.d_k = (static_cast<int32_T>
            (matlab_semifinal_B.lower_voltage_index) - 1) * 201 +
            matlab_semifinal_B.i_o;
          matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o] =
            (matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[(static_cast<
              int32_T>(matlab_semifinal_B.upper_voltage_index) - 1) * 201 +
             matlab_semifinal_B.i_o] -
             matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[matlab_semifinal_B.d_k])
            * matlab_semifinal_B.rtb_DeadZone_p_idx_1 / matlab_semifinal_B.b_t +
            matlab_semifinal_ConstP.forceToPWMCalculator_cw_force[matlab_semifinal_B.d_k];
        }
      }

      matlab_semifinal_B.b_varargin_1_size =
        matlab_semifinal_B.force_column_size_idx_0;
      for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o <
           matlab_semifinal_B.force_column_size_idx_0; matlab_semifinal_B.i_o++)
      {
        matlab_semifinal_B.b_x_data[matlab_semifinal_B.i_o] =
          matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o] -
          matlab_semifinal_B.rtb_DeadZone_p_idx_2;
        matlab_semifinal_B.b_varargin_1_data[matlab_semifinal_B.i_o] = std::abs
          (matlab_semifinal_B.b_x_data[matlab_semifinal_B.i_o]);
      }

      matlab_semifinal_minimum_g(matlab_semifinal_B.b_varargin_1_data,
        &matlab_semifinal_B.b_varargin_1_size,
        &matlab_semifinal_B.rtb_DeadZone_p_idx_1, &matlab_semifinal_B.i_o);
      if ((matlab_semifinal_B.i_o == 1) || (matlab_semifinal_B.i_o == 2)) {
        matlab_semifinal_B.b_t = 1.0;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 1.0;
      } else if ((matlab_semifinal_B.i_o == 8) || (matlab_semifinal_B.i_o == 7))
      {
        matlab_semifinal_B.b_t = 8.0;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 8.0;
      } else if (matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o - 1]
                 < matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o]) {
        matlab_semifinal_B.b_t = matlab_semifinal_B.i_o;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = static_cast<real_T>
          (matlab_semifinal_B.i_o) + 1.0;
      } else {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = matlab_semifinal_B.i_o;
        matlab_semifinal_B.b_t = static_cast<real_T>(matlab_semifinal_B.i_o) -
          1.0;
      }

      if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 >
          matlab_semifinal_B.force_column_size_idx_0) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 =
          matlab_semifinal_B.force_column_size_idx_0;
      }

      if ((static_cast<int32_T>(matlab_semifinal_B.rtb_DeadZone_p_idx_1) ==
           matlab_semifinal_B.force_column_size_idx_0) && (static_cast<real_T>
           (matlab_semifinal_B.force_column_size_idx_0) - 1.0 ==
           matlab_semifinal_B.b_t)) {
        matlab_semifinal_B.b_t = matlab_semifinal_B.rtb_DeadZone_p_idx_1;
      } else if ((matlab_semifinal_B.rtb_DeadZone_p_idx_1 == 2.0) &&
                 (matlab_semifinal_B.b_t == 1.0)) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 1.0;
      }

      if (matlab_semifinal_B.b_t == matlab_semifinal_B.rtb_DeadZone_p_idx_1) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 0.0;
      } else if (std::abs(matlab_semifinal_B.force_column_data
                          [static_cast<int32_T>
                          (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
                          matlab_semifinal_B.force_column_data[static_cast<
                          int32_T>(matlab_semifinal_B.b_t) - 1]) < 0.001) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 0.0;
      } else {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 =
          (matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o] -
           matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1]) /
          (matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
           matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.b_t) - 1]);
      }

      matlab_semifinal_B.pwms[matlab_semifinal_B.k_o] = std::round
        ((matlab_semifinal_ConstP.forceToPWMCalculator_cw_pwm
          [static_cast<int32_T>(matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
          matlab_semifinal_ConstP.forceToPWMCalculator_cw_pwm
          [static_cast<int32_T>(matlab_semifinal_B.b_t) - 1]) *
         matlab_semifinal_B.rtb_DeadZone_p_idx_2 +
         matlab_semifinal_ConstP.forceToPWMCalculator_cw_pwm[static_cast<int32_T>
         (matlab_semifinal_B.b_t) - 1]);
    }
  }

  for (matlab_semifinal_B.pos = 0; matlab_semifinal_B.pos < 4;
       matlab_semifinal_B.pos++) {
    matlab_semifinal_B.k_o = (matlab_semifinal_B.pos << 1) + 1;
    matlab_semifinal_B.rtb_DeadZone_p_idx_2 =
      matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o];
    if (std::abs(matlab_semifinal_B.rtb_DeadZone_p_idx_2) < 0.001) {
      matlab_semifinal_B.pwms[matlab_semifinal_B.k_o] = 1500.0;
    } else {
      for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 6;
           matlab_semifinal_B.i_o++) {
        matlab_semifinal_B.varargin_1_f[matlab_semifinal_B.i_o] = std::abs
          (matlab_semifinal_ConstP.forceToPWMCalculator_voltage[matlab_semifinal_B.i_o]
           - 15.0);
      }

      matlab_semifinal_minimum(matlab_semifinal_B.varargin_1_f,
        &matlab_semifinal_B.rtb_DeadZone_p_idx_1, &matlab_semifinal_B.i_o);
      switch (matlab_semifinal_B.i_o) {
       case 1:
        matlab_semifinal_B.lower_voltage_index = 1.0;
        matlab_semifinal_B.upper_voltage_index = 1.0;
        break;

       case 6:
        matlab_semifinal_B.lower_voltage_index = 6.0;
        matlab_semifinal_B.upper_voltage_index = 6.0;
        break;

       default:
        if (matlab_semifinal_ConstP.forceToPWMCalculator_voltage[matlab_semifinal_B.i_o
            - 1] < 15.0) {
          matlab_semifinal_B.lower_voltage_index = matlab_semifinal_B.i_o;
          matlab_semifinal_B.upper_voltage_index = static_cast<real_T>
            (matlab_semifinal_B.i_o) + 1.0;
        } else {
          matlab_semifinal_B.upper_voltage_index = matlab_semifinal_B.i_o;
          matlab_semifinal_B.lower_voltage_index = static_cast<real_T>
            (matlab_semifinal_B.i_o) - 1.0;
        }
        break;
      }

      if (matlab_semifinal_B.upper_voltage_index ==
          matlab_semifinal_B.lower_voltage_index) {
        matlab_semifinal_B.force_column_size_idx_0 = 1;
        matlab_semifinal_B.force_column_data[0] =
          matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(matlab_semifinal_B.upper_voltage_index) -
                  1] - matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) -
                  1]) < 0.001) {
        matlab_semifinal_B.force_column_size_idx_0 = 1;
        matlab_semifinal_B.force_column_data[0] =
          matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
      } else {
        matlab_semifinal_B.b_a_h = 15.0 -
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
        matlab_semifinal_B.b_t =
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.upper_voltage_index) - 1] -
          matlab_semifinal_ConstP.forceToPWMCalculator_voltage
          [static_cast<int32_T>(matlab_semifinal_B.lower_voltage_index) - 1];
        matlab_semifinal_B.force_column_size_idx_0 = 201;
        for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 201;
             matlab_semifinal_B.i_o++) {
          matlab_semifinal_B.d_k = (static_cast<int32_T>
            (matlab_semifinal_B.lower_voltage_index) - 1) * 201 +
            matlab_semifinal_B.i_o;
          matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o] =
            (matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force[(
              static_cast<int32_T>(matlab_semifinal_B.upper_voltage_index) - 1) *
             201 + matlab_semifinal_B.i_o] -
             matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force[matlab_semifinal_B.d_k])
            * matlab_semifinal_B.b_a_h / matlab_semifinal_B.b_t +
            matlab_semifinal_ConstP.forceToPWMCalculator_ccw_force[matlab_semifinal_B.d_k];
        }
      }

      matlab_semifinal_B.b_varargin_1_size =
        matlab_semifinal_B.force_column_size_idx_0;
      for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o <
           matlab_semifinal_B.force_column_size_idx_0; matlab_semifinal_B.i_o++)
      {
        matlab_semifinal_B.b_x_data[matlab_semifinal_B.i_o] =
          matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o] -
          matlab_semifinal_B.rtb_DeadZone_p_idx_2;
        matlab_semifinal_B.b_varargin_1_data[matlab_semifinal_B.i_o] = std::abs
          (matlab_semifinal_B.b_x_data[matlab_semifinal_B.i_o]);
      }

      matlab_semifinal_minimum_g(matlab_semifinal_B.b_varargin_1_data,
        &matlab_semifinal_B.b_varargin_1_size,
        &matlab_semifinal_B.rtb_DeadZone_p_idx_1, &matlab_semifinal_B.i_o);
      if ((matlab_semifinal_B.i_o == 1) || (matlab_semifinal_B.i_o == 2)) {
        matlab_semifinal_B.b_t = 1.0;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 1.0;
      } else if ((matlab_semifinal_B.i_o == 8) || (matlab_semifinal_B.i_o == 7))
      {
        matlab_semifinal_B.b_t = 8.0;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 8.0;
      } else if (matlab_semifinal_B.force_column_data[matlab_semifinal_B.i_o - 1]
                 < matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o]) {
        matlab_semifinal_B.b_t = matlab_semifinal_B.i_o;
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = static_cast<real_T>
          (matlab_semifinal_B.i_o) + 1.0;
      } else {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 = matlab_semifinal_B.i_o;
        matlab_semifinal_B.b_t = static_cast<real_T>(matlab_semifinal_B.i_o) -
          1.0;
      }

      if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 >
          matlab_semifinal_B.force_column_size_idx_0) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_1 =
          matlab_semifinal_B.force_column_size_idx_0;
      }

      if (matlab_semifinal_B.b_t == matlab_semifinal_B.rtb_DeadZone_p_idx_1) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 0.0;
      } else if (std::abs(matlab_semifinal_B.force_column_data
                          [static_cast<int32_T>
                          (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
                          matlab_semifinal_B.force_column_data[static_cast<
                          int32_T>(matlab_semifinal_B.b_t) - 1]) < 0.001) {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 0.0;
      } else {
        matlab_semifinal_B.rtb_DeadZone_p_idx_2 =
          (matlab_semifinal_B.FT_cmd_list[matlab_semifinal_B.k_o] -
           matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1]) /
          (matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
           matlab_semifinal_B.force_column_data[static_cast<int32_T>
           (matlab_semifinal_B.b_t) - 1]);
      }

      matlab_semifinal_B.pwms[matlab_semifinal_B.k_o] = std::round
        ((matlab_semifinal_ConstP.forceToPWMCalculator_ccw_pwm
          [static_cast<int32_T>(matlab_semifinal_B.rtb_DeadZone_p_idx_1) - 1] -
          matlab_semifinal_ConstP.forceToPWMCalculator_ccw_pwm
          [static_cast<int32_T>(matlab_semifinal_B.b_t) - 1]) *
         matlab_semifinal_B.rtb_DeadZone_p_idx_2 +
         matlab_semifinal_ConstP.forceToPWMCalculator_ccw_pwm
         [static_cast<int32_T>(matlab_semifinal_B.b_t) - 1]);
    }
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 8;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.pwms[matlab_semifinal_B.i_o] = std::fmax(1100.0, std::
      fmin(1900.0, matlab_semifinal_B.pwms[matlab_semifinal_B.i_o]));
  }

  // DeadZone: '<S131>/DeadZone'
  if (matlab_semifinal_B.eps[0] > 1.0) {
    matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[0] - 1.0;

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant'

    tmp_0 = 1;
  } else {
    if (matlab_semifinal_B.eps[0] >= -1.0) {
      matlab_semifinal_B.b_a_h = 0.0;
    } else {
      matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[0] - -1.0;
    }

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant2'

    tmp_0 = -1;
  }

  // Switch: '<S129>/Switch' incorporates:
  //   Constant: '<S129>/Clamping_zero'
  //   Constant: '<S129>/Constant1'
  //   DeadZone: '<S131>/DeadZone'
  //   Gain: '<S136>/Integral Gain'
  //   Logic: '<S129>/AND3'
  //   RelationalOperator: '<S129>/Equal1'
  //   RelationalOperator: '<S129>/Relational Operator'
  //   Switch: '<S129>/Switch1'
  //   Switch: '<S129>/Switch2'

  if ((matlab_semifinal_B.b_a_h != 0.0) && (tmp_0 == -1)) {
    matlab_semifinal_B.eps_b = 0.0;
  } else {
    matlab_semifinal_B.eps_b = 0.0 * matlab_semifinal_B.eps_n[0];
  }

  // DeadZone: '<S190>/DeadZone'
  if (matlab_semifinal_B.rtb_Eul_idx_0 > 100.0) {
    matlab_semifinal_B.rtb_Eul_idx_0 -= 100.0;
  } else if (matlab_semifinal_B.rtb_Eul_idx_0 >= -100.0) {
    matlab_semifinal_B.rtb_Eul_idx_0 = 0.0;
  } else {
    matlab_semifinal_B.rtb_Eul_idx_0 -= -100.0;
  }

  // Gain: '<S195>/Integral Gain'
  matlab_semifinal_B.eps_p[0] = 20.0 * matlab_semifinal_B.dRb_e[0];

  // DeadZone: '<S131>/DeadZone'
  if (matlab_semifinal_B.eps[1] > 1.0) {
    matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[1] - 1.0;

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant'

    tmp_0 = 1;
  } else {
    if (matlab_semifinal_B.eps[1] >= -1.0) {
      matlab_semifinal_B.b_a_h = 0.0;
    } else {
      matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[1] - -1.0;
    }

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant2'

    tmp_0 = -1;
  }

  // Switch: '<S129>/Switch' incorporates:
  //   Constant: '<S129>/Clamping_zero'
  //   Constant: '<S129>/Constant1'
  //   DeadZone: '<S131>/DeadZone'
  //   Gain: '<S136>/Integral Gain'
  //   Logic: '<S129>/AND3'
  //   RelationalOperator: '<S129>/Equal1'
  //   RelationalOperator: '<S129>/Relational Operator'
  //   Switch: '<S129>/Switch1'
  //   Switch: '<S129>/Switch2'

  if ((matlab_semifinal_B.b_a_h != 0.0) && (tmp_0 == -1)) {
    matlab_semifinal_B.lower_voltage_index = 0.0;
  } else {
    matlab_semifinal_B.lower_voltage_index = 0.0 * matlab_semifinal_B.eps_n[1];
  }

  // DeadZone: '<S190>/DeadZone'
  if (matlab_semifinal_B.rtb_Eul_idx_1 > 100.0) {
    matlab_semifinal_B.rtb_Eul_idx_1 -= 100.0;
  } else if (matlab_semifinal_B.rtb_Eul_idx_1 >= -100.0) {
    matlab_semifinal_B.rtb_Eul_idx_1 = 0.0;
  } else {
    matlab_semifinal_B.rtb_Eul_idx_1 -= -100.0;
  }

  // Gain: '<S195>/Integral Gain'
  matlab_semifinal_B.eps_p[1] = 20.0 * matlab_semifinal_B.dRb_e[1];

  // DeadZone: '<S131>/DeadZone'
  if (matlab_semifinal_B.eps[2] > 1.0) {
    matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[2] - 1.0;

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant'

    tmp_0 = 1;
  } else {
    if (matlab_semifinal_B.eps[2] >= -1.0) {
      matlab_semifinal_B.b_a_h = 0.0;
    } else {
      matlab_semifinal_B.b_a_h = matlab_semifinal_B.eps[2] - -1.0;
    }

    // Switch: '<S129>/Switch1' incorporates:
    //   Constant: '<S129>/Constant2'

    tmp_0 = -1;
  }

  // Switch: '<S129>/Switch' incorporates:
  //   Constant: '<S129>/Clamping_zero'
  //   Constant: '<S129>/Constant1'
  //   DeadZone: '<S131>/DeadZone'
  //   Gain: '<S136>/Integral Gain'
  //   Logic: '<S129>/AND3'
  //   RelationalOperator: '<S129>/Equal1'
  //   RelationalOperator: '<S129>/Relational Operator'
  //   Switch: '<S129>/Switch1'
  //   Switch: '<S129>/Switch2'

  if ((matlab_semifinal_B.b_a_h != 0.0) && (tmp_0 == -1)) {
    matlab_semifinal_B.b_a_h = 0.0;
  } else {
    matlab_semifinal_B.b_a_h = 0.0 * matlab_semifinal_B.eps_n[2];
  }

  // DeadZone: '<S190>/DeadZone' incorporates:
  //   Sum: '<S207>/Sum'

  if (matlab_semifinal_B.phi > 100.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_1 = matlab_semifinal_B.phi - 100.0;
  } else if (matlab_semifinal_B.phi >= -100.0) {
    matlab_semifinal_B.rtb_DeadZone_p_idx_1 = 0.0;
  } else {
    matlab_semifinal_B.rtb_DeadZone_p_idx_1 = matlab_semifinal_B.phi - -100.0;
  }

  // MATLAB Function: '<S25>/quatToEul'
  matlab_semifinal_quatToEul(matlab_semifinal_B.qib_int_u,
    matlab_semifinal_B.eps_n, &matlab_semifinal_B.sf_quatToEul);

  // MATLAB Function: '<S25>/quatToEul1'
  matlab_semifinal_quatToEul(matlab_semifinal_B.qe_matlab,
    matlab_semifinal_B.eps_n, &matlab_semifinal_B.sf_quatToEul1);

  // MATLAB Function: '<S26>/quatToEul'
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 3;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.theta_b = matlab_semifinal_B.X_u[matlab_semifinal_B.i_o +
      3] * 2.0;
    matlab_semifinal_B.Cbi[3 * matlab_semifinal_B.i_o] =
      (matlab_semifinal_B.theta_b * matlab_semifinal_B.X_u[3] +
       matlab_semifinal_B.qk_plus_1_tmp[3 * matlab_semifinal_B.i_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[3 * matlab_semifinal_B.i_o];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 1;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] = (matlab_semifinal_B.theta_b
      * matlab_semifinal_B.X_u[4] +
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.k_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o];
    matlab_semifinal_B.k_o = 3 * matlab_semifinal_B.i_o + 2;
    matlab_semifinal_B.Cbi[matlab_semifinal_B.k_o] = (matlab_semifinal_B.theta_b
      * matlab_semifinal_B.X_u[5] +
      matlab_semifinal_B.qk_plus_1_tmp[matlab_semifinal_B.k_o]) +
      matlab_semifinal_B.rtb_Cbi_tmp[matlab_semifinal_B.k_o];
  }

  matlab_semifinal_B.theta_b = std::asin(std::fmax(-1.0, std::fmin(1.0,
    matlab_semifinal_B.Cbi[6])));
  if (std::abs(std::cos(-matlab_semifinal_B.theta_b)) < 1.0E-6) {
    matlab_semifinal_B.phi = 0.0;
    matlab_semifinal_B.b_t = matlab_semifinal_rt_atan2d_snf
      (-matlab_semifinal_B.Cbi[1], matlab_semifinal_B.Cbi[4]);
  } else {
    matlab_semifinal_B.phi = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[7], matlab_semifinal_B.Cbi[8]);
    matlab_semifinal_B.b_t = matlab_semifinal_rt_atan2d_snf
      (matlab_semifinal_B.Cbi[3], matlab_semifinal_B.Cbi[0]);
  }

  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.phi);
  matlab_semifinal_B.theta_b = -matlab_semifinal_B.theta_b;
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.theta_b);
  matlab_semifinal_wrapToPi_k(&matlab_semifinal_B.b_t);

  // MATLAB Function: '<S12>/joystick_inputs_to_body_forces' incorporates:
  //   MATLAB Function: '<S11>/MATLAB Function'

  matlab_semifinal_B.b_t = ((300.0F * matlab_semifinal_B.In1_k.rise - 300.0F *
    matlab_semifinal_B.In1_k.sink) + 1500.0F) - 300.0F *
    matlab_semifinal_B.In1_k.pitch;
  matlab_semifinal_B.phi = (-(300.0F * matlab_semifinal_B.In1_k.rise - 300.0F *
    matlab_semifinal_B.In1_k.sink) + 1500.0F) - (-(300.0F *
    matlab_semifinal_B.In1_k.pitch));
  matlab_semifinal_B.rtb_DeadZone_p_idx_2 = ((300.0F *
    matlab_semifinal_B.In1_k.rise - 300.0F * matlab_semifinal_B.In1_k.sink) +
    1500.0F) + 300.0F * matlab_semifinal_B.In1_k.pitch;
  matlab_semifinal_B.upper_voltage_index = (-(300.0F *
    matlab_semifinal_B.In1_k.rise - 300.0F * matlab_semifinal_B.In1_k.sink) +
    1500.0F) - 300.0F * matlab_semifinal_B.In1_k.pitch;
  matlab_semifinal_B.theta_b = ((300.0F * matlab_semifinal_B.In1_k.y + 1500.0F)
    + matlab_semifinal_B.In1_k.x * 300.0F) + matlab_semifinal_B.In1_k.yaw *
    300.0F;
  matlab_semifinal_B.pwms_horiz_idx_1 = ((1500.0F - 300.0F *
    matlab_semifinal_B.In1_k.y) + matlab_semifinal_B.In1_k.x * 300.0F) +
    matlab_semifinal_B.In1_k.yaw * 300.0F;
  matlab_semifinal_B.pwms_horiz_idx_2 = ((300.0F * matlab_semifinal_B.In1_k.y +
    1500.0F) - matlab_semifinal_B.In1_k.x * 300.0F) +
    matlab_semifinal_B.In1_k.yaw * 300.0F;
  matlab_semifinal_B.pwms_horiz_idx_3 = ((1500.0F - 300.0F *
    matlab_semifinal_B.In1_k.y) - matlab_semifinal_B.In1_k.x * 300.0F) +
    matlab_semifinal_B.In1_k.yaw * 300.0F;
  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.theta_b;
  if (matlab_semifinal_B.theta_b > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.theta_b = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.theta_b = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.b_t;
  if (matlab_semifinal_B.b_t > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.b_t = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.theta_b = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.pwms_horiz_idx_1;
  if (matlab_semifinal_B.pwms_horiz_idx_1 > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.pwms_horiz_idx_1 = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_1 = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.phi;
  if (matlab_semifinal_B.phi > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.phi = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_1 = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.pwms_horiz_idx_2;
  if (matlab_semifinal_B.pwms_horiz_idx_2 > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.pwms_horiz_idx_2 = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_2 = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.rtb_DeadZone_p_idx_2;
  if (matlab_semifinal_B.rtb_DeadZone_p_idx_2 > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.rtb_DeadZone_p_idx_2 = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_2 = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.pwms_horiz_idx_3;
  if (matlab_semifinal_B.pwms_horiz_idx_3 > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.pwms_horiz_idx_3 = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_3 = 1200.0;
  }

  matlab_semifinal_B.Qe1_e = matlab_semifinal_B.upper_voltage_index;
  if (matlab_semifinal_B.upper_voltage_index > 1800.0) {
    matlab_semifinal_B.Qe1_e = 1800.0;
    matlab_semifinal_B.upper_voltage_index = 1800.0;
  }

  if (matlab_semifinal_B.Qe1_e < 1200.0) {
    matlab_semifinal_B.pwms_horiz_idx_3 = 1200.0;
  }

  // Switch: '<Root>/Switch' incorporates:
  //   MATLAB Function: '<Root>/joystick_mode_manager'

  if (matlab_semifinal_DW.joystick_flag) {
    // MATLAB Function: '<S12>/joystick_inputs_to_body_forces'
    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.b_t);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[0] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[0] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[0] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.theta_b);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[4] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[4] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[4] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.phi);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[1] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[1] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[1] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.pwms_horiz_idx_1);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[5] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[5] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[5] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.rtb_DeadZone_p_idx_2);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[2] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[2] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[2] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.pwms_horiz_idx_2);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[6] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[6] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[6] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.upper_voltage_index);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[3] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[3] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[3] = MAX_int32_T;
    }

    matlab_semifinal_B.b_t = std::round(matlab_semifinal_B.pwms_horiz_idx_3);
    if (matlab_semifinal_B.b_t < 2.147483648E+9) {
      if (matlab_semifinal_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[7] = static_cast<int32_T>
          (matlab_semifinal_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        matlab_semifinal_B.BusCreator3.pwms[7] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      matlab_semifinal_B.BusCreator3.pwms[7] = MAX_int32_T;
    }
  } else {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 8;
         matlab_semifinal_B.i_o++) {
      // DataTypeConversion: '<S25>/Cast' incorporates:
      //   MATLAB Function: '<S34>/forceToPWMCalculator'
      //   Switch: '<S4>/Switch'

      matlab_semifinal_B.b_t = matlab_semifinal_B.pwms[matlab_semifinal_B.i_o];
      if (std::isnan(matlab_semifinal_B.b_t) || std::isinf
          (matlab_semifinal_B.b_t)) {
        matlab_semifinal_B.b_t = 0.0;
      } else {
        matlab_semifinal_B.b_t = std::fmod(matlab_semifinal_B.b_t,
          4.294967296E+9);
      }

      // BusCreator: '<S14>/Bus Creator3' incorporates:
      //   DataTypeConversion: '<S25>/Cast'
      //   MATLAB Function: '<S34>/forceToPWMCalculator'
      //   Switch: '<Root>/Switch'
      //   Switch: '<S4>/Switch'

      matlab_semifinal_B.BusCreator3.pwms[matlab_semifinal_B.i_o] =
        matlab_semifinal_B.b_t < 0.0 ? -static_cast<int32_T>
        (static_cast<uint32_T>(-matlab_semifinal_B.b_t)) : static_cast<int32_T>(
        static_cast<uint32_T>(matlab_semifinal_B.b_t));
    }
  }

  // End of Switch: '<Root>/Switch'

  // MATLABSystem: '<S236>/SinkBlock'
  Pub_matlab_semifinal_626_2.publish(&matlab_semifinal_B.BusCreator3);

  // SignalConversion generated from: '<S225>/ SFunction ' incorporates:
  //   DataStoreRead: '<Root>/Data Store Read12'
  //   DataStoreRead: '<Root>/Data Store Read6'
  //   DataStoreWrite: '<S4>/Data Store Write'
  //   DataTypeConversion: '<S1>/Cast'
  //   DataTypeConversion: '<S4>/Cast'
  //   DataTypeConversion: '<S4>/Cast1'
  //   DataTypeConversion: '<S6>/Cast'
  //   MATLAB Function: '<Root>/joystick_mode_manager'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S7>/MATLAB Function'
  //   MATLABSystem: '<S17>/SourceBlock'
  //
  matlab_semifinal_B.TmpSignalConversionAtSFunct[0] = matlab_semifinal_B.X_u[0];
  matlab_semifinal_B.TmpSignalConversionAtSFunct[6] = matlab_semifinal_B.b_scale;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[9] = matlab_semifinal_B.norm_w;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[1] = matlab_semifinal_B.X_u[1];
  matlab_semifinal_B.TmpSignalConversionAtSFunct[7] = matlab_semifinal_B.b_absxk;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[10] = matlab_semifinal_B.theta;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[2] = matlab_semifinal_B.X_u[2];
  matlab_semifinal_B.TmpSignalConversionAtSFunct[8] =
    matlab_semifinal_B.rotm_tmp;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[11] = matlab_semifinal_B.t;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[12] =
    matlab_semifinal_DW.joystick_flag;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[13] = reset_dvl_pos;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[14] =
    matlab_semifinal_B.DataStoreRead_n;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[15] =
    matlab_semifinal_B.b_varargout_1_c;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[16] = matlab_semifinal_B.db6;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[17] =
    matlab_semifinal_B.In1.altitude;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[18] = matlab_semifinal_B.idx;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[19] =
    matlab_semifinal_B.In1_c.pos_std;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[20] =
    matlab_semifinal_B.In1.fom;
  matlab_semifinal_B.TmpSignalConversionAtSFunct[21] = matlab_semifinal_DW.db11;

  // MATLAB Function: '<S7>/MATLAB Function'
  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 256;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.temp_char[matlab_semifinal_B.i_o] = '_';
  }

  matlab_semifinal_B.idx = 1.0;
  for (matlab_semifinal_B.k_o = 0; matlab_semifinal_B.k_o < 22;
       matlab_semifinal_B.k_o++) {
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 16;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.s[matlab_semifinal_B.i_o] = ' ';
    }

    matlab_semifinal_B.theta_b = std::abs
      (matlab_semifinal_B.TmpSignalConversionAtSFunct[matlab_semifinal_B.k_o]);
    matlab_semifinal_B.b_t = std::floor(matlab_semifinal_B.theta_b);
    if (matlab_semifinal_B.b_t < 4.294967296E+9) {
      matlab_semifinal_B.temp = static_cast<uint32_T>(matlab_semifinal_B.b_t);
    } else {
      matlab_semifinal_B.temp = MAX_uint32_T;
    }

    matlab_semifinal_B.int_part = matlab_semifinal_B.temp;
    matlab_semifinal_B.b_t = std::round((matlab_semifinal_B.theta_b -
      static_cast<real_T>(matlab_semifinal_B.temp)) * 10000.0);
    if (matlab_semifinal_B.b_t < 4.294967296E+9) {
      if (matlab_semifinal_B.b_t >= 0.0) {
        matlab_semifinal_B.frac_part = static_cast<uint32_T>
          (matlab_semifinal_B.b_t);
      } else {
        matlab_semifinal_B.frac_part = 0U;
      }
    } else {
      matlab_semifinal_B.frac_part = MAX_uint32_T;
    }

    if (matlab_semifinal_B.frac_part >= 10000U) {
      matlab_semifinal_B.int_part = matlab_semifinal_B.temp + /*MW:OvSatOk*/ 1U;
      if (matlab_semifinal_B.temp + 1U < matlab_semifinal_B.temp) {
        matlab_semifinal_B.int_part = MAX_uint32_T;
      }

      matlab_semifinal_B.frac_part = 0U;
    }

    matlab_semifinal_B.temp = matlab_semifinal_B.int_part;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 10;
         matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.digits[9 - matlab_semifinal_B.i_o] = static_cast<int8_T>
        (static_cast<int8_T>(matlab_semifinal_B.temp - matlab_semifinal_B.temp /
          10U * 10U) + 48);
      matlab_semifinal_B.temp /= 10U;
    }

    matlab_semifinal_B.db6 = 9;
    matlab_semifinal_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (matlab_semifinal_B.i_o < 10)) {
      if (matlab_semifinal_B.digits[matlab_semifinal_B.i_o] != '0') {
        matlab_semifinal_B.db6 = matlab_semifinal_B.i_o;
        exitg1 = true;
      } else {
        matlab_semifinal_B.i_o++;
      }
    }

    if (matlab_semifinal_B.int_part == 0U) {
      matlab_semifinal_B.db6 = 9;
    }

    matlab_semifinal_B.pos = 1;
    if (matlab_semifinal_B.TmpSignalConversionAtSFunct[matlab_semifinal_B.k_o] <
        0.0) {
      matlab_semifinal_B.s[0] = '-';
      matlab_semifinal_B.pos = 2;
    }

    matlab_semifinal_B.d_k = -matlab_semifinal_B.db6;
    for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o <=
         matlab_semifinal_B.d_k + 9; matlab_semifinal_B.i_o++) {
      matlab_semifinal_B.s[(matlab_semifinal_B.pos + matlab_semifinal_B.i_o) - 1]
        = matlab_semifinal_B.digits[matlab_semifinal_B.db6 +
        matlab_semifinal_B.i_o];
    }

    matlab_semifinal_B.pos = (matlab_semifinal_B.pos - matlab_semifinal_B.db6) +
      9;
    matlab_semifinal_B.s[matlab_semifinal_B.pos] = '.';
    matlab_semifinal_B.int_part = matlab_semifinal_B.frac_part / 10U;
    matlab_semifinal_B.fd[2] = static_cast<int8_T>(static_cast<int8_T>
      (matlab_semifinal_B.int_part - matlab_semifinal_B.int_part / 10U * 10U) +
      48);
    matlab_semifinal_B.int_part /= 10U;
    matlab_semifinal_B.s[matlab_semifinal_B.pos + 1] = static_cast<int8_T>(
      static_cast<int32_T>(matlab_semifinal_B.int_part / 10U) + 48);
    matlab_semifinal_B.s[matlab_semifinal_B.pos + 2] = static_cast<int8_T>(
      static_cast<int8_T>(matlab_semifinal_B.int_part -
                          matlab_semifinal_B.int_part / 10U * 10U) + 48);
    matlab_semifinal_B.s[matlab_semifinal_B.pos + 3] = matlab_semifinal_B.fd[2];
    matlab_semifinal_B.s[matlab_semifinal_B.pos + 4] = static_cast<int8_T>(
      static_cast<int8_T>(matlab_semifinal_B.frac_part -
                          matlab_semifinal_B.frac_part / 10U * 10U) + 48);
    matlab_semifinal_B.pos += 5;
    matlab_semifinal_B.b_t = (matlab_semifinal_B.idx + static_cast<real_T>
      (matlab_semifinal_B.pos)) - 1.0;
    if (matlab_semifinal_B.b_t <= 256.0) {
      if (matlab_semifinal_B.idx > matlab_semifinal_B.b_t) {
        matlab_semifinal_B.db6 = 1;
      } else {
        matlab_semifinal_B.db6 = static_cast<int32_T>(matlab_semifinal_B.idx);
      }

      for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o <
           matlab_semifinal_B.pos; matlab_semifinal_B.i_o++) {
        matlab_semifinal_B.temp_char[(matlab_semifinal_B.db6 +
          matlab_semifinal_B.i_o) - 1] =
          matlab_semifinal_B.s[matlab_semifinal_B.i_o];
      }

      matlab_semifinal_B.idx += static_cast<real_T>(matlab_semifinal_B.pos);
    }

    if ((matlab_semifinal_B.k_o + 1 < 22) && (matlab_semifinal_B.idx <= 256.0))
    {
      matlab_semifinal_B.temp_char[static_cast<int32_T>(matlab_semifinal_B.idx)
        - 1] = ',';
      matlab_semifinal_B.idx++;
    }
  }

  for (matlab_semifinal_B.i_o = 0; matlab_semifinal_B.i_o < 256;
       matlab_semifinal_B.i_o++) {
    matlab_semifinal_B.debug_msg.message[matlab_semifinal_B.i_o] =
      static_cast<uint8_T>(matlab_semifinal_B.temp_char[matlab_semifinal_B.i_o]);
  }

  // MATLABSystem: '<S226>/SinkBlock'
  Pub_matlab_semifinal_594_3.publish(&matlab_semifinal_B.debug_msg);

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //
  matlab_semifinal_DW.PositionIntegrator_IC_LOADING = 0U;
  if (matlab_semifinal_B.b_varargout_1_h) {
    matlab_semifinal_DW.PositionIntegrator_PrevResetSta = 1;
  } else {
    matlab_semifinal_DW.PositionIntegrator_PrevResetSta = 0;
  }

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator'
  matlab_semifinal_DW.VelocityIntegrator_IC_LOADING = 0U;

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_DW.PositionIntegrator_DSTATE[0] += 0.01 *
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[0];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   Sum: '<S6>/Sum'

  matlab_semifinal_DW.VelocityIntegrator_DSTATE[0] += 0.01 *
    matlab_semifinal_B.rtb_dvl_pos_l[0];

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_DW.PositionIntegrator_DSTATE[1] += 0.01 *
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[1];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   Sum: '<S6>/Sum'

  matlab_semifinal_DW.VelocityIntegrator_DSTATE[1] += 0.01 *
    matlab_semifinal_B.rtb_dvl_pos_l[1];

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  matlab_semifinal_DW.PositionIntegrator_DSTATE[2] += 0.01 *
    matlab_semifinal_DW.VelocityIntegrator_DSTATE[2];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   MATLABSystem: '<S8>/SourceBlock'
  //   Sum: '<S6>/Sum'
  //
  matlab_semifinal_DW.VelocityIntegrator_DSTATE[2] += 0.01 *
    matlab_semifinal_B.rtb_dvl_pos_l[2];
  if (matlab_semifinal_B.b_varargout_1) {
    matlab_semifinal_DW.VelocityIntegrator_PrevResetSta = 1;
  } else {
    matlab_semifinal_DW.VelocityIntegrator_PrevResetSta = 0;
  }

  // Update for UnitDelay: '<S29>/Delay Input1' incorporates:
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S29>/Delay Input1':
  //
  //   Store in Global RAM

  matlab_semifinal_DW.DelayInput1_DSTATE = matlab_semifinal_DW.UnitDelay_DSTATE;

  // Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_DW.DiscreteTimeIntegrator_PrevRese = static_cast<int8_T>
    (reset_pids);
  matlab_semifinal_B.idx = (1.0 - matlab_semifinal_B.rtb_delta_qe_idx_3) * 0.01
    + matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[0];
  matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[0] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[0] = 1.0471975511965976;
  } else if (matlab_semifinal_B.idx < -1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[0] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  matlab_semifinal_DW.DiscreteTransferFcn_states[0] = matlab_semifinal_B.scale;

  // Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_B.idx = (0.0 - matlab_semifinal_B.eta) * 0.01 +
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[1];
  matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[1] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[1] = 1.0471975511965976;
  } else if (matlab_semifinal_B.idx < -1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[1] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  matlab_semifinal_DW.DiscreteTransferFcn_states[1] = matlab_semifinal_B.absxk;

  // Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_B.idx = (0.0 - matlab_semifinal_B.rtb_delta_qe_idx_1) * 0.01
    + matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[2];
  matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[2] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[2] = 1.0471975511965976;
  } else if (matlab_semifinal_B.idx < -1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[2] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  matlab_semifinal_DW.DiscreteTransferFcn_states[2] =
    matlab_semifinal_B.DiscreteTransferFcn_tmp_idx_2;

  // Update for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  matlab_semifinal_B.idx = (0.0 - matlab_semifinal_B.rtb_delta_qe_idx_2) * 0.01
    + matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[3];
  matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[3] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[3] = 1.0471975511965976;
  } else if (matlab_semifinal_B.idx < -1.0471975511965976) {
    matlab_semifinal_DW.DiscreteTimeIntegrator_DSTATE[3] = -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  matlab_semifinal_DW.DiscreteTransferFcn_states[3] = matlab_semifinal_B.eps_tmp;

  // Update for DiscreteIntegrator: '<S139>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'

  matlab_semifinal_DW.Integrator_PrevResetState = static_cast<int8_T>(reset_pids);

  // Update for DiscreteIntegrator: '<S134>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'

  matlab_semifinal_DW.Filter_PrevResetState = static_cast<int8_T>(reset_pids);

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'

  matlab_semifinal_DW.Integrator_PrevResetState_d = static_cast<int8_T>
    (reset_pids);

  // Update for DiscreteIntegrator: '<S78>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'

  matlab_semifinal_DW.Filter_PrevResetState_g = static_cast<int8_T>(reset_pids);

  // Update for DiscreteIntegrator: '<S198>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'

  matlab_semifinal_DW.Integrator_PrevResetState_p = static_cast<int8_T>
    (reset_pids);

  // Update for DiscreteIntegrator: '<S139>/Integrator' incorporates:
  //   Switch: '<S129>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.eps_b +
    matlab_semifinal_DW.Integrator_DSTATE[0];
  matlab_semifinal_DW.Integrator_DSTATE[0] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[0] = 1.0;
  } else if (matlab_semifinal_B.idx < -1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[0] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S134>/Filter' incorporates:
  //   Gain: '<S142>/Filter Coefficient'

  matlab_semifinal_DW.Filter_DSTATE[0] += 0.01 * matlab_semifinal_B.Rb_u[0];

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Switch: '<S73>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.rtb_Cbi_tmp_tmp_f +
    matlab_semifinal_DW.Integrator_DSTATE_m[0];
  matlab_semifinal_DW.Integrator_DSTATE_m[0] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[0] = 10.0;
  } else if (matlab_semifinal_B.idx < -10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[0] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S78>/Filter'
  matlab_semifinal_DW.Filter_DSTATE_d[0] += 0.01 * matlab_semifinal_B.dRb_u[0];

  // Switch: '<S188>/Switch1' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant'
  //   Constant: '<S188>/Constant2'
  //   RelationalOperator: '<S188>/fix for DT propagation issue'

  if (matlab_semifinal_B.rtb_Eul_idx_0 > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S188>/Switch2' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant3'
  //   Constant: '<S188>/Constant4'
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   RelationalOperator: '<S188>/fix for DT propagation issue1'

  if (matlab_semifinal_B.eps_p[0] > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S188>/Switch' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant1'
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   Logic: '<S188>/AND3'
  //   RelationalOperator: '<S188>/Equal1'
  //   RelationalOperator: '<S188>/Relational Operator'
  //   Switch: '<S188>/Switch1'
  //   Switch: '<S188>/Switch2'

  if ((matlab_semifinal_B.rtb_Eul_idx_0 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.b_t = 0.0;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.eps_p[0];
  }

  // Update for DiscreteIntegrator: '<S198>/Integrator' incorporates:
  //   Switch: '<S188>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.b_t +
    matlab_semifinal_DW.Integrator_DSTATE_d[0];
  matlab_semifinal_DW.Integrator_DSTATE_d[0] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[0] = 100.0;
  } else if (matlab_semifinal_B.idx < -100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[0] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S193>/Filter'
  matlab_semifinal_DW.Filter_DSTATE_c[0] += 0.01 *
    matlab_semifinal_B.rtb_FilterCoefficient_d_idx_0;

  // Update for DiscreteIntegrator: '<S139>/Integrator' incorporates:
  //   Switch: '<S129>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.lower_voltage_index +
    matlab_semifinal_DW.Integrator_DSTATE[1];
  matlab_semifinal_DW.Integrator_DSTATE[1] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[1] = 1.0;
  } else if (matlab_semifinal_B.idx < -1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[1] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S134>/Filter' incorporates:
  //   Gain: '<S142>/Filter Coefficient'

  matlab_semifinal_DW.Filter_DSTATE[1] += 0.01 * matlab_semifinal_B.Rb_u[1];

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Switch: '<S73>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.rtb_X_est_wb +
    matlab_semifinal_DW.Integrator_DSTATE_m[1];
  matlab_semifinal_DW.Integrator_DSTATE_m[1] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[1] = 10.0;
  } else if (matlab_semifinal_B.idx < -10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[1] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S78>/Filter'
  matlab_semifinal_DW.Filter_DSTATE_d[1] += 0.01 * matlab_semifinal_B.dRb_u[1];

  // Switch: '<S188>/Switch1' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant'
  //   Constant: '<S188>/Constant2'
  //   RelationalOperator: '<S188>/fix for DT propagation issue'

  if (matlab_semifinal_B.rtb_Eul_idx_1 > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S188>/Switch2' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant3'
  //   Constant: '<S188>/Constant4'
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   RelationalOperator: '<S188>/fix for DT propagation issue1'

  if (matlab_semifinal_B.eps_p[1] > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S188>/Switch' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant1'
  //   DiscreteIntegrator: '<S198>/Integrator'
  //   Logic: '<S188>/AND3'
  //   RelationalOperator: '<S188>/Equal1'
  //   RelationalOperator: '<S188>/Relational Operator'
  //   Switch: '<S188>/Switch1'
  //   Switch: '<S188>/Switch2'

  if ((matlab_semifinal_B.rtb_Eul_idx_1 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.b_t = 0.0;
  } else {
    matlab_semifinal_B.b_t = matlab_semifinal_B.eps_p[1];
  }

  // Update for DiscreteIntegrator: '<S198>/Integrator' incorporates:
  //   Switch: '<S188>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.b_t +
    matlab_semifinal_DW.Integrator_DSTATE_d[1];
  matlab_semifinal_DW.Integrator_DSTATE_d[1] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[1] = 100.0;
  } else if (matlab_semifinal_B.idx < -100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[1] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S193>/Filter'
  matlab_semifinal_DW.Filter_DSTATE_c[1] += 0.01 *
    matlab_semifinal_B.rtb_FilterCoefficient_d_idx_1;

  // Update for DiscreteIntegrator: '<S139>/Integrator' incorporates:
  //   Switch: '<S129>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.b_a_h +
    matlab_semifinal_DW.Integrator_DSTATE[2];
  matlab_semifinal_DW.Integrator_DSTATE[2] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[2] = 1.0;
  } else if (matlab_semifinal_B.idx < -1.0) {
    matlab_semifinal_DW.Integrator_DSTATE[2] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S134>/Filter' incorporates:
  //   Gain: '<S142>/Filter Coefficient'

  matlab_semifinal_DW.Filter_DSTATE[2] += 0.01 * matlab_semifinal_B.Rb_u[2];

  // Switch: '<S73>/Switch1' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant'
  //   Constant: '<S73>/Constant2'
  //   RelationalOperator: '<S73>/fix for DT propagation issue'

  if (matlab_semifinal_B.rtb_DeadZone_p_idx_0 > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S73>/Switch2' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant3'
  //   Constant: '<S73>/Constant4'
  //   RelationalOperator: '<S73>/fix for DT propagation issue1'

  if (matlab_semifinal_B.rtb_X_est_wb_j > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S73>/Switch' incorporates:
  //   Constant: '<S73>/Clamping_zero'
  //   Constant: '<S73>/Constant1'
  //   Logic: '<S73>/AND3'
  //   RelationalOperator: '<S73>/Equal1'
  //   RelationalOperator: '<S73>/Relational Operator'
  //   Switch: '<S73>/Switch1'
  //   Switch: '<S73>/Switch2'

  if ((matlab_semifinal_B.rtb_DeadZone_p_idx_0 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.rtb_X_est_wb_j = 0.0;
  }

  // Update for DiscreteIntegrator: '<S83>/Integrator' incorporates:
  //   Switch: '<S73>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.rtb_X_est_wb_j +
    matlab_semifinal_DW.Integrator_DSTATE_m[2];
  matlab_semifinal_DW.Integrator_DSTATE_m[2] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[2] = 10.0;
  } else if (matlab_semifinal_B.idx < -10.0) {
    matlab_semifinal_DW.Integrator_DSTATE_m[2] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S78>/Filter' incorporates:
  //   Gain: '<S86>/Filter Coefficient'

  matlab_semifinal_DW.Filter_DSTATE_d[2] += 0.01 *
    matlab_semifinal_B.rtb_dRb_u_d;

  // Switch: '<S188>/Switch1' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant'
  //   Constant: '<S188>/Constant2'
  //   RelationalOperator: '<S188>/fix for DT propagation issue'

  if (matlab_semifinal_B.rtb_DeadZone_p_idx_1 > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Gain: '<S195>/Integral Gain'
  matlab_semifinal_B.b_t = 20.0 * matlab_semifinal_B.dRb_e[2];

  // Switch: '<S188>/Switch2' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant3'
  //   Constant: '<S188>/Constant4'
  //   Gain: '<S195>/Integral Gain'
  //   RelationalOperator: '<S188>/fix for DT propagation issue1'

  if (matlab_semifinal_B.b_t > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  // Switch: '<S188>/Switch' incorporates:
  //   Constant: '<S188>/Clamping_zero'
  //   Constant: '<S188>/Constant1'
  //   Logic: '<S188>/AND3'
  //   RelationalOperator: '<S188>/Equal1'
  //   RelationalOperator: '<S188>/Relational Operator'
  //   Switch: '<S188>/Switch1'
  //   Switch: '<S188>/Switch2'

  if ((matlab_semifinal_B.rtb_DeadZone_p_idx_1 != 0.0) && (tmp_0 == tmp_1)) {
    matlab_semifinal_B.b_t = 0.0;
  }

  // Update for DiscreteIntegrator: '<S198>/Integrator' incorporates:
  //   Switch: '<S188>/Switch'

  matlab_semifinal_B.idx = 0.01 * matlab_semifinal_B.b_t +
    matlab_semifinal_DW.Integrator_DSTATE_d[2];
  matlab_semifinal_DW.Integrator_DSTATE_d[2] = matlab_semifinal_B.idx;
  if (matlab_semifinal_B.idx > 100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[2] = 100.0;
  } else if (matlab_semifinal_B.idx < -100.0) {
    matlab_semifinal_DW.Integrator_DSTATE_d[2] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S193>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   DiscreteIntegrator: '<S32>/Discrete-Time Integrator'
  //   Gain: '<S201>/Filter Coefficient'

  matlab_semifinal_DW.Filter_DSTATE_c[2] += 0.01 *
    matlab_semifinal_B.rtb_Cbi_tmp_tmp;
  matlab_semifinal_DW.Filter_PrevResetState_k = static_cast<int8_T>(reset_pids);

  // Update for UnitDelay: '<S30>/Delay Input1' incorporates:
  //   RelationalOperator: '<S101>/Compare'
  //
  //  Block description for '<S30>/Delay Input1':
  //
  //   Store in Global RAM

  matlab_semifinal_DW.DelayInput1_DSTATE_g = matlab_semifinal_B.dropper_trigger;

  // Update absolute time
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&matlab_semifinal_M)->Timing.clockTick0++;
}

// Model step function for TID1
void matlab_semifinal::step1()         // Sample time: [0.5s, 0.0s]
{
  // MATLABSystem: '<S235>/SinkBlock' incorporates:
  //   Constant: '<S234>/Constant'

  Pub_matlab_semifinal_625_150.publish(&matlab_semifinal_ConstP.Constant_Value_n);
}

// Use this function only if you need to maintain compatibility with an existing static main program.
void matlab_semifinal_step(matlab_semifinal & matlab_semifinal_Obj_In, int_T tid)
{
  switch (tid) {
   case 0 :
    matlab_semifinal_Obj_In.step0();
    break;

   case 1 :
    matlab_semifinal_Obj_In.step1();
    break;

   default :
    // do nothing
    break;
  }
}

// Model initialize function
void matlab_semifinal::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S6>/Position Integrator'
  matlab_semifinal_DW.PositionIntegrator_PrevResetSta = 2;
  matlab_semifinal_DW.PositionIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S6>/Velocity Integrator'
  matlab_semifinal_DW.VelocityIntegrator_PrevResetSta = 2;
  matlab_semifinal_DW.VelocityIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S32>/Discrete-Time Integrator' 
  matlab_semifinal_DW.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S139>/Integrator'
  matlab_semifinal_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S134>/Filter'
  matlab_semifinal_DW.Filter_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S83>/Integrator'
  matlab_semifinal_DW.Integrator_PrevResetState_d = 2;

  // InitializeConditions for DiscreteIntegrator: '<S78>/Filter'
  matlab_semifinal_DW.Filter_PrevResetState_g = 2;

  // InitializeConditions for DiscreteIntegrator: '<S198>/Integrator'
  matlab_semifinal_DW.Integrator_PrevResetState_p = 2;

  // InitializeConditions for DiscreteIntegrator: '<S193>/Filter'
  matlab_semifinal_DW.Filter_PrevResetState_k = 2;

  // SystemInitialize for Enabled SubSystem: '<S1>/Subsystem'
  // Start for MATLABSystem: '<S22>/SinkBlock'
  matlab_semifinal_DW.obj_f.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_f.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_f.isSetupComplete = false;
  matlab_semifinal_DW.obj_f.isInitialized = 1;
  matlab_semi_Publisher_setupImpl(&matlab_semifinal_DW.obj_f);
  matlab_semifinal_DW.obj_f.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S1>/Subsystem'

  // SystemInitialize for Enabled SubSystem: '<S33>/Subsystem'
  // Start for MATLABSystem: '<S160>/SinkBlock'
  matlab_semifinal_DW.obj_oc.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_oc.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_oc.isSetupComplete = false;
  matlab_semifinal_DW.obj_oc.isInitialized = 1;
  matlab_se_Publisher_setupImpl_m(&matlab_semifinal_DW.obj_oc);
  matlab_semifinal_DW.obj_oc.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S33>/Subsystem'

  // SystemInitialize for MATLAB Function: '<S33>/Dropper Magazine'
  matlab_semifinal_DW.ammo = 2.0;

  // SystemInitialize for MATLAB Function: '<S25>/guidanceLaw'
  matlab_semifinal_DW.action_id = 1.0;
  matlab_semifinal_DW.prior_Ri_u[0] = 999.0;
  matlab_semifinal_DW.prior_Ri_u[1] = 999.0;
  matlab_semifinal_DW.prior_Ri_u[2] = 999.0;

  // SystemInitialize for MATLAB Function: '<S6>/dvl_reset'
  matlab_semifinal_DW.prior_flag = true;

  // Start for MATLABSystem: '<S231>/SourceBlock'
  matlab_semifinal_DW.obj.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj.isSetupComplete = false;
  matlab_semifinal_DW.obj.isInitialized = 1;
  matl_Subscriber_setupImpl_mj3b3(&matlab_semifinal_DW.obj);
  matlab_semifinal_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  matlab_semifinal_DW.obj_b.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_b.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_b.isSetupComplete = false;
  matlab_semifinal_DW.obj_b.isInitialized = 1;
  matlab__Subscriber_setupImpl_mj(&matlab_semifinal_DW.obj_b);
  matlab_semifinal_DW.obj_b.isSetupComplete = true;

  // Start for MATLABSystem: '<S8>/SourceBlock'
  matlab_semifinal_DW.obj_p.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_p.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_p.isSetupComplete = false;
  matlab_semifinal_DW.obj_p.isInitialized = 1;
  matlab_Subscriber_setupImpl_mj3(&matlab_semifinal_DW.obj_p);
  matlab_semifinal_DW.obj_p.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  matlab_semifinal_DW.obj_bu.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_bu.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_bu.isSetupComplete = false;
  matlab_semifinal_DW.obj_bu.isInitialized = 1;
  matlab_s_Subscriber_setupImpl_m(&matlab_semifinal_DW.obj_bu);
  matlab_semifinal_DW.obj_bu.isSetupComplete = true;

  // Start for MATLABSystem: '<S17>/SourceBlock'
  matlab_semifinal_DW.obj_j.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_j.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_j.isSetupComplete = false;
  matlab_semifinal_DW.obj_j.isInitialized = 1;
  matlab_sem_Subscriber_setupImpl(&matlab_semifinal_DW.obj_j);
  matlab_semifinal_DW.obj_j.isSetupComplete = true;

  // Start for MATLABSystem: '<S228>/SourceBlock'
  matlab_semifinal_DW.obj_i.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_i.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_i.isSetupComplete = false;
  matlab_semifinal_DW.obj_i.isInitialized = 1;
  matla_Subscriber_setupImpl_mj3b(&matlab_semifinal_DW.obj_i);
  matlab_semifinal_DW.obj_i.isSetupComplete = true;

  // Start for MATLABSystem: '<S236>/SinkBlock'
  matlab_semifinal_DW.obj_n.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_n.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_n.isSetupComplete = false;
  matlab_semifinal_DW.obj_n.isInitialized = 1;
  matlab_Publisher_setupImpl_mj3b(&matlab_semifinal_DW.obj_n);
  matlab_semifinal_DW.obj_n.isSetupComplete = true;

  // Start for MATLABSystem: '<S226>/SinkBlock'
  matlab_semifinal_DW.obj_iq.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_iq.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_iq.isSetupComplete = false;
  matlab_semifinal_DW.obj_iq.isInitialized = 1;
  matlab_s_Publisher_setupImpl_mj(&matlab_semifinal_DW.obj_iq);
  matlab_semifinal_DW.obj_iq.isSetupComplete = true;

  // Start for MATLABSystem: '<S235>/SinkBlock'
  matlab_semifinal_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
  matlab_semifinal_DW.obj_o.matlabCodegenIsDeleted = false;
  matlab_semifinal_DW.obj_o.isSetupComplete = false;
  matlab_semifinal_DW.obj_o.isInitialized = 1;
  matlab__Publisher_setupImpl_mj3(&matlab_semifinal_DW.obj_o);
  matlab_semifinal_DW.obj_o.isSetupComplete = true;
}

// Model terminate function
void matlab_semifinal::terminate()
{
  // Terminate for MATLABSystem: '<S231>/SourceBlock'
  if (!matlab_semifinal_DW.obj.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj.isInitialized == 1) &&
        matlab_semifinal_DW.obj.isSetupComplete) {
      Sub_matlab_semifinal_618.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S231>/SourceBlock'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!matlab_semifinal_DW.obj_b.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_b.isInitialized == 1) &&
        matlab_semifinal_DW.obj_b.isSetupComplete) {
      Sub_matlab_semifinal_587.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S8>/SourceBlock'
  if (!matlab_semifinal_DW.obj_p.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_p.isInitialized == 1) &&
        matlab_semifinal_DW.obj_p.isSetupComplete) {
      Sub_matlab_semifinal_602.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S8>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!matlab_semifinal_DW.obj_bu.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_bu.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_bu.isInitialized == 1) &&
        matlab_semifinal_DW.obj_bu.isSetupComplete) {
      Sub_matlab_semifinal_552.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S17>/SourceBlock'
  if (!matlab_semifinal_DW.obj_j.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_j.isInitialized == 1) &&
        matlab_semifinal_DW.obj_j.isSetupComplete) {
      Sub_matlab_semifinal_549_284.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S17>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S1>/Subsystem'
  // Terminate for MATLABSystem: '<S22>/SinkBlock'
  if (!matlab_semifinal_DW.obj_f.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_f.isInitialized == 1) &&
        matlab_semifinal_DW.obj_f.isSetupComplete) {
      Pub_matlab_semifinal_549_7.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S22>/SinkBlock'
  // End of Terminate for SubSystem: '<S1>/Subsystem'

  // Terminate for MATLABSystem: '<S228>/SourceBlock'
  if (!matlab_semifinal_DW.obj_i.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_i.isInitialized == 1) &&
        matlab_semifinal_DW.obj_i.isSetupComplete) {
      Sub_matlab_semifinal_606.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S228>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S33>/Subsystem'
  // Terminate for MATLABSystem: '<S160>/SinkBlock'
  if (!matlab_semifinal_DW.obj_oc.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_oc.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_oc.isInitialized == 1) &&
        matlab_semifinal_DW.obj_oc.isSetupComplete) {
      Pub_matlab_semifinal_588_262_826_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S160>/SinkBlock'
  // End of Terminate for SubSystem: '<S33>/Subsystem'

  // Terminate for MATLABSystem: '<S236>/SinkBlock'
  if (!matlab_semifinal_DW.obj_n.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_n.isInitialized == 1) &&
        matlab_semifinal_DW.obj_n.isSetupComplete) {
      Pub_matlab_semifinal_626_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S236>/SinkBlock'

  // Terminate for MATLABSystem: '<S226>/SinkBlock'
  if (!matlab_semifinal_DW.obj_iq.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_iq.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_iq.isInitialized == 1) &&
        matlab_semifinal_DW.obj_iq.isSetupComplete) {
      Pub_matlab_semifinal_594_3.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S226>/SinkBlock'

  // Terminate for MATLABSystem: '<S235>/SinkBlock'
  if (!matlab_semifinal_DW.obj_o.matlabCodegenIsDeleted) {
    matlab_semifinal_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((matlab_semifinal_DW.obj_o.isInitialized == 1) &&
        matlab_semifinal_DW.obj_o.isSetupComplete) {
      Pub_matlab_semifinal_625_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S235>/SinkBlock'
}

// Constructor
matlab_semifinal::matlab_semifinal() :
  matlab_semifinal_B(),
  matlab_semifinal_DW(),
  matlab_semifinal_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
matlab_semifinal::~matlab_semifinal() = default;

// Real-Time Model get method
RT_MODEL_matlab_semifinal_T * matlab_semifinal::getRTM()
{
  return (&matlab_semifinal_M);
}

uint8_T &RT_MODEL_matlab_semifinal_T::TaskCounter(int32_T idx)
{
  return (Timing.TaskCounters.TID[(idx)]);
}

boolean_T RT_MODEL_matlab_semifinal_T::StepTask(int32_T idx) const
{
  return (Timing.TaskCounters.TID[(idx)] == 0);
}

const char_T* RT_MODEL_matlab_semifinal_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_matlab_semifinal_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
