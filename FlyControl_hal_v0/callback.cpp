#include "callback.h"



void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_4)
	{
		ultrasound_Callback(GPIO_Pin);
	}

	if (GPIO_Pin > GPIO_PIN_9)
	{
		RC_Callback(GPIO_Pin);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance == USART1)
	{
		UART1_Handler();
	}
	else if (huart->Instance == USART2)
	{
		UART2_Handler();
	}

}