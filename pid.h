/*
 * pid.h
 *
 */

#ifndef PID_H_
#define PID_H_

#include "F28x_Project.h"



typedef struct PID_STRUCT{

    float   RefSetPoint;             // Input: Reference input
    uint16_t  Feedback_AdcValue[8];    // Input: Feedback input
    float  Feedback_V;
    float  Feedback_I;
    float  Feedback_Value;
    uint16_t  AdcCounter;
    uint16_t  Counter;


    float  Error;         // Variable: Error
    float  LastError_1;
    float  LastError_2;
    float  incPID;

    float  Kp;          // Parameter: Proportional gain
    float  Ki;          // Parameter: Integral gain
    float  Kd;          // Parameter: Derivative gain

    float  OutputMax;      // Parameter: Maximum output
    float  OutputMin;      // Parameter: Minimum output
    float  Preoutput;         // Output: PID output
    float  Output;         // Output: PID output
    float  OutPreSat;
    float  lastPID;
    float  Fs;
    float  Tau_iL;

    float  outputorg;


}PID_STRUCT;


extern PID_STRUCT* Init_PID(void);
extern void PID_Process(PID_STRUCT* psPID);




#endif /* PID_H_ */
