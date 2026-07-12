//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: joystick_enabled_matlab_node.cpp
//
// Code generated for Simulink model 'joystick_enabled_matlab_node'.
//
// Model version                  : 1.11
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sun Jul 12 15:12:27 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "joystick_enabled_matlab_node.h"
#include "rtwtypes.h"
#include "joystick_enabled_matlab_node_types.h"
#include <cmath>
#include "joystick_enabled_matlab_node_private.h"
#include <cstring>
#include "rmw/qos_profiles.h"
#include <stddef.h>
#include "rt_defines.h"
#include "cmath"

static void rate_monotonic_scheduler(RT_MODEL_joystick_enabled_mat_T *const
  joystick_enabled_matlab_node_M);

//
// Set which subrates need to run this base step (base rate always runs).
// This function must be called prior to calling the model step function
// in order to remember which rates need to run this base step.  The
// buffering of events allows for overlapping preemption.
//
void joystick_enabled_matlab_node_SetEventsForThisBaseStep(boolean_T *eventFlags,
  RT_MODEL_joystick_enabled_mat_T *const joystick_enabled_matlab_node_M)
{
  // Task runs when its counter is zero, computed via rtmStepTask macro
  eventFlags[1] = ((boolean_T)joystick_enabled_matlab_node_M->StepTask(1));
}

//
//         This function updates active task flag for each subrate
//         and rate transition flags for tasks that exchange data.
//         The function assumes rate-monotonic multitasking scheduler.
//         The function must be called at model base rate so that
//         the generated code self-manages all its subrates and rate
//         transition flags.
//
static void rate_monotonic_scheduler(RT_MODEL_joystick_enabled_mat_T *const
  joystick_enabled_matlab_node_M)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (joystick_enabled_matlab_node_M->Timing.TaskCounters.TID[1])++;
  if ((joystick_enabled_matlab_node_M->Timing.TaskCounters.TID[1]) > 49) {// Sample time: [0.5s, 0.0s] 
    joystick_enabled_matlab_node_M->Timing.TaskCounters.TID[1] = 0;
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
void joystick_enabled_matlab_node::joystick_enabled_matla_wrapToPi(real_T
  *lambda)
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
void joystick_enabled_matlab_node::joystick_enabled__quatToEul(const real_T
  rtu_qib_u[4], real_T rty_Eul_u[3], B_quatToEul_joystick_enabled__T *localB)
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

  joystick_enabled_matla_wrapToPi(&rty_Eul_u[0]);
  rty_Eul_u[1] = -b_a;
  joystick_enabled_matla_wrapToPi(&rty_Eul_u[1]);
  joystick_enabled_matla_wrapToPi(&psi);
  rty_Eul_u[2] = psi;
}

real_T joystick_enabled_matlab_node::joystick_enabled__rt_atan2d_snf(real_T u0,
  real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    if (u0 > 0.0) {
      joystick_enabled_matlab_node_B.i1 = 1;
    } else {
      joystick_enabled_matlab_node_B.i1 = -1;
    }

    if (u1 > 0.0) {
      joystick_enabled_matlab_node_B.i2 = 1;
    } else {
      joystick_enabled_matlab_node_B.i2 = -1;
    }

    y = std::atan2(static_cast<real_T>(joystick_enabled_matlab_node_B.i1),
                   static_cast<real_T>(joystick_enabled_matlab_node_B.i2));
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
void joystick_enabled_matlab_node::joystick_enabled_mat_wrapToPi_k(real_T
  *lambda)
{
  boolean_T tmp;
  joystick_enabled_matlab_node_B.trueCount = 0;
  tmp = ((*lambda < -3.1415926535897931) || (*lambda > 3.1415926535897931));
  if (tmp) {
    for (joystick_enabled_matlab_node_B.i_i = 0;
         joystick_enabled_matlab_node_B.i_i < 1;
         joystick_enabled_matlab_node_B.i_i++) {
      joystick_enabled_matlab_node_B.trueCount++;
    }
  }

  if (joystick_enabled_matlab_node_B.trueCount - 1 >= 0) {
    if (std::isnan(*lambda + 3.1415926535897931)) {
      joystick_enabled_matlab_node_B.q_n = (rtNaN);
    } else if (std::isinf(*lambda + 3.1415926535897931)) {
      joystick_enabled_matlab_node_B.q_n = (rtNaN);
    } else {
      joystick_enabled_matlab_node_B.q_n = std::abs((*lambda +
        3.1415926535897931) / 6.2831853071795862);
      if (std::abs(joystick_enabled_matlab_node_B.q_n - std::floor
                   (joystick_enabled_matlab_node_B.q_n + 0.5)) >
          2.2204460492503131E-16 * joystick_enabled_matlab_node_B.q_n) {
        joystick_enabled_matlab_node_B.q_n = std::fmod(*lambda +
          3.1415926535897931, 6.2831853071795862);
      } else {
        joystick_enabled_matlab_node_B.q_n = 0.0;
      }

      if (joystick_enabled_matlab_node_B.q_n == 0.0) {
        joystick_enabled_matlab_node_B.q_n = 0.0;
      } else if (joystick_enabled_matlab_node_B.q_n < 0.0) {
        joystick_enabled_matlab_node_B.q_n += 6.2831853071795862;
      }
    }

    joystick_enabled_matlab_node_B.varargin_1_data =
      joystick_enabled_matlab_node_B.q_n;
  }

  for (joystick_enabled_matlab_node_B.i_i = 0;
       joystick_enabled_matlab_node_B.i_i <
       joystick_enabled_matlab_node_B.trueCount;
       joystick_enabled_matlab_node_B.i_i++) {
    joystick_enabled_matlab_node_B.i_f = 0;
    if ((joystick_enabled_matlab_node_B.varargin_1_data == 0.0) && (*lambda +
         3.1415926535897931 > 0.0)) {
      joystick_enabled_matlab_node_B.varargin_1_data = 6.2831853071795862;
    }
  }

  if (tmp) {
    *lambda = joystick_enabled_matlab_node_B.varargin_1_data -
      3.1415926535897931;
  }
}

// Function for MATLAB Function: '<S26>/commandExecuter'
void joystick_enabled_matlab_node::joystick_enabled_ma_eulToQuat_f(const real_T
  Eul[3], real_T qib[4])
{
  joystick_enabled_matlab_node_B.eta_j = std::cos(Eul[1]);
  joystick_enabled_matlab_node_B.scale_j = std::sin(Eul[1]);
  joystick_enabled_matlab_node_B.b_t_n = std::cos(Eul[2]);
  joystick_enabled_matlab_node_B.rotm_tmp_i = std::sin(Eul[2]);
  joystick_enabled_matlab_node_B.eps_idx_1 = std::sin(Eul[0]);
  joystick_enabled_matlab_node_B.rotm_tmp_o = std::cos(Eul[0]);
  joystick_enabled_matlab_node_B.rotm_idx_0 =
    joystick_enabled_matlab_node_B.eta_j * joystick_enabled_matlab_node_B.b_t_n;
  joystick_enabled_matlab_node_B.eps_idx_2 =
    joystick_enabled_matlab_node_B.eta_j *
    joystick_enabled_matlab_node_B.rotm_tmp_i;
  joystick_enabled_matlab_node_B.rotm_idx_4_tmp =
    joystick_enabled_matlab_node_B.eps_idx_1 *
    joystick_enabled_matlab_node_B.scale_j;
  joystick_enabled_matlab_node_B.eps_idx_0 =
    joystick_enabled_matlab_node_B.rotm_idx_4_tmp *
    joystick_enabled_matlab_node_B.rotm_tmp_i +
    joystick_enabled_matlab_node_B.rotm_tmp_o *
    joystick_enabled_matlab_node_B.b_t_n;
  joystick_enabled_matlab_node_B.absxk_o =
    joystick_enabled_matlab_node_B.eps_idx_1 *
    joystick_enabled_matlab_node_B.eta_j;
  joystick_enabled_matlab_node_B.rotm_idx_8 =
    joystick_enabled_matlab_node_B.rotm_tmp_o *
    joystick_enabled_matlab_node_B.eta_j;
  joystick_enabled_matlab_node_B.eta_j = std::sqrt
    (((joystick_enabled_matlab_node_B.rotm_idx_0 +
       joystick_enabled_matlab_node_B.eps_idx_0) +
      joystick_enabled_matlab_node_B.rotm_idx_8) + 1.0) / 2.0;
  if (joystick_enabled_matlab_node_B.eta_j != 0.0) {
    joystick_enabled_matlab_node_B.rotm_idx_0 =
      joystick_enabled_matlab_node_B.rotm_tmp_o *
      joystick_enabled_matlab_node_B.scale_j;
    joystick_enabled_matlab_node_B.rotm_idx_8 = 4.0 *
      joystick_enabled_matlab_node_B.eta_j;
    joystick_enabled_matlab_node_B.eps_idx_0 =
      (joystick_enabled_matlab_node_B.absxk_o -
       (joystick_enabled_matlab_node_B.rotm_idx_0 *
        joystick_enabled_matlab_node_B.rotm_tmp_i -
        joystick_enabled_matlab_node_B.eps_idx_1 *
        joystick_enabled_matlab_node_B.b_t_n)) /
      joystick_enabled_matlab_node_B.rotm_idx_8;
    joystick_enabled_matlab_node_B.eps_idx_1 =
      ((joystick_enabled_matlab_node_B.rotm_idx_0 *
        joystick_enabled_matlab_node_B.b_t_n +
        joystick_enabled_matlab_node_B.eps_idx_1 *
        joystick_enabled_matlab_node_B.rotm_tmp_i) -
       (-joystick_enabled_matlab_node_B.scale_j)) /
      joystick_enabled_matlab_node_B.rotm_idx_8;
    joystick_enabled_matlab_node_B.eps_idx_2 =
      (joystick_enabled_matlab_node_B.eps_idx_2 -
       (joystick_enabled_matlab_node_B.rotm_idx_4_tmp *
        joystick_enabled_matlab_node_B.b_t_n -
        joystick_enabled_matlab_node_B.rotm_tmp_o *
        joystick_enabled_matlab_node_B.rotm_tmp_i)) /
      joystick_enabled_matlab_node_B.rotm_idx_8;
  } else {
    joystick_enabled_matlab_node_B.b_t_n =
      (joystick_enabled_matlab_node_B.rotm_idx_0 + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x[0] = joystick_enabled_matlab_node_B.b_t_n;
    joystick_enabled_matlab_node_B.eps_idx_1 =
      (joystick_enabled_matlab_node_B.eps_idx_0 + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x[1] =
      joystick_enabled_matlab_node_B.eps_idx_1;
    joystick_enabled_matlab_node_B.rotm_tmp_i =
      (joystick_enabled_matlab_node_B.rotm_idx_8 + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x[2] =
      joystick_enabled_matlab_node_B.rotm_tmp_i;
    if (!std::isnan(joystick_enabled_matlab_node_B.b_t_n)) {
      joystick_enabled_matlab_node_B.idx_i = 1;
    } else {
      boolean_T exitg1;
      joystick_enabled_matlab_node_B.idx_i = 0;
      joystick_enabled_matlab_node_B.b_k = 2;
      exitg1 = false;
      while ((!exitg1) && (joystick_enabled_matlab_node_B.b_k < 4)) {
        if (!std::isnan
            (joystick_enabled_matlab_node_B.x[joystick_enabled_matlab_node_B.b_k
             - 1])) {
          joystick_enabled_matlab_node_B.idx_i =
            joystick_enabled_matlab_node_B.b_k;
          exitg1 = true;
        } else {
          joystick_enabled_matlab_node_B.b_k++;
        }
      }
    }

    if (joystick_enabled_matlab_node_B.idx_i == 0) {
      joystick_enabled_matlab_node_B.b_k = 1;
    } else {
      joystick_enabled_matlab_node_B.eps_idx_0 =
        joystick_enabled_matlab_node_B.x[joystick_enabled_matlab_node_B.idx_i -
        1];
      joystick_enabled_matlab_node_B.b_k = joystick_enabled_matlab_node_B.idx_i;
      for (joystick_enabled_matlab_node_B.c_k =
           joystick_enabled_matlab_node_B.idx_i + 1;
           joystick_enabled_matlab_node_B.c_k < 4;
           joystick_enabled_matlab_node_B.c_k++) {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          joystick_enabled_matlab_node_B.x[joystick_enabled_matlab_node_B.c_k -
          1];
        if (joystick_enabled_matlab_node_B.eps_idx_0 <
            joystick_enabled_matlab_node_B.rotm_tmp_o) {
          joystick_enabled_matlab_node_B.eps_idx_0 =
            joystick_enabled_matlab_node_B.rotm_tmp_o;
          joystick_enabled_matlab_node_B.b_k =
            joystick_enabled_matlab_node_B.c_k;
        }
      }
    }

    switch (joystick_enabled_matlab_node_B.b_k) {
     case 1:
      joystick_enabled_matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_n));
      if (std::isnan(joystick_enabled_matlab_node_B.eps_idx_2)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.eps_idx_2 < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (joystick_enabled_matlab_node_B.eps_idx_2 > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      if (std::isnan(-joystick_enabled_matlab_node_B.scale_j)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.scale_j < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (-joystick_enabled_matlab_node_B.scale_j > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_i)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      break;

     case 2:
      joystick_enabled_matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1));
      if (std::isnan(joystick_enabled_matlab_node_B.eps_idx_2)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.eps_idx_2 < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (joystick_enabled_matlab_node_B.eps_idx_2 > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_n)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      if (std::isnan(joystick_enabled_matlab_node_B.absxk_o)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.absxk_o < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (joystick_enabled_matlab_node_B.absxk_o > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_i)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      break;

     default:
      joystick_enabled_matlab_node_B.eps_idx_2 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_i));
      if (std::isnan(-joystick_enabled_matlab_node_B.scale_j)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.scale_j < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (-joystick_enabled_matlab_node_B.scale_j > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_0 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_n)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      if (std::isnan(joystick_enabled_matlab_node_B.absxk_o)) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.absxk_o < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_o = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_o =
          (joystick_enabled_matlab_node_B.absxk_o > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_1 = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1)) *
        joystick_enabled_matlab_node_B.rotm_tmp_o;
      break;
    }
  }

  joystick_enabled_matlab_node_B.scale_j = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_B.absxk_o = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_0);
  if (joystick_enabled_matlab_node_B.absxk_o > 3.3121686421112381E-170) {
    joystick_enabled_matlab_node_B.rotm_tmp_i = 1.0;
    joystick_enabled_matlab_node_B.scale_j =
      joystick_enabled_matlab_node_B.absxk_o;
  } else {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.absxk_o / 3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.rotm_tmp_i =
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n;
  }

  joystick_enabled_matlab_node_B.absxk_o = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_1);
  if (joystick_enabled_matlab_node_B.absxk_o >
      joystick_enabled_matlab_node_B.scale_j) {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.scale_j /
      joystick_enabled_matlab_node_B.absxk_o;
    joystick_enabled_matlab_node_B.rotm_tmp_i =
      joystick_enabled_matlab_node_B.rotm_tmp_i *
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n + 1.0;
    joystick_enabled_matlab_node_B.scale_j =
      joystick_enabled_matlab_node_B.absxk_o;
  } else {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.absxk_o /
      joystick_enabled_matlab_node_B.scale_j;
    joystick_enabled_matlab_node_B.rotm_tmp_i +=
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n;
  }

  joystick_enabled_matlab_node_B.absxk_o = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_2);
  if (joystick_enabled_matlab_node_B.absxk_o >
      joystick_enabled_matlab_node_B.scale_j) {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.scale_j /
      joystick_enabled_matlab_node_B.absxk_o;
    joystick_enabled_matlab_node_B.rotm_tmp_i =
      joystick_enabled_matlab_node_B.rotm_tmp_i *
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n + 1.0;
    joystick_enabled_matlab_node_B.scale_j =
      joystick_enabled_matlab_node_B.absxk_o;
  } else {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.absxk_o /
      joystick_enabled_matlab_node_B.scale_j;
    joystick_enabled_matlab_node_B.rotm_tmp_i +=
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n;
  }

  if (joystick_enabled_matlab_node_B.eta_j >
      joystick_enabled_matlab_node_B.scale_j) {
    joystick_enabled_matlab_node_B.b_t_n =
      joystick_enabled_matlab_node_B.scale_j /
      joystick_enabled_matlab_node_B.eta_j;
    joystick_enabled_matlab_node_B.rotm_tmp_i =
      joystick_enabled_matlab_node_B.rotm_tmp_i *
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n + 1.0;
    joystick_enabled_matlab_node_B.scale_j =
      joystick_enabled_matlab_node_B.eta_j;
  } else {
    joystick_enabled_matlab_node_B.b_t_n = joystick_enabled_matlab_node_B.eta_j /
      joystick_enabled_matlab_node_B.scale_j;
    joystick_enabled_matlab_node_B.rotm_tmp_i +=
      joystick_enabled_matlab_node_B.b_t_n *
      joystick_enabled_matlab_node_B.b_t_n;
  }

  joystick_enabled_matlab_node_B.rotm_tmp_i =
    joystick_enabled_matlab_node_B.scale_j * std::sqrt
    (joystick_enabled_matlab_node_B.rotm_tmp_i);
  qib[0] = joystick_enabled_matlab_node_B.eps_idx_0 /
    joystick_enabled_matlab_node_B.rotm_tmp_i;
  qib[1] = joystick_enabled_matlab_node_B.eps_idx_1 /
    joystick_enabled_matlab_node_B.rotm_tmp_i;
  qib[2] = joystick_enabled_matlab_node_B.eps_idx_2 /
    joystick_enabled_matlab_node_B.rotm_tmp_i;
  qib[3] = joystick_enabled_matlab_node_B.eta_j /
    joystick_enabled_matlab_node_B.rotm_tmp_i;
}

// Function for MATLAB Function: '<S26>/commandExecuter'
boolean_T joystick_enabled_matlab_node::joystick_enabled_ma_withinWPTol(const
  real_T X_Ri[3], const real_T X_qib[4], const real_T X_u[13], const real_T
  cmd_wp_tol[6])
{
  boolean_T tf;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  boolean_T exitg1;
  joystick_enabled_matlab_node_B.qe_matlab_idx_0 = ((X_qib[3] * X_u[6] - -X_qib
    [0] * X_u[3]) - -X_qib[1] * X_u[4]) - -X_qib[2] * X_u[5];
  joystick_enabled_matlab_node_B.qe_matlab_idx_1 = (X_qib[3] * X_u[3] + X_u[6] *
    -X_qib[0]) + (-X_qib[1] * X_u[5] - X_u[4] * -X_qib[2]);
  joystick_enabled_matlab_node_B.qe_matlab_idx_2 = (X_qib[3] * X_u[4] + X_u[6] *
    -X_qib[1]) + (X_u[3] * -X_qib[2] - -X_qib[0] * X_u[5]);
  joystick_enabled_matlab_node_B.qe_matlab_idx_3 = (X_qib[3] * X_u[5] + X_u[6] *
    -X_qib[2]) + (-X_qib[0] * X_u[4] - X_u[3] * -X_qib[1]);
  joystick_enabled_matlab_node_B.qinv_m[0] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_1;
  joystick_enabled_matlab_node_B.qinv_m[1] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_2;
  joystick_enabled_matlab_node_B.qinv_m[2] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_3;
  joystick_enabled_matlab_node_B.qinv_m[3] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0;
  if (joystick_enabled_matlab_node_B.qe_matlab_idx_0 < 0.0) {
    joystick_enabled_matlab_node_B.qinv_m[0] =
      -joystick_enabled_matlab_node_B.qe_matlab_idx_1;
    joystick_enabled_matlab_node_B.qinv_m[1] =
      -joystick_enabled_matlab_node_B.qe_matlab_idx_2;
    joystick_enabled_matlab_node_B.qinv_m[2] =
      -joystick_enabled_matlab_node_B.qe_matlab_idx_3;
    joystick_enabled_matlab_node_B.qinv_m[3] =
      -joystick_enabled_matlab_node_B.qe_matlab_idx_0;
  }

  joystick_enabled_matlab_node_B.qe_matlab_idx_1 =
    joystick_enabled_matlab_node_B.qinv_m[3] *
    joystick_enabled_matlab_node_B.qinv_m[3] * 2.0 - 1.0;
  joystick_enabled_matlab_node_B.qe_matlab_idx_0 = 2.0 *
    joystick_enabled_matlab_node_B.qinv_m[3];
  for (joystick_enabled_matlab_node_B.c_k_f = 0;
       joystick_enabled_matlab_node_B.c_k_f < 3;
       joystick_enabled_matlab_node_B.c_k_f++) {
    joystick_enabled_matlab_node_B.qe_matlab_idx_2 = 2.0 *
      joystick_enabled_matlab_node_B.qinv_m[joystick_enabled_matlab_node_B.c_k_f];
    joystick_enabled_matlab_node_B.a[3 * joystick_enabled_matlab_node_B.c_k_f] =
      joystick_enabled_matlab_node_B.qe_matlab_idx_2 *
      joystick_enabled_matlab_node_B.qinv_m[0] +
      joystick_enabled_matlab_node_B.qe_matlab_idx_1 * static_cast<real_T>
      (b[joystick_enabled_matlab_node_B.c_k_f]);
    joystick_enabled_matlab_node_B.a[3 * joystick_enabled_matlab_node_B.c_k_f +
      1] = static_cast<real_T>(b[joystick_enabled_matlab_node_B.c_k_f + 3]) *
      joystick_enabled_matlab_node_B.qe_matlab_idx_1 +
      joystick_enabled_matlab_node_B.qe_matlab_idx_2 *
      joystick_enabled_matlab_node_B.qinv_m[1];
    joystick_enabled_matlab_node_B.a[3 * joystick_enabled_matlab_node_B.c_k_f +
      2] = static_cast<real_T>(b[joystick_enabled_matlab_node_B.c_k_f + 6]) *
      joystick_enabled_matlab_node_B.qe_matlab_idx_1 +
      joystick_enabled_matlab_node_B.qe_matlab_idx_2 *
      joystick_enabled_matlab_node_B.qinv_m[2];
  }

  joystick_enabled_matlab_node_B.qe_matlab_idx_1 =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 * 0.0;
  joystick_enabled_matlab_node_B.b_a[0] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_1;
  joystick_enabled_matlab_node_B.b_a[1] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    -joystick_enabled_matlab_node_B.qinv_m[2];
  joystick_enabled_matlab_node_B.b_a[2] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    joystick_enabled_matlab_node_B.qinv_m[1];
  joystick_enabled_matlab_node_B.b_a[3] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    joystick_enabled_matlab_node_B.qinv_m[2];
  joystick_enabled_matlab_node_B.b_a[4] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_1;
  joystick_enabled_matlab_node_B.b_a[5] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    -joystick_enabled_matlab_node_B.qinv_m[0];
  joystick_enabled_matlab_node_B.b_a[6] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    -joystick_enabled_matlab_node_B.qinv_m[1];
  joystick_enabled_matlab_node_B.b_a[7] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 *
    joystick_enabled_matlab_node_B.qinv_m[0];
  joystick_enabled_matlab_node_B.b_a[8] =
    joystick_enabled_matlab_node_B.qe_matlab_idx_1;
  for (joystick_enabled_matlab_node_B.c_k_f = 0;
       joystick_enabled_matlab_node_B.c_k_f < 9;
       joystick_enabled_matlab_node_B.c_k_f++) {
    joystick_enabled_matlab_node_B.Cbi_p[joystick_enabled_matlab_node_B.c_k_f] =
      joystick_enabled_matlab_node_B.a[joystick_enabled_matlab_node_B.c_k_f] +
      joystick_enabled_matlab_node_B.b_a[joystick_enabled_matlab_node_B.c_k_f];
  }

  joystick_enabled_matlab_node_B.qe_matlab_idx_2 = std::asin(std::fmax(-1.0, std::
    fmin(1.0, joystick_enabled_matlab_node_B.Cbi_p[6])));
  if (std::abs(std::cos(-joystick_enabled_matlab_node_B.qe_matlab_idx_2)) <
      1.0E-6) {
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 = 0.0;
    joystick_enabled_matlab_node_B.qe_matlab_idx_1 =
      joystick_enabled__rt_atan2d_snf(-joystick_enabled_matlab_node_B.Cbi_p[1],
      joystick_enabled_matlab_node_B.Cbi_p[4]);
  } else {
    joystick_enabled_matlab_node_B.qe_matlab_idx_0 =
      joystick_enabled__rt_atan2d_snf(joystick_enabled_matlab_node_B.Cbi_p[7],
      joystick_enabled_matlab_node_B.Cbi_p[8]);
    joystick_enabled_matlab_node_B.qe_matlab_idx_1 =
      joystick_enabled__rt_atan2d_snf(joystick_enabled_matlab_node_B.Cbi_p[3],
      joystick_enabled_matlab_node_B.Cbi_p[0]);
  }

  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.qe_matlab_idx_0);
  joystick_enabled_matlab_node_B.qe_matlab_idx_2 =
    -joystick_enabled_matlab_node_B.qe_matlab_idx_2;
  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.qe_matlab_idx_2);
  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.qe_matlab_idx_1);
  joystick_enabled_matlab_node_B.R_error[0] = std::abs(X_Ri[0] - X_u[0]);
  joystick_enabled_matlab_node_B.R_error[3] = std::abs
    (joystick_enabled_matlab_node_B.qe_matlab_idx_0);
  joystick_enabled_matlab_node_B.R_error[1] = std::abs(X_Ri[1] - X_u[1]);
  joystick_enabled_matlab_node_B.R_error[4] = std::abs
    (joystick_enabled_matlab_node_B.qe_matlab_idx_2);
  joystick_enabled_matlab_node_B.R_error[2] = std::abs(X_Ri[2] - X_u[2]);
  joystick_enabled_matlab_node_B.R_error[5] = std::abs
    (joystick_enabled_matlab_node_B.qe_matlab_idx_1);
  for (joystick_enabled_matlab_node_B.c_k_f = 0;
       joystick_enabled_matlab_node_B.c_k_f < 6;
       joystick_enabled_matlab_node_B.c_k_f++) {
    joystick_enabled_matlab_node_B.b_x[joystick_enabled_matlab_node_B.c_k_f] =
      (joystick_enabled_matlab_node_B.R_error[joystick_enabled_matlab_node_B.c_k_f]
       < cmd_wp_tol[joystick_enabled_matlab_node_B.c_k_f]);
  }

  tf = true;
  joystick_enabled_matlab_node_B.c_k_f = 0;
  exitg1 = false;
  while ((!exitg1) && (joystick_enabled_matlab_node_B.c_k_f < 6)) {
    if (!joystick_enabled_matlab_node_B.b_x[joystick_enabled_matlab_node_B.c_k_f])
    {
      tf = false;
      exitg1 = true;
    } else {
      joystick_enabled_matlab_node_B.c_k_f++;
    }
  }

  return tf;
}

