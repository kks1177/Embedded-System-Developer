// exti_Btn
// app.c

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "app.h"

#define GET_BTN()  HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);


bool flag_btn; // = false;
uint8_t count_btn = 0;


void app_init(void) {
	printf("System Start... \n");
	flag_btn = false;
}

void app_loop(void)
{
//	GPIO_PinState pinStsCurr, pinStsPrev;
	uint32_t localCount = 0;
	
	app_init();
	
//	pinStsCurr = pinStsPrev = GET_BTN();

	
	while (1) {
		if (flag_btn == true) {
			flag_btn = false;
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			printf("Button Pushed : %d/%d\n", count_btn, localCount++);
			count_btn = 0;
		}

		
		
//		HAL_Delay(100);
//		
//		pinStsCurr = GET_BTN();
//		
//		// rising edge 
//		if (pinStsPrev == GPIO_PIN_RESET && pinStsCurr == GPIO_PIN_SET) {			// 버튼이 눌리면
//			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
//			printf("LED on \n");
//			timeCurr = HAL_GetTick();
//		} 
//		// falling edge
//		else if (pinStsPrev == GPIO_PIN_SET && pinStsCurr == GPIO_PIN_RESET) {			// 버튼이 눌리지 않았으면
//			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
//			printf("LED off \n");
//			
//			if (HAL_GetTick() - timeCurr > 1000)		// 1초 이상 버튼 눌러짐
//				printf("Long Key... \n");
//			else 
//				printf("Short Key... \n");
//		}
//		pinStsPrev = pinStsCurr;
	}
}

// 현재 tick 값을 읽고 이전에 저장되어 있는 값과 비교
// 그 값의 차이가 150m/s가 넘는다면,
// flag_btn = true로 만든다.
// 그리고 현재 tick 값을 이전에 tick 값에 저장하고 
// 함수를 빠져 나온다.
//static uint32_t preTick = 0, currTick;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	static uint32_t prevTick = 0, currTick;
	
	currTick = HAL_GetTick();
		
	if (currTick - prevTick > 150) {
		flag_btn = true;
		count_btn++;
		prevTick = currTick;
	}
}

extern UART_HandleTypeDef huart3;
int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
