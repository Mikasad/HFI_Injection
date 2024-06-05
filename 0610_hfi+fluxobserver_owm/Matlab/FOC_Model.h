/*
 * File: FOC_Model.h
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

#ifndef RTW_HEADER_FOC_Model_h_
#define RTW_HEADER_FOC_Model_h_
#include <stddef.h>
#include <math.h>
#include <float.h>
#ifndef FOC_Model_COMMON_INCLUDES_
#define FOC_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Model_COMMON_INCLUDES_ */

/* Shared type includes */
#include "multiword_types.h"

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T RestsSingal;                  /* '<S2>/Chart1' */
  real32_T RateTransition3;            /* '<S1>/Rate Transition3' */
  real32_T ThetaOpen;                  /* '<S2>/Merge' */
  real32_T Merge1;                     /* '<S2>/Merge1' */
  real32_T ZReset;                     /* '<S2>/Chart1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S21>/Discrete-Time Integrator' */
  real32_T Integrator_DSTATE;          /* '<S157>/Integrator' */
  real32_T UnitDelay4_DSTATE;          /* '<S22>/Unit Delay4' */
  real32_T UnitDelay1_DSTATE;          /* '<S22>/Unit Delay1' */
  real32_T Integrator_DSTATE_f;        /* '<S55>/Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S11>/Discrete-Time Integrator1' */
  real32_T UnitDelay_DSTATE_i;         /* '<S11>/Unit Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_l;/* '<S9>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTAT_c;/* '<S9>/Discrete-Time Integrator1' */
  real32_T Integrator_DSTATE_b;        /* '<S210>/Integrator' */
  real32_T RateTransition3_Buffer0;    /* '<S1>/Rate Transition3' */
  real32_T DiscreteTimeIntegrator_PREV_U;/* '<S21>/Discrete-Time Integrator' */
  real32_T Integrator_PREV_U;          /* '<S157>/Integrator' */
  real32_T Integrator_PREV_U_i;        /* '<S55>/Integrator' */
  real32_T DiscreteTimeIntegrator1_PREV_U;/* '<S11>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_PREV_U_i;/* '<S9>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_PREV__k;/* '<S9>/Discrete-Time Integrator1' */
  real32_T cnt;                        /* '<S2>/Chart1' */
  real32_T Integrator_PREV_U_f;        /* '<S210>/Integrator' */
  uint32_T currloop_PREV_T;            /* '<S1>/currloop' */
  uint32_T IfActionSubsystem4_PREV_T;  /* '<S2>/If Action Subsystem4' */
  uint32_T IfActionSubsystem2_PREV_T;  /* '<S2>/If Action Subsystem2' */
  uint32_T speedloop_PREV_T;           /* '<S1>/speedloop' */
  int16_T Integrator_DSTATE_p;         /* '<S107>/Integrator' */
  int16_T Integrator_PREV_U_iy;        /* '<S107>/Integrator' */
  uint16_T temporalCounter_i1;         /* '<S2>/Chart1' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S2>/Switch Case' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S9>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S9>/Discrete-Time Integrator1' */
  int8_T Integrator_PrevResetState;    /* '<S210>/Integrator' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_E;/* '<S21>/Discrete-Time Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S107>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_l;  /* '<S157>/Integrator' */
  uint8_T Integrator_SYSTEM_ENABLE_ln; /* '<S55>/Integrator' */
  uint8_T DiscreteTimeIntegrator1_SYSTEM_;/* '<S11>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_o;/* '<S9>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator1_SYSTE_c;/* '<S9>/Discrete-Time Integrator1' */
  uint8_T is_active_c7_FOC_Model;      /* '<S2>/Chart1' */
  uint8_T is_c7_FOC_Model;             /* '<S2>/Chart1' */
  uint8_T Integrator_SYSTEM_ENABLE_a;  /* '<S210>/Integrator' */
  boolean_T currloop_RESET_ELAPS_T;    /* '<S1>/currloop' */
  boolean_T IfActionSubsystem4_RESET_ELAPS_;/* '<S2>/If Action Subsystem4' */
  boolean_T IfActionSubsystem2_RESET_ELAPS_;/* '<S2>/If Action Subsystem2' */
  boolean_T speedloop_RESET_ELAPS_T;   /* '<S1>/speedloop' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T ia;                         /* '<Root>/ia' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T v_bus;                      /* '<Root>/v_bus' */
  real_T Motor_OnOff;                  /* '<Root>/Motor_OnOff' */
  real32_T Speed_ref;                  /* '<Root>/Speed_ref' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T Tcmp1;                      /* '<Root>/Tcmp1' */
  real32_T Tcmp2;                      /* '<Root>/Tcmp2' */
  real32_T Tcmp3;                      /* '<Root>/Tcmp3' */
} ExtY;

