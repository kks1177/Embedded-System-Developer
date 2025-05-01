// app.c
// exti_ext_btn

//#include "app.h"

//typedef struct {
//	
//} AA;

//typedef union {
//	
//} BB;

//void init(void) 
//{
//	printf("System Start \n");
//}

//void app_main(void)
//{
//	void init();
//	
//	while (1) {
//		
//	}
//}

//int fputc(int ch, FILE *f)
//{
//	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
//	
//	return ch;
//}





///*
#include "app.h"

/*
//// ��Ʈ ��ũ��
//#define SET_VAL(var, val, bits, pos)	\
//do { \
//	var &= (~(bits << pos));	\
//	var |= ((val & bits) << pos);	\
//}	while (0)

#include <stdio.h>
#include <stdint.h>
void SET_VAL(uint16_t var, uint8_t val, uint8_t bits, uint8_t pos){
    var &= (~(bits << pos));
		var |= ((val&bits) << pos);
    printf(" val : %x\n", var);
}

int main(int argc, char **argv)
{
    uint16_t var = 0x4864;
    uint8_t val = 0x11;
    uint8_t bits = 0xFF;
    uint8_t pos = 4;
    
    SET_VAL(var, val, bits, pos);
    
   return 0;
}
*/


//extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;

bool flag_btn[2] = {false, false};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == USER_Btn_Pin) {
		flag_btn[0] = true;
	} else if (GPIO_Pin == EXT_Btn_Pin) {
		flag_btn[1] = true;
	}
}

void app_init(void)
{
	printf("System start \n");
}

typedef struct {
	uint32_t q1 : 5;
	uint32_t q2 : 5;
	uint32_t q3 : 5;
	uint32_t q4 : 5;
	uint32_t jl : 2;
} ADC_JSQ_T;

typedef union {
	uint32_t reg;
	ADC_JSQ_T bit;
} ADC_JSQ_U;

// Bit-Field ��ũ��
#define SET_VAL(var, val, bits, pos)	\
do { \
	printf("var1 = %04x \n", x);	\
\
	var &= (~(bits << pos));	\
	var |= ((val & bits) << pos);	\
\
	printf("var2 = %04x \n\n", var);	\
} while (0);	\

#define GET_VAL(var, bits, pos) ((var >> pos) & bits)

void app_loop(void)
{
	app_init(); 
	
	uint16_t x = 0x1234;
	
	SET_VAL(x, 0xFF, 0xFF, 4);
	SET_VAL(x, 0x1, 0x1, 0);
	SET_VAL(x, 0x12344, 0x1, 0);
	
	printf("var3 = %x \n", GET_VAL(x, 0xF, 12));
	
//	ADC_JSQ_T xx = {0, 1, 2, 3, 2};
//	
//	printf("sizeof = %d \n", sizeof(ADC_JSQ_T));
//	
//	printf("%x, %x, %x, %x, %x \n", xx.q1, xx.q2, xx.q3, xx.q4, xx.jl);
//	
//	xx.q1 = 0x1f;
//	printf("%x, %x, %x, %x, %x \n", xx.q1, xx.q2, xx.q3, xx.q4, xx.jl);
	
	/*
	ADC_JSQ_U x2;
	
	x2.bit.q1 = 0x02;
	x2.bit.q2 = 0x03;
	x2.bit.q3 = 0x04;
	x2.bit.q4 = 0x05;
	x2.bit.jl = 0x01;
	
	for (uint8_t i = 0; i < 32; i++) {
		if (x2.reg & (0x80000000 >> i)) printf("1");
		else printf("0");
	}
	printf("\n");
	
	x2.reg = 0x12345678;
	
	for (uint8_t i = 0; i < 32; i++) {
		if (x2.reg & (0x80000000 >> i)) printf("1");
		else printf("0");
	}
	printf("\n");
	
	x2.bit.q1 = 0x07;
	
	for (uint8_t i = 0; i < 32; i++) {
		if (x2.reg & (0x80000000 >> i)) printf("1");
		else printf("0");
	}
	printf("\n");
	*/
	
	/*
	uint8_t p1, p2, p3;
	
	p1 = -125;
	p2 = -5;
	
	printf("[p1][p2] : %x %x \n", p1, p2);	// 83 fb
	
	printf("[p1+p2] = %x \n", (uint8_t)p1+(uint8_t)p2);		// 17e
	printf("[p1+p2] = %x \n", (uint8_t)p1+p2);						// 17e
	printf("[p1+p2] = %x \n", (uint8_t)(p1+p2));					// 7e
	
	p3 = p1+p2;
	printf("[p3] = %x \n", p3);														// 7e
	
	p3 &= ~(1 << 4);
	printf("[p3] = %x:", p3);															// 6e:
	
	for(uint8_t i = 0; i < 8; i++) {
		if (p3 & (0x80 >> i)) printf("1");									// 01101110
		else printf("0");
	}
	printf("\n");
	*/
	
	while (1) {
		if (flag_btn[0] == true) {
			flag_btn[0] = false;
			printf("Button 0 pushed.. \r\n");
		}
		if (flag_btn[1] == true) {
			flag_btn[1] = false;
			printf("Button 1 pushed.. \r\n");
		}
	}
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	
	return ch;
}
//*/






