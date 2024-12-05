
//
// Included Files
//

#include "F28x_Project.h"
#include "Init.h"
#include "math.h"
#include "main.h"
#include "pid.h"
//int adcc_soc0 = 0;
//int adcc_soc1 = 0;
PID_STRUCT*   psPID;

void main(void)
{
    InitSysCtrl();
//    Init_GPIO();
    SetupGpio();
    Init_PIE();
    EALLOW;
    PieVectTable.EPWM6_INT = &ePWM6ISR;            // Function for estimate interrupt
    PieVectTable.ADCA1_INT = &adcA3ISR;            // Function for estimate interrupt
    PieVectTable.ADCA2_INT = &adcA9ISR;            // Function for estimate interrupt
    PieVectTable.ADCC1_INT = &adcC3ISR;            // Function for estimate interrupt
    PieVectTable.ADCC2_INT = &adcC5ISR;            // Function for estimate interrupt
    EDIS;
    Init_ePWM();
    Init_ADC();
    Init_ADCSOC();
    psPID = Init_PID();

    while(1){

    }

}
int a = 0;
int i=0;
// 計算目標duty cycle轉換後的CMPA值之中斷
__interrupt void ePWM6ISR(void)
{
    EALLOW;
    EPwm6Regs.ETCLR.bit.INT = 1;
    a++;

    psPID->RefSetPoint = iL_ref;
    psPID->Feedback_I = current_f;
    psPID->Feedback_V = voltage3_f;
    // CC
    if (mode==0){
        iL_ref = iL_refm1 + Ts/Delay_tau * (iL_cmd - iL_refm1);
        psPID->Feedback_Value = psPID->Feedback_I;
        psPID->RefSetPoint = iL_refm1 + Ts/Delay_tau * (iL_cmd - iL_refm1);
        PID_Process(psPID);
        iL_refm1 = iL_ref;
    }
    // CV
    if (mode==1){
        V_ref = V_refm1 + Ts/Delay_tau * (V_cmd - V_refm1);
        psPID->Feedback_Value = psPID->Feedback_V;
        psPID->RefSetPoint = V_refm1 + Ts/Delay_tau * (V_cmd - V_refm1);
        PID_Process(psPID);
        V_refm1 = V_ref;
    }
    EPwm6Regs.CMPA.bit.CMPA = (int)(psPID->Output*EPwm6Regs.TBPRD);


//    float adc_val1=0;
//    adc_val1 = AdcaResultRegs.ADCRESULT0;
//    voltage3_a = adc_val1*0.00122;
//    float adc_val2=0;
//    adc_val2 = AdcaResultRegs.ADCRESULT1;
//    voltage1_a = adc_val2*0.00122;
//    float adc_val3=0;
//    adc_val3 = AdccResultRegs.ADCRESULT1;
//    voltage2_a = adc_val3*0.00122;
//    float adc_val4=0;
//    adc_val4 = AdccResultRegs.ADCRESULT0;
//    current_a = (adc_val4-2048)*0.00735;
//    voltage3_a = 5;

    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP3;
    EPwm6Regs.ETCLR.bit.INT = 1;
    EDIS;
}

// 輸出電池之電壓
__interrupt void adcA3ISR(void)
{
    EALLOW;
//    int i=0;
    Uint16 adc_val1=0;
    adc_val1 = AdcaResultRegs.ADCRESULT0;
    voltage3_a = 0;
    voltage3[voltage3_d]=adc_val1*0.000122;
    for (i=0;i<10;i++){
        voltage3_a+=voltage3[i];
    }
    voltage3_f = voltage3_a;
    voltage3_d++;
    if (voltage3_d>=10){
        voltage3_d=0;
    }

    AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1|PIEACK_GROUP10;
    EDIS;
}

// 輸入電池1之電壓
__interrupt void adcA9ISR(void)
{
    EALLOW;
    Uint16 adc_val2=0;
    adc_val2 = AdcaResultRegs.ADCRESULT1;
    voltage1_a = 0;
//    voltage1_a = adc_val2*0.00122;
    voltage1[voltage1_d]=adc_val2*0.000122;
    for (i=0;i<10;i++){
        voltage1_a+=voltage1[i];
    }
    voltage1_f = voltage1_a;
    voltage1_d++;
    if (voltage1_d>=10){
        voltage1_d=0;
    }

//    voltage1_a += 1e-3;
    AdcaRegs.ADCINTOVFCLR.bit.ADCINT2 = 1;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 1 <- INT1 flag cleared
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1|PIEACK_GROUP10;

    EDIS;
}

// 輸入電池2之電壓
__interrupt void adcC3ISR(void)
{
    EALLOW;

//    int i=0;
    Uint16 adc_val3=0;
    adc_val3 = AdccResultRegs.ADCRESULT1;
    voltage2_a = 0;
    voltage2[voltage2_d]=adc_val3*0.000122;
    for (i=0;i<10;i++){
        voltage2_a+=voltage2[i];
    }
    voltage2_f = voltage2_a;
    voltage2_d++;
    if (voltage2_d>=10){
        voltage2_d=0;
    }

    AdccRegs.ADCINTOVFCLR.bit.ADCINT2 = 1;
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 1 <- INT1 flag cleared
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1|PIEACK_GROUP10;
    EDIS;
}

// 輸出電流
__interrupt void adcC5ISR(void)
{
    EALLOW;
//    int i=0;
    float adc_val4=0;
    adc_val4 = AdccResultRegs.ADCRESULT0;
    current_a = 0;
    current_v = (adc_val4/4096)*3.3;
    current[current_d] = (current_v-2.362)*(3.5/3.3)*0.6024;
//    current[current_d]=(adc_val4-2925)*0.000156;
    for (i=0;i<10;i++){
        current_a+=current[i];
    }
    current_f = current_a;
//    current_a = current_a/10;
    current_d++;
    if (current_d>=10){
        current_d=0;
    }
//    current_a += 1e-3;
    AdccRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 1 <- INT1 flag cleared
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1|PIEACK_GROUP10;
    EDIS;
}



void SetupGpio(void)
{
    InitGpio();
    EALLOW;
//GPIO10 = PWM6A
    GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 0; //
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;  //設定成EPWM功能
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;   //Output
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;   //使用Pull-up電阻
    GpioDataRegs.GPACLEAR.bit.GPIO10 = 1; //設置輸出為0
//GPIO11 = PWM6B
    GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 0; //
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;  //設定成EPWM功能
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;   //Output
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;   //使用Pull-up電阻
    GpioDataRegs.GPACLEAR.bit.GPIO11 = 1; //設置輸出為0
    EDIS;
}



