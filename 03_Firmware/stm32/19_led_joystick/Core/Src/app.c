// app.c

#include "main.h"
#include "app.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart3;

uint16_t adc_result[4];

void app_main(void)
{
	uint16_t cmp_r, cmp_g, cmp_b;
	
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_result, 4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
	
	while(1) {
		HAL_Delay(300);
		printf("%d, %d, %d, %d \n", adc_result[0], adc_result[1], adc_result[2], adc_result[3]);
		
		cmp_r = (uint16_t)((float)adc_result[0] / 4096.0f * 1000.0f);
		cmp_g = (uint16_t)((float)adc_result[1] / 4096.0f * 1000.0f);
		cmp_b = (uint16_t)((float)adc_result[2] / 4096.0f * 1000.0f);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, cmp_r);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, cmp_g);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, cmp_b);
	}
}



int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
