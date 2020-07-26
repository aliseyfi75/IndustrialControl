/*
 * Subsystem_sf.h
 *
 * Code generation for model "Subsystem_sf".
 *
 * Model version              : 1.31
 * Simulink Coder version : 8.5 (R2013b) 08-Aug-2013
 * C source code generated on : Tue May 23 06:51:52 2017
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_Subsystem_sf_h_
#define RTW_HEADER_Subsystem_sf_h_
#ifndef Subsystem_sf_COMMON_INCLUDES_
# define Subsystem_sf_COMMON_INCLUDES_
#include <stdlib.h>
#include <float.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#define S_FUNCTION_NAME                Subsystem_sf
#define S_FUNCTION_LEVEL               2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "multiword_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                 /* Subsystem_sf_COMMON_INCLUDES_ */

#include "Subsystem_sf_types.h"

/* Block signals (auto storage) */
typedef struct {
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Gain1;                        /* '<S1>/Gain1' */
  real_T StateSpace;                   /* '<S1>/State-Space' */
  real_T StateSpace1;                  /* '<S1>/State-Space1' */
  real_T StateSpace2;                  /* '<S1>/State-Space2' */
} B_Subsystem_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T StateSpace3_CSTATE;           /* '<S1>/State-Space3' */
  real_T StateSpace_CSTATE;            /* '<S1>/State-Space' */
  real_T StateSpace1_CSTATE;           /* '<S1>/State-Space1' */
  real_T StateSpace2_CSTATE;           /* '<S1>/State-Space2' */
} X_Subsystem_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T StateSpace3_CSTATE;           /* '<S1>/State-Space3' */
  real_T StateSpace_CSTATE;            /* '<S1>/State-Space' */
  real_T StateSpace1_CSTATE;           /* '<S1>/State-Space1' */
  real_T StateSpace2_CSTATE;           /* '<S1>/State-Space2' */
} XDot_Subsystem_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace3_CSTATE;        /* '<S1>/State-Space3' */
  boolean_T StateSpace_CSTATE;         /* '<S1>/State-Space' */
  boolean_T StateSpace1_CSTATE;        /* '<S1>/State-Space1' */
  boolean_T StateSpace2_CSTATE;        /* '<S1>/State-Space2' */
} XDis_Subsystem_T;

/* Continuous State Absolute Tolerance  */
typedef struct {
  real_T StateSpace3_CSTATE;           /* '<S1>/State-Space3' */
  real_T StateSpace_CSTATE;            /* '<S1>/State-Space' */
  real_T StateSpace1_CSTATE;           /* '<S1>/State-Space1' */
  real_T StateSpace2_CSTATE;           /* '<S1>/State-Space2' */
} CStateAbsTol_Subsystem_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T *In1;                         /* '<Root>/In1' */
} ExternalUPtrs_Subsystem_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T *Out1;                        /* '<Root>/Out1' */
} ExtY_Subsystem_T;

/* Parameters (auto storage) */
struct P_Subsystem_T_ {
  real_T tmp;                          /* Variable: tmp
                                        * Referenced by:
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain1'
                                        *   '<S1>/State-Space'
                                        *   '<S1>/State-Space1'
                                        *   '<S1>/State-Space2'
                                        *   '<S1>/State-Space3'
                                        *   '<S1>/dead time 1'
                                        */
};

extern P_Subsystem_T Subsystem_DefaultP;

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
 * hilite_system('Model/Subsystem')    - opens subsystem Model/Subsystem
 * hilite_system('Model/Subsystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Model'
 * '<S1>'   : 'Model/Subsystem'
 * '<S2>'   : 'Model/Subsystem/Band-Limited White Noise'
 */
#endif                                 /* RTW_HEADER_Subsystem_sf_h_ */
