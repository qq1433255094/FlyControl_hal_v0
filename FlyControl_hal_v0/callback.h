
#ifndef __CALLBACK_H__
#define __CALLBACK_H__


#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
#include "RC.h"
#include "pwmout.h"
#include "ultrasound.h"
#include "uart1.h"
#include "uart2.h"
#include "i2c1.h"
#include "spi1.h"

	void SysTick_Handler(void);
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#ifdef __cplusplus
}
#endif

#endif


