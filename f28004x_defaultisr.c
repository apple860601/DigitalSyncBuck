
//
// Included Files
//
#include "f28004x_device.h"       // F28004x Header File Include File
#include "f28004x_examples.h"     // F28004x Examples Include File
#include "Init.h"

uint16_t counter_PWMINT=0;
float aa=0.0;
int c = 0;
int ADCRESULT0_max = 0;
int ADCRESULT0_max_new = 0;
int ADCRESULT0_min = 0;
int ADCRESULT0_min_new = 0;
int ADCRESULT3_max = 0;
int ADCRESULT3_max_new = 0;
int ADCRESULT3_min = 0;
int ADCRESULT3_min_new = 0;
int ADCRESULT12_max = 0;
int ADCRESULT12_max_new = 0;
int ADCRESULT12_min = 0;
int ADCRESULT12_min_new = 0;
//
// EPWM1_ISR - ePWM1 Interrupt
//
//interrupt void
/*EPWM1_ISR(void) 原版
{
	GpioDataRegs.GPBSET.bit.GPIO35=1;

//測試PWM設定
    aa = (float)(AdcbResultRegs.ADCRESULT4)*0.0002442;
	EPwm1Regs.CMPB.bit.CMPB = (uint16_t)(aa*EPwm1Regs.TBPRD);
	EPwm1Regs.CMPA.bit.CMPA = (uint16_t)(aa*EPwm1Regs.TBPRD);



    ILoop();



    counter_PWMINT++;
    if(counter_PWMINT> 27000)
    {
        counter_PWMINT = 0;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34=1;    //LED5(INT)
    }


    if(DI_Fault_Reset.out == 1)//當reset搖頭開關turn on 清除保護旗標
    	{
    	EALLOW;
    	//EPwm1Regs.TZOSTCLR.bit.OST1 =1;
    	EPwm1Regs.TZCLR.bit.OST = 1;
    	EDIS;
    	Protection_status.bits.OUTOV = CLEAR;

    	}




    EPwm1Regs.ETCLR.bit.INT = 1; //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
//    DELAY_US(0.1);

    GpioDataRegs.GPBCLEAR.bit.GPIO35=1;

//    GpioDataRegs.GPBCLEAR.bit.GPIO35=1;
}*/
interrupt void
EPWM1_ISR(void)
{
    EALLOW;
    // 週期性清除OST旗標
    EPwm1Regs.TZCLR.bit.OST = 1;
    // 清除EPWM1中斷旗標
    EPwm1Regs.ETCLR.bit.INT = 1;
    // 清掉INT3中斷旗標，使CPU能接收下一次中斷要求
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3|PIEACK_GROUP1|PIEACK_GROUP10;
    EDIS;
}
//
// ECAP1_ISR - eCAP1 Interrupt
//

interrupt void
ECAP1_ISR(void)
{

//  GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1; //可以看ECAP中斷觸發訊號

    EALLOW;
    ECap1Regs.ECCLR.bit.CEVT1 = 1; //1 = Writing a 1 clears the CEVT1 flag condition.
  // ECap1Regs.ECCLR.bit.CEVT2 = 1;
    ECap1Regs.ECCLR.bit.INT = 1;   //1 = Writing a 1 clears the INT flag and enable further interrupts to be generated if any of the event flags are set to 1
    ECap1Regs.ECCTL2.bit.REARM = 1;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
    EDIS;
}


//
// TIMER0_ISR - Timer 0 Interrupt
//
interrupt void
TIMER0_ISR(void)
{
    // 中斷計數器，每進入中斷一次就加1
    CpuTimer0.InterruptCount++;
    EALLOW;
    // 每進入中斷就切換GPIO0輸出狀態
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;
    // 清掉INT1中斷旗標，使CPU能接收下一次中斷要求
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    EDIS;
}

