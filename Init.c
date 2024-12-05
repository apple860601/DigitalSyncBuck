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
//    // 關閉所有GPIO內部上拉，減少功率損耗
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

    PieCtrlRegs.PIEIER3.bit.INTx6= 1;  // INT3.6 => EPWM6中斷
//    PieCtrlRegs.PIEIER1.bit.INTx7= 1;  // INT1.7 => TIMER0中斷
    PieCtrlRegs.PIEIER1.bit.INTx1= 1;  // INT1.1 => ADCA1中斷
    PieCtrlRegs.PIEIER1.bit.INTx3= 1;  // INT1.3 => ADCC1中斷
    PieCtrlRegs.PIEIER10.bit.INTx2= 1;  // INT10.2 => ADCA2中斷
    PieCtrlRegs.PIEIER10.bit.INTx10= 1;  // INT10.10 => ADCC2中斷
    IER |= M_INT3;
    IER |= M_INT1;
    IER |= M_INT10;

    EINT;
    ERTM;

}


void Init_CpuTimer(void)
{

    EALLOW;

//    //設定Timer0
//    //  初始化位址 CPU Timer0 位址
//    CpuTimer0.RegsAddr = &CpuTimer0Regs;
//    //  設定週期暫存器，TSYSCLK = 10ns，每經過一個TSYSCLK，Timer就減1，減到0後傳遞中斷要求並將Timer重制回PRD
//    CpuTimer0Regs.PRD.all  = 500; //TSYSCLK*PRD = Period = 10n*500 = 5us
//    //  設定分頻器，本例題週期0.2s不需用到分頻器，均設為0即可
//    CpuTimer0Regs.TPR.all  = 0;
//    CpuTimer0Regs.TPRH.all = 0;
//    //  TSS : 暫停Timer計數。TSS = 1 => 暫停Timer計數；TSS = 0 => 開啟Timer計數。
//    CpuTimer0Regs.TCR.bit.TSS = 0;
//    //  TIE : 啟用Timer0中斷。TIE = 1 => 啟用Timer中斷；TIE = 0 => 關閉Timer中斷。
//    CpuTimer0Regs.TCR.bit.TIE = 1;
//    //  初始化TIF。當Timer數到0時，TIF = 1，並清除該旗標使TIF = 0，開始下一輪計數。
//    CpuTimer0Regs.TCR.bit.TIF = 1;
//    //  初始化中斷計數器。中斷計數器 : 紀錄Timer0中斷執行了幾次。
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
    //計數器TBCTR與週期PRD設定
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //啟用CPU給EPWM的Clock(SYSCLK)
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
    //設定分頻器。均設為0，使TBCLK = SYSCLK = 100MHz，T_TBCLK = 1/100M = 10ns。
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = 0;
    EPwm6Regs.TBCTL.bit.CLKDIV = 0;
    //設定FREE_SOFT。設定FREE_SOFT = 2 => TBCTR自由運行(正常計數)，若FREE_SOFT為0或1將停止TBCTR計數狀態。
    EPwm6Regs.TBCTL.bit.FREE_SOFT = 2;
    //設定計數器計數模式，CTRMOD = 0 => 上數模式。
    EPwm6Regs.TBCTL.bit.CTRMODE = 0;
    //初始化計數器TBCTR。
    EPwm6Regs.TBCTR = 0;
    //設定PRD調整EPWM週期，下數狀態。
    EPwm6Regs.TBPRD = 999; //(1+PRD)*T_TBCLK = 1000*10n = 10us = T_PWM => F_PWM = 1/T_PWM = 100kHz。
    //設定PRDLD，更動TBPRD值時，調整讀取新TBPRD值的時機，建議使用Shadow Mode。
    EPwm6Regs.TBCTL.bit.PRDLD = 0;
    //設定PRDLDSYNC，Shadow Mode的指定條件。
    EPwm6Regs.TBCTL2.bit.PRDLDSYNC = 0; //更動TBPRD時，當TBCTR數到0，才會Load新的TBCTR。

    //CC submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //設定比較器CMPA
    EPwm6Regs.CMPA.bit.CMPA = 0.5*(EPwm6Regs.TBPRD);
    //設定比較器CMPB
    EPwm6Regs.CMPB.bit.CMPB = EPwm6Regs.CMPA.bit.CMPA;
    //設定SHDWxMODE，更動CMPx值時，調整讀取新CMPx值的時機，建議使用Shadow Mode。
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    //設定LOADxSYNC，Shadow Mode的指定條件。LOADxMODE = 0 => 根據LOADxMODE來Load新的CMPx
    EPwm6Regs.CMPCTL.bit.LOADASYNC = 0;
    EPwm6Regs.CMPCTL.bit.LOADBSYNC = 0;
    //設定LOADxMODE。LOADxMODE = 0 => 更動CMPx時，當計數器TBCTR數到0才會Load新的CMPx
    EPwm6Regs.CMPCTL.bit.LOADAMODE = 0;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = 0;

    //AQ submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //上數模式，TBCTR數到ZRO時SET(EPWM6A輸出High)，數到CMPA時CLEAR(EPWM6A輸出Low)。
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm6Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;
    EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    //設定RLDCSF調整讀取軟體控制訊號的時機。
    EPwm6Regs.AQSFRC.bit.RLDCSF = 0;
    //本例題不會使用到軟體強控EPWM輸出 => CSFA/CSFB = 0 => 關閉軟體強控EPWM6A/EPWM6B。
    EPwm6Regs.AQCSFRC.bit.CSFA = 0;
    EPwm6Regs.AQCSFRC.bit.CSFB = 0;

    //DB submodule--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    EPwm6Regs.DBCTL.bit.IN_MODE = 0; // 路徑A&B皆採用EPWMxA訊號源
    EPwm6Regs.DBCTL.bit.DEDB_MODE = 0; // 分別生成上升緣延遲以及下降緣延遲訊號
    EPwm6Regs.DBCTL.bit.POLSEL = 2; // 上升緣延遲訊號不反向，下降緣延遲訊號反向
    EPwm6Regs.DBCTL.bit.OUT_MODE = 3; // 路徑A接上上升緣延遲訊號，路徑B接上下降緣延遲訊號
    EPwm6Regs.DBCTL.bit.OUTSWAP = 0; // 路徑A連接到OutA ，路徑B連接到OutB

    EPwm6Regs.DBCTL.bit.SHDWDBFEDMODE = 1; // 使用Immediate mode指定條件來更新上緣延遲時間
    EPwm6Regs.DBCTL.bit.LOADFEDMODE = 0;
    EPwm6Regs.DBCTL.bit.SHDWDBREDMODE = 1; // 使用Immediate mode指定條件來更新下緣延遲時間
    EPwm6Regs.DBCTL.bit.LOADREDMODE = 0;
    EPwm6Regs.DBFED.bit.DBFED = 5; // 上緣延遲5*10ns = 50ns
    EPwm6Regs.DBRED.bit.DBRED = 5; // 下緣延遲5*10ns = 50ns

    EPwm6Regs.DBCTL.bit.HALFCYCLE = 0;

    //ET submodule---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //設定INTSEL，選擇事件觸發條件。INTSEL = 1 => 當TBCTR數到0時，Interrupt事件計數器CNT就會加1。 => 每週期(10us)，CNT+1。
    EPwm6Regs.ETSEL.bit.INTSEL = 1; //當計數器CTR數到ZERO時傳遞事件訊號
    //啟用EPWM6中斷
    EPwm6Regs.ETSEL.bit.INTEN = 1;//啟用
    //清除中斷旗標
    EPwm6Regs.ETCLR.bit.INT = 1;
    //調整中斷週期，每個事件時間為5us。設定為每1個事件觸發中斷 => 5us中斷一次 => 中斷頻率 = 200kHz
    EPwm6Regs.ETPS.bit.INTPSSEL = 0;
    EPwm6Regs.ETPS.bit.INTPRD = 1;

    //EPWM SOC
    //透過EPWM訊號來觸發ADC的SOC採樣與中斷
    EPwm6Regs.ETSEL.bit.SOCAEN = 1; //啟用EPWM6觸發SOCA
    EPwm6Regs.ETSEL.bit.SOCASEL = 1; //當計數器CTR數到ZERO時傳遞事件訊號
    EPwm6Regs.ETPS.bit.SOCPSSEL = 0; //清除中斷旗標
    EPwm6Regs.ETPS.bit.SOCAPRD = 3; //每觸發三個事件就會觸發SOCA

    //TZ submodule-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //EPwm6---------------------------------------------------------------------------------------------------------------
    //CBC-------------------------------------------------------------------------------
    //選擇是否使用TZ1來觸發週期性跳閘事件。TZSEL.OSHT1 : 1 => 選擇使用TZ1來觸發一次性跳閘事件。
//    EPwm6Regs.TZSEL.bit.OSHT1 = 1;
//    //初始化，清除OST旗標。
//    EPwm6Regs.TZCLR.bit.OST = 1;
//    //清除中斷旗標
//    EPwm6Regs.ETCLR.bit.INT = 1;
//    //Trip Logic------------------------------------------------------------------------
//    //選擇EPWM Trip Logic 觸發後的動作。TZCTL2.ETZE : 0 => 使用TBCTL定義的動作。
//    EPwm6Regs.TZCTL2.bit.ETZE = 0;
//    //當跳閘事件發生時，強制改變EPWMxA輸出。TZCTL.TZA : 2 => 使EPWMxA為低電位輸出。
//    EPwm6Regs.TZCTL.bit.TZA = 2;
    EDIS;
}






