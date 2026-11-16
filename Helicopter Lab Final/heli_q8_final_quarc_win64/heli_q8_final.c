/*
 * heli_q8_final.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_q8_final".
 *
 * Model version              : 11.70
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Sun Nov 15 13:05:47 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "heli_q8_final.h"
#include "heli_q8_final_private.h"
#include "heli_q8_final_dt.h"

t_stream heli_q8_final_rtZt_stream = NULL;

/* Block signals (default storage) */
B_heli_q8_final_T heli_q8_final_B;

/* Continuous states */
X_heli_q8_final_T heli_q8_final_X;

/* Block states (default storage) */
DW_heli_q8_final_T heli_q8_final_DW;

/* Real-time model */
static RT_MODEL_heli_q8_final_T heli_q8_final_M_;
RT_MODEL_heli_q8_final_T *const heli_q8_final_M = &heli_q8_final_M_;
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

int32_T div_s32(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T tempAbsQuotient;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    tempAbsQuotient = (numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
                       numerator) / (denominator < 0 ? ~(uint32_T)denominator +
      1U : (uint32_T)denominator);
    quotient = (numerator < 0) != (denominator < 0) ? -(int32_T)tempAbsQuotient :
      (int32_T)tempAbsQuotient;
  }

  return quotient;
}

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(heli_q8_final_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(heli_q8_final_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (heli_q8_final_M->Timing.TaskCounters.TID[1] == 0) {
    heli_q8_final_M->Timing.RateInteraction.TID1_2 =
      (heli_q8_final_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    heli_q8_final_M->Timing.perTaskSampleHits[5] =
      heli_q8_final_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (heli_q8_final_M->Timing.TaskCounters.TID[2])++;
  if ((heli_q8_final_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    heli_q8_final_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  heli_q8_final_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model output function for TID0 */
void heli_q8_final_output0(void)       /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  t_stream_ptr rtb_StreamCall1_o1;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[21];
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  boolean_T rtb_StreamRead1_o3;
  static const int8_T b_I[36] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 };

  real_T P_hat_tmp_0[36];
  real_T P_hat_tmp_1[36];
  real_T P_hat_tmp_2[36];
  real_T P_hat_tmp_3[36];
  real_T A_tmp[30];
  real_T L[30];
  real_T tmp_3[30];
  real_T A[25];
  real_T b[25];
  real_T tmp[9];
  real_T tmp_4[6];
  real_T tmp_5[5];
  real_T tmp_6[5];
  real_T tmp_7[5];
  real_T rtb_Gain2[3];
  real_T tmp_0[3];
  real_T tmp_1[2];
  real_T tmp_2[2];
  real_T euler_rates_pre_offset_tmp;
  real_T euler_rates_pre_offset_tmp_0;
  real_T rtb_ManualSwitch5;
  real_T rtb_PulseGenerator2;
  int32_T c_ix;
  int32_T c_j;
  int32_T d_k;
  int32_T e;
  int32_T i;
  int32_T ijA;
  int32_T ix;
  int32_T iy;
  int8_T P_hat_tmp[36];
  int8_T ipiv[5];
  int8_T p[5];
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* set solver stop time */
    if (!(heli_q8_final_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&heli_q8_final_M->solverInfo,
                            ((heli_q8_final_M->Timing.clockTickH0 + 1) *
        heli_q8_final_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&heli_q8_final_M->solverInfo,
                            ((heli_q8_final_M->Timing.clockTick0 + 1) *
        heli_q8_final_M->Timing.stepSize0 + heli_q8_final_M->Timing.clockTickH0 *
        heli_q8_final_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(heli_q8_final_M)) {
    heli_q8_final_M->Timing.t[0] = rtsiGetT(&heli_q8_final_M->solverInfo);
  }

  /* RateTransition: '<S7>/Rate Transition: x' */
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: heli_q8_final/Lab_4/Heli 3D1/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (heli_q8_final_DW.HILReadEncoderTimebase_Task, 1,
         &heli_q8_final_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          heli_q8_final_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          heli_q8_final_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          heli_q8_final_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* DiscretePulseGenerator: '<S1>/Pulse Generator1' */
    rtb_PulseGenerator2 = (heli_q8_final_DW.clockTickCounter <
      heli_q8_final_P.PulseGenerator1_Duty) &&
      (heli_q8_final_DW.clockTickCounter >= 0) ?
      heli_q8_final_P.PulseGenerator1_Amp : 0.0;
    if (heli_q8_final_DW.clockTickCounter >=
        heli_q8_final_P.PulseGenerator1_Period - 1.0) {
      heli_q8_final_DW.clockTickCounter = 0;
    } else {
      heli_q8_final_DW.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<S1>/Pulse Generator1' */

    /* Sum: '<S1>/Sum9' incorporates:
     *  Constant: '<S1>/Constant7'
     */
    heli_q8_final_B.Sum9 = rtb_PulseGenerator2 + heli_q8_final_P.Constant7_Value;
    if (heli_q8_final_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S7>/Rate Transition: x' */
      heli_q8_final_B.RateTransitionx = heli_q8_final_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S7>/Dead Zone: x' */
    if (heli_q8_final_B.RateTransitionx > heli_q8_final_P.DeadZonex_End) {
      rtb_PulseGenerator2 = heli_q8_final_B.RateTransitionx -
        heli_q8_final_P.DeadZonex_End;
    } else if (heli_q8_final_B.RateTransitionx >=
               heli_q8_final_P.DeadZonex_Start) {
      rtb_PulseGenerator2 = 0.0;
    } else {
      rtb_PulseGenerator2 = heli_q8_final_B.RateTransitionx -
        heli_q8_final_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S7>/Dead Zone: x' */

    /* Gain: '<S7>/Joystick_gain_x' incorporates:
     *  Gain: '<S7>/Gain: x'
     */
    heli_q8_final_B.Joystick_gain_x = heli_q8_final_P.Gainx_Gain *
      rtb_PulseGenerator2 * heli_q8_final_P.Joystick_gain_x;
  }

  /* End of RateTransition: '<S7>/Rate Transition: x' */

  /* ManualSwitch: '<S1>/Manual Switch6' */
  if (heli_q8_final_P.ManualSwitch6_CurrentSetting == 1) {
    /* Step: '<S1>/Step1' incorporates:
     *  Step: '<S1>/Step6'
     */
    rtb_PulseGenerator2 = heli_q8_final_M->Timing.t[0];
    if (rtb_PulseGenerator2 < heli_q8_final_P.Step1_Time) {
      euler_rates_pre_offset_tmp = heli_q8_final_P.Step1_Y0;
    } else {
      euler_rates_pre_offset_tmp = heli_q8_final_P.Step1_YFinal;
    }

    /* End of Step: '<S1>/Step1' */

    /* Step: '<S1>/Step6' */
    if (rtb_PulseGenerator2 < heli_q8_final_P.Step6_Time) {
      rtb_PulseGenerator2 = heli_q8_final_P.Step6_Y0;
    } else {
      rtb_PulseGenerator2 = heli_q8_final_P.Step6_YFinal;
    }

    /* Switch: '<S1>/Switch1' incorporates:
     *  Sum: '<S1>/Sum8'
     */
    if (euler_rates_pre_offset_tmp - rtb_PulseGenerator2 >
        heli_q8_final_P.Switch1_Threshold) {
      /* ManualSwitch: '<S1>/Manual Switch6' */
      heli_q8_final_B.p_c = heli_q8_final_B.Sum9;
    } else {
      /* ManualSwitch: '<S1>/Manual Switch6' incorporates:
       *  Constant: '<S1>/Constant6'
       */
      heli_q8_final_B.p_c = heli_q8_final_P.Constant6_Value;
    }

    /* End of Switch: '<S1>/Switch1' */
  } else {
    /* ManualSwitch: '<S1>/Manual Switch6' */
    heli_q8_final_B.p_c = heli_q8_final_B.Joystick_gain_x;
  }

  /* End of ManualSwitch: '<S1>/Manual Switch6' */

  /* ManualSwitch: '<S1>/Manual Switch5' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Step: '<S10>/Step'
   */
  if (heli_q8_final_P.ManualSwitch5_CurrentSetting == 1) {
    rtb_ManualSwitch5 = heli_q8_final_P.Constant4_Value;
  } else {
    if (heli_q8_final_M->Timing.t[0] < heli_q8_final_P.Ramp4_start) {
      /* Step: '<S10>/Step' */
      rtb_PulseGenerator2 = heli_q8_final_P.Step_Y0;
    } else {
      /* Step: '<S10>/Step' */
      rtb_PulseGenerator2 = heli_q8_final_P.Ramp4_slope;
    }

    /* Sum: '<S10>/Output' incorporates:
     *  Clock: '<S10>/Clock'
     *  Constant: '<S10>/Constant'
     *  Constant: '<S10>/Constant1'
     *  Product: '<S10>/Product'
     *  Sum: '<S10>/Sum'
     */
    rtb_ManualSwitch5 = (heli_q8_final_M->Timing.t[0] -
                         heli_q8_final_P.Ramp4_start) * rtb_PulseGenerator2 +
      heli_q8_final_P.Ramp4_InitialOutput;

    /* Saturate: '<S1>/Saturation4' */
    if (rtb_ManualSwitch5 > heli_q8_final_P.Saturation4_UpperSat) {
      rtb_ManualSwitch5 = heli_q8_final_P.Saturation4_UpperSat;
    } else {
      if (rtb_ManualSwitch5 < heli_q8_final_P.Saturation4_LowerSat) {
        rtb_ManualSwitch5 = heli_q8_final_P.Saturation4_LowerSat;
      }
    }

    /* End of Saturate: '<S1>/Saturation4' */
  }

  /* End of ManualSwitch: '<S1>/Manual Switch5' */

  /* RateTransition: '<S7>/Rate Transition: y' */
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    if (heli_q8_final_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S7>/Rate Transition: y' */
      heli_q8_final_B.RateTransitiony = heli_q8_final_DW.RateTransitiony_Buffer0;
    }

    /* DeadZone: '<S7>/Dead Zone: y' */
    if (heli_q8_final_B.RateTransitiony > heli_q8_final_P.DeadZoney_End) {
      rtb_PulseGenerator2 = heli_q8_final_B.RateTransitiony -
        heli_q8_final_P.DeadZoney_End;
    } else if (heli_q8_final_B.RateTransitiony >=
               heli_q8_final_P.DeadZoney_Start) {
      rtb_PulseGenerator2 = 0.0;
    } else {
      rtb_PulseGenerator2 = heli_q8_final_B.RateTransitiony -
        heli_q8_final_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S7>/Dead Zone: y' */

    /* Gain: '<S7>/Joystick_gain_y' incorporates:
     *  Gain: '<S7>/Gain: y'
     */
    heli_q8_final_B.Joystick_gain_y = heli_q8_final_P.Gainy_Gain *
      rtb_PulseGenerator2 * heli_q8_final_P.Joystick_gain_y;

    /* DiscretePulseGenerator: '<S1>/Pulse Generator2' */
    rtb_PulseGenerator2 = (heli_q8_final_DW.clockTickCounter_j <
      heli_q8_final_P.PulseGenerator2_Duty) &&
      (heli_q8_final_DW.clockTickCounter_j >= 0) ?
      heli_q8_final_P.PulseGenerator2_Amp : 0.0;
    if (heli_q8_final_DW.clockTickCounter_j >=
        heli_q8_final_P.PulseGenerator2_Period - 1.0) {
      heli_q8_final_DW.clockTickCounter_j = 0;
    } else {
      heli_q8_final_DW.clockTickCounter_j++;
    }

    /* End of DiscretePulseGenerator: '<S1>/Pulse Generator2' */

    /* Sum: '<S1>/Sum7' incorporates:
     *  Constant: '<S1>/Constant8'
     */
    heli_q8_final_B.Sum7 = rtb_PulseGenerator2 + heli_q8_final_P.Constant8_Value;
  }

  /* End of RateTransition: '<S7>/Rate Transition: y' */

  /* ManualSwitch: '<S1>/Manual Switch7' */
  if (heli_q8_final_P.ManualSwitch7_CurrentSetting == 1) {
    rtb_PulseGenerator2 = heli_q8_final_B.Joystick_gain_y;
  } else {
    /* Step: '<S1>/Step4' incorporates:
     *  Step: '<S1>/Step5'
     */
    rtb_PulseGenerator2 = heli_q8_final_M->Timing.t[0];
    if (rtb_PulseGenerator2 < heli_q8_final_P.Step4_Time) {
      euler_rates_pre_offset_tmp = heli_q8_final_P.Step4_Y0;
    } else {
      euler_rates_pre_offset_tmp = heli_q8_final_P.Step4_YFinal;
    }

    /* End of Step: '<S1>/Step4' */

    /* Step: '<S1>/Step5' */
    if (rtb_PulseGenerator2 < heli_q8_final_P.Step5_Time) {
      rtb_PulseGenerator2 = heli_q8_final_P.Step5_Y0;
    } else {
      rtb_PulseGenerator2 = heli_q8_final_P.Step5_YFinal;
    }

    /* Switch: '<S1>/Switch2' incorporates:
     *  Constant: '<S1>/Constant5'
     *  Sum: '<S1>/Sum6'
     */
    if (euler_rates_pre_offset_tmp - rtb_PulseGenerator2 >
        heli_q8_final_P.Switch2_Threshold) {
      rtb_PulseGenerator2 = heli_q8_final_B.Sum7;
    } else {
      rtb_PulseGenerator2 = heli_q8_final_P.Constant5_Value;
    }

    /* End of Switch: '<S1>/Switch2' */
  }

  /* End of ManualSwitch: '<S1>/Manual Switch7' */

  /* Sum: '<S1>/Sum' */
  heli_q8_final_B.Sum = rtb_PulseGenerator2 - rtb_ManualSwitch5;
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* Gain: '<S5>/Pitch: Count to rad' */
    heli_q8_final_B.PitchCounttorad = heli_q8_final_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* S-Function (stream_call_block): '<S6>/Stream Call1' incorporates:
     *  Constant: '<S6>/Constant'
     *  S-Function (string_constant_block): '<S6>/String Constant'
     */

    /* S-Function Block: heli_q8_final/Lab_4/IMU1/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (heli_q8_final_P.Constant_Value != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (heli_q8_final_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *) heli_q8_final_P.StringConstant_Value, 255)
                == 255) {
              rtmSetErrorStatus(heli_q8_final_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *)
                heli_q8_final_P.StringConstant_Value,
                heli_q8_final_P.StreamCall1_NonBlocking != 0,
                heli_q8_final_P.StreamCall1_SendBufferSize,
                heli_q8_final_P.StreamCall1_ReceiveBufferSize,
                &heli_q8_final_DW.StreamCall1_Stream);
              if (result == 0) {
                heli_q8_final_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order(heli_q8_final_DW.StreamCall1_Stream,
                                      (t_stream_byte_order)
                                      heli_q8_final_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 = &heli_q8_final_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                heli_q8_final_DW.StreamCall1_State =
                  STREAM_CALL_STATE_CONNECTING;
                result = 0;
              }
            }
          }
          break;
        }

       case STREAM_CALL_STATE_CONNECTING:
        {
          if (!close_flag) {
            const t_timeout timeout = { 0, 0, false };/* zero seconds */

            result = stream_poll(heli_q8_final_DW.StreamCall1_Stream, &timeout,
                                 STREAM_POLL_CONNECT);
            if (result > 0) {
              heli_q8_final_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(heli_q8_final_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    heli_q8_final_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &heli_q8_final_DW.StreamCall1_Stream;
              result = 0;
              break;
            } else if (result == 0) {
              break;
            }
          }

          /* Fall through deliberately */
        }

       case STREAM_CALL_STATE_CONNECTED:
        {
          rtb_StreamCall1_o1 = &heli_q8_final_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close
            (heli_q8_final_DW.StreamCall1_Stream);
          if (close_result == 0) {
            heli_q8_final_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
            heli_q8_final_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      heli_q8_final_B.StreamCall1_o2 = heli_q8_final_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S6>/Stream Formatted Write' incorporates:
     *  Constant: '<S6>/Constant1'
     */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          heli_q8_final_P.StreamFormattedWrite_MaxUnits,
          &rtb_StreamFormattedWrite_o2, "%c\n"
          , (char) heli_q8_final_P.Constant1_Value
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }
    }

    /* S-Function (stream_read_block): '<S6>/Stream Read1' incorporates:
     *  Constant: '<S6>/Constant1'
     *  S-Function (stream_call_block): '<S6>/Stream Call1'
     *  S-Function (stream_formatted_write_block): '<S6>/Stream Formatted Write'
     */

    /* S-Function Block: heli_q8_final/Lab_4/IMU1/Stream Read1 (stream_read_block) */
    {
      t_error result;
      memset(&rtb_StreamRead1_o2[0], 0, 10 * sizeof(real32_T));
      if (((t_stream_ptr)rtb_StreamCall1_o1) != NULL) {
        result = stream_receive_unit_array(*((t_stream_ptr)rtb_StreamCall1_o1),
          &rtb_StreamRead1_o2[0], sizeof(real32_T), 10);
        rtb_StreamRead1_o3 = (result > 0);
        if (result > 0 || result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      } else {
        rtb_StreamRead1_o3 = false;
        result = 0;
      }
    }

    for (i = 0; i < 10; i++) {
      /* Switch: '<S6>/Switch' */
      if (rtb_StreamRead1_o3) {
        /* Switch: '<S6>/Switch' incorporates:
         *  DataTypeConversion: '<S6>/Data Type Conversion'
         */
        heli_q8_final_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        /* Switch: '<S6>/Switch' incorporates:
         *  Memory: '<S6>/Memory'
         */
        heli_q8_final_B.Switch[i] = heli_q8_final_DW.Memory_PreviousInput[i];
      }

      /* End of Switch: '<S6>/Switch' */
    }

    /* Gain: '<S6>/Gain2' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = heli_q8_final_P.Gain2_Gain[i + 6] * heli_q8_final_B.Switch
        [2] + (heli_q8_final_P.Gain2_Gain[i + 3] * heli_q8_final_B.Switch[1] +
               heli_q8_final_P.Gain2_Gain[i] * heli_q8_final_B.Switch[0]);
    }

    /* End of Gain: '<S6>/Gain2' */

    /* MATLAB Function: '<S1>/Accel vector to [pitch, elevation]1' */
    /* MATLAB Function 'Lab_4/Accel vector to [pitch, elevation]1': '<S2>:1' */
    /* '<S2>:1:2' */
    /* '<S2>:1:3' */
    /* '<S2>:1:5' */
    /* '<S2>:1:6' */
    /* '<S2>:1:8' */
    heli_q8_final_B.euler_angles[0] = -rt_atan2d_snf(rtb_Gain2[1], -rtb_Gain2[2])
      + 0.025;
    heli_q8_final_B.euler_angles[1] = rt_atan2d_snf(rtb_Gain2[0], sqrt
      (rtb_Gain2[1] * rtb_Gain2[1] + rtb_Gain2[2] * rtb_Gain2[2])) + 0.0325;

    /* MATLAB Function: '<S1>/Gyro vector to [pitch rate, elevation rate, travle rate]1' */
    /* MATLAB Function 'Lab_4/Gyro vector to [pitch rate, elevation rate, travle rate]1': '<S4>:1' */
    /* '<S4>:1:3' */
    /* '<S4>:1:4' */
    /* '<S4>:1:5' */
    /* '<S4>:1:7' */
    /* '<S4>:1:8' */
    /* '<S4>:1:12' */
    /* '<S4>:1:16' */
    rtb_ManualSwitch5 = tan(heli_q8_final_B.euler_angles[1]);
    rtb_PulseGenerator2 = sin(heli_q8_final_B.euler_angles[0]);
    euler_rates_pre_offset_tmp = cos(heli_q8_final_B.euler_angles[0]);
    euler_rates_pre_offset_tmp_0 = cos(heli_q8_final_B.euler_angles[1]);
    tmp[0] = 1.0;
    tmp[3] = rtb_PulseGenerator2 * rtb_ManualSwitch5;
    tmp[6] = euler_rates_pre_offset_tmp * rtb_ManualSwitch5;
    tmp[1] = 0.0;
    tmp[4] = euler_rates_pre_offset_tmp;
    tmp[7] = -rtb_PulseGenerator2;
    tmp[2] = 0.0;
    tmp[5] = rtb_PulseGenerator2 / euler_rates_pre_offset_tmp_0;
    tmp[8] = euler_rates_pre_offset_tmp / euler_rates_pre_offset_tmp_0;

    /* Gain: '<S6>/Gain1' */
    for (i = 0; i < 3; i++) {
      tmp_0[i] = heli_q8_final_P.Gain1_Gain[i + 6] * heli_q8_final_B.Switch[5] +
        (heli_q8_final_P.Gain1_Gain[i + 3] * heli_q8_final_B.Switch[4] +
         heli_q8_final_P.Gain1_Gain[i] * heli_q8_final_B.Switch[3]);
    }

    /* End of Gain: '<S6>/Gain1' */

    /* MATLAB Function: '<S1>/Gyro vector to [pitch rate, elevation rate, travle rate]1' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = tmp[i + 6] * tmp_0[2] + (tmp[i + 3] * tmp_0[1] + tmp[i] *
        tmp_0[0]);
    }

    /* '<S4>:1:17' */
    heli_q8_final_B.euler_rates[0] = rtb_Gain2[0] + -0.003;
    heli_q8_final_B.euler_rates[1] = rtb_Gain2[1] + 0.04;
    heli_q8_final_B.euler_rates[2] = rtb_Gain2[2] + 0.0475;

    /* MATLAB Function: '<S8>/Kalman Correction' incorporates:
     *  Constant: '<S8>/Constant'
     *  Constant: '<S8>/Constant1'
     *  UnitDelay: '<S8>/Unit Delay'
     *  UnitDelay: '<S8>/Unit Delay1'
     */
    /* MATLAB Function 'Lab_4/Kalman Filter1/Kalman Correction': '<S11>:1' */
    /* '<S11>:1:4' */
    if (rtb_StreamRead1_o3) {
      /* '<S11>:1:2' */
      /* '<S11>:1:3' */
      for (i = 0; i < 25; i++) {
        b[i] = 0.0;
      }

      for (i = 0; i < 5; i++) {
        for (c_j = 0; c_j < 6; c_j++) {
          ix = 5 * c_j + i;
          A_tmp[c_j + 6 * i] = heli_q8_final_P.C_d[ix];
          tmp_3[ix] = 0.0;
          for (iy = 0; iy < 6; iy++) {
            tmp_3[ix] += heli_q8_final_P.C_d[5 * iy + i] *
              heli_q8_final_DW.UnitDelay_DSTATE[6 * c_j + iy];
          }
        }
      }

      for (i = 0; i < 5; i++) {
        for (c_j = 0; c_j < 5; c_j++) {
          rtb_PulseGenerator2 = 0.0;
          for (iy = 0; iy < 6; iy++) {
            rtb_PulseGenerator2 += tmp_3[5 * iy + i] * A_tmp[6 * c_j + iy];
          }

          iy = 5 * c_j + i;
          A[iy] = heli_q8_final_P.R_flying[iy] + rtb_PulseGenerator2;
        }

        ipiv[i] = (int8_T)(i + 1);
      }

      for (c_j = 0; c_j < 4; c_j++) {
        i = c_j * 6;
        iy = 0;
        ix = i;
        rtb_ManualSwitch5 = fabs(A[i]);
        for (d_k = 2; d_k <= 5 - c_j; d_k++) {
          ix++;
          rtb_PulseGenerator2 = fabs(A[ix]);
          if (rtb_PulseGenerator2 > rtb_ManualSwitch5) {
            iy = d_k - 1;
            rtb_ManualSwitch5 = rtb_PulseGenerator2;
          }
        }

        if (A[i + iy] != 0.0) {
          if (iy != 0) {
            iy += c_j;
            ipiv[c_j] = (int8_T)(iy + 1);
            ix = c_j;
            for (d_k = 0; d_k < 5; d_k++) {
              rtb_ManualSwitch5 = A[ix];
              A[ix] = A[iy];
              A[iy] = rtb_ManualSwitch5;
              ix += 5;
              iy += 5;
            }
          }

          iy = (i - c_j) + 5;
          for (ix = i + 1; ix < iy; ix++) {
            A[ix] /= A[i];
          }
        }

        iy = i;
        ix = i + 5;
        for (d_k = 0; d_k <= 3 - c_j; d_k++) {
          if (A[ix] != 0.0) {
            rtb_ManualSwitch5 = -A[ix];
            c_ix = i + 1;
            e = (iy - c_j) + 10;
            for (ijA = iy + 6; ijA < e; ijA++) {
              A[ijA] += A[c_ix] * rtb_ManualSwitch5;
              c_ix++;
            }
          }

          ix += 5;
          iy += 5;
        }
      }

      for (i = 0; i < 5; i++) {
        p[i] = (int8_T)(i + 1);
      }

      if (ipiv[0] > 1) {
        i = p[ipiv[0] - 1];
        p[ipiv[0] - 1] = p[0];
        p[0] = (int8_T)i;
      }

      if (ipiv[1] > 2) {
        i = p[ipiv[1] - 1];
        p[ipiv[1] - 1] = p[1];
        p[1] = (int8_T)i;
      }

      if (ipiv[2] > 3) {
        i = p[ipiv[2] - 1];
        p[ipiv[2] - 1] = p[2];
        p[2] = (int8_T)i;
      }

      if (ipiv[3] > 4) {
        i = p[ipiv[3] - 1];
        p[ipiv[3] - 1] = p[3];
        p[3] = (int8_T)i;
      }

      for (c_j = 0; c_j < 5; c_j++) {
        d_k = p[c_j] - 1;
        b[c_j + 5 * d_k] = 1.0;
        for (iy = c_j; iy + 1 < 6; iy++) {
          i = 5 * d_k + iy;
          if (b[i] != 0.0) {
            for (ix = iy + 1; ix + 1 < 6; ix++) {
              c_ix = 5 * d_k + ix;
              b[c_ix] -= b[i] * A[5 * iy + ix];
            }
          }
        }
      }

      for (c_j = 0; c_j < 5; c_j++) {
        i = 5 * c_j;
        for (iy = 4; iy >= 0; iy--) {
          ix = 5 * iy;
          if (b[iy + i] != 0.0) {
            c_ix = iy + i;
            b[c_ix] /= A[iy + ix];
            for (d_k = 0; d_k < iy; d_k++) {
              e = d_k + i;
              b[e] -= b[c_ix] * A[d_k + ix];
            }
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (c_j = 0; c_j < 5; c_j++) {
          iy = i + 6 * c_j;
          tmp_3[iy] = 0.0;
          for (ix = 0; ix < 6; ix++) {
            tmp_3[iy] += heli_q8_final_DW.UnitDelay_DSTATE[6 * ix + i] * A_tmp[6
              * c_j + ix];
          }
        }

        for (c_j = 0; c_j < 5; c_j++) {
          ix = i + 6 * c_j;
          L[ix] = 0.0;
          for (iy = 0; iy < 5; iy++) {
            L[ix] += tmp_3[6 * iy + i] * b[5 * c_j + iy];
          }
        }
      }

      /* SignalConversion generated from: '<S11>/ SFunction ' incorporates:
       *  Constant: '<S8>/Constant'
       *  Constant: '<S8>/Constant1'
       *  UnitDelay: '<S8>/Unit Delay'
       */
      /* '<S11>:1:4' */
      /* '<S11>:1:6' */
      tmp_5[0] = heli_q8_final_B.euler_angles[0];
      tmp_5[1] = heli_q8_final_B.euler_rates[0];
      tmp_5[2] = heli_q8_final_B.euler_angles[1];
      tmp_5[3] = heli_q8_final_B.euler_rates[1];
      tmp_5[4] = heli_q8_final_B.euler_rates[2];
      for (i = 0; i < 5; i++) {
        tmp_6[i] = 0.0;
        for (c_j = 0; c_j < 6; c_j++) {
          tmp_6[i] += heli_q8_final_P.C_d[5 * c_j + i] *
            heli_q8_final_DW.UnitDelay1_DSTATE[c_j];
        }

        tmp_7[i] = tmp_5[i] - tmp_6[i];
      }

      for (i = 0; i < 6; i++) {
        rtb_PulseGenerator2 = 0.0;
        for (c_j = 0; c_j < 5; c_j++) {
          rtb_PulseGenerator2 += L[6 * c_j + i] * tmp_7[c_j];
        }

        heli_q8_final_B.x_hat[i] = heli_q8_final_DW.UnitDelay1_DSTATE[i] +
          rtb_PulseGenerator2;
      }

      /* '<S11>:1:7' */
      for (i = 0; i < 36; i++) {
        P_hat_tmp[i] = b_I[i];
      }

      for (i = 0; i < 6; i++) {
        for (c_j = 0; c_j < 6; c_j++) {
          ix = c_j + 6 * i;
          P_hat_tmp_0[ix] = 0.0;
          for (iy = 0; iy < 5; iy++) {
            P_hat_tmp_0[ix] += L[6 * iy + c_j] * heli_q8_final_P.C_d[5 * i + iy];
          }
        }
      }

      for (i = 0; i < 36; i++) {
        P_hat_tmp_1[i] = (real_T)P_hat_tmp[i] - P_hat_tmp_0[i];
      }

      for (i = 0; i < 6; i++) {
        for (c_j = 0; c_j < 6; c_j++) {
          ix = i + 6 * c_j;
          P_hat_tmp_2[ix] = 0.0;
          for (iy = 0; iy < 6; iy++) {
            P_hat_tmp_2[ix] += P_hat_tmp_1[6 * iy + i] *
              heli_q8_final_DW.UnitDelay_DSTATE[6 * c_j + iy];
          }

          P_hat_tmp_3[c_j + 6 * i] = (real_T)P_hat_tmp[ix] - P_hat_tmp_0[ix];
        }

        for (c_j = 0; c_j < 5; c_j++) {
          ix = i + 6 * c_j;
          A_tmp[ix] = 0.0;
          for (iy = 0; iy < 5; iy++) {
            A_tmp[ix] += L[6 * iy + i] * heli_q8_final_P.R_flying[5 * c_j + iy];
          }
        }
      }

      for (i = 0; i < 6; i++) {
        for (c_j = 0; c_j < 6; c_j++) {
          ix = i + 6 * c_j;
          P_hat_tmp_0[ix] = 0.0;
          for (iy = 0; iy < 6; iy++) {
            P_hat_tmp_0[ix] += P_hat_tmp_2[6 * iy + i] * P_hat_tmp_3[6 * c_j +
              iy];
          }

          P_hat_tmp_1[ix] = 0.0;
          for (iy = 0; iy < 5; iy++) {
            P_hat_tmp_1[ix] += A_tmp[6 * iy + i] * L[6 * iy + c_j];
          }
        }
      }

      for (i = 0; i < 36; i++) {
        heli_q8_final_B.P_hat[i] = P_hat_tmp_0[i] + P_hat_tmp_1[i];
      }
    } else {
      /* '<S11>:1:9' */
      for (i = 0; i < 6; i++) {
        heli_q8_final_B.x_hat[i] = heli_q8_final_DW.UnitDelay1_DSTATE[i];
      }

      /* '<S11>:1:10' */
      memcpy(&heli_q8_final_B.P_hat[0], &heli_q8_final_DW.UnitDelay_DSTATE[0],
             36U * sizeof(real_T));
    }

    /* End of MATLAB Function: '<S8>/Kalman Correction' */

    /* Gain: '<S5>/Elevation: Count to rad' */
    heli_q8_final_B.ElevationCounttorad =
      heli_q8_final_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;
  }

  /* TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  heli_q8_final_B.ElevationTransferFcn = 0.0;
  heli_q8_final_B.ElevationTransferFcn += heli_q8_final_P.ElevationTransferFcn_C
    * heli_q8_final_X.ElevationTransferFcn_CSTATE;
  heli_q8_final_B.ElevationTransferFcn += heli_q8_final_P.ElevationTransferFcn_D
    * heli_q8_final_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
  }

  /* TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  heli_q8_final_B.PitchTransferFcn = 0.0;
  heli_q8_final_B.PitchTransferFcn += heli_q8_final_P.PitchTransferFcn_C *
    heli_q8_final_X.PitchTransferFcn_CSTATE;
  heli_q8_final_B.PitchTransferFcn += heli_q8_final_P.PitchTransferFcn_D *
    heli_q8_final_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Elevation Offset'
     */
    heli_q8_final_B.Sum_d = heli_q8_final_B.ElevationCounttorad -
      heli_q8_final_P.elevation_offset;

    /* Gain: '<S5>/Travel: Count to rad' */
    heli_q8_final_B.TravelCounttorad = heli_q8_final_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* TransferFcn: '<S5>/Travel: Transfer Fcn' */
  heli_q8_final_B.TravelTransferFcn = 0.0;
  heli_q8_final_B.TravelTransferFcn += heli_q8_final_P.TravelTransferFcn_C *
    heli_q8_final_X.TravelTransferFcn_CSTATE;
  heli_q8_final_B.TravelTransferFcn += heli_q8_final_P.TravelTransferFcn_D *
    heli_q8_final_B.TravelCounttorad;

  /* ManualSwitch: '<S1>/Estimates//Encoder' */
  if (heli_q8_final_P.EstimatesEncoder_CurrentSetting == 1) {
    /* ManualSwitch: '<S1>/Estimates//Encoder' */
    heli_q8_final_B.EstimatesEncoder[0] = heli_q8_final_B.x_hat[4];
    heli_q8_final_B.EstimatesEncoder[1] = heli_q8_final_B.x_hat[5];
    heli_q8_final_B.EstimatesEncoder[2] = heli_q8_final_B.x_hat[0];
    heli_q8_final_B.EstimatesEncoder[3] = heli_q8_final_B.x_hat[1];
    heli_q8_final_B.EstimatesEncoder[4] = heli_q8_final_B.x_hat[2];
    heli_q8_final_B.EstimatesEncoder[5] = heli_q8_final_B.x_hat[3];
  } else {
    /* ManualSwitch: '<S1>/Estimates//Encoder' */
    heli_q8_final_B.EstimatesEncoder[0] = heli_q8_final_B.TravelCounttorad;
    heli_q8_final_B.EstimatesEncoder[1] = heli_q8_final_B.TravelTransferFcn;
    heli_q8_final_B.EstimatesEncoder[2] = heli_q8_final_B.PitchCounttorad;
    heli_q8_final_B.EstimatesEncoder[3] = heli_q8_final_B.PitchTransferFcn;
    heli_q8_final_B.EstimatesEncoder[4] = heli_q8_final_B.Sum_d;
    heli_q8_final_B.EstimatesEncoder[5] = heli_q8_final_B.ElevationTransferFcn;
  }

  /* End of ManualSwitch: '<S1>/Estimates//Encoder' */

  /* Integrator: '<S9>/Integrator' */
  heli_q8_final_B.Integrator = heli_q8_final_X.Integrator_CSTATE;

  /* Integrator: '<S9>/Integrator1' */
  heli_q8_final_B.Integrator1 = heli_q8_final_X.Integrator1_CSTATE;

  /* SignalConversion generated from: '<S9>/Transpose1' */
  tmp_5[2] = heli_q8_final_B.EstimatesEncoder[5];
  tmp_5[3] = heli_q8_final_B.Integrator;
  tmp_5[4] = heli_q8_final_B.Integrator1;
  tmp_5[0] = heli_q8_final_B.EstimatesEncoder[2];

  /* Gain: '<S9>/Gain' incorporates:
   *  SignalConversion generated from: '<S9>/Transpose'
   */
  tmp_1[0] = heli_q8_final_P.F[0] * heli_q8_final_B.p_c + heli_q8_final_P.F[2] *
    heli_q8_final_B.Sum;

  /* SignalConversion generated from: '<S9>/Transpose1' */
  tmp_5[1] = heli_q8_final_B.EstimatesEncoder[3];

  /* Gain: '<S9>/Gain' incorporates:
   *  SignalConversion generated from: '<S9>/Transpose'
   */
  tmp_1[1] = heli_q8_final_P.F[1] * heli_q8_final_B.p_c;
  tmp_1[1] += heli_q8_final_P.F[3] * heli_q8_final_B.Sum;
  for (i = 0; i < 2; i++) {
    /* Gain: '<S9>/Gain1' */
    tmp_2[i] = 0.0;
    for (c_j = 0; c_j < 5; c_j++) {
      tmp_2[i] += heli_q8_final_P.K[(c_j << 1) + i] * tmp_5[c_j];
    }

    /* End of Gain: '<S9>/Gain1' */

    /* Sum: '<S9>/Sum' */
    heli_q8_final_B.Sum_j[i] = tmp_1[i] - tmp_2[i];
  }

  /* Sum: '<S9>/Sum3' incorporates:
   *  Constant: '<S9>/Constant'
   */
  rtb_ManualSwitch5 = heli_q8_final_P.V_s0 + heli_q8_final_B.Sum_j[0];

  /* Gain: '<S3>/Front gain' incorporates:
   *  Sum: '<S3>/Add'
   */
  rtb_PulseGenerator2 = (rtb_ManualSwitch5 - heli_q8_final_B.Sum_j[1]) *
    heli_q8_final_P.Frontgain_Gain;

  /* Saturate: '<S5>/Front motor: Saturation' */
  if (rtb_PulseGenerator2 > heli_q8_final_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    heli_q8_final_B.FrontmotorSaturation =
      heli_q8_final_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_PulseGenerator2 < heli_q8_final_P.FrontmotorSaturation_LowerSat)
  {
    /* Saturate: '<S5>/Front motor: Saturation' */
    heli_q8_final_B.FrontmotorSaturation =
      heli_q8_final_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Front motor: Saturation' */
    heli_q8_final_B.FrontmotorSaturation = rtb_PulseGenerator2;
  }

  /* End of Saturate: '<S5>/Front motor: Saturation' */

  /* Gain: '<S3>/Back gain' incorporates:
   *  Sum: '<S3>/Subtract'
   */
  rtb_PulseGenerator2 = (rtb_ManualSwitch5 + heli_q8_final_B.Sum_j[1]) *
    heli_q8_final_P.Backgain_Gain;

  /* Saturate: '<S5>/Back motor: Saturation' */
  if (rtb_PulseGenerator2 > heli_q8_final_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    heli_q8_final_B.BackmotorSaturation =
      heli_q8_final_P.BackmotorSaturation_UpperSat;
  } else if (rtb_PulseGenerator2 < heli_q8_final_P.BackmotorSaturation_LowerSat)
  {
    /* Saturate: '<S5>/Back motor: Saturation' */
    heli_q8_final_B.BackmotorSaturation =
      heli_q8_final_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Back motor: Saturation' */
    heli_q8_final_B.BackmotorSaturation = rtb_PulseGenerator2;
  }

  /* End of Saturate: '<S5>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* SignalConversion generated from: '<S1>/To File1' */
    rtb_TmpSignalConversionAtToFile[0] = heli_q8_final_B.FrontmotorSaturation;
    rtb_TmpSignalConversionAtToFile[1] = heli_q8_final_B.BackmotorSaturation;
    rtb_TmpSignalConversionAtToFile[2] = heli_q8_final_B.p_c;
    rtb_TmpSignalConversionAtToFile[3] = heli_q8_final_B.Sum;
    rtb_TmpSignalConversionAtToFile[4] = heli_q8_final_B.TravelCounttorad;
    rtb_TmpSignalConversionAtToFile[5] = heli_q8_final_B.TravelTransferFcn;
    rtb_TmpSignalConversionAtToFile[6] = heli_q8_final_B.PitchCounttorad;
    rtb_TmpSignalConversionAtToFile[7] = heli_q8_final_B.PitchTransferFcn;
    rtb_TmpSignalConversionAtToFile[8] = heli_q8_final_B.Sum_d;
    rtb_TmpSignalConversionAtToFile[9] = heli_q8_final_B.ElevationTransferFcn;
    rtb_TmpSignalConversionAtToFile[10] = heli_q8_final_B.x_hat[4];
    rtb_TmpSignalConversionAtToFile[11] = heli_q8_final_B.x_hat[5];
    rtb_TmpSignalConversionAtToFile[12] = heli_q8_final_B.x_hat[0];
    rtb_TmpSignalConversionAtToFile[13] = heli_q8_final_B.x_hat[1];
    rtb_TmpSignalConversionAtToFile[14] = heli_q8_final_B.x_hat[2];
    rtb_TmpSignalConversionAtToFile[15] = heli_q8_final_B.x_hat[3];
    rtb_TmpSignalConversionAtToFile[16] = heli_q8_final_B.euler_angles[0];
    rtb_TmpSignalConversionAtToFile[17] = heli_q8_final_B.euler_angles[1];
    rtb_TmpSignalConversionAtToFile[18] = heli_q8_final_B.euler_rates[0];
    rtb_TmpSignalConversionAtToFile[19] = heli_q8_final_B.euler_rates[1];
    rtb_TmpSignalConversionAtToFile[20] = heli_q8_final_B.euler_rates[2];

    /* ToFile: '<S1>/To File1' */
    if (rtmIsMajorTimeStep(heli_q8_final_M)) {
      if (rtmIsMajorTimeStep(heli_q8_final_M) ) {
        {
          if (!(++heli_q8_final_DW.ToFile1_IWORK.Decimation % 1) &&
              (heli_q8_final_DW.ToFile1_IWORK.Count * (21 + 1)) + 1 < 100000000 )
          {
            FILE *fp = (FILE *) heli_q8_final_DW.ToFile1_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[21 + 1];
              heli_q8_final_DW.ToFile1_IWORK.Decimation = 0;
              u[0] = heli_q8_final_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtToFile[0];
              u[2] = rtb_TmpSignalConversionAtToFile[1];
              u[3] = rtb_TmpSignalConversionAtToFile[2];
              u[4] = rtb_TmpSignalConversionAtToFile[3];
              u[5] = rtb_TmpSignalConversionAtToFile[4];
              u[6] = rtb_TmpSignalConversionAtToFile[5];
              u[7] = rtb_TmpSignalConversionAtToFile[6];
              u[8] = rtb_TmpSignalConversionAtToFile[7];
              u[9] = rtb_TmpSignalConversionAtToFile[8];
              u[10] = rtb_TmpSignalConversionAtToFile[9];
              u[11] = rtb_TmpSignalConversionAtToFile[10];
              u[12] = rtb_TmpSignalConversionAtToFile[11];
              u[13] = rtb_TmpSignalConversionAtToFile[12];
              u[14] = rtb_TmpSignalConversionAtToFile[13];
              u[15] = rtb_TmpSignalConversionAtToFile[14];
              u[16] = rtb_TmpSignalConversionAtToFile[15];
              u[17] = rtb_TmpSignalConversionAtToFile[16];
              u[18] = rtb_TmpSignalConversionAtToFile[17];
              u[19] = rtb_TmpSignalConversionAtToFile[18];
              u[20] = rtb_TmpSignalConversionAtToFile[19];
              u[21] = rtb_TmpSignalConversionAtToFile[20];
              if (fwrite(u, sizeof(real_T), 21 + 1, fp) != 21 + 1) {
                rtmSetErrorStatus(heli_q8_final_M,
                                  "Error writing to MAT-file Test.mat");
                return;
              }

              if (((++heli_q8_final_DW.ToFile1_IWORK.Count) * (21 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file Test.mat.\n");
              }
            }
          }
        }
      }
    }

    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: heli_q8_final/Lab_4/Heli 3D1/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      heli_q8_final_DW.HILWriteAnalog_Buffer[0] =
        heli_q8_final_B.FrontmotorSaturation;
      heli_q8_final_DW.HILWriteAnalog_Buffer[1] =
        heli_q8_final_B.BackmotorSaturation;
      result = hil_write_analog(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILWriteAnalog_channels, 2,
        &heli_q8_final_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      }
    }

    /* S-Function (stop_with_error_block): '<S6>/Stop with Call Error' */

    /* S-Function Block: heli_q8_final/Lab_4/IMU1/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }
  }

  /* SignalConversion generated from: '<S12>/ SFunction ' incorporates:
   *  MATLAB Function: '<S8>/Kalman Prediction'
   */
  /* MATLAB Function 'Lab_4/Kalman Filter1/Kalman Prediction': '<S12>:1' */
  /* '<S12>:1:2' */
  euler_rates_pre_offset_tmp = heli_q8_final_B.Sum_j[1];

  /* MATLAB Function: '<S8>/Kalman Prediction' incorporates:
   *  Constant: '<S8>/Constant2'
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant4'
   *  SignalConversion generated from: '<S12>/ SFunction '
   */
  /* '<S12>:1:3' */
  for (i = 0; i < 6; i++) {
    tmp_4[i] = 0.0;
    for (c_j = 0; c_j < 6; c_j++) {
      iy = 6 * c_j + i;
      P_hat_tmp_0[iy] = 0.0;
      for (ix = 0; ix < 6; ix++) {
        P_hat_tmp_0[iy] += heli_q8_final_P.A_d[6 * ix + i] *
          heli_q8_final_B.P_hat[6 * c_j + ix];
      }

      tmp_4[i] += heli_q8_final_P.A_d[iy] * heli_q8_final_B.x_hat[c_j];
    }

    heli_q8_final_B.x_bar[i] = tmp_4[i] + (heli_q8_final_P.B_d[i + 6] *
      rtb_ManualSwitch5 + heli_q8_final_P.B_d[i] * euler_rates_pre_offset_tmp);
    for (c_j = 0; c_j < 6; c_j++) {
      rtb_PulseGenerator2 = 0.0;
      for (iy = 0; iy < 6; iy++) {
        rtb_PulseGenerator2 += P_hat_tmp_0[6 * iy + i] * heli_q8_final_P.A_d[6 *
          iy + c_j];
      }

      iy = 6 * c_j + i;
      heli_q8_final_B.P_bar[iy] = heli_q8_final_P.Q_d[iy] + rtb_PulseGenerator2;
    }
  }

  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
  }

  /* Sum: '<S9>/Sum1' */
  heli_q8_final_B.Sum1 = heli_q8_final_B.p_c - heli_q8_final_B.EstimatesEncoder
    [2];

  /* Sum: '<S9>/Sum2' */
  heli_q8_final_B.Sum2 = heli_q8_final_B.Sum - heli_q8_final_B.EstimatesEncoder
    [5];
}

/* Model update function for TID0 */
void heli_q8_final_update0(void)       /* Sample time: [0.0s, 0.0s] */
{
  int32_T i;
  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    /* Update for Memory: '<S6>/Memory' */
    memcpy(&heli_q8_final_DW.Memory_PreviousInput[0], &heli_q8_final_B.Switch[0],
           10U * sizeof(real_T));

    /* Update for UnitDelay: '<S8>/Unit Delay1' */
    for (i = 0; i < 6; i++) {
      heli_q8_final_DW.UnitDelay1_DSTATE[i] = heli_q8_final_B.x_bar[i];
    }

    /* End of Update for UnitDelay: '<S8>/Unit Delay1' */

    /* Update for UnitDelay: '<S8>/Unit Delay' */
    memcpy(&heli_q8_final_DW.UnitDelay_DSTATE[0], &heli_q8_final_B.P_bar[0], 36U
           * sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(heli_q8_final_M)) {
    rt_ertODEUpdateContinuousStates(&heli_q8_final_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_final_M->Timing.clockTick0)) {
    ++heli_q8_final_M->Timing.clockTickH0;
  }

  heli_q8_final_M->Timing.t[0] = rtsiGetSolverStopTime
    (&heli_q8_final_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_final_M->Timing.clockTick1)) {
    ++heli_q8_final_M->Timing.clockTickH1;
  }

  heli_q8_final_M->Timing.t[1] = heli_q8_final_M->Timing.clockTick1 *
    heli_q8_final_M->Timing.stepSize1 + heli_q8_final_M->Timing.clockTickH1 *
    heli_q8_final_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void heli_q8_final_derivatives(void)
{
  XDot_heli_q8_final_T *_rtXdot;
  _rtXdot = ((XDot_heli_q8_final_T *) heli_q8_final_M->derivs);

  /* Derivatives for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_final_P.ElevationTransferFcn_A
    * heli_q8_final_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_q8_final_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_final_P.PitchTransferFcn_A *
    heli_q8_final_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += heli_q8_final_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_final_P.TravelTransferFcn_A *
    heli_q8_final_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += heli_q8_final_B.TravelCounttorad;

  /* Derivatives for Integrator: '<S9>/Integrator' */
  _rtXdot->Integrator_CSTATE = heli_q8_final_B.Sum1;

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = heli_q8_final_B.Sum2;
}

/* Model output function for TID2 */
void heli_q8_final_output2(void)       /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S7>/Game Controller' */

  /* S-Function Block: heli_q8_final/Lab_4/Joystick1/Game Controller (game_controller_block) */
  {
    if (heli_q8_final_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(heli_q8_final_DW.GameController_Controller,
        &state, &new_data);
      if (result < 0) {
        new_data = false;
      }

      rtb_GameController_o4 = state.x;
      rtb_GameController_o5 = state.y;
    } else {
      rtb_GameController_o4 = 0;
      rtb_GameController_o5 = 0;
    }
  }

  /* RateTransition: '<S7>/Rate Transition: x' */
  heli_q8_final_DW.RateTransitionx_Buffer0 = rtb_GameController_o4;

  /* RateTransition: '<S7>/Rate Transition: y' */
  heli_q8_final_DW.RateTransitiony_Buffer0 = rtb_GameController_o5;
}

/* Model update function for TID2 */
void heli_q8_final_update2(void)       /* Sample time: [0.01s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_q8_final_M->Timing.clockTick2)) {
    ++heli_q8_final_M->Timing.clockTickH2;
  }

  heli_q8_final_M->Timing.t[2] = heli_q8_final_M->Timing.clockTick2 *
    heli_q8_final_M->Timing.stepSize2 + heli_q8_final_M->Timing.clockTickH2 *
    heli_q8_final_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void heli_q8_final_output(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_final_output0();
    break;

   case 2 :
    heli_q8_final_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void heli_q8_final_update(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_q8_final_update0();
    break;

   case 2 :
    heli_q8_final_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void heli_q8_final_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8_final/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &heli_q8_final_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(heli_q8_final_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(heli_q8_final_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      return;
    }

    if ((heli_q8_final_P.HILInitialize_AIPStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &heli_q8_final_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (heli_q8_final_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &heli_q8_final_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = heli_q8_final_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_AIChannels, 8U,
        &heli_q8_final_DW.HILInitialize_AIMinimums[0],
        &heli_q8_final_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_AOPStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &heli_q8_final_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (heli_q8_final_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &heli_q8_final_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = heli_q8_final_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_AOChannels, 8U,
        &heli_q8_final_DW.HILInitialize_AOMinimums[0],
        &heli_q8_final_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_AOStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_final_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_final_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_AOChannels, 8U,
        &heli_q8_final_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_final_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_final_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_final_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (heli_q8_final_DW.HILInitialize_Card,
         heli_q8_final_P.HILInitialize_AOChannels, 8U,
         &heli_q8_final_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_EIPStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &heli_q8_final_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = heli_q8_final_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (heli_q8_final_DW.HILInitialize_Card,
         heli_q8_final_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &heli_q8_final_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_EIStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &heli_q8_final_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = heli_q8_final_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_EIChannels, 8U,
        &heli_q8_final_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_POPStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_final_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_final_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &heli_q8_final_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          heli_q8_final_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &heli_q8_final_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            heli_q8_final_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            heli_q8_final_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              heli_q8_final_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            heli_q8_final_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            heli_q8_final_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = heli_q8_final_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(heli_q8_final_DW.HILInitialize_Card,
          &heli_q8_final_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &heli_q8_final_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(heli_q8_final_DW.HILInitialize_Card,
          &heli_q8_final_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &heli_q8_final_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_q8_final_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_q8_final_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &heli_q8_final_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = heli_q8_final_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &heli_q8_final_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = heli_q8_final_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &heli_q8_final_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &heli_q8_final_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &heli_q8_final_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &heli_q8_final_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = heli_q8_final_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_final_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_final_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_POChannels, 8U,
        &heli_q8_final_DW.HILInitialize_POSortedFreqs[0],
        &heli_q8_final_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if ((heli_q8_final_P.HILInitialize_POStart && !is_switching) ||
        (heli_q8_final_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_final_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_final_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(heli_q8_final_DW.HILInitialize_Card,
        heli_q8_final_P.HILInitialize_POChannels, 8U,
        &heli_q8_final_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }

    if (heli_q8_final_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_final_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_final_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (heli_q8_final_DW.HILInitialize_Card,
         heli_q8_final_P.HILInitialize_POChannels, 8U,
         &heli_q8_final_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: heli_q8_final/Lab_4/Heli 3D1/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(heli_q8_final_DW.HILInitialize_Card,
      heli_q8_final_P.HILReadEncoderTimebase_SamplesI,
      heli_q8_final_P.HILReadEncoderTimebase_Channels, 3,
      &heli_q8_final_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (heli_q8_final_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (heli_q8_final_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
    }
  }

  /* Start for DiscretePulseGenerator: '<S1>/Pulse Generator1' */
  heli_q8_final_DW.clockTickCounter = 5000 - (int32_T)
    (heli_q8_final_P.PulseGenerator1_Period * (real_T)div_s32(5000, (int32_T)
      heli_q8_final_P.PulseGenerator1_Period));

  /* Start for RateTransition: '<S7>/Rate Transition: x' */
  heli_q8_final_B.RateTransitionx =
    heli_q8_final_P.RateTransitionx_InitialConditio;

  /* Start for RateTransition: '<S7>/Rate Transition: y' */
  heli_q8_final_B.RateTransitiony =
    heli_q8_final_P.RateTransitiony_InitialConditio;

  /* Start for DiscretePulseGenerator: '<S1>/Pulse Generator2' */
  heli_q8_final_DW.clockTickCounter_j = 0;

  /* Start for S-Function (stream_call_block): '<S6>/Stream Call1' incorporates:
   *  Constant: '<S6>/Constant'
   *  S-Function (string_constant_block): '<S6>/String Constant'
   */

  /* S-Function Block: heli_q8_final/Lab_4/IMU1/Stream Call1 (stream_call_block) */
  {
    heli_q8_final_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    heli_q8_final_DW.StreamCall1_Stream = NULL;
  }

  /* Start for ToFile: '<S1>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Test.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_q8_final_M, "Error creating .mat file Test.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 21 + 1, 0, "ans")) {
      rtmSetErrorStatus(heli_q8_final_M,
                        "Error writing mat file header to file Test.mat");
      return;
    }

    heli_q8_final_DW.ToFile1_IWORK.Count = 0;
    heli_q8_final_DW.ToFile1_IWORK.Decimation = -1;
    heli_q8_final_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (game_controller_block): '<S7>/Game Controller' */

  /* S-Function Block: heli_q8_final/Lab_4/Joystick1/Game Controller (game_controller_block) */
  {
    if (heli_q8_final_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open
        (heli_q8_final_P.GameController_ControllerNumber,
         heli_q8_final_P.GameController_BufferSize, deadzone, saturation,
         heli_q8_final_P.GameController_AutoCenter, 0, 1.0,
         &heli_q8_final_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
      }
    }
  }

  {
    int32_T i;

    /* InitializeConditions for RateTransition: '<S7>/Rate Transition: x' */
    heli_q8_final_DW.RateTransitionx_Buffer0 =
      heli_q8_final_P.RateTransitionx_InitialConditio;

    /* InitializeConditions for RateTransition: '<S7>/Rate Transition: y' */
    heli_q8_final_DW.RateTransitiony_Buffer0 =
      heli_q8_final_P.RateTransitiony_InitialConditio;

    /* InitializeConditions for Memory: '<S6>/Memory' */
    memcpy(&heli_q8_final_DW.Memory_PreviousInput[0],
           &heli_q8_final_P.Memory_InitialCondition[0], 10U * sizeof(real_T));

    /* InitializeConditions for UnitDelay: '<S8>/Unit Delay1' */
    for (i = 0; i < 6; i++) {
      heli_q8_final_DW.UnitDelay1_DSTATE[i] =
        heli_q8_final_P.UnitDelay1_InitialCondition[i];
    }

    /* End of InitializeConditions for UnitDelay: '<S8>/Unit Delay1' */

    /* InitializeConditions for UnitDelay: '<S8>/Unit Delay' */
    for (i = 0; i < 36; i++) {
      heli_q8_final_DW.UnitDelay_DSTATE[i] =
        heli_q8_final_P.UnitDelay_InitialCondition;
    }

    /* End of InitializeConditions for UnitDelay: '<S8>/Unit Delay' */

    /* InitializeConditions for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
    heli_q8_final_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
    heli_q8_final_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S5>/Travel: Transfer Fcn' */
    heli_q8_final_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S9>/Integrator' */
    heli_q8_final_X.Integrator_CSTATE = heli_q8_final_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S9>/Integrator1' */
    heli_q8_final_X.Integrator1_CSTATE = heli_q8_final_P.Integrator1_IC;
  }
}

/* Model terminate function */
void heli_q8_final_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_q8_final/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(heli_q8_final_DW.HILInitialize_Card);
    hil_monitor_stop_all(heli_q8_final_DW.HILInitialize_Card);
    is_switching = false;
    if ((heli_q8_final_P.HILInitialize_AOTerminate && !is_switching) ||
        (heli_q8_final_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_q8_final_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_q8_final_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((heli_q8_final_P.HILInitialize_POTerminate && !is_switching) ||
        (heli_q8_final_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_q8_final_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_q8_final_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(heli_q8_final_DW.HILInitialize_Card
                         , heli_q8_final_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , heli_q8_final_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &heli_q8_final_DW.HILInitialize_AOVoltages[0]
                         , &heli_q8_final_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(heli_q8_final_DW.HILInitialize_Card,
            heli_q8_final_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &heli_q8_final_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(heli_q8_final_DW.HILInitialize_Card,
            heli_q8_final_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &heli_q8_final_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_q8_final_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(heli_q8_final_DW.HILInitialize_Card);
    hil_monitor_delete_all(heli_q8_final_DW.HILInitialize_Card);
    hil_close(heli_q8_final_DW.HILInitialize_Card);
    heli_q8_final_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (stream_call_block): '<S6>/Stream Call1' incorporates:
   *  Constant: '<S6>/Constant'
   *  S-Function (string_constant_block): '<S6>/String Constant'
   */

  /* S-Function Block: heli_q8_final/Lab_4/IMU1/Stream Call1 (stream_call_block) */
  {
    if (heli_q8_final_DW.StreamCall1_Stream != NULL) {
      stream_close(heli_q8_final_DW.StreamCall1_Stream);
      heli_q8_final_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<S1>/To File1' */
  {
    FILE *fp = (FILE *) heli_q8_final_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Test.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_final_M, "Error closing MAT-file Test.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_q8_final_M, "Error reopening MAT-file Test.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 21 + 1,
           heli_q8_final_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(heli_q8_final_M,
                          "Error writing header for ans to MAT-file Test.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_q8_final_M, "Error closing MAT-file Test.mat");
        return;
      }

      heli_q8_final_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S7>/Game Controller' */

  /* S-Function Block: heli_q8_final/Lab_4/Joystick1/Game Controller (game_controller_block) */
  {
    if (heli_q8_final_P.GameController_Enabled) {
      game_controller_close(heli_q8_final_DW.GameController_Controller);
      heli_q8_final_DW.GameController_Controller = NULL;
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_q8_final_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_q8_final_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  heli_q8_final_initialize();
}

void MdlTerminate(void)
{
  heli_q8_final_terminate();
}

/* Registration function */
RT_MODEL_heli_q8_final_T *heli_q8_final(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)heli_q8_final_M, 0,
                sizeof(RT_MODEL_heli_q8_final_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&heli_q8_final_M->solverInfo,
                          &heli_q8_final_M->Timing.simTimeStep);
    rtsiSetTPtr(&heli_q8_final_M->solverInfo, &rtmGetTPtr(heli_q8_final_M));
    rtsiSetStepSizePtr(&heli_q8_final_M->solverInfo,
                       &heli_q8_final_M->Timing.stepSize0);
    rtsiSetdXPtr(&heli_q8_final_M->solverInfo, &heli_q8_final_M->derivs);
    rtsiSetContStatesPtr(&heli_q8_final_M->solverInfo, (real_T **)
                         &heli_q8_final_M->contStates);
    rtsiSetNumContStatesPtr(&heli_q8_final_M->solverInfo,
      &heli_q8_final_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&heli_q8_final_M->solverInfo,
      &heli_q8_final_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&heli_q8_final_M->solverInfo,
      &heli_q8_final_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&heli_q8_final_M->solverInfo,
      &heli_q8_final_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&heli_q8_final_M->solverInfo, (&rtmGetErrorStatus
      (heli_q8_final_M)));
    rtsiSetRTModelPtr(&heli_q8_final_M->solverInfo, heli_q8_final_M);
  }

  rtsiSetSimTimeStep(&heli_q8_final_M->solverInfo, MAJOR_TIME_STEP);
  heli_q8_final_M->intgData.f[0] = heli_q8_final_M->odeF[0];
  heli_q8_final_M->contStates = ((real_T *) &heli_q8_final_X);
  rtsiSetSolverData(&heli_q8_final_M->solverInfo, (void *)
                    &heli_q8_final_M->intgData);
  rtsiSetSolverName(&heli_q8_final_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = heli_q8_final_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    heli_q8_final_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    heli_q8_final_M->Timing.sampleTimes =
      (&heli_q8_final_M->Timing.sampleTimesArray[0]);
    heli_q8_final_M->Timing.offsetTimes =
      (&heli_q8_final_M->Timing.offsetTimesArray[0]);

    /* task periods */
    heli_q8_final_M->Timing.sampleTimes[0] = (0.0);
    heli_q8_final_M->Timing.sampleTimes[1] = (0.002);
    heli_q8_final_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    heli_q8_final_M->Timing.offsetTimes[0] = (0.0);
    heli_q8_final_M->Timing.offsetTimes[1] = (0.0);
    heli_q8_final_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(heli_q8_final_M, &heli_q8_final_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = heli_q8_final_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = heli_q8_final_M->Timing.perTaskSampleHitsArray;
    heli_q8_final_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    heli_q8_final_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(heli_q8_final_M, -1);
  heli_q8_final_M->Timing.stepSize0 = 0.002;
  heli_q8_final_M->Timing.stepSize1 = 0.002;
  heli_q8_final_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  heli_q8_final_M->Sizes.checksums[0] = (1120882639U);
  heli_q8_final_M->Sizes.checksums[1] = (2406549812U);
  heli_q8_final_M->Sizes.checksums[2] = (3097751148U);
  heli_q8_final_M->Sizes.checksums[3] = (14917709U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[9];
    heli_q8_final_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(heli_q8_final_M->extModeInfo,
      &heli_q8_final_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(heli_q8_final_M->extModeInfo,
                        heli_q8_final_M->Sizes.checksums);
    rteiSetTPtr(heli_q8_final_M->extModeInfo, rtmGetTPtr(heli_q8_final_M));
  }

  heli_q8_final_M->solverInfoPtr = (&heli_q8_final_M->solverInfo);
  heli_q8_final_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&heli_q8_final_M->solverInfo, 0.002);
  rtsiSetSolverMode(&heli_q8_final_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  heli_q8_final_M->blockIO = ((void *) &heli_q8_final_B);
  (void) memset(((void *) &heli_q8_final_B), 0,
                sizeof(B_heli_q8_final_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_final_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_final_B.EstimatesEncoder[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_final_B.x_bar[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_final_B.P_bar[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      heli_q8_final_B.x_hat[i] = 0.0;
    }

    for (i = 0; i < 36; i++) {
      heli_q8_final_B.P_hat[i] = 0.0;
    }

    heli_q8_final_B.Sum9 = 0.0;
    heli_q8_final_B.RateTransitionx = 0.0;
    heli_q8_final_B.Joystick_gain_x = 0.0;
    heli_q8_final_B.p_c = 0.0;
    heli_q8_final_B.RateTransitiony = 0.0;
    heli_q8_final_B.Joystick_gain_y = 0.0;
    heli_q8_final_B.Sum7 = 0.0;
    heli_q8_final_B.Sum = 0.0;
    heli_q8_final_B.PitchCounttorad = 0.0;
    heli_q8_final_B.ElevationCounttorad = 0.0;
    heli_q8_final_B.ElevationTransferFcn = 0.0;
    heli_q8_final_B.PitchTransferFcn = 0.0;
    heli_q8_final_B.Sum_d = 0.0;
    heli_q8_final_B.TravelCounttorad = 0.0;
    heli_q8_final_B.TravelTransferFcn = 0.0;
    heli_q8_final_B.Integrator = 0.0;
    heli_q8_final_B.Integrator1 = 0.0;
    heli_q8_final_B.Sum_j[0] = 0.0;
    heli_q8_final_B.Sum_j[1] = 0.0;
    heli_q8_final_B.FrontmotorSaturation = 0.0;
    heli_q8_final_B.BackmotorSaturation = 0.0;
    heli_q8_final_B.Sum1 = 0.0;
    heli_q8_final_B.Sum2 = 0.0;
    heli_q8_final_B.euler_rates[0] = 0.0;
    heli_q8_final_B.euler_rates[1] = 0.0;
    heli_q8_final_B.euler_rates[2] = 0.0;
    heli_q8_final_B.euler_angles[0] = 0.0;
    heli_q8_final_B.euler_angles[1] = 0.0;
  }

  /* parameters */
  heli_q8_final_M->defaultParam = ((real_T *)&heli_q8_final_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &heli_q8_final_X;
    heli_q8_final_M->contStates = (x);
    (void) memset((void *)&heli_q8_final_X, 0,
                  sizeof(X_heli_q8_final_T));
  }

  /* states (dwork) */
  heli_q8_final_M->dwork = ((void *) &heli_q8_final_DW);
  (void) memset((void *)&heli_q8_final_DW, 0,
                sizeof(DW_heli_q8_final_T));

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      heli_q8_final_DW.UnitDelay1_DSTATE[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 36; i++) {
      heli_q8_final_DW.UnitDelay_DSTATE[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_q8_final_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  heli_q8_final_DW.RateTransitionx_Buffer0 = 0.0;
  heli_q8_final_DW.RateTransitiony_Buffer0 = 0.0;

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      heli_q8_final_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  heli_q8_final_DW.HILWriteAnalog_Buffer[0] = 0.0;
  heli_q8_final_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    heli_q8_final_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  heli_q8_final_M->Sizes.numContStates = (5);/* Number of continuous states */
  heli_q8_final_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  heli_q8_final_M->Sizes.numY = (0);   /* Number of model outputs */
  heli_q8_final_M->Sizes.numU = (0);   /* Number of model inputs */
  heli_q8_final_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  heli_q8_final_M->Sizes.numSampTimes = (3);/* Number of sample times */
  heli_q8_final_M->Sizes.numBlocks = (118);/* Number of blocks */
  heli_q8_final_M->Sizes.numBlockIO = (31);/* Number of block outputs */
  heli_q8_final_M->Sizes.numBlockPrms = (629);/* Sum of parameter "widths" */
  return heli_q8_final_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
