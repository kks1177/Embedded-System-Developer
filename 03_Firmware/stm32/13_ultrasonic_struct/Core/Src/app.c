// app.c
// 13_ultrasonic_struct

// 강사님 코드
///*
#include "app.h"

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim14;

static SENSE_T gSenseObj[] = {
	{{{0, },	0.0,	0,	false},	{{0, },	0,	0,	0,	false,	false,	0.0,	0.0,	0.0},	trig_GPIO_Port,	GPIOG,	trig_Pin,	echo_Pin},
	{{{0, },	0.0,	0,	false},	{{0, },	0,	0,	0,	false,	false,	0.0,	0.0,	0.0},	NULL,						NULL,		0,				0				},
};

//static uint16_t cnt[2];
//static uint16_t time_rising;
//static bool flag_tx = false;
//static bool flag = false;
//static bool machine_flag = false;
//static bool mot_on_flag = false;
//static float dist_mean = 0.0, velo_mean = 0.0, accl_mean = 0.0;

void machine_status(SENSE_T* pSense, float d){
	DIST_T* pDist = &pSense->d;

	pDist->accl_mean = pDist->velo_mean;
	pDist->velo_mean = pDist->dist_mean;
	pDist->dist_mean = moving_avg(&pSense->m, d);
		
	if(pDist->dist_mean >= 3.0f && pDist->dist_mean <= 140.0f){	
		pDist->velo_mean = (pDist->dist_mean - pDist->velo_mean) * (1000.0f / DELTA_T);
		pDist->accl_mean = (pDist->velo_mean - pDist->accl_mean) * (1000.0f / DELTA_T);
		printf("%.2f %.2f\n", d, pDist->dist_mean);
		//printf("d : %8.2f, v : %8.2fm/s, a : %8.2fm/s^2\n", pDist->dist_mean, -pDist->velo_mean/100, -pDist->accl_mean/100);
		
//		if(machine_flag && dist_mean < 100 && fabs(accl_mean) > 5){
//			HAL_GPIO_ReadPin(GPIOB, LD1_Pin)
//			if(dist_mean > 15 && accl_mean > 5){
//				HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
//				HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
//				mot_on_flag = false;
//			}
//			else if(dist_mean < 8 && accl_mean < -5){
//				HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
//				mot_on_flag = false;
//			}
//		}
//		else if(dist_mean > 100){
//			HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
//			mot_on_flag = false;
//			machine_flag = false;
//		}
//		else if(!mot_on_flag){
//			HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
//			machine_flag = true;
//			mot_on_flag = true;
//		}
//	}
//	else if(mot_on_flag) {
//		HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
//		mot_on_flag = false;
//		machine_flag = false;
	}
}

void app_init(){
	printf("System start\n");
	
	HAL_TIM_Base_Start(&htim14);
}

void ultrasonic_proc(SENSE_T* pSense){
	SENSE_T* pSen;
	DIST_T* pDist;
	float dist;
	
	for(uint8_t i=0; pSense[i].trigger_pin != NULL; i++){
		pSen = &pSense[i];
		pDist = &pSen->d;
		
		pDist->curr_t = HAL_GetTick();
		if (!pDist->flag_tx && !pDist->flag){
			HAL_GPIO_WritePin(pSen->trigger_port, pSen->trigger_pin, GPIO_PIN_SET);

			pDist->flag_tx = true;
			pDist->flag = true;
			pDist->prev_t = pDist->curr_t;
			pDist->time_rising = __HAL_TIM_GET_COUNTER(&htim14);
		}
		else if(pDist->flag_tx && pDist->flag && pDist->curr_t - pDist->prev_t < DELTA_T && (uint16_t)(__HAL_TIM_GET_COUNTER(&htim14) - pDist->time_rising) > 100){
			HAL_GPIO_WritePin(pSen->trigger_port, pSen->trigger_pin, GPIO_PIN_RESET);
			pDist->flag = false;
		}
		else if(pDist->flag_tx && pDist->curr_t - pDist->prev_t >= DELTA_T){
			dist = (uint16_t)(pDist->cnt[1] - pDist->cnt[0]) / (float)58;
			machine_status(pSen, dist);
			pDist->flag_tx = false;
		}
	}
}