//
// initADC - Function to configure and power up ADCA.
//
/*void Init_ADC(void) //原full module
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
    AdcaRegs.ADCCTL2.bit.PRESCALE = 2;  //因為ADC模組能接受最高頻率為50MHz，(100MHz/2)

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

void Init_ADC(void) //啟用ADC
{
//    設定AdcA的參考準位來源。
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3); //設定ADCA為內部參考準位模式。
    EALLOW;
    //啟用CPU給ADCA的Clock(SYSCLK)。
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    //將Input Clock分頻成ADCCLK給ADCA。
    AdcaRegs.ADCCTL2.bit.PRESCALE = 2; //PRESCALE = 0，ADCCLK = Input Clock/1 = 100M/1 = 100M。
    //設定INTPULSEPOS調整EOC pulse產生的時機。INTPULSEPOS : 1 => 當SOC轉換結束並改變ADCRESULT時，會產生EOC pulse，進而觸發ADCA中斷。
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //啟用ADCA模組中的類比電路。
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;


    /*
        !!!!!!!!!!!!啟用ADC_C模組前要先設定ADC_B模組!!!!!!!!!!
     */
    SetVREF(ADC_ADCB, ADC_INTERNAL, ADC_VREF3P3); //設定ADCB為內部參考準位模式。

    //設定AdcC的參考準位來源。
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3); //設定ADCC為內部參考準位模式。
    EALLOW;
    //啟用CPU給ADCC的Clock(SYSCLK)。
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    //將Input Clock分頻成ADCCLK給ADCC。
    AdccRegs.ADCCTL2.bit.PRESCALE = 2; //PRESCALE = 0，ADCCLK = Input Clock/1 = 100M/1 = 100M。
    //設定INTPULSEPOS調整EOC pulse產生的時機。INTPULSEPOS : 1 => 當SOC轉換結束並改變ADCRESULT時，會產生EOC pulse，進而觸發ADCC中斷。
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //啟用ADCC模組中的類比電路。
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //ADC模組啟用需一點時間，可參考詳細版P.1462。
    DELAY_US(1000);
    EDIS;
}