/*
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "app.h"

void USER_Btn_callBack();
void Ext_Btn_callBack();

//#define GET_BTN()		HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);

//����ü ����
typedef struct {
   uint32_t prevTick, currTick; //�����ð�, ����ð�
   uint32_t count;							//��ư ���� Ƚ��
   uint8_t flag; 								//����
   uint16_t pin; 								//��. ������ư���� �ܺι�ư����
   uint16_t wait; 							//ä�͸� �����ϱ� ���� ����.
   void (*cbf)(void); 					//�ݹ��Լ� ����.
} BTN_T; 			//����ü �̸� BTN_T

//����ü �迭 ����
static BTN_T gBtnObj[] = {
   {0, 0, 0, false, USER_Btn_Pin, 150, USER_Btn_callBack}, 	//���忡 �ִ� USER��ư�� ������ ��
   {0, 0, 0, false, EXT_Btn_Pin,  100, Ext_Btn_callBack}, 	//�극�庸�忡 ������ ��ư�� ������ ��
   {0, 0, 0, false, 0,            0,   NULL}, 							//�ƹ���ư�� ������ �ʾ��� ��
};

//�����Լ�. ���¹�ư�� ������ ȣ��ȴ�.
void app_init(void)
{
   printf("System start.......\n");
}

void app_loop(void)
{
//   GPIO_PinState pinStsCurr, pinStsPrev;
   //uint32_t localCount = 0;
   
   app_init();
   
//   pinStsCurr = pinStsPrev = GET_BTN();
   
   //�Լ��̸��� �ּ�. �ڵ��� �����ּ�.
	
   while (1) {
      for(int i=0; gBtnObj[i].wait != 0; i++){ 
         if (gBtnObj[i].flag == true) { 	//���ͷ�Ʈ �ݹ��Լ��� ����Ǹ� flag==true �� �Ǳ� ������ true�϶� ����Ǿ���Ѵ�.
            gBtnObj[i].flag = false; 			//�ݹ�Ǿ��⶧���� �ٽ� ���¸� false�� �ٲ���.
            gBtnObj[i].cbf(); 						//callBack
            //printf("Button Pushed : %d/%d/%d\n", i, gBtnObj[i].count, localCount++);
            gBtnObj[i].count = 0;
         }
      }

   
//      HAL_Delay(100);
//      
//      pinStsCurr = HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);
//      
//      //0�� �ƴѰ��̸� ��(True)
//      //rising edge
//      if(pinStsCurr == GPIO_PIN_SET && pinStsPrev == GPIO_PIN_RESET){
//         HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
//         printf("LED on\n");
//         timeCurr = HAL_GetTick();
//         //falling edge (����=high, ����=low)
//      } else if (pinStsCurr == GPIO_PIN_RESET && pinStsPrev == GPIO_PIN_SET) {
//         HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
//         printf("LED off\n");
//         if (HAL_GetTick() - timeCurr > 1000) printf("long key...\n");
//         else printf("short key...\n");
//      }
//      
//      pinStsPrev= pinStsCurr;
      
   }
}

//user��ư �ݹ��Լ�. user��ư�� ������ �� ����.
void USER_Btn_callBack(void){
   printf("USER button Pushed...\n"); //user��ư�� �������� ���. print.
   //led ��»��� ���� ��Ŵ. Write�� SET, RESET���� ���� ���¸� �Է�����ٸ�, toggle �Լ��� ���� ���¸� �Է����� �ʰ�, 
   //������¿� �ݴ�Ǵ� ���·� �ٲ��ش�. high���ٸ� ->low, low���ٸ� ->high
   HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin); 
}
//ext��ư �ݹ��Լ�. ext��ư�� ������ �� ����.
void Ext_Btn_callBack(void){
   printf("Ext button Pushed...\n");
   HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}

//HAL_GetTick���� ��������, ������� �޾ƿ���
//���� tick ���� �а� ������ ����Ǿ� �ִ� ���� ��
//�� ���� ���̰� 150ms�� �Ѵ´ٸ�,
//flag_btn = true�� �����.
//�׸��� ���� tick���� ���� tick���� �����ϰ�
//�Լ��� �������´�.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 		//���ͷ�Ʈ �ݹ� �Լ�. 
{
   BTN_T *p = gBtnObj;		//����ü ������ ���� ����.
   for(int i=0; p[i].wait != 0; i++){
      if(GPIO_Pin == p[i].pin){ 				//user��ư �Ǵ� ext��ư�̸� true. if�� ����.
         p[i].currTick = HAL_GetTick(); //���� �ð� �о����.
         
         if (p[i].currTick - p[i].prevTick > p[i].wait){ 	//����ð��� �����ð��� ���̰� wait���� ��ٸ� true. if�� ����. ä�͸� ����
            p[i].prevTick = p[i].currTick; 								//����ð��� �����ð��� ��. => �����ð��� ����ð� ����.
            p[i].count++; 																//��ư�� ��� ���ȴ��� �˾ƺ��� ���� �ѹ� ���������� count������Ŵ.
            p[i].flag = true; 														//����ǥ��
         }
      }
   }
   
//   if(GPIO_Pin == EXT_Btn_Pin){
//      currTick = HAL_GetTick();
//      
//      if(currTick - prevTick > 150){
//         flag_btn = true;
//         count_btn++;
//         prevTick = currTick;
//      }
//   } else if(GPIO_Pin == USER_Btn_Pin) {
//      
//   }
}

extern UART_HandleTypeDef huart3;

int fputc(int ch, FILE *f)
{
   HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
   return ch;
}
*/






