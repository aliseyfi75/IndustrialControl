/*
 * Subsystem_sid.h
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
 *
 * SOURCES: Subsystem_sf.c
 */

/* statically allocated instance data for model: Subsystem */
{
  extern P_Subsystem_T Subsystem_DefaultP;

  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static B_Subsystem_T sfcnB;
      void *b = (real_T *) &sfcnB;
      ssSetLocalBlockIO(rts, b);
      (void) memset(b, 0,
                    sizeof(B_Subsystem_T));
    }

    /* model parameters */
    ssSetLocalDefaultParam(rts, (real_T *) &Subsystem_DefaultP);

    /* model checksums */
    ssSetChecksumVal(rts, 0, 1901214054U);
    ssSetChecksumVal(rts, 1, 3442290532U);
    ssSetChecksumVal(rts, 2, 2827833653U);
    ssSetChecksumVal(rts, 3, 1091222260U);
  }
}
