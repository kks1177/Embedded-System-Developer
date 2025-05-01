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
//		if (pinStsPrev == GPIO_PIN_RESET && pinStsCurr == GPIO_PIN_SET) {			// ��ư�� ������
//			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
//			printf("LED on \n");
//			timeCurr = HAL_GetTick();
//		} 
//		// falling edge
//		else if (pinStsPrev == GPIO_PIN_SET && pinStsCurr == GPIO_PIN_RESET) {			// ��ư�� ������ �ʾ�����
//			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
//			printf("LED off \n");
//			
//			if (HAL_GetTick() - timeCurr > 1000)		// 1�� �̻� ��ư ������
//				printf("Long Key... \n");
//			else 
//				printf("Short Key... \n");
//		}
//		pinStsPrev = pinStsCurr;
	}
}

// ���� tick ���� �а� ������ ����Ǿ� �ִ� ���� ��
// �� ���� ���̰� 150m/s�� �Ѵ´ٸ�,
// flag_btn = true�� �����.
// �׸��� ���� tick ���� ������ tick ���� �����ϰ� 
// �Լ��� ���� ���´�.
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