/* Type definition for custom storage class: Struct */
typedef struct Gramma_tag {
  real32_T Gamma;                      /* Referenced by:
                                        * '<S22>/Constant1'
                                        * '<S22>/Constant2'
                                        */
} Gramma_type;

typedef struct LPFFilter_tag {
  real32_T LPFFilter;                  /* Referenced by: '<S20>/Constant' */
} LPFFilter_type;

typedef struct PLL_tag {
  real32_T PLLKI;                     /* Referenced by: '<S52>/Integral Gain' */
  real32_T PLLKP;                 /* Referenced by: '<S60>/Proportional Gain' */
} PLL_type;

typedef struct curr_kpki_tag {
  real32_T curr_d_ki;                  /* Referenced by:
                                        * '<S13>/Constant2'
                                        * '<S13>/Constant4'
                                        */
  real32_T curr_d_kp;                  /* Referenced by:
                                        * '<S13>/Constant1'
                                        * '<S13>/Constant3'
                                        */
} curr_kpki_type;

typedef struct motor_tag {
  real32_T L;                          /* Referenced by:
                                        * '<S22>/Gain12'
                                        * '<S22>/Gain13'
                                        * '<S22>/Gain16'
                                        * '<S22>/Gain2'
                                        */
  real32_T Pn;                         /* Referenced by:
                                        * '<S9>/Gain1'
                                        * '<S11>/Gain'
                                        * '<S12>/Gain'
                                        */
  real32_T Rs;                         /* Referenced by:
                                        * '<S22>/Gain11'
                                        * '<S22>/Gain14'
                                        */
  real32_T flux;                       /* Referenced by:
                                        * '<S22>/Constant'
                                        * '<S22>/Gain17'
                                        * '<S22>/Gain3'
                                        */
} motor_type;

typedef struct spd_kpki_tag {
  real32_T spd_ki;                   /* Referenced by: '<S207>/Integral Gain' */
  real32_T spd_kp;               /* Referenced by: '<S215>/Proportional Gain' */
} spd_kpki_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T FluxTheta;              /* '<S21>/Mod' */
extern real32_T FluxWm;                 /* '<S20>/Plus1' */
extern real32_T ialpha;                /* '<S6>/Add1' */
extern real32_T state;                 /* '<S2>/Chart1' */

