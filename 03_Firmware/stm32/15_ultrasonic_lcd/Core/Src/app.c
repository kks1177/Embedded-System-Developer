// app.c
// 15_ultrasonic_lcd

#include "app.h"

#define D_PULSE_ON(port, pin)		HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET)
#define D_PULSE_OFF(port, pin)	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET)
#define D_GET_CNT()							(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_LOOP_TICK			2

#define D_ULTRA_ECHO_RANGE		(5000)			// micro-second
#define D_ULTRA_TRIG_PULSE		(10)				// micro-second
#define D_ULTRA_ECHO_PULSE		(4500)


extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

#define D_MAX_AVR		20
typedef struct {
	float dist[D_MAX_AVR];
	float avr;
	uint8_t idx_new, idx_old;
} MOVAVR_T;

typedef struct {
	uint16_t trig_prev, trig_curr; // pulse 길이, milli second
	uint8_t trig_state;
	
	bool echo_flag;
	uint16_t echo_counter[2];
	uint16_t echo_prev, echo_curr;


	
	// trigger port
	GPIO_TypeDef *trig_port;
	uint16_t trig_pin;
	// echo port
	GPIO_TypeDef *echo_port;
	uint16_t echo_pin;
	
} PULSE_T;

typedef struct {
	PULSE_T 	p;
	MOVAVR_T 	m;
	uint32_t currTick, prevTick;
} ULTRA_T;

#define D_ULTRA_MAX		1
ULTRA_T gUltra[D_ULTRA_MAX];

bool trigger_ultrasonic(PULSE_T *pPulse)
{
	bool ret = false;
	uint16_t temp;
	
	switch (pPulse->trig_state) {
		case 0 : {
			pPulse->trig_prev = D_GET_CNT();
			pPulse->trig_state++;
		} break;
		
		case 1 : {
			pPulse->trig_curr = D_GET_CNT();
			temp = pPulse->trig_curr - pPulse->trig_prev;
			if (temp > 5) pPulse->trig_state++;
		} break;
		
		case 2 : {
			D_PULSE_ON(pPulse->trig_port,  pPulse->trig_pin);
			pPulse->trig_prev = D_GET_CNT();
			pPulse->trig_state++;
		} break;
		
		case 3 : {
			pPulse->trig_curr = D_GET_CNT();
			temp = pPulse->trig_curr - pPulse->trig_prev;
			
			if (temp > D_ULTRA_TRIG_PULSE) {
				D_PULSE_OFF(pPulse->trig_port, pPulse->trig_pin);
				pPulse->trig_state = 0;
				ret = true;
			} 
		} break;
	} // switch
	
	return ret;
}

void app_init(void)
{
	gUltra[0].p.trig_port = GPIOG;
	gUltra[0].p.trig_pin = GPIO_PIN_2;
	gUltra[0].p.echo_port	= GPIOG;
	gUltra[0].p.echo_pin	= GPIO_PIN_3;
	
	gUltra[1].p.trig_port = GPIOG;
	gUltra[1].p.trig_pin = GPIO_PIN_2;
	gUltra[1].p.echo_port	= GPIOG;
	gUltra[1].p.echo_pin	= GPIO_PIN_3;
	
	for (int i=0; i<D_ULTRA_MAX; i++) {
		gUltra[i].m.idx_new = 0;
		gUltra[i].m.idx_old = 1;
	}
}	

//#define PERIODIC_SCAN

// LCD 제어 함수
void lcd_func(void)
{
	lcd_init();						// lcd 초기화
	lcd_disp_on();					// 화면에 글씨 출력
	lcd_clear_display();		// 화면 초기화
	lcd_home();
	//lcd_print_string("Hello");
}