void app_loop(){
	app_init();
	
	while(1){
		ultrasonic_proc(gSenseObj);

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	for(uint8_t i=0; gSenseObj[i].trigger_pin != NULL; i++){
		if (GPIO_Pin == gSenseObj[i].echo_pin){ //ECHO
			if(HAL_GPIO_ReadPin(gSenseObj[i].echo_port, gSenseObj[i].echo_pin) == GPIO_PIN_SET){ // rising
				gSenseObj[i].d.cnt[0] = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
				return;
			}
			else { // falling
				gSenseObj[i].d.cnt[1] = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
				return;
			}
		}
	}
	if(GPIO_Pin == GPIO_PIN_13){ //USER_Btn

	}
//	
}


int fputc(int ch, FILE *f){
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
//*/









// 웅식이형 코드
/*
#include "app.h"

#define D_PULSE_ON()   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
#define D_PULSE_OFF()   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
#define D_GET_CNT()      (uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_ULTRA_RANGE      4000      // micro-second
#define D_ULTRA_PULSE      30         // micro-second
#define D_ULTRA_PERIOD   	 70         // micro-second (trigger priod)

extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

//uint16_t curTick, preTick;

//volatile bool flag_tick = false;
//volatile bool flag_button = false;
//volatile bool flag_echo = false;

#define D_MAX_AVR      30
#define D_ULTRA_MAX      2

typedef struct {
   float dist[D_MAX_AVR];
   float avr;
   uint8_t idx_new, idx_old;
} MOVAVR_T;
typedef struct {
   uint16_t counter[2];
   uint32_t curTickMs, preTickMs;
   bool flag_echo;
} PULSE_T;
typedef struct {
   PULSE_T    p;
   MOVAVR_T    m;
   uint16_t preTick, curTick;
   bool flag_tick;
   uint8_t state;
} ULTRA_T;

ULTRA_T gUltra[2];

void trigger_ultrasonic(ULTRA_T *pUltra)
{
   if (pUltra->flag_tick == true) {
      pUltra->flag_tick = false;
      pUltra->state = 0;
   }
   
   switch (pUltra->state) {
      case 0 : {
         pUltra->preTick = pUltra->curTick = (uint16_t)D_GET_CNT();
         D_PULSE_ON();
         pUltra->state++;
      } break;
      
      case 1 : {
         pUltra->curTick = (uint16_t)D_GET_CNT();
         if ((uint16_t)(pUltra->preTick - pUltra->curTick) > D_ULTRA_PULSE) {
            D_PULSE_OFF();
            pUltra->state++;
         } 
      } break;
      
//      defalut : {
//      } break;
   }   
}

void trigger(ULTRA_T *pUltra)
{
   PULSE_T *pPulse;
   
   pPulse = &(pUltra->p);
   
   pPulse->curTickMs = HAL_GetTick();
   if (pPulse->curTickMs - pPulse->preTickMs > D_ULTRA_PERIOD) { // Milli-Second
      if (pUltra->flag_tick == false) {
         pUltra->flag_tick = true;
      }
      pPulse->preTickMs = pPulse->curTickMs;
   }
   trigger_ultrasonic(pUltra);
}

void app_init(void)
{
   for (int i=0; i<D_ULTRA_MAX; i++) {
      gUltra[i].m.idx_new = 0;
      gUltra[i].m.idx_old = 1;
      gUltra[i].p.preTickMs = gUltra[i].p.curTickMs = HAL_GetTick();
   }
}   

void app_main(void)
{
   //uint8_t toggle = 0;
   PULSE_T *pPulse;
   MOVAVR_T *pMovAvr;
   ULTRA_T *pUltra;
   volatile float dist ;
   volatile uint16_t pulse;
   
   app_init();
	 
   HAL_TIM_Base_Start(&htim14);
   
   while (1) {
//      if (flag_button == true) {
//         flag_button = false;
//         flag_tick = true;
//      }
		 
      pUltra = &gUltra[0];
      pPulse = &pUltra->p; 
      pMovAvr = &pUltra->m;
      
      trigger(pUltra);

      if (pPulse->flag_echo == true) {
         //거리 계산식.. && 출력
//         printf("counter[0] = %d\n", counter[0]);
//         printf("counter[1] = %d\n", counter[1]);
         dist = 0;
         pulse = pPulse->counter[1] - pPulse->counter[0];

         if (pulse < D_ULTRA_RANGE) {
            dist = (float)pulse / 58.0f;
            pMovAvr->dist[pMovAvr->idx_new] = dist/D_MAX_AVR;
            //printf("pulse, dist = %d, %f\n", pulse, dist);            
         } else {
            pMovAvr->dist[pMovAvr->idx_new] = 0;
         }

         pMovAvr->avr -= pMovAvr->dist[pMovAvr->idx_old];
         pMovAvr->avr += pMovAvr->dist[pMovAvr->idx_new];
         
         pMovAvr->idx_old++;
         pMovAvr->idx_new++;
         pMovAvr->idx_old %= D_MAX_AVR;         
         pMovAvr->idx_new %= D_MAX_AVR;
         
         if (pMovAvr->avr < 0.001f && pMovAvr->avr > -0.001f)
					 pMovAvr->avr = 0.0f;
				 
         printf("%5.2f,%5.2f\r\n", dist, pMovAvr->avr);

         pPulse->flag_echo = false;
      }      
   }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if (GPIO_Pin == GPIO_PIN_3) {  // ECHO
      if (gUltra[0].p.flag_echo == false) {
         if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) { // rising
            gUltra[0].p.counter[0] = (uint16_t)D_GET_CNT(); //htim14.Instance->CNT;
         } else { // falling
            gUltra[0].p.counter[1] = (uint16_t)D_GET_CNT();
            gUltra[0].p.flag_echo = true;
         }
      }
   } else if (GPIO_Pin == GPIO_PIN_13) { // User Button
      //flag_button = true;
   }
}

int fputc(int ch, FILE *f)
{
   HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
   return ch;
}
*/