// Function for MATLAB Function: '<S26>/commandExecuter'
void joystick_enabled_matlab_node::joystick_e_executeDurationTrick(real_T
  cmd_hold_time, const int8_T cmd_trick_id[16], const real_T idle_wp[6], const
  real_T X_Ri[3], const real_T X_Eul[3], const real_T X_Cib[9], real_T
  *hold_timer_start_time, real_T t, boolean_T new_cmd_reset, real_T
  cmd_specific_wp[6], int8_T cmd_status[4], real_T *hold_timer, real_T X_u[13])
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
  for (joystick_enabled_matlab_node_B.c_ret = 0;
       joystick_enabled_matlab_node_B.c_ret < 16;
       joystick_enabled_matlab_node_B.c_ret++) {
    joystick_enabled_matlab_node_B.b.f1[joystick_enabled_matlab_node_B.c_ret] =
      rb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.c.f1[joystick_enabled_matlab_node_B.c_ret] =
      sb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.d.f1[joystick_enabled_matlab_node_B.c_ret] =
      tb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.e.f1[joystick_enabled_matlab_node_B.c_ret] =
      ub[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.f.f1[joystick_enabled_matlab_node_B.c_ret] =
      vb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.g.f1[joystick_enabled_matlab_node_B.c_ret] =
      wb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.h.f1[joystick_enabled_matlab_node_B.c_ret] =
      xb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.i.f1[joystick_enabled_matlab_node_B.c_ret] =
      yb[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.j.f1[joystick_enabled_matlab_node_B.c_ret] =
      ac[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.k.f1[joystick_enabled_matlab_node_B.c_ret] =
      bc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.l.f1[joystick_enabled_matlab_node_B.c_ret] =
      cc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.m.f1[joystick_enabled_matlab_node_B.c_ret] =
      dc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.n.f1[joystick_enabled_matlab_node_B.c_ret] =
      ec[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.o.f1[joystick_enabled_matlab_node_B.c_ret] =
      fc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.p.f1[joystick_enabled_matlab_node_B.c_ret] =
      gc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.q.f1[joystick_enabled_matlab_node_B.c_ret] =
      hc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.r.f1[joystick_enabled_matlab_node_B.c_ret] =
      ic[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.s_l.f1[joystick_enabled_matlab_node_B.c_ret] =
      jc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.u.f1[joystick_enabled_matlab_node_B.c_ret] =
      kc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.v.f1[joystick_enabled_matlab_node_B.c_ret] =
      lc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.w.f1[joystick_enabled_matlab_node_B.c_ret] =
      mc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.x_d.f1[joystick_enabled_matlab_node_B.c_ret] =
      nc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.y.f1[joystick_enabled_matlab_node_B.c_ret] =
      oc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.ab.f1[joystick_enabled_matlab_node_B.c_ret] =
      pc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.bb.f1[joystick_enabled_matlab_node_B.c_ret] =
      qc[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.cb.f1[joystick_enabled_matlab_node_B.c_ret] =
      rc[joystick_enabled_matlab_node_B.c_ret];
  }

  joystick_enabled_matlab_node_B.varargin_1[0] =
    joystick_enabled_matlab_node_B.b;
  joystick_enabled_matlab_node_B.varargin_1[1] =
    joystick_enabled_matlab_node_B.c;
  joystick_enabled_matlab_node_B.varargin_1[2] =
    joystick_enabled_matlab_node_B.d;
  joystick_enabled_matlab_node_B.varargin_1[3] =
    joystick_enabled_matlab_node_B.e;
  joystick_enabled_matlab_node_B.varargin_1[4] =
    joystick_enabled_matlab_node_B.f;
  joystick_enabled_matlab_node_B.varargin_1[5] =
    joystick_enabled_matlab_node_B.g;
  joystick_enabled_matlab_node_B.varargin_1[6] =
    joystick_enabled_matlab_node_B.h;
  joystick_enabled_matlab_node_B.varargin_1[7] =
    joystick_enabled_matlab_node_B.i;
  joystick_enabled_matlab_node_B.varargin_1[8] =
    joystick_enabled_matlab_node_B.j;
  joystick_enabled_matlab_node_B.varargin_1[9] =
    joystick_enabled_matlab_node_B.k;
  joystick_enabled_matlab_node_B.varargin_1[10] =
    joystick_enabled_matlab_node_B.l;
  joystick_enabled_matlab_node_B.varargin_1[11] =
    joystick_enabled_matlab_node_B.m;
  joystick_enabled_matlab_node_B.varargin_1[12] =
    joystick_enabled_matlab_node_B.n;
  joystick_enabled_matlab_node_B.varargin_2[0] =
    joystick_enabled_matlab_node_B.o;
  joystick_enabled_matlab_node_B.varargin_2[1] =
    joystick_enabled_matlab_node_B.p;
  joystick_enabled_matlab_node_B.varargin_2[2] =
    joystick_enabled_matlab_node_B.q;
  joystick_enabled_matlab_node_B.varargin_2[3] =
    joystick_enabled_matlab_node_B.r;
  joystick_enabled_matlab_node_B.varargin_2[4] =
    joystick_enabled_matlab_node_B.s_l;
  joystick_enabled_matlab_node_B.varargin_2[5] =
    joystick_enabled_matlab_node_B.u;
  joystick_enabled_matlab_node_B.varargin_2[6] =
    joystick_enabled_matlab_node_B.v;
  joystick_enabled_matlab_node_B.varargin_2[7] =
    joystick_enabled_matlab_node_B.w;
  joystick_enabled_matlab_node_B.varargin_2[8] =
    joystick_enabled_matlab_node_B.x_d;
  joystick_enabled_matlab_node_B.varargin_2[9] =
    joystick_enabled_matlab_node_B.y;
  joystick_enabled_matlab_node_B.varargin_2[10] =
    joystick_enabled_matlab_node_B.ab;
  joystick_enabled_matlab_node_B.varargin_2[11] =
    joystick_enabled_matlab_node_B.bb;
  joystick_enabled_matlab_node_B.varargin_2[12] =
    joystick_enabled_matlab_node_B.cb;
  for (joystick_enabled_matlab_node_B.c_ret = 0;
       joystick_enabled_matlab_node_B.c_ret < 16;
       joystick_enabled_matlab_node_B.c_ret++) {
    joystick_enabled_matlab_node_B.b.f1[joystick_enabled_matlab_node_B.c_ret] =
      n_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.c.f1[joystick_enabled_matlab_node_B.c_ret] =
      o_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.d.f1[joystick_enabled_matlab_node_B.c_ret] =
      p_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.e.f1[joystick_enabled_matlab_node_B.c_ret] =
      q_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.f.f1[joystick_enabled_matlab_node_B.c_ret] =
      r_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.g.f1[joystick_enabled_matlab_node_B.c_ret] =
      s_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.h.f1[joystick_enabled_matlab_node_B.c_ret] =
      t_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.i.f1[joystick_enabled_matlab_node_B.c_ret] =
      u_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.j.f1[joystick_enabled_matlab_node_B.c_ret] =
      v_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.k.f1[joystick_enabled_matlab_node_B.c_ret] =
      w_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.l.f1[joystick_enabled_matlab_node_B.c_ret] =
      x_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.m.f1[joystick_enabled_matlab_node_B.c_ret] =
      y_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.n.f1[joystick_enabled_matlab_node_B.c_ret] =
      ab_a[joystick_enabled_matlab_node_B.c_ret];
    joystick_enabled_matlab_node_B.o.f1[joystick_enabled_matlab_node_B.c_ret] =
      sc[joystick_enabled_matlab_node_B.c_ret];
  }

  joystick_enabled_matlab_node_B.varargin_3[0] =
    joystick_enabled_matlab_node_B.b;
  joystick_enabled_matlab_node_B.varargin_3[1] =
    joystick_enabled_matlab_node_B.c;
  joystick_enabled_matlab_node_B.varargin_3[2] =
    joystick_enabled_matlab_node_B.d;
  joystick_enabled_matlab_node_B.varargin_3[3] =
    joystick_enabled_matlab_node_B.e;
  joystick_enabled_matlab_node_B.varargin_3[4] =
    joystick_enabled_matlab_node_B.f;
  joystick_enabled_matlab_node_B.varargin_3[5] =
    joystick_enabled_matlab_node_B.g;
  joystick_enabled_matlab_node_B.varargin_3[6] =
    joystick_enabled_matlab_node_B.h;
  joystick_enabled_matlab_node_B.varargin_3[7] =
    joystick_enabled_matlab_node_B.i;
  joystick_enabled_matlab_node_B.varargin_3[8] =
    joystick_enabled_matlab_node_B.j;
  joystick_enabled_matlab_node_B.varargin_3[9] =
    joystick_enabled_matlab_node_B.k;
  joystick_enabled_matlab_node_B.varargin_3[10] =
    joystick_enabled_matlab_node_B.l;
  joystick_enabled_matlab_node_B.varargin_3[11] =
    joystick_enabled_matlab_node_B.m;
  joystick_enabled_matlab_node_B.varargin_3[12] =
    joystick_enabled_matlab_node_B.n;
  for (joystick_enabled_matlab_node_B.c_ret = 0;
       joystick_enabled_matlab_node_B.c_ret < 16;
       joystick_enabled_matlab_node_B.c_ret++) {
    joystick_enabled_matlab_node_B.switch_expression[joystick_enabled_matlab_node_B.c_ret]
      = cmd_trick_id[joystick_enabled_matlab_node_B.c_ret];
  }

  joystick_enabled_matlab_node_B.c_ret = 0;
  do {
    exitg3 = 0;
    if (joystick_enabled_matlab_node_B.c_ret < 13) {
      joystick_enabled_matlab_node_B.d_ret = std::memcmp
        (&joystick_enabled_matlab_node_B.varargin_1[joystick_enabled_matlab_node_B.c_ret]
         .f1[0], &joystick_enabled_matlab_node_B.switch_expression[0], 16);
      if (joystick_enabled_matlab_node_B.d_ret == 0) {
        joystick_enabled_matlab_node_B.c_ret = 0;
        exitg3 = 1;
      } else {
        joystick_enabled_matlab_node_B.c_ret++;
      }
    } else {
      joystick_enabled_matlab_node_B.c_ret = 0;
      exitg3 = 2;
    }
  } while (exitg3 == 0);

  if (exitg3 == 1) {
  } else {
    do {
      exitg2 = 0;
      if (joystick_enabled_matlab_node_B.c_ret < 13) {
        joystick_enabled_matlab_node_B.d_ret = std::memcmp
          (&joystick_enabled_matlab_node_B.varargin_2[joystick_enabled_matlab_node_B.c_ret]
           .f1[0], &joystick_enabled_matlab_node_B.switch_expression[0], 16);
        if (joystick_enabled_matlab_node_B.d_ret == 0) {
          joystick_enabled_matlab_node_B.c_ret = 1;
          exitg2 = 1;
        } else {
          joystick_enabled_matlab_node_B.c_ret++;
        }
      } else {
        joystick_enabled_matlab_node_B.c_ret = 0;
        exitg2 = 2;
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        if (joystick_enabled_matlab_node_B.c_ret < 13) {
          joystick_enabled_matlab_node_B.d_ret = std::memcmp
            (&joystick_enabled_matlab_node_B.varargin_3[joystick_enabled_matlab_node_B.c_ret]
             .f1[0], &joystick_enabled_matlab_node_B.switch_expression[0], 16);
          if (joystick_enabled_matlab_node_B.d_ret == 0) {
            joystick_enabled_matlab_node_B.c_ret = 2;
            exitg1 = 1;
          } else {
            joystick_enabled_matlab_node_B.c_ret++;
          }
        } else {
          joystick_enabled_matlab_node_B.c_ret = std::memcmp
            (&joystick_enabled_matlab_node_B.o.f1[0],
             &joystick_enabled_matlab_node_B.switch_expression[0], 16);
          if (joystick_enabled_matlab_node_B.c_ret == 0) {
            joystick_enabled_matlab_node_B.c_ret = 3;
          } else {
            joystick_enabled_matlab_node_B.c_ret = -1;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }
  }

  switch (joystick_enabled_matlab_node_B.c_ret) {
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

    for (joystick_enabled_matlab_node_B.c_ret = 0;
         joystick_enabled_matlab_node_B.c_ret < 6;
         joystick_enabled_matlab_node_B.c_ret++) {
      cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
        idle_wp[joystick_enabled_matlab_node_B.c_ret];
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

    for (joystick_enabled_matlab_node_B.c_ret = 0;
         joystick_enabled_matlab_node_B.c_ret < 6;
         joystick_enabled_matlab_node_B.c_ret++) {
      cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
        idle_wp[joystick_enabled_matlab_node_B.c_ret];
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

    joystick_enabled_matlab_node_B.c_ret = std::memcmp(&a[0],
      &joystick_enabled_matlab_node_B.switch_expression[0], 16);
    if (joystick_enabled_matlab_node_B.c_ret == 0) {
      joystick_enabled_matlab_node_B.c_ret = 0;
    } else {
      joystick_enabled_matlab_node_B.c_ret = std::memcmp(&b_a[0],
        &joystick_enabled_matlab_node_B.switch_expression[0], 16);
      if (joystick_enabled_matlab_node_B.c_ret == 0) {
        joystick_enabled_matlab_node_B.c_ret = 1;
      } else {
        joystick_enabled_matlab_node_B.c_ret = std::memcmp(&c_a[0],
          &joystick_enabled_matlab_node_B.switch_expression[0], 16);
        if (joystick_enabled_matlab_node_B.c_ret == 0) {
          joystick_enabled_matlab_node_B.c_ret = 2;
        } else {
          joystick_enabled_matlab_node_B.c_ret = std::memcmp(&d_a[0],
            &joystick_enabled_matlab_node_B.switch_expression[0], 16);
          if (joystick_enabled_matlab_node_B.c_ret == 0) {
            joystick_enabled_matlab_node_B.c_ret = 3;
          } else {
            joystick_enabled_matlab_node_B.c_ret = std::memcmp(&e_a[0],
              &joystick_enabled_matlab_node_B.switch_expression[0], 16);
            if (joystick_enabled_matlab_node_B.c_ret == 0) {
              joystick_enabled_matlab_node_B.c_ret = 4;
            } else {
              joystick_enabled_matlab_node_B.c_ret = std::memcmp(&f_a[0],
                &joystick_enabled_matlab_node_B.switch_expression[0], 16);
              if (joystick_enabled_matlab_node_B.c_ret == 0) {
                joystick_enabled_matlab_node_B.c_ret = 5;
              } else {
                joystick_enabled_matlab_node_B.c_ret = std::memcmp(&g_a[0],
                  &joystick_enabled_matlab_node_B.switch_expression[0], 16);
                if (joystick_enabled_matlab_node_B.c_ret == 0) {
                  joystick_enabled_matlab_node_B.c_ret = 6;
                } else {
                  joystick_enabled_matlab_node_B.c_ret = std::memcmp(&h_a[0],
                    &joystick_enabled_matlab_node_B.switch_expression[0], 16);
                  if (joystick_enabled_matlab_node_B.c_ret == 0) {
                    joystick_enabled_matlab_node_B.c_ret = 7;
                  } else {
                    joystick_enabled_matlab_node_B.c_ret = std::memcmp(&i_a[0],
                      &joystick_enabled_matlab_node_B.switch_expression[0], 16);
                    if (joystick_enabled_matlab_node_B.c_ret == 0) {
                      joystick_enabled_matlab_node_B.c_ret = 8;
                    } else {
                      joystick_enabled_matlab_node_B.c_ret = std::memcmp(&j_a[0],
                        &joystick_enabled_matlab_node_B.switch_expression[0], 16);
                      if (joystick_enabled_matlab_node_B.c_ret == 0) {
                        joystick_enabled_matlab_node_B.c_ret = 9;
                      } else {
                        joystick_enabled_matlab_node_B.c_ret = std::memcmp(&k_a
                          [0],
                          &joystick_enabled_matlab_node_B.switch_expression[0],
                          16);
                        if (joystick_enabled_matlab_node_B.c_ret == 0) {
                          joystick_enabled_matlab_node_B.c_ret = 10;
                        } else {
                          joystick_enabled_matlab_node_B.c_ret = std::memcmp
                            (&l_a[0],
                             &joystick_enabled_matlab_node_B.switch_expression[0],
                             16);
                          if (joystick_enabled_matlab_node_B.c_ret == 0) {
                            joystick_enabled_matlab_node_B.c_ret = 11;
                          } else {
                            joystick_enabled_matlab_node_B.c_ret = std::memcmp
                              (&m_a[0],
                               &joystick_enabled_matlab_node_B.switch_expression[
                               0], 16);
                            if (joystick_enabled_matlab_node_B.c_ret == 0) {
                              joystick_enabled_matlab_node_B.c_ret = 12;
                            } else {
                              joystick_enabled_matlab_node_B.c_ret = -1;
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

    switch (joystick_enabled_matlab_node_B.c_ret) {
     case 0:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 0.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * 1000.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 0.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 1:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 0.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * -1000.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 0.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 2:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 1000.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * 0.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 0.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 3:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * -1000.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * 0.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 0.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 4:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 0.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * 0.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * -1000.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 5:
      if (new_cmd_reset) {
        for (joystick_enabled_matlab_node_B.c_ret = 0;
             joystick_enabled_matlab_node_B.c_ret < 3;
             joystick_enabled_matlab_node_B.c_ret++) {
          cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
            ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 0.0 +
              X_Cib[joystick_enabled_matlab_node_B.c_ret] * 0.0) +
             X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 1000.0) +
            X_Ri[joystick_enabled_matlab_node_B.c_ret];
        }
      }

      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 6:
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 7:
      cmd_specific_wp[5] = X_Eul[2] + 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 8:
      cmd_specific_wp[5] = X_Eul[2] - 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 9:
      cmd_specific_wp[5] = X_Eul[0] + 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 10:
      cmd_specific_wp[5] = X_Eul[0] - 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 11:
      cmd_specific_wp[5] = X_Eul[1] + 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     case 12:
      cmd_specific_wp[5] = X_Eul[1] - 0.52359877559829882;
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
      X_u[7] = 0.0;
      X_u[10] = 0.0;
      X_u[8] = 0.0;
      X_u[11] = 0.0;
      X_u[9] = 0.0;
      X_u[12] = 0.0;
      break;

     default:
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
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
      joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
        joystick_enabled_matlab_node_B.dv2);
      X_u[0] = cmd_specific_wp[0];
      X_u[1] = cmd_specific_wp[1];
      X_u[2] = cmd_specific_wp[2];
      X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
      X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
      X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
      X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
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
      for (joystick_enabled_matlab_node_B.c_ret = 0;
           joystick_enabled_matlab_node_B.c_ret < 3;
           joystick_enabled_matlab_node_B.c_ret++) {
        cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
          ((X_Cib[joystick_enabled_matlab_node_B.c_ret + 3] * 0.0 +
            X_Cib[joystick_enabled_matlab_node_B.c_ret] * 1000.0) +
           X_Cib[joystick_enabled_matlab_node_B.c_ret + 6] * 0.0) +
          X_Ri[joystick_enabled_matlab_node_B.c_ret];
      }
    }

    joystick_enabled_ma_eulToQuat_f(&cmd_specific_wp[3],
      joystick_enabled_matlab_node_B.dv2);
    X_u[0] = cmd_specific_wp[0];
    X_u[1] = cmd_specific_wp[1];
    X_u[2] = cmd_specific_wp[2];
    X_u[3] = joystick_enabled_matlab_node_B.dv2[0];
    X_u[4] = joystick_enabled_matlab_node_B.dv2[1];
    X_u[5] = joystick_enabled_matlab_node_B.dv2[2];
    X_u[6] = joystick_enabled_matlab_node_B.dv2[3];
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
    for (joystick_enabled_matlab_node_B.c_ret = 0;
         joystick_enabled_matlab_node_B.c_ret < 6;
         joystick_enabled_matlab_node_B.c_ret++) {
      cmd_specific_wp[joystick_enabled_matlab_node_B.c_ret] =
        idle_wp[joystick_enabled_matlab_node_B.c_ret];
    }
    break;
  }
}

// Function for MATLAB Function: '<S25>/guidanceLaw'
real_T joystick_enabled_matlab_node::joystick_enabled_matlab_no_norm(const
  real_T x[2])
{
  real_T y;
  joystick_enabled_matlab_node_B.scale_a = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_B.absxk_a = std::abs(x[0]);
  if (joystick_enabled_matlab_node_B.absxk_a > 3.3121686421112381E-170) {
    y = 1.0;
    joystick_enabled_matlab_node_B.scale_a =
      joystick_enabled_matlab_node_B.absxk_a;
  } else {
    joystick_enabled_matlab_node_B.t_i = joystick_enabled_matlab_node_B.absxk_a /
      3.3121686421112381E-170;
    y = joystick_enabled_matlab_node_B.t_i * joystick_enabled_matlab_node_B.t_i;
  }

  joystick_enabled_matlab_node_B.absxk_a = std::abs(x[1]);
  if (joystick_enabled_matlab_node_B.absxk_a >
      joystick_enabled_matlab_node_B.scale_a) {
    joystick_enabled_matlab_node_B.t_i = joystick_enabled_matlab_node_B.scale_a /
      joystick_enabled_matlab_node_B.absxk_a;
    y = y * joystick_enabled_matlab_node_B.t_i *
      joystick_enabled_matlab_node_B.t_i + 1.0;
    joystick_enabled_matlab_node_B.scale_a =
      joystick_enabled_matlab_node_B.absxk_a;
  } else {
    joystick_enabled_matlab_node_B.t_i = joystick_enabled_matlab_node_B.absxk_a /
      joystick_enabled_matlab_node_B.scale_a;
    y += joystick_enabled_matlab_node_B.t_i * joystick_enabled_matlab_node_B.t_i;
  }

  return joystick_enabled_matlab_node_B.scale_a * std::sqrt(y);
}

// Function for MATLAB Function: '<S25>/quatInjector'
void joystick_enabled_matlab_node::joystick_enabled_matl_eulToQuat(const real_T
  Eul[3], real_T qib[4])
{
  joystick_enabled_matlab_node_B.eta_m = std::cos(Eul[1]);
  joystick_enabled_matlab_node_B.scale_c = std::sin(Eul[1]);
  joystick_enabled_matlab_node_B.b_t_m = std::cos(Eul[2]);
  joystick_enabled_matlab_node_B.rotm_tmp_j = std::sin(Eul[2]);
  joystick_enabled_matlab_node_B.eps_idx_1_c = std::sin(Eul[0]);
  joystick_enabled_matlab_node_B.rotm_tmp_h = std::cos(Eul[0]);
  joystick_enabled_matlab_node_B.rotm_idx_0_p =
    joystick_enabled_matlab_node_B.eta_m * joystick_enabled_matlab_node_B.b_t_m;
  joystick_enabled_matlab_node_B.eps_idx_2_p =
    joystick_enabled_matlab_node_B.eta_m *
    joystick_enabled_matlab_node_B.rotm_tmp_j;
  joystick_enabled_matlab_node_B.rotm_idx_4_tmp_e =
    joystick_enabled_matlab_node_B.eps_idx_1_c *
    joystick_enabled_matlab_node_B.scale_c;
  joystick_enabled_matlab_node_B.eps_idx_0_c =
    joystick_enabled_matlab_node_B.rotm_idx_4_tmp_e *
    joystick_enabled_matlab_node_B.rotm_tmp_j +
    joystick_enabled_matlab_node_B.rotm_tmp_h *
    joystick_enabled_matlab_node_B.b_t_m;
  joystick_enabled_matlab_node_B.absxk_m =
    joystick_enabled_matlab_node_B.eps_idx_1_c *
    joystick_enabled_matlab_node_B.eta_m;
  joystick_enabled_matlab_node_B.rotm_idx_8_a =
    joystick_enabled_matlab_node_B.rotm_tmp_h *
    joystick_enabled_matlab_node_B.eta_m;
  joystick_enabled_matlab_node_B.eta_m = std::sqrt
    (((joystick_enabled_matlab_node_B.rotm_idx_0_p +
       joystick_enabled_matlab_node_B.eps_idx_0_c) +
      joystick_enabled_matlab_node_B.rotm_idx_8_a) + 1.0) / 2.0;
  if (joystick_enabled_matlab_node_B.eta_m != 0.0) {
    joystick_enabled_matlab_node_B.rotm_idx_0_p =
      joystick_enabled_matlab_node_B.rotm_tmp_h *
      joystick_enabled_matlab_node_B.scale_c;
    joystick_enabled_matlab_node_B.rotm_idx_8_a = 4.0 *
      joystick_enabled_matlab_node_B.eta_m;
    joystick_enabled_matlab_node_B.eps_idx_0_c =
      (joystick_enabled_matlab_node_B.absxk_m -
       (joystick_enabled_matlab_node_B.rotm_idx_0_p *
        joystick_enabled_matlab_node_B.rotm_tmp_j -
        joystick_enabled_matlab_node_B.eps_idx_1_c *
        joystick_enabled_matlab_node_B.b_t_m)) /
      joystick_enabled_matlab_node_B.rotm_idx_8_a;
    joystick_enabled_matlab_node_B.eps_idx_1_c =
      ((joystick_enabled_matlab_node_B.rotm_idx_0_p *
        joystick_enabled_matlab_node_B.b_t_m +
        joystick_enabled_matlab_node_B.eps_idx_1_c *
        joystick_enabled_matlab_node_B.rotm_tmp_j) -
       (-joystick_enabled_matlab_node_B.scale_c)) /
      joystick_enabled_matlab_node_B.rotm_idx_8_a;
    joystick_enabled_matlab_node_B.eps_idx_2_p =
      (joystick_enabled_matlab_node_B.eps_idx_2_p -
       (joystick_enabled_matlab_node_B.rotm_idx_4_tmp_e *
        joystick_enabled_matlab_node_B.b_t_m -
        joystick_enabled_matlab_node_B.rotm_tmp_h *
        joystick_enabled_matlab_node_B.rotm_tmp_j)) /
      joystick_enabled_matlab_node_B.rotm_idx_8_a;
  } else {
    joystick_enabled_matlab_node_B.b_t_m =
      (joystick_enabled_matlab_node_B.rotm_idx_0_p + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x_j[0] = joystick_enabled_matlab_node_B.b_t_m;
    joystick_enabled_matlab_node_B.eps_idx_1_c =
      (joystick_enabled_matlab_node_B.eps_idx_0_c + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x_j[1] =
      joystick_enabled_matlab_node_B.eps_idx_1_c;
    joystick_enabled_matlab_node_B.rotm_tmp_j =
      (joystick_enabled_matlab_node_B.rotm_idx_8_a + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.x_j[2] =
      joystick_enabled_matlab_node_B.rotm_tmp_j;
    if (!std::isnan(joystick_enabled_matlab_node_B.b_t_m)) {
      joystick_enabled_matlab_node_B.idx_g = 1;
    } else {
      boolean_T exitg1;
      joystick_enabled_matlab_node_B.idx_g = 0;
      joystick_enabled_matlab_node_B.b_k_c = 2;
      exitg1 = false;
      while ((!exitg1) && (joystick_enabled_matlab_node_B.b_k_c < 4)) {
        if (!std::isnan
            (joystick_enabled_matlab_node_B.x_j[joystick_enabled_matlab_node_B.b_k_c
             - 1])) {
          joystick_enabled_matlab_node_B.idx_g =
            joystick_enabled_matlab_node_B.b_k_c;
          exitg1 = true;
        } else {
          joystick_enabled_matlab_node_B.b_k_c++;
        }
      }
    }

    if (joystick_enabled_matlab_node_B.idx_g == 0) {
      joystick_enabled_matlab_node_B.b_k_c = 1;
    } else {
      joystick_enabled_matlab_node_B.eps_idx_0_c =
        joystick_enabled_matlab_node_B.x_j[joystick_enabled_matlab_node_B.idx_g
        - 1];
      joystick_enabled_matlab_node_B.b_k_c =
        joystick_enabled_matlab_node_B.idx_g;
      for (joystick_enabled_matlab_node_B.c_k_o =
           joystick_enabled_matlab_node_B.idx_g + 1;
           joystick_enabled_matlab_node_B.c_k_o < 4;
           joystick_enabled_matlab_node_B.c_k_o++) {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          joystick_enabled_matlab_node_B.x_j[joystick_enabled_matlab_node_B.c_k_o
          - 1];
        if (joystick_enabled_matlab_node_B.eps_idx_0_c <
            joystick_enabled_matlab_node_B.rotm_tmp_h) {
          joystick_enabled_matlab_node_B.eps_idx_0_c =
            joystick_enabled_matlab_node_B.rotm_tmp_h;
          joystick_enabled_matlab_node_B.b_k_c =
            joystick_enabled_matlab_node_B.c_k_o;
        }
      }
    }

    switch (joystick_enabled_matlab_node_B.b_k_c) {
     case 1:
      joystick_enabled_matlab_node_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_m));
      if (std::isnan(joystick_enabled_matlab_node_B.eps_idx_2_p)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.eps_idx_2_p < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (joystick_enabled_matlab_node_B.eps_idx_2_p > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1_c)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      if (std::isnan(-joystick_enabled_matlab_node_B.scale_c)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.scale_c < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (-joystick_enabled_matlab_node_B.scale_c > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_2_p = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_j)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      break;

     case 2:
      joystick_enabled_matlab_node_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1_c));
      if (std::isnan(joystick_enabled_matlab_node_B.eps_idx_2_p)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.eps_idx_2_p < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (joystick_enabled_matlab_node_B.eps_idx_2_p > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_m)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      if (std::isnan(joystick_enabled_matlab_node_B.absxk_m)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.absxk_m < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (joystick_enabled_matlab_node_B.absxk_m > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_2_p = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_j)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      break;

     default:
      joystick_enabled_matlab_node_B.eps_idx_2_p = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.rotm_tmp_j));
      if (std::isnan(-joystick_enabled_matlab_node_B.scale_c)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.scale_c < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (-joystick_enabled_matlab_node_B.scale_c > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_0_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_t_m)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      if (std::isnan(joystick_enabled_matlab_node_B.absxk_m)) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.absxk_m < 0.0) {
        joystick_enabled_matlab_node_B.rotm_tmp_h = -1.0;
      } else {
        joystick_enabled_matlab_node_B.rotm_tmp_h =
          (joystick_enabled_matlab_node_B.absxk_m > 0.0);
      }

      joystick_enabled_matlab_node_B.eps_idx_1_c = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.eps_idx_1_c)) *
        joystick_enabled_matlab_node_B.rotm_tmp_h;
      break;
    }
  }

  joystick_enabled_matlab_node_B.scale_c = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_B.absxk_m = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_0_c);
  if (joystick_enabled_matlab_node_B.absxk_m > 3.3121686421112381E-170) {
    joystick_enabled_matlab_node_B.rotm_tmp_j = 1.0;
    joystick_enabled_matlab_node_B.scale_c =
      joystick_enabled_matlab_node_B.absxk_m;
  } else {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.absxk_m / 3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.rotm_tmp_j =
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m;
  }

  joystick_enabled_matlab_node_B.absxk_m = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_1_c);
  if (joystick_enabled_matlab_node_B.absxk_m >
      joystick_enabled_matlab_node_B.scale_c) {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.scale_c /
      joystick_enabled_matlab_node_B.absxk_m;
    joystick_enabled_matlab_node_B.rotm_tmp_j =
      joystick_enabled_matlab_node_B.rotm_tmp_j *
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m + 1.0;
    joystick_enabled_matlab_node_B.scale_c =
      joystick_enabled_matlab_node_B.absxk_m;
  } else {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.absxk_m /
      joystick_enabled_matlab_node_B.scale_c;
    joystick_enabled_matlab_node_B.rotm_tmp_j +=
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m;
  }

  joystick_enabled_matlab_node_B.absxk_m = std::abs
    (joystick_enabled_matlab_node_B.eps_idx_2_p);
  if (joystick_enabled_matlab_node_B.absxk_m >
      joystick_enabled_matlab_node_B.scale_c) {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.scale_c /
      joystick_enabled_matlab_node_B.absxk_m;
    joystick_enabled_matlab_node_B.rotm_tmp_j =
      joystick_enabled_matlab_node_B.rotm_tmp_j *
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m + 1.0;
    joystick_enabled_matlab_node_B.scale_c =
      joystick_enabled_matlab_node_B.absxk_m;
  } else {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.absxk_m /
      joystick_enabled_matlab_node_B.scale_c;
    joystick_enabled_matlab_node_B.rotm_tmp_j +=
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m;
  }

  if (joystick_enabled_matlab_node_B.eta_m >
      joystick_enabled_matlab_node_B.scale_c) {
    joystick_enabled_matlab_node_B.b_t_m =
      joystick_enabled_matlab_node_B.scale_c /
      joystick_enabled_matlab_node_B.eta_m;
    joystick_enabled_matlab_node_B.rotm_tmp_j =
      joystick_enabled_matlab_node_B.rotm_tmp_j *
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m + 1.0;
    joystick_enabled_matlab_node_B.scale_c =
      joystick_enabled_matlab_node_B.eta_m;
  } else {
    joystick_enabled_matlab_node_B.b_t_m = joystick_enabled_matlab_node_B.eta_m /
      joystick_enabled_matlab_node_B.scale_c;
    joystick_enabled_matlab_node_B.rotm_tmp_j +=
      joystick_enabled_matlab_node_B.b_t_m *
      joystick_enabled_matlab_node_B.b_t_m;
  }

  joystick_enabled_matlab_node_B.rotm_tmp_j =
    joystick_enabled_matlab_node_B.scale_c * std::sqrt
    (joystick_enabled_matlab_node_B.rotm_tmp_j);
  qib[0] = joystick_enabled_matlab_node_B.eps_idx_0_c /
    joystick_enabled_matlab_node_B.rotm_tmp_j;
  qib[1] = joystick_enabled_matlab_node_B.eps_idx_1_c /
    joystick_enabled_matlab_node_B.rotm_tmp_j;
  qib[2] = joystick_enabled_matlab_node_B.eps_idx_2_p /
    joystick_enabled_matlab_node_B.rotm_tmp_j;
  qib[3] = joystick_enabled_matlab_node_B.eta_m /
    joystick_enabled_matlab_node_B.rotm_tmp_j;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T joystick_enabled_matlab_node::joystick_enabled_matlab_isequal(const
  char_T varargin_1[16])
{
  boolean_T b_p;
  boolean_T p;
  static const char_T b[16]{ 'd', 'u', 'r', 'a', 't', 'i', 'o', 'n', '_', 't',
    'r', 'i', 'c', 'k', '_', '_' };

  boolean_T exitg1;
  p = false;
  b_p = true;
  joystick_enabled_matlab_node_B.k_c = 0;
  exitg1 = false;
  while ((!exitg1) && (joystick_enabled_matlab_node_B.k_c < 16)) {
    if (varargin_1[joystick_enabled_matlab_node_B.k_c] !=
        b[joystick_enabled_matlab_node_B.k_c]) {
      b_p = false;
      exitg1 = true;
    } else {
      joystick_enabled_matlab_node_B.k_c++;
    }
  }

  if (b_p) {
    p = true;
  }

  return p;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T joystick_enabled_matlab_node::joystick_enabled_matlab__strcmp(const
  char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'R',
    'i', 'g', 'h', 't', '_', '_' };

  joystick_enabled_matlab_node_B.ret_p = std::memcmp(&b_a[0], &b[0], 16);
  return joystick_enabled_matlab_node_B.ret_p == 0;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T joystick_enabled_matlab_node::joystick_enabled_matla_strcmp_g(const
  char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 'r', 'o', 'l', 'l', 'L',
    'e', 'f', 't', '_', '_', '_' };

  joystick_enabled_matlab_node_B.ret_f = std::memcmp(&b_a[0], &b[0], 16);
  return joystick_enabled_matlab_node_B.ret_f == 0;
}

// Function for MATLAB Function: '<S25>/rateInjector'
boolean_T joystick_enabled_matlab_node::joystick_enabled_matl_strcmp_gy(const
  char_T b[16])
{
  static const char_T b_a[16]{ 'r', 's', 'f', 'f', '_', 's', 't', 'o', 'p', '_',
    '_', '_', '_', '_', '_', '_' };

  joystick_enabled_matlab_node_B.ret = std::memcmp(&b_a[0], &b[0], 16);
  return joystick_enabled_matlab_node_B.ret == 0;
}

// Function for MATLAB Function: '<S32>/forceToPWMCalculator'
void joystick_enabled_matlab_node::joystick_enabled_matlab_minimum(const real_T
  x[6], real_T *ex, int32_T *idx)
{
  if (!std::isnan(x[0])) {
    joystick_enabled_matlab_node_B.b_idx_m = 1;
  } else {
    boolean_T exitg1;
    joystick_enabled_matlab_node_B.b_idx_m = 0;
    joystick_enabled_matlab_node_B.k_m = 2;
    exitg1 = false;
    while ((!exitg1) && (joystick_enabled_matlab_node_B.k_m < 7)) {
      if (!std::isnan(x[joystick_enabled_matlab_node_B.k_m - 1])) {
        joystick_enabled_matlab_node_B.b_idx_m =
          joystick_enabled_matlab_node_B.k_m;
        exitg1 = true;
      } else {
        joystick_enabled_matlab_node_B.k_m++;
      }
    }
  }

  if (joystick_enabled_matlab_node_B.b_idx_m == 0) {
    *ex = x[0];
    *idx = 1;
  } else {
    *ex = x[joystick_enabled_matlab_node_B.b_idx_m - 1];
    *idx = joystick_enabled_matlab_node_B.b_idx_m;
    for (joystick_enabled_matlab_node_B.k_m =
         joystick_enabled_matlab_node_B.b_idx_m + 1;
         joystick_enabled_matlab_node_B.k_m < 7;
         joystick_enabled_matlab_node_B.k_m++) {
      joystick_enabled_matlab_node_B.x_o = x[joystick_enabled_matlab_node_B.k_m
        - 1];
      if (*ex > joystick_enabled_matlab_node_B.x_o) {
        *ex = joystick_enabled_matlab_node_B.x_o;
        *idx = joystick_enabled_matlab_node_B.k_m;
      }
    }
  }
}

// Function for MATLAB Function: '<S32>/forceToPWMCalculator'
void joystick_enabled_matlab_node::joystick_enabled_matl_minimum_i(const real_T
  x_data[], const int32_T *x_size, real_T *ex, int32_T *idx)
{
  joystick_enabled_matlab_node_B.last = *x_size;
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
      joystick_enabled_matlab_node_B.b_idx = 1;
    } else {
      boolean_T exitg1;
      joystick_enabled_matlab_node_B.b_idx = 0;
      joystick_enabled_matlab_node_B.k_l = 2;
      exitg1 = false;
      while ((!exitg1) && (joystick_enabled_matlab_node_B.k_l <=
                           joystick_enabled_matlab_node_B.last)) {
        if (!std::isnan(x_data[joystick_enabled_matlab_node_B.k_l - 1])) {
          joystick_enabled_matlab_node_B.b_idx =
            joystick_enabled_matlab_node_B.k_l;
          exitg1 = true;
        } else {
          joystick_enabled_matlab_node_B.k_l++;
        }
      }
    }

    if (joystick_enabled_matlab_node_B.b_idx == 0) {
      *ex = x_data[0];
      *idx = 1;
    } else {
      *ex = x_data[joystick_enabled_matlab_node_B.b_idx - 1];
      *idx = joystick_enabled_matlab_node_B.b_idx;
      for (joystick_enabled_matlab_node_B.k_l =
           joystick_enabled_matlab_node_B.b_idx + 1;
           joystick_enabled_matlab_node_B.k_l <=
           joystick_enabled_matlab_node_B.last;
           joystick_enabled_matlab_node_B.k_l++) {
        joystick_enabled_matlab_node_B.x_l =
          x_data[joystick_enabled_matlab_node_B.k_l - 1];
        if (*ex > joystick_enabled_matlab_node_B.x_l) {
          *ex = joystick_enabled_matlab_node_B.x_l;
          *idx = joystick_enabled_matlab_node_B.k_l;
        }
      }
    }
  }
}

void joystick_enabled_matlab_node::joystick_en_Publisher_setupImpl(const
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
    joystick_enabled_matlab_node_B.b_zeroDelimTopic_o[i] = b_zeroDelimTopic[i];
  }

  Pub_joystick_enabled_matlab_node_360_7.createPublisher
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic_o[0], qos_profile);
}

void joystick_enabled_matlab_node::joys_Subscriber_setupImpl_oroz0(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ps5_controller" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S224>/SourceBlock'
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
    // Start for MATLABSystem: '<S224>/SourceBlock'
    joystick_enabled_matlab_node_B.b_zeroDelimTopic_l[i] = b_zeroDelimTopic[i];
  }

  Sub_joystick_enabled_matlab_node_428.createSubscriber
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic_l[0], qos_profile);
}

void joystick_enabled_matlab_node::joystic_Subscriber_setupImpl_or(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[12]{ "/imu_custom" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[12];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  joystick_enabled_matlab_node_B.deadline_n.sec = 0.0;
  joystick_enabled_matlab_node_B.deadline_n.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 joystick_enabled_matlab_node_B.deadline_n, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 12; i++) {
    // Start for MATLABSystem: '<S3>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_joystick_enabled_matlab_node_397.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void joystick_enabled_matlab_node::joysti_Subscriber_setupImpl_oro(const
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
    joystick_enabled_matlab_node_B.b_zeroDelimTopic_g[i] = b_zeroDelimTopic[i];
  }

  Sub_joystick_enabled_matlab_node_412.createSubscriber
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic_g[0], qos_profile);
}

void joystick_enabled_matlab_node::joystick_Subscriber_setupImpl_o(const
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
    joystick_enabled_matlab_node_B.b_zeroDelimTopic_d[i] = b_zeroDelimTopic[i];
  }

  Sub_joystick_enabled_matlab_node_363.createSubscriber
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic_d[0], qos_profile);
}

void joystick_enabled_matlab_node::joystick_e_Subscriber_setupImpl(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[13]{ "/command_msg" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[13];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S17>/SourceBlock'
  joystick_enabled_matlab_node_B.deadline_b.sec = 0.0;
  joystick_enabled_matlab_node_B.deadline_b.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 joystick_enabled_matlab_node_B.deadline_b, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 13; i++) {
    // Start for MATLABSystem: '<S17>/SourceBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Sub_joystick_enabled_matlab_node_360_284.createSubscriber(&b_zeroDelimTopic[0],
    qos_profile);
}

void joystick_enabled_matlab_node::joyst_Subscriber_setupImpl_oroz(const
  ros_slros2_internal_block_Sub_T *obj)
{
  static const char_T b_zeroDelimTopic[18]{ "/matlab_pos_reset" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S221>/SourceBlock'
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
    // Start for MATLABSystem: '<S221>/SourceBlock'
    joystick_enabled_matlab_node_B.b_zeroDelimTopic[i] = b_zeroDelimTopic[i];
  }

  Sub_joystick_enabled_matlab_node_416.createSubscriber
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic[0], qos_profile);
}

void joystick_enabled_matlab_node::joystic_Publisher_setupImpl_oro(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[10]{ "/pwm_ctrl" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[10];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S229>/SinkBlock'
  joystick_enabled_matlab_node_B.deadline_bs.sec = 0.0;
  joystick_enabled_matlab_node_B.deadline_bs.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 joystick_enabled_matlab_node_B.deadline_bs, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 10; i++) {
    // Start for MATLABSystem: '<S229>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_joystick_enabled_matlab_node_436_2.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

void joystick_enabled_matlab_node::joystick__Publisher_setupImpl_o(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic_0[14]{ "/matlab_debug" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  char_T b_zeroDelimTopic[14];
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S219>/SinkBlock'
  joystick_enabled_matlab_node_B.deadline.sec = 0.0;
  joystick_enabled_matlab_node_B.deadline.nsec = 0.0;
  lifespan.sec = 0.0;
  lifespan.nsec = 0.0;
  liveliness_lease_duration.sec = 0.0;
  liveliness_lease_duration.nsec = 0.0;
  SET_QOS_VALUES(qos_profile, RMW_QOS_POLICY_HISTORY_KEEP_LAST, (size_t)10.0,
                 RMW_QOS_POLICY_DURABILITY_VOLATILE,
                 RMW_QOS_POLICY_RELIABILITY_RELIABLE,
                 joystick_enabled_matlab_node_B.deadline, lifespan,
                 RMW_QOS_POLICY_LIVELINESS_AUTOMATIC, liveliness_lease_duration,
                 (bool)obj->QOSAvoidROSNamespaceConventions);
  for (int32_T i{0}; i < 14; i++) {
    // Start for MATLABSystem: '<S219>/SinkBlock'
    b_zeroDelimTopic[i] = b_zeroDelimTopic_0[i];
  }

  Pub_joystick_enabled_matlab_node_404_3.createPublisher(&b_zeroDelimTopic[0],
    qos_profile);
}

void joystick_enabled_matlab_node::joystick_Publisher_setupImpl_or(const
  ros_slros2_internal_block_Pub_T *obj)
{
  static const char_T b_zeroDelimTopic[16]{ "/ctrl_heartbeat" };

  rmw_qos_profile_t qos_profile;
  sJ4ih70VmKcvCeguWN0mNVF deadline;
  sJ4ih70VmKcvCeguWN0mNVF lifespan;
  sJ4ih70VmKcvCeguWN0mNVF liveliness_lease_duration;
  qos_profile = rmw_qos_profile_default;

  // Start for MATLABSystem: '<S228>/SinkBlock'
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
    // Start for MATLABSystem: '<S228>/SinkBlock'
    joystick_enabled_matlab_node_B.b_zeroDelimTopic_dy[i] = b_zeroDelimTopic[i];
  }

  Pub_joystick_enabled_matlab_node_435_150.createPublisher
    (&joystick_enabled_matlab_node_B.b_zeroDelimTopic_dy[0], qos_profile);
}

// Model step function for TID0
void joystick_enabled_matlab_node::step0() // Sample time: [0.01s, 0.0s]
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

  static const char_T m_a[16]{ 'f', 'f', '_', 's', 't', 'o', 'p', '_', '_', '_',
    '_', '_', '_', '_', '_', '_' };

  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_RelationalOperator_idx_0;
  boolean_T rtb_RelationalOperator_idx_1;
  boolean_T rtb_fixforDTpropagationissue__0;
  boolean_T rtb_fixforDTpropagationissue_id;
  static const int8_T b[9]{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  static const uint8_T b_0[16]{ 112U, 108U, 97U, 99U, 101U, 104U, 111U, 108U,
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
    rate_monotonic_scheduler((&joystick_enabled_matlab_node_M));
  }

  // MATLABSystem: '<S224>/SourceBlock'
  joystick_enabled_matlab_node_B.b_varargout_1 =
    Sub_joystick_enabled_matlab_node_428.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_lx_g);

  // Outputs for Enabled SubSystem: '<S224>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S225>/Enable'

  // Start for MATLABSystem: '<S224>/SourceBlock'
  if (joystick_enabled_matlab_node_B.b_varargout_1) {
    // SignalConversion generated from: '<S225>/In1'
    joystick_enabled_matlab_node_B.In1_f =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_lx_g;
  }

  // End of Start for MATLABSystem: '<S224>/SourceBlock'
  // End of Outputs for SubSystem: '<S224>/Enabled Subsystem'

  // MATLAB Function: '<Root>/joystick_mode_manager' incorporates:
  //   MATLAB Function: '<S11>/MATLAB Function'

  if (joystick_enabled_matlab_node_B.In1_f.circle_button) {
    joystick_enabled_matlab_node_DW.joystick_flag =
      ((!joystick_enabled_matlab_node_DW.prior_joystick_flag) ||
       joystick_enabled_matlab_node_DW.joystick_flag);
    joystick_enabled_matlab_node_DW.joystick_flag =
      ((!joystick_enabled_matlab_node_DW.prior_joystick_flag) &&
       joystick_enabled_matlab_node_DW.joystick_flag);
  } else {
    joystick_enabled_matlab_node_DW.prior_joystick_flag =
      joystick_enabled_matlab_node_DW.joystick_flag;
  }

  if (joystick_enabled_matlab_node_B.In1_f.cross_button) {
    joystick_enabled_matlab_node_DW.do_mission_file_flag =
      ((!joystick_enabled_matlab_node_DW.prior_do_mission_file_flag) ||
       joystick_enabled_matlab_node_DW.do_mission_file_flag);
  }

  if (joystick_enabled_matlab_node_B.In1_f.circle_button) {
    joystick_enabled_matlab_node_DW.do_mission_file_flag =
      ((!joystick_enabled_matlab_node_DW.prior_do_mission_file_flag) &&
       joystick_enabled_matlab_node_DW.do_mission_file_flag);
  } else {
    joystick_enabled_matlab_node_DW.prior_do_mission_file_flag =
      joystick_enabled_matlab_node_DW.do_mission_file_flag;
  }

  // MATLABSystem: '<S3>/SourceBlock'
  joystick_enabled_matlab_node_B.b_varargout_1 =
    Sub_joystick_enabled_matlab_node_397.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_b_c);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S24>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (joystick_enabled_matlab_node_B.b_varargout_1) {
    // SignalConversion generated from: '<S24>/In1'
    joystick_enabled_matlab_node_B.In1_o =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_b_c;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'

  // MATLABSystem: '<S8>/SourceBlock'
  joystick_enabled_matlab_node_B.b_varargout_1 =
    Sub_joystick_enabled_matlab_node_412.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_m);

  // Outputs for Enabled SubSystem: '<S8>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S220>/Enable'

  // Start for MATLABSystem: '<S8>/SourceBlock'
  if (joystick_enabled_matlab_node_B.b_varargout_1) {
    // SignalConversion generated from: '<S220>/In1'
    joystick_enabled_matlab_node_B.In1 =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_m;
  }

  // End of Outputs for SubSystem: '<S8>/Enabled Subsystem'

  // MATLABSystem: '<S2>/SourceBlock'
  joystick_enabled_matlab_node_B.b_varargout_1_e =
    Sub_joystick_enabled_matlab_node_363.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_l_c);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S23>/Enable'

  // Start for MATLABSystem: '<S2>/SourceBlock'
  if (joystick_enabled_matlab_node_B.b_varargout_1_e) {
    // SignalConversion generated from: '<S23>/In1'
    joystick_enabled_matlab_node_B.In1_g =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_l_c;
  }

  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  joystick_enabled_matlab_node_B.Integrator_i[0] =
    joystick_enabled_matlab_node_B.In1_g.angle.x * 0.017453292519943295;
  joystick_enabled_matlab_node_B.Integrator_i[1] =
    joystick_enabled_matlab_node_B.In1_g.angle.y * 0.017453292519943295;
  joystick_enabled_matlab_node_B.Integrator_i[2] =
    joystick_enabled_matlab_node_B.In1_g.angle.z * 0.017453292519943295;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o]
      = b[joystick_enabled_matlab_node_B.i_o];
  }

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<Root>/Data Store Write1'

  joystick_enabled_matlab_node_B.db6 = (static_cast<int32_T>
    (joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[0]) +
    static_cast<int32_T>(joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[4]))
    + static_cast<int32_T>(joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[8]);

  // MATLABSystem: '<S17>/SourceBlock'
  joystick_enabled_matlab_node_B.b_varargout_1_o =
    Sub_joystick_enabled_matlab_node_360_284.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_e_k);

  // DataStoreRead: '<S1>/Data Store Read'
  joystick_enabled_matlab_node_B.DataStoreRead_k =
    joystick_enabled_matlab_node_DW.mission_is_started;

  // MATLAB Function: '<S1>/MATLAB Function' incorporates:
  //   DataStoreWrite: '<S1>/Data Store Write1'
  //   DataStoreWrite: '<S1>/Data Store Write2'
  //   MATLABSystem: '<S17>/SourceBlock'
  //
  if ((!joystick_enabled_matlab_node_DW.mission_is_started) &&
      joystick_enabled_matlab_node_B.b_varargout_1_o) {
    joystick_enabled_matlab_node_B.reset_dvl_pos = true;
    joystick_enabled_matlab_node_DW.mission_is_started = true;
  } else {
    joystick_enabled_matlab_node_B.reset_dvl_pos = false;
  }

  // End of MATLAB Function: '<S1>/MATLAB Function'

  // Outputs for Enabled SubSystem: '<S17>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S21>/Enable'

  // Start for MATLABSystem: '<S17>/SourceBlock'
  if (joystick_enabled_matlab_node_B.b_varargout_1_o) {
    // SignalConversion generated from: '<S21>/In1'
    joystick_enabled_matlab_node_B.In1_e =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_e_k;
  }

  // End of Outputs for SubSystem: '<S17>/Enabled Subsystem'

  // MATLAB Function: '<S1>/cmdMsgToCmdBus'
  joystick_enabled_matlab_node_B.cmd.wp_tol[0] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.x;
  joystick_enabled_matlab_node_B.cmd.wp_tol[1] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.y;
  joystick_enabled_matlab_node_B.cmd.wp_tol[2] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.z;
  joystick_enabled_matlab_node_B.cmd.wp_tol[3] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.roll;
  joystick_enabled_matlab_node_B.cmd.wp_tol[4] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.pitch;
  joystick_enabled_matlab_node_B.cmd.wp_tol[5] =
    joystick_enabled_matlab_node_B.In1_e.tolerance.yaw;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 16;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.integrator_reset =
      joystick_enabled_matlab_node_B.In1_e.command_id[joystick_enabled_matlab_node_B.i_o];
    if (joystick_enabled_matlab_node_B.integrator_reset > 127) {
      joystick_enabled_matlab_node_B.integrator_reset = 127U;
    }

    joystick_enabled_matlab_node_B.cmd.cmd_id[joystick_enabled_matlab_node_B.i_o]
      = static_cast<int8_T>(joystick_enabled_matlab_node_B.integrator_reset);
    joystick_enabled_matlab_node_B.integrator_reset =
      joystick_enabled_matlab_node_B.In1_e.trick[joystick_enabled_matlab_node_B.i_o];
    if (joystick_enabled_matlab_node_B.integrator_reset > 127) {
      joystick_enabled_matlab_node_B.integrator_reset = 127U;
    }

    joystick_enabled_matlab_node_B.cmd.trick_id[joystick_enabled_matlab_node_B.i_o]
      = static_cast<int8_T>(joystick_enabled_matlab_node_B.integrator_reset);
  }

  // MATLAB Function: '<S1>/statusKwdToBool' incorporates:
  //   UnitDelay: '<S1>/Unit Delay'

  joystick_enabled_matlab_node_B.fd[0] =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0];
  joystick_enabled_matlab_node_B.fd[1] =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1];
  joystick_enabled_matlab_node_B.fd[2] =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2];
  joystick_enabled_matlab_node_B.fd[3] =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3];
  joystick_enabled_matlab_node_B.i_o = std::memcmp(&a[0],
    &joystick_enabled_matlab_node_B.fd[0], 4);
  if (joystick_enabled_matlab_node_B.i_o == 0) {
    joystick_enabled_matlab_node_B.b_index = 0;
  } else {
    joystick_enabled_matlab_node_B.i_o = std::memcmp(&b_a[0],
      &joystick_enabled_matlab_node_B.fd[0], 4);
    if (joystick_enabled_matlab_node_B.i_o == 0) {
      joystick_enabled_matlab_node_B.b_index = 1;
    } else {
      joystick_enabled_matlab_node_B.i_o = std::memcmp(&c_a[0],
        &joystick_enabled_matlab_node_B.fd[0], 4);
      if (joystick_enabled_matlab_node_B.i_o == 0) {
        joystick_enabled_matlab_node_B.b_index = 2;
      } else {
        joystick_enabled_matlab_node_B.b_index = -1;
      }
    }
  }

  switch (joystick_enabled_matlab_node_B.b_index) {
   case 0:
    joystick_enabled_matlab_node_B.result_msg.success = true;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.result_msg.found_object[joystick_enabled_matlab_node_B.i_o]
        = b_0[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.result_msg.reached_waypoint_without_detection
      = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S18>/Enable'

    // MATLABSystem: '<S22>/SinkBlock'
    Pub_joystick_enabled_matlab_node_360_7.publish
      (&joystick_enabled_matlab_node_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 1:
    joystick_enabled_matlab_node_B.result_msg.success = false;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.result_msg.found_object[joystick_enabled_matlab_node_B.i_o]
        = b_0[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.result_msg.reached_waypoint_without_detection
      = false;

    // Outputs for Enabled SubSystem: '<S1>/Subsystem' incorporates:
    //   EnablePort: '<S18>/Enable'

    // MATLABSystem: '<S22>/SinkBlock'
    Pub_joystick_enabled_matlab_node_360_7.publish
      (&joystick_enabled_matlab_node_B.result_msg);

    // End of Outputs for SubSystem: '<S1>/Subsystem'
    break;

   case 2:
    break;
  }

  // End of MATLAB Function: '<S1>/statusKwdToBool'

  // DigitalClock: '<S26>/Digital Clock' incorporates:
  //   DigitalClock: '<Root>/Digital Clock'

  joystick_enabled_matlab_node_B.idx = (((&joystick_enabled_matlab_node_M)
    ->Timing.clockTick0) * 0.01);

  // MATLAB Function: '<S6>/eulToQuat'
  joystick_enabled_matlab_node_B.rotm_tmp = std::cos
    (joystick_enabled_matlab_node_B.Integrator_i[1]);
  joystick_enabled_matlab_node_B.norm_w = std::sin
    (joystick_enabled_matlab_node_B.Integrator_i[1]);
  joystick_enabled_matlab_node_B.t = std::cos
    (joystick_enabled_matlab_node_B.Integrator_i[2]);
  joystick_enabled_matlab_node_B.theta = std::sin
    (joystick_enabled_matlab_node_B.Integrator_i[2]);
  joystick_enabled_matlab_node_B.b_scale = std::sin
    (joystick_enabled_matlab_node_B.Integrator_i[0]);
  joystick_enabled_matlab_node_B.b_absxk = std::cos
    (joystick_enabled_matlab_node_B.Integrator_i[0]);
  joystick_enabled_matlab_node_B.Cbi[0] =
    joystick_enabled_matlab_node_B.rotm_tmp * joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.Cbi[3] =
    joystick_enabled_matlab_node_B.rotm_tmp *
    joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.theta_h =
    joystick_enabled_matlab_node_B.b_scale *
    joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.Cbi[4] = joystick_enabled_matlab_node_B.theta_h
    * joystick_enabled_matlab_node_B.theta +
    joystick_enabled_matlab_node_B.b_absxk * joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.Cbi[7] = joystick_enabled_matlab_node_B.b_scale
    * joystick_enabled_matlab_node_B.rotm_tmp;
  joystick_enabled_matlab_node_B.Cbi[8] = joystick_enabled_matlab_node_B.b_absxk
    * joystick_enabled_matlab_node_B.rotm_tmp;
  joystick_enabled_matlab_node_B.eta = std::sqrt
    (((joystick_enabled_matlab_node_B.Cbi[0] +
       joystick_enabled_matlab_node_B.Cbi[4]) +
      joystick_enabled_matlab_node_B.Cbi[8]) + 1.0) / 2.0;
  if (joystick_enabled_matlab_node_B.eta != 0.0) {
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.b_absxk *
      joystick_enabled_matlab_node_B.norm_w;
    joystick_enabled_matlab_node_B.scale = 4.0 *
      joystick_enabled_matlab_node_B.eta;
    joystick_enabled_matlab_node_B.eps[0] = (joystick_enabled_matlab_node_B.Cbi
      [7] - (joystick_enabled_matlab_node_B.eps_tmp *
             joystick_enabled_matlab_node_B.theta -
             joystick_enabled_matlab_node_B.b_scale *
             joystick_enabled_matlab_node_B.t)) /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.eps[1] =
      ((joystick_enabled_matlab_node_B.eps_tmp *
        joystick_enabled_matlab_node_B.t +
        joystick_enabled_matlab_node_B.b_scale *
        joystick_enabled_matlab_node_B.theta) -
       (-joystick_enabled_matlab_node_B.norm_w)) /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.eps[2] = (joystick_enabled_matlab_node_B.Cbi
      [3] - (joystick_enabled_matlab_node_B.theta_h *
             joystick_enabled_matlab_node_B.t -
             joystick_enabled_matlab_node_B.b_absxk *
             joystick_enabled_matlab_node_B.theta)) /
      joystick_enabled_matlab_node_B.scale;
  } else {
    joystick_enabled_matlab_node_B.t = (joystick_enabled_matlab_node_B.Cbi[0] +
      1.0) / 2.0;
    joystick_enabled_matlab_node_B.Integrator_i[0] =
      joystick_enabled_matlab_node_B.t;
    joystick_enabled_matlab_node_B.theta = (joystick_enabled_matlab_node_B.Cbi[4]
      + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.Integrator_i[1] =
      joystick_enabled_matlab_node_B.theta;
    joystick_enabled_matlab_node_B.b_scale =
      (joystick_enabled_matlab_node_B.Cbi[8] + 1.0) / 2.0;
    joystick_enabled_matlab_node_B.Integrator_i[2] =
      joystick_enabled_matlab_node_B.b_scale;
    if (!std::isnan(joystick_enabled_matlab_node_B.t)) {
      joystick_enabled_matlab_node_B.b_index = 1;
    } else {
      joystick_enabled_matlab_node_B.b_index = 0;
      joystick_enabled_matlab_node_B.pos = 2;
      exitg1 = false;
      while ((!exitg1) && (joystick_enabled_matlab_node_B.pos < 4)) {
        if (!std::isnan
            (joystick_enabled_matlab_node_B.Integrator_i[joystick_enabled_matlab_node_B.pos
             - 1])) {
          joystick_enabled_matlab_node_B.b_index =
            joystick_enabled_matlab_node_B.pos;
          exitg1 = true;
        } else {
          joystick_enabled_matlab_node_B.pos++;
        }
      }
    }

    if (joystick_enabled_matlab_node_B.b_index == 0) {
      joystick_enabled_matlab_node_B.i_o = 1;
    } else {
      joystick_enabled_matlab_node_B.absxk =
        joystick_enabled_matlab_node_B.Integrator_i[joystick_enabled_matlab_node_B.b_index
        - 1];
      joystick_enabled_matlab_node_B.i_o =
        joystick_enabled_matlab_node_B.b_index;
      for (joystick_enabled_matlab_node_B.pos =
           joystick_enabled_matlab_node_B.b_index + 1;
           joystick_enabled_matlab_node_B.pos < 4;
           joystick_enabled_matlab_node_B.pos++) {
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
          joystick_enabled_matlab_node_B.Integrator_i[joystick_enabled_matlab_node_B.pos
          - 1];
        if (joystick_enabled_matlab_node_B.absxk <
            joystick_enabled_matlab_node_B.rtb_Integrator_i_d) {
          joystick_enabled_matlab_node_B.absxk =
            joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
          joystick_enabled_matlab_node_B.i_o =
            joystick_enabled_matlab_node_B.pos;
        }
      }
    }

    switch (joystick_enabled_matlab_node_B.i_o) {
     case 1:
      joystick_enabled_matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.t));
      if (std::isnan(joystick_enabled_matlab_node_B.Cbi[3])) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.Cbi[3] < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (joystick_enabled_matlab_node_B.Cbi[3] > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.theta)) *
        joystick_enabled_matlab_node_B.b_t;
      if (std::isnan(-joystick_enabled_matlab_node_B.norm_w)) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.norm_w < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (-joystick_enabled_matlab_node_B.norm_w > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_scale)) *
        joystick_enabled_matlab_node_B.b_t;
      break;

     case 2:
      joystick_enabled_matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.theta));
      if (std::isnan(joystick_enabled_matlab_node_B.Cbi[3])) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.Cbi[3] < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (joystick_enabled_matlab_node_B.Cbi[3] > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.t)) * joystick_enabled_matlab_node_B.b_t;
      if (std::isnan(joystick_enabled_matlab_node_B.Cbi[7])) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.Cbi[7] < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (joystick_enabled_matlab_node_B.Cbi[7] > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_scale)) *
        joystick_enabled_matlab_node_B.b_t;
      break;

     default:
      joystick_enabled_matlab_node_B.eps[2] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.b_scale));
      if (std::isnan(-joystick_enabled_matlab_node_B.norm_w)) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (-joystick_enabled_matlab_node_B.norm_w < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (-joystick_enabled_matlab_node_B.norm_w > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[0] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.t)) * joystick_enabled_matlab_node_B.b_t;
      if (std::isnan(joystick_enabled_matlab_node_B.Cbi[7])) {
        joystick_enabled_matlab_node_B.b_t = (rtNaN);
      } else if (joystick_enabled_matlab_node_B.Cbi[7] < 0.0) {
        joystick_enabled_matlab_node_B.b_t = -1.0;
      } else {
        joystick_enabled_matlab_node_B.b_t =
          (joystick_enabled_matlab_node_B.Cbi[7] > 0.0);
      }

      joystick_enabled_matlab_node_B.eps[1] = std::sqrt(std::fmax(0.0,
        joystick_enabled_matlab_node_B.theta)) *
        joystick_enabled_matlab_node_B.b_t;
      break;
    }
  }

  joystick_enabled_matlab_node_B.scale = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.eps[0]);
  if (joystick_enabled_matlab_node_B.absxk > 3.3121686421112381E-170) {
    joystick_enabled_matlab_node_B.eps_tmp = 1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
      3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.eps_tmp = joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.eps[1]);
  if (joystick_enabled_matlab_node_B.absxk >
      joystick_enabled_matlab_node_B.scale) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
      joystick_enabled_matlab_node_B.absxk;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.eps[2]);
  if (joystick_enabled_matlab_node_B.absxk >
      joystick_enabled_matlab_node_B.scale) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
      joystick_enabled_matlab_node_B.absxk;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  if (joystick_enabled_matlab_node_B.eta > joystick_enabled_matlab_node_B.scale)
  {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
      joystick_enabled_matlab_node_B.eta;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.eta;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.eta /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.eps_tmp = joystick_enabled_matlab_node_B.scale *
    std::sqrt(joystick_enabled_matlab_node_B.eps_tmp);

  // MATLAB Function: '<Root>/sensorRosMsgToBus'
  joystick_enabled_matlab_node_B.dv3[0] =
    joystick_enabled_matlab_node_B.In1_o.imu_fusion.angular_velocity.x;
  joystick_enabled_matlab_node_B.dv3[1] =
    joystick_enabled_matlab_node_B.In1_o.imu_fusion.angular_velocity.y;
  joystick_enabled_matlab_node_B.dv3[2] =
    joystick_enabled_matlab_node_B.In1_o.imu_fusion.angular_velocity.z;

  // Product: '<S6>/Matrix Multiply2' incorporates:
  //   Constant: '<S6>/Constant1'

  joystick_enabled_matlab_node_B.rtb_Integrator_i_d = 0.0;
  joystick_enabled_matlab_node_B.rtb_X_est_wb = 0.0;
  joystick_enabled_matlab_node_B.rtb_X_est_wb_a = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.dv3[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d +=
      joystick_enabled_matlab__ConstP.Constant1_Value_e[3 *
      joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.rtb_X_est_wb +=
      joystick_enabled_matlab__ConstP.Constant1_Value_e[3 *
      joystick_enabled_matlab_node_B.i_o + 1] *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.rtb_X_est_wb_a +=
      joystick_enabled_matlab__ConstP.Constant1_Value_e[3 *
      joystick_enabled_matlab_node_B.i_o + 2] *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.X_est.wb[2] =
    joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
  joystick_enabled_matlab_node_B.X_est.wb[1] =
    joystick_enabled_matlab_node_B.rtb_X_est_wb;
  joystick_enabled_matlab_node_B.X_est.wb[0] =
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d;

  // MATLAB Function: '<S6>/discreteTimeQuatPropagation' incorporates:
  //   MATLAB Function: '<S6>/eulToQuat'
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S6>/Matrix Multiply2'
  //
  if (!joystick_enabled_matlab_node_DW.qk_not_empty) {
    joystick_enabled_matlab_node_DW.qk[0] = 0.0;
    joystick_enabled_matlab_node_DW.qk[1] = 0.0;
    joystick_enabled_matlab_node_DW.qk[2] = 0.0;
    joystick_enabled_matlab_node_DW.qk[3] = 1.0;
    joystick_enabled_matlab_node_DW.qk_not_empty = true;
  }

  if (joystick_enabled_matlab_node_B.b_varargout_1_e) {
    joystick_enabled_matlab_node_DW.qk[0] = joystick_enabled_matlab_node_B.eps[0]
      / joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_DW.qk[1] = joystick_enabled_matlab_node_B.eps[1]
      / joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_DW.qk[2] = joystick_enabled_matlab_node_B.eps[2]
      / joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_DW.qk[3] = joystick_enabled_matlab_node_B.eta /
      joystick_enabled_matlab_node_B.eps_tmp;
  }

  joystick_enabled_matlab_node_B.scale = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.rtb_Integrator_i_d);
  if (joystick_enabled_matlab_node_B.absxk > 3.3121686421112381E-170) {
    joystick_enabled_matlab_node_B.norm_w = 1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.t = joystick_enabled_matlab_node_B.absxk /
      3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.norm_w = joystick_enabled_matlab_node_B.t *
      joystick_enabled_matlab_node_B.t;
  }

  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.rtb_X_est_wb);
  if (joystick_enabled_matlab_node_B.absxk >
      joystick_enabled_matlab_node_B.scale) {
    joystick_enabled_matlab_node_B.t = joystick_enabled_matlab_node_B.scale /
      joystick_enabled_matlab_node_B.absxk;
    joystick_enabled_matlab_node_B.norm_w =
      joystick_enabled_matlab_node_B.norm_w * joystick_enabled_matlab_node_B.t *
      joystick_enabled_matlab_node_B.t + 1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.t = joystick_enabled_matlab_node_B.absxk /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.norm_w += joystick_enabled_matlab_node_B.t *
      joystick_enabled_matlab_node_B.t;
  }

  joystick_enabled_matlab_node_B.absxk = std::abs
    (joystick_enabled_matlab_node_B.rtb_X_est_wb_a);
  if (joystick_enabled_matlab_node_B.absxk >
      joystick_enabled_matlab_node_B.scale) {
    joystick_enabled_matlab_node_B.t = joystick_enabled_matlab_node_B.scale /
      joystick_enabled_matlab_node_B.absxk;
    joystick_enabled_matlab_node_B.norm_w =
      joystick_enabled_matlab_node_B.norm_w * joystick_enabled_matlab_node_B.t *
      joystick_enabled_matlab_node_B.t + 1.0;
    joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.absxk;
  } else {
    joystick_enabled_matlab_node_B.t = joystick_enabled_matlab_node_B.absxk /
      joystick_enabled_matlab_node_B.scale;
    joystick_enabled_matlab_node_B.norm_w += joystick_enabled_matlab_node_B.t *
      joystick_enabled_matlab_node_B.t;
  }

  joystick_enabled_matlab_node_B.norm_w = joystick_enabled_matlab_node_B.scale *
    std::sqrt(joystick_enabled_matlab_node_B.norm_w);
  if (joystick_enabled_matlab_node_B.norm_w > 1.0E-10) {
    joystick_enabled_matlab_node_B.b_a_l = std::sin(0.5 *
      joystick_enabled_matlab_node_B.norm_w * 0.01) /
      joystick_enabled_matlab_node_B.norm_w;
    joystick_enabled_matlab_node_B.eps[0] = joystick_enabled_matlab_node_B.b_a_l
      * joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
    joystick_enabled_matlab_node_B.eps[1] = joystick_enabled_matlab_node_B.b_a_l
      * joystick_enabled_matlab_node_B.rtb_X_est_wb;
    joystick_enabled_matlab_node_B.eps[2] = joystick_enabled_matlab_node_B.b_a_l
      * joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
  } else {
    joystick_enabled_matlab_node_B.eps[0] = 0.005 *
      joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
    joystick_enabled_matlab_node_B.eps[1] = 0.005 *
      joystick_enabled_matlab_node_B.rtb_X_est_wb;
    joystick_enabled_matlab_node_B.eps[2] = 0.005 *
      joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
  }

  joystick_enabled_matlab_node_B.norm_w = std::cos(0.5 *
    joystick_enabled_matlab_node_B.norm_w * 0.01);
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    // MATLAB Function: '<S6>/quatToRotm' incorporates:
    //   MATLAB Function: '<S6>/derivedStateEstimates'

    joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o]
      = b[joystick_enabled_matlab_node_B.i_o];
  }

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[0] = 0.0;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3] =
    -joystick_enabled_matlab_node_B.eps[2];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[6] =
    joystick_enabled_matlab_node_B.eps[1];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[1] =
    joystick_enabled_matlab_node_B.eps[2];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[4] = 0.0;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[7] =
    -joystick_enabled_matlab_node_B.eps[0];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[2] =
    -joystick_enabled_matlab_node_B.eps[1];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[5] =
    joystick_enabled_matlab_node_B.eps[0];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[8] = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_index = joystick_enabled_matlab_node_B.i_o <<
      2;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index] =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[3 *
      joystick_enabled_matlab_node_B.i_o] *
      joystick_enabled_matlab_node_B.norm_w -
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3 *
      joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.pos = 3 * joystick_enabled_matlab_node_B.i_o
      + 1;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      1] =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.pos]
      * joystick_enabled_matlab_node_B.norm_w -
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.pos];
    joystick_enabled_matlab_node_B.pos = 3 * joystick_enabled_matlab_node_B.i_o
      + 2;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      2] =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.pos]
      * joystick_enabled_matlab_node_B.norm_w -
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.pos];
    joystick_enabled_matlab_node_B.eps_b =
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.i_o + 12] =
      joystick_enabled_matlab_node_B.eps_b;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      3] = -joystick_enabled_matlab_node_B.eps_b;
  }

  joystick_enabled_matlab_node_B.c_a[15] = joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.b_absxk = 0.0;
  joystick_enabled_matlab_node_B.norm_w = 0.0;
  joystick_enabled_matlab_node_B.t = 0.0;
  joystick_enabled_matlab_node_B.theta = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 4;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_DW.qk[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_index = joystick_enabled_matlab_node_B.i_o <<
      2;
    joystick_enabled_matlab_node_B.b_absxk +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.norm_w +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 1] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.t +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 2] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.theta +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 3] * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.b_scale = 3.3121686421112381E-170;
  joystick_enabled_matlab_node_DW.qk[0] = joystick_enabled_matlab_node_B.b_absxk;
  joystick_enabled_matlab_node_B.b_absxk = std::abs
    (joystick_enabled_matlab_node_DW.qk[0]);
  if (joystick_enabled_matlab_node_B.b_absxk > 3.3121686421112381E-170) {
    joystick_enabled_matlab_node_B.eps_tmp = 1.0;
    joystick_enabled_matlab_node_B.b_scale =
      joystick_enabled_matlab_node_B.b_absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_absxk /
      3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.eps_tmp = joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_DW.qk[1] = joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.b_absxk = std::abs
    (joystick_enabled_matlab_node_DW.qk[1]);
  if (joystick_enabled_matlab_node_B.b_absxk >
      joystick_enabled_matlab_node_B.b_scale) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_scale /
      joystick_enabled_matlab_node_B.b_absxk;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.b_scale =
      joystick_enabled_matlab_node_B.b_absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_absxk /
      joystick_enabled_matlab_node_B.b_scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_DW.qk[2] = joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.b_absxk = std::abs
    (joystick_enabled_matlab_node_DW.qk[2]);
  if (joystick_enabled_matlab_node_B.b_absxk >
      joystick_enabled_matlab_node_B.b_scale) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_scale /
      joystick_enabled_matlab_node_B.b_absxk;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.b_scale =
      joystick_enabled_matlab_node_B.b_absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_absxk /
      joystick_enabled_matlab_node_B.b_scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_DW.qk[3] = joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.b_absxk = std::abs
    (joystick_enabled_matlab_node_DW.qk[3]);
  if (joystick_enabled_matlab_node_B.b_absxk >
      joystick_enabled_matlab_node_B.b_scale) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_scale /
      joystick_enabled_matlab_node_B.b_absxk;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t +
      1.0;
    joystick_enabled_matlab_node_B.b_scale =
      joystick_enabled_matlab_node_B.b_absxk;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_absxk /
      joystick_enabled_matlab_node_B.b_scale;
    joystick_enabled_matlab_node_B.eps_tmp += joystick_enabled_matlab_node_B.b_t
      * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.eps_tmp =
    joystick_enabled_matlab_node_B.b_scale * std::sqrt
    (joystick_enabled_matlab_node_B.eps_tmp);
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
    joystick_enabled_matlab_node_DW.qk[0] /
    joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_DW.qk[0] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.X_est.qib[0] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
    joystick_enabled_matlab_node_DW.qk[1] /
    joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_DW.qk[1] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.X_est.qib[1] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
    joystick_enabled_matlab_node_DW.qk[2] /
    joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_DW.qk[2] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.X_est.qib[2] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
    joystick_enabled_matlab_node_DW.qk[3] /
    joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_DW.qk[3] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  joystick_enabled_matlab_node_B.X_est.qib[3] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'
  //   Math: '<S6>/Transpose'

  joystick_enabled_matlab_node_B.upper_force_index =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 * 2.0 - 1.0;
  joystick_enabled_matlab_node_B.b_a_l = 2.0 *
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3 *
      joystick_enabled_matlab_node_B.i_o] = 2.0 *
      joystick_enabled_matlab_node_B.X_est.qib[0] *
      joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
      joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index]
      = 2.0 * joystick_enabled_matlab_node_B.X_est.qib[1] *
      joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o
      + 3];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index]
      = 2.0 * joystick_enabled_matlab_node_B.X_est.qib[2] *
      joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];

    // Math: '<S6>/Transpose' incorporates:
    //   MATLAB Function: '<S4>/quatToEul'
    //   Math: '<S25>/Transpose'

    joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o
      + 6];
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.Cbi[3 * joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
      joystick_enabled_matlab_node_B.i_o] *
      joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.i_o];

    // Math: '<S6>/Transpose'
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.i_o
      + 3];

    // Math: '<S6>/Transpose'
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.i_o
      + 6];
  }

  joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 =
    joystick_enabled_matlab_node_B.b_a_l * 0.0;

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[0] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 =
    joystick_enabled_matlab_node_B.b_a_l *
    -joystick_enabled_matlab_node_B.X_est.qib[2];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[1] =
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.phi = joystick_enabled_matlab_node_B.b_a_l *
    joystick_enabled_matlab_node_B.X_est.qib[1];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[2] =
    joystick_enabled_matlab_node_B.phi;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.alpha = joystick_enabled_matlab_node_B.b_a_l *
    joystick_enabled_matlab_node_B.X_est.qib[2];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3] =
    joystick_enabled_matlab_node_B.alpha;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[4] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.upper_voltage_index =
    joystick_enabled_matlab_node_B.b_a_l *
    -joystick_enabled_matlab_node_B.X_est.qib[0];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[5] =
    joystick_enabled_matlab_node_B.upper_voltage_index;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.lower_voltage_index =
    joystick_enabled_matlab_node_B.b_a_l *
    -joystick_enabled_matlab_node_B.X_est.qib[1];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[6] =
    joystick_enabled_matlab_node_B.lower_voltage_index;

  // MATLAB Function: '<S6>/quatToRotm' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatToRotm'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_B.pwms_horiz_idx_1 =
    joystick_enabled_matlab_node_B.b_a_l *
    joystick_enabled_matlab_node_B.X_est.qib[0];

  // Math: '<S6>/Transpose' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/quatToRotm'

  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[7] =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[8] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o];
  }

  // MATLABSystem: '<S221>/SourceBlock'
  joystick_enabled_matlab_node_B.OR1 =
    Sub_joystick_enabled_matlab_node_416.getLatestMessage
    (&joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_j_h);

  // Outputs for Enabled SubSystem: '<S221>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S222>/Enable'

  // Start for MATLABSystem: '<S221>/SourceBlock'
  if (joystick_enabled_matlab_node_B.OR1) {
    // SignalConversion generated from: '<S222>/In1'
    joystick_enabled_matlab_node_B.In1_b =
      joystick_enabled_matlab_node_B.rtb_SourceBlock_o2_j_h;
  }

  // End of Outputs for SubSystem: '<S221>/Enabled Subsystem'

  // Logic: '<S6>/OR' incorporates:
  //   DataStoreRead: '<S6>/Data Store Read1'
  //   Logic: '<S9>/AND'
  //   MATLAB Function: '<Root>/joystick_mode_manager'
  //   MATLABSystem: '<S221>/SourceBlock'
  //
  joystick_enabled_matlab_node_B.reset_dvl_pos =
    (joystick_enabled_matlab_node_B.reset_dvl_pos ||
     joystick_enabled_matlab_node_DW.joystick_flag ||
     (joystick_enabled_matlab_node_B.OR1 &&
      joystick_enabled_matlab_node_B.In1_b.data));

  // MATLAB Function: '<S6>/dvl_reset' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'

  if (joystick_enabled_matlab_node_DW.prior_flag &&
      (!joystick_enabled_matlab_node_B.reset_dvl_pos)) {
    joystick_enabled_matlab_node_DW.offset[0] =
      joystick_enabled_matlab_node_B.In1_g.position.x;
    joystick_enabled_matlab_node_DW.offset[1] =
      joystick_enabled_matlab_node_B.In1_g.position.y;
    joystick_enabled_matlab_node_DW.offset[2] =
      joystick_enabled_matlab_node_B.In1_g.position.z;
  }

  joystick_enabled_matlab_node_DW.prior_flag =
    joystick_enabled_matlab_node_B.reset_dvl_pos;
  joystick_enabled_matlab_node_B.rtb_dvl_pos_l[0] =
    joystick_enabled_matlab_node_B.In1_g.position.x -
    joystick_enabled_matlab_node_DW.offset[0];
  joystick_enabled_matlab_node_B.rtb_dvl_pos_l[1] =
    joystick_enabled_matlab_node_B.In1_g.position.y -
    joystick_enabled_matlab_node_DW.offset[1];
  joystick_enabled_matlab_node_B.rtb_dvl_pos_l[2] =
    joystick_enabled_matlab_node_B.In1_g.position.z -
    joystick_enabled_matlab_node_DW.offset[2];

  // End of MATLAB Function: '<S6>/dvl_reset'

  // Product: '<S6>/Matrix Multiply3' incorporates:
  //   Math: '<S6>/Transpose'

  joystick_enabled_matlab_node_B.eps_b = 0.0;
  joystick_enabled_matlab_node_B.eps_f = 0.0;
  joystick_enabled_matlab_node_B.norm_w = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.rtb_dvl_pos_l[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.eps_b +=
      joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.eps_f +=
      joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o + 1] *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.norm_w +=
      joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o + 2] *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.eps[2] = joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.eps[1] = joystick_enabled_matlab_node_B.eps_f;

  // DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //   Product: '<S6>/Matrix Multiply3'
  //
  if (joystick_enabled_matlab_node_DW.PositionIntegrator_IC_LOADING != 0) {
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[0] =
      joystick_enabled_matlab_node_B.eps_b;
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[1] =
      joystick_enabled_matlab_node_B.eps_f;
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[2] =
      joystick_enabled_matlab_node_B.norm_w;
  }

  if (joystick_enabled_matlab_node_B.b_varargout_1_e &&
      (joystick_enabled_matlab_node_DW.PositionIntegrator_PrevResetSta <= 0)) {
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[0] =
      joystick_enabled_matlab_node_B.eps_b;
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[1] =
      joystick_enabled_matlab_node_B.eps_f;
    joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[2] =
      joystick_enabled_matlab_node_B.norm_w;
  }

  // DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   MATLABSystem: '<S8>/SourceBlock'
  //
  if (joystick_enabled_matlab_node_DW.VelocityIntegrator_IC_LOADING != 0) {
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0] =
      joystick_enabled_matlab_node_B.In1.velocity_data.x;
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1] =
      joystick_enabled_matlab_node_B.In1.velocity_data.y;
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2] =
      joystick_enabled_matlab_node_B.In1.velocity_data.z;
  }

  if (joystick_enabled_matlab_node_B.b_varargout_1 &&
      (joystick_enabled_matlab_node_DW.VelocityIntegrator_PrevResetSta <= 0)) {
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0] =
      joystick_enabled_matlab_node_B.In1.velocity_data.x;
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1] =
      joystick_enabled_matlab_node_B.In1.velocity_data.y;
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2] =
      joystick_enabled_matlab_node_B.In1.velocity_data.z;
  }

  // Product: '<S6>/Matrix Multiply' incorporates:
  //   Constant: '<S6>/Constant'
  //   Math: '<S6>/Transpose'

  joystick_enabled_matlab_node_B.norm_w = 0.0;
  joystick_enabled_matlab_node_B.t = 0.0;
  joystick_enabled_matlab_node_B.theta = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab__ConstP.Constant_Value_m[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.norm_w +=
      joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.t += joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o + 1] *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.theta +=
      joystick_enabled_matlab_node_B.Cbi_c[3 *
      joystick_enabled_matlab_node_B.i_o + 2] *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.Rb_u[2] = joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.Rb_u[1] = joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.Rb_u[0] = joystick_enabled_matlab_node_B.norm_w;

  // End of Product: '<S6>/Matrix Multiply'

  // Sum: '<S6>/Sum' incorporates:
  //   Constant: '<S6>/Constant1'
  //   MATLAB Function: '<Root>/sensorRosMsgToBus'
  //   Product: '<S6>/Matrix Multiply1'

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.rtb_dvl_pos_l[joystick_enabled_matlab_node_B.i_o]
      =
      ((joystick_enabled_matlab__ConstP.Constant1_Value_e[joystick_enabled_matlab_node_B.i_o
        + 3] *
        joystick_enabled_matlab_node_B.In1_o.imu_fusion.linear_acceleration.y +
        joystick_enabled_matlab__ConstP.Constant1_Value_e[joystick_enabled_matlab_node_B.i_o]
        * joystick_enabled_matlab_node_B.In1_o.imu_fusion.linear_acceleration.x)
       + joystick_enabled_matlab__ConstP.Constant1_Value_e[joystick_enabled_matlab_node_B.i_o
       + 6] *
       joystick_enabled_matlab_node_B.In1_o.imu_fusion.linear_acceleration.z) -
      joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o];
  }

  // End of Sum: '<S6>/Sum'

  // MATLAB Function: '<S6>/derivedStateEstimates' incorporates:
  //   DiscreteIntegrator: '<S6>/Position Integrator'
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'

  joystick_enabled_matlab_node_B.Cbi_c[0] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[3] =
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[6] = joystick_enabled_matlab_node_B.phi;
  joystick_enabled_matlab_node_B.Cbi_c[1] = joystick_enabled_matlab_node_B.alpha;
  joystick_enabled_matlab_node_B.Cbi_c[4] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[7] =
    joystick_enabled_matlab_node_B.upper_voltage_index;
  joystick_enabled_matlab_node_B.Cbi_c[2] =
    joystick_enabled_matlab_node_B.lower_voltage_index;
  joystick_enabled_matlab_node_B.Cbi_c[5] =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
  joystick_enabled_matlab_node_B.Cbi_c[8] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.X_est.Cib[joystick_enabled_matlab_node_B.i_o]
      = (joystick_enabled_matlab_node_B.upper_force_index *
         joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o]
         + joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.i_o])
      + joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] +=
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o];
  }

  joystick_enabled_matlab_node_B.theta_h = std::asin(std::fmax(-1.0, std::fmin
    (1.0, joystick_enabled_matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-joystick_enabled_matlab_node_B.theta_h)) < 1.0E-6) {
    joystick_enabled_matlab_node_B.norm_w = 0.0;
    joystick_enabled_matlab_node_B.t = joystick_enabled__rt_atan2d_snf
      (-joystick_enabled_matlab_node_B.Cbi[1],
       joystick_enabled_matlab_node_B.Cbi[4]);
  } else {
    joystick_enabled_matlab_node_B.norm_w = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[7],
       joystick_enabled_matlab_node_B.Cbi[8]);
    joystick_enabled_matlab_node_B.t = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[3],
       joystick_enabled_matlab_node_B.Cbi[0]);
  }

  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.norm_w);
  joystick_enabled_matlab_node_B.theta = -joystick_enabled_matlab_node_B.theta_h;
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.theta);
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.t);
  joystick_enabled_matlab_node_B.b_scale = 0.0;
  joystick_enabled_matlab_node_B.b_absxk = 0.0;
  joystick_enabled_matlab_node_B.rotm_tmp = 0.0;
  joystick_enabled_matlab_node_B.X_est.Eul[0] =
    joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.X_est.Eul[1] =
    joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.X_est.Eul[2] = joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.pwms_horiz_idx_2 = 0.0;
  joystick_enabled_matlab_node_B.pwms_horiz_idx_3 = 0.0;
  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.eta =
      joystick_enabled_matlab_node_B.X_est.Cib[3 *
      joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_scale += joystick_enabled_matlab_node_B.eta
      * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 =
      joystick_enabled_matlab_node_B.X_est.Cib[3 *
      joystick_enabled_matlab_node_B.i_o + 1];
    joystick_enabled_matlab_node_B.b_absxk +=
      joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.X_est.Cib[3 *
      joystick_enabled_matlab_node_B.i_o + 2];
    joystick_enabled_matlab_node_B.rotm_tmp +=
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.pwms_horiz_idx_2 +=
      joystick_enabled_matlab_node_B.eta * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.pwms_horiz_idx_3 +=
      joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 +=
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.X_est.Ri[0] =
    joystick_enabled_matlab_node_B.b_scale;
  joystick_enabled_matlab_node_B.X_est.Ri[1] =
    joystick_enabled_matlab_node_B.b_absxk;
  joystick_enabled_matlab_node_B.X_est.Ri[2] =
    joystick_enabled_matlab_node_B.rotm_tmp;

  // Logic: '<S4>/OR1' incorporates:
  //   MATLAB Function: '<Root>/joystick_mode_manager'
  //   MATLABSystem: '<S17>/SourceBlock'
  //
  joystick_enabled_matlab_node_B.OR1 =
    (joystick_enabled_matlab_node_B.b_varargout_1_o ||
     joystick_enabled_matlab_node_DW.joystick_flag);

  // MATLAB Function: '<S26>/commandExecuter' incorporates:
  //   DataStoreWrite: '<S26>/Data Store Write'
  //   DigitalClock: '<S26>/Digital Clock'
  //   DiscreteIntegrator: '<S6>/Position Integrator'
  //   MATLAB Function: '<S1>/cmdMsgToCmdBus'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'

  if (!joystick_enabled_matlab_node_DW.hold_timer_start_time_not_empty) {
    joystick_enabled_matlab_node_DW.hold_timer_start_time =
      joystick_enabled_matlab_node_B.idx;
    joystick_enabled_matlab_node_DW.hold_timer_start_time_not_empty = true;
  }

  if (!joystick_enabled_matlab_node_DW.idle_wp_not_empty) {
    joystick_enabled_matlab_node_DW.idle_wp[0] =
      joystick_enabled_matlab_node_B.b_scale;
    joystick_enabled_matlab_node_DW.idle_wp[1] =
      joystick_enabled_matlab_node_B.b_absxk;
    joystick_enabled_matlab_node_DW.idle_wp[2] =
      joystick_enabled_matlab_node_B.rotm_tmp;
    joystick_enabled_matlab_node_DW.idle_wp[3] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[4] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[5] =
      joystick_enabled_matlab_node_B.t;
    joystick_enabled_matlab_node_DW.idle_wp_not_empty = true;
  }

  if (!joystick_enabled_matlab_node_DW.cmd_specific_wp_not_empty) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 6;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_DW.cmd_specific_wp[joystick_enabled_matlab_node_B.i_o]
        =
        joystick_enabled_matlab_node_DW.idle_wp[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_DW.cmd_specific_wp_not_empty = true;
  }

  if ((joystick_enabled_matlab_node_DW.UnitDelay_DSTATE == 2.0) &&
      (joystick_enabled_matlab_node_DW.prior_action_id != 2.0)) {
    joystick_enabled_matlab_node_DW.idle_wp[5] =
      joystick_enabled_matlab_node_DW.UnitDelay1_DSTATE;
  }

  joystick_enabled_matlab_node_DW.prior_action_id =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE;
  if (joystick_enabled_matlab_node_B.OR1) {
    joystick_enabled_matlab_node_DW.idle_wp[0] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[1] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[2] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[3] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[4] = 0.0;
    joystick_enabled_matlab_node_DW.idle_wp[5] =
      joystick_enabled_matlab_node_B.t;
    joystick_enabled_matlab_node_DW.hold_timer_start_time =
      joystick_enabled_matlab_node_B.idx;
    joystick_enabled_matlab_node_DW.prior_action_id = 0.0;
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 16;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.cmd.cmd_id[joystick_enabled_matlab_node_B.i_o];
  }

  joystick_enabled_matlab_node_B.i_o = std::memcmp(&a_0[0],
    &joystick_enabled_matlab_node_B.s[0], 16);
  if (joystick_enabled_matlab_node_B.i_o == 0) {
    joystick_enabled_matlab_node_B.b_index = 0;
  } else {
    joystick_enabled_matlab_node_B.i_o = std::memcmp(&b_a_0[0],
      &joystick_enabled_matlab_node_B.s[0], 16);
    if (joystick_enabled_matlab_node_B.i_o == 0) {
      joystick_enabled_matlab_node_B.b_index = 1;
    } else {
      joystick_enabled_matlab_node_B.i_o = std::memcmp(&c_a_0[0],
        &joystick_enabled_matlab_node_B.s[0], 16);
      if (joystick_enabled_matlab_node_B.i_o == 0) {
        joystick_enabled_matlab_node_B.b_index = 2;
      } else {
        joystick_enabled_matlab_node_B.i_o = std::memcmp(&d_a[0],
          &joystick_enabled_matlab_node_B.s[0], 16);
        if (joystick_enabled_matlab_node_B.i_o == 0) {
          joystick_enabled_matlab_node_B.b_index = 3;
        } else {
          joystick_enabled_matlab_node_B.b_index = -1;
        }
      }
    }
  }

  switch (joystick_enabled_matlab_node_B.b_index) {
   case 0:
    joystick_enabled_matlab_node_B.dv3[0] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.roll) *
      joystick_enabled_matlab_node_DW.idle_wp[3] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.roll * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.roll);
    joystick_enabled_matlab_node_B.X_u[0] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.x) *
      joystick_enabled_matlab_node_DW.idle_wp[0] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.x * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.x);
    joystick_enabled_matlab_node_B.dv3[1] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.pitch) *
      joystick_enabled_matlab_node_DW.idle_wp[4] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.pitch * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.pitch);
    joystick_enabled_matlab_node_B.X_u[1] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.y) *
      joystick_enabled_matlab_node_DW.idle_wp[1] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.y * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.y);
    joystick_enabled_matlab_node_B.dv3[2] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.yaw) *
      joystick_enabled_matlab_node_DW.idle_wp[5] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.yaw * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.yaw);
    joystick_enabled_matlab_node_B.X_u[2] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.z) *
      joystick_enabled_matlab_node_DW.idle_wp[2] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.z * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.z);
    joystick_enabled_ma_eulToQuat_f(joystick_enabled_matlab_node_B.dv3,
      joystick_enabled_matlab_node_B.dv1);
    joystick_enabled_matlab_node_B.X_u[3] = joystick_enabled_matlab_node_B.dv1[0];
    joystick_enabled_matlab_node_B.X_u[4] = joystick_enabled_matlab_node_B.dv1[1];
    joystick_enabled_matlab_node_B.X_u[5] = joystick_enabled_matlab_node_B.dv1[2];
    joystick_enabled_matlab_node_B.X_u[6] = joystick_enabled_matlab_node_B.dv1[3];
    joystick_enabled_matlab_node_B.X_u[7] = 0.0;
    joystick_enabled_matlab_node_B.X_u[10] = 0.0;
    joystick_enabled_matlab_node_B.X_u[8] = 0.0;
    joystick_enabled_matlab_node_B.X_u[11] = 0.0;
    joystick_enabled_matlab_node_B.X_u[9] = 0.0;
    joystick_enabled_matlab_node_B.X_u[12] = 0.0;
    if (joystick_enabled_ma_withinWPTol(joystick_enabled_matlab_node_B.X_est.Ri,
         joystick_enabled_matlab_node_B.X_est.qib,
         joystick_enabled_matlab_node_B.X_u,
         joystick_enabled_matlab_node_B.cmd.wp_tol)) {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.idx -
        joystick_enabled_matlab_node_DW.hold_timer_start_time;
    } else {
      joystick_enabled_matlab_node_DW.hold_timer_start_time =
        joystick_enabled_matlab_node_B.idx;
      joystick_enabled_matlab_node_B.b_t = 0.0;
    }

    if (joystick_enabled_matlab_node_B.b_t >=
        joystick_enabled_matlab_node_B.In1_e.hold_time) {
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 83;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 67;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 67;
      joystick_enabled_matlab_node_DW.hold_timer_start_time =
        joystick_enabled_matlab_node_B.idx;
    } else {
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 82;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 78;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 78;
    }

    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 6;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_DW.cmd_specific_wp[joystick_enabled_matlab_node_B.i_o]
        =
        joystick_enabled_matlab_node_DW.idle_wp[joystick_enabled_matlab_node_B.i_o];
    }
    break;

   case 1:
    joystick_e_executeDurationTrick
      (joystick_enabled_matlab_node_B.In1_e.hold_time,
       joystick_enabled_matlab_node_B.cmd.trick_id,
       joystick_enabled_matlab_node_DW.idle_wp,
       joystick_enabled_matlab_node_B.X_est.Ri,
       joystick_enabled_matlab_node_B.X_est.Eul,
       joystick_enabled_matlab_node_B.X_est.Cib,
       &joystick_enabled_matlab_node_DW.hold_timer_start_time,
       joystick_enabled_matlab_node_B.idx, joystick_enabled_matlab_node_B.OR1,
       joystick_enabled_matlab_node_DW.cmd_specific_wp,
       joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d,
       &joystick_enabled_matlab_node_B.b_t, joystick_enabled_matlab_node_B.X_u);
    break;

   case 2:
    if (!joystick_enabled_matlab_node_DW.wp_defined_latch) {
      joystick_enabled_matlab_node_B.Rb_u[0] =
        joystick_enabled_matlab_node_B.In1_e.waypoint.x +
        joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.Rb_u[1] =
        joystick_enabled_matlab_node_B.In1_e.waypoint.y +
        joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.Rb_u[2] =
        joystick_enabled_matlab_node_B.In1_e.waypoint.z +
        joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.eta = 0.0;
      joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 = 0.0;
      joystick_enabled_matlab_node_B.eps_tmp = 0.0;
      for (joystick_enabled_matlab_node_B.i_o = 0;
           joystick_enabled_matlab_node_B.i_o < 3;
           joystick_enabled_matlab_node_B.i_o++) {
        joystick_enabled_matlab_node_B.b_t =
          joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o];
        joystick_enabled_matlab_node_B.eta +=
          joystick_enabled_matlab_node_B.X_est.Cib[3 *
          joystick_enabled_matlab_node_B.i_o] *
          joystick_enabled_matlab_node_B.b_t;
        joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 +=
          joystick_enabled_matlab_node_B.X_est.Cib[3 *
          joystick_enabled_matlab_node_B.i_o + 1] *
          joystick_enabled_matlab_node_B.b_t;
        joystick_enabled_matlab_node_B.eps_tmp +=
          joystick_enabled_matlab_node_B.X_est.Cib[3 *
          joystick_enabled_matlab_node_B.i_o + 2] *
          joystick_enabled_matlab_node_B.b_t;
      }

      joystick_enabled_matlab_node_DW.body_relative_wp[2] =
        joystick_enabled_matlab_node_B.eps_tmp;
      joystick_enabled_matlab_node_DW.body_relative_wp[1] =
        joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1;
      joystick_enabled_matlab_node_DW.body_relative_wp[0] =
        joystick_enabled_matlab_node_B.eta;
      joystick_enabled_matlab_node_DW.wp_defined_latch = true;
    }

    joystick_enabled_matlab_node_B.dv3[0] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.roll) *
      joystick_enabled_matlab_node_DW.idle_wp[3] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.roll * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.roll);
    joystick_enabled_matlab_node_B.dv3[1] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.pitch) *
      joystick_enabled_matlab_node_DW.idle_wp[4] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.pitch * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.pitch);
    joystick_enabled_matlab_node_B.dv3[2] = static_cast<real_T>
      (!joystick_enabled_matlab_node_B.In1_e.waypoint_mask.yaw) *
      joystick_enabled_matlab_node_DW.idle_wp[5] +
      joystick_enabled_matlab_node_B.In1_e.waypoint.yaw * static_cast<real_T>
      (joystick_enabled_matlab_node_B.In1_e.waypoint_mask.yaw);
    joystick_enabled_ma_eulToQuat_f(joystick_enabled_matlab_node_B.dv3,
      joystick_enabled_matlab_node_B.dv1);
    joystick_enabled_matlab_node_B.X_u[0] =
      joystick_enabled_matlab_node_DW.body_relative_wp[0];
    joystick_enabled_matlab_node_B.X_u[1] =
      joystick_enabled_matlab_node_DW.body_relative_wp[1];
    joystick_enabled_matlab_node_B.X_u[2] =
      joystick_enabled_matlab_node_DW.body_relative_wp[2];
    joystick_enabled_matlab_node_B.X_u[3] = joystick_enabled_matlab_node_B.dv1[0];
    joystick_enabled_matlab_node_B.X_u[4] = joystick_enabled_matlab_node_B.dv1[1];
    joystick_enabled_matlab_node_B.X_u[5] = joystick_enabled_matlab_node_B.dv1[2];
    joystick_enabled_matlab_node_B.X_u[6] = joystick_enabled_matlab_node_B.dv1[3];
    joystick_enabled_matlab_node_B.X_u[7] = 0.0;
    joystick_enabled_matlab_node_B.X_u[10] = 0.0;
    joystick_enabled_matlab_node_B.X_u[8] = 0.0;
    joystick_enabled_matlab_node_B.X_u[11] = 0.0;
    joystick_enabled_matlab_node_B.X_u[9] = 0.0;
    joystick_enabled_matlab_node_B.X_u[12] = 0.0;
    if (joystick_enabled_ma_withinWPTol(joystick_enabled_matlab_node_B.X_est.Ri,
         joystick_enabled_matlab_node_B.X_est.qib,
         joystick_enabled_matlab_node_B.X_u,
         joystick_enabled_matlab_node_B.cmd.wp_tol)) {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.idx -
        joystick_enabled_matlab_node_DW.hold_timer_start_time;
    } else {
      joystick_enabled_matlab_node_DW.hold_timer_start_time =
        joystick_enabled_matlab_node_B.idx;
      joystick_enabled_matlab_node_B.b_t = 0.0;
    }

    if (joystick_enabled_matlab_node_B.b_t >=
        joystick_enabled_matlab_node_B.In1_e.hold_time) {
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 83;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 67;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 67;
      joystick_enabled_matlab_node_DW.hold_timer_start_time =
        joystick_enabled_matlab_node_B.idx;
      joystick_enabled_matlab_node_DW.wp_defined_latch = false;
    } else {
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 82;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 78;
      joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 78;
    }
    break;

   case 3:
    joystick_enabled_ma_eulToQuat_f(&joystick_enabled_matlab_node_DW.idle_wp[3],
      joystick_enabled_matlab_node_B.dv1);
    joystick_enabled_matlab_node_B.X_u[0] =
      joystick_enabled_matlab_node_DW.idle_wp[0];
    joystick_enabled_matlab_node_B.X_u[1] =
      joystick_enabled_matlab_node_DW.idle_wp[1];
    joystick_enabled_matlab_node_B.X_u[2] =
      joystick_enabled_matlab_node_DW.idle_wp[2];
    joystick_enabled_matlab_node_B.X_u[3] = joystick_enabled_matlab_node_B.dv1[0];
    joystick_enabled_matlab_node_B.X_u[4] = joystick_enabled_matlab_node_B.dv1[1];
    joystick_enabled_matlab_node_B.X_u[5] = joystick_enabled_matlab_node_B.dv1[2];
    joystick_enabled_matlab_node_B.X_u[6] = joystick_enabled_matlab_node_B.dv1[3];
    joystick_enabled_matlab_node_B.X_u[7] = 0.0;
    joystick_enabled_matlab_node_B.X_u[10] = 0.0;
    joystick_enabled_matlab_node_B.X_u[8] = 0.0;
    joystick_enabled_matlab_node_B.X_u[11] = 0.0;
    joystick_enabled_matlab_node_B.X_u[9] = 0.0;
    joystick_enabled_matlab_node_B.X_u[12] = 0.0;
    joystick_enabled_matlab_node_DW.hold_timer_start_time =
      joystick_enabled_matlab_node_B.idx;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 82;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 78;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 78;
    joystick_enabled_matlab_node_DW.mission_is_started = false;
    break;

   default:
    joystick_enabled_ma_eulToQuat_f(&joystick_enabled_matlab_node_DW.idle_wp[3],
      joystick_enabled_matlab_node_B.dv1);
    joystick_enabled_matlab_node_B.X_u[0] =
      joystick_enabled_matlab_node_DW.idle_wp[0];
    joystick_enabled_matlab_node_B.X_u[1] =
      joystick_enabled_matlab_node_DW.idle_wp[1];
    joystick_enabled_matlab_node_B.X_u[2] =
      joystick_enabled_matlab_node_DW.idle_wp[2];
    joystick_enabled_matlab_node_B.X_u[3] = joystick_enabled_matlab_node_B.dv1[0];
    joystick_enabled_matlab_node_B.X_u[4] = joystick_enabled_matlab_node_B.dv1[1];
    joystick_enabled_matlab_node_B.X_u[5] = joystick_enabled_matlab_node_B.dv1[2];
    joystick_enabled_matlab_node_B.X_u[6] = joystick_enabled_matlab_node_B.dv1[3];
    joystick_enabled_matlab_node_B.X_u[7] = 0.0;
    joystick_enabled_matlab_node_B.X_u[10] = 0.0;
    joystick_enabled_matlab_node_B.X_u[8] = 0.0;
    joystick_enabled_matlab_node_B.X_u[11] = 0.0;
    joystick_enabled_matlab_node_B.X_u[9] = 0.0;
    joystick_enabled_matlab_node_B.X_u[12] = 0.0;
    joystick_enabled_matlab_node_DW.hold_timer_start_time =
      joystick_enabled_matlab_node_B.idx;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[0] = 82;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[1] = 85;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[2] = 78;
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE_d[3] = 78;
    break;
  }

  // End of MATLAB Function: '<S26>/commandExecuter'

  // MATLAB Function: '<S4>/quatToEul' incorporates:
  //   MATLAB Function: '<S26>/quatToEul'

  joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.X_u[6] *
    joystick_enabled_matlab_node_B.X_u[6] * 2.0 - 1.0;
  joystick_enabled_matlab_node_B.b_a_l = 2.0 *
    joystick_enabled_matlab_node_B.X_u[6];
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.i_o]
      = joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o];
  }

  joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.b_a_l *
    0.0;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[0] =
    joystick_enabled_matlab_node_B.b_t;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[1] =
    joystick_enabled_matlab_node_B.b_a_l * -joystick_enabled_matlab_node_B.X_u[5];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[2] =
    joystick_enabled_matlab_node_B.b_a_l * joystick_enabled_matlab_node_B.X_u[4];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3] =
    joystick_enabled_matlab_node_B.b_a_l * joystick_enabled_matlab_node_B.X_u[5];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[4] =
    joystick_enabled_matlab_node_B.b_t;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[5] =
    joystick_enabled_matlab_node_B.b_a_l * -joystick_enabled_matlab_node_B.X_u[3];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[6] =
    joystick_enabled_matlab_node_B.b_a_l * -joystick_enabled_matlab_node_B.X_u[4];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[7] =
    joystick_enabled_matlab_node_B.b_a_l * joystick_enabled_matlab_node_B.X_u[3];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp[8] =
    joystick_enabled_matlab_node_B.b_t;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.theta_h =
      joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.i_o + 3]
      * 2.0;
    joystick_enabled_matlab_node_B.Cbi[3 * joystick_enabled_matlab_node_B.i_o] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[3] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[3 *
       joystick_enabled_matlab_node_B.i_o]) +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3 *
      joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[4] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.b_index])
      + joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[5] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.b_index])
      + joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index];
  }

  joystick_enabled_matlab_node_B.theta_h = std::asin(std::fmax(-1.0, std::fmin
    (1.0, joystick_enabled_matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-joystick_enabled_matlab_node_B.theta_h)) < 1.0E-6) {
    // SignalConversion generated from: '<S218>/ SFunction ' incorporates:
    //   MATLAB Function: '<S7>/MATLAB Function'

    joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[3] = 0.0;
    joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[5] =
      joystick_enabled__rt_atan2d_snf(-joystick_enabled_matlab_node_B.Cbi[1],
      joystick_enabled_matlab_node_B.Cbi[4]);
  } else {
    // SignalConversion generated from: '<S218>/ SFunction ' incorporates:
    //   MATLAB Function: '<S7>/MATLAB Function'

    joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[3] =
      joystick_enabled__rt_atan2d_snf(joystick_enabled_matlab_node_B.Cbi[7],
      joystick_enabled_matlab_node_B.Cbi[8]);
    joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[5] =
      joystick_enabled__rt_atan2d_snf(joystick_enabled_matlab_node_B.Cbi[3],
      joystick_enabled_matlab_node_B.Cbi[0]);
  }

  // SignalConversion generated from: '<S218>/ SFunction ' incorporates:
  //   MATLAB Function: '<S4>/quatToEul'
  //   MATLAB Function: '<S7>/MATLAB Function'

  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[3]);
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[4] =
    -joystick_enabled_matlab_node_B.theta_h;
  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[4]);
  joystick_enabled_mat_wrapToPi_k
    (&joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[5]);

  // MATLAB Function: '<S25>/guidanceLaw' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'
  //   UnitDelay: '<S4>/Unit Delay'
  //   UnitDelay: '<S4>/Unit Delay1'

  if (!joystick_enabled_matlab_node_DW.prior_action_id_not_empty) {
    joystick_enabled_matlab_node_DW.prior_action_id_g =
      joystick_enabled_matlab_node_DW.action_id;
    joystick_enabled_matlab_node_DW.prior_action_id_not_empty = true;
  }

  joystick_enabled_matlab_node_B.OR1 = false;
  rtb_RelationalOperator_idx_0 = true;
  joystick_enabled_matlab_node_B.b_index = 0;
  exitg1 = false;
  while ((!exitg1) && (joystick_enabled_matlab_node_B.b_index < 3)) {
    if (!(joystick_enabled_matlab_node_DW.prior_Ri_u[joystick_enabled_matlab_node_B.b_index]
          ==
          joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.b_index]))
    {
      rtb_RelationalOperator_idx_0 = false;
      exitg1 = true;
    } else {
      joystick_enabled_matlab_node_B.b_index++;
    }
  }

  if (rtb_RelationalOperator_idx_0) {
    joystick_enabled_matlab_node_B.OR1 = true;
  }

  if (!joystick_enabled_matlab_node_B.OR1) {
    joystick_enabled_matlab_node_B.OR1 = true;
    joystick_enabled_matlab_node_DW.prior_Ri_u[0] =
      joystick_enabled_matlab_node_B.X_u[0];
    joystick_enabled_matlab_node_DW.prior_Ri_u[1] =
      joystick_enabled_matlab_node_B.X_u[1];
    joystick_enabled_matlab_node_DW.prior_Ri_u[2] =
      joystick_enabled_matlab_node_B.X_u[2];
  } else {
    joystick_enabled_matlab_node_B.OR1 = false;
    joystick_enabled_matlab_node_DW.prior_Ri_u[0] =
      joystick_enabled_matlab_node_B.X_u[0];
    joystick_enabled_matlab_node_DW.prior_Ri_u[1] =
      joystick_enabled_matlab_node_B.X_u[1];
    joystick_enabled_matlab_node_DW.prior_Ri_u[2] =
      joystick_enabled_matlab_node_B.X_u[2];
  }

  joystick_enabled_matlab_node_B.Ri_xy_e[0] =
    joystick_enabled_matlab_node_B.X_u[0] -
    joystick_enabled_matlab_node_B.b_scale;
  joystick_enabled_matlab_node_B.Ri_xy_e[1] =
    joystick_enabled_matlab_node_B.X_u[1] -
    joystick_enabled_matlab_node_B.b_absxk;
  joystick_enabled_matlab_node_B.b_t = joystick_enabled__rt_atan2d_snf
    (joystick_enabled_matlab_node_B.Ri_xy_e[1],
     joystick_enabled_matlab_node_B.Ri_xy_e[0]);
  if (joystick_enabled_matlab_node_B.OR1) {
    joystick_enabled_matlab_node_DW.persistant_yaw_target =
      joystick_enabled_matlab_node_B.b_t;
  } else if (joystick_enabled_matlab_node_DW.action_id !=
             joystick_enabled_matlab_node_DW.prior_action_id_g) {
    joystick_enabled_matlab_node_DW.persistant_yaw_target =
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 =
    joystick_enabled_matlab_no_norm(joystick_enabled_matlab_node_B.Ri_xy_e);
  if (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 >= 0.5) {
    joystick_enabled_matlab_node_B.theta_h = std::sin
      (joystick_enabled_matlab_node_DW.persistant_yaw_target);
    joystick_enabled_matlab_node_B.eps_tmp = std::cos
      (joystick_enabled_matlab_node_DW.persistant_yaw_target);
    joystick_enabled_matlab_node_B.b_t = std::sin
      (joystick_enabled_matlab_node_DW.persistant_yaw_target);
    joystick_enabled_matlab_node_B.absxk = 0.0 *
      joystick_enabled_matlab_node_B.theta_h;
    joystick_enabled_matlab_node_B.Cbi[4] = joystick_enabled_matlab_node_B.absxk
      + joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_B.eta = std::sqrt(((std::cos
      (joystick_enabled_matlab_node_DW.persistant_yaw_target) +
      joystick_enabled_matlab_node_B.Cbi[4]) + 1.0) + 1.0) / 2.0;
    if (joystick_enabled_matlab_node_B.eta != 0.0) {
      joystick_enabled_matlab_node_B.eps_tmp *= 0.0;
      joystick_enabled_matlab_node_B.scale = 4.0 *
        joystick_enabled_matlab_node_B.eta;
      joystick_enabled_matlab_node_B.eps_n[0] = (0.0 -
        (joystick_enabled_matlab_node_B.absxk -
         joystick_enabled_matlab_node_B.eps_tmp)) /
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps_n[1] =
        (joystick_enabled_matlab_node_B.eps_tmp +
         joystick_enabled_matlab_node_B.absxk) /
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps_n[2] =
        (joystick_enabled_matlab_node_B.b_t -
         (joystick_enabled_matlab_node_B.eps_tmp -
          joystick_enabled_matlab_node_B.theta_h)) /
        joystick_enabled_matlab_node_B.scale;
    } else {
      joystick_enabled_matlab_node_B.eps_tmp = (std::cos
        (joystick_enabled_matlab_node_DW.persistant_yaw_target) + 1.0) / 2.0;
      joystick_enabled_matlab_node_B.eps[0] =
        joystick_enabled_matlab_node_B.eps_tmp;
      joystick_enabled_matlab_node_B.scale =
        (joystick_enabled_matlab_node_B.Cbi[4] + 1.0) / 2.0;
      joystick_enabled_matlab_node_B.eps[1] =
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps[2] = 1.0;
      if (!std::isnan(joystick_enabled_matlab_node_B.eps_tmp)) {
        joystick_enabled_matlab_node_B.b_index = 1;
      } else {
        joystick_enabled_matlab_node_B.b_index = 0;
        joystick_enabled_matlab_node_B.pos = 2;
        exitg1 = false;
        while ((!exitg1) && (joystick_enabled_matlab_node_B.pos < 4)) {
          if (!std::isnan
              (joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.pos
               - 1])) {
            joystick_enabled_matlab_node_B.b_index =
              joystick_enabled_matlab_node_B.pos;
            exitg1 = true;
          } else {
            joystick_enabled_matlab_node_B.pos++;
          }
        }
      }

      if (joystick_enabled_matlab_node_B.b_index == 0) {
        joystick_enabled_matlab_node_B.i_o = 1;
      } else {
        joystick_enabled_matlab_node_B.absxk =
          joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.b_index
          - 1];
        joystick_enabled_matlab_node_B.i_o =
          joystick_enabled_matlab_node_B.b_index;
        for (joystick_enabled_matlab_node_B.d_k =
             joystick_enabled_matlab_node_B.b_index + 1;
             joystick_enabled_matlab_node_B.d_k < 4;
             joystick_enabled_matlab_node_B.d_k++) {
          joystick_enabled_matlab_node_B.eps_b =
            joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.d_k
            - 1];
          if (joystick_enabled_matlab_node_B.absxk <
              joystick_enabled_matlab_node_B.eps_b) {
            joystick_enabled_matlab_node_B.absxk =
              joystick_enabled_matlab_node_B.eps_b;
            joystick_enabled_matlab_node_B.i_o =
              joystick_enabled_matlab_node_B.d_k;
          }
        }
      }

      switch (joystick_enabled_matlab_node_B.i_o) {
       case 1:
        joystick_enabled_matlab_node_B.eps_n[0] = std::sqrt(std::fmax(0.0,
          joystick_enabled_matlab_node_B.eps_tmp));
        if (std::isnan(joystick_enabled_matlab_node_B.b_t)) {
          joystick_enabled_matlab_node_B.b_t = (rtNaN);
        } else if (joystick_enabled_matlab_node_B.b_t < 0.0) {
          joystick_enabled_matlab_node_B.b_t = -1.0;
        } else {
          joystick_enabled_matlab_node_B.b_t =
            (joystick_enabled_matlab_node_B.b_t > 0.0);
        }

        joystick_enabled_matlab_node_B.eps_n[1] = std::sqrt(std::fmax(0.0,
          joystick_enabled_matlab_node_B.scale)) *
          joystick_enabled_matlab_node_B.b_t;
        joystick_enabled_matlab_node_B.eps_n[2] = 0.0;
        break;

       case 2:
        joystick_enabled_matlab_node_B.eps_n[1] = std::sqrt(std::fmax(0.0,
          joystick_enabled_matlab_node_B.scale));
        if (std::isnan(joystick_enabled_matlab_node_B.b_t)) {
          joystick_enabled_matlab_node_B.b_t = (rtNaN);
        } else if (joystick_enabled_matlab_node_B.b_t < 0.0) {
          joystick_enabled_matlab_node_B.b_t = -1.0;
        } else {
          joystick_enabled_matlab_node_B.b_t =
            (joystick_enabled_matlab_node_B.b_t > 0.0);
        }

        joystick_enabled_matlab_node_B.eps_n[0] = std::sqrt(std::fmax(0.0,
          joystick_enabled_matlab_node_B.eps_tmp)) *
          joystick_enabled_matlab_node_B.b_t;
        joystick_enabled_matlab_node_B.eps_n[2] = 0.0;
        break;

       default:
        joystick_enabled_matlab_node_B.eps_n[2] = 1.0;
        joystick_enabled_matlab_node_B.eps_n[0] = 0.0;
        joystick_enabled_matlab_node_B.eps_n[1] = 0.0;
        break;
      }
    }

    joystick_enabled_matlab_node_B.scale = 3.3121686421112381E-170;
    joystick_enabled_matlab_node_B.absxk = std::abs
      (joystick_enabled_matlab_node_B.eps_n[0]);
    if (joystick_enabled_matlab_node_B.absxk > 3.3121686421112381E-170) {
      joystick_enabled_matlab_node_B.eps_tmp = 1.0;
      joystick_enabled_matlab_node_B.scale =
        joystick_enabled_matlab_node_B.absxk;
    } else {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
        3.3121686421112381E-170;
      joystick_enabled_matlab_node_B.eps_tmp =
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.absxk = std::abs
      (joystick_enabled_matlab_node_B.eps_n[1]);
    if (joystick_enabled_matlab_node_B.absxk >
        joystick_enabled_matlab_node_B.scale) {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
        joystick_enabled_matlab_node_B.absxk;
      joystick_enabled_matlab_node_B.eps_tmp =
        joystick_enabled_matlab_node_B.eps_tmp *
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t
        + 1.0;
      joystick_enabled_matlab_node_B.scale =
        joystick_enabled_matlab_node_B.absxk;
    } else {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps_tmp +=
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.absxk = std::abs
      (joystick_enabled_matlab_node_B.eps_n[2]);
    if (joystick_enabled_matlab_node_B.absxk >
        joystick_enabled_matlab_node_B.scale) {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
        joystick_enabled_matlab_node_B.absxk;
      joystick_enabled_matlab_node_B.eps_tmp =
        joystick_enabled_matlab_node_B.eps_tmp *
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t
        + 1.0;
      joystick_enabled_matlab_node_B.scale =
        joystick_enabled_matlab_node_B.absxk;
    } else {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.absxk /
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps_tmp +=
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t;
    }

    if (joystick_enabled_matlab_node_B.eta >
        joystick_enabled_matlab_node_B.scale) {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.scale /
        joystick_enabled_matlab_node_B.eta;
      joystick_enabled_matlab_node_B.eps_tmp =
        joystick_enabled_matlab_node_B.eps_tmp *
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t
        + 1.0;
      joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.eta;
    } else {
      joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.eta /
        joystick_enabled_matlab_node_B.scale;
      joystick_enabled_matlab_node_B.eps_tmp +=
        joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.eps_tmp =
      joystick_enabled_matlab_node_B.scale * std::sqrt
      (joystick_enabled_matlab_node_B.eps_tmp);
    joystick_enabled_matlab_node_B.qib_int_u[0] =
      joystick_enabled_matlab_node_B.eps_n[0] /
      joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_B.qib_int_u[1] =
      joystick_enabled_matlab_node_B.eps_n[1] /
      joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_B.qib_int_u[2] =
      joystick_enabled_matlab_node_B.eps_n[2] /
      joystick_enabled_matlab_node_B.eps_tmp;
    joystick_enabled_matlab_node_B.qib_int_u[3] =
      joystick_enabled_matlab_node_B.eta /
      joystick_enabled_matlab_node_B.eps_tmp;
  } else {
    joystick_enabled_matlab_node_B.qib_int_u[0] =
      joystick_enabled_matlab_node_B.X_u[3];
    joystick_enabled_matlab_node_B.qib_int_u[1] =
      joystick_enabled_matlab_node_B.X_u[4];
    joystick_enabled_matlab_node_B.qib_int_u[2] =
      joystick_enabled_matlab_node_B.X_u[5];
    joystick_enabled_matlab_node_B.qib_int_u[3] =
      joystick_enabled_matlab_node_B.X_u[6];
  }

  joystick_enabled_matlab_node_B.qe_matlab[0] =
    ((joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
      joystick_enabled_matlab_node_B.qib_int_u[3] -
      -joystick_enabled_matlab_node_B.X_est.qib[0] *
      joystick_enabled_matlab_node_B.qib_int_u[0]) -
     -joystick_enabled_matlab_node_B.X_est.qib[1] *
     joystick_enabled_matlab_node_B.qib_int_u[1]) -
    -joystick_enabled_matlab_node_B.X_est.qib[2] *
    joystick_enabled_matlab_node_B.qib_int_u[2];
  joystick_enabled_matlab_node_B.qe_matlab[1] =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qib_int_u[0] +
     joystick_enabled_matlab_node_B.qib_int_u[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[0]) +
    (-joystick_enabled_matlab_node_B.X_est.qib[1] *
     joystick_enabled_matlab_node_B.qib_int_u[2] -
     joystick_enabled_matlab_node_B.qib_int_u[1] *
     -joystick_enabled_matlab_node_B.X_est.qib[2]);
  joystick_enabled_matlab_node_B.qe_matlab[2] =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qib_int_u[1] +
     joystick_enabled_matlab_node_B.qib_int_u[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[1]) +
    (joystick_enabled_matlab_node_B.qib_int_u[0] *
     -joystick_enabled_matlab_node_B.X_est.qib[2] -
     -joystick_enabled_matlab_node_B.X_est.qib[0] *
     joystick_enabled_matlab_node_B.qib_int_u[2]);
  joystick_enabled_matlab_node_B.qe_matlab[3] =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qib_int_u[2] +
     joystick_enabled_matlab_node_B.qib_int_u[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[2]) +
    (-joystick_enabled_matlab_node_B.X_est.qib[0] *
     joystick_enabled_matlab_node_B.qib_int_u[1] -
     joystick_enabled_matlab_node_B.qib_int_u[0] *
     -joystick_enabled_matlab_node_B.X_est.qib[1]);
  joystick_enabled_matlab_node_B.qinv[0] =
    joystick_enabled_matlab_node_B.qe_matlab[1];
  joystick_enabled_matlab_node_B.qinv[1] =
    joystick_enabled_matlab_node_B.qe_matlab[2];
  joystick_enabled_matlab_node_B.qinv[2] =
    joystick_enabled_matlab_node_B.qe_matlab[3];
  joystick_enabled_matlab_node_B.qinv[3] =
    joystick_enabled_matlab_node_B.qe_matlab[0];
  if (joystick_enabled_matlab_node_B.qe_matlab[0] < 0.0) {
    joystick_enabled_matlab_node_B.qinv[0] =
      -joystick_enabled_matlab_node_B.qe_matlab[1];
    joystick_enabled_matlab_node_B.qinv[1] =
      -joystick_enabled_matlab_node_B.qe_matlab[2];
    joystick_enabled_matlab_node_B.qinv[2] =
      -joystick_enabled_matlab_node_B.qe_matlab[3];
    joystick_enabled_matlab_node_B.qinv[3] =
      -joystick_enabled_matlab_node_B.qe_matlab[0];
  }

  joystick_enabled_matlab_node_B.eta = joystick_enabled_matlab_node_B.qinv[3] *
    joystick_enabled_matlab_node_B.qinv[3] * 2.0 - 1.0;
  joystick_enabled_matlab_node_B.b_t = 2.0 *
    joystick_enabled_matlab_node_B.qinv[3];
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.eps_tmp = 2.0 *
      joystick_enabled_matlab_node_B.qinv[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.Cbi_c[3 * joystick_enabled_matlab_node_B.i_o]
      = joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
      joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.eta +
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.qinv[0];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.eta +
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.qinv[1];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.eta +
      joystick_enabled_matlab_node_B.eps_tmp *
      joystick_enabled_matlab_node_B.qinv[2];
  }

  joystick_enabled_matlab_node_B.eta = joystick_enabled_matlab_node_B.b_t * 0.0;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[0] =
    joystick_enabled_matlab_node_B.eta;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[1] =
    joystick_enabled_matlab_node_B.b_t * -joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[2] =
    joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3] =
    joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[4] =
    joystick_enabled_matlab_node_B.eta;
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[5] =
    joystick_enabled_matlab_node_B.b_t * -joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[6] =
    joystick_enabled_matlab_node_B.b_t * -joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[7] =
    joystick_enabled_matlab_node_B.b_t * joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[8] =
    joystick_enabled_matlab_node_B.eta;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o] +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o];
  }

  joystick_enabled_matlab_node_B.theta_h = std::asin(std::fmax(-1.0, std::fmin
    (1.0, joystick_enabled_matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-joystick_enabled_matlab_node_B.theta_h)) < 1.0E-6) {
    joystick_enabled_matlab_node_B.eps[0] = 0.0;
    joystick_enabled_matlab_node_B.b_t = joystick_enabled__rt_atan2d_snf
      (-joystick_enabled_matlab_node_B.Cbi[1],
       joystick_enabled_matlab_node_B.Cbi[4]);
  } else {
    joystick_enabled_matlab_node_B.eps[0] = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[7],
       joystick_enabled_matlab_node_B.Cbi[8]);
    joystick_enabled_matlab_node_B.b_t = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[3],
       joystick_enabled_matlab_node_B.Cbi[0]);
  }

  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.eps[0]);
  joystick_enabled_matlab_node_B.theta_h =
    -joystick_enabled_matlab_node_B.theta_h;
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.theta_h);
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.b_t);
  joystick_enabled_matlab_node_B.eps[1] = joystick_enabled_matlab_node_B.theta_h;
  joystick_enabled_matlab_node_B.eps[2] = joystick_enabled_matlab_node_B.b_t;
  joystick_enabled_matlab_node_B.OR1 = false;
  rtb_RelationalOperator_idx_0 = true;
  joystick_enabled_matlab_node_B.i_o = 0;
  exitg1 = false;
  while ((!exitg1) && (joystick_enabled_matlab_node_B.i_o < 16)) {
    if (joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o] !=
        c[joystick_enabled_matlab_node_B.i_o]) {
      rtb_RelationalOperator_idx_0 = false;
      exitg1 = true;
    } else {
      joystick_enabled_matlab_node_B.i_o++;
    }
  }

  if (rtb_RelationalOperator_idx_0) {
    joystick_enabled_matlab_node_B.OR1 = true;
  }

  guard1 = false;
  if (joystick_enabled_matlab_node_B.OR1) {
    guard1 = true;
  } else {
    joystick_enabled_matlab_node_B.OR1 = false;
    rtb_RelationalOperator_idx_0 = true;
    joystick_enabled_matlab_node_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (joystick_enabled_matlab_node_B.i_o < 16)) {
      if (joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o]
          != d[joystick_enabled_matlab_node_B.i_o]) {
        rtb_RelationalOperator_idx_0 = false;
        exitg1 = true;
      } else {
        joystick_enabled_matlab_node_B.i_o++;
      }
    }

    if (rtb_RelationalOperator_idx_0) {
      joystick_enabled_matlab_node_B.OR1 = true;
    }

    if (joystick_enabled_matlab_node_B.OR1) {
      guard1 = true;
    }
  }

  if (guard1) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.x1[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.cmd.trick_id[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.OR1 = false;
    rtb_RelationalOperator_idx_0 = true;
    joystick_enabled_matlab_node_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (joystick_enabled_matlab_node_B.i_o < 16)) {
      if (joystick_enabled_matlab_node_B.x1[joystick_enabled_matlab_node_B.i_o]
          != e[joystick_enabled_matlab_node_B.i_o]) {
        rtb_RelationalOperator_idx_0 = false;
        exitg1 = true;
      } else {
        joystick_enabled_matlab_node_B.i_o++;
      }
    }

    if (rtb_RelationalOperator_idx_0) {
      joystick_enabled_matlab_node_B.OR1 = true;
    }

    if (joystick_enabled_matlab_node_B.OR1) {
      joystick_enabled_matlab_node_B.eps[0] = 0.0;
      joystick_enabled_matlab_node_B.eps[1] =
        joystick_enabled_matlab_node_B.theta_h;
      joystick_enabled_matlab_node_B.eps[2] = joystick_enabled_matlab_node_B.b_t;
    }
  }

  joystick_enabled_matlab_node_B.Rb_u[0] = std::abs
    (joystick_enabled_matlab_node_B.eps[0]);
  joystick_enabled_matlab_node_B.Rb_u[1] = std::abs
    (joystick_enabled_matlab_node_B.eps[1]);
  joystick_enabled_matlab_node_B.Rb_u[2] = std::abs
    (joystick_enabled_matlab_node_B.eps[2]);
  if (!std::isnan(joystick_enabled_matlab_node_B.Rb_u[0])) {
    joystick_enabled_matlab_node_B.i_o = 1;
  } else {
    joystick_enabled_matlab_node_B.i_o = 0;
    joystick_enabled_matlab_node_B.b_index = 2;
    exitg1 = false;
    while ((!exitg1) && (joystick_enabled_matlab_node_B.b_index < 4)) {
      if (!std::isnan
          (joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.b_index
           - 1])) {
        joystick_enabled_matlab_node_B.i_o =
          joystick_enabled_matlab_node_B.b_index;
        exitg1 = true;
      } else {
        joystick_enabled_matlab_node_B.b_index++;
      }
    }
  }

  if (joystick_enabled_matlab_node_B.i_o == 0) {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.Rb_u[0];
  } else {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o - 1];
    for (joystick_enabled_matlab_node_B.b_index =
         joystick_enabled_matlab_node_B.i_o + 1;
         joystick_enabled_matlab_node_B.b_index < 4;
         joystick_enabled_matlab_node_B.b_index++) {
      joystick_enabled_matlab_node_B.b_a_l =
        joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.b_index
        - 1];
      if (joystick_enabled_matlab_node_B.b_t <
          joystick_enabled_matlab_node_B.b_a_l) {
        joystick_enabled_matlab_node_B.b_t =
          joystick_enabled_matlab_node_B.b_a_l;
      }
    }
  }

  if (joystick_enabled_matlab_node_B.b_t > 0.17453292519943295) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t = 2.0 *
        joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3 *
        joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
        joystick_enabled_matlab_node_B.i_o] *
        joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[0];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 1;
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[1];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 2;
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[2];
    }

    joystick_enabled_matlab_node_B.Cbi_c[0] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.Cbi_c[1] =
      joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
    joystick_enabled_matlab_node_B.Cbi_c[2] = joystick_enabled_matlab_node_B.phi;
    joystick_enabled_matlab_node_B.Cbi_c[3] =
      joystick_enabled_matlab_node_B.alpha;
    joystick_enabled_matlab_node_B.Cbi_c[4] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.Cbi_c[5] =
      joystick_enabled_matlab_node_B.upper_voltage_index;
    joystick_enabled_matlab_node_B.Cbi_c[6] =
      joystick_enabled_matlab_node_B.lower_voltage_index;
    joystick_enabled_matlab_node_B.Cbi_c[7] =
      joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
    joystick_enabled_matlab_node_B.Cbi_c[8] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 9;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o]
        + joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.b_a_l = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t =
        joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.b_a_l +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_b +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 1] *
        joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_j +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 2] *
        joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.Rb_u[2] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_j;
    joystick_enabled_matlab_node_B.Rb_u[1] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_b;
    joystick_enabled_matlab_node_B.Rb_u[0] =
      joystick_enabled_matlab_node_B.b_a_l;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o]
        - ((joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
            + 3] * joystick_enabled_matlab_node_B.b_absxk +
            joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o]
            * joystick_enabled_matlab_node_B.b_scale) +
           joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
           + 6] * joystick_enabled_matlab_node_B.rotm_tmp);
    }

    joystick_enabled_matlab_node_B.eps_n[0] = 0.0;
    joystick_enabled_matlab_node_B.eps_n[1] = 0.0;
    joystick_enabled_matlab_node_B.eps_n[2] =
      joystick_enabled_matlab_node_B.eps[2];
    joystick_enabled_matlab_node_DW.action_id = 1.0;
  } else if (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 >= 0.5) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t = 2.0 *
        joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.Cbi_c[3 *
        joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
        joystick_enabled_matlab_node_B.i_o] *
        joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[0];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 1;
      joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[1];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 2;
      joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[2];
    }

    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[0] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[1] =
      joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[2] =
      joystick_enabled_matlab_node_B.phi;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3] =
      joystick_enabled_matlab_node_B.alpha;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[4] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[5] =
      joystick_enabled_matlab_node_B.upper_voltage_index;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[6] =
      joystick_enabled_matlab_node_B.lower_voltage_index;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[7] =
      joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[8] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 9;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o]
        + joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.b_a_l = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t =
        joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.b_a_l +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_b +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 1] *
        joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_j +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 2] *
        joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.Rb_u[2] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_j;
    joystick_enabled_matlab_node_B.Rb_u[1] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_b;
    joystick_enabled_matlab_node_B.Rb_u[0] =
      joystick_enabled_matlab_node_B.b_a_l;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.eps_n[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o]
        - ((joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
            + 3] * joystick_enabled_matlab_node_B.b_absxk +
            joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o]
            * joystick_enabled_matlab_node_B.b_scale) +
           joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
           + 6] * joystick_enabled_matlab_node_B.rotm_tmp);
    }

    joystick_enabled_matlab_node_DW.action_id = 2.0;
  } else {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t = 2.0 *
        joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.Cbi_c[3 *
        joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
        joystick_enabled_matlab_node_B.i_o] *
        joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[0];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 1;
      joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[1];
      joystick_enabled_matlab_node_B.b_index = 3 *
        joystick_enabled_matlab_node_B.i_o + 2;
      joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.b_index]
        =
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
        * joystick_enabled_matlab_node_B.upper_force_index +
        joystick_enabled_matlab_node_B.b_t *
        joystick_enabled_matlab_node_B.X_est.qib[2];
    }

    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[0] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[1] =
      joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[2] =
      joystick_enabled_matlab_node_B.phi;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3] =
      joystick_enabled_matlab_node_B.alpha;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[4] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[5] =
      joystick_enabled_matlab_node_B.upper_voltage_index;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[6] =
      joystick_enabled_matlab_node_B.lower_voltage_index;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[7] =
      joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[8] =
      joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 9;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o]
        + joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.b_a_l = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.b_t =
        joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.b_a_l +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o] * joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_b +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 1] *
        joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_j +=
        joystick_enabled_matlab_node_B.Cbi[3 *
        joystick_enabled_matlab_node_B.i_o + 2] *
        joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.Rb_u[2] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_j;
    joystick_enabled_matlab_node_B.Rb_u[1] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_b;
    joystick_enabled_matlab_node_B.Rb_u[0] =
      joystick_enabled_matlab_node_B.b_a_l;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 3;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.eps_n[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o]
        - ((joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
            + 3] * joystick_enabled_matlab_node_B.b_absxk +
            joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o]
            * joystick_enabled_matlab_node_B.b_scale) +
           joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.i_o
           + 6] * joystick_enabled_matlab_node_B.rotm_tmp);
    }

    joystick_enabled_matlab_node_DW.action_id = 3.0;
  }

  joystick_enabled_matlab_node_DW.UnitDelay_DSTATE =
    joystick_enabled_matlab_node_DW.action_id;
  joystick_enabled_matlab_node_DW.UnitDelay1_DSTATE =
    joystick_enabled_matlab_node_DW.persistant_yaw_target;
  joystick_enabled_matlab_node_DW.prior_action_id_g =
    joystick_enabled_matlab_node_DW.action_id;

  // Gain: '<S25>/Gain5' incorporates:
  //   DataStoreWrite: '<S25>/Data Store Write1'
  //   RelationalOperator: '<S29>/FixPt Relational Operator'
  //   UnitDelay: '<S29>/Delay Input1'
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S29>/Delay Input1':
  //
  //   Store in Global RAM

  joystick_enabled_matlab_node_B.integrator_reset = static_cast<uint8_T>
    ((joystick_enabled_matlab_node_DW.UnitDelay_DSTATE !=
      joystick_enabled_matlab_node_DW.DelayInput1_DSTATE) << 7);

  // MATLAB Function: '<S25>/quatInjector' incorporates:
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   UnitDelay: '<S4>/Unit Delay'

  joystick_enabled_matlab_node_B.Rb_u[1] = joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.Rb_u[2] = joystick_enabled_matlab_node_B.t;
  if ((joystick_enabled_matlab_node_DW.UnitDelay_DSTATE == 2.0) ||
      (joystick_enabled_matlab_node_DW.UnitDelay_DSTATE == 1.0)) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.x1[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.cmd.trick_id[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.i_o = std::memcmp(&a_1[0],
      &joystick_enabled_matlab_node_B.x1[0], 16);
    if (joystick_enabled_matlab_node_B.i_o == 0) {
      joystick_enabled_matlab_node_B.Rb_u[0] =
        joystick_enabled_matlab_node_B.norm_w + 3.1;
      joystick_enabled_matl_eulToQuat(joystick_enabled_matlab_node_B.Rb_u,
        joystick_enabled_matlab_node_B.qe_matlab);
    } else {
      joystick_enabled_matlab_node_B.qe_matlab[0] =
        joystick_enabled_matlab_node_B.qib_int_u[0];
      joystick_enabled_matlab_node_B.qe_matlab[1] =
        joystick_enabled_matlab_node_B.qib_int_u[1];
      joystick_enabled_matlab_node_B.qe_matlab[2] =
        joystick_enabled_matlab_node_B.qib_int_u[2];
      joystick_enabled_matlab_node_B.qe_matlab[3] =
        joystick_enabled_matlab_node_B.qib_int_u[3];
    }
  } else {
    joystick_enabled_matlab_node_B.qe_matlab[0] =
      joystick_enabled_matlab_node_B.qib_int_u[0];
    joystick_enabled_matlab_node_B.qe_matlab[1] =
      joystick_enabled_matlab_node_B.qib_int_u[1];
    joystick_enabled_matlab_node_B.qe_matlab[2] =
      joystick_enabled_matlab_node_B.qib_int_u[2];
    joystick_enabled_matlab_node_B.qe_matlab[3] =
      joystick_enabled_matlab_node_B.qib_int_u[3];
  }

  // End of MATLAB Function: '<S25>/quatInjector'

  // DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_PrevRese <= 0)) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0;
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0;
  }

  // MATLAB Function: '<S25>/deltaQuatError' incorporates:
  //   MATLAB Function: '<S25>/guidanceLaw'
  //   MATLAB Function: '<S25>/quatPID'
  //   MATLAB Function: '<S6>/discreteTimeQuatPropagation'

  joystick_enabled_matlab_node_B.b_t =
    ((joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
      joystick_enabled_matlab_node_B.qe_matlab[3] -
      -joystick_enabled_matlab_node_B.X_est.qib[0] *
      joystick_enabled_matlab_node_B.qe_matlab[0]) -
     -joystick_enabled_matlab_node_B.X_est.qib[1] *
     joystick_enabled_matlab_node_B.qe_matlab[1]) -
    -joystick_enabled_matlab_node_B.X_est.qib[2] *
    joystick_enabled_matlab_node_B.qe_matlab[2];
  joystick_enabled_matlab_node_B.eps_b =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qe_matlab[0] +
     joystick_enabled_matlab_node_B.qe_matlab[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[0]) +
    (-joystick_enabled_matlab_node_B.X_est.qib[1] *
     joystick_enabled_matlab_node_B.qe_matlab[2] -
     joystick_enabled_matlab_node_B.qe_matlab[1] *
     -joystick_enabled_matlab_node_B.X_est.qib[2]);
  joystick_enabled_matlab_node_B.eta = joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qe_matlab[1] +
     joystick_enabled_matlab_node_B.qe_matlab[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[1]) +
    (joystick_enabled_matlab_node_B.qe_matlab[0] *
     -joystick_enabled_matlab_node_B.X_est.qib[2] -
     -joystick_enabled_matlab_node_B.X_est.qib[0] *
     joystick_enabled_matlab_node_B.qe_matlab[2]);
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  joystick_enabled_matlab_node_B.b_a_l =
    (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *
     joystick_enabled_matlab_node_B.qe_matlab[2] +
     joystick_enabled_matlab_node_B.qe_matlab[3] *
     -joystick_enabled_matlab_node_B.X_est.qib[2]) +
    (-joystick_enabled_matlab_node_B.X_est.qib[0] *
     joystick_enabled_matlab_node_B.qe_matlab[1] -
     joystick_enabled_matlab_node_B.qe_matlab[0] *
     -joystick_enabled_matlab_node_B.X_est.qib[1]);
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
    joystick_enabled_matlab_node_B.b_a_l;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3 =
    joystick_enabled_matlab_node_B.b_t;
  if (joystick_enabled_matlab_node_B.b_t < 0.0) {
    joystick_enabled_matlab_node_B.eta = -joystick_enabled_matlab_node_B.eps_b;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 =
      -joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 =
      -joystick_enabled_matlab_node_B.b_a_l;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3 =
      -joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.OR1 = false;
  if (std::isnan(joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3)) {
    joystick_enabled_matlab_node_B.theta_h = (rtNaN);
  } else {
    joystick_enabled_matlab_node_B.theta_h =
      (joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3 > 0.0);
  }

  if (joystick_enabled_matlab_node_B.theta_h == 0.0) {
    joystick_enabled_matlab_node_B.OR1 = true;
  }

  if (!joystick_enabled_matlab_node_B.OR1) {
    joystick_enabled_matlab_node_B.eta *= joystick_enabled_matlab_node_B.theta_h;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1 *=
      joystick_enabled_matlab_node_B.theta_h;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2 *=
      joystick_enabled_matlab_node_B.theta_h;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3 *=
      joystick_enabled_matlab_node_B.theta_h;
  }

  // SignalConversion generated from: '<S25>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  joystick_enabled_matlab_node_B.qe_matlab_g[0] = 1.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3;
  joystick_enabled_matlab_node_B.qe_matlab_g[1] = 0.0 -
    joystick_enabled_matlab_node_B.eta;
  joystick_enabled_matlab_node_B.qe_matlab_g[2] = 0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1;
  joystick_enabled_matlab_node_B.qe_matlab_g[3] = 0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2;

  // DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  joystick_enabled_matlab_node_B.eps_tmp = ((1.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3) -
    (-joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[0])) / 1.1;
  joystick_enabled_matlab_node_B.scale = joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_B.DiscreteTransferFcn[0] = 10.0 *
    joystick_enabled_matlab_node_B.eps_tmp + -10.0 *
    joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[0];
  joystick_enabled_matlab_node_B.eps_tmp = ((0.0 -
    joystick_enabled_matlab_node_B.eta) -
    (-joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[1])) / 1.1;
  joystick_enabled_matlab_node_B.absxk = joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_B.DiscreteTransferFcn[1] = 10.0 *
    joystick_enabled_matlab_node_B.eps_tmp + -10.0 *
    joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[1];
  joystick_enabled_matlab_node_B.eps_tmp = ((0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1) -
    (-joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[2])) / 1.1;
  joystick_enabled_matlab_node_B.DiscreteTransferFcn_tmp_idx_2 =
    joystick_enabled_matlab_node_B.eps_tmp;
  joystick_enabled_matlab_node_B.DiscreteTransferFcn[2] = 10.0 *
    joystick_enabled_matlab_node_B.eps_tmp + -10.0 *
    joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[2];
  joystick_enabled_matlab_node_B.eps_tmp = ((0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2) -
    (-joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[3])) / 1.1;
  joystick_enabled_matlab_node_B.DiscreteTransferFcn[3] = 10.0 *
    joystick_enabled_matlab_node_B.eps_tmp + -10.0 *
    joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[3];

  // MATLAB Function: '<S25>/quatPID' incorporates:
  //   DiscreteIntegrator: '<S31>/Discrete-Time Integrator'
  //   Gain: '<S25>/Gain1'
  //   Gain: '<S25>/Gain2'
  //   SignalConversion generated from: '<S25>/Discrete Transfer Fcn'

  joystick_enabled_matlab_node_B.qinv[0] = joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.qinv[1] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  joystick_enabled_matlab_node_B.qinv[2] = joystick_enabled_matlab_node_B.b_a_l;
  joystick_enabled_matlab_node_B.qinv[3] = joystick_enabled_matlab_node_B.b_t;
  if (joystick_enabled_matlab_node_B.b_t < 0.0) {
    joystick_enabled_matlab_node_B.qinv[0] =
      -joystick_enabled_matlab_node_B.eps_b;
    joystick_enabled_matlab_node_B.qinv[1] =
      -joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
    joystick_enabled_matlab_node_B.qinv[2] =
      -joystick_enabled_matlab_node_B.b_a_l;
    joystick_enabled_matlab_node_B.qinv[3] = -joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.Qe1[0] = -joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.Qe1[4] = -joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[8] = -joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[1] = joystick_enabled_matlab_node_B.qinv[3];
  joystick_enabled_matlab_node_B.Qe1[5] = -joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[9] = joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[2] = joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[6] = joystick_enabled_matlab_node_B.qinv[3];
  joystick_enabled_matlab_node_B.Qe1[10] = -joystick_enabled_matlab_node_B.qinv
    [0];
  joystick_enabled_matlab_node_B.Qe1[3] = -joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[7] = joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.Qe1[11] = joystick_enabled_matlab_node_B.qinv[3];
  joystick_enabled_matlab_node_B.eps_b = 0.0;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp = 0.0;
  joystick_enabled_matlab_node_B.b_a_l = 0.0;
  joystick_enabled_matlab_node_B.eps_f = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 4;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0;
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0;
    joystick_enabled_matlab_node_B.theta_h = 0.0;
    joystick_enabled_matlab_node_B.Qe1_e = 0.0;
    for (joystick_enabled_matlab_node_B.b_index = 0;
         joystick_enabled_matlab_node_B.b_index < 3;
         joystick_enabled_matlab_node_B.b_index++) {
      joystick_enabled_matlab_node_B.pos =
        joystick_enabled_matlab_node_B.b_index << 2;
      joystick_enabled_matlab_node_B.b_t =
        joystick_enabled_matlab_node_B.Qe1[joystick_enabled_matlab_node_B.pos +
        joystick_enabled_matlab_node_B.i_o];
      joystick_enabled_matlab_node_B.rtb_Rb_u_j +=
        joystick_enabled_matlab_node_B.Qe1[joystick_enabled_matlab_node_B.pos] *
        joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.rtb_Rb_u_b +=
        joystick_enabled_matlab_node_B.Qe1[joystick_enabled_matlab_node_B.pos +
        1] * joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.theta_h +=
        joystick_enabled_matlab_node_B.Qe1[joystick_enabled_matlab_node_B.pos +
        2] * joystick_enabled_matlab_node_B.b_t;
      joystick_enabled_matlab_node_B.Qe1_e +=
        joystick_enabled_matlab_node_B.Qe1[joystick_enabled_matlab_node_B.pos +
        3] * joystick_enabled_matlab_node_B.b_t;
    }

    joystick_enabled_matlab_node_B.b_index = joystick_enabled_matlab_node_B.i_o <<
      2;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      3] = joystick_enabled_matlab_node_B.Qe1_e;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      2] = joystick_enabled_matlab_node_B.theta_h;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index +
      1] = joystick_enabled_matlab_node_B.rtb_Rb_u_b;
    joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index] =
      joystick_enabled_matlab_node_B.rtb_Rb_u_j;
    joystick_enabled_matlab_node_B.dv1[joystick_enabled_matlab_node_B.i_o] =
      (joystick_enabled_matlab__ConstP.Gain1_Gain[joystick_enabled_matlab_node_B.i_o]
       * joystick_enabled_matlab_node_B.qe_matlab_g[joystick_enabled_matlab_node_B.i_o]
       + 0.0 *
       joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[joystick_enabled_matlab_node_B.i_o])
      + joystick_enabled_matlab_node_B.DiscreteTransferFcn[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.dv1[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.eps_b +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 1] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.b_a_l +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 2] * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.eps_f +=
      joystick_enabled_matlab_node_B.c_a[joystick_enabled_matlab_node_B.b_index
      + 3] * joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.Qe1[0] = joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.Qe1[1] = joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[2] = joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[3] = -joystick_enabled_matlab_node_B.qinv[3];
  joystick_enabled_matlab_node_B.Qe1[4] = -joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[5] = joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[6] = joystick_enabled_matlab_node_B.qinv[2];
  joystick_enabled_matlab_node_B.Qe1[7] = -joystick_enabled_matlab_node_B.qinv[3];
  joystick_enabled_matlab_node_B.Qe1[8] = -joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.Qe1[9] = -joystick_enabled_matlab_node_B.qinv[1];
  joystick_enabled_matlab_node_B.Qe1[10] = joystick_enabled_matlab_node_B.qinv[0];
  joystick_enabled_matlab_node_B.Qe1[11] = -joystick_enabled_matlab_node_B.qinv
    [3];
  joystick_enabled_matlab_node_B.dv1[0] = 2.0 *
    joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.dv1[1] = 2.0 *
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  joystick_enabled_matlab_node_B.dv1[2] = 2.0 *
    joystick_enabled_matlab_node_B.b_a_l;
  joystick_enabled_matlab_node_B.dv1[3] = 2.0 *
    joystick_enabled_matlab_node_B.eps_f;
  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp = 0.0;
  joystick_enabled_matlab_node_B.eps_b = 0.0;
  joystick_enabled_matlab_node_B.b_a_l = 0.0;
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 4;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.dv1[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp +=
      joystick_enabled_matlab_node_B.Qe1[3 * joystick_enabled_matlab_node_B.i_o]
      * joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.eps_b += joystick_enabled_matlab_node_B.Qe1[3
      * joystick_enabled_matlab_node_B.i_o + 1] *
      joystick_enabled_matlab_node_B.b_t;
    joystick_enabled_matlab_node_B.b_a_l += joystick_enabled_matlab_node_B.Qe1[3
      * joystick_enabled_matlab_node_B.i_o + 2] *
      joystick_enabled_matlab_node_B.b_t;
  }

  joystick_enabled_matlab_node_B.wb_u[2] = joystick_enabled_matlab_node_B.b_a_l;
  joystick_enabled_matlab_node_B.wb_u[1] = joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.wb_u[0] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;

  // DiscreteIntegrator: '<S136>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read1'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Integrator_PrevResetState <= 0)) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[0] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[1] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[2] = 0.0;
  }

  // DiscreteIntegrator: '<S131>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read1'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Filter_PrevResetState <= 0)) {
    joystick_enabled_matlab_node_DW.Filter_DSTATE[0] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE[1] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE[2] = 0.0;
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    // Gain: '<S129>/Derivative Gain'
    joystick_enabled_matlab_node_B.eps_b =
      joystick_enabled_matlab_node_B.eps_n[joystick_enabled_matlab_node_B.i_o];

    // Gain: '<S139>/Filter Coefficient' incorporates:
    //   DiscreteIntegrator: '<S131>/Filter'
    //   Gain: '<S129>/Derivative Gain'
    //   Sum: '<S131>/SumD'

    joystick_enabled_matlab_node_B.eps_f = (0.0 *
      joystick_enabled_matlab_node_B.eps_b -
      joystick_enabled_matlab_node_DW.Filter_DSTATE[joystick_enabled_matlab_node_B.i_o])
      * 100.0;
    joystick_enabled_matlab_node_B.eps_p[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.eps_f;

    // Sum: '<S145>/Sum' incorporates:
    //   DeadZone: '<S128>/DeadZone'
    //   DiscreteIntegrator: '<S136>/Integrator'
    //   Gain: '<S139>/Filter Coefficient'
    //   Gain: '<S141>/Proportional Gain'

    joystick_enabled_matlab_node_B.b_a_l =
      (joystick_enabled_matlab__ConstP.ProportionalGain_Gain[joystick_enabled_matlab_node_B.i_o]
       * joystick_enabled_matlab_node_B.eps_b +
       joystick_enabled_matlab_node_DW.Integrator_DSTATE[joystick_enabled_matlab_node_B.i_o])
      + joystick_enabled_matlab_node_B.eps_f;
    joystick_enabled_matlab_node_B.Rb_u[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.b_a_l;

    // Saturate: '<S143>/Saturation'
    if (joystick_enabled_matlab_node_B.b_a_l > 1.0) {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o] =
        1.0;
    } else if (joystick_enabled_matlab_node_B.b_a_l < -1.0) {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o] =
        -1.0;
    } else {
      // MATLAB Function: '<S25>/dRbSetpointInjector'
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.b_a_l;
    }

    // End of Saturate: '<S143>/Saturation'

    // MATLAB Function: '<S25>/quatToRotm' incorporates:
    //   DataStoreRead: '<S25>/Data Store Read'
    //   DataStoreWrite: '<S25>/Data Store Write'
    //   Math: '<S25>/Transpose'

    joystick_enabled_matlab_node_B.b_t = 2.0 *
      joystick_enabled_matlab_node_B.X_est.qib[joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[3 *
      joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[3 *
      joystick_enabled_matlab_node_B.i_o] *
      joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.X_est.qib[0];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.X_est.qib[1];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.b_index]
      =
      joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.b_index]
      * joystick_enabled_matlab_node_B.upper_force_index +
      joystick_enabled_matlab_node_B.b_t *
      joystick_enabled_matlab_node_B.X_est.qib[2];
  }

  // Math: '<S25>/Transpose'
  joystick_enabled_matlab_node_B.Cbi_c[0] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[1] =
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[2] = joystick_enabled_matlab_node_B.phi;
  joystick_enabled_matlab_node_B.Cbi_c[3] = joystick_enabled_matlab_node_B.alpha;
  joystick_enabled_matlab_node_B.Cbi_c[4] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;
  joystick_enabled_matlab_node_B.Cbi_c[5] =
    joystick_enabled_matlab_node_B.upper_voltage_index;
  joystick_enabled_matlab_node_B.Cbi_c[6] =
    joystick_enabled_matlab_node_B.lower_voltage_index;
  joystick_enabled_matlab_node_B.Cbi_c[7] =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
  joystick_enabled_matlab_node_B.Cbi_c[8] =
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0;

  // MATLAB Function: '<S25>/quatToRotm'
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 9;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o]
      =
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp_b[joystick_enabled_matlab_node_B.i_o]
      + joystick_enabled_matlab_node_B.Cbi_c[joystick_enabled_matlab_node_B.i_o];
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    // Sum: '<S25>/Subtract4' incorporates:
    //   MATLAB Function: '<S6>/derivedStateEstimates'
    //   Product: '<S25>/Matrix Multiply3'

    joystick_enabled_matlab_node_B.dRb_e[joystick_enabled_matlab_node_B.i_o] =
      joystick_enabled_matlab_node_B.eps[joystick_enabled_matlab_node_B.i_o] -
      ((joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o
        + 3] * joystick_enabled_matlab_node_B.pwms_horiz_idx_3 +
        joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o]
        * joystick_enabled_matlab_node_B.pwms_horiz_idx_2) +
       joystick_enabled_matlab_node_B.rtb_sensors_dvl_cov[joystick_enabled_matlab_node_B.i_o
       + 6] * joystick_enabled_matlab_node_B.rtb_X_est_idx_2);

    // MATLAB Function: '<S25>/rateInjector' incorporates:
    //   SignalConversion generated from: '<S25>/Bus Selector'
    //   Sum: '<S25>/Subtract'

    joystick_enabled_matlab_node_B.wb_u[joystick_enabled_matlab_node_B.i_o] -=
      joystick_enabled_matlab_node_B.X_est.wb[joystick_enabled_matlab_node_B.i_o];
  }

  // MATLAB Function: '<S25>/rateInjector' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S25>/trickFTListInjector'
  //   MATLAB Function: '<S6>/derivedStateEstimates'
  //   Product: '<S6>/Matrix Multiply2'

  joystick_enabled_matlab_node_B.OR1 = joystick_enabled_matlab_isequal
    (joystick_enabled_matlab_node_B.s);
  if (joystick_enabled_matlab_node_B.OR1) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.x1[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.cmd.trick_id[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.i_o = std::memcmp(&a_2[0],
      &joystick_enabled_matlab_node_B.x1[0], 16);
    if (joystick_enabled_matlab_node_B.i_o == 0) {
      joystick_enabled_matlab_node_B.b_index = 0;
    } else {
      joystick_enabled_matlab_node_B.i_o = std::memcmp(&b_a_1[0],
        &joystick_enabled_matlab_node_B.x1[0], 16);
      if (joystick_enabled_matlab_node_B.i_o == 0) {
        joystick_enabled_matlab_node_B.b_index = 1;
      } else {
        joystick_enabled_matlab_node_B.i_o = std::memcmp(&c_a_1[0],
          &joystick_enabled_matlab_node_B.x1[0], 16);
        if (joystick_enabled_matlab_node_B.i_o == 0) {
          joystick_enabled_matlab_node_B.b_index = 2;
        } else {
          joystick_enabled_matlab_node_B.i_o = std::memcmp(&d_a_0[0],
            &joystick_enabled_matlab_node_B.x1[0], 16);
          if (joystick_enabled_matlab_node_B.i_o == 0) {
            joystick_enabled_matlab_node_B.b_index = 3;
          } else {
            joystick_enabled_matlab_node_B.i_o = std::memcmp(&e_a[0],
              &joystick_enabled_matlab_node_B.x1[0], 16);
            if (joystick_enabled_matlab_node_B.i_o == 0) {
              joystick_enabled_matlab_node_B.b_index = 4;
            } else {
              joystick_enabled_matlab_node_B.i_o = std::memcmp(&f_a[0],
                &joystick_enabled_matlab_node_B.x1[0], 16);
              if (joystick_enabled_matlab_node_B.i_o == 0) {
                joystick_enabled_matlab_node_B.b_index = 5;
              } else {
                joystick_enabled_matlab_node_B.i_o = std::memcmp(&g_a[0],
                  &joystick_enabled_matlab_node_B.x1[0], 16);
                if (joystick_enabled_matlab_node_B.i_o == 0) {
                  joystick_enabled_matlab_node_B.b_index = 6;
                } else {
                  joystick_enabled_matlab_node_B.i_o = std::memcmp(&h_a[0],
                    &joystick_enabled_matlab_node_B.x1[0], 16);
                  if (joystick_enabled_matlab_node_B.i_o == 0) {
                    joystick_enabled_matlab_node_B.b_index = 7;
                  } else {
                    joystick_enabled_matlab_node_B.i_o = std::memcmp(&i_a[0],
                      &joystick_enabled_matlab_node_B.x1[0], 16);
                    if (joystick_enabled_matlab_node_B.i_o == 0) {
                      joystick_enabled_matlab_node_B.b_index = 8;
                    } else {
                      joystick_enabled_matlab_node_B.i_o = std::memcmp(&j_a[0],
                        &joystick_enabled_matlab_node_B.x1[0], 16);
                      if (joystick_enabled_matlab_node_B.i_o == 0) {
                        joystick_enabled_matlab_node_B.b_index = 9;
                      } else if (joystick_enabled_matlab__strcmp
                                 (joystick_enabled_matlab_node_B.x1)) {
                        joystick_enabled_matlab_node_B.b_index = 10;
                      } else if (joystick_enabled_matla_strcmp_g
                                 (joystick_enabled_matlab_node_B.x1)) {
                        joystick_enabled_matlab_node_B.b_index = 11;
                      } else if (joystick_enabled_matl_strcmp_gy
                                 (joystick_enabled_matlab_node_B.x1)) {
                        joystick_enabled_matlab_node_B.b_index = 12;
                      } else {
                        joystick_enabled_matlab_node_B.b_index = -1;
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

    switch (joystick_enabled_matlab_node_B.b_index) {
     case 0:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.5 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 1:
      joystick_enabled_matlab_node_B.dRb_e[0] = -0.5 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 2:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = -1.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 3:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 1.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 4:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 1.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 5:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = -1.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 6:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 1.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 7:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = -1.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 8:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 1.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 9:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = -1.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 10:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 1.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 11:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = -1.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;

     case 12:
      joystick_enabled_matlab_node_B.dRb_e[0] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];
      joystick_enabled_matlab_node_B.wb_u[0] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_Integrator_i_d;
      joystick_enabled_matlab_node_B.dRb_e[1] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];
      joystick_enabled_matlab_node_B.wb_u[1] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb;
      joystick_enabled_matlab_node_B.dRb_e[2] = 0.0 -
        joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];
      joystick_enabled_matlab_node_B.wb_u[2] = 0.0 -
        joystick_enabled_matlab_node_B.rtb_X_est_wb_a;
      break;
    }
  }

  // DiscreteIntegrator: '<S81>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read7'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Integrator_PrevResetState_d <= 0)) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2] = 0.0;
  }

  // DiscreteIntegrator: '<S76>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read7'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Filter_PrevResetState_j <= 0)) {
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[0] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[1] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[2] = 0.0;
  }

  // Gain: '<S84>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S76>/Filter'
  //   Gain: '<S74>/Derivative Gain'
  //   Sum: '<S76>/SumD'

  joystick_enabled_matlab_node_B.eps_b = (0.0 *
    joystick_enabled_matlab_node_B.wb_u[0] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[0]) * 100.0;
  joystick_enabled_matlab_node_B.eps[0] = joystick_enabled_matlab_node_B.eps_b;

  // Sum: '<S90>/Sum' incorporates:
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   Gain: '<S74>/Derivative Gain'

  joystick_enabled_matlab_node_B.upper_force_index =
    (joystick_enabled_matlab_node_B.wb_u[0] +
     joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0]) +
    joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 =
    joystick_enabled_matlab_node_B.upper_force_index;

  // DeadZone: '<S73>/DeadZone'
  if (joystick_enabled_matlab_node_B.upper_force_index > 10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - 10.0;
  } else if (joystick_enabled_matlab_node_B.upper_force_index >= -10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - -10.0;
  }

  // RelationalOperator: '<S71>/Relational Operator' incorporates:
  //   Constant: '<S71>/Clamping_zero'

  rtb_RelationalOperator_idx_0 =
    (joystick_enabled_matlab_node_B.rtb_Integrator_i_d != 0.0);

  // RelationalOperator: '<S71>/fix for DT propagation issue' incorporates:
  //   Constant: '<S71>/Clamping_zero'

  rtb_fixforDTpropagationissue_id =
    (joystick_enabled_matlab_node_B.rtb_Integrator_i_d > 0.0);

  // Gain: '<S78>/Integral Gain' incorporates:
  //   Gain: '<S74>/Derivative Gain'

  joystick_enabled_matlab_node_B.Integrator_i[0] =
    joystick_enabled_matlab_node_B.wb_u[0];

  // Gain: '<S84>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S76>/Filter'
  //   Gain: '<S74>/Derivative Gain'
  //   Sum: '<S76>/SumD'

  joystick_enabled_matlab_node_B.eps_b = (0.0 *
    joystick_enabled_matlab_node_B.wb_u[1] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[1]) * 100.0;
  joystick_enabled_matlab_node_B.eps[1] = joystick_enabled_matlab_node_B.eps_b;

  // Gain: '<S86>/Proportional Gain' incorporates:
  //   Gain: '<S74>/Derivative Gain'
  //   Gain: '<S78>/Integral Gain'

  joystick_enabled_matlab_node_B.rtb_X_est_wb = 5.0 *
    joystick_enabled_matlab_node_B.wb_u[1];

  // Sum: '<S90>/Sum' incorporates:
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   Gain: '<S86>/Proportional Gain'

  joystick_enabled_matlab_node_B.upper_force_index =
    (joystick_enabled_matlab_node_B.rtb_X_est_wb +
     joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1]) +
    joystick_enabled_matlab_node_B.eps_b;
  joystick_enabled_matlab_node_B.b_t =
    joystick_enabled_matlab_node_B.upper_force_index;

  // DeadZone: '<S73>/DeadZone'
  if (joystick_enabled_matlab_node_B.upper_force_index > 10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - 10.0;
  } else if (joystick_enabled_matlab_node_B.upper_force_index >= -10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - -10.0;
  }

  // RelationalOperator: '<S71>/Relational Operator' incorporates:
  //   Constant: '<S71>/Clamping_zero'

  rtb_RelationalOperator_idx_1 =
    (joystick_enabled_matlab_node_B.rtb_Integrator_i_d != 0.0);

  // RelationalOperator: '<S71>/fix for DT propagation issue' incorporates:
  //   Constant: '<S71>/Clamping_zero'

  rtb_fixforDTpropagationissue__0 =
    (joystick_enabled_matlab_node_B.rtb_Integrator_i_d > 0.0);

  // Gain: '<S84>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S76>/Filter'
  //   Gain: '<S74>/Derivative Gain'
  //   Sum: '<S76>/SumD'

  joystick_enabled_matlab_node_B.eps_b = (0.0 *
    joystick_enabled_matlab_node_B.wb_u[2] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_n[2]) * 100.0;

  // Gain: '<S86>/Proportional Gain' incorporates:
  //   Gain: '<S74>/Derivative Gain'
  //   Gain: '<S78>/Integral Gain'

  joystick_enabled_matlab_node_B.rtb_X_est_wb_a = 5.0 *
    joystick_enabled_matlab_node_B.wb_u[2];

  // Sum: '<S90>/Sum' incorporates:
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   Gain: '<S86>/Proportional Gain'

  joystick_enabled_matlab_node_B.upper_force_index =
    (joystick_enabled_matlab_node_B.rtb_X_est_wb_a +
     joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2]) +
    joystick_enabled_matlab_node_B.eps_b;

  // DeadZone: '<S73>/DeadZone'
  if (joystick_enabled_matlab_node_B.upper_force_index > 10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - 10.0;
  } else if (joystick_enabled_matlab_node_B.upper_force_index >= -10.0) {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Integrator_i_d =
      joystick_enabled_matlab_node_B.upper_force_index - -10.0;
  }

  // DiscreteIntegrator: '<S191>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read9'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Integrator_PrevResetState_p <= 0)) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1] = 0.0;
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2] = 0.0;
  }

  // DiscreteIntegrator: '<S186>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read9'

  if ((joystick_enabled_matlab_node_B.integrator_reset > 0) &&
      (joystick_enabled_matlab_node_DW.Filter_PrevResetState_a <= 0)) {
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[0] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[1] = 0.0;
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[2] = 0.0;
  }

  // Gain: '<S194>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S186>/Filter'
  //   Gain: '<S184>/Derivative Gain'
  //   Sum: '<S186>/SumD'

  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp = (0.0 *
    joystick_enabled_matlab_node_B.dRb_e[0] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[0]) * 100.0;
  joystick_enabled_matlab_node_B.wb_u[0] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;

  // Sum: '<S200>/Sum' incorporates:
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   Gain: '<S184>/Derivative Gain'
  //   Gain: '<S196>/Proportional Gain'

  joystick_enabled_matlab_node_B.phi = (60.0 *
    joystick_enabled_matlab_node_B.dRb_e[0] +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0]) +
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 =
    joystick_enabled_matlab_node_B.phi;

  // Saturate: '<S88>/Saturation'
  if (joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 > 10.0) {
    joystick_enabled_matlab_node_B.dv3[0] = 10.0;
  } else if (joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 < -10.0) {
    joystick_enabled_matlab_node_B.dv3[0] = -10.0;
  } else {
    joystick_enabled_matlab_node_B.dv3[0] =
      joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0;
  }

  // Saturate: '<S198>/Saturation'
  if (joystick_enabled_matlab_node_B.phi > 100.0) {
    joystick_enabled_matlab_node_B.dv4[0] = 100.0;
  } else if (joystick_enabled_matlab_node_B.phi < -100.0) {
    joystick_enabled_matlab_node_B.dv4[0] = -100.0;
  } else {
    joystick_enabled_matlab_node_B.dv4[0] = joystick_enabled_matlab_node_B.phi;
  }

  // Gain: '<S194>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S186>/Filter'
  //   Gain: '<S184>/Derivative Gain'
  //   Sum: '<S186>/SumD'

  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp = (0.0 *
    joystick_enabled_matlab_node_B.dRb_e[1] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[1]) * 100.0;
  joystick_enabled_matlab_node_B.wb_u[1] =
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;

  // Sum: '<S200>/Sum' incorporates:
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   Gain: '<S184>/Derivative Gain'
  //   Gain: '<S196>/Proportional Gain'

  joystick_enabled_matlab_node_B.phi = (60.0 *
    joystick_enabled_matlab_node_B.dRb_e[1] +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1]) +
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 =
    joystick_enabled_matlab_node_B.phi;

  // Saturate: '<S88>/Saturation'
  if (joystick_enabled_matlab_node_B.b_t > 10.0) {
    joystick_enabled_matlab_node_B.dv3[1] = 10.0;
  } else if (joystick_enabled_matlab_node_B.b_t < -10.0) {
    joystick_enabled_matlab_node_B.dv3[1] = -10.0;
  } else {
    joystick_enabled_matlab_node_B.dv3[1] = joystick_enabled_matlab_node_B.b_t;
  }

  // Saturate: '<S198>/Saturation'
  if (joystick_enabled_matlab_node_B.phi > 100.0) {
    joystick_enabled_matlab_node_B.dv4[1] = 100.0;
  } else if (joystick_enabled_matlab_node_B.phi < -100.0) {
    joystick_enabled_matlab_node_B.dv4[1] = -100.0;
  } else {
    joystick_enabled_matlab_node_B.dv4[1] = joystick_enabled_matlab_node_B.phi;
  }

  // Gain: '<S194>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S186>/Filter'
  //   Gain: '<S184>/Derivative Gain'
  //   Sum: '<S186>/SumD'

  joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp = (0.0 *
    joystick_enabled_matlab_node_B.dRb_e[2] -
    joystick_enabled_matlab_node_DW.Filter_DSTATE_g[2]) * 100.0;

  // Sum: '<S200>/Sum' incorporates:
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   Gain: '<S184>/Derivative Gain'
  //   Gain: '<S196>/Proportional Gain'

  joystick_enabled_matlab_node_B.phi = (100.0 *
    joystick_enabled_matlab_node_B.dRb_e[2] +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2]) +
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;

  // Saturate: '<S88>/Saturation' incorporates:
  //   Sum: '<S90>/Sum'

  if (joystick_enabled_matlab_node_B.upper_force_index > 10.0) {
    joystick_enabled_matlab_node_B.dv3[2] = 10.0;
  } else if (joystick_enabled_matlab_node_B.upper_force_index < -10.0) {
    joystick_enabled_matlab_node_B.dv3[2] = -10.0;
  } else {
    joystick_enabled_matlab_node_B.dv3[2] =
      joystick_enabled_matlab_node_B.upper_force_index;
  }

  // Saturate: '<S198>/Saturation'
  if (joystick_enabled_matlab_node_B.phi > 100.0) {
    joystick_enabled_matlab_node_B.dv4[2] = 100.0;
  } else if (joystick_enabled_matlab_node_B.phi < -100.0) {
    joystick_enabled_matlab_node_B.dv4[2] = -100.0;
  } else {
    joystick_enabled_matlab_node_B.dv4[2] = joystick_enabled_matlab_node_B.phi;
  }

  // Product: '<S25>/Matrix Multiply' incorporates:
  //   Constant: '<S25>/Constant'

  std::memset(&joystick_enabled_matlab_node_B.pwms[0], 0, sizeof(real_T) << 3U);
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.dv3[joystick_enabled_matlab_node_B.i_o];
    for (joystick_enabled_matlab_node_B.b_index = 0;
         joystick_enabled_matlab_node_B.b_index < 8;
         joystick_enabled_matlab_node_B.b_index++) {
      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.b_index]
        += joystick_enabled_matlab__ConstP.Constant_Value_p
        [(joystick_enabled_matlab_node_B.i_o << 3) +
        joystick_enabled_matlab_node_B.b_index] *
        joystick_enabled_matlab_node_B.b_t;
    }
  }

  // End of Product: '<S25>/Matrix Multiply'

  // Product: '<S25>/Matrix Multiply1' incorporates:
  //   Constant: '<S25>/Constant1'

  std::memset(&joystick_enabled_matlab_node_B.dv[0], 0, sizeof(real_T) << 3U);
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.dv4[joystick_enabled_matlab_node_B.i_o];
    for (joystick_enabled_matlab_node_B.b_index = 0;
         joystick_enabled_matlab_node_B.b_index < 8;
         joystick_enabled_matlab_node_B.b_index++) {
      joystick_enabled_matlab_node_B.dv[joystick_enabled_matlab_node_B.b_index] +=
        joystick_enabled_matlab__ConstP.Constant1_Value
        [(joystick_enabled_matlab_node_B.i_o << 3) +
        joystick_enabled_matlab_node_B.b_index] *
        joystick_enabled_matlab_node_B.b_t;
    }
  }

  // End of Product: '<S25>/Matrix Multiply1'

  // MATLAB Function: '<S25>/thrusterAllocator'
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 8;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
      = joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.i_o]
      + joystick_enabled_matlab_node_B.dv[joystick_enabled_matlab_node_B.i_o];
  }

  // End of MATLAB Function: '<S25>/thrusterAllocator'

  // MATLAB Function: '<S25>/trickFTListInjector'
  if (joystick_enabled_matlab_node_B.OR1) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o] =
        joystick_enabled_matlab_node_B.cmd.trick_id[joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.i_o = std::memcmp(&a_3[0],
      &joystick_enabled_matlab_node_B.s[0], 16);
    if (joystick_enabled_matlab_node_B.i_o == 0) {
      joystick_enabled_matlab_node_B.b_index = 0;
    } else {
      joystick_enabled_matlab_node_B.i_o = std::memcmp(&b_a_2[0],
        &joystick_enabled_matlab_node_B.s[0], 16);
      if (joystick_enabled_matlab_node_B.i_o == 0) {
        joystick_enabled_matlab_node_B.b_index = 1;
      } else {
        joystick_enabled_matlab_node_B.i_o = std::memcmp(&c_a_2[0],
          &joystick_enabled_matlab_node_B.s[0], 16);
        if (joystick_enabled_matlab_node_B.i_o == 0) {
          joystick_enabled_matlab_node_B.b_index = 2;
        } else {
          joystick_enabled_matlab_node_B.i_o = std::memcmp(&d_a_1[0],
            &joystick_enabled_matlab_node_B.s[0], 16);
          if (joystick_enabled_matlab_node_B.i_o == 0) {
            joystick_enabled_matlab_node_B.b_index = 3;
          } else {
            joystick_enabled_matlab_node_B.i_o = std::memcmp(&e_a_0[0],
              &joystick_enabled_matlab_node_B.s[0], 16);
            if (joystick_enabled_matlab_node_B.i_o == 0) {
              joystick_enabled_matlab_node_B.b_index = 4;
            } else {
              joystick_enabled_matlab_node_B.i_o = std::memcmp(&f_a_0[0],
                &joystick_enabled_matlab_node_B.s[0], 16);
              if (joystick_enabled_matlab_node_B.i_o == 0) {
                joystick_enabled_matlab_node_B.b_index = 5;
              } else {
                joystick_enabled_matlab_node_B.i_o = std::memcmp(&g_a_0[0],
                  &joystick_enabled_matlab_node_B.s[0], 16);
                if (joystick_enabled_matlab_node_B.i_o == 0) {
                  joystick_enabled_matlab_node_B.b_index = 6;
                } else {
                  joystick_enabled_matlab_node_B.i_o = std::memcmp(&h_a_0[0],
                    &joystick_enabled_matlab_node_B.s[0], 16);
                  if (joystick_enabled_matlab_node_B.i_o == 0) {
                    joystick_enabled_matlab_node_B.b_index = 7;
                  } else {
                    joystick_enabled_matlab_node_B.i_o = std::memcmp(&i_a_0[0],
                      &joystick_enabled_matlab_node_B.s[0], 16);
                    if (joystick_enabled_matlab_node_B.i_o == 0) {
                      joystick_enabled_matlab_node_B.b_index = 8;
                    } else {
                      joystick_enabled_matlab_node_B.i_o = std::memcmp(&j_a_0[0],
                        &joystick_enabled_matlab_node_B.s[0], 16);
                      if (joystick_enabled_matlab_node_B.i_o == 0) {
                        joystick_enabled_matlab_node_B.b_index = 9;
                      } else {
                        joystick_enabled_matlab_node_B.i_o = std::memcmp(&k_a[0],
                          &joystick_enabled_matlab_node_B.s[0], 16);
                        if (joystick_enabled_matlab_node_B.i_o == 0) {
                          joystick_enabled_matlab_node_B.b_index = 10;
                        } else {
                          joystick_enabled_matlab_node_B.i_o = std::memcmp(&l_a
                            [0], &joystick_enabled_matlab_node_B.s[0], 16);
                          if (joystick_enabled_matlab_node_B.i_o == 0) {
                            joystick_enabled_matlab_node_B.b_index = 11;
                          } else {
                            joystick_enabled_matlab_node_B.i_o = std::memcmp
                              (&m_a[0], &joystick_enabled_matlab_node_B.s[0], 16);
                            if (joystick_enabled_matlab_node_B.i_o == 0) {
                              joystick_enabled_matlab_node_B.b_index = 12;
                            } else {
                              joystick_enabled_matlab_node_B.b_index = -1;
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

    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 8;
         joystick_enabled_matlab_node_B.i_o++) {
      switch (joystick_enabled_matlab_node_B.b_index) {
       case 0:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.forward
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 1:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.backward
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 2:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.up[joystick_enabled_matlab_node_B.i_o];
        break;

       case 3:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.down[joystick_enabled_matlab_node_B.i_o];
        break;

       case 4:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.left[joystick_enabled_matlab_node_B.i_o];
        break;

       case 5:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.right[joystick_enabled_matlab_node_B.i_o];
        break;

       case 6:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.pitchUp
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 7:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.pitchDown
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 8:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.yawRight
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 9:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.yawLeft
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 10:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.rollRight
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 11:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab__ConstP.trickFTListInjector_FF_maneuver.rollLeft
          [joystick_enabled_matlab_node_B.i_o];
        break;

       case 12:
        joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.i_o]
          = 0.0;
        break;
      }
    }
  }

  // MATLAB Function: '<S32>/forceToPWMCalculator' incorporates:
  //   Constant: '<S25>/Constant3'

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 8;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.i_o] =
      1500.0;
  }

  for (joystick_enabled_matlab_node_B.pos = 0;
       joystick_enabled_matlab_node_B.pos < 4;
       joystick_enabled_matlab_node_B.pos++) {
    joystick_enabled_matlab_node_B.b_index = joystick_enabled_matlab_node_B.pos <<
      1;
    joystick_enabled_matlab_node_B.alpha =
      joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index];
    if (std::abs(joystick_enabled_matlab_node_B.alpha) < 0.001) {
      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.b_index]
        = 1500.0;
    } else {
      for (joystick_enabled_matlab_node_B.d_k = 0;
           joystick_enabled_matlab_node_B.d_k < 6;
           joystick_enabled_matlab_node_B.d_k++) {
        joystick_enabled_matlab_node_B.varargin_1_f[joystick_enabled_matlab_node_B.d_k]
          = std::abs
          (joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[joystick_enabled_matlab_node_B.d_k]
           - 15.0);
      }

      joystick_enabled_matlab_minimum
        (joystick_enabled_matlab_node_B.varargin_1_f,
         &joystick_enabled_matlab_node_B.upper_force_index,
         &joystick_enabled_matlab_node_B.i_o);
      switch (joystick_enabled_matlab_node_B.i_o) {
       case 1:
        joystick_enabled_matlab_node_B.lower_voltage_index = 1.0;
        joystick_enabled_matlab_node_B.upper_voltage_index = 1.0;
        break;

       case 6:
        joystick_enabled_matlab_node_B.lower_voltage_index = 6.0;
        joystick_enabled_matlab_node_B.upper_voltage_index = 6.0;
        break;

       default:
        if (joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[joystick_enabled_matlab_node_B.i_o
            - 1] < 15.0) {
          joystick_enabled_matlab_node_B.lower_voltage_index =
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.upper_voltage_index =
            static_cast<real_T>(joystick_enabled_matlab_node_B.i_o) + 1.0;
        } else {
          joystick_enabled_matlab_node_B.upper_voltage_index =
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.lower_voltage_index = static_cast<
            real_T>(joystick_enabled_matlab_node_B.i_o) - 1.0;
        }
        break;
      }

      if (joystick_enabled_matlab_node_B.upper_voltage_index ==
          joystick_enabled_matlab_node_B.lower_voltage_index) {
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 1;
        joystick_enabled_matlab_node_B.force_column_data[0] =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>
                  (joystick_enabled_matlab_node_B.upper_voltage_index) - 1] -
                  joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[
                  static_cast<int32_T>
                  (joystick_enabled_matlab_node_B.lower_voltage_index) - 1]) <
                 0.001) {
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 1;
        joystick_enabled_matlab_node_B.force_column_data[0] =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
      } else {
        joystick_enabled_matlab_node_B.upper_force_index = 15.0 -
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
        joystick_enabled_matlab_node_B.b_t =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.upper_voltage_index) - 1] -
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 201;
        for (joystick_enabled_matlab_node_B.i_o = 0;
             joystick_enabled_matlab_node_B.i_o < 201;
             joystick_enabled_matlab_node_B.i_o++) {
          joystick_enabled_matlab_node_B.d_k = (static_cast<int32_T>
            (joystick_enabled_matlab_node_B.lower_voltage_index) - 1) * 201 +
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o]
            = (joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[(
                static_cast<int32_T>
                (joystick_enabled_matlab_node_B.upper_voltage_index) - 1) * 201
               + joystick_enabled_matlab_node_B.i_o] -
               joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[joystick_enabled_matlab_node_B.d_k])
            * joystick_enabled_matlab_node_B.upper_force_index /
            joystick_enabled_matlab_node_B.b_t +
            joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_force[joystick_enabled_matlab_node_B.d_k];
        }
      }

      joystick_enabled_matlab_node_B.b_varargin_1_size =
        joystick_enabled_matlab_node_B.force_column_size_idx_0;
      for (joystick_enabled_matlab_node_B.i_o = 0;
           joystick_enabled_matlab_node_B.i_o <
           joystick_enabled_matlab_node_B.force_column_size_idx_0;
           joystick_enabled_matlab_node_B.i_o++) {
        joystick_enabled_matlab_node_B.b_x_data[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o]
          - joystick_enabled_matlab_node_B.alpha;
        joystick_enabled_matlab_node_B.b_varargin_1_data[joystick_enabled_matlab_node_B.i_o]
          = std::abs
          (joystick_enabled_matlab_node_B.b_x_data[joystick_enabled_matlab_node_B.i_o]);
      }

      joystick_enabled_matl_minimum_i
        (joystick_enabled_matlab_node_B.b_varargin_1_data,
         &joystick_enabled_matlab_node_B.b_varargin_1_size,
         &joystick_enabled_matlab_node_B.upper_force_index,
         &joystick_enabled_matlab_node_B.i_o);
      if ((joystick_enabled_matlab_node_B.i_o == 1) ||
          (joystick_enabled_matlab_node_B.i_o == 2)) {
        joystick_enabled_matlab_node_B.b_t = 1.0;
        joystick_enabled_matlab_node_B.upper_force_index = 1.0;
      } else if ((joystick_enabled_matlab_node_B.i_o == 8) ||
                 (joystick_enabled_matlab_node_B.i_o == 7)) {
        joystick_enabled_matlab_node_B.b_t = 8.0;
        joystick_enabled_matlab_node_B.upper_force_index = 8.0;
      } else if
          (joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o
           - 1] <
           joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index])
      {
        joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.i_o;
        joystick_enabled_matlab_node_B.upper_force_index = static_cast<real_T>
          (joystick_enabled_matlab_node_B.i_o) + 1.0;
      } else {
        joystick_enabled_matlab_node_B.upper_force_index =
          joystick_enabled_matlab_node_B.i_o;
        joystick_enabled_matlab_node_B.b_t = static_cast<real_T>
          (joystick_enabled_matlab_node_B.i_o) - 1.0;
      }

      if (joystick_enabled_matlab_node_B.upper_force_index >
          joystick_enabled_matlab_node_B.force_column_size_idx_0) {
        joystick_enabled_matlab_node_B.upper_force_index =
          joystick_enabled_matlab_node_B.force_column_size_idx_0;
      }

      if ((static_cast<int32_T>(joystick_enabled_matlab_node_B.upper_force_index)
           == joystick_enabled_matlab_node_B.force_column_size_idx_0) && (
           static_cast<real_T>
           (joystick_enabled_matlab_node_B.force_column_size_idx_0) - 1.0 ==
           joystick_enabled_matlab_node_B.b_t)) {
        joystick_enabled_matlab_node_B.b_t =
          joystick_enabled_matlab_node_B.upper_force_index;
      } else if ((joystick_enabled_matlab_node_B.upper_force_index == 2.0) &&
                 (joystick_enabled_matlab_node_B.b_t == 1.0)) {
        joystick_enabled_matlab_node_B.upper_force_index = 1.0;
      }

      if (joystick_enabled_matlab_node_B.b_t ==
          joystick_enabled_matlab_node_B.upper_force_index) {
        joystick_enabled_matlab_node_B.alpha = 0.0;
      } else if (std::abs(joystick_enabled_matlab_node_B.force_column_data[
                          static_cast<int32_T>
                          (joystick_enabled_matlab_node_B.upper_force_index) - 1]
                          - joystick_enabled_matlab_node_B.force_column_data[
                          static_cast<int32_T>
                          (joystick_enabled_matlab_node_B.b_t) - 1]) < 0.001) {
        joystick_enabled_matlab_node_B.alpha = 0.0;
      } else {
        joystick_enabled_matlab_node_B.alpha =
          (joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index]
           - joystick_enabled_matlab_node_B.force_column_data
           [static_cast<int32_T>
           (joystick_enabled_matlab_node_B.upper_force_index) - 1]) /
          (joystick_enabled_matlab_node_B.force_column_data[static_cast<int32_T>
           (joystick_enabled_matlab_node_B.upper_force_index) - 1] -
           joystick_enabled_matlab_node_B.force_column_data[static_cast<int32_T>
           (joystick_enabled_matlab_node_B.b_t) - 1]);
      }

      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.b_index]
        = std::round
        ((joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_pwm[
          static_cast<int32_T>(joystick_enabled_matlab_node_B.upper_force_index)
          - 1] - joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_pwm[
          static_cast<int32_T>(joystick_enabled_matlab_node_B.b_t) - 1]) *
         joystick_enabled_matlab_node_B.alpha +
         joystick_enabled_matlab__ConstP.forceToPWMCalculator_cw_pwm[
         static_cast<int32_T>(joystick_enabled_matlab_node_B.b_t) - 1]);
    }
  }

  for (joystick_enabled_matlab_node_B.pos = 0;
       joystick_enabled_matlab_node_B.pos < 4;
       joystick_enabled_matlab_node_B.pos++) {
    joystick_enabled_matlab_node_B.b_index = (joystick_enabled_matlab_node_B.pos
      << 1) + 1;
    joystick_enabled_matlab_node_B.alpha =
      joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index];
    if (std::abs(joystick_enabled_matlab_node_B.alpha) < 0.001) {
      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.b_index]
        = 1500.0;
    } else {
      for (joystick_enabled_matlab_node_B.i_o = 0;
           joystick_enabled_matlab_node_B.i_o < 6;
           joystick_enabled_matlab_node_B.i_o++) {
        joystick_enabled_matlab_node_B.varargin_1_f[joystick_enabled_matlab_node_B.i_o]
          = std::abs
          (joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[joystick_enabled_matlab_node_B.i_o]
           - 15.0);
      }

      joystick_enabled_matlab_minimum
        (joystick_enabled_matlab_node_B.varargin_1_f,
         &joystick_enabled_matlab_node_B.upper_force_index,
         &joystick_enabled_matlab_node_B.i_o);
      switch (joystick_enabled_matlab_node_B.i_o) {
       case 1:
        joystick_enabled_matlab_node_B.lower_voltage_index = 1.0;
        joystick_enabled_matlab_node_B.upper_voltage_index = 1.0;
        break;

       case 6:
        joystick_enabled_matlab_node_B.lower_voltage_index = 6.0;
        joystick_enabled_matlab_node_B.upper_voltage_index = 6.0;
        break;

       default:
        if (joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[joystick_enabled_matlab_node_B.i_o
            - 1] < 15.0) {
          joystick_enabled_matlab_node_B.lower_voltage_index =
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.upper_voltage_index =
            static_cast<real_T>(joystick_enabled_matlab_node_B.i_o) + 1.0;
        } else {
          joystick_enabled_matlab_node_B.upper_voltage_index =
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.lower_voltage_index = static_cast<
            real_T>(joystick_enabled_matlab_node_B.i_o) - 1.0;
        }
        break;
      }

      if (joystick_enabled_matlab_node_B.upper_voltage_index ==
          joystick_enabled_matlab_node_B.lower_voltage_index) {
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 1;
        joystick_enabled_matlab_node_B.force_column_data[0] =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
      } else if (std::abs
                 (joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>
                  (joystick_enabled_matlab_node_B.upper_voltage_index) - 1] -
                  joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[
                  static_cast<int32_T>
                  (joystick_enabled_matlab_node_B.lower_voltage_index) - 1]) <
                 0.001) {
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 1;
        joystick_enabled_matlab_node_B.force_column_data[0] =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
      } else {
        joystick_enabled_matlab_node_B.b_a_l = 15.0 -
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
        joystick_enabled_matlab_node_B.b_t =
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.upper_voltage_index) - 1] -
          joystick_enabled_matlab__ConstP.forceToPWMCalculator_voltage[
          static_cast<int32_T>
          (joystick_enabled_matlab_node_B.lower_voltage_index) - 1];
        joystick_enabled_matlab_node_B.force_column_size_idx_0 = 201;
        for (joystick_enabled_matlab_node_B.i_o = 0;
             joystick_enabled_matlab_node_B.i_o < 201;
             joystick_enabled_matlab_node_B.i_o++) {
          joystick_enabled_matlab_node_B.d_k = (static_cast<int32_T>
            (joystick_enabled_matlab_node_B.lower_voltage_index) - 1) * 201 +
            joystick_enabled_matlab_node_B.i_o;
          joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o]
            = (joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[(
                static_cast<int32_T>
                (joystick_enabled_matlab_node_B.upper_voltage_index) - 1) * 201
               + joystick_enabled_matlab_node_B.i_o] -
               joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[joystick_enabled_matlab_node_B.d_k])
            * joystick_enabled_matlab_node_B.b_a_l /
            joystick_enabled_matlab_node_B.b_t +
            joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_force[joystick_enabled_matlab_node_B.d_k];
        }
      }

      joystick_enabled_matlab_node_B.b_varargin_1_size =
        joystick_enabled_matlab_node_B.force_column_size_idx_0;
      for (joystick_enabled_matlab_node_B.i_o = 0;
           joystick_enabled_matlab_node_B.i_o <
           joystick_enabled_matlab_node_B.force_column_size_idx_0;
           joystick_enabled_matlab_node_B.i_o++) {
        joystick_enabled_matlab_node_B.b_x_data[joystick_enabled_matlab_node_B.i_o]
          =
          joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o]
          - joystick_enabled_matlab_node_B.alpha;
        joystick_enabled_matlab_node_B.b_varargin_1_data[joystick_enabled_matlab_node_B.i_o]
          = std::abs
          (joystick_enabled_matlab_node_B.b_x_data[joystick_enabled_matlab_node_B.i_o]);
      }

      joystick_enabled_matl_minimum_i
        (joystick_enabled_matlab_node_B.b_varargin_1_data,
         &joystick_enabled_matlab_node_B.b_varargin_1_size,
         &joystick_enabled_matlab_node_B.upper_force_index,
         &joystick_enabled_matlab_node_B.i_o);
      if ((joystick_enabled_matlab_node_B.i_o == 1) ||
          (joystick_enabled_matlab_node_B.i_o == 2)) {
        joystick_enabled_matlab_node_B.b_t = 1.0;
        joystick_enabled_matlab_node_B.upper_force_index = 1.0;
      } else if ((joystick_enabled_matlab_node_B.i_o == 8) ||
                 (joystick_enabled_matlab_node_B.i_o == 7)) {
        joystick_enabled_matlab_node_B.b_t = 8.0;
        joystick_enabled_matlab_node_B.upper_force_index = 8.0;
      } else if
          (joystick_enabled_matlab_node_B.force_column_data[joystick_enabled_matlab_node_B.i_o
           - 1] <
           joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index])
      {
        joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.i_o;
        joystick_enabled_matlab_node_B.upper_force_index = static_cast<real_T>
          (joystick_enabled_matlab_node_B.i_o) + 1.0;
      } else {
        joystick_enabled_matlab_node_B.upper_force_index =
          joystick_enabled_matlab_node_B.i_o;
        joystick_enabled_matlab_node_B.b_t = static_cast<real_T>
          (joystick_enabled_matlab_node_B.i_o) - 1.0;
      }

      if (joystick_enabled_matlab_node_B.upper_force_index >
          joystick_enabled_matlab_node_B.force_column_size_idx_0) {
        joystick_enabled_matlab_node_B.upper_force_index =
          joystick_enabled_matlab_node_B.force_column_size_idx_0;
      }

      if (joystick_enabled_matlab_node_B.b_t ==
          joystick_enabled_matlab_node_B.upper_force_index) {
        joystick_enabled_matlab_node_B.alpha = 0.0;
      } else if (std::abs(joystick_enabled_matlab_node_B.force_column_data[
                          static_cast<int32_T>
                          (joystick_enabled_matlab_node_B.upper_force_index) - 1]
                          - joystick_enabled_matlab_node_B.force_column_data[
                          static_cast<int32_T>
                          (joystick_enabled_matlab_node_B.b_t) - 1]) < 0.001) {
        joystick_enabled_matlab_node_B.alpha = 0.0;
      } else {
        joystick_enabled_matlab_node_B.alpha =
          (joystick_enabled_matlab_node_B.FT_cmd_list[joystick_enabled_matlab_node_B.b_index]
           - joystick_enabled_matlab_node_B.force_column_data
           [static_cast<int32_T>
           (joystick_enabled_matlab_node_B.upper_force_index) - 1]) /
          (joystick_enabled_matlab_node_B.force_column_data[static_cast<int32_T>
           (joystick_enabled_matlab_node_B.upper_force_index) - 1] -
           joystick_enabled_matlab_node_B.force_column_data[static_cast<int32_T>
           (joystick_enabled_matlab_node_B.b_t) - 1]);
      }

      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.b_index]
        = std::round
        ((joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_pwm[
          static_cast<int32_T>(joystick_enabled_matlab_node_B.upper_force_index)
          - 1] - joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_pwm[
          static_cast<int32_T>(joystick_enabled_matlab_node_B.b_t) - 1]) *
         joystick_enabled_matlab_node_B.alpha +
         joystick_enabled_matlab__ConstP.forceToPWMCalculator_ccw_pwm[
         static_cast<int32_T>(joystick_enabled_matlab_node_B.b_t) - 1]);
    }
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 8;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.i_o] =
      std::fmax(1100.0, std::fmin(1900.0,
      joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.i_o]));
  }

  // DeadZone: '<S128>/DeadZone'
  if (joystick_enabled_matlab_node_B.Rb_u[0] > 1.0) {
    joystick_enabled_matlab_node_B.b_a_l = joystick_enabled_matlab_node_B.Rb_u[0]
      - 1.0;

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant'

    tmp = 1;
  } else {
    if (joystick_enabled_matlab_node_B.Rb_u[0] >= -1.0) {
      joystick_enabled_matlab_node_B.b_a_l = 0.0;
    } else {
      joystick_enabled_matlab_node_B.b_a_l =
        joystick_enabled_matlab_node_B.Rb_u[0] - -1.0;
    }

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant2'

    tmp = -1;
  }

  // Switch: '<S126>/Switch' incorporates:
  //   Constant: '<S126>/Clamping_zero'
  //   Constant: '<S126>/Constant1'
  //   DeadZone: '<S128>/DeadZone'
  //   Gain: '<S133>/Integral Gain'
  //   Logic: '<S126>/AND3'
  //   RelationalOperator: '<S126>/Equal1'
  //   RelationalOperator: '<S126>/Relational Operator'
  //   Switch: '<S126>/Switch1'
  //   Switch: '<S126>/Switch2'

  if ((joystick_enabled_matlab_node_B.b_a_l != 0.0) && (tmp == -1)) {
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Rb_u_b = 0.0 *
      joystick_enabled_matlab_node_B.eps_n[0];
  }

  // DeadZone: '<S183>/DeadZone'
  if (joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 > 100.0) {
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 -= 100.0;
  } else if (joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 >= -100.0) {
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 -= -100.0;
  }

  // Gain: '<S188>/Integral Gain'
  joystick_enabled_matlab_node_B.eps_n[0] = 20.0 *
    joystick_enabled_matlab_node_B.dRb_e[0];

  // DeadZone: '<S128>/DeadZone'
  if (joystick_enabled_matlab_node_B.Rb_u[1] > 1.0) {
    joystick_enabled_matlab_node_B.b_a_l = joystick_enabled_matlab_node_B.Rb_u[1]
      - 1.0;

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant'

    tmp = 1;
  } else {
    if (joystick_enabled_matlab_node_B.Rb_u[1] >= -1.0) {
      joystick_enabled_matlab_node_B.b_a_l = 0.0;
    } else {
      joystick_enabled_matlab_node_B.b_a_l =
        joystick_enabled_matlab_node_B.Rb_u[1] - -1.0;
    }

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant2'

    tmp = -1;
  }

  // Switch: '<S126>/Switch' incorporates:
  //   Constant: '<S126>/Clamping_zero'
  //   Constant: '<S126>/Constant1'
  //   DeadZone: '<S128>/DeadZone'
  //   Gain: '<S133>/Integral Gain'
  //   Logic: '<S126>/AND3'
  //   RelationalOperator: '<S126>/Equal1'
  //   RelationalOperator: '<S126>/Relational Operator'
  //   Switch: '<S126>/Switch1'
  //   Switch: '<S126>/Switch2'

  if ((joystick_enabled_matlab_node_B.b_a_l != 0.0) && (tmp == -1)) {
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Rb_u_j = 0.0 *
      joystick_enabled_matlab_node_B.eps_n[1];
  }

  // DeadZone: '<S183>/DeadZone'
  if (joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 > 100.0) {
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 -= 100.0;
  } else if (joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 >= -100.0) {
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 = 0.0;
  } else {
    joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 -= -100.0;
  }

  // Gain: '<S188>/Integral Gain'
  joystick_enabled_matlab_node_B.eps_n[1] = 20.0 *
    joystick_enabled_matlab_node_B.dRb_e[1];

  // DeadZone: '<S128>/DeadZone'
  if (joystick_enabled_matlab_node_B.Rb_u[2] > 1.0) {
    joystick_enabled_matlab_node_B.b_a_l = joystick_enabled_matlab_node_B.Rb_u[2]
      - 1.0;

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant'

    tmp = 1;
  } else {
    if (joystick_enabled_matlab_node_B.Rb_u[2] >= -1.0) {
      joystick_enabled_matlab_node_B.b_a_l = 0.0;
    } else {
      joystick_enabled_matlab_node_B.b_a_l =
        joystick_enabled_matlab_node_B.Rb_u[2] - -1.0;
    }

    // Switch: '<S126>/Switch1' incorporates:
    //   Constant: '<S126>/Constant2'

    tmp = -1;
  }

  // Switch: '<S126>/Switch' incorporates:
  //   Constant: '<S126>/Clamping_zero'
  //   Constant: '<S126>/Constant1'
  //   DeadZone: '<S128>/DeadZone'
  //   Gain: '<S133>/Integral Gain'
  //   Logic: '<S126>/AND3'
  //   RelationalOperator: '<S126>/Equal1'
  //   RelationalOperator: '<S126>/Relational Operator'
  //   Switch: '<S126>/Switch1'
  //   Switch: '<S126>/Switch2'

  if ((joystick_enabled_matlab_node_B.b_a_l != 0.0) && (tmp == -1)) {
    joystick_enabled_matlab_node_B.b_a_l = 0.0;
  } else {
    joystick_enabled_matlab_node_B.b_a_l = 0.0 *
      joystick_enabled_matlab_node_B.eps_n[2];
  }

  // DeadZone: '<S183>/DeadZone' incorporates:
  //   Sum: '<S200>/Sum'

  if (joystick_enabled_matlab_node_B.phi > 100.0) {
    joystick_enabled_matlab_node_B.upper_force_index =
      joystick_enabled_matlab_node_B.phi - 100.0;
  } else if (joystick_enabled_matlab_node_B.phi >= -100.0) {
    joystick_enabled_matlab_node_B.upper_force_index = 0.0;
  } else {
    joystick_enabled_matlab_node_B.upper_force_index =
      joystick_enabled_matlab_node_B.phi - -100.0;
  }

  // Gain: '<S188>/Integral Gain'
  joystick_enabled_matlab_node_B.eps_f = 20.0 *
    joystick_enabled_matlab_node_B.dRb_e[2];

  // MATLAB Function: '<S25>/quatToEul'
  joystick_enabled__quatToEul(joystick_enabled_matlab_node_B.qib_int_u,
    joystick_enabled_matlab_node_B.dRb_e,
    &joystick_enabled_matlab_node_B.sf_quatToEul);

  // MATLAB Function: '<S25>/quatToEul1'
  joystick_enabled__quatToEul(joystick_enabled_matlab_node_B.qe_matlab,
    joystick_enabled_matlab_node_B.dRb_e,
    &joystick_enabled_matlab_node_B.sf_quatToEul1);

  // MATLAB Function: '<S26>/quatToEul'
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 3;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.theta_h =
      joystick_enabled_matlab_node_B.X_u[joystick_enabled_matlab_node_B.i_o + 3]
      * 2.0;
    joystick_enabled_matlab_node_B.Cbi[3 * joystick_enabled_matlab_node_B.i_o] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[3] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[3 *
       joystick_enabled_matlab_node_B.i_o]) +
      joystick_enabled_matlab_node_B.rtb_Cbi_tmp[3 *
      joystick_enabled_matlab_node_B.i_o];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 1;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[4] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.b_index])
      + joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index];
    joystick_enabled_matlab_node_B.b_index = 3 *
      joystick_enabled_matlab_node_B.i_o + 2;
    joystick_enabled_matlab_node_B.Cbi[joystick_enabled_matlab_node_B.b_index] =
      (joystick_enabled_matlab_node_B.theta_h *
       joystick_enabled_matlab_node_B.X_u[5] +
       joystick_enabled_matlab_node_B.qk_plus_1_tmp[joystick_enabled_matlab_node_B.b_index])
      + joystick_enabled_matlab_node_B.rtb_Cbi_tmp[joystick_enabled_matlab_node_B.b_index];
  }

  joystick_enabled_matlab_node_B.theta_h = std::asin(std::fmax(-1.0, std::fmin
    (1.0, joystick_enabled_matlab_node_B.Cbi[6])));
  if (std::abs(std::cos(-joystick_enabled_matlab_node_B.theta_h)) < 1.0E-6) {
    joystick_enabled_matlab_node_B.phi = 0.0;
    joystick_enabled_matlab_node_B.b_t = joystick_enabled__rt_atan2d_snf
      (-joystick_enabled_matlab_node_B.Cbi[1],
       joystick_enabled_matlab_node_B.Cbi[4]);
  } else {
    joystick_enabled_matlab_node_B.phi = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[7],
       joystick_enabled_matlab_node_B.Cbi[8]);
    joystick_enabled_matlab_node_B.b_t = joystick_enabled__rt_atan2d_snf
      (joystick_enabled_matlab_node_B.Cbi[3],
       joystick_enabled_matlab_node_B.Cbi[0]);
  }

  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.phi);
  joystick_enabled_matlab_node_B.theta_h =
    -joystick_enabled_matlab_node_B.theta_h;
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.theta_h);
  joystick_enabled_mat_wrapToPi_k(&joystick_enabled_matlab_node_B.b_t);

  // MATLAB Function: '<S12>/joystick_inputs_to_body_forces' incorporates:
  //   MATLAB Function: '<S11>/MATLAB Function'

  joystick_enabled_matlab_node_B.b_t = ((300.0F *
    joystick_enabled_matlab_node_B.In1_f.rise - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.sink) + 1500.0F) - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.pitch;
  joystick_enabled_matlab_node_B.phi = (-(300.0F *
    joystick_enabled_matlab_node_B.In1_f.rise - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.sink) + 1500.0F) - (-(300.0F *
    joystick_enabled_matlab_node_B.In1_f.pitch));
  joystick_enabled_matlab_node_B.alpha = ((300.0F *
    joystick_enabled_matlab_node_B.In1_f.rise - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.sink) + 1500.0F) + 300.0F *
    joystick_enabled_matlab_node_B.In1_f.pitch;
  joystick_enabled_matlab_node_B.upper_voltage_index = (-(300.0F *
    joystick_enabled_matlab_node_B.In1_f.rise - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.sink) + 1500.0F) - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.pitch;
  joystick_enabled_matlab_node_B.lower_voltage_index = ((300.0F *
    joystick_enabled_matlab_node_B.In1_f.y + 1500.0F) +
    joystick_enabled_matlab_node_B.In1_f.x * 300.0F) +
    joystick_enabled_matlab_node_B.In1_f.yaw * 300.0F;
  joystick_enabled_matlab_node_B.pwms_horiz_idx_1 = ((1500.0F - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.y) +
    joystick_enabled_matlab_node_B.In1_f.x * 300.0F) +
    joystick_enabled_matlab_node_B.In1_f.yaw * 300.0F;
  joystick_enabled_matlab_node_B.pwms_horiz_idx_2 = ((300.0F *
    joystick_enabled_matlab_node_B.In1_f.y + 1500.0F) -
    joystick_enabled_matlab_node_B.In1_f.x * 300.0F) +
    joystick_enabled_matlab_node_B.In1_f.yaw * 300.0F;
  joystick_enabled_matlab_node_B.pwms_horiz_idx_3 = ((1500.0F - 300.0F *
    joystick_enabled_matlab_node_B.In1_f.y) -
    joystick_enabled_matlab_node_B.In1_f.x * 300.0F) +
    joystick_enabled_matlab_node_B.In1_f.yaw * 300.0F;
  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.lower_voltage_index;
  if (joystick_enabled_matlab_node_B.lower_voltage_index > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.lower_voltage_index = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.lower_voltage_index = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.b_t;
  if (joystick_enabled_matlab_node_B.b_t > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.b_t = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.lower_voltage_index = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1;
  if (joystick_enabled_matlab_node_B.pwms_horiz_idx_1 > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1 = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1 = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.phi;
  if (joystick_enabled_matlab_node_B.phi > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.phi = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_1 = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_2;
  if (joystick_enabled_matlab_node_B.pwms_horiz_idx_2 > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.pwms_horiz_idx_2 = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_2 = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.alpha;
  if (joystick_enabled_matlab_node_B.alpha > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.alpha = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_2 = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.pwms_horiz_idx_3;
  if (joystick_enabled_matlab_node_B.pwms_horiz_idx_3 > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.pwms_horiz_idx_3 = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_3 = 1200.0;
  }

  joystick_enabled_matlab_node_B.rtb_X_est_idx_2 =
    joystick_enabled_matlab_node_B.upper_voltage_index;
  if (joystick_enabled_matlab_node_B.upper_voltage_index > 1800.0) {
    joystick_enabled_matlab_node_B.rtb_X_est_idx_2 = 1800.0;
    joystick_enabled_matlab_node_B.upper_voltage_index = 1800.0;
  }

  if (joystick_enabled_matlab_node_B.rtb_X_est_idx_2 < 1200.0) {
    joystick_enabled_matlab_node_B.pwms_horiz_idx_3 = 1200.0;
  }

  // Switch: '<Root>/Switch' incorporates:
  //   MATLAB Function: '<Root>/joystick_mode_manager'

  if (joystick_enabled_matlab_node_DW.joystick_flag) {
    // MATLAB Function: '<S12>/joystick_inputs_to_body_forces'
    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.b_t);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[0] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[0] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[0] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.lower_voltage_index);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[4] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[4] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[4] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.phi);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[1] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[1] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[1] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.pwms_horiz_idx_1);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[5] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[5] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[5] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.alpha);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[2] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[2] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[2] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.pwms_horiz_idx_2);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[6] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[6] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[6] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.upper_voltage_index);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[3] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[3] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[3] = MAX_int32_T;
    }

    joystick_enabled_matlab_node_B.b_t = std::round
      (joystick_enabled_matlab_node_B.pwms_horiz_idx_3);
    if (joystick_enabled_matlab_node_B.b_t < 2.147483648E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= -2.147483648E+9) {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[7] = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        // BusCreator: '<S14>/Bus Creator3'
        joystick_enabled_matlab_node_B.BusCreator3.pwms[7] = MIN_int32_T;
      }
    } else {
      // BusCreator: '<S14>/Bus Creator3'
      joystick_enabled_matlab_node_B.BusCreator3.pwms[7] = MAX_int32_T;
    }
  } else {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 8;
         joystick_enabled_matlab_node_B.i_o++) {
      // DataTypeConversion: '<S25>/Cast' incorporates:
      //   MATLAB Function: '<S32>/forceToPWMCalculator'
      //   Switch: '<S4>/Switch'

      joystick_enabled_matlab_node_B.b_t =
        joystick_enabled_matlab_node_B.pwms[joystick_enabled_matlab_node_B.i_o];
      if (std::isnan(joystick_enabled_matlab_node_B.b_t) || std::isinf
          (joystick_enabled_matlab_node_B.b_t)) {
        joystick_enabled_matlab_node_B.b_t = 0.0;
      } else {
        joystick_enabled_matlab_node_B.b_t = std::fmod
          (joystick_enabled_matlab_node_B.b_t, 4.294967296E+9);
      }

      // BusCreator: '<S14>/Bus Creator3' incorporates:
      //   DataTypeConversion: '<S25>/Cast'
      //   MATLAB Function: '<S32>/forceToPWMCalculator'
      //   Switch: '<Root>/Switch'
      //   Switch: '<S4>/Switch'

      joystick_enabled_matlab_node_B.BusCreator3.pwms[joystick_enabled_matlab_node_B.i_o]
        = joystick_enabled_matlab_node_B.b_t < 0.0 ? -static_cast<int32_T>(
        static_cast<uint32_T>(-joystick_enabled_matlab_node_B.b_t)) :
        static_cast<int32_T>(static_cast<uint32_T>
        (joystick_enabled_matlab_node_B.b_t));
    }
  }

  // End of Switch: '<Root>/Switch'

  // MATLABSystem: '<S229>/SinkBlock'
  Pub_joystick_enabled_matlab_node_436_2.publish
    (&joystick_enabled_matlab_node_B.BusCreator3);

  // SignalConversion generated from: '<S218>/ SFunction ' incorporates:
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
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[0] =
    joystick_enabled_matlab_node_B.X_u[0];
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[6] =
    joystick_enabled_matlab_node_B.b_scale;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[9] =
    joystick_enabled_matlab_node_B.norm_w;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[1] =
    joystick_enabled_matlab_node_B.X_u[1];
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[7] =
    joystick_enabled_matlab_node_B.b_absxk;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[10] =
    joystick_enabled_matlab_node_B.theta;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[2] =
    joystick_enabled_matlab_node_B.X_u[2];
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[8] =
    joystick_enabled_matlab_node_B.rotm_tmp;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[11] =
    joystick_enabled_matlab_node_B.t;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[12] =
    joystick_enabled_matlab_node_DW.joystick_flag;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[13] =
    joystick_enabled_matlab_node_B.reset_dvl_pos;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[14] =
    joystick_enabled_matlab_node_B.DataStoreRead_k;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[15] =
    joystick_enabled_matlab_node_B.b_varargout_1_o;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[16] =
    joystick_enabled_matlab_node_B.db6;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[17] =
    joystick_enabled_matlab_node_B.In1.altitude;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[18] =
    joystick_enabled_matlab_node_B.idx;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[19] =
    joystick_enabled_matlab_node_B.In1_g.pos_std;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[20] =
    joystick_enabled_matlab_node_B.In1.fom;
  joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[21] =
    joystick_enabled_matlab_node_DW.db11;

  // MATLAB Function: '<S7>/MATLAB Function'
  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 256;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.temp_char[joystick_enabled_matlab_node_B.i_o]
      = '_';
  }

  joystick_enabled_matlab_node_B.idx = 1.0;
  for (joystick_enabled_matlab_node_B.b_index = 0;
       joystick_enabled_matlab_node_B.b_index < 22;
       joystick_enabled_matlab_node_B.b_index++) {
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 16;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o] = ' ';
    }

    joystick_enabled_matlab_node_B.theta_h = std::abs
      (joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[joystick_enabled_matlab_node_B.b_index]);
    joystick_enabled_matlab_node_B.b_t = std::floor
      (joystick_enabled_matlab_node_B.theta_h);
    if (joystick_enabled_matlab_node_B.b_t < 4.294967296E+9) {
      joystick_enabled_matlab_node_B.temp = static_cast<uint32_T>
        (joystick_enabled_matlab_node_B.b_t);
    } else {
      joystick_enabled_matlab_node_B.temp = MAX_uint32_T;
    }

    joystick_enabled_matlab_node_B.int_part =
      joystick_enabled_matlab_node_B.temp;
    joystick_enabled_matlab_node_B.b_t = std::round
      ((joystick_enabled_matlab_node_B.theta_h - static_cast<real_T>
        (joystick_enabled_matlab_node_B.temp)) * 10000.0);
    if (joystick_enabled_matlab_node_B.b_t < 4.294967296E+9) {
      if (joystick_enabled_matlab_node_B.b_t >= 0.0) {
        joystick_enabled_matlab_node_B.frac_part = static_cast<uint32_T>
          (joystick_enabled_matlab_node_B.b_t);
      } else {
        joystick_enabled_matlab_node_B.frac_part = 0U;
      }
    } else {
      joystick_enabled_matlab_node_B.frac_part = MAX_uint32_T;
    }

    if (joystick_enabled_matlab_node_B.frac_part >= 10000U) {
      joystick_enabled_matlab_node_B.int_part =
        joystick_enabled_matlab_node_B.temp + /*MW:OvSatOk*/ 1U;
      if (joystick_enabled_matlab_node_B.temp + 1U <
          joystick_enabled_matlab_node_B.temp) {
        joystick_enabled_matlab_node_B.int_part = MAX_uint32_T;
      }

      joystick_enabled_matlab_node_B.frac_part = 0U;
    }

    joystick_enabled_matlab_node_B.temp =
      joystick_enabled_matlab_node_B.int_part;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o < 10;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.digits[9 -
        joystick_enabled_matlab_node_B.i_o] = static_cast<int8_T>
        (static_cast<int8_T>(joystick_enabled_matlab_node_B.temp -
          joystick_enabled_matlab_node_B.temp / 10U * 10U) + 48);
      joystick_enabled_matlab_node_B.temp /= 10U;
    }

    joystick_enabled_matlab_node_B.db6 = 9;
    joystick_enabled_matlab_node_B.i_o = 0;
    exitg1 = false;
    while ((!exitg1) && (joystick_enabled_matlab_node_B.i_o < 10)) {
      if (joystick_enabled_matlab_node_B.digits[joystick_enabled_matlab_node_B.i_o]
          != '0') {
        joystick_enabled_matlab_node_B.db6 = joystick_enabled_matlab_node_B.i_o;
        exitg1 = true;
      } else {
        joystick_enabled_matlab_node_B.i_o++;
      }
    }

    if (joystick_enabled_matlab_node_B.int_part == 0U) {
      joystick_enabled_matlab_node_B.db6 = 9;
    }

    joystick_enabled_matlab_node_B.pos = 1;
    if (joystick_enabled_matlab_node_B.TmpSignalConversionAtSFunct[joystick_enabled_matlab_node_B.b_index]
        < 0.0) {
      joystick_enabled_matlab_node_B.s[0] = '-';
      joystick_enabled_matlab_node_B.pos = 2;
    }

    joystick_enabled_matlab_node_B.d_k = -joystick_enabled_matlab_node_B.db6;
    for (joystick_enabled_matlab_node_B.i_o = 0;
         joystick_enabled_matlab_node_B.i_o <=
         joystick_enabled_matlab_node_B.d_k + 9;
         joystick_enabled_matlab_node_B.i_o++) {
      joystick_enabled_matlab_node_B.s[(joystick_enabled_matlab_node_B.pos +
        joystick_enabled_matlab_node_B.i_o) - 1] =
        joystick_enabled_matlab_node_B.digits[joystick_enabled_matlab_node_B.db6
        + joystick_enabled_matlab_node_B.i_o];
    }

    joystick_enabled_matlab_node_B.pos = (joystick_enabled_matlab_node_B.pos -
      joystick_enabled_matlab_node_B.db6) + 9;
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.pos] = '.';
    joystick_enabled_matlab_node_B.int_part =
      joystick_enabled_matlab_node_B.frac_part / 10U;
    joystick_enabled_matlab_node_B.fd[2] = static_cast<int8_T>
      (static_cast<int8_T>(joystick_enabled_matlab_node_B.int_part -
        joystick_enabled_matlab_node_B.int_part / 10U * 10U) + 48);
    joystick_enabled_matlab_node_B.int_part /= 10U;
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.pos + 1] =
      static_cast<int8_T>(static_cast<int32_T>
                          (joystick_enabled_matlab_node_B.int_part / 10U) + 48);
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.pos + 2] =
      static_cast<int8_T>(static_cast<int8_T>
                          (joystick_enabled_matlab_node_B.int_part -
      joystick_enabled_matlab_node_B.int_part / 10U * 10U) + 48);
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.pos + 3] =
      joystick_enabled_matlab_node_B.fd[2];
    joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.pos + 4] =
      static_cast<int8_T>(static_cast<int8_T>
                          (joystick_enabled_matlab_node_B.frac_part -
      joystick_enabled_matlab_node_B.frac_part / 10U * 10U) + 48);
    joystick_enabled_matlab_node_B.pos += 5;
    joystick_enabled_matlab_node_B.b_t = (joystick_enabled_matlab_node_B.idx +
      static_cast<real_T>(joystick_enabled_matlab_node_B.pos)) - 1.0;
    if (joystick_enabled_matlab_node_B.b_t <= 256.0) {
      if (joystick_enabled_matlab_node_B.idx >
          joystick_enabled_matlab_node_B.b_t) {
        joystick_enabled_matlab_node_B.db6 = 1;
      } else {
        joystick_enabled_matlab_node_B.db6 = static_cast<int32_T>
          (joystick_enabled_matlab_node_B.idx);
      }

      for (joystick_enabled_matlab_node_B.i_o = 0;
           joystick_enabled_matlab_node_B.i_o <
           joystick_enabled_matlab_node_B.pos;
           joystick_enabled_matlab_node_B.i_o++) {
        joystick_enabled_matlab_node_B.temp_char
          [(joystick_enabled_matlab_node_B.db6 +
            joystick_enabled_matlab_node_B.i_o) - 1] =
          joystick_enabled_matlab_node_B.s[joystick_enabled_matlab_node_B.i_o];
      }

      joystick_enabled_matlab_node_B.idx += static_cast<real_T>
        (joystick_enabled_matlab_node_B.pos);
    }

    if ((joystick_enabled_matlab_node_B.b_index + 1 < 22) &&
        (joystick_enabled_matlab_node_B.idx <= 256.0)) {
      joystick_enabled_matlab_node_B.temp_char[static_cast<int32_T>
        (joystick_enabled_matlab_node_B.idx) - 1] = ',';
      joystick_enabled_matlab_node_B.idx++;
    }
  }

  for (joystick_enabled_matlab_node_B.i_o = 0;
       joystick_enabled_matlab_node_B.i_o < 256;
       joystick_enabled_matlab_node_B.i_o++) {
    joystick_enabled_matlab_node_B.debug_msg.message[joystick_enabled_matlab_node_B.i_o]
      = static_cast<uint8_T>
      (joystick_enabled_matlab_node_B.temp_char[joystick_enabled_matlab_node_B.i_o]);
  }

  // MATLABSystem: '<S219>/SinkBlock'
  Pub_joystick_enabled_matlab_node_404_3.publish
    (&joystick_enabled_matlab_node_B.debug_msg);

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   MATLABSystem: '<S2>/SourceBlock'
  //
  joystick_enabled_matlab_node_DW.PositionIntegrator_IC_LOADING = 0U;
  if (joystick_enabled_matlab_node_B.b_varargout_1_e) {
    joystick_enabled_matlab_node_DW.PositionIntegrator_PrevResetSta = 1;
  } else {
    joystick_enabled_matlab_node_DW.PositionIntegrator_PrevResetSta = 0;
  }

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator'
  joystick_enabled_matlab_node_DW.VelocityIntegrator_IC_LOADING = 0U;

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[0] += 0.01 *
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   Sum: '<S6>/Sum'

  joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[0] += 0.01 *
    joystick_enabled_matlab_node_B.rtb_dvl_pos_l[0];

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[1] += 0.01 *
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   Sum: '<S6>/Sum'

  joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[1] += 0.01 *
    joystick_enabled_matlab_node_B.rtb_dvl_pos_l[1];

  // Update for DiscreteIntegrator: '<S6>/Position Integrator' incorporates:
  //   DiscreteIntegrator: '<S6>/Velocity Integrator'
  //   MATLAB Function: '<S6>/derivedStateEstimates'

  joystick_enabled_matlab_node_DW.PositionIntegrator_DSTATE[2] += 0.01 *
    joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2];

  // Update for DiscreteIntegrator: '<S6>/Velocity Integrator' incorporates:
  //   MATLABSystem: '<S8>/SourceBlock'
  //   Sum: '<S6>/Sum'
  //
  joystick_enabled_matlab_node_DW.VelocityIntegrator_DSTATE[2] += 0.01 *
    joystick_enabled_matlab_node_B.rtb_dvl_pos_l[2];
  if (joystick_enabled_matlab_node_B.b_varargout_1) {
    joystick_enabled_matlab_node_DW.VelocityIntegrator_PrevResetSta = 1;
  } else {
    joystick_enabled_matlab_node_DW.VelocityIntegrator_PrevResetSta = 0;
  }

  // Update for UnitDelay: '<S29>/Delay Input1' incorporates:
  //   UnitDelay: '<S4>/Unit Delay'
  //
  //  Block description for '<S29>/Delay Input1':
  //
  //   Store in Global RAM

  joystick_enabled_matlab_node_DW.DelayInput1_DSTATE =
    joystick_enabled_matlab_node_DW.UnitDelay_DSTATE;

  // Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read6'
  //   MATLAB Function: '<S25>/deltaQuatError'
  //
  if (joystick_enabled_matlab_node_B.integrator_reset > 0) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 1;
  } else {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 0;
  }

  joystick_enabled_matlab_node_B.idx = (1.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_3) * 0.01 +
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0];
  joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] =
      1.0471975511965976;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[0] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[0] =
    joystick_enabled_matlab_node_B.scale;

  // Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  joystick_enabled_matlab_node_B.idx = (0.0 - joystick_enabled_matlab_node_B.eta)
    * 0.01 + joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1];
  joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] =
      1.0471975511965976;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[1] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[1] =
    joystick_enabled_matlab_node_B.absxk;

  // Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  joystick_enabled_matlab_node_B.idx = (0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1) * 0.01 +
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2];
  joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] =
      1.0471975511965976;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[2] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[2] =
    joystick_enabled_matlab_node_B.DiscreteTransferFcn_tmp_idx_2;

  // Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
  //   MATLAB Function: '<S25>/deltaQuatError'

  joystick_enabled_matlab_node_B.idx = (0.0 -
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_2) * 0.01 +
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3];
  joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] =
      1.0471975511965976;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0471975511965976) {
    joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_DSTATE[3] =
      -1.0471975511965976;
  }

  // Update for DiscreteTransferFcn: '<S25>/Discrete Transfer Fcn'
  joystick_enabled_matlab_node_DW.DiscreteTransferFcn_states[3] =
    joystick_enabled_matlab_node_B.eps_tmp;

  // Update for DiscreteIntegrator: '<S136>/Integrator' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read1'
  //   DiscreteIntegrator: '<S131>/Filter'
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   DiscreteIntegrator: '<S76>/Filter'
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   Switch: '<S126>/Switch'
  //
  if (joystick_enabled_matlab_node_B.integrator_reset > 0) {
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState = 1;
    joystick_enabled_matlab_node_DW.Filter_PrevResetState = 1;
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState_d = 1;
    joystick_enabled_matlab_node_DW.Filter_PrevResetState_j = 1;
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState_p = 1;
  } else {
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState = 0;
    joystick_enabled_matlab_node_DW.Filter_PrevResetState = 0;
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState_d = 0;
    joystick_enabled_matlab_node_DW.Filter_PrevResetState_j = 0;
    joystick_enabled_matlab_node_DW.Integrator_PrevResetState_p = 0;
  }

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.rtb_Rb_u_b +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[0];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE[0] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[0] = 1.0;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[0] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S131>/Filter' incorporates:
  //   Gain: '<S139>/Filter Coefficient'

  joystick_enabled_matlab_node_DW.Filter_DSTATE[0] += 0.01 *
    joystick_enabled_matlab_node_B.eps_p[0];

  // Switch: '<S71>/Switch1' incorporates:
  //   Constant: '<S71>/Constant'
  //   Constant: '<S71>/Constant2'

  if (rtb_fixforDTpropagationissue_id) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S71>/Switch2' incorporates:
  //   Constant: '<S71>/Clamping_zero'
  //   Constant: '<S71>/Constant3'
  //   Constant: '<S71>/Constant4'
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   RelationalOperator: '<S71>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.Integrator_i[0] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S71>/Switch' incorporates:
  //   Constant: '<S71>/Constant1'
  //   DiscreteIntegrator: '<S81>/Integrator'
  //   Logic: '<S71>/AND3'
  //   RelationalOperator: '<S71>/Equal1'
  //   Switch: '<S71>/Switch1'
  //   Switch: '<S71>/Switch2'

  if (rtb_RelationalOperator_idx_0 && (tmp == tmp_0)) {
    joystick_enabled_matlab_node_B.b_t = 0.0;
  } else {
    joystick_enabled_matlab_node_B.b_t =
      joystick_enabled_matlab_node_B.Integrator_i[0];
  }

  // Update for DiscreteIntegrator: '<S81>/Integrator' incorporates:
  //   Switch: '<S71>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 * joystick_enabled_matlab_node_B.b_t
    + joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0] = 10.0;
  } else if (joystick_enabled_matlab_node_B.idx < -10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[0] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S76>/Filter'
  joystick_enabled_matlab_node_DW.Filter_DSTATE_n[0] += 0.01 *
    joystick_enabled_matlab_node_B.eps[0];

  // Switch: '<S181>/Switch1' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant'
  //   Constant: '<S181>/Constant2'
  //   RelationalOperator: '<S181>/fix for DT propagation issue'

  if (joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S181>/Switch2' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant3'
  //   Constant: '<S181>/Constant4'
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   RelationalOperator: '<S181>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.eps_n[0] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S181>/Switch' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant1'
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   Logic: '<S181>/AND3'
  //   RelationalOperator: '<S181>/Equal1'
  //   RelationalOperator: '<S181>/Relational Operator'
  //   Switch: '<S181>/Switch1'
  //   Switch: '<S181>/Switch2'

  if ((joystick_enabled_matlab_node_B.rtb_DeadZone_o_idx_0 != 0.0) && (tmp ==
       tmp_0)) {
    joystick_enabled_matlab_node_B.b_t = 0.0;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.eps_n[0];
  }

  // Update for DiscreteIntegrator: '<S191>/Integrator' incorporates:
  //   Switch: '<S181>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 * joystick_enabled_matlab_node_B.b_t
    + joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0] = 100.0;
  } else if (joystick_enabled_matlab_node_B.idx < -100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[0] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S186>/Filter'
  joystick_enabled_matlab_node_DW.Filter_DSTATE_g[0] += 0.01 *
    joystick_enabled_matlab_node_B.wb_u[0];

  // Update for DiscreteIntegrator: '<S136>/Integrator' incorporates:
  //   Switch: '<S126>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.rtb_Rb_u_j +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[1];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE[1] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[1] = 1.0;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[1] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S131>/Filter' incorporates:
  //   Gain: '<S139>/Filter Coefficient'

  joystick_enabled_matlab_node_DW.Filter_DSTATE[1] += 0.01 *
    joystick_enabled_matlab_node_B.eps_p[1];

  // Switch: '<S71>/Switch1' incorporates:
  //   Constant: '<S71>/Constant'
  //   Constant: '<S71>/Constant2'

  if (rtb_fixforDTpropagationissue__0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S71>/Switch2' incorporates:
  //   Constant: '<S71>/Clamping_zero'
  //   Constant: '<S71>/Constant3'
  //   Constant: '<S71>/Constant4'
  //   RelationalOperator: '<S71>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.rtb_X_est_wb > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S71>/Switch' incorporates:
  //   Constant: '<S71>/Constant1'
  //   Logic: '<S71>/AND3'
  //   RelationalOperator: '<S71>/Equal1'
  //   Switch: '<S71>/Switch1'
  //   Switch: '<S71>/Switch2'

  if (rtb_RelationalOperator_idx_1 && (tmp == tmp_0)) {
    joystick_enabled_matlab_node_B.rtb_X_est_wb = 0.0;
  }

  // Update for DiscreteIntegrator: '<S81>/Integrator' incorporates:
  //   Switch: '<S71>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.rtb_X_est_wb +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1] = 10.0;
  } else if (joystick_enabled_matlab_node_B.idx < -10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[1] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S76>/Filter'
  joystick_enabled_matlab_node_DW.Filter_DSTATE_n[1] += 0.01 *
    joystick_enabled_matlab_node_B.eps[1];

  // Switch: '<S181>/Switch1' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant'
  //   Constant: '<S181>/Constant2'
  //   RelationalOperator: '<S181>/fix for DT propagation issue'

  if (joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S181>/Switch2' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant3'
  //   Constant: '<S181>/Constant4'
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   RelationalOperator: '<S181>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.eps_n[1] > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S181>/Switch' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant1'
  //   DiscreteIntegrator: '<S191>/Integrator'
  //   Logic: '<S181>/AND3'
  //   RelationalOperator: '<S181>/Equal1'
  //   RelationalOperator: '<S181>/Relational Operator'
  //   Switch: '<S181>/Switch1'
  //   Switch: '<S181>/Switch2'

  if ((joystick_enabled_matlab_node_B.rtb_Filter_p_idx_0 != 0.0) && (tmp ==
       tmp_0)) {
    joystick_enabled_matlab_node_B.b_t = 0.0;
  } else {
    joystick_enabled_matlab_node_B.b_t = joystick_enabled_matlab_node_B.eps_n[1];
  }

  // Update for DiscreteIntegrator: '<S191>/Integrator' incorporates:
  //   Switch: '<S181>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 * joystick_enabled_matlab_node_B.b_t
    + joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1] = 100.0;
  } else if (joystick_enabled_matlab_node_B.idx < -100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[1] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S186>/Filter'
  joystick_enabled_matlab_node_DW.Filter_DSTATE_g[1] += 0.01 *
    joystick_enabled_matlab_node_B.wb_u[1];

  // Update for DiscreteIntegrator: '<S136>/Integrator' incorporates:
  //   Switch: '<S126>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.b_a_l +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[2];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE[2] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[2] = 1.0;
  } else if (joystick_enabled_matlab_node_B.idx < -1.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE[2] = -1.0;
  }

  // Update for DiscreteIntegrator: '<S131>/Filter' incorporates:
  //   Gain: '<S139>/Filter Coefficient'

  joystick_enabled_matlab_node_DW.Filter_DSTATE[2] += 0.01 *
    joystick_enabled_matlab_node_B.eps_p[2];

  // Switch: '<S71>/Switch1' incorporates:
  //   Constant: '<S71>/Clamping_zero'
  //   Constant: '<S71>/Constant'
  //   Constant: '<S71>/Constant2'
  //   RelationalOperator: '<S71>/fix for DT propagation issue'

  if (joystick_enabled_matlab_node_B.rtb_Integrator_i_d > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S71>/Switch2' incorporates:
  //   Constant: '<S71>/Clamping_zero'
  //   Constant: '<S71>/Constant3'
  //   Constant: '<S71>/Constant4'
  //   RelationalOperator: '<S71>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.rtb_X_est_wb_a > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S71>/Switch' incorporates:
  //   Constant: '<S71>/Clamping_zero'
  //   Constant: '<S71>/Constant1'
  //   Logic: '<S71>/AND3'
  //   RelationalOperator: '<S71>/Equal1'
  //   RelationalOperator: '<S71>/Relational Operator'
  //   Switch: '<S71>/Switch1'
  //   Switch: '<S71>/Switch2'

  if ((joystick_enabled_matlab_node_B.rtb_Integrator_i_d != 0.0) && (tmp ==
       tmp_0)) {
    joystick_enabled_matlab_node_B.rtb_X_est_wb_a = 0.0;
  }

  // Update for DiscreteIntegrator: '<S81>/Integrator' incorporates:
  //   Switch: '<S71>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.rtb_X_est_wb_a +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2] = 10.0;
  } else if (joystick_enabled_matlab_node_B.idx < -10.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_j[2] = -10.0;
  }

  // Update for DiscreteIntegrator: '<S76>/Filter' incorporates:
  //   Gain: '<S84>/Filter Coefficient'

  joystick_enabled_matlab_node_DW.Filter_DSTATE_n[2] += 0.01 *
    joystick_enabled_matlab_node_B.eps_b;

  // Switch: '<S181>/Switch1' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant'
  //   Constant: '<S181>/Constant2'
  //   RelationalOperator: '<S181>/fix for DT propagation issue'

  if (joystick_enabled_matlab_node_B.upper_force_index > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S181>/Switch2' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant3'
  //   Constant: '<S181>/Constant4'
  //   Gain: '<S188>/Integral Gain'
  //   RelationalOperator: '<S181>/fix for DT propagation issue1'

  if (joystick_enabled_matlab_node_B.eps_f > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S181>/Switch' incorporates:
  //   Constant: '<S181>/Clamping_zero'
  //   Constant: '<S181>/Constant1'
  //   Logic: '<S181>/AND3'
  //   RelationalOperator: '<S181>/Equal1'
  //   RelationalOperator: '<S181>/Relational Operator'
  //   Switch: '<S181>/Switch1'
  //   Switch: '<S181>/Switch2'

  if ((joystick_enabled_matlab_node_B.upper_force_index != 0.0) && (tmp == tmp_0))
  {
    joystick_enabled_matlab_node_B.eps_f = 0.0;
  }

  // Update for DiscreteIntegrator: '<S191>/Integrator' incorporates:
  //   Switch: '<S181>/Switch'

  joystick_enabled_matlab_node_B.idx = 0.01 *
    joystick_enabled_matlab_node_B.eps_f +
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2];
  joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2] =
    joystick_enabled_matlab_node_B.idx;
  if (joystick_enabled_matlab_node_B.idx > 100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2] = 100.0;
  } else if (joystick_enabled_matlab_node_B.idx < -100.0) {
    joystick_enabled_matlab_node_DW.Integrator_DSTATE_h[2] = -100.0;
  }

  // Update for DiscreteIntegrator: '<S186>/Filter' incorporates:
  //   DataStoreRead: '<S25>/Data Store Read9'
  //   Gain: '<S194>/Filter Coefficient'
  //
  joystick_enabled_matlab_node_DW.Filter_DSTATE_g[2] += 0.01 *
    joystick_enabled_matlab_node_B.rtb_delta_qe_idx_1_tmp;
  if (joystick_enabled_matlab_node_B.integrator_reset > 0) {
    joystick_enabled_matlab_node_DW.Filter_PrevResetState_a = 1;
  } else {
    joystick_enabled_matlab_node_DW.Filter_PrevResetState_a = 0;
  }

  // Update absolute time
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&joystick_enabled_matlab_node_M)->Timing.clockTick0++;
}

