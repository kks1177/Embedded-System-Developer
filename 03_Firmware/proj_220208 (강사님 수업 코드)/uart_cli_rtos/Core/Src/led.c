#include <stdio.h>
#include "led.h"

void led_onoff(uint32_t no, bool on)
{
	GPIO_PinState sts;
	
	if (on == true) sts = GPIO_PIN_SET;
	else sts = GPIO_PIN_RESET;
	
	switch (no) {
		case 0 : HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, sts); break;
		case 1 : HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, sts); break;
		case 2 : HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, sts); break;
			
		default : 
			printf("Invalid Parameter...\n");
	}	
}