/*
 * Init.c
 *
 */

#include "F28x_Project.h"
#include "Init.h"


//void Init_GPIO(void)
//{
//    // Initialize GPIO and configure the GPIO pin as a push-pull output
//    InitGpio();
//    EALLOW;
//    // �����Ҧ�GPIO�����W�ԡA��֥\�v�l��
//    GpioCtrlRegs.GPAPUD.all = 0xFFFFFFFF;
//    // Disable internal pull-up for the selected output pins for reduced power consumption
//    // Pull-ups can be enabled or disabled by the user.
//    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO10 (EPWM6A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO11 (EPWM6B)
//
//    // Configure EPWM-6 pins using GPIO regs This specifies which of the possible GPIO pins will be EPWM1 functional pins.
//    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
//    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
//
//    //------------------------------------------------------------------------------------------------------
//    EDIS;
//}


void Init_PIE(void)
{

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;
    PieCtrlRegs.PIECTRL.bit.ENPIE  =  1;  // Enable the PIE Vector Table

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    InitPieVectTable();

    PieCtrlRegs.PIEIER3.bit.INTx6= 1;  // INT3.6 => EPWM6���_
//    PieCtrlRegs.PIEIER1.bit.INTx7= 1;  // INT1.7 => TIMER0���_
    PieCtrlRegs.PIEIER1.bit.INTx1= 1;  // INT1.1 => ADCA1���_
    PieCtrlRegs.PIEIER1.bit.INTx3= 1;  // INT1.3 => ADCC1���_
    PieCtrlRegs.PIEIER10.bit.INTx2= 1;  // INT10.2 => ADCA2���_
    PieCtrlRegs.PIEIER10.bit.INTx10= 1;  // INT10.10 => ADCC2���_
    IER |= M_INT3;
    IER |= M_INT1;
    IER |= M_INT10;

    EINT;
    ERTM;

}


void Init_CpuTimer(void)
{

    EALLOW;

//    //�]�wTimer0
//    //  ��l�Ʀ�} CPU Timer0 ��}
//    CpuTimer0.RegsAddr = &CpuTimer0Regs;
//    //  �]�w�g���Ȧs���ATSYSCLK = 10ns�A�C�g�L�@��TSYSCLK�ATimer�N��1�A���0��ǻ����_�n�D�ñNTimer����^PRD
//    CpuTimer0Regs.PRD.all  = 500; //TSYSCLK*PRD = Period = 10n*500 = 5us
//    //  �]�w���W���A�����D�g��0.2s���ݥΨ���W���A���]��0�Y�i
//    CpuTimer0Regs.TPR.all  = 0;
//    CpuTimer0Regs.TPRH.all = 0;
//    //  TSS : �Ȱ�Timer�p�ơCTSS = 1 => �Ȱ�Timer�p�ơFTSS = 0 => �}��Timer�p�ơC
//    CpuTimer0Regs.TCR.bit.TSS = 0;
//    //  TIE : �ҥ�Timer0���_�CTIE = 1 => �ҥ�Timer���_�FTIE = 0 => ����Timer���_�C
//    CpuTimer0Regs.TCR.bit.TIE = 1;
//    //  ��l��TIF�C��Timer�ƨ�0�ɡATIF = 1�A�òM���ӺX�Ш�TIF = 0�A�}�l�U�@���p�ơC
//    CpuTimer0Regs.TCR.bit.TIF = 1;
//    //  ��l�Ƥ��_�p�ƾ��C���_�p�ƾ� : ����Timer0���_����F�X���C
//    CpuTimer0.InterruptCount = 0;


//    CpuTimer0Regs.TCR.bit.TRB = 1;
//    CpuTimer0Regs.TCR.bit.SOFT=0;
//    CpuTimer0Regs.TCR.bit.FREE=0;
//    CpuTimer0Regs.TCR.bit.TIE = 1;
//    CpuTimer0Regs.TCR.all = 0x4000;


    //
        // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
        // which is connected to CPU-Timer 1, and CPU int 14, which is connected
        // to CPU-Timer 2
        //
//        IER |= M_INT1;
//        IER |= M_INT13;
//        IER |= M_INT14;

        //
        // Enable TINT0 in the PIE: Group 1 interrupt 7
        //
//        PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

        //
        // Enable global Interrupts and higher priority real-time debug events
        //
//        EINT;
//        ERTM;

/*
    // Initialize the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    InitCpuTimers();
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 100MHz CPU Freq, 1 second Period (in uSeconds)
    ConfigCpuTimer(&CpuTimer0, 100, 1000000);
    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers, the below settings must also be
    // be updated.
    //
    CpuTimer0Regs.TCR.all = 0x4000;
    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int 14, which is connected
    // to CPU-Timer 2
    //
    IER |= M_INT1;
    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;
    ERTM;
*/

        EDIS;
}


