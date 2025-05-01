// gpio_input
// app.c

#include <string.h>
#include <stdio.h>
#include "app.h"

#define GET_BTN()		HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin)

void app_init(void) {
	printf("System Start....\n");
}

void app_loop(void)
{
	GPIO_PinState pinStsCurr, pinStsPrev;
	uint32_t timeCurr;
	
	app_init();
	
	pinStsCurr = pinStsPrev = GET_BTN();

	while (1) {
		HAL_Delay(100);
		
		pinStsCurr = GET_BTN();
		
		// rising edge
		if (pinStsPrev == GPIO_PIN_RESET && pinStsCurr == GPIO_PIN_SET ) {
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
			printf("LED on\n");
			timeCurr = HAL_GetTick();			
		}
		// falling edge	
		else if (pinStsPrev == GPIO_PIN_SET && pinStsCurr == GPIO_PIN_RESET ) {
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
			printf("LED off\n");
			if (HAL_GetTick() - timeCurr > 1000)		// 1초 이상 버튼 눌러짐
				printf("long key....\n");
			else 
				printf("short key....\n");
		}
		pinStsPrev = pinStsCurr;
	}
}

extern UART_HandleTypeDef huart3;
int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
