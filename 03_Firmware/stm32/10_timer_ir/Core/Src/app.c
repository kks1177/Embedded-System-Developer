// app.c
// 10_timer_ir			// 초음파 거리 측정


#include "app.h"

#define D_PULSE_ON()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
#define D_FULSE_OFF()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
#define D_GET_CNT()			(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_ULTRA_RANGE		5000		// micro-second


// ========== 전역 변수부 ==========
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

bool flag_ir = false;
uint16_t counter[2];


// ========== 함수 선언부 ==========
void app_init(void);


// 유저 버튼 누를 때 초음파 거리 측정
///*
// ========== 메인 함수 ==========
void app_main(void)
{
	app_init();
	
	HAL_TIM_Base_Start(&htim14);
	
	while(1) {
		if (flag_ir == true) { 			// 에코 입력 되었으면
			//printf("Button Pushed!!! \n");
			volatile float distance;		// 거리
			uint16_t pulse;							// 펄스
			
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


// ========== 함수 정의부 ==========
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


