// CLI
// app.c

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "app.h"

typedef struct {
	uint32_t prevTick, currTick;
	uint32_t count;
	bool flag;
	uint16_t pin;
	uint16_t wait;
	void (*cbf)(void);		// cbf : call back function
} BTN_T;

void USER_Btn_callBack(void); 
void USER_Btn_callBack2(void); 
void Ext_Btn_callBack(void); 

static BTN_T gBtnObj[] = {
	{ 0, 0, 0, false, USER_Btn_Pin, 150, USER_Btn_callBack }, 
	{ 0, 0, 0, false, EXT_Btn_Pin,	100, Ext_Btn_callBack  },
  { 0, 0, 0, false, 0,						0,	 NULL							 }
};

void USER_Btn_callBack(void) {
	printf("USER button Pushed 1...\n");
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	gBtnObj[0].cbf = USER_Btn_callBack2;
}
void USER_Btn_callBack2(void) {
	printf("USER button Pushed 2...\n");
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	gBtnObj[0].cbf = USER_Btn_callBack;
}

void Ext_Btn_callBack(void) {
	printf("Ext button Pushed...\n");
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}

void app_init(void) {
	printf("System start....\n");
}


void app_loop(void) 
{
	//uint32_t localCount = 0;
	
	app_init();
	
	while (1) {
		for (int i=0; gBtnObj[i].wait != 0; i++) {
			if (gBtnObj[i].flag == true) {
				gBtnObj[i].flag = false;
				gBtnObj[i].cbf(); 
				//gBtnObj[i].cbf = app_init;
				//printf("Button Pushed : %d/%d/%d\n", i, gBtnObj[i].count, localCount++);
				gBtnObj[i].count = 0;
			}
		}	
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	BTN_T *p = gBtnObj;
	
	for (int i=0; p[i].wait != 0; i++) {
		if (GPIO_Pin == p[i].pin) {
			p[i].currTick = HAL_GetTick();
			
			if (p[i].currTick - p[i].prevTick > p[i].wait) {
				p[i].prevTick = p[i].currTick;
				p[i].count++;
				p[i].flag = true;
			}
		} 
	}
}

extern UART_HandleTypeDef huart3;
int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
	return ch;
}

