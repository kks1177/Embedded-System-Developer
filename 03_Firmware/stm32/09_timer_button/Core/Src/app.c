// app.c
// 09_timer_button			// 초음파 거리 측정

#include "app.h"
#define DEL_T 10
#define MOV_LEN 20

extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

uint16_t curTick, preTick;

volatile bool flag_tick = false;
volatile bool flag_button = false;
volatile bool flag_echo = false;

uint16_t counter[2];

void trigger_ultrasonic(void)
{
   static uint8_t state = 0;
   
   
   if(state == 2) state = 0;
   
   switch (state) {
      case 0 : {
         preTick = curTick = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
         HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET); //pin2 = trig?
         state++;
      } break;
      
      case 1 : {
         curTick = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
         if ((uint16_t)(preTick - curTick) > 30) {
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
            state++;
         } 
      } break;
      
      defalut : {
      } break;
   }   
}

void delay_us(uint32_t us){
      __HAL_TIM_SET_COUNTER(&htim14, 0);
   while(__HAL_TIM_GET_COUNTER(&htim14) < us)
   {
   }
}

void delay_ms(uint32_t ms){
   
    uint8_t count = 0;
   while(count < ms){
      delay_us(1000);
      count++;
   }
}

float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, int nextNum);

typedef struct{
   

   int pos;
   float arrNumbers[MOV_LEN];
   float newAvg;
   float newAvg_bf;
   float sum;
   //int len = sizeof(arrNumbers) / sizeof(int);
   int len;
   
   
}AVG_T;

AVG_T AVG_O = {.pos = 0, .newAvg = 0, .newAvg_bf = 0, .sum = 0};

void app_main(void)
{
   
   for (int i = 0; i < MOV_LEN ; i++){
      AVG_O.arrNumbers[i] = 0;
   }
   AVG_O.len = sizeof(AVG_O.arrNumbers) / sizeof(int);
   
   HAL_TIM_Base_Start(&htim14);
   // the size of this array represents how many numbers will be used
  // to calculate the average
   
   
   
   while (1) {
      /*
      if (flag_button == true) {
         flag_button = false;
         flag_tick = true;
         
         //trigger_ultrasonic();
      }
      */
      HAL_Delay(DEL_T);
      trigger_ultrasonic();

      
      if (flag_echo == true) {
         //거리 계산식.. && 출력
//         printf("counter[0] = %d\n", counter[0]);
//         printf("counter[1] = %d\n", counter[1]);
         volatile float dist;
         uint16_t pulse;
         
         pulse = counter[1]-counter[0];
         //Distance in cm = echo pulse width in uS/58 
         
         /*
         if (pulse > 150 )
         {
         HAL_GPIO_WritePin(GPIOG,GPIO_Pin_13);//ultra sonic sensor activate 
         value[10]=HAL_GPIO_ReadPin(GPIOG, GPIO_Pin_3);//ultra sonic sensor value input 
         }
         */
         dist = (float)pulse / 58.0f;
         AVG_O.newAvg = movingAvg(AVG_O.arrNumbers, &AVG_O.sum, AVG_O.pos, AVG_O.len, dist);
         float acc = (AVG_O.newAvg - AVG_O.newAvg_bf)/DEL_T/DEL_T*1000000/100;
         if (pulse < 4500) {
            printf("time = %d, dist = %f newavg = %f acc : %f\n", pulse, dist, AVG_O.newAvg, acc);
            AVG_O.pos++;
            if (AVG_O.pos >= AVG_O.len){
            AVG_O.pos = 0;
            }
         } else {
            printf("Out of range!\n");
         }
         //printf("d=%f\n", (float)((uint16_t)((uint16_t)counter[1]-(uint16_t)counter[0]))/58.0f);
         
         if( acc > 1){
            HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 1);
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 0);
         }
         else if( acc < -1){
            HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 0);
         }
         else if( acc > -1 && acc < 1){
            HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
            HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 1);
         }
         flag_echo = false;
         
         AVG_O.newAvg_bf = AVG_O.newAvg;
         
         // a sample array of numbers. The represent "readings" from a sensor over time
         }
         
         
         
         
   }
   
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if (GPIO_Pin == GPIO_PIN_3) {  // ECHO
      if (flag_echo == false) {
         if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) { // rising
            counter[0] = __HAL_TIM_GET_COUNTER(&htim14); //htim14.Instance->CNT;
         } else { // falling
            counter[1] = __HAL_TIM_GET_COUNTER(&htim14);
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

float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, int nextNum)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
  //Assign the nextNum to the position in the array
  ptrArrNumbers[pos] = nextNum;
  //return the average
  return *ptrSum / len;
}