// Model step function for TID1
void joystick_enabled_matlab_node::step1() // Sample time: [0.5s, 0.0s]
{
  // MATLABSystem: '<S228>/SinkBlock' incorporates:
  //   Constant: '<S227>/Constant'

  Pub_joystick_enabled_matlab_node_435_150.publish
    (&joystick_enabled_matlab__ConstP.Constant_Value_d);
}

// Use this function only if you need to maintain compatibility with an existing static main program.
void joystick_enabled_matlab_node_step(joystick_enabled_matlab_node &
  joystick_enabled_matlab_nod_Obj_In, int_T tid)
{
  switch (tid) {
   case 0 :
    joystick_enabled_matlab_nod_Obj_In.step0();
    break;

   case 1 :
    joystick_enabled_matlab_nod_Obj_In.step1();
    break;

   default :
    // do nothing
    break;
  }
}

// Model initialize function
void joystick_enabled_matlab_node::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S6>/Position Integrator'
  joystick_enabled_matlab_node_DW.PositionIntegrator_PrevResetSta = 2;
  joystick_enabled_matlab_node_DW.PositionIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S6>/Velocity Integrator'
  joystick_enabled_matlab_node_DW.VelocityIntegrator_PrevResetSta = 2;
  joystick_enabled_matlab_node_DW.VelocityIntegrator_IC_LOADING = 1U;

  // InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' 
  joystick_enabled_matlab_node_DW.DiscreteTimeIntegrator_PrevRese = 2;

  // InitializeConditions for DiscreteIntegrator: '<S136>/Integrator'
  joystick_enabled_matlab_node_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S131>/Filter'
  joystick_enabled_matlab_node_DW.Filter_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S81>/Integrator'
  joystick_enabled_matlab_node_DW.Integrator_PrevResetState_d = 2;

  // InitializeConditions for DiscreteIntegrator: '<S76>/Filter'
  joystick_enabled_matlab_node_DW.Filter_PrevResetState_j = 2;

  // InitializeConditions for DiscreteIntegrator: '<S191>/Integrator'
  joystick_enabled_matlab_node_DW.Integrator_PrevResetState_p = 2;

  // InitializeConditions for DiscreteIntegrator: '<S186>/Filter'
  joystick_enabled_matlab_node_DW.Filter_PrevResetState_a = 2;

  // SystemInitialize for Enabled SubSystem: '<S1>/Subsystem'
  // Start for MATLABSystem: '<S22>/SinkBlock'
  joystick_enabled_matlab_node_DW.obj_o.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_o.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_o.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_o.isInitialized = 1;
  joystick_en_Publisher_setupImpl(&joystick_enabled_matlab_node_DW.obj_o);
  joystick_enabled_matlab_node_DW.obj_o.isSetupComplete = true;

  // End of SystemInitialize for SubSystem: '<S1>/Subsystem'

  // SystemInitialize for MATLAB Function: '<S25>/guidanceLaw'
  joystick_enabled_matlab_node_DW.action_id = 1.0;
  joystick_enabled_matlab_node_DW.prior_Ri_u[0] = 999.0;
  joystick_enabled_matlab_node_DW.prior_Ri_u[1] = 999.0;
  joystick_enabled_matlab_node_DW.prior_Ri_u[2] = 999.0;

  // SystemInitialize for MATLAB Function: '<S6>/dvl_reset'
  joystick_enabled_matlab_node_DW.prior_flag = true;

  // SystemInitialize for MATLAB Function: '<Root>/joystick_mode_manager'
  joystick_enabled_matlab_node_DW.joystick_flag = true;
  joystick_enabled_matlab_node_DW.prior_joystick_flag = true;

  // Start for MATLABSystem: '<S224>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj.isInitialized = 1;
  joys_Subscriber_setupImpl_oroz0(&joystick_enabled_matlab_node_DW.obj);
  joystick_enabled_matlab_node_DW.obj.isSetupComplete = true;

  // Start for MATLABSystem: '<S3>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj_b.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_b.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_b.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_b.isInitialized = 1;
  joystic_Subscriber_setupImpl_or(&joystick_enabled_matlab_node_DW.obj_b);
  joystick_enabled_matlab_node_DW.obj_b.isSetupComplete = true;

  // Start for MATLABSystem: '<S8>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj_p.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_p.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_p.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_p.isInitialized = 1;
  joysti_Subscriber_setupImpl_oro(&joystick_enabled_matlab_node_DW.obj_p);
  joystick_enabled_matlab_node_DW.obj_p.isSetupComplete = true;

  // Start for MATLABSystem: '<S2>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj_a.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_a.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_a.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_a.isInitialized = 1;
  joystick_Subscriber_setupImpl_o(&joystick_enabled_matlab_node_DW.obj_a);
  joystick_enabled_matlab_node_DW.obj_a.isSetupComplete = true;

  // Start for MATLABSystem: '<S17>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj_n.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_n.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_n.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_n.isInitialized = 1;
  joystick_e_Subscriber_setupImpl(&joystick_enabled_matlab_node_DW.obj_n);
  joystick_enabled_matlab_node_DW.obj_n.isSetupComplete = true;

  // Start for MATLABSystem: '<S221>/SourceBlock'
  joystick_enabled_matlab_node_DW.obj_c.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_c.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_c.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_c.isInitialized = 1;
  joyst_Subscriber_setupImpl_oroz(&joystick_enabled_matlab_node_DW.obj_c);
  joystick_enabled_matlab_node_DW.obj_c.isSetupComplete = true;

  // Start for MATLABSystem: '<S229>/SinkBlock'
  joystick_enabled_matlab_node_DW.obj_e.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_e.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_e.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_e.isInitialized = 1;
  joystic_Publisher_setupImpl_oro(&joystick_enabled_matlab_node_DW.obj_e);
  joystick_enabled_matlab_node_DW.obj_e.isSetupComplete = true;

  // Start for MATLABSystem: '<S219>/SinkBlock'
  joystick_enabled_matlab_node_DW.obj_g.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_g.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_g.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_g.isInitialized = 1;
  joystick__Publisher_setupImpl_o(&joystick_enabled_matlab_node_DW.obj_g);
  joystick_enabled_matlab_node_DW.obj_g.isSetupComplete = true;

  // Start for MATLABSystem: '<S228>/SinkBlock'
  joystick_enabled_matlab_node_DW.obj_f.QOSAvoidROSNamespaceConventions = false;
  joystick_enabled_matlab_node_DW.obj_f.matlabCodegenIsDeleted = false;
  joystick_enabled_matlab_node_DW.obj_f.isSetupComplete = false;
  joystick_enabled_matlab_node_DW.obj_f.isInitialized = 1;
  joystick_Publisher_setupImpl_or(&joystick_enabled_matlab_node_DW.obj_f);
  joystick_enabled_matlab_node_DW.obj_f.isSetupComplete = true;
}

