/*
 * Trial License - for use to evaluate programs for possible purchase as
 * an end-user only.
 *
 * File: Total_pjt.h
 *
 * Code generated for Simulink model 'Total_pjt'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jan 22 14:08:45 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Total_pjt_h_
#define RTW_HEADER_Total_pjt_h_
#ifndef Total_pjt_COMMON_INCLUDES_
#define Total_pjt_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Total_pjt_COMMON_INCLUDES_ */

#include "Total_pjt_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T counter;                     /* '<S1>/Sine Wave' */
} DW_Total_pjt_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T pushSwitch;                /* '<Root>/pushSwitch' */
} ExtU_Total_pjt_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint16_T blueLed;                    /* '<Root>/blueLed' */
} ExtY_Total_pjt_T;

/* Real-time Model Data Structure */
struct tag_RTM_Total_pjt_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Total_pjt_T Total_pjt_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Total_pjt_T Total_pjt_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Total_pjt_T Total_pjt_Y;

/* Model entry point functions */
extern void Total_pjt_initialize(void);
extern void Total_pjt_step(void);
extern void Total_pjt_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Total_pjt_T *const Total_pjt_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Total_pjt'
 * '<S1>'   : 'Total_pjt/Subsystem'
 * '<S2>'   : 'Total_pjt/Subsystem/sw_off'
 * '<S3>'   : 'Total_pjt/Subsystem/sw_on '
 */
#endif                                 /* RTW_HEADER_Total_pjt_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