void Init_ADCSOC(void) //設定SOC
{
    EALLOW;
    //設定SOCPRIORITY選擇那些SOC是High Priority。SOCPRIORITY : 10h => SOC0~SOC10都是High Priority。
    AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;
    AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0x10;

    //使用ADCA的SOC0通道(A3)-----------------------------------------------------------------------------------------------------------------------------------
    //設定ADCSOC0CTL.TRIGSEL調整SOC0觸發源。ADCSOC0CTL.TRIGSEL : 5 => 以EPWM6的SOCA觸發SOC0。
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x0F;   //
    //設定ADCSOC0CTL.CHSEL調整SOC0選擇要採樣哪一個ADCIN並轉換。ADCSOC0CTL.CHSEL : 3 => SOC0採樣ADCIN3(A3)(Vadc3)
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;
    //ACQPS設定採樣窗格。Acquisition window = (ACQPS+1)*TSYSCLK。
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 64;     // Acquisition window = (64+1)*10ns = 650ns

    //使用ADCC的SOC0通道(C5)-----------------------------------------------------------------------------------------------------------------------------------
    //設定ADCSOC0CTL.TRIGSEL調整SOC0觸發源。ADCSOC0CTL.TRIGSEL : 5 => 以EPWM6的SOCA觸發SOC1。
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x0F;   //
    //設定ADCSOC0CTL.CHSEL調整SOC12選擇要採樣哪一個ADCIN並轉換。ADCSOC0CTL.CHSEL : 3 => SOC0採樣ADCIN3(C5)(Iadc)
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 5;
    //ACQPS設定採樣窗格。Acquisition window = (ACQPS+1)*TSYSCLK。
    AdccRegs.ADCSOC0CTL.bit.ACQPS = 64;    // Acquisition window = (64+1)*10ns = 650ns

    //使用ADCA的SOC1通道(A9)-----------------------------------------------------------------------------------------------------------------------------------
    //設定ADCSOC1CTL.TRIGSEL調整SOC1觸發源。ADCSOC1CTL.TRIGSEL : 0 => 以軟觸發SOC1。
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x0F;   //
    //設定ADCSOC0CTL.CHSEL調整SOC1選擇要採樣哪一個ADCIN並轉換。ADCSOC0CTL.CHSEL : 9 => SOC0採樣ADCIN9(A9)(Vadc1)
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 9;
    //ACQPS設定採樣窗格。Acquisition window = (ACQPS+1)*TSYSCLK。
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 64;     // Acquisition window = (64+1)*10ns = 650ns

    //使用ADCC的SOC1通道(C3)-----------------------------------------------------------------------------------------------------------------------------------
    //設定ADCSOC1CTL.TRIGSEL調整SOC1觸發源。ADCSOC0CTL.TRIGSEL : 5 => 以EPWM6的SOC觸發SOC1。
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0x0F;   //
    //設定ADCSOC1CTL.CHSEL調整SOC1選擇要採樣哪一個ADCIN並轉換。ADCSOC1CTL.CHSEL : 5 => SOC1採樣ADCIN5(C3)(Vadc2)
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 3;
    //ACQPS設定採樣窗格。Acquisition window = (ACQPS+1)*TSYSCLK。
    AdccRegs.ADCSOC1CTL.bit.ACQPS = 64;    // Acquisition window = (64+1)*10ns = 650ns

    //ADCAINT===========================================================================================================================================
    //啟用ADCAINT1中斷
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //ADCAINT1為連續中斷模式，不論ADCAINT1旗標是否為1，ADCA都會產生ADCAINT1要求給PIE
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    //選擇ADCAINT1觸發源。ADCINTSEL1N2.INT1SEL : 0 => 選擇使用EOC0觸發ADCAINT1 => 由adcA3訊號進行中斷
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    //初始化，清除ADCAINT1旗標
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //啟用ADCAINT2中斷
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;
    //ADCAINT2為連續中斷模式，不論ADCAINT2旗標是否為1，ADCA都會產生ADCAINT2要求給PIE
    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    //選擇ADCAINT2觸發源。ADCINTSEL1N2.INT2SEL : 1 => 選擇使用EOC1觸發ADCAINT2 => 由adcA9訊號進行中斷
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 1;
    //初始化，清除ADCAINT2旗標
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //ADCCINT===========================================================================================================================================
    //啟用ADCCINT1中斷
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //ADCCINT1為連續中斷模式，不論ADCCINT1旗標是否為1，ADCC都會產生ADCCINT1要求給PIE
    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    //選擇ADCCINT1觸發源。ADCINTSEL1N2.INT1SEL : 0 => 選擇使用EOC0觸發ADCCINT1 => 由adcC5訊號進行中斷
    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    //初始化，清除ADCCINT1旗標
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // 0 <- X,  1 <- INT1 flag cleared

    //啟用ADCCINT2中斷
    AdccRegs.ADCINTSEL1N2.bit.INT2E = 1;
    //ADCCINT2為連續中斷模式，不論ADCAINT2旗標是否為1，ADCA都會產生ADCAINT2要求給PIE
    AdccRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    //選擇ADCCINT2觸發源。ADCINTSEL1N2.INT1SEL : 1 => 選擇使用EOC1(SOC1)觸發ADCCINT2 => 由adcC3訊號進行中斷
    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = 1;
    //初始化，清除ADCCINT2旗標
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; // 0 <- X,  1 <- INT1 flag cleared

    EDIS;
}

/*void Init_ADCSOC(void) //原full module
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

       AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;     // SOC4 will convert pin A4            //VR(微調)  //ADCINA4--> pin64
       AdcaRegs.ADCSOC4CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;     // SOC0 will convert pin B2            //Vout    //ADCINB2--> pin27
       AdcbRegs.ADCSOC2CTL.bit.ACQPS = 35;     // Sample window is 10 SYSCLK cycles
       AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 5;   // 5 <- Trigger on ePWM1 SOCA

       AdcbRegs.ADCSOC4CTL.bit.CHSEL = 4;     // SOC4 will convert pin B4            //VR(粗調)    //ADCINB4--> pin45
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


