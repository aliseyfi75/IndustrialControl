/*
 * Subsystem_sf.c
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
#include <math.h>
#include "Subsystem_sf.h"
#include "Subsystem_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *Subsystem_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

/* Forward declaration for local functions */
static real_T Subs_rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
static real_T Subs_rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T Subsystem_sf_rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

static real_T Subs_rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

static real_T Subs_rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T y;
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * Subs_rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * Subs_rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

/* Initial conditions for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  X_Subsystem_T *_rtX;
  _rtX = ((X_Subsystem_T *) ssGetContStates(S));

  /* InitializeConditions for StateSpace: '<S1>/State-Space3' */
  _rtX->StateSpace3_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/State-Space' */
  _rtX->StateSpace_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/State-Space1' */
  _rtX->StateSpace1_CSTATE = 0.0;

  /* InitializeConditions for StateSpace: '<S1>/State-Space2' */
  _rtX->StateSpace2_CSTATE = 0.0;
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Check for invalid switching between solver types */
  if (!ssIsVariableStepSolver(S)) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "a solver type of fixed-step "
                     "because this S-Function was created from a model with "
                     "solver type of variable-step solver and it has continuous time blocks. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

#  endif

  Subsystem_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
    /* Start for RandomNumber: '<S2>/White Noise' */
    ((uint32_T *)ssGetDWork(S, 3))[0] = 1529675776U;
    ((real_T *)ssGetDWork(S, 0))[0] = Subs_rt_nrand_Upu32_Yd_f_pw_snf
      (&((uint32_T *)ssGetDWork(S, 3))[0]);

    /* Start for TransportDelay: '<S1>/dead time 1' */
    {
      real_T *pBuffer = &((real_T*) ssGetDWork(S, 1))[1];
      ((int_T*) ssGetDWork(S, 4))[0] = 0;
      ((int_T*) ssGetDWork(S, 4))[1] = 0;
      ((int_T*) ssGetDWork(S, 4))[2] = 0;
      ((int_T*) ssGetDWork(S, 4))[3] = 1024;
      pBuffer[0] = 0.0;
      pBuffer[1024] = ssGetT(S);
      ((pointer_T*) ssGetDWork(S, 2))[0] = (void *) &pBuffer[0];
      ((pointer_T*) ssGetDWork(S, 2))[1] = (void *) &pBuffer[1024];
    }
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* local block i/o variables */
  real_T rtb_deadtime1;
  B_Subsystem_T *_rtB;
  X_Subsystem_T *_rtX;
  _rtX = ((X_Subsystem_T *) ssGetContStates(S));
  _rtB = ((B_Subsystem_T *) ssGetLocalBlockIO(S));
  if (ssIsSampleHit(S, 2, 0)) {
    /* Gain: '<S1>/Gain' incorporates:
     *  Gain: '<S2>/Output'
     *  RandomNumber: '<S2>/White Noise'
     */
    _rtB->Gain = (0.025 * (*(real_T *)(mxGetData(tmp(S)))) + 0.2) *
      (0.60553007081949839 * ((real_T *)ssGetDWork(S, 0))[0]);
  }

  if (1) {
    /* StateSpace: '<S1>/State-Space3' */
    rtb_deadtime1 = 0.0;
    rtb_deadtime1 += _rtX->StateSpace3_CSTATE;

    /* Outport: '<Root>/Out1' incorporates:
     *  Sum: '<S1>/Add'
     */
    ((real_T *)ssGetOutputPortSignal(S, 0))[0] = _rtB->Gain + rtb_deadtime1;

    /* TransportDelay: '<S1>/dead time 1' */
    {
      real_T **uBuffer = (real_T**)&((pointer_T*) ssGetDWork(S, 2))[0];
      real_T **tBuffer = (real_T**)&((pointer_T*) ssGetDWork(S, 2))[1];
      real_T simTime = ssGetT(S);
      real_T tMinusDelay = simTime - (3.0 * sqrt( (*(real_T *)(mxGetData(tmp(S))))
        ));
      rtb_deadtime1 = Subsystem_sf_rt_TDelayInterpolate(
        tMinusDelay,
        0.0,
        *tBuffer,
        *uBuffer,
        ((int_T*) ssGetDWork(S, 4))[3],
        &((int_T*) ssGetDWork(S, 4))[2],
        ((int_T*) ssGetDWork(S, 4))[0],
        ((int_T*) ssGetDWork(S, 4))[1],
        0.0,
        1,
        (boolean_T) (ssIsMinorTimeStep(S) && (ssGetTimeOfLastOutput(S) == ssGetT
        (S))));
    }

    /* Gain: '<S1>/Gain1' */
    _rtB->Gain1 = (*(real_T *)(mxGetData(tmp(S)))) / 1.5 * rtb_deadtime1;

    /* StateSpace: '<S1>/State-Space' */
    _rtB->StateSpace = 0.0;
    _rtB->StateSpace += _rtX->StateSpace_CSTATE;

    /* StateSpace: '<S1>/State-Space1' */
    _rtB->StateSpace1 = 0.0;
    _rtB->StateSpace1 += _rtX->StateSpace1_CSTATE;

    /* StateSpace: '<S1>/State-Space2' */
    _rtB->StateSpace2 = 0.0;
    _rtB->StateSpace2 += _rtX->StateSpace2_CSTATE;
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  if (ssIsSampleHit(S, 2, 0)) {
    /* Update for RandomNumber: '<S2>/White Noise' */
    ((real_T *)ssGetDWork(S, 0))[0] = Subs_rt_nrand_Upu32_Yd_f_pw_snf
      (&((uint32_T *)ssGetDWork(S, 3))[0]);
  }

  if (1) {
    /* Update for TransportDelay: '<S1>/dead time 1' */
    {
      real_T **uBuffer = (real_T**)&((pointer_T*) ssGetDWork(S, 2))[0];
      real_T **tBuffer = (real_T**)&((pointer_T*) ssGetDWork(S, 2))[1];
      real_T simTime = ssGetT(S);
      ((int_T*) ssGetDWork(S, 4))[1] = ((((int_T*) ssGetDWork(S, 4))[1] <
        (((int_T*) ssGetDWork(S, 4))[3]-1)) ? (((int_T*) ssGetDWork(S, 4))[1]+1)
        : 0);
      if (((int_T*) ssGetDWork(S, 4))[1] == ((int_T*) ssGetDWork(S, 4))[0]) {
        ((int_T*) ssGetDWork(S, 4))[0] = ((((int_T*) ssGetDWork(S, 4))[0] <
          (((int_T*) ssGetDWork(S, 4))[3]-1)) ? (((int_T*) ssGetDWork(S, 4))[0]+
          1) : 0);
      }

      (*tBuffer)[((int_T*) ssGetDWork(S, 4))[1]] = simTime;
      (*uBuffer)[((int_T*) ssGetDWork(S, 4))[1]] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[0];
    }
  }

  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
#define MDL_DERIVATIVES

static void mdlDerivatives(SimStruct *S)
{
  B_Subsystem_T *_rtB;
  X_Subsystem_T *_rtX;
  XDot_Subsystem_T *_rtXdot;
  _rtXdot = ((XDot_Subsystem_T *) ssGetdX(S));
  _rtX = ((X_Subsystem_T *) ssGetContStates(S));
  _rtB = ((B_Subsystem_T *) ssGetLocalBlockIO(S));

  /* Derivatives for StateSpace: '<S1>/State-Space3' */
  _rtXdot->StateSpace3_CSTATE = 0.0;
  _rtXdot->StateSpace3_CSTATE += -2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtX->StateSpace3_CSTATE;
  _rtXdot->StateSpace3_CSTATE += 2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtB->StateSpace2;

  /* Derivatives for StateSpace: '<S1>/State-Space' */
  _rtXdot->StateSpace_CSTATE = 0.0;
  _rtXdot->StateSpace_CSTATE += -2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtX->StateSpace_CSTATE;
  _rtXdot->StateSpace_CSTATE += 2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtB->Gain1;

  /* Derivatives for StateSpace: '<S1>/State-Space1' */
  _rtXdot->StateSpace1_CSTATE = 0.0;
  _rtXdot->StateSpace1_CSTATE += -2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtX->StateSpace1_CSTATE;
  _rtXdot->StateSpace1_CSTATE += 2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtB->StateSpace;

  /* Derivatives for StateSpace: '<S1>/State-Space2' */
  _rtXdot->StateSpace2_CSTATE = 0.0;
  _rtXdot->StateSpace2_CSTATE += -2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtX->StateSpace2_CSTATE;
  _rtXdot->StateSpace2_CSTATE += 2.0 / (*(real_T *)(mxGetData(tmp(S)))) *
    _rtB->StateSpace1;
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

/* This function checks the attributes of tunable parameters. */
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

static void mdlCheckParameters(SimStruct *S)
{
  /* Parameter check for 'tmp' */
  if (mxIsComplex(ssGetSFcnParam(S, 0))) {
    ssSetErrorStatus(S,"Parameter 'tmp' has to be a non complex array.");
    return;
  }

  if (!mxIsDouble(ssGetSFcnParam(S, 0))) {
    ssSetErrorStatus(S,"Parameter 'tmp' has to be a double array.");
    return;
  }

  if ((mxGetNumberOfDimensions(ssGetSFcnParam(S, 0)) != 2) ||
      (mxGetDimensions(ssGetSFcnParam(S, 0))[0] != 1) ||
      (mxGetDimensions(ssGetSFcnParam(S, 0))[1] != 1) ) {
    ssSetErrorStatus(S,"Parameter 'tmp' has to be a [1x1] array.");
    return;
  }
}

#endif                                 /* MDL_CHECK_PARAMETERS */

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  include "Subsystem_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 3);           /* Number of sample times */
  ssSetNumContStates(S, 4);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */
  ssSetZCCacheNeedsReset(S, 0);
  ssSetDerivCacheNeedsReset(S, 0);

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 1))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.0);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 1))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 1))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortSampleTime(S, 0, 0.0);
    ssSetInputPortOffsetTime(S, 0, 1.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 5)) {
    return;
  }

  /* '<S2>/White Noise': NextOutput */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);

  /* '<S1>/dead time 1': RWORK */
  ssSetDWorkName(S, 1, "DWORK1");
  ssSetDWorkWidth(S, 1, 2049);

  /* '<S1>/dead time 1': PWORK */
  ssSetDWorkName(S, 2, "DWORK2");
  ssSetDWorkWidth(S, 2, 2);
  ssSetDWorkDataType(S, 2, SS_POINTER);

  /* '<S2>/White Noise': RandSeed */
  ssSetDWorkName(S, 3, "DWORK3");
  ssSetDWorkWidth(S, 3, 1);
  ssSetDWorkDataType(S, 3, SS_UINT32);

  /* '<S1>/dead time 1': IWORK */
  ssSetDWorkName(S, 4, "DWORK4");
  ssSetDWorkWidth(S, 4, 4);
  ssSetDWorkDataType(S, 4, SS_INTEGER);

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 1);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, true);
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.0);
  ssSetSampleTime(S, 1, 0.0);
  ssSetSampleTime(S, 2, 0.3);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
  ssSetOffsetTime(S, 1, 1.0);
  ssSetOffsetTime(S, 2, 0.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               Subsystem_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
