/*
 * pid.c
 *
 */

#include    "pid.h"


static PID_STRUCT sPID;

PID_STRUCT* Init_PID(void)
{
    // Set PID Coefficients
    sPID.Kp = 0.00055; // below 200Hz: 0.01
    sPID.Ki = 0.01; // below 200Hz: 0.015 3
    //sPID.Kd = 0.005;

    sPID.LastError_1 = 0;
    sPID.LastError_2 = 0;

    // Set PID Setpoint
    sPID.RefSetPoint = 0.5;

    sPID.OutputMax = 0.9;
    sPID.OutputMin = 0.1;

    sPID.lastPID = EPwm6Regs.CMPA.bit.CMPA;
    sPID.AdcCounter = 0;
    sPID.Counter = 0;
    sPID.Fs = 1e5;
    sPID.Tau_iL = 1e-4;

    return &sPID;

}


void PID_Process(PID_STRUCT* psPID)
{
    // Compute current error
    psPID->Error = (psPID->RefSetPoint - psPID->Feedback_Value);

    // Compute PID
    psPID->Preoutput = psPID->lastPID  + (psPID->Kp * psPID->Error/psPID->Fs/psPID->Tau_iL);

    psPID->Preoutput += (psPID->Kp * psPID->Error);

    psPID->Output = psPID->Preoutput;

    // Limit the output
    if(psPID->Output > psPID->OutputMax)
    {
        psPID->Output = psPID->OutputMax;
    }
    else if(psPID->Output < psPID->OutputMin)
    {
        psPID->Output = psPID->OutputMin;
    }

    psPID->LastError_1 = psPID->Error;
    psPID->lastPID = psPID->Output;

}



