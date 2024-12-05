/*
 * Init.h
 *
 */

#ifndef INIT_H_
#define INIT_H_

//#include "MODULE.h"    /* For extern parameter */
#include "pid.h"
//#include "GLB_CONST.h"

extern void Init_CpuTimer(void);

extern void Init_GPIO(void);
extern void Init_PIE(void);

void Init_ePWM(void);
void Init_ADC(void);
void Init_ADCSOC(void);


#endif /* INIT_H_ */







