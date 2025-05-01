// app.c
// 10_timer_ir			// ������ �Ÿ� ����


#include "app.h"

#define D_PULSE_ON()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
#define D_FULSE_OFF()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
#define D_GET_CNT()			(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_ULTRA_RANGE		5000		// micro-second


// ========== ���� ������ ==========
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

bool flag_ir = false;
uint16_t counter[2];


// ========== �Լ� ����� ==========
void app_init(void);


// ���� ��ư ���� �� ������ �Ÿ� ����
///*
// ========== ���� �Լ� ==========
void app_main(void)
{
	app_init();
	
	HAL_TIM_Base_Start(&htim14);
	
	while(1) {
		if (flag_ir == true) { 			// ���� �Է� �Ǿ�����
			//printf("Button Pushed!!! \n");
			volatile float distance;		// �Ÿ�
			uint16_t pulse;							// �޽�
			
			pulse = counter[1] - counter[0];
			distance = (float)pulse / 58.0f;
			
			if (pulse < D_ULTRA_RANGE) {		// D_ULTRA_RANGE : 5000
				printf("time = %d, distance = %f\n", pulse, distance);
			} 
			else {
				printf("Out of Range!\n");
			}
         
      flag_ir = false;
    }
	}
}


// ========== �Լ� ���Ǻ� ==========
void app_init(void)
{
	printf("System start \n");
	HAL_TIM_Base_Start(&htim14);
}

void remoteControl(void)
{
	
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
{
	if (GPIO_Pin == GPIO_PIN_3) {		// ECHO
		if (flag_ir == false) {
			if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) {		// rising
				counter[0] = D_GET_CNT(); //htim14.Instance->CNT;
			} 
			else {		// falling
				counter[1] = D_GET_CNT();
				flag_ir = true;
			}
		}
	}
	else if (GPIO_Pin == GPIO_PIN_13) {		// User Button
		flag_ir = true;
	}
}

int fputc(int ch, FILE *f) 
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
//*/


