#include "app.h"


#define D_GET_CNT()		(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;


#define D_MAX	100

typedef struct {
	uint16_t down, up, diff;
} PAIR_T;

typedef union {
	uint8_t 	d4[4];
	uint16_t 	d2[2];
	uint32_t  d1;
} TYPE_T;

PAIR_T arr[D_MAX];
volatile uint16_t idx = 0;
volatile uint16_t cnt_last = 0;
volatile bool flag_ir = false;

void app_main(void)
{
	
	printf("system start.....!\n");
	
	HAL_TIM_Base_Start(&htim14);
	
	while (1) {
		if (idx > 35) {
			if (1) {
				flag_ir = true;
				
				for (uint16_t i=0; i<idx; i++) {
					printf("%5d, %5d, %5d\n", arr[i].down, arr[i].up, arr[i].diff);
				}				

				for (uint16_t i=0; i<idx; i++) {
					arr[i].diff = arr[i+1].down - arr[i].up;
					printf("%5d\n", arr[i].diff);
				}				
				
				TYPE_T val, res;
				
				val.d1 = 0;
				
				for (uint16_t i=0; i<32; i++) {
					val.d1 |= (arr[i+1].diff > 1200 ? 1 : 0) << i;
				}

				printf("%08x\n", val.d1);	
				
				if ((val.d4[0] == (uint8_t)(~val.d4[1])) && (val.d4[2] == (uint8_t)(~val.d4[3]))) {
					res.d4[1] = val.d4[0];
					res.d4[0] = val.d4[2];

					printf("result code : %04x\n", res.d2[0]);
				} else {
					printf("result code : error!\n");
				}
				
				idx = 0;
				flag_ir = false;
			}
		}
	}
	
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	volatile uint16_t diff;
	
	if (GPIO_Pin == GPIO_PIN_3) {  // IR
		if (flag_ir == false) {
			if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) { // rising
				arr[idx].up = D_GET_CNT(); //htim14.Instance->CNT;
				cnt_last = arr[idx].up;
				
				arr[idx].diff = arr[idx].up - arr[idx].down;
				
				if (arr[idx].diff > 7000 && idx < 10) idx = 0;
				
				if (idx < D_MAX-1) {
					idx++;
				}			
			} else { // falling
				arr[idx].down = D_GET_CNT(); //htim14.Instance->CNT;
			}	

		}
	} else if (GPIO_Pin == GPIO_PIN_13) { // User Button

	}
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
