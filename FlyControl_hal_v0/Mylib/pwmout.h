#ifndef __PWM_OUT_H__
#define __PWM_OUT_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <stm32f1xx_hal.h>

#define PWM_freq	200							//PWM频率设置
#define PWM_Period	5000						//周期频率设置
#define PWM_CLOCK (PWM_freq*PWM_Period)			//PWM时钟频率计算

#define  PWM_PA8	2
#define  PWM_PA9	3
#define  PWM_PA10	4
#define  PWM_PA11	7

	typedef struct
	{
		short CH[8];
	}PWM_TypeDef;

	void PWM_init(void);
	void set_pwm_val(char CH, uint32_t val);
	void all_pwm_set();

#ifdef __cplusplus
}
#endif

#endif