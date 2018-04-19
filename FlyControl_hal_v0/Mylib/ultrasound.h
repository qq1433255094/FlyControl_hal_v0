#ifndef __ULTRA_SOUND_H__
#define __ULTRA_SOUND_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"

	void ultrasound_init();
	void ultrasound_start();
	void ultrasound_Callback(uint16_t GPIO_Pin);



#ifdef __cplusplus
}
#endif

#endif