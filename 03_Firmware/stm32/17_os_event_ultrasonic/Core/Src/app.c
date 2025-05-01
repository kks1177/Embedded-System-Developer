#include "app.h"

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim14;

void StartDefaultTask(void *argument);	//pulse
void StartDefaultTask2(void *argument); //print
void StartDefaultTask3(void *argument); //lcd

static SENSE_T gSenseObj[] = {
	{	{{0, },	0.0,	0},	{0,	0,	0,	false,	false,	0.0,	0.0,	0.0},	{{0, },	0.0,	0},	{0, },	GPIOG,	GPIOG,	trig_Pin,		echo_Pin,		},
	{	{{0, },	0.0,	0},	{0,	0,	0,	false,	false,	0.0,	0.0,	0.0},	{{0, },	0.0,	0},	{0, },	GPIOG,	GPIOG,	trig2_Pin,	echo2_Pin,	},
	{	{{0, },	0.0,	0},	{0,	0,	0,	false,	false,	0.0,	0.0,	0.0},	{{0, },	0.0,	0},	{0, },	NULL,		NULL,		0,					0,					},
};

SENSE_T* p = gSenseObj;


osEventFlagsId_t evt_id;                        // message queue id
osThreadId_t defaultTaskHandle;
osThreadId_t defaultTaskHandle2;
osThreadId_t defaultTaskHandle3;


const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t defaultTask_attributes2 = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t defaultTask_attributes3 = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void app_init(){
	SENSE_T *pCurr, *pStart;
	printf("System start\n");
	
	HAL_TIM_Base_Start(&htim14);
	
	pStart = pCurr = &gSenseObj[0];
	
	for(uint8_t i=0; gSenseObj[i+1].trigger_pin != NULL;i++){
		pCurr->pNext = &gSenseObj[i+1];
		pCurr = pCurr->pNext;
	}
	
	pCurr->pNext = pStart;
}

void os_init(void){
	osKernelInitialize();
	
	defaultTaskHandle = osThreadNew(StartDefaultTask, p, &defaultTask_attributes);
	defaultTaskHandle2 = osThreadNew(StartDefaultTask2, p, &defaultTask_attributes2);
	defaultTaskHandle3 = osThreadNew(StartDefaultTask3, p, &defaultTask_attributes3);
	
	evt_id = osEventFlagsNew(NULL);
	osKernelStart();
	
}

void app_loop(void){
	app_init();
	lcd_initial();
	os_init();
	
}

void machine_status(SENSE_T* pSense, float d){
	DIST_T* pDist = &pSense->d;

	pDist->accl_mean = pDist->velo_mean;
	pDist->velo_mean = pDist->dist_mean;
	pDist->dist_mean = moving_avg(&pSense->m, d);
		
	pDist->velo_mean = (pDist->dist_mean - pDist->velo_mean) * (1000.0f / DELTA_T);
	pDist->accl_mean = (pDist->velo_mean - pDist->accl_mean) * (1000.0f / DELTA_T);
}


void StartDefaultTask(void *argument)
{
	SENSE_T* pSen;
	DIST_T* pDist;
	float dist;
	
	/* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		pSen = p;
		pDist = &pSen->d;
  
		HAL_GPIO_WritePin(pSen->trigger_port, pSen->trigger_pin, GPIO_PIN_SET);
		pDist->time_rising = __HAL_TIM_GET_COUNTER(&htim14);
		
		while((uint16_t)(__HAL_TIM_GET_COUNTER(&htim14) - pDist->time_rising) <= 100);
		
		HAL_GPIO_WritePin(pSen->trigger_port, pSen->trigger_pin, GPIO_PIN_RESET);
		
		osDelay(DELTA_T);
		
		dist = (uint16_t)(pSen->cnt[1] - pSen->cnt[0]) / (float)58;
		machine_status(pSen, dist);
		moving_avg(&pSen->m_l, pDist->dist_mean);
		p = p->pNext;
		
		if(pSen == gSenseObj){
			osEventFlagsSet(evt_id, 0x00000001U);
			osThreadYield();  
		}
		
		//flags = osEventFlagsWait(evt_id, 0x00000001U, osFlagsWaitAny, osWaitForever);
    
  }
  /* USER CODE END 5 */
}

void StartDefaultTask2(void *argument)
{
	SENSE_T* pSen = gSenseObj;
	/* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		osEventFlagsWait(evt_id, 0x00000001U, osFlagsWaitAny, osWaitForever);
		
		for(uint8_t i=0; gSenseObj[i].trigger_pin != NULL; i++)
			printf("%f ", pSen[i].d.dist_mean);
		printf("\n");
//		printf("%f %f\n", pSen[0].d.dist_mean, pSen[1].d.dist_mean);
//		if(flags & 1) {
//			printf("j=%d\n", j++);
//		}
//		if(flags & 2) {
//		}
//		osDelay(1000);
//		osEventFlagsSet(evt_id, 0x00000001U);
//    osThreadYield();  
  }
  /* USER CODE END 5 */
}

void StartDefaultTask3(void *argument)
{
	for(;;)
	{
		osDelay(500);
		lcd_print(gSenseObj[0].m_l.mean, gSenseObj[1].m_l.mean);
	}
}

#if 0


void machine_status(SENSE_T* pSense, float d){
	DIST_T* pDist = &pSense->d;

	pDist->accl_mean = pDist->velo_mean;
	pDist->velo_mean = pDist->dist_mean;
	pDist->dist_mean = moving_avg(&pSense->m, d);
		
//	if(pDist->dist_mean >= 3.0f && pDist->dist_mean <= 140.0f){	
		pDist->velo_mean = (pDist->dist_mean - pDist->velo_mean) * (1000.0f / DELTA_T);
		pDist->accl_mean = (pDist->velo_mean - pDist->accl_mean) * (1000.0f / DELTA_T);
		if(pSense->echo_pin == echo_Pin){
			printf("%f %f ", d, pDist->dist_mean);
			lcd_print(0, pDist->dist_mean);
		}
		else{
			printf("%f %f\n", d, pDist->dist_mean);
			lcd_print(1, pDist->dist_mean);
		}
		//printf("d : %8.2f, v : %8.2fm/s, a : %8.2fm/s^2\n", pDist->dist_mean, -pDist->velo_mean/100, -pDist->accl_mean/100);
//	}
}



	
void ultrasonic_proc(){
	SENSE_T* pSen;
	DIST_T* pDist;
	float dist;
	
	pSen = p;
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
		dist = (uint16_t)(pSen->cnt[1] - pSen->cnt[0]) / (float)58;
		machine_status(pSen, dist);
		pDist->flag_tx = false;
		
		p = p->pNext;
	}
}

void app_loop(){
	app_init();
	
	while(1){
		ultrasonic_proc();

	}
	
}

#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == p->echo_pin){ //ECHO
		if(HAL_GPIO_ReadPin(p->echo_port, p->echo_pin) == GPIO_PIN_SET){ // rising
			p->cnt[0] = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
			return;
		}
		else { // falling
			p->cnt[1] = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
			return;
		}
	}
	if(GPIO_Pin == GPIO_PIN_13){ //USER_Btn

	}
	
}


int fputc(int ch, FILE *f){
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
	
}
