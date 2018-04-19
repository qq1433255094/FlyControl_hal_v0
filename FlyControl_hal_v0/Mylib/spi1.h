#ifndef __SPI1_H__
#define __SPI1_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
#define READWRITE_CMD                     ((uint8_t)0x80) 
#define MULTIPLEBYTE_CMD                  ((uint8_t)0x40)
#define DUMMY_BYTE						  ((uint8_t)0x00)

	void spi1_init(void);
	uint8_t SPI1_WriteRead(uint8_t Byte);
	void ACCELERO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
#ifdef __cplusplus
}
#endif

#endif