void app_main(void)
{
	char buf1[17];
	char buf2[17];
	
	lcd_func();		
	
	//uint8_t toggle = 0;
	PULSE_T *pPulse;
	MOVAVR_T *pMovAvr;
	ULTRA_T *pUltra;
	
	volatile float dist ;
	volatile uint16_t pulse;
	uint8_t sen_idx = 0, sen_state = 0;
	uint16_t temp;
#ifdef PERIODIC_SCAN
	uint16_t period_prev, period_curr;
#endif	
	app_init();
	HAL_TIM_Base_Start(&htim14);
	
	pUltra = &gUltra[sen_idx];
	pPulse = &pUltra->p; 
	pMovAvr = &pUltra->m;

#ifdef PERIODIC_SCAN
	period_prev = HAL_GetTick();
#endif

	while (1) {
		switch (sen_state) {
			case 0 : {
#ifdef PERIODIC_SCAN
				period_curr = HAL_GetTick();
				temp = period_curr - period_prev;
				if (temp > 10) { // 10ms
					sen_state++;
					period_prev = period_curr;
				}
#else				
				sen_state++;
#endif
			} break;
			
			case 1 : {
				// trigger pulse
				pPulse->echo_flag = false;		// interrup routine에서 timer capture 가능하도록...
				
				if (trigger_ultrasonic(pPulse) == true) sen_state++;
				pPulse->echo_prev = D_GET_CNT();
			} break;
				
			case 2 : {
				temp = (uint16_t)D_GET_CNT() - pPulse->echo_prev;			// 놓쳤을 경우 에코 처리
				
				if (temp < D_ULTRA_ECHO_RANGE) {  // 응답이 대기 시간
					if (pPulse->echo_flag == true) {
						dist = 0;					
						pulse = pPulse->echo_counter[1] - pPulse->echo_counter[0];

						if (pulse < D_ULTRA_ECHO_PULSE) {
							dist = (float)pulse / 58.0f;
							pMovAvr->dist[pMovAvr->idx_new] = dist/D_MAX_AVR;
							//printf("pulse, dist = %d, %f\n", pulse, dist);				
						} 

						pMovAvr->avr -= pMovAvr->dist[pMovAvr->idx_old];
						pMovAvr->avr += pMovAvr->dist[pMovAvr->idx_new];
						
						pMovAvr->idx_old++;
						pMovAvr->idx_new++;
						pMovAvr->idx_old %= D_MAX_AVR;			
						pMovAvr->idx_new %= D_MAX_AVR;
						
						if (pMovAvr->avr < 0.001f && pMovAvr->avr > -0.001f) 
							pMovAvr->avr = 0.0f;					
						
						//printf("%5.2f,%5.2f\r\n", dist, pMovAvr->avr);	
						
						lcd_clear_display();
						
						sprintf(buf1, "%8.3f", dist);
						lcd_locate(1,1);
						lcd_print_string(buf1);
						
						sprintf(buf2, "%8.3f", pMovAvr->avr);
						lcd_locate(2,1);
						lcd_print_string(buf2);
						
						HAL_Delay(500);
						
						//pPulse->echo_flag = false;
						sen_state++;
					} 
				} else {
					//pPulse->echo_flag = false;					
					sen_state++; // timeout
				}
			}	break;
				
			case 3 : {			
				// 다음 센서					
				sen_idx++;
				sen_idx %= D_ULTRA_MAX;				
				sen_state = 0;			
				
				pUltra = &gUltra[sen_idx];
				pPulse = &pUltra->p; 
				pMovAvr = &pUltra->m;

			} break;
		} // switch(sen_state) {
	} // if (currTick - prevTick > D_LOOP_TICK) {	// 2ms
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)	
{
	if (GPIO_Pin == gUltra[0].p.echo_pin) {  // ECHO
		if (gUltra[0].p.echo_flag == false) {
			if (HAL_GPIO_ReadPin(gUltra[0].p.echo_port, gUltra[0].p.echo_pin) == GPIO_PIN_SET) { // rising
				gUltra[0].p.echo_counter[0] = (uint16_t)D_GET_CNT(); //htim14.Instance->CNT;
			} else { // falling
				gUltra[0].p.echo_counter[1] = (uint16_t)D_GET_CNT();
				gUltra[0].p.echo_flag = true;
			}
		}
	} else if (GPIO_Pin == GPIO_PIN_13) { // User Button
		//flag_button = true;
	}
}

// ComPort Master 출력을 위한 코드
//int fputc(int ch, FILE *f)
//{
//	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
//	return ch;
//}