/* Model entry point functions */
extern void FOC_Model_initialize(void);
extern void FOC_Model_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern Gramma_type Gramma;
extern LPFFilter_type LPFFilter;
extern PLL_type PLL;
extern curr_kpki_type curr_kpki;
extern motor_type motor;
extern spd_kpki_type spd_kpki;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S11>/Add1' : Unused code path elimination
 * Block '<S11>/Add2' : Unused code path elimination
 * Block '<S11>/Constant3' : Unused code path elimination
 * Block '<S11>/Mod1' : Unused code path elimination
 * Block '<S11>/Product' : Unused code path elimination
 * Block '<S11>/Scope' : Unused code path elimination
 * Block '<S11>/Scope1' : Unused code path elimination
 * Block '<S11>/Scope2' : Unused code path elimination
 * Block '<S11>/Scope3' : Unused code path elimination
 * Block '<S11>/Scope4' : Unused code path elimination
 * Block '<S21>/Scope' : Unused code path elimination
 * Block '<S13>/Scope' : Unused code path elimination
 * Block '<S13>/Scope1' : Unused code path elimination
 * Block '<S13>/Scope2' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope4' : Unused code path elimination
 * Block '<S2>/Scope5' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('flux_Observer/FOC_Model')    - opens subsystem flux_Observer/FOC_Model
 * hilite_system('flux_Observer/FOC_Model/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'flux_Observer'
 * '<S1>'   : 'flux_Observer/FOC_Model'
 * '<S2>'   : 'flux_Observer/FOC_Model/currloop'
 * '<S3>'   : 'flux_Observer/FOC_Model/speedloop'
 * '<S4>'   : 'flux_Observer/FOC_Model/currloop/AntiPark'
 * '<S5>'   : 'flux_Observer/FOC_Model/currloop/Chart1'
 * '<S6>'   : 'flux_Observer/FOC_Model/currloop/Clark_test'
 * '<S7>'   : 'flux_Observer/FOC_Model/currloop/If Action Subsystem'
 * '<S8>'   : 'flux_Observer/FOC_Model/currloop/If Action Subsystem1'
 * '<S9>'   : 'flux_Observer/FOC_Model/currloop/If Action Subsystem2'
 * '<S10>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem3'
 * '<S11>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem4'
 * '<S12>'  : 'flux_Observer/FOC_Model/currloop/Nonflux'
 * '<S13>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller'
 * '<S14>'  : 'flux_Observer/FOC_Model/currloop/Park'
 * '<S15>'  : 'flux_Observer/FOC_Model/currloop/SVPWM'
 * '<S16>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem4/If Action Subsystem'
 * '<S17>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem4/If Action Subsystem1'
 * '<S18>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem4/If Action Subsystem2'
 * '<S19>'  : 'flux_Observer/FOC_Model/currloop/If Action Subsystem4/If Action Subsystem3'
 * '<S20>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/LPF'
 * '<S21>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2'
 * '<S22>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/non-flux observer'
 * '<S23>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller'
 * '<S24>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Anti-windup'
 * '<S25>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/D Gain'
 * '<S26>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Filter'
 * '<S27>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Filter ICs'
 * '<S28>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/I Gain'
 * '<S29>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Ideal P Gain'
 * '<S30>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Ideal P Gain Fdbk'
 * '<S31>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Integrator'
 * '<S32>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Integrator ICs'
 * '<S33>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/N Copy'
 * '<S34>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/N Gain'
 * '<S35>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/P Copy'
 * '<S36>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Parallel P Gain'
 * '<S37>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Reset Signal'
 * '<S38>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Saturation'
 * '<S39>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Saturation Fdbk'
 * '<S40>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Sum'
 * '<S41>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Sum Fdbk'
 * '<S42>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tracking Mode'
 * '<S43>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tracking Mode Sum'
 * '<S44>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tsamp - Integral'
 * '<S45>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tsamp - Ngain'
 * '<S46>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/postSat Signal'
 * '<S47>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/preSat Signal'
 * '<S48>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Anti-windup/Passthrough'
 * '<S49>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/D Gain/Disabled'
 * '<S50>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Filter/Disabled'
 * '<S51>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Filter ICs/Disabled'
 * '<S52>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/I Gain/Internal Parameters'
 * '<S53>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Ideal P Gain/Passthrough'
 * '<S54>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S55>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Integrator/Discrete'
 * '<S56>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Integrator ICs/Internal IC'
 * '<S57>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S58>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/N Gain/Disabled'
 * '<S59>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/P Copy/Disabled'
 * '<S60>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S61>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Reset Signal/Disabled'
 * '<S62>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Saturation/Enabled'
 * '<S63>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Saturation Fdbk/Disabled'
 * '<S64>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Sum/Sum_PI'
 * '<S65>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Sum Fdbk/Disabled'
 * '<S66>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tracking Mode/Disabled'
 * '<S67>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S68>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tsamp - Integral/Passthrough'
 * '<S69>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S70>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/postSat Signal/Forward_Path'
 * '<S71>'  : 'flux_Observer/FOC_Model/currloop/Nonflux/PLL2/PID Controller/preSat Signal/Forward_Path'
 * '<S72>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller'
 * '<S73>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1'
 * '<S74>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Anti-windup'
 * '<S75>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/D Gain'
 * '<S76>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Filter'
 * '<S77>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Filter ICs'
 * '<S78>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/I Gain'
 * '<S79>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Ideal P Gain'
 * '<S80>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Ideal P Gain Fdbk'
 * '<S81>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Integrator'
 * '<S82>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Integrator ICs'
 * '<S83>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/N Copy'
 * '<S84>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/N Gain'
 * '<S85>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/P Copy'
 * '<S86>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Parallel P Gain'
 * '<S87>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Reset Signal'
 * '<S88>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Saturation'
 * '<S89>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Saturation Fdbk'
 * '<S90>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Sum'
 * '<S91>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Sum Fdbk'
 * '<S92>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tracking Mode'
 * '<S93>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tracking Mode Sum'
 * '<S94>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tsamp - Integral'
 * '<S95>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tsamp - Ngain'
 * '<S96>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/postSat Signal'
 * '<S97>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/preSat Signal'
 * '<S98>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S99>'  : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S100>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S101>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/D Gain/Disabled'
 * '<S102>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Filter/Disabled'
 * '<S103>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Filter ICs/Disabled'
 * '<S104>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/I Gain/External Parameters'
 * '<S105>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S106>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S107>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Integrator/Discrete'
 * '<S108>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Integrator ICs/Internal IC'
 * '<S109>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S110>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/N Gain/Disabled'
 * '<S111>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/P Copy/Disabled'
 * '<S112>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Parallel P Gain/External Parameters'
 * '<S113>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Reset Signal/Disabled'
 * '<S114>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Saturation/Enabled'
 * '<S115>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S116>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Sum/Sum_PI'
 * '<S117>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Sum Fdbk/Disabled'
 * '<S118>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tracking Mode/Disabled'
 * '<S119>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S120>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tsamp - Integral/Passthrough'
 * '<S121>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S122>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/postSat Signal/Forward_Path'
 * '<S123>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller/preSat Signal/Forward_Path'
 * '<S124>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Anti-windup'
 * '<S125>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/D Gain'
 * '<S126>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Filter'
 * '<S127>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Filter ICs'
 * '<S128>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/I Gain'
 * '<S129>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Ideal P Gain'
 * '<S130>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S131>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Integrator'
 * '<S132>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Integrator ICs'
 * '<S133>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/N Copy'
 * '<S134>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/N Gain'
 * '<S135>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/P Copy'
 * '<S136>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Parallel P Gain'
 * '<S137>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Reset Signal'
 * '<S138>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Saturation'
 * '<S139>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Saturation Fdbk'
 * '<S140>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Sum'
 * '<S141>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Sum Fdbk'
 * '<S142>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tracking Mode'
 * '<S143>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tracking Mode Sum'
 * '<S144>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tsamp - Integral'
 * '<S145>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tsamp - Ngain'
 * '<S146>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/postSat Signal'
 * '<S147>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/preSat Signal'
 * '<S148>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S149>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S150>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S151>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/D Gain/Disabled'
 * '<S152>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Filter/Disabled'
 * '<S153>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Filter ICs/Disabled'
 * '<S154>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/I Gain/External Parameters'
 * '<S155>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S156>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S157>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Integrator/Discrete'
 * '<S158>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S159>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S160>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/N Gain/Disabled'
 * '<S161>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/P Copy/Disabled'
 * '<S162>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Parallel P Gain/External Parameters'
 * '<S163>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Reset Signal/Disabled'
 * '<S164>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Saturation/Enabled'
 * '<S165>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S166>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Sum/Sum_PI'
 * '<S167>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S168>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tracking Mode/Disabled'
 * '<S169>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S170>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S171>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S172>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S173>' : 'flux_Observer/FOC_Model/currloop/PID_Controller/PID Controller1/preSat Signal/Forward_Path'
 * '<S174>' : 'flux_Observer/FOC_Model/currloop/SVPWM/AntiClark'
 * '<S175>' : 'flux_Observer/FOC_Model/currloop/SVPWM/ei_t'
 * '<S176>' : 'flux_Observer/FOC_Model/speedloop/PID Controller'
 * '<S177>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Anti-windup'
 * '<S178>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/D Gain'
 * '<S179>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Filter'
 * '<S180>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Filter ICs'
 * '<S181>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/I Gain'
 * '<S182>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Ideal P Gain'
 * '<S183>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Ideal P Gain Fdbk'
 * '<S184>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Integrator'
 * '<S185>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Integrator ICs'
 * '<S186>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/N Copy'
 * '<S187>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/N Gain'
 * '<S188>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/P Copy'
 * '<S189>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Parallel P Gain'
 * '<S190>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Reset Signal'
 * '<S191>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Saturation'
 * '<S192>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Saturation Fdbk'
 * '<S193>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Sum'
 * '<S194>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Sum Fdbk'
 * '<S195>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tracking Mode'
 * '<S196>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tracking Mode Sum'
 * '<S197>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tsamp - Integral'
 * '<S198>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tsamp - Ngain'
 * '<S199>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/postSat Signal'
 * '<S200>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/preSat Signal'
 * '<S201>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S202>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S203>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S204>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/D Gain/Disabled'
 * '<S205>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Filter/Disabled'
 * '<S206>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Filter ICs/Disabled'
 * '<S207>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/I Gain/Internal Parameters'
 * '<S208>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Ideal P Gain/Passthrough'
 * '<S209>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S210>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Integrator/Discrete'
 * '<S211>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Integrator ICs/Internal IC'
 * '<S212>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S213>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/N Gain/Disabled'
 * '<S214>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/P Copy/Disabled'
 * '<S215>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S216>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Reset Signal/External Reset'
 * '<S217>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Saturation/Enabled'
 * '<S218>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Saturation Fdbk/Disabled'
 * '<S219>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Sum/Sum_PI'
 * '<S220>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Sum Fdbk/Disabled'
 * '<S221>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tracking Mode/Disabled'
 * '<S222>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S223>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tsamp - Integral/Passthrough'
 * '<S224>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S225>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/postSat Signal/Forward_Path'
 * '<S226>' : 'flux_Observer/FOC_Model/speedloop/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_FOC_Model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