//
// TIMER1_ISR - CPU Timer 1 Interrupt
//
interrupt void
TIMER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// TIMER2_ISR - CPU Timer 2 Interrupt
//
interrupt void
TIMER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DATALOG_ISR - Datalogging Interrupt
//
interrupt void
DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RTOS_ISR - RTOS Interrupt
//
interrupt void
RTOS_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EMU_ISR - Emulation Interrupt
//
interrupt void
EMU_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-Maskable Interrupt
//
interrupt void
NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ILLEGAL_ISR - Illegal Operation Trap
//
interrupt void
ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined Trap 1
//
interrupt void
USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined Trap 2
//
interrupt void
USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined Trap 3
//
interrupt void
USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined Trap 4
//
interrupt void
USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined Trap 5
//
interrupt void
USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined Trap 6
//
interrupt void
USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined Trap 7
//
interrupt void
USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined Trap 8
//
interrupt void
USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined Trap 9
//
interrupt void
USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined Trap 10
//
interrupt void
USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined Trap 11
//
interrupt void
USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined Trap 12
//
interrupt void
USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCA1_ISR - ADCA Interrupt 1
//
interrupt void
ADCA1_ISR(void)
{
    //切換GPIO6輸出狀態。
    GpioDataRegs.GPATOGGLE.bit.GPIO6 = 1;
    //利用手撥開關控制GPIO7輸入，若GPIO7輸入為高態，執行ADCRESULT最大與最小值追蹤。
    if (GpioDataRegs.GPADAT.bit.GPIO7 == 1)
    {
        c++;
        if (c == 1)
        {
            //ADCRESULT0----------------------------------------------
            ADCRESULT0_max_new = AdcaResultRegs.ADCRESULT0;
            ADCRESULT0_max = ADCRESULT0_max_new;
            ADCRESULT0_min_new = AdcaResultRegs.ADCRESULT0;
            ADCRESULT0_min = ADCRESULT0_min_new;
            //ADCRESULT3----------------------------------------------
            ADCRESULT3_max_new = AdcaResultRegs.ADCRESULT3;
            ADCRESULT3_max = ADCRESULT3_max_new;
            ADCRESULT3_min_new = AdcaResultRegs.ADCRESULT3;
            ADCRESULT3_min = ADCRESULT3_min_new;
            //ADCRESULT12----------------------------------------------
            ADCRESULT12_max_new = AdcaResultRegs.ADCRESULT12;
            ADCRESULT12_max = ADCRESULT12_max_new;
            ADCRESULT12_min_new = AdcaResultRegs.ADCRESULT12;
            ADCRESULT12_min = ADCRESULT12_min_new;
        }
        else
        {
            c--;
            //ADCRESULT0----------------------------------------------
            ADCRESULT0_max_new = AdcaResultRegs.ADCRESULT0;
            ADCRESULT0_min_new = AdcaResultRegs.ADCRESULT0;
            if (ADCRESULT0_max_new > ADCRESULT0_max)
            {
                ADCRESULT0_max = ADCRESULT0_max_new;
            }
            if (ADCRESULT0_min_new < ADCRESULT0_min)
            {
                ADCRESULT0_min = ADCRESULT0_min_new;
            }
            //ADCRESULT3----------------------------------------------
            ADCRESULT3_max_new = AdcaResultRegs.ADCRESULT3;
            ADCRESULT3_min_new = AdcaResultRegs.ADCRESULT3;
            if (ADCRESULT3_max_new > ADCRESULT3_max)
            {
                ADCRESULT3_max = ADCRESULT3_max_new;
            }
            if (ADCRESULT3_min_new < ADCRESULT3_min)
            {
                ADCRESULT3_min = ADCRESULT3_min_new;
            }
            //ADCRESULT12----------------------------------------------
            ADCRESULT12_max_new = AdcaResultRegs.ADCRESULT12;
            ADCRESULT12_min_new = AdcaResultRegs.ADCRESULT12;
            if (ADCRESULT12_max_new > ADCRESULT12_max)
            {
                ADCRESULT12_max = ADCRESULT12_max_new;
            }
            if (ADCRESULT12_min_new < ADCRESULT12_min)
            {
                ADCRESULT12_min = ADCRESULT12_min_new;
            }
        }
    }
    else
    {
        c = 0;
    }
    //清除ADCAINT1旗標
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //清除ADCAINT1溢位旗標。(當ADC中斷溢位時需清除ADCINT溢位旗標，否則在非連續中斷模式時會無法提出ADCINT要求)
    AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
    //清除PIEACK
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// ADCB1_ISR - ADCB Interrupt 1
//
interrupt void
ADCB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCC1_ISR - ADCC Interrupt 1
//
interrupt void
ADCC1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT1_ISR - XINT1 Interrupt
//
interrupt void
XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT2_ISR - XINT2 Interrupt
//
interrupt void
XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}


//
// WAKE_ISR - Halt Wakeup Interrupt
//
interrupt void
WAKE_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM1_TZ_ISR - ePWM1 Trip Zone Interrupt
//
interrupt void
EPWM1_TZ_ISR(void)
{
    c++;
    EALLOW;
    // 每進入中斷就切換GPIO3輸出狀態
    GpioDataRegs.GPATOGGLE.bit.GPIO3 = 1;
    // 清除CBC旗標。註:會被週期性自動清除的是CBC latch的輸出值，CBC旗標仍要自己清理，兩者都清除後才能重啟EPWM
//    EPwm1Regs.TZCLR.bit.CBC = 1;
    // 清除EPWM1_TZ中斷旗標
    EPwm1Regs.TZCLR.bit.INT = 1;
    // 清掉INT2中斷旗標，使CPU能接收下一次中斷要求
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    EDIS;
}