// Model terminate function
void joystick_enabled_matlab_node::terminate()
{
  // Terminate for MATLABSystem: '<S224>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_428.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S224>/SourceBlock'

  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj_b.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_b.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_b.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_397.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'

  // Terminate for MATLABSystem: '<S8>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj_p.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_p.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_p.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_412.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S8>/SourceBlock'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj_a.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_a.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_a.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_363.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'

  // Terminate for MATLABSystem: '<S17>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj_n.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_n.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_n.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_360_284.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S17>/SourceBlock'

  // Terminate for Enabled SubSystem: '<S1>/Subsystem'
  // Terminate for MATLABSystem: '<S22>/SinkBlock'
  if (!joystick_enabled_matlab_node_DW.obj_o.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_o.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_o.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_o.isSetupComplete) {
      Pub_joystick_enabled_matlab_node_360_7.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S22>/SinkBlock'
  // End of Terminate for SubSystem: '<S1>/Subsystem'

  // Terminate for MATLABSystem: '<S221>/SourceBlock'
  if (!joystick_enabled_matlab_node_DW.obj_c.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_c.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_c.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_c.isSetupComplete) {
      Sub_joystick_enabled_matlab_node_416.resetSubscriberPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S221>/SourceBlock'

  // Terminate for MATLABSystem: '<S229>/SinkBlock'
  if (!joystick_enabled_matlab_node_DW.obj_e.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_e.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_e.isSetupComplete) {
      Pub_joystick_enabled_matlab_node_436_2.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S229>/SinkBlock'

  // Terminate for MATLABSystem: '<S219>/SinkBlock'
  if (!joystick_enabled_matlab_node_DW.obj_g.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_g.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_g.isSetupComplete) {
      Pub_joystick_enabled_matlab_node_404_3.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S219>/SinkBlock'

  // Terminate for MATLABSystem: '<S228>/SinkBlock'
  if (!joystick_enabled_matlab_node_DW.obj_f.matlabCodegenIsDeleted) {
    joystick_enabled_matlab_node_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((joystick_enabled_matlab_node_DW.obj_f.isInitialized == 1) &&
        joystick_enabled_matlab_node_DW.obj_f.isSetupComplete) {
      Pub_joystick_enabled_matlab_node_435_150.resetPublisherPtr();//();
    }
  }

  // End of Terminate for MATLABSystem: '<S228>/SinkBlock'
}

// Constructor
joystick_enabled_matlab_node::joystick_enabled_matlab_node() :
  joystick_enabled_matlab_node_B(),
  joystick_enabled_matlab_node_DW(),
  joystick_enabled_matlab_node_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
joystick_enabled_matlab_node::~joystick_enabled_matlab_node() = default;

// Real-Time Model get method
RT_MODEL_joystick_enabled_mat_T * joystick_enabled_matlab_node::getRTM()
{
  return (&joystick_enabled_matlab_node_M);
}

uint8_T &RT_MODEL_joystick_enabled_mat_T::TaskCounter(int32_T idx)
{
  return (Timing.TaskCounters.TID[(idx)]);
}

boolean_T RT_MODEL_joystick_enabled_mat_T::StepTask(int32_T idx) const
{
  return (Timing.TaskCounters.TID[(idx)] == 0);
}

const char_T* RT_MODEL_joystick_enabled_mat_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_joystick_enabled_mat_T::setErrorStatus(const char_T* const
  volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
