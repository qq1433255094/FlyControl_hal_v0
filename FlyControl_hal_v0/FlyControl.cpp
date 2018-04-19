#include <stm32f1xx_hal.h>
#include "callback.h"
#include "arm_math.h"

extern RC_TypeDef RC;
extern PWM_TypeDef PWM;
extern I2C_HandleTypeDef hi2c1;


uint8_t data[14];
short test[7] = {0};
uint8_t reg[2] = { 0 };
uint32_t flashdata;
int angle = 0;
int angle2 = 0,angle_set=-300;
int angle3 = 0,speed=0;
uint8_t test_val = 0;
int32_t add = 360;
float Kp = 0.3, Kd = 0.5;

void set_motor_speed(int32_t l, int32_t r)
{
	
	if (l > 0)
	{
		set_pwm_val(PWM_PA11, 0);
		set_pwm_val(PWM_PA10, l+ add);
	}
	else
	{
		set_pwm_val(PWM_PA10, 0);
		set_pwm_val(PWM_PA11, -l+ add);
	}

	if (r>0)
	{
		set_pwm_val(PWM_PA9, 0);
		set_pwm_val(PWM_PA8, r + add);
	}
	else
	{
		set_pwm_val(PWM_PA8, 0);
		set_pwm_val(PWM_PA9, -r+ add);
	}
	
}

int32_t out=0;
int32_t out_last=0;


int main(void)
{
	HAL_Init(); 

	PWM_init();
	i2c1_init();
	spi1_init();

	GPIO_InitTypeDef gpio_init;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_init.Pin = GPIO_PIN_1;
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &gpio_init);

	test_val = I2C1_ReadData(SlaveAddress, WHO_AM_I);
	I2C1_WriteData(SlaveAddress, PWR_MGMT_1, 0x00);
	I2C1_WriteData(SlaveAddress, SMPLRT_DIV, 0x07);
	I2C1_WriteData(SlaveAddress, CONFIG, 0x06);
	I2C1_WriteData(SlaveAddress, GYRO_CONFIG, 0x18);
	I2C1_WriteData(SlaveAddress, ACCEL_CONFIG, 0x01);
	
	for (;;)
	{
		/*set_pwm_val(PWM_PA8, 4500);
		set_pwm_val(PWM_PA9, 0);
		set_pwm_val(PWM_PA10, 1400);
		set_pwm_val(PWM_PA11, 0);*/
		

		I2C1_ReadMultData(SlaveAddress, ACCEL_XOUT_H, data, 14);

		for (uint8_t i = 0; i < 7; i++)
		{
			test[i] = (data[i * 2] << 8) + data[i * 2 + 1];
		}
		int temp = angle;
		angle = atan((float)test[1] / (float)test[2])*6000;
		if (test[2] < 0 )
		{
			if (angle < 0)
			{
				angle += 9384*2;
			}
			else
			{
				angle -= 9384 * 2;
			}
		}
		angle = 0.5*temp + 0.5*angle;
		angle2 += test[4] * 0.1;
		angle2 = 0.2*angle + 0.8*angle2;
		angle3 = angle2;


		//speed += out*0.2 + speed*0.8;


		if (out > 500)
		{
			angle_set = -800 -300;
		}
		if (out < -500)
		{
			angle_set = 800 - 300;
		}

		out = (angle2-angle_set) *0.4 + test[4] * 0.55;// +speed*0.1;
		out_last = out;

		set_motor_speed(out, out);

		HAL_Delay(10);
	}
}










