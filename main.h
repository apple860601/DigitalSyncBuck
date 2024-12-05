/*
 * main.h
 *
 */
#ifndef MAIN_H_
#define MAIN_H_

void SetupGpio(void);

__interrupt void ePWM6ISR(void);
__interrupt void adcA3ISR(void);
__interrupt void adcA9ISR(void);
__interrupt void adcC3ISR(void);
__interrupt void adcC5ISR(void);

int voltage1_d = 0;
float voltage1_a = 0;
float voltage1_f = 0;
float voltage1_avg = 0;
float voltage1[10] = {0,0,0,0,0,0,0,0,0,0};

int voltage2_d = 0;
float voltage2_a = 0;
float voltage2_f = 0;
float voltage2_avg = 0;
float voltage2[10] = {0,0,0,0,0,0,0,0,0,0};

int voltage3_d = 0;
float voltage3_a = 0;
float voltage3_f = 0;
float voltage3_avg = 0;
float voltage3[10] = {0,0,0,0,0,0,0,0,0,0};

int current_d = 0;
float current_a = 0;
float current_f = 0;
float current_v = 0;
float current_avg = 0;
float current[10] = {0,0,0,0,0,0,0,0,0,0};

//float ind = 0;
float iL_refm1 = 0;
float iL_ref = 0;
float V_refm1 = 0;
float V_ref = 0;
float freq = 1e5; //200KHz
float Ts = 1/1e5;

float iL_cmd = 0.5;
float V_cmd = 4.2;
int mode = 0;// 0 : CC mode ; 1: CV mode

static float Delay_tau = 2e-3;


#endif /* MAIN_H_ */
