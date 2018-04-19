#ifndef __IIC1_H__
#define __IIC1_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"

/* MPU6050 Register Address ------------------------------------------------------------*/
#define	SMPLRT_DIV		0x19	
#define	CONFIG			0x1A	
#define	GYRO_CONFIG		0x1B	
#define	ACCEL_CONFIG	0x1C	
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	
#define	WHO_AM_I		0x75	
#define	SlaveAddress	0xD0	

#define I2C_ADDRESS 0x20

	void i2c1_init(void);
	uint8_t I2C1_ReadData(uint8_t Addr, uint8_t Reg);
	void I2C1_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value);
	void I2C1_ReadMultData(uint8_t Addr, uint8_t Reg, uint8_t *value, uint8_t len);
#ifdef __cplusplus
}
#endif

#endif