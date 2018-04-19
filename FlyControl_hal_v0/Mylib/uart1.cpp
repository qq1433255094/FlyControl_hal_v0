#include "uart1.h"

UART_HandleTypeDef huart1;
uint8_t receive1[10], transmit1[10];

extern "C" void USART1_IRQHandler();
/**
* @brief ��ʼ������4
* @param none
* @note none
* @retval none
*/

void uart1_init(void)
{
	GPIO_InitTypeDef gpio_init;

	HAL_NVIC_SetPriority(USART1_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	__HAL_AFIO_REMAP_USART1_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	gpio_init.Pin = GPIO_PIN_6;
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &gpio_init);

	gpio_init.Pin = GPIO_PIN_7;
	gpio_init.Mode = GPIO_MODE_AF_INPUT;
	HAL_GPIO_Init(GPIOB, &gpio_init);

	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = USART_WORDLENGTH_8B;
	huart1.Init.StopBits = USART_STOPBITS_1;
	huart1.Init.Parity = USART_PARITY_NONE;
	huart1.Init.Mode = USART_MODE_TX_RX;
	huart1.Instance = USART1;

	HAL_UART_Init(&huart1);
	HAL_UART_Receive_IT(&huart1, receive1, 1);
}

/**
* @brief ����4�����ַ���
* @param *b���ַ�������ָ��
* @note none
* @retval none
*/
void uart1_send(const char *b)
{
	char len = strlen(b);
	HAL_UART_Transmit(&huart1, (uint8_t *)b, len, len * 2);
}

void UART1_Handler(void)
{
	HAL_UART_Receive_IT(&huart1, receive1, 1);
}

void USART1_IRQHandler()
{
	HAL_UART_IRQHandler(&huart1);
}