/*
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "app.h"

typedef struct {
   uint32_t prevTick;
   uint32_t currTick;
   uint32_t count;
   bool flag;
   uint16_t pin;
   uint16_t wait;
   void (*cbf)(void);
} BTN_T;

void USER_Btn_callback(void);
void SWITCH_Btn_callback(void);

static BTN_T gBtnObj[] = {
   { 0, 0, 0, false, USER_Btn_Pin,    150,   USER_Btn_callback}, 
   { 0, 0, 0, false, EXT_Btn_Pin,     100,   SWITCH_Btn_callback},
  { 0, 0, 0, false, 0,                     0,      NULL}
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   BTN_T *p = gBtnObj;
   
   for (int i=0; p[i].wait != 0; i++) {
      if (GPIO_Pin == p[i].pin) {
         p[i].currTick = HAL_GetTick();
         
         if (p[i].currTick - p[i].prevTick > p[i].wait) {
            p[i].prevTick = p[i].currTick;
            p[i].flag = true;
         }
      } 
   }
}

void USER_Btn_callback(void) 
{
   printf("USER button Pushed...\n");
}

void SWITCH_Btn_callback(void) 
{
   printf("SWITCH button Pushed...\n");
}

void app_init(void)
{
   printf("System start\n");
}

void app_loop(void)
{
   app_init();
   
   while (1){
      for(int i=0; gBtnObj[i].wait !=0; i++){
         if (gBtnObj[i].flag == true) {
            gBtnObj[i].flag = false;
            gBtnObj[i].cbf(); 
         }
      }
   }
}

extern UART_HandleTypeDef huart3;

int fputc(int ch, FILE *f){
   HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
   return ch;
}
*/
