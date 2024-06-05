/*
 * File: FOC_Model.c
 *
 * Code generated for Simulink model 'FOC_Model'.
 *
 * Model version                  : 1.22
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon May 13 09:06:48 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "FOC_Model.h"

/* Named constants for Chart: '<S2>/Chart1' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_OpenStage                   ((uint8_T)3U)
#define IN_RunStage                    ((uint8_T)4U)
#define IN_ThetaAlign                  ((uint8_T)5U)
#define NumBitsPerChar                 8U
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Exported block signals */
real32_T FluxTheta;                     /* '<S21>/Mod' */
real32_T FluxWm;                        /* '<S20>/Plus1' */
real32_T ialpha;                       /* '<S6>/Add1' */
real32_T state;                        /* '<S2>/Chart1' */

/* Exported data definition */

/* Definition for custom storage class: Struct */
Gramma_type Gramma = {
  /* Gamma */
  10000.0F
};

LPFFilter_type LPFFilter = {
  /* LPFFilter */
  0.3F
};

PLL_type PLL = {
  /* PLLKI */
  640000.0F,

  /* PLLKP */
  1131.0F
};

curr_kpki_type curr_kpki = {
  /* curr_d_ki */
  35.0F,

  /* curr_d_kp */
  0.05F
};

motor_type motor = {
  /* L */
  0.00535F,

  /* Pn */
  2.0F,

  /* Rs */
  6.97F,

  /* flux */
  0.008442F
};

spd_kpki_type spd_kpki = {
  /* spd_ki */
  0.00144F,

  /* spd_kp */
  0.03389F
};

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real32_T rt_modf_snf(real32_T u0, real32_T u1);
static real32_T sMultiWord2Single(const uint64_T u1[], int32_T n1, int32_T e1);
static void sMultiWordMul(const uint64_T u1[], int32_T n1, const uint64_T u2[],
  int32_T n2, uint64_T y[], int32_T n);
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3]);
static void Clark_test(void);
static void rate_scheduler(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

static real32_T sMultiWord2Single(const uint64_T u1[], int32_T n1, int32_T e1)
{
  int32_T exp_0;
  int32_T i;
  real32_T y;
  y = 0.0F;
  exp_0 = e1;
  if ((u1[n1 - 1] & 9223372036854775808ULL) != 0ULL) {
    uint64_T cb;
    cb = 1ULL;
    for (i = 0; i < n1; i++) {
      uint64_T u1i;
      u1i = ~u1[i];
      cb += u1i;
      y -= (real32_T)ldexp((real32_T)cb, exp_0);
      cb = (uint64_T)(cb < u1i);
      exp_0 += 64;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += (real32_T)ldexp((real32_T)u1[i], exp_0);
      exp_0 += 64;
    }
  }

  return y;
}

static void sMultiWordMul(const uint64_T u1[], int32_T n1, const uint64_T u2[],
  int32_T n2, uint64_T y[], int32_T n)
{
  uint64_T cb;
  uint64_T cb1;
  uint64_T yk;
  int32_T i;
  int32_T j;
  int32_T k;
  boolean_T isNegative1;
  boolean_T isNegative2;
  isNegative1 = ((u1[n1 - 1] & 9223372036854775808ULL) != 0ULL);
  isNegative2 = ((u2[n2 - 1] & 9223372036854775808ULL) != 0ULL);
  cb1 = 1ULL;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0ULL;
  }

  for (i = 0; i < n1; i++) {
    uint64_T a0;
    uint64_T a1;
    uint64_T cb2;
    uint64_T u1i;
    int32_T ni;
    cb = 0ULL;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint64_T)(u1i < cb1);
    }

    a1 = u1i >> 32U;
    a0 = u1i & 4294967295ULL;
    cb2 = 1ULL;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      uint64_T b1;
      uint64_T w01;
      uint64_T w10;
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint64_T)(u1i < cb2);
      }

      b1 = u1i >> 32U;
      u1i &= 4294967295ULL;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint64_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 32U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 32U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 32U;
      cb += w01 >> 32U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1ULL;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint64_T)(yk < cb);
    }
  }
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[1])++;
  if ((rtM->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.001s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Output and update for atomic system: '<S2>/Clark_test' */
static void Clark_test(void)
{
  /* Sum: '<S6>/Add1' incorporates:
   *  Gain: '<S6>/Gain'
   *  Gain: '<S6>/Gain1'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S6>/Add'
   */
  ialpha = 0.666666687F * rtU.ia - (rtU.ib + rtU.ic) * 0.333333343F;

  /* Outport: '<Root>/Tcmp3' incorporates:
   *  Gain: '<S6>/Gain2'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S6>/Add2'
   */
  rtY.Tcmp3 = (rtU.ib - rtU.ic) * 0.577350259F;
}

/* Output and update for atomic system: '<S2>/SVPWM' */
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3])
{
  real32_T rtb_Min;
  real32_T rtb_Sum1_k;
  real32_T rtb_Sum_n;

  /* Gain: '<S174>/Gain' */
  rtb_Min = -0.5F * rtu_Valpha;

  /* Gain: '<S174>/Gain1' */
  rtb_Sum1_k = 0.866025388F * rtu_Vbeta;

  /* Sum: '<S174>/Sum' */
  rtb_Sum_n = rtb_Min + rtb_Sum1_k;

  /* Sum: '<S174>/Sum1' */
  rtb_Sum1_k = rtb_Min - rtb_Sum1_k;

  /* Gain: '<S175>/Gain' incorporates:
   *  MinMax: '<S175>/Min'
   *  MinMax: '<S175>/Min1'
   *  Sum: '<S175>/Sum'
   */
  rtb_Min = (fminf(fminf(rtu_Valpha, rtb_Sum_n), rtb_Sum1_k) + fmaxf(fmaxf
              (rtu_Valpha, rtb_Sum_n), rtb_Sum1_k)) * -0.5F;

  /* Gain: '<S15>/PWM_HalfPeriod' incorporates:
   *  Constant: '<S15>/Constant'
   *  Gain: '<S15>/Gain'
   *  Product: '<S15>/Divide'
   *  Sum: '<S15>/Sum'
   *  Sum: '<S15>/Sum1'
   */
  rty_tABC[0] = (-(rtb_Min + rtu_Valpha) / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[1] = (-(rtb_Min + rtb_Sum_n) / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[2] = (-(rtb_Min + rtb_Sum1_k) / rtu_v_bus + 0.5F) * 8000.0F;
}

real32_T rt_modf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  y = u0;
  if (u1 == 0.0F) {
    if (u0 == 0.0F) {
      y = u1;
    }
  } else if (rtIsNaNF(u0) || rtIsNaNF(u1) || rtIsInfF(u0)) {
    y = (rtNaNF);
  } else if (u0 == 0.0F) {
    y = 0.0F / u1;
  } else if (rtIsInfF(u1)) {
    if ((u1 < 0.0F) != (u0 < 0.0F)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmodf(u0, u1);
    yEq = (y == 0.0F);
    if ((!yEq) && (u1 > floorf(u1))) {
      real32_T q;
      q = fabsf(u0 / u1);
      yEq = !(fabsf(q - floorf(q + 0.5F)) > FLT_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0F;
    } else if ((u0 < 0.0F) != (u1 < 0.0F)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void FOC_Model_step(void)
{
  int128m_T tmp;
  uint64_T tmp_0;
  uint64_T tmp_1;
  real32_T PWM_HalfPeriod[3];
  real32_T DiscreteTimeIntegrator;
  real32_T DiscreteTimeIntegrator1_n;
  real32_T DiscreteTimeIntegrator_p;
  real32_T Integrator;
  real32_T rtb_Add1_f;
  real32_T rtb_Add_f;
  real32_T rtb_Cos_e;
  real32_T rtb_Plus9;
  real32_T rtb_RateTransition1;
  real32_T rtb_Saturation;
  real32_T rtb_SignPreIntegrator_j;
  real32_T rtb_SignPreSat_c;
  real32_T rtb_Sum;
  real32_T rtb_Sum_d_tmp;
  real32_T rtb_Sum_l;
  uint32_T currloop_ELAPS_T;
  uint32_T currloop_PREV_T_tmp;
  int16_T Integrator_p;
  int16_T rtb_IProdOut_a;
  int8_T rtAction;
  int8_T rtPrevAction;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  /* RateTransition: '<S1>/Rate Transition1' incorporates:
   *  Inport: '<Root>/Speed_ref'
   */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    rtb_RateTransition1 = rtU.Speed_ref;

    /* RateTransition: '<S1>/Rate Transition3' incorporates:
     *  Inport: '<Root>/Speed_ref'
     */
    rtDW.RateTransition3 = rtDW.RateTransition3_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition1' */

  /* S-Function (fcgen): '<S1>/Function-Call Generator1' incorporates:
   *  SubSystem: '<S1>/currloop'
   */
  if (rtDW.currloop_RESET_ELAPS_T) {
    currloop_ELAPS_T = 0U;
  } else {
    currloop_ELAPS_T = rtM->Timing.clockTick0 - rtDW.currloop_PREV_T;
  }

  /* Update for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
   *  ActionPort: '<S11>/Action Port'
   */
  /* Update for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
   *  ActionPort: '<S9>/Action Port'
   */
  /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
   *  ActionPort: '<S11>/Action Port'
   */
  /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
   *  ActionPort: '<S9>/Action Port'
   */
  /* SwitchCase: '<S2>/Switch Case' */
  currloop_PREV_T_tmp = rtM->Timing.clockTick0;

  /* End of Outputs for SubSystem: '<S2>/If Action Subsystem2' */
  /* End of Outputs for SubSystem: '<S2>/If Action Subsystem4' */
  /* End of Update for SubSystem: '<S2>/If Action Subsystem2' */
  /* End of Update for SubSystem: '<S2>/If Action Subsystem4' */
  rtDW.currloop_PREV_T = currloop_PREV_T_tmp;
  rtDW.currloop_RESET_ELAPS_T = false;

  /* Outputs for Atomic SubSystem: '<S2>/Clark_test' */
  Clark_test();

  /* End of Outputs for SubSystem: '<S2>/Clark_test' */

  /* Chart: '<S2>/Chart1' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i1 < 32767U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c7_FOC_Model == 0U) {
    rtDW.is_active_c7_FOC_Model = 1U;
    rtDW.is_c7_FOC_Model = IN_IDLE;
  } else {
    switch (rtDW.is_c7_FOC_Model) {
     case IN_AlignStage:
      if (rtDW.temporalCounter_i1 >= 1000) {
        rtDW.is_c7_FOC_Model = IN_OpenStage;
        rtDW.temporalCounter_i1 = 0U;
        rtDW.ZReset = 0.0F;
        rtDW.cnt = 0.0F;
      } else if (rtU.Motor_OnOff == 0.0) {
        rtDW.is_c7_FOC_Model = IN_IDLE;
      } else {
        state = 2.0F;
        rtDW.RestsSingal = 0.0;
      }
      break;

     case IN_IDLE:
      if (rtU.Motor_OnOff == 1.0) {
        rtDW.is_c7_FOC_Model = IN_AlignStage;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        state = 1.0F;
        rtDW.RestsSingal = 0.0;
      }
      break;

     case IN_OpenStage:
      if (rtU.Motor_OnOff == 0.0) {
        rtDW.is_c7_FOC_Model = IN_IDLE;
      } else if (rtDW.temporalCounter_i1 >= 30000) {
        rtDW.is_c7_FOC_Model = IN_ThetaAlign;
        rtDW.temporalCounter_i1 = 0U;
      } else {
        if (rtDW.cnt == 1.0F) {
          rtDW.ZReset = 1.0F;
        }

        rtDW.cnt = 1.0F;
        state = 3.0F;
        rtDW.RestsSingal = 0.0;
      }
      break;

     case IN_RunStage:
      if (rtU.Motor_OnOff == 0.0) {
        rtDW.is_c7_FOC_Model = IN_IDLE;
      } else {
        state = 5.0F;
        rtDW.RestsSingal = 1.0;
      }
      break;

     default:
      /* case IN_ThetaAlign: */
      if (rtDW.temporalCounter_i1 >= 5000) {
        rtDW.is_c7_FOC_Model = IN_RunStage;
      } else {
        state = 4.0F;
        rtDW.RestsSingal = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/Chart1' */

  /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  if (rtDW.DiscreteTimeIntegrator_SYSTEM_E != 0) {
    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    DiscreteTimeIntegrator = rtDW.DiscreteTimeIntegrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
    DiscreteTimeIntegrator = 0.0001F * (real32_T)currloop_ELAPS_T
      * rtDW.DiscreteTimeIntegrator_PREV_U + rtDW.DiscreteTimeIntegrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */

  /* Math: '<S21>/Mod' incorporates:
   *  Constant: '<S21>/Constant'
   */
  FluxTheta = rt_modf_snf(DiscreteTimeIntegrator, 6.28318548F);

  /* SwitchCase: '<S2>/Switch Case' */
  rtPrevAction = rtDW.SwitchCase_ActiveSubsystem;
  switch ((int32_T)state) {
   case 1:
    rtAction = 0;
    break;

   case 2:
    rtAction = 1;
    break;

   case 3:
    rtAction = 2;
    break;

   case 4:
    rtAction = 3;
    break;

   case 5:
    rtAction = 4;
    break;

   default:
    rtAction = 5;
    break;
  }

  rtDW.SwitchCase_ActiveSubsystem = rtAction;
  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S7>/Constant'
     *  SignalConversion generated from: '<S7>/theta_fd'
     */
    rtDW.ThetaOpen = 0.0F;

    /* Merge: '<S2>/Merge1' incorporates:
     *  Constant: '<S7>/Constant1'
     *  SignalConversion generated from: '<S7>/iq_ref'
     */
    rtDW.Merge1 = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Constant: '<S8>/Constant'
     *  SignalConversion generated from: '<S8>/theta_fd'
     */
    rtDW.ThetaOpen = 0.0F;

    /* Merge: '<S2>/Merge1' incorporates:
     *  Constant: '<S8>/Constant1'
     *  SignalConversion generated from: '<S8>/iq_ref'
     */
    rtDW.Merge1 = 2.0F;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem1' */
    break;

   case 2:
    {
      uint32_T IfActionSubsystem2_ELAPS_T;
      if (rtAction != rtPrevAction) {
        rtDW.IfActionSubsystem2_RESET_ELAPS_ = true;

        /* Enable for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
         *  ActionPort: '<S9>/Action Port'
         */
        /* Enable for SwitchCase: '<S2>/Switch Case' incorporates:
         *  DiscreteIntegrator: '<S9>/Discrete-Time Integrator'
         *  DiscreteIntegrator: '<S9>/Discrete-Time Integrator1'
         */
        rtDW.DiscreteTimeIntegrator_SYSTEM_o = 1U;
        rtDW.DiscreteTimeIntegrator1_SYSTE_c = 1U;

        /* End of Enable for SubSystem: '<S2>/If Action Subsystem2' */
      }

      /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
       *  ActionPort: '<S9>/Action Port'
       */
      if (rtDW.IfActionSubsystem2_RESET_ELAPS_) {
        IfActionSubsystem2_ELAPS_T = 0U;
      } else {
        IfActionSubsystem2_ELAPS_T = currloop_PREV_T_tmp -
          rtDW.IfActionSubsystem2_PREV_T;
      }

      rtDW.IfActionSubsystem2_PREV_T = currloop_PREV_T_tmp;
      rtDW.IfActionSubsystem2_RESET_ELAPS_ = false;

      /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
      if (rtDW.DiscreteTimeIntegrator_SYSTEM_o != 0) {
        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
        DiscreteTimeIntegrator_p = rtDW.DiscreteTimeIntegrator_DSTATE_l;
      } else if ((rtDW.ZReset > 0.0F) && (rtDW.DiscreteTimeIntegrator_PrevRese <=
                  0)) {
        rtDW.DiscreteTimeIntegrator_DSTATE_l = 0.0F;

        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
        DiscreteTimeIntegrator_p = rtDW.DiscreteTimeIntegrator_DSTATE_l;
      } else {
        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
        DiscreteTimeIntegrator_p = 0.0001F * (real32_T)
          IfActionSubsystem2_ELAPS_T * rtDW.DiscreteTimeIntegrator_PREV_U_i +
          rtDW.DiscreteTimeIntegrator_DSTATE_l;
      }

      /* End of DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */

      /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
      if (rtDW.DiscreteTimeIntegrator1_SYSTE_c != 0) {
        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
        DiscreteTimeIntegrator1_n = rtDW.DiscreteTimeIntegrator1_DSTAT_c;
      } else if ((rtDW.ZReset > 0.0F) && (rtDW.DiscreteTimeIntegrator1_PrevRes <=
                  0)) {
        rtDW.DiscreteTimeIntegrator1_DSTAT_c = 0.0F;

        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
        DiscreteTimeIntegrator1_n = rtDW.DiscreteTimeIntegrator1_DSTAT_c;
      } else {
        /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
        DiscreteTimeIntegrator1_n = 0.0001F * (real32_T)
          IfActionSubsystem2_ELAPS_T * rtDW.DiscreteTimeIntegrator1_PREV__k +
          rtDW.DiscreteTimeIntegrator1_DSTAT_c;
      }

      /* End of DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */

      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S9>/Constant1'
       *  Math: '<S9>/Mod'
       */
      rtDW.ThetaOpen = rt_modf_snf(DiscreteTimeIntegrator1_n, 6.28318548F);

      /* Merge: '<S2>/Merge1' incorporates:
       *  Constant: '<S2>/Constant2'
       *  Inport: '<S9>/iq_ref'
       */
      rtDW.Merge1 = 1.0F;

      /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
      rtDW.DiscreteTimeIntegrator_SYSTEM_o = 0U;
      rtDW.DiscreteTimeIntegrator_DSTATE_l = DiscreteTimeIntegrator_p;
      if (rtDW.ZReset > 0.0F) {
        rtDW.DiscreteTimeIntegrator_PrevRese = 1;
      } else if (rtDW.ZReset < 0.0F) {
        rtDW.DiscreteTimeIntegrator_PrevRese = -1;
      } else if (rtDW.ZReset == 0.0F) {
        rtDW.DiscreteTimeIntegrator_PrevRese = 0;
      } else {
        rtDW.DiscreteTimeIntegrator_PrevRese = 2;
      }

      /* Gain: '<S9>/Gain1' incorporates:
       *  Gain: '<S9>/Gain'
       */
      rtb_Cos_e = motor.Pn * 2.30584301E+18F;
      rtb_Plus9 = fabsf(rtb_Cos_e);
      if (rtb_Plus9 < 8.388608E+6F) {
        if (rtb_Plus9 >= 0.5F) {
          rtb_Cos_e = floorf(rtb_Cos_e + 0.5F);
        } else {
          rtb_Cos_e *= 0.0F;
        }
      }

      if (rtb_Cos_e < 9.22337204E+18F) {
        if (rtb_Cos_e >= -9.22337204E+18F) {
          tmp_0 = (uint64_T)(int64_T)rtb_Cos_e;
        } else {
          tmp_0 = 9223372036854775808ULL;
        }
      } else {
        tmp_0 = 9223372036854775807ULL;
      }

      tmp_1 = 1079443016400ULL;
      sMultiWordMul(&tmp_0, 1, &tmp_1, 1, &tmp.chunks[0U], 2);

      /* End of Gain: '<S9>/Gain1' */

      /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' incorporates:
       *  Product: '<S9>/Product'
       */
      rtDW.DiscreteTimeIntegrator_PREV_U_i = sMultiWord2Single(&tmp.chunks[0U],
        2, 0) * 2.5243549E-29F * 0.333333343F;

      /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
      rtDW.DiscreteTimeIntegrator1_SYSTE_c = 0U;
      rtDW.DiscreteTimeIntegrator1_DSTAT_c = DiscreteTimeIntegrator1_n;
      if (rtDW.ZReset > 0.0F) {
        rtDW.DiscreteTimeIntegrator1_PrevRes = 1;
      } else if (rtDW.ZReset < 0.0F) {
        rtDW.DiscreteTimeIntegrator1_PrevRes = -1;
      } else if (rtDW.ZReset == 0.0F) {
        rtDW.DiscreteTimeIntegrator1_PrevRes = 0;
      } else {
        rtDW.DiscreteTimeIntegrator1_PrevRes = 2;
      }

      rtDW.DiscreteTimeIntegrator1_PREV__k = DiscreteTimeIntegrator_p;

      /* End of Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
      /* End of Outputs for SubSystem: '<S2>/If Action Subsystem2' */
    }
    break;

   case 3:
    {
      uint32_T IfActionSubsystem2_ELAPS_T;
      if (rtAction != rtPrevAction) {
        rtDW.IfActionSubsystem4_RESET_ELAPS_ = true;

        /* Enable for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
         *  ActionPort: '<S11>/Action Port'
         */
        /* Enable for SwitchCase: '<S2>/Switch Case' incorporates:
         *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator1'
         */
        rtDW.DiscreteTimeIntegrator1_SYSTEM_ = 1U;

        /* End of Enable for SubSystem: '<S2>/If Action Subsystem4' */
      }

      /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
       *  ActionPort: '<S11>/Action Port'
       */
      if (rtDW.IfActionSubsystem4_RESET_ELAPS_) {
        IfActionSubsystem2_ELAPS_T = 0U;
      } else {
        IfActionSubsystem2_ELAPS_T = currloop_PREV_T_tmp -
          rtDW.IfActionSubsystem4_PREV_T;
      }

      rtDW.IfActionSubsystem4_PREV_T = currloop_PREV_T_tmp;
      rtDW.IfActionSubsystem4_RESET_ELAPS_ = false;

      /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */
      if (rtDW.DiscreteTimeIntegrator1_SYSTEM_ != 0) {
        /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */
        DiscreteTimeIntegrator_p = rtDW.DiscreteTimeIntegrator1_DSTATE;
      } else {
        /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */
        DiscreteTimeIntegrator_p = 0.0001F * (real32_T)
          IfActionSubsystem2_ELAPS_T * rtDW.DiscreteTimeIntegrator1_PREV_U +
          rtDW.DiscreteTimeIntegrator1_DSTATE;
      }

      /* End of DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' */

      /* Merge: '<S2>/Merge' incorporates:
       *  Constant: '<S11>/Constant'
       *  Math: '<S11>/Mod'
       *  SignalConversion generated from: '<S11>/Theta_fd'
       */
      rtDW.ThetaOpen = rt_modf_snf(DiscreteTimeIntegrator_p, 6.28318548F);

      /* If: '<S11>/If' incorporates:
       *  Constant: '<S11>/Constant1'
       *  Constant: '<S16>/Constant'
       *  SignalConversion generated from: '<S16>/Out1'
       *  Sum: '<S11>/Add'
       *  UnitDelay: '<S11>/Unit Delay'
       */
      if (rtDW.UnitDelay_DSTATE_i + 0.01F >= 1.0F) {
        /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem' incorporates:
         *  ActionPort: '<S16>/Action Port'
         */
        DiscreteTimeIntegrator1_n = 1.0F;

        /* End of Outputs for SubSystem: '<S11>/If Action Subsystem' */
      } else {
        DiscreteTimeIntegrator1_n = rtDW.UnitDelay_DSTATE_i + 0.01F;
      }

      /* End of If: '<S11>/If' */

      /* Merge: '<S2>/Merge1' incorporates:
       *  Constant: '<S11>/Constant2'
       *  Constant: '<S11>/Constant4'
       *  Product: '<S11>/Product1'
       *  Sum: '<S11>/Add4'
       */
      rtDW.Merge1 = 1.0F - DiscreteTimeIntegrator1_n * 0.7F;

      /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator1' incorporates:
       *  Gain: '<S11>/Gain'
       */
      rtDW.DiscreteTimeIntegrator1_SYSTEM_ = 0U;
      rtDW.DiscreteTimeIntegrator1_DSTATE = DiscreteTimeIntegrator_p;
      rtDW.DiscreteTimeIntegrator1_PREV_U = motor.Pn * 62.8318558F;

      /* Update for UnitDelay: '<S11>/Unit Delay' incorporates:
       *  Constant: '<S11>/Constant1'
       *  Sum: '<S11>/Add'
       */
      rtDW.UnitDelay_DSTATE_i += 0.01F;

      /* End of Outputs for SubSystem: '<S2>/If Action Subsystem4' */
    }
    break;

   case 4:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Merge: '<S2>/Merge' incorporates:
     *  Inport: '<S10>/theta'
     */
    rtDW.ThetaOpen = FluxTheta;

    /* Merge: '<S2>/Merge1' incorporates:
     *  Inport: '<S10>/iq_ref'
     */
    rtDW.Merge1 = rtDW.RateTransition3;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem3' */
    break;
  }

  /* Trigonometry: '<S2>/Cos' */
  rtb_Cos_e = cosf(rtDW.ThetaOpen);

  /* Trigonometry: '<S2>/SinCos' */
  rtb_Plus9 = sinf(rtDW.ThetaOpen);

  /* Sum: '<S13>/Sum' incorporates:
   *  Constant: '<S13>/Constant'
   *  Outport: '<Root>/Tcmp3'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product1'
   *  Sum: '<S14>/Add'
   */
  rtb_Sum = 0.0F - (ialpha * rtb_Cos_e + rtY.Tcmp3 * rtb_Plus9);

  /* DiscreteIntegrator: '<S107>/Integrator' */
  if (rtDW.Integrator_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S107>/Integrator' */
    Integrator_p = rtDW.Integrator_DSTATE_p;
  } else {
    /* DiscreteIntegrator: '<S107>/Integrator' */
    Integrator_p = (int16_T)((int16_T)((int32_T)currloop_ELAPS_T
      * rtDW.Integrator_PREV_U_iy) + rtDW.Integrator_DSTATE_p);
  }

  /* End of DiscreteIntegrator: '<S107>/Integrator' */

  /* Sum: '<S116>/Sum' incorporates:
   *  Constant: '<S13>/Constant1'
   *  DiscreteIntegrator: '<S107>/Integrator'
   *  Product: '<S112>/PProd Out'
   */
  DiscreteTimeIntegrator_p = rtb_Sum * curr_kpki.curr_d_kp + (real32_T)
    Integrator_p * 0.0001F;

  /* Saturate: '<S114>/Saturation' */
  if (DiscreteTimeIntegrator_p > 12.4707661F) {
    rtb_Sum_l = 12.4707661F;
  } else if (DiscreteTimeIntegrator_p < -12.4707661F) {
    rtb_Sum_l = -12.4707661F;
  } else {
    rtb_Sum_l = DiscreteTimeIntegrator_p;
  }

  /* End of Saturate: '<S114>/Saturation' */

  /* Sum: '<S13>/Sum1' incorporates:
   *  Outport: '<Root>/Tcmp3'
   *  Product: '<S14>/Product2'
   *  Product: '<S14>/Product3'
   *  Sum: '<S14>/Add1'
   */
  DiscreteTimeIntegrator1_n = rtDW.Merge1 - (rtY.Tcmp3 * rtb_Cos_e - ialpha *
    rtb_Plus9);

  /* DiscreteIntegrator: '<S157>/Integrator' */
  if (rtDW.Integrator_SYSTEM_ENABLE_l != 0) {
    /* DiscreteIntegrator: '<S157>/Integrator' */
    Integrator = rtDW.Integrator_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S157>/Integrator' */
    Integrator = 0.0001F * (real32_T)currloop_ELAPS_T * rtDW.Integrator_PREV_U +
      rtDW.Integrator_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S157>/Integrator' */

  /* Sum: '<S166>/Sum' incorporates:
   *  Constant: '<S13>/Constant3'
   *  Product: '<S162>/PProd Out'
   */
  rtb_SignPreSat_c = DiscreteTimeIntegrator1_n * curr_kpki.curr_d_kp +
    Integrator;

  /* Saturate: '<S164>/Saturation' */
  if (rtb_SignPreSat_c > 12.4707661F) {
    rtb_SignPreIntegrator_j = 12.4707661F;
  } else if (rtb_SignPreSat_c < -12.4707661F) {
    rtb_SignPreIntegrator_j = -12.4707661F;
  } else {
    rtb_SignPreIntegrator_j = rtb_SignPreSat_c;
  }

  /* End of Saturate: '<S164>/Saturation' */

  /* Sum: '<S4>/Add' incorporates:
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   */
  rtb_Add_f = rtb_Sum_l * rtb_Cos_e - rtb_SignPreIntegrator_j * rtb_Plus9;

  /* Sum: '<S4>/Add1' incorporates:
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   */
  rtb_Add1_f = rtb_Sum_l * rtb_Plus9 + rtb_SignPreIntegrator_j * rtb_Cos_e;

  /* Gain: '<S22>/Gain12' incorporates:
   *  Gain: '<S22>/Gain16'
   */
  rtb_Saturation = motor.L * ialpha;     

  /* Sum: '<S22>/Sum' incorporates:
   *  Gain: '<S22>/Gain12'
   *  UnitDelay: '<S22>/Unit Delay4'
   */
  rtb_SignPreIntegrator_j = rtDW.UnitDelay4_DSTATE - rtb_Saturation;    //eta(x1)=x1-L*Ia

  /* Gain: '<S22>/Gain13' incorporates:
   *  Gain: '<S22>/Gain2'
   *  Outport: '<Root>/Tcmp3'
   */
  rtb_Sum_d_tmp = motor.L * rtY.Tcmp3;       

  /* Sum: '<S22>/Sum1' incorporates:
   *  Gain: '<S22>/Gain13'
   *  UnitDelay: '<S22>/Unit Delay1'
   */
  rtb_Sum_l = rtDW.UnitDelay1_DSTATE - rtb_Sum_d_tmp;          //eta(x2)=x2-L*Ib

  /* Sum: '<S22>/Plus9' incorporates:
   *  Constant: '<S22>/Constant'
   *  Math: '<S22>/Square'
   *  Math: '<S22>/Square1'
   *  Math: '<S22>/Square2'
   *  Sum: '<S22>/Plus8'
   */
  rtb_Plus9 = motor.flux * motor.flux - (rtb_SignPreIntegrator_j *
    rtb_SignPreIntegrator_j + rtb_Sum_l * rtb_Sum_l);                     //flux平方-eta(x)平方    eta(x)平方=eta(x1)平方+eta(x2)平方

  /* Sum: '<S22>/Plus11' incorporates:
   *  Constant: '<S22>/Constant1'
   *  Gain: '<S22>/Gain11'
   *  Gain: '<S22>/Gain15'
   *  Product: '<S22>/Product2'
   *  Sum: '<S22>/Plus10'
   *  Sum: '<S22>/Plus6'
   *  UnitDelay: '<S22>/Unit Delay4'
   */
  rtb_Cos_e = ((rtb_Add_f - motor.Rs * ialpha) + Gramma.Gamma *
               rtb_SignPreIntegrator_j * rtb_Plus9) * 0.0001F +
    rtDW.UnitDelay4_DSTATE;                                  //x1(k)=Ts(y1(k-1)+flux*etax1(k-1)*flux平方-eta1(x)平方)+x1(k-1)     y1(k-1)=Ualpha-Rs*iaplha

  /* Sum: '<S22>/Plus2' incorporates:
   *  Constant: '<S22>/Constant2'
   *  Gain: '<S22>/Gain1'
   *  Gain: '<S22>/Gain14'
   *  Outport: '<Root>/Tcmp3'
   *  Product: '<S22>/Product1'
   *  Sum: '<S22>/Plus1'
   *  Sum: '<S22>/Plus7'
   *  UnitDelay: '<S22>/Unit Delay1'
   */
  rtb_Plus9 = (rtb_Plus9 * rtb_Sum_l * Gramma.Gamma + (rtb_Add1_f - motor.Rs *
    rtY.Tcmp3)) * 0.0001F + rtDW.UnitDelay1_DSTATE;         //x2(k)=Ts(y2(k-1)+flux*etax2(k-1)*flux平方-eta2(x)平方)+x2(k-1)    y2(k-1)=Ubta-Rs*ibeta

  /* Sum: '<S21>/Plus' incorporates:
   *  Gain: '<S22>/Gain17'
   *  Gain: '<S22>/Gain3'
   *  Product: '<S21>/Product'
   *  Product: '<S21>/Product1'
   *  Sum: '<S22>/Plus12'
   *  Sum: '<S22>/Plus3'
   *  Trigonometry: '<S21>/Cos'
   *  Trigonometry: '<S21>/Sin'
   */
  rtb_SignPreIntegrator_j = (rtb_Plus9 - rtb_Sum_d_tmp) * (1.0F / motor.flux) *
    cosf(FluxTheta) - (rtb_Cos_e - rtb_Saturation) * (1.0F / motor.flux) * sinf
    (FluxTheta);                                                                             //cosθ=x1(k)-L*Iaplha    sinθ=x2(k)-L*Ibeta      PLL:sinθ*cosFluxTheta- cosθ*sinFluxTheta

  /* DiscreteIntegrator: '<S55>/Integrator' */
  if (rtDW.Integrator_SYSTEM_ENABLE_ln != 0) {
    /* DiscreteIntegrator: '<S55>/Integrator' */
    rtb_Sum_l = rtDW.Integrator_DSTATE_f;
  } else {
    /* DiscreteIntegrator: '<S55>/Integrator' */
    rtb_Sum_l = 0.0001F * (real32_T)currloop_ELAPS_T * rtDW.Integrator_PREV_U_i
      + rtDW.Integrator_DSTATE_f;
  }

  /* End of DiscreteIntegrator: '<S55>/Integrator' */

  /* Sum: '<S64>/Sum' incorporates:
   *  Gain: '<S60>/Proportional Gain'
   */
  rtb_Saturation = PLL.PLLKP * rtb_SignPreIntegrator_j + rtb_Sum_l;     //We=PID(sinθ*cosFluxTheta- cosθ*sinFluxTheta)

  /* Saturate: '<S62>/Saturation' */
  if (rtb_Saturation > 2000.0F) {
    rtb_Saturation = 2000.0F;
  } else if (rtb_Saturation < -2000.0F) {
    rtb_Saturation = -2000.0F;
  }

  /* End of Saturate: '<S62>/Saturation' */

  /* Sum: '<S20>/Plus1' incorporates:
   *  Constant: '<S20>/Constant'
   *  Gain: '<S12>/Gain'
   *  Gain: '<S12>/Gain1'
   *  Product: '<S20>/Product2'
   *  Sum: '<S20>/Plus7'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  FluxWm += (1.0F / motor.Pn * rtb_Saturation * 9.54929638F - FluxWm) *
    LPFFilter.LPFFilter;                                                //FluxWm+=LPF*(1/Pn*30/pi*Flux(K-1)-FluxWm)
  
  //FluxWm += (rtU.Input - FluxWm) * LPFFilter.LPFFilter;
	

  /* Outputs for Atomic SubSystem: '<S2>/SVPWM' */
  /* Inport: '<Root>/v_bus' */
  SVPWM(rtb_Add_f, rtb_Add1_f, rtU.v_bus, PWM_HalfPeriod);

  /* End of Outputs for SubSystem: '<S2>/SVPWM' */

  /* Outport: '<Root>/Tcmp2' incorporates:
   *  SignalConversion generated from: '<S2>/Tcmp2'
   */
  rtY.Tcmp2 = PWM_HalfPeriod[1];

  /* SignalConversion generated from: '<S2>/Tcmp3' incorporates:
   *  Outport: '<Root>/Tcmp3'
   */
  rtY.Tcmp3 = PWM_HalfPeriod[2];

  /* Gain: '<S98>/ZeroGain' */
  rtb_Add_f = 0.0F * DiscreteTimeIntegrator_p;

  /* DeadZone: '<S100>/DeadZone' */
  if (DiscreteTimeIntegrator_p > 12.4707661F) {
    DiscreteTimeIntegrator_p -= 12.4707661F;
  } else if (DiscreteTimeIntegrator_p >= -12.4707661F) {
    DiscreteTimeIntegrator_p = 0.0F;
  } else {
    DiscreteTimeIntegrator_p -= -12.4707661F;
  }

  /* End of DeadZone: '<S100>/DeadZone' */

  /* Product: '<S104>/IProd Out' incorporates:
   *  Constant: '<S13>/Constant2'
   */
  rtb_IProdOut_a = (int16_T)floorf(rtb_Sum * curr_kpki.curr_d_ki);

  /* Gain: '<S148>/ZeroGain' */
  rtb_Sum = 0.0F * rtb_SignPreSat_c;

  /* DeadZone: '<S150>/DeadZone' */
  if (rtb_SignPreSat_c > 12.4707661F) {
    rtb_SignPreSat_c -= 12.4707661F;
  } else if (rtb_SignPreSat_c >= -12.4707661F) {
    rtb_SignPreSat_c = 0.0F;
  } else {
    rtb_SignPreSat_c -= -12.4707661F;
  }

  /* End of DeadZone: '<S150>/DeadZone' */

  /* Product: '<S154>/IProd Out' incorporates:
   *  Constant: '<S13>/Constant4'
   */
  DiscreteTimeIntegrator1_n *= curr_kpki.curr_d_ki;

  /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_SYSTEM_E = 0U;
  rtDW.DiscreteTimeIntegrator_DSTATE = DiscreteTimeIntegrator;
  rtDW.DiscreteTimeIntegrator_PREV_U = rtb_Saturation;

  /* Update for SwitchCase: '<S2>/Switch Case' */
  switch (rtDW.SwitchCase_ActiveSubsystem) {
   case 0:
   case 1:
   case 4:
   case 5:
    break;

   case 2:
    /* Update for IfAction SubSystem: '<S2>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    rtDW.IfActionSubsystem2_PREV_T = currloop_PREV_T_tmp;
    rtDW.IfActionSubsystem2_RESET_ELAPS_ = false;

    /* End of Update for SubSystem: '<S2>/If Action Subsystem2' */
    break;

   case 3:
    /* Update for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    rtDW.IfActionSubsystem4_PREV_T = currloop_PREV_T_tmp;
    rtDW.IfActionSubsystem4_RESET_ELAPS_ = false;

    /* End of Update for SubSystem: '<S2>/If Action Subsystem4' */
    break;
  }

  /* Update for DiscreteIntegrator: '<S107>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 0U;
  rtDW.Integrator_DSTATE_p = Integrator_p;

  /* Signum: '<S98>/SignPreSat' */
  if (DiscreteTimeIntegrator_p < 0.0F) {
    DiscreteTimeIntegrator = -1.0F;
  } else if (DiscreteTimeIntegrator_p > 0.0F) {
    DiscreteTimeIntegrator = 1.0F;
  } else if (DiscreteTimeIntegrator_p == 0.0F) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = (rtNaNF);
  }

  /* End of Signum: '<S98>/SignPreSat' */

  /* Signum: '<S98>/SignPreIntegrator' */
  if (rtb_IProdOut_a < 0) {
    Integrator_p = -1;
  } else {
    Integrator_p = (int16_T)(rtb_IProdOut_a > 0);
  }

  /* End of Signum: '<S98>/SignPreIntegrator' */

  /* Switch: '<S98>/Switch' incorporates:
   *  DataTypeConversion: '<S98>/DataTypeConv1'
   *  DataTypeConversion: '<S98>/DataTypeConv2'
   *  Logic: '<S98>/AND3'
   *  RelationalOperator: '<S98>/Equal1'
   *  RelationalOperator: '<S98>/NotEqual'
   */
  if ((rtb_Add_f != DiscreteTimeIntegrator_p) && ((int8_T)DiscreteTimeIntegrator
       == Integrator_p)) {
    /* Update for DiscreteIntegrator: '<S107>/Integrator' incorporates:
     *  Constant: '<S98>/Constant1'
     */
    rtDW.Integrator_PREV_U_iy = 0;
  } else {
    /* Update for DiscreteIntegrator: '<S107>/Integrator' */
    rtDW.Integrator_PREV_U_iy = rtb_IProdOut_a;
  }

  /* End of Switch: '<S98>/Switch' */

  /* Update for DiscreteIntegrator: '<S157>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE_l = 0U;
  rtDW.Integrator_DSTATE = Integrator;

  /* Signum: '<S148>/SignPreSat' */
  if (rtb_SignPreSat_c < 0.0F) {
    DiscreteTimeIntegrator_p = -1.0F;
  } else if (rtb_SignPreSat_c > 0.0F) {
    DiscreteTimeIntegrator_p = 1.0F;
  } else if (rtb_SignPreSat_c == 0.0F) {
    DiscreteTimeIntegrator_p = 0.0F;
  } else {
    DiscreteTimeIntegrator_p = (rtNaNF);
  }

  /* End of Signum: '<S148>/SignPreSat' */

  /* Signum: '<S148>/SignPreIntegrator' */
  if (DiscreteTimeIntegrator1_n < 0.0F) {
    DiscreteTimeIntegrator = -1.0F;
  } else if (DiscreteTimeIntegrator1_n > 0.0F) {
    DiscreteTimeIntegrator = 1.0F;
  } else if (DiscreteTimeIntegrator1_n == 0.0F) {
    DiscreteTimeIntegrator = 0.0F;
  } else {
    DiscreteTimeIntegrator = (rtNaNF);
  }

  /* End of Signum: '<S148>/SignPreIntegrator' */

  /* Switch: '<S148>/Switch' incorporates:
   *  DataTypeConversion: '<S148>/DataTypeConv1'
   *  DataTypeConversion: '<S148>/DataTypeConv2'
   *  Logic: '<S148>/AND3'
   *  RelationalOperator: '<S148>/Equal1'
   *  RelationalOperator: '<S148>/NotEqual'
   */
  if ((rtb_Sum != rtb_SignPreSat_c) && ((int8_T)DiscreteTimeIntegrator_p ==
       (int8_T)DiscreteTimeIntegrator)) {
    /* Update for DiscreteIntegrator: '<S157>/Integrator' incorporates:
     *  Constant: '<S148>/Constant1'
     */
    rtDW.Integrator_PREV_U = 0.0F;
  } else {
    /* Update for DiscreteIntegrator: '<S157>/Integrator' */
    rtDW.Integrator_PREV_U = DiscreteTimeIntegrator1_n;
  }

  /* End of Switch: '<S148>/Switch' */

  /* Update for UnitDelay: '<S22>/Unit Delay4' */
  rtDW.UnitDelay4_DSTATE = rtb_Cos_e;

  /* Update for UnitDelay: '<S22>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE = rtb_Plus9;

  /* Update for DiscreteIntegrator: '<S55>/Integrator' incorporates:
   *  Gain: '<S52>/Integral Gain'
   */
  rtDW.Integrator_SYSTEM_ENABLE_ln = 0U;
  rtDW.Integrator_DSTATE_f = rtb_Sum_l;
  rtDW.Integrator_PREV_U_i = PLL.PLLKI * rtb_SignPreIntegrator_j;

  /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator1' */

  /* RateTransition: '<S1>/Rate Transition2' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/speedloop'
     */
    if (rtDW.speedloop_RESET_ELAPS_T) {
      currloop_ELAPS_T = 0U;
    } else {
      currloop_ELAPS_T = rtM->Timing.clockTick1 - rtDW.speedloop_PREV_T;
    }

    rtDW.speedloop_PREV_T = rtM->Timing.clockTick1;
    rtDW.speedloop_RESET_ELAPS_T = false;

    /* Sum: '<S3>/Sum' */
    rtb_RateTransition1 -= FluxWm;

    /* DiscreteIntegrator: '<S210>/Integrator' incorporates:
     *  RateTransition: '<S1>/Rate Transition'
     */
    if (rtDW.Integrator_SYSTEM_ENABLE_a != 0) {
      /* DiscreteIntegrator: '<S210>/Integrator' */
      DiscreteTimeIntegrator = rtDW.Integrator_DSTATE_b;
    } else if ((rtDW.RestsSingal > 0.0) && (rtDW.Integrator_PrevResetState <= 0))
    {
      rtDW.Integrator_DSTATE_b = 0.0F;

      /* DiscreteIntegrator: '<S210>/Integrator' */
      DiscreteTimeIntegrator = rtDW.Integrator_DSTATE_b;
    } else {
      /* DiscreteIntegrator: '<S210>/Integrator' */
      DiscreteTimeIntegrator = 0.001F * (real32_T)currloop_ELAPS_T
        * rtDW.Integrator_PREV_U_f + rtDW.Integrator_DSTATE_b;
    }

    /* End of DiscreteIntegrator: '<S210>/Integrator' */

    /* Sum: '<S219>/Sum' incorporates:
     *  Gain: '<S215>/Proportional Gain'
     */
    DiscreteTimeIntegrator_p = spd_kpki.spd_kp * rtb_RateTransition1 +
      DiscreteTimeIntegrator;

    /* DeadZone: '<S203>/DeadZone' */
    if (DiscreteTimeIntegrator_p > 3.0F) {
      DiscreteTimeIntegrator1_n = DiscreteTimeIntegrator_p - 3.0F;
    } else if (DiscreteTimeIntegrator_p >= -3.0F) {
      DiscreteTimeIntegrator1_n = 0.0F;
    } else {
      DiscreteTimeIntegrator1_n = DiscreteTimeIntegrator_p - -3.0F;
    }

    /* End of DeadZone: '<S203>/DeadZone' */

    /* Gain: '<S207>/Integral Gain' */
    rtb_RateTransition1 *= spd_kpki.spd_ki;

    /* Update for DiscreteIntegrator: '<S210>/Integrator' incorporates:
     *  RateTransition: '<S1>/Rate Transition'
     */
    rtDW.Integrator_SYSTEM_ENABLE_a = 0U;
    rtDW.Integrator_DSTATE_b = DiscreteTimeIntegrator;
    if (rtDW.RestsSingal > 0.0) {
      rtDW.Integrator_PrevResetState = 1;
    } else if (rtDW.RestsSingal < 0.0) {
      rtDW.Integrator_PrevResetState = -1;
    } else if (rtDW.RestsSingal == 0.0) {
      rtDW.Integrator_PrevResetState = 0;
    } else {
      rtDW.Integrator_PrevResetState = 2;
    }

    /* Signum: '<S201>/SignPreSat' */
    if (DiscreteTimeIntegrator1_n < 0.0F) {
      DiscreteTimeIntegrator = -1.0F;
    } else if (DiscreteTimeIntegrator1_n > 0.0F) {
      DiscreteTimeIntegrator = 1.0F;
    } else if (DiscreteTimeIntegrator1_n == 0.0F) {
      DiscreteTimeIntegrator = 0.0F;
    } else {
      DiscreteTimeIntegrator = (rtNaNF);
    }

    /* End of Signum: '<S201>/SignPreSat' */

    /* Signum: '<S201>/SignPreIntegrator' */
    if (rtb_RateTransition1 < 0.0F) {
      rtb_Cos_e = -1.0F;
    } else if (rtb_RateTransition1 > 0.0F) {
      rtb_Cos_e = 1.0F;
    } else if (rtb_RateTransition1 == 0.0F) {
      rtb_Cos_e = 0.0F;
    } else {
      rtb_Cos_e = (rtNaNF);
    }

    /* End of Signum: '<S201>/SignPreIntegrator' */

    /* Switch: '<S201>/Switch' incorporates:
     *  DataTypeConversion: '<S201>/DataTypeConv1'
     *  DataTypeConversion: '<S201>/DataTypeConv2'
     *  Gain: '<S201>/ZeroGain'
     *  Logic: '<S201>/AND3'
     *  RelationalOperator: '<S201>/Equal1'
     *  RelationalOperator: '<S201>/NotEqual'
     */
    if ((0.0F * DiscreteTimeIntegrator_p != DiscreteTimeIntegrator1_n) &&
        ((int8_T)DiscreteTimeIntegrator == (int8_T)rtb_Cos_e)) {
      /* Update for DiscreteIntegrator: '<S210>/Integrator' incorporates:
       *  Constant: '<S201>/Constant1'
       */
      rtDW.Integrator_PREV_U_f = 0.0F;
    } else {
      /* Update for DiscreteIntegrator: '<S210>/Integrator' */
      rtDW.Integrator_PREV_U_f = rtb_RateTransition1;
    }

    /* End of Switch: '<S201>/Switch' */

    /* Saturate: '<S217>/Saturation' */
    if (DiscreteTimeIntegrator_p > 3.0F) {
      /* Update for RateTransition: '<S1>/Rate Transition3' */
      rtDW.RateTransition3_Buffer0 = 3.0F;
    } else if (DiscreteTimeIntegrator_p < -3.0F) {
      /* Update for RateTransition: '<S1>/Rate Transition3' */
      rtDW.RateTransition3_Buffer0 = -3.0F;
    } else {
      /* Update for RateTransition: '<S1>/Rate Transition3' */
      rtDW.RateTransition3_Buffer0 = DiscreteTimeIntegrator_p;
    }

    /* End of Saturate: '<S217>/Saturation' */
    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  }

  /* End of RateTransition: '<S1>/Rate Transition2' */
  /* End of Outputs for SubSystem: '<Root>/FOC_Model' */

  /* Outport: '<Root>/Tcmp1' */
  rtY.Tcmp1 = PWM_HalfPeriod[0];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.0001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rtM->Timing.clockTick0++;
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }

  rate_scheduler();
}

/* Model initialize function */
void FOC_Model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_Model' */
  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator1' incorporates:
   *  SubSystem: '<S1>/currloop'
   */
  /* Start for SwitchCase: '<S2>/Switch Case' */
  rtDW.SwitchCase_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action Subsystem2' */
  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW.DiscreteTimeIntegrator1_PrevRes = 2;

  /* End of SystemInitialize for SubSystem: '<S2>/If Action Subsystem2' */
  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator1' */

  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S210>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_Model' */

  /* Enable for Atomic SubSystem: '<Root>/FOC_Model' */
  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator1' incorporates:
   *  SubSystem: '<S1>/currloop'
   */
  rtDW.currloop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_SYSTEM_E = 1U;

  /* Enable for DiscreteIntegrator: '<S107>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 1U;

  /* Enable for DiscreteIntegrator: '<S157>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE_l = 1U;

  /* Enable for DiscreteIntegrator: '<S55>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE_ln = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator1' */

  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  rtDW.speedloop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S210>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE_a = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Enable for SubSystem: '<Root>/FOC_Model' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
