#include "pwmout.h"
#include "RC.h"

PWM_TypeDef PWM;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
extern RC_TypeDef RC;

void PWM_init(void)
{
	GPIO_InitTypeDef gpio_init;
	TIM_OC_InitTypeDef oc_init;

	__HAL_RCC_AFIO_CLK_ENABLE();		//����AFIOʱ��
	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	gpio_init.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	gpio_init.Mode	= GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOA, &gpio_init);

	gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 ;
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOB, &gpio_init);

	htim1.Instance					= TIM1;
	htim1.Init.Prescaler			= SystemCoreClock / PWM_CLOCK - 1;
	htim1.Init.Period				= PWM_Period - 1;
	htim1.Init.CounterMode			= TIM_COUNTERMODE_UP;
	htim1.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter	= 0;

	htim3							= htim1;
	htim3.Instance					= TIM3;

	HAL_TIM_PWM_Init(&htim1); //��ʱ��1 PWM�����ʼ��
	HAL_TIM_PWM_Init(&htim3); //��ʱ��3 PWM�����ʼ��

	oc_init.OCMode			= TIM_OCMODE_PWM1;			//�������ʽ����
	oc_init.OCPolarity		= TIM_OCPOLARITY_HIGH;
	oc_init.OCNPolarity		= TIM_OCNPOLARITY_LOW;
	oc_init.OCFastMode		= TIM_OCFAST_DISABLE;
	oc_init.OCNIdleState	= TIM_OCNIDLESTATE_RESET;
	oc_init.OCIdleState		= TIM_OCIDLESTATE_RESET;
	oc_init.Pulse			= 0;

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_1); //��ʱ��1 PWM CH1-CH4 ��ʼ��
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	HAL_TIM_PWM_ConfigChannel(&htim1, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	oc_init.OCMode			= TIM_OCMODE_PWM2; //�������ʽ����
	oc_init.OCPolarity		= TIM_OCPOLARITY_LOW;
	oc_init.OCNPolarity		= TIM_OCNPOLARITY_LOW;

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_1); //��ʱ��3 PWM CH1-CH2 ��ʼ��
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_3); //��ʱ��3 PWM CH1-CH2 ��ʼ��
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

	HAL_TIM_PWM_ConfigChannel(&htim3, &oc_init, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	for (char i = 0; i < 8; i++)
	{
		PWM.CH[i] = 1100;				//����PWM����ĳ�ʼֵ
		set_pwm_val(i, PWM.CH[i]);
	}

}

void set_pwm_val(char CH,uint32_t val)  //����PWM���ֵ
{
	switch (CH)
	{
	case 0:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;
	case 1:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;
	case 2:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, (val > PWM_Period ? PWM_Period : val)); break;
	case 3:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, (val > PWM_Period ? PWM_Period : val)); break;
	case 4:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;
	case 5:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, (val > PWM_Period ? PWM_Period : val)); break;
	case 6:__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;
	case 7:__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (val > PWM_Period ? PWM_Period : val)); break;
	
	default:
		break;
	}
}

void all_pwm_set()  //����PWM�������ֵ�����㶨ʱ������
{
	for (char i = 0; i < 6; i++)
	{
		PWM.CH[i] = RC.CH[i];
		set_pwm_val(i, PWM.CH[i]);
	}
}