void Init_ePWM(void)
{
    EALLOW;
    //TB submodule----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //�p�ƾ�TBCTR�P�g��PRD�]�w
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //�ҥ�CPU��EPWM��Clock(SYSCLK)
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
    //�]�w���W���C���]��0�A��TBCLK = SYSCLK = 100MHz�AT_TBCLK = 1/100M = 10ns�C
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm6Regs.TBCTL.bit.CLKDIV = 0;
    //�]�wFREE_SOFT�C�]�wFREE_SOFT = 2 => TBCTR�ۥѹB��(���`�p��)�A�YFREE_SOFT��0��1�N����TBCTR�p�ƪ��A�C
    EPwm6Regs.TBCTL.bit.FREE_SOFT = 2;
    //�]�w�p�ƾ��p�ƼҦ��ACTRMOD = 0 => �W�ƼҦ��C
    EPwm6Regs.TBCTL.bit.CTRMODE = 0;
    //��l�ƭp�ƾ�TBCTR�C
    EPwm6Regs.TBCTR = 0;
    //�]�wPRD�վ�EPWM�g���A�U�ƪ��A�C
    EPwm6Regs.TBPRD = 999; //(1+PRD)*T_TBCLK = 1000*10n = 10us = T_PWM => F_PWM = 1/T_PWM = 100kHz�C
    //�]�wPRDLD�A���TBPRD�ȮɡA�վ�Ū���sTBPRD�Ȫ��ɾ��A��ĳ�ϥ�Shadow Mode�C
    EPwm6Regs.TBCTL.bit.PRDLD = 0;
    //�]�wPRDLDSYNC�AShadow Mode�����w����C
    EPwm6Regs.TBCTL2.bit.PRDLDSYNC = 0; //���TBPRD�ɡA��TBCTR�ƨ�0�A�~�|Load�s��TBCTR�C

    //CC submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //�]�w�����CMPA
    EPwm6Regs.CMPA.bit.CMPA = 0.5*(EPwm6Regs.TBPRD);
    //�]�w�����CMPB
    EPwm6Regs.CMPB.bit.CMPB = EPwm6Regs.CMPA.bit.CMPA;
    //�]�wSHDWxMODE�A���CMPx�ȮɡA�վ�Ū���sCMPx�Ȫ��ɾ��A��ĳ�ϥ�Shadow Mode�C
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //�]�wLOADxSYNC�AShadow Mode�����w����CLOADxMODE = 0 => �ھ�LOADxMODE��Load�s��CMPx
    EPwm6Regs.CMPCTL.bit.LOADASYNC = 0;
    EPwm6Regs.CMPCTL.bit.LOADBSYNC = 0;
    //�]�wLOADxMODE�CLOADxMODE = 0 => ���CMPx�ɡA��p�ƾ�TBCTR�ƨ�0�~�|Load�s��CMPx
    EPwm6Regs.CMPCTL.bit.LOADAMODE = 0;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = 0;

    //AQ submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //�W�ƼҦ��ATBCTR�ƨ�ZRO��SET(EPWM6A��XHigh)�A�ƨ�CMPA��CLEAR(EPWM6A��XLow)�C
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm6Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;
    EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    //�]�wRLDCSF�վ�Ū���n�鱱��T�����ɾ��C
    EPwm6Regs.AQSFRC.bit.RLDCSF = 0;
    //�����D���|�ϥΨ�n��j��EPWM��X => CSFA/CSFB = 0 => �����n��j��EPWM6A/EPWM6B�C
    EPwm6Regs.AQCSFRC.bit.CSFA = 0;
    EPwm6Regs.AQCSFRC.bit.CSFB = 0;

    //DB submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    EPwm6Regs.DBCTL.bit.IN_MODE = 0; // ���|A&B�ұĥ�EPWMxA�T����
    EPwm6Regs.DBCTL.bit.DEDB_MODE = 0; // ���O�ͦ��W�ɽt����H�ΤU���t����T��
    EPwm6Regs.DBCTL.bit.POLSEL = 2; // �W�ɽt����T�����ϦV�A�U���t����T���ϦV
    EPwm6Regs.DBCTL.bit.OUT_MODE = 3; // ���|A���W�W�ɽt����T���A���|B���W�U���t����T��
    EPwm6Regs.DBCTL.bit.OUTSWAP = 0; // ���|A�s����OutA �A���|B�s����OutB

    EPwm6Regs.DBCTL.bit.SHDWDBFEDMODE = 1; // �ϥ�Immediate mode���w����ӧ�s�W�t����ɶ�
    EPwm6Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm6Regs.DBCTL.bit.SHDWDBREDMODE = 1; // �ϥ�Immediate mode���w����ӧ�s�U�t����ɶ�
    EPwm6Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm6Regs.DBFED.bit.DBFED = 5; // �W�t����5*10ns = 50ns
    EPwm6Regs.DBRED.bit.DBRED = 5; // �U�t����5*10ns = 50ns

    EPwm6Regs.DBCTL.bit.HALFCYCLE = 0;

    //ET submodule---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //�]�wINTSEL�A��ܨƥ�Ĳ�o����CINTSEL = 1 => ��TBCTR�ƨ�0�ɡAInterrupt�ƥ�p�ƾ�CNT�N�|�[1�C => �C�g��(10us)�ACNT+1�C
    EPwm6Regs.ETSEL.bit.INTSEL = 1; //��p�ƾ�CTR�ƨ�ZERO�ɶǻ��ƥ�T��
    //�ҥ�EPWM6���_
    EPwm6Regs.ETSEL.bit.INTEN = 1;//�ҥ�
    //�M�����_�X��
    EPwm6Regs.ETCLR.bit.INT = 1;
    //�վ㤤�_�g���A�C�Өƥ�ɶ���5us�C�]�w���C1�Өƥ�Ĳ�o���_ => 5us���_�@�� => ���_�W�v = 200kHz
    EPwm6Regs.ETPS.bit.INTPSSEL = 0;
    EPwm6Regs.ETPS.bit.INTPRD = 1;

    //EPWM SOC
    //�z�LEPWM�T����Ĳ�oADC��SOC�ļ˻P���_
    EPwm6Regs.ETSEL.bit.SOCAEN = 1; //�ҥ�EPWM6Ĳ�oSOCA
    EPwm6Regs.ETSEL.bit.SOCASEL = 1; //��p�ƾ�CTR�ƨ�ZERO�ɶǻ��ƥ�T��
    EPwm6Regs.ETPS.bit.SOCPSSEL = 0; //�M�����_�X��
    EPwm6Regs.ETPS.bit.SOCAPRD = 3; //�CĲ�o�T�Өƥ�N�|Ĳ�oSOCA

    //TZ submodule-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //CBC-------------------------------------------------------------------------------
    //��ܬO�_�ϥ�TZ1��Ĳ�o�g���ʸ��h�ƥ�CTZSEL.OSHT1 : 1 => ��ܨϥ�TZ1��Ĳ�o�@���ʸ��h�ƥ�C
//    EPwm6Regs.TZSEL.bit.OSHT1 = 1;
//    //��l�ơA�M��OST�X�СC
//    EPwm6Regs.TZCLR.bit.OST = 1;
//    //�M�����_�X��
//    EPwm6Regs.ETCLR.bit.INT = 1;
//    //Trip Logic------------------------------------------------------------------------
//    //���EPWM Trip Logic Ĳ�o�᪺�ʧ@�CTZCTL2.ETZE : 0 => �ϥ�TBCTL�w�q���ʧ@�C
//    EPwm6Regs.TZCTL2.bit.ETZE = 0;
//    //����h�ƥ�o�ͮɡA�j�����EPWMxA��X�CTZCTL.TZA : 2 => ��EPWMxA���C�q���X�C
//    EPwm6Regs.TZCTL.bit.TZA = 2;
    EDIS;
}






//
// initADC - Function to configure and power up ADCA.
//
/*void Init_ADC(void) //��full module
{
    //
    // Setup VREF as internal
    //
    SetVREF(ADC_ADCA, ADC_EXTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCB, ADC_EXTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCC, ADC_EXTERNAL, ADC_VREF3P3);
    EALLOW;

    //
    // Set ADCCLK divider to /2
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 2;  //�]��ADC�Ҳկ౵���̰��W�v��50MHz�A(100MHz/2)

    // Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;  //ADC Interrupt Pulse Position.
    //1 : Interrupt pulse generation occurs at the end of the conversion, 1 cycle prior to the ADC result latching into its result register

    // Power up the ADC and then delay for 1 ms
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; //1 : All analog circuitry inside the core is powered up

    AdcbRegs.ADCCTL2.bit.PRESCALE = 2;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    AdccRegs.ADCCTL2.bit.PRESCALE = 2;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    EDIS;

    DELAY_US(1000);
}*/

void Init_ADC(void) //�ҥ�ADC
{
//    �]�wAdcA���ѦҷǦ�ӷ��C
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3); //�]�wADCA�������ѦҷǦ�Ҧ��C
    EALLOW;
    //�ҥ�CPU��ADCA��Clock(SYSCLK)�C
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    //�NInput Clock���W��ADCCLK��ADCA�C
    AdcaRegs.ADCCTL2.bit.PRESCALE = 2; //PRESCALE = 0�AADCCLK = Input Clock/1 = 100M/1 = 100M�C
    //�]�wINTPULSEPOS�վ�EOC pulse���ͪ��ɾ��CINTPULSEPOS : 1 => ��SOC�ഫ�����ç���ADCRESULT�ɡA�|����EOC pulse�A�i��Ĳ�oADCA���_�C
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //�ҥ�ADCA�Ҳդ�������q���C
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;


    /*
        !!!!!!!!!!!!�ҥ�ADC_C�Ҳիe�n���]�wADC_B�Ҳ�!!!!!!!!!!
     */
    SetVREF(ADC_ADCB, ADC_INTERNAL, ADC_VREF3P3); //�]�wADCB�������ѦҷǦ�Ҧ��C

    //�]�wAdcC���ѦҷǦ�ӷ��C
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3); //�]�wADCC�������ѦҷǦ�Ҧ��C
    EALLOW;
    //�ҥ�CPU��ADCC��Clock(SYSCLK)�C
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    //�NInput Clock���W��ADCCLK��ADCC�C
    AdccRegs.ADCCTL2.bit.PRESCALE = 2; //PRESCALE = 0�AADCCLK = Input Clock/1 = 100M/1 = 100M�C
    //�]�wINTPULSEPOS�վ�EOC pulse���ͪ��ɾ��CINTPULSEPOS : 1 => ��SOC�ഫ�����ç���ADCRESULT�ɡA�|����EOC pulse�A�i��Ĳ�oADCC���_�C
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //�ҥ�ADCC�Ҳդ�������q���C
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //ADC�Ҳձҥλݤ@�I�ɶ��A�i�ѦҸԲӪ�P.1462�C
    DELAY_US(1000);
    EDIS;
}


void Init_ADCSOC(void) //�]�wSOC
{
    EALLOW;
    //�]�wSOCPRIORITY��ܨ���SOC�OHigh Priority�CSOCPRIORITY : 10h => SOC0~SOC10���OHigh Priority�C
    AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;
    AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;

    //�ϥ�ADCA��SOC0�q�D(A3)-----------------------------------------------------------------------------------------------------------------------------------
    //�]�wADCSOC0CTL.TRIGSEL�վ�SOC0Ĳ�o���CADCSOC0CTL.TRIGSEL : 5 => �HEPWM6��SOCAĲ�oSOC0�C
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x0F;   //
    //�]�wADCSOC0CTL.CHSEL�վ�SOC0��ܭn�ļ˭��@��ADCIN���ഫ�CADCSOC0CTL.CHSEL : 3 => SOC0�ļ�ADCIN3(A3)(Vadc3)
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;
    //ACQPS�]�w�ļ˵���CAcquisition window = (ACQPS+1)*TSYSCLK�C
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 64;     // Acquisition window = (64+1)*10ns = 650ns

    //�ϥ�ADCC��SOC0�q�D(C5)-----------------------------------------------------------------------------------------------------------------------------------
    //�]�wADCSOC0CTL.TRIGSEL�վ�SOC0Ĳ�o���CADCSOC0CTL.TRIGSEL : 5 => �HEPWM6��SOCAĲ�oSOC1�C
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x0F;   //
    //�]�wADCSOC0CTL.CHSEL�վ�SOC12��ܭn�ļ˭��@��ADCIN���ഫ�CADCSOC0CTL.CHSEL : 3 => SOC0�ļ�ADCIN3(C5)(Iadc)
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 5;
    //ACQPS�]�w�ļ˵���CAcquisition window = (ACQPS+1)*TSYSCLK�C
    AdccRegs.ADCSOC0CTL.bit.ACQPS = 64;    // Acquisition window = (64+1)*10ns = 650ns

    //�ϥ�ADCA��SOC1�q�D(A9)-----------------------------------------------------------------------------------------------------------------------------------
    //�]�wADCSOC1CTL.TRIGSEL�վ�SOC1Ĳ�o���CADCSOC1CTL.TRIGSEL : 0 => �H�nĲ�oSOC1�C
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x0F;   //
    //�]�wADCSOC0CTL.CHSEL�վ�SOC1��ܭn�ļ˭��@��ADCIN���ഫ�CADCSOC0CTL.CHSEL : 9 => SOC0�ļ�ADCIN9(A9)(Vadc1)
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 9;
    //ACQPS�]�w�ļ˵���CAcquisition window = (ACQPS+1)*TSYSCLK�C
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 64;     // Acquisition window = (64+1)*10ns = 650ns

    //�ϥ�ADCC��SOC1�q�D(C3)-----------------------------------------------------------------------------------------------------------------------------------
    //�]�wADCSOC1CTL.TRIGSEL�վ�SOC1Ĳ�o���CADCSOC0CTL.TRIGSEL : 5 => �HEPWM6��SOCĲ�oSOC1�C
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0x0F;   //
    //�]�wADCSOC1CTL.CHSEL�վ�SOC1��ܭn�ļ˭��@��ADCIN���ഫ�CADCSOC1CTL.CHSEL : 5 => SOC1�ļ�ADCIN5(C3)(Vadc2)
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 3;
    //ACQPS�]�w�ļ˵���CAcquisition window = (ACQPS+1)*TSYSCLK�C
    AdccRegs.ADCSOC1CTL.bit.ACQPS = 64;    // Acquisition window = (64+1)*10ns = 650ns

    //ADCAINT===========================================================================================================================================
    //�ҥ�ADCAINT1���_
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //ADCAINT1���s���_�Ҧ��A����ADCAINT1�X�ЬO�_��1�AADCA���|����ADCAINT1�n�D��PIE
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    //���ADCAINT1Ĳ�o���CADCINTSEL1N2.INT1SEL : 0 => ��ܨϥ�EOC0Ĳ�oADCAINT1 => ��adcA3�T���i�椤�_
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    //��l�ơA�M��ADCAINT1�X��
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //�ҥ�ADCAINT2���_
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;
    //ADCAINT2���s���_�Ҧ��A����ADCAINT2�X�ЬO�_��1�AADCA���|����ADCAINT2�n�D��PIE
    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    //���ADCAINT2Ĳ�o���CADCINTSEL1N2.INT2SEL : 1 => ��ܨϥ�EOC1Ĳ�oADCAINT2 => ��adcA9�T���i�椤�_
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 1;
    //��l�ơA�M��ADCAINT2�X��
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //ADCCINT===========================================================================================================================================
    //�ҥ�ADCCINT1���_
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //ADCCINT1���s���_�Ҧ��A����ADCCINT1�X�ЬO�_��1�AADCC���|����ADCCINT1�n�D��PIE
    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    //���ADCCINT1Ĳ�o���CADCINTSEL1N2.INT1SEL : 0 => ��ܨϥ�EOC0Ĳ�oADCCINT1 => ��adcC5�T���i�椤�_
    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    //��l�ơA�M��ADCCINT1�X��
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //�ҥ�ADCCINT2���_
    AdccRegs.ADCINTSEL1N2.bit.INT2E = 1;
    //ADCCINT2���s���_�Ҧ��A����ADCAINT2�X�ЬO�_��1�AADCA���|����ADCAINT2�n�D��PIE
    AdccRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    //���ADCCINT2Ĳ�o���CADCINTSEL1N2.INT1SEL : 1 => ��ܨϥ�EOC1(SOC1)Ĳ�oADCCINT2 => ��adcC3�T���i�椤�_
    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = 1;
    //��l�ơA�M��ADCCINT2�X��
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 0 <- X,  1 <- INT1 flag cleared

    EDIS;
}

/*void Init_ADCSOC(void) //��full module
{

    //
    // Select the channels to convert and the end of conversion flag
    //
    EALLOW;

    AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;  // All SOCs are in high priority mode, arbitrated by SOC number.
    AdcbRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;  // All SOCs are in high priority mode, arbitrated by SOC number.
    AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;  // All SOCs are in high priority mode, arbitrated by SOC number.


       AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;     // SOC3 will convert pin A3            //IL      //ADCINA3--> pin69
       AdcaRegs.ADCSOC3CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;     // SOC4 will convert pin A4            //VR(�L��)  //ADCINA4--> pin64
       AdcaRegs.ADCSOC4CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;     // SOC0 will convert pin B2            //Vout    //ADCINB2--> pin27
       AdcbRegs.ADCSOC2CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcbRegs.ADCSOC4CTL.bit.CHSEL = 4;     // SOC4 will convert pin B4            //VR(�ʽ�)    //ADCINB4--> pin45
       AdcbRegs.ADCSOC4CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdccRegs.ADCSOC0CTL.bit.CHSEL = 0;     // SOC0 will convert pin C0            //Vin      //ADCINC0--> pin28
       AdccRegs.ADCSOC0CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdccRegs.ADCSOC5CTL.bit.CHSEL = 5;     // SOC0 will convert pin C5            //Temperature //ADCINC0--> pin68
       AdccRegs.ADCSOC5CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdccRegs.ADCSOC5CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcbRegs.ADCINTSEL1N2.bit.INT1CONT = 1; // 0 <- No further ADCINT1 generated until ADCINT1 flag cleared, 1 <- Continue to ADCINT1
       AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;    // 0 <- Disable INT1, 1 <- Enable INT1
       AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 4;  // ADCINT1 EOC Source Select, 0 <- EOC0, 2 <- EOC2

       AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared
       AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared
       AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared

       EDIS;
}*/





//void InitSCIB(void)
//{
//    //
//    // Note: Clocks were turned on to the SCIA peripheral
//    // in the InitSysCtrl() function
//    //
//    ScibRegs.SCICCR.all = 0x0007;           // 1 stop bit,  No loopback
//                                            // No parity, 8 char bits,
//                                            // async mode, idle-line protocol
//    ScibRegs.SCICTL1.all = 0x0003;          // enable TX, RX, internal SCICLK,
//                                            // Disable RX ERR, SLEEP, TXWAKE
//
//    ScibRegs.SCICTL2.bit.TXINTENA = 1;
//    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
//
//
//
//    ScibRegs.SCIHBAUD.all = 0x0005;
//    ScibRegs.SCILBAUD.all = 0x0015;
//
//    ScibRegs.SCICTL1.all = 0x0023;          // Relinquish SCI from Reset
//
//    ScibRegs.SCIFFTX.all = 0xE040;
//    ScibRegs.SCIFFRX.all = 0x2044;
//    ScibRegs.SCIFFCT.all = 0x0;
//}
//
//
//void InitSCIBFIFO(void)
//{
//    ScibRegs.SCIFFTX.all = 0xE040;
//    ScibRegs.SCIFFRX.all = 0x2044;
//    ScibRegs.SCIFFCT.all = 0x0;
//}