/*
#include "app.h"

#define D_PULSE_ON()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET)
#define D_FULSE_OFF()		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET)
#define D_GET_CNT()			(uint16_t)__HAL_TIM_GET_COUNTER(&htim14)

#define D_ULTRA_RANGE		4500		// micro-second
#define D_ULTRA_PULSE		30			// micro-second


// ========== 전역 변수부 ==========
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

bool flag_tick = false;
bool flag_button = false;
bool flag_echo = false;

uint8_t state = 0;
uint16_t curTick, preTick;
uint16_t counter[2];
volatile uint32_t curTickMs, preTickMs;


// ========== 함수 선언부 ==========
void app_init(void);
void trigger_ultrasonic(void);


// 거리 측정 자동화
///*
// ========== 메인 함수 ==========
void app_main(void)
{
	app_init();
   
  HAL_TIM_Base_Start(&htim14);
   
  preTickMs = curTickMs = HAL_GetTick();

  while(1) {
     if (flag_button == true) {
        flag_button = false;
        flag_tick = true;
     }
      
     trigger_ultrasonic();
      
     curTickMs = HAL_GetTick();
     if (curTickMs - preTickMs > 150) { // Milli-Second
        if (flag_tick == false) {
           flag_tick = true;
        }
        preTickMs = curTickMs;
     }
      
     if (flag_echo == true) {
        // 거리 계산식, 출력
        //printf("counter[0] = %d \n", counter[0]);
        //printf("counter[1] = %d \n", counter[1]);
         
        volatile float distance;
        static float predis = 0.0;
        static float v, prev=0.0, a;    // 속도
        uint16_t pulse;         				// 펄스
         
        pulse = counter[1] - counter[0];
        distance = (float)pulse / 58.0f;	// 거리
        v = (distance-predis) / 0.15;			// 속도
        predis = distance;
        a = (v-prev) / 0.15;
        prev = v;
			 
                  
         
        if (pulse < D_ULTRA_RANGE) {      // D_ULTRA_RANGE : 4500
           printf("time = %d, dist = %f, v =%f, a =%f\n", pulse, distance, v, a);
        } 
        else {
           printf("Out of range!\n");
        }
        //printf("%f \n", (float)(counter[1]-counter[0] / 58.0f));
        flag_echo = false;
     }
  }
}


// ========== 함수 정의부 ==========
void app_init(void){
	printf("System start\n");
	HAL_TIM_Base_Start(&htim14);
}

void trigger_ultrasonic(void) {
	//static uint8_t state = 0;
	
	if (flag_tick == true) {
		flag_tick = false;
		state = 0;
	}
	
	switch (state) {
		case 0: {
			preTick = curTick = (uint16_t)D_GET_CNT();
			D_PULSE_ON();
			state++;
		} break;
		case 1: {
			curTick = (uint16_t)D_GET_CNT();
			if ((uint16_t)(preTick - curTick) > D_ULTRA_PULSE) {		// D_ULTRA_PULSE : 30
				D_FULSE_OFF();
				state++;
			}
		} break;
		default: {
		} break;
	} 
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_3) {			// ECHO
		if (flag_echo == false) {
			if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) {		// rising
				counter[0] = D_GET_CNT(); 	//htim14.Instance->CNT;
			} 
			else {		// falling
				counter[1] = D_GET_CNT();
				flag_echo = true;
			}
		}
	}
	else if (GPIO_Pin == GPIO_PIN_13) {		// User Button
		//flag_button = true;
		if (state == 0){
			counter[0] = D_GET_CNT(); //htim14.Instance->CNT;
			state++;
		}
		else if(state == 1){
			counter[1] = D_GET_CNT();
			state++;
		}
	}
}

int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
//*/
*/






// 유저 버튼 누를 때 초음파 거리 측정
/*
// ========== 메인 함수 ==========
void app_main(void)
{
	app_init();
	
	HAL_TIM_Base_Start(&htim14);
	
	while(1) {
		if (flag_button == true) {
			flag_button = false;
			flag_tick = true;
		}
		trigger_ultrasonic();
		
		if (flag_echo == true) {
			// 거리 계산식, 출력
			//printf("counter[0] = %d \n", counter[0]);
			//printf("counter[1] = %d \n", counter[1]);
			
			volatile float distance;		// 거리
			uint16_t pulse;							// 펄스
			
			pulse = counter[1] - counter[0];
			distance = (float)pulse / 58.0f;
			
			if (pulse < D_ULTRA_RANGE) {		// D_ULTRA_RANGE : 4500
				printf("time = %d, dist = %f\n", pulse, distance);
			} 
			else {
				printf("Out of range!\n");
			}
			//printf("%f \n", (float)(counter[1]-counter[0] / 58.0f));
			flag_echo = false;
		}
	}
}


// ========== 함수 정의부 ==========
void app_init(void){
	printf("System start\n");
	HAL_TIM_Base_Start(&htim14);
}

void trigger_ultrasonic(void) {
	static uint8_t state = 0;
	
	if (flag_tick == true) {
		flag_tick = false;
		state = 0;
	}
	
	switch (state) {
		case 0: {
			preTick = curTick = (uint16_t)D_GET_CNT();
			D_PULSE_ON();
			state++;
		} break;
		case 1: {
			curTick = (uint16_t)D_GET_CNT();
			if ((uint16_t)(preTick - curTick) > D_ULTRA_PULSE) {		// D_ULTRA_PULSE : 30
				D_FULSE_OFF();
				state++;
			}
		} break;
		default: {
		} break;
	} 
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_3) {		// ECHO
		if (flag_echo == false) {
			if (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == GPIO_PIN_SET) {		// rising
				counter[0] = D_GET_CNT(); //htim14.Instance->CNT;
			} 
			else {		// falling
				counter[1] = D_GET_CNT();
				flag_echo = true;
			}
		}
	}
	else if (GPIO_Pin == GPIO_PIN_13) {		// User Button
		flag_button = true;
//		if (state == 0) { 
//			counter[0] = __HAL_TIM_GET_COUNTER(&htim14); //htim14.Instance->CNT;
//			state++;
//		}
//		else if (state == 1) {
//			counter[1] = __HAL_TIM_GET_COUNTER(&htim14);
//			state++;
//		}
	}
}

int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}
*/