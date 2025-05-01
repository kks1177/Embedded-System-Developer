#include "app.h"


#define D_PULSE_ON()	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
#define D_PULSE_OFF()	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
#define D_GET_CNT()		(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_ULTRA_RANGE		4500		// micro-second
#define D_ULTRA_PULSE		30			// micro-second

extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

uint16_t curTick, preTick;

volatile bool flag_tick = false;
volatile bool flag_button = false;
volatile bool flag_echo = false;

uint16_t counter[2];

//volatile uint32_t curTickMs, preTickMs;

void trigger_ultrasonic(void)
{
	static uint8_t state = 0;
	
	if (flag_tick == true) {
		flag_tick = false;
		state = 0;
	}
	
	switch (state) {
		case 0 : {
			preTick = curTick = (uint16_t)D_GET_CNT();
			D_PULSE_ON();
			state++;
		} break;
		
		case 1 : {
			curTick = (uint16_t)D_GET_CNT();
			if ((uint16_t)(preTick - curTick) > D_ULTRA_PULSE) {
				D_PULSE_OFF();
				state++;
			} 
		} break;
		
		defalut : {
		} break;
	}	
}

void app_main(void)
{
	
	HAL_TIM_Base_Start(&htim14);
	
//	preTickMs = curTickMs = HAL_GetTick();
	
	while (1) {
		if (flag_button == true) {
			flag_button = false;
			flag_tick = true;
		}
		
//		curTickMs = HAL_GetTick();
//		if (curTickMs - preTickMs > 150) { // Milli-Second
//			if (flag_tick == false) {
//				flag_tick = true;
//			}
//			preTickMs = curTickMs;
//		}

		trigger_ultrasonic();

		
		if (flag_echo == true) {
			//거리 계산식.. && 출력
//			printf("counter[0] = %d\n", counter[0]);
//			printf("counter[1] = %d\n", counter[1]);
			volatile float dist;
			uint16_t pulse;
			
			pulse = counter[1]-counter[0];
			dist = (float)pulse / 58.0f;
			if (pulse < D_ULTRA_RANGE) {
				printf("time = %d, dist = %f\n", pulse, dist);
			} else {
				printf("Out of range!\n");
			}
			//printf("d=%f\n", (float)((uint16_t)((uint16_t)counter[1]-(uint16_t)counter[0]))/58.0f);
			
			flag_echo = false;
		}		
	}
	
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_3) {  // ECHO
		if (flag_echo == false) {
			if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) { // rising
				counter[0] = D_GET_CNT(); //htim14.Instance->CNT;
			} else { // falling
				counter[1] = D_GET_CNT();
				flag_echo = true;
			}
		}
	} else if (GPIO_Pin == GPIO_PIN_13) { // User Button
		flag_button = true;
	}
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
