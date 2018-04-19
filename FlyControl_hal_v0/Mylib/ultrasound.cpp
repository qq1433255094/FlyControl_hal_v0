#include "ultrasound.h"
#include "RC.h"

extern "C" void EXTI4_IRQHandler();

uint32_t ultra_time = 0;

void ultrasound_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();

	GPIO_InitStructure.Pin = GPIO_PIN_4;

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_3;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	HAL_NVIC_SetPriority(EXTI4_IRQn, 0x0f, 0);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void ultrasound_start()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++)
	{
		asm("nop");
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
}


void ultrasound_Callback(uint16_t GPIO_Pin)
{
	static char status = 1;
	static uint32_t ultrasound_timh;
	static uint32_t ultrasound_timl;
	static uint32_t ultrasound_timmh;
	static uint32_t ultrasound_timml;

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN; //IO重新初始化

	if (status == 1) {					//等待上升沿处理

		ultrasound_timh = TIM4->CNT;				//获取上升沿时间
		ultrasound_timmh = HAL_GetTick();
		GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;		//重新初始化为下降沿接收
		status = 0;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	else if (status == 0)					//等待下降沿处理
	{

		ultrasound_timl = TIM4->CNT;					//获取下降沿时间
		ultrasound_timml = HAL_GetTick();
		int data = (int)(ultrasound_timl - ultrasound_timh);

		ultra_time = (ultrasound_timml - ultrasound_timmh)>18?18000:(data > 0 ? data : data + TIM4Period);			//计算高电平时间
		status = 1;
		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;		//重新初始化为上升沿接收
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	}
}

void EXTI4_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}