//
// EPWM2_TZ_ISR - ePWM2 Trip Zone Interrupt
//
interrupt void
EPWM2_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_TZ_ISR - ePWM3 Trip Zone Interrupt
//
interrupt void
EPWM3_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_TZ_ISR - ePWM4 Trip Zone Interrupt
//
interrupt void
EPWM4_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_TZ_ISR - ePWM5 Trip Zone Interrupt
//
interrupt void
EPWM5_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_TZ_ISR - ePWM6 Trip Zone Interrupt
//
interrupt void
EPWM6_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM7_TZ_ISR - ePWM7 Trip Zone Interrupt
//
interrupt void
EPWM7_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM8_TZ_ISR - ePWM8 Trip Zone Interrupt
//
interrupt void
EPWM8_TZ_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}


//
// EPWM2_ISR - ePWM2 Interrupt
//
interrupt void
EPWM2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_ISR - ePWM3 Interrupt
//
interrupt void
EPWM3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_ISR - ePWM4 Interrupt
//
interrupt void
EPWM4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_ISR - ePWM5 Interrupt
//
interrupt void
EPWM5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_ISR - ePWM6 Interrupt
//
interrupt void
EPWM6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
//    asm ("      ESTOP0");
//    for(;;);
}

//
// EPWM7_ISR - ePWM7 Interrupt
//
interrupt void
EPWM7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM8_ISR - ePWM8 Interrupt
//
interrupt void
EPWM8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}



//
// ECAP2_ISR - eCAP2 Interrupt
//
interrupt void
ECAP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP3_ISR - eCAP3 Interrupt
//
interrupt void
ECAP3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP4_ISR - eCAP4 Interrupt
//
interrupt void
ECAP4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP5_ISR - eCAP5 Interrupt
//
interrupt void
ECAP5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP6_ISR - eCAP6 Interrupt
//
interrupt void
ECAP6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP7_ISR - eCAP7 Interrupt
//
interrupt void
ECAP7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP6_2_ISR - eCAP6_2 Interrupt
//
interrupt void
ECAP6_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP7_2_ISR - eCAP7_2 Interrupt
//
interrupt void
ECAP7_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EQEP1_ISR - eQEP1 Interrupt
//
interrupt void
EQEP1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EQEP2_ISR - eQEP2 Interrupt
//
interrupt void
EQEP2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPIA_RX_ISR - SPIA Receive Interrupt
//
interrupt void
SPIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPIA_TX_ISR - SPIA Transmit Interrupt
//
interrupt void
SPIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPIB_RX_ISR - SPIB Receive Interrupt
//
interrupt void
SPIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPIB_TX_ISR - SPIB Transmit Interrupt
//
interrupt void
SPIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH1_ISR - DMA Channel 1 Interrupt
//
interrupt void
DMA_CH1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH2_ISR - DMA Channel 2 Interrupt
//
interrupt void
DMA_CH2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH3_ISR - DMA Channel 3 Interrupt
//
interrupt void
DMA_CH3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH4_ISR - DMA Channel 4 Interrupt
//
interrupt void
DMA_CH4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH5_ISR - DMA Channel 5 Interrupt
//
interrupt void
DMA_CH5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DMA_CH6_ISR - DMA Channel 6 Interrupt
//
interrupt void
DMA_CH6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// I2CA_ISR - I2CA Interrupt 1
//
interrupt void
I2CA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// I2CA_FIFO_ISR - I2CA Interrupt 2
//
interrupt void
I2CA_FIFO_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCIA_RX_ISR - SCIA Receive Interrupt
//
interrupt void
SCIA_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCIA_TX_ISR - SCIA Transmit Interrupt
//
interrupt void
SCIA_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCIB_RX_ISR - SCIB Receive Interrupt
//
interrupt void
SCIB_RX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCIB_TX_ISR - SCIB Transmit Interrupt
//
interrupt void
SCIB_TX_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CANA0_ISR - CANA Interrupt 0
//
interrupt void
CANA0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CANA1_ISR - CANA Interrupt 1
//
interrupt void
CANA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CANB0_ISR - CANB Interrupt 0
//
interrupt void
CANB0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CANB1_ISR - CANB Interrupt 1
//
interrupt void
CANB1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCA_EVT_ISR - ADCA Event Interrupt
//
interrupt void
ADCA_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCA2_ISR - ADCA Interrupt 2
//
interrupt void
ADCA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCA3_ISR - ADCA Interrupt 3
//
interrupt void
ADCA3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCA4_ISR - ADCA Interrupt 4
//
interrupt void
ADCA4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCB_EVT_ISR - ADCB Event Interrupt
//
interrupt void
ADCB_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCB2_ISR - ADCB Interrupt 2
//
interrupt void
ADCB2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCB3_ISR - ADCB Interrupt 3
//
interrupt void
ADCB3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCB4_ISR - ADCB Interrupt 4
//
interrupt void
ADCB4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_1_ISR - CLA1 Interrupt 1
//
interrupt void
CLA1_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_2_ISR - CLA1 Interrupt 2
//
interrupt void
CLA1_2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_3_ISR - CLA1 Interrupt 3
//
interrupt void
CLA1_3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_4_ISR - CLA1 Interrupt 4
//
interrupt void
CLA1_4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_5_ISR - CLA1 Interrupt 5
//
interrupt void
CLA1_5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_6_ISR - CLA1 Interrupt 6
//
interrupt void
CLA1_6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_7_ISR - CLA1 Interrupt 7
//
interrupt void
CLA1_7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1_8_ISR - CLA1 Interrupt 8
//
interrupt void
CLA1_8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP11;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT3_ISR - XINT3 Interrupt
//
interrupt void
XINT3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT4_ISR - XINT4 Interrupt
//
interrupt void
XINT4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT5_ISR - XINT5 Interrupt
//
interrupt void
XINT5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FPU_OVERFLOW_ISR - FPU Overflow Interrupt
//
interrupt void
FPU_OVERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FPU_UNDERFLOW_ISR - FPU Underflow Interrupt
//
interrupt void
FPU_UNDERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SD1_ISR - SDFM1 Interrupt
//
interrupt void
SD1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SD1DR1_ISR - SDFM1 DR Interrupt 1
//
interrupt void
SD1DR1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SD1DR2_ISR - SDFM1 DR Interrupt 2
//
interrupt void
SD1DR2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SD1DR3_ISR - SDFM1 DR Interrupt 3
//
interrupt void
SD1DR3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SD1DR4_ISR - SDFM1 DR Interrupt 4
//
interrupt void
SD1DR4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}


//
// FSITXA1_ISR - FSITXA1_ISR Interrupt
//
interrupt void
FSITXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FSITXA2_ISR - FSITXA2_ISR Interrupt
//
interrupt void
FSITXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FSIRXA1_ISR - FSIRXA1_ISR Interrupt
//
interrupt void
FSIRXA1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FSIRXA2_ISR - FSIRXA2_ISR Interrupt
//
interrupt void
FSIRXA2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA1PROMCRC - CLA1PROMCRC Interrupt
//
interrupt void
CLA1PROMCRC_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// LINA_0 - LINA Interrupt 0
//
interrupt void
LINA_0_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// LINA_1 - LINA Interrupt 1
//
interrupt void
LINA_1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PMBUSA - PMBUSA Interrupt
//
interrupt void
PMBUSA_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCC_EVT_ISR - ADCC Event Interrupt
//
interrupt void
ADCC_EVT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCC2_ISR - ADCC Interrupt 2
//
interrupt void
ADCC2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCC3_ISR - ADCC Interrupt 3
//
interrupt void
ADCC3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCC4_ISR - ADCC Interrupt 4
//
interrupt void
ADCC4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RAM_CORRECTABLE_ERROR_ISR - RAM Correctable Error Interrupt
//
interrupt void
RAM_CORRECTABLE_ERROR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// FLASH_CORRECTABLE_ERROR_ISR - Flash Correctable Error Interrupt
//
interrupt void
FLASH_CORRECTABLE_ERROR_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RAM_ACCESS_VIOLATION_ISR - RAM Access Violation Interrupt
//
interrupt void
RAM_ACCESS_VIOLATION_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SYS_PLL_SLIP_ISR - System PLL Slip Interrupt
//
interrupt void
SYS_PLL_SLIP_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA_OVERFLOW_ISR - CLA Overflow Interrupt
//
interrupt void
CLA_OVERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// CLA_UNDERFLOW_ISR - CLA Underflow Interrupt
//
interrupt void
CLA_UNDERFLOW_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group,
    // acknowledge this interrupt.
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Catch-all Default ISRs
//

//
// PIE_RESERVED_ISR - Reserved ISR
//
interrupt void
PIE_RESERVED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// EMPTY_ISR - Only does a return
//
interrupt void
EMPTY_ISR(void)
{

}

//
// NOTUSED_ISR - Unused ISR
//
interrupt void
NOTUSED_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

