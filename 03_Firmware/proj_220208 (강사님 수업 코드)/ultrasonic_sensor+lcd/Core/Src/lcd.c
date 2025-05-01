#include <stdio.h>
#include <string.h>
#include "i2c_HD44780.h"
#include "app.h"

typedef struct {
	uint32_t currTick, prevTick;
//	float dist;
} LCD_T;


LCD_T gLcdObj;

void lcd_initialize(void)
{
	lcd_init();
	lcd_disp_on();
	lcd_clear_display();
	lcd_home();
	gLcdObj.prevTick = gLcdObj.currTick = HAL_GetTick();
}	

char str[20];
void lcd_displaying(float dist)
{
	gLcdObj.currTick = HAL_GetTick();
	if (gLcdObj.currTick - gLcdObj.prevTick > 100) { //300ms
		lcd_locate(1,1);
		sprintf(str, "%5.2f", dist);
		lcd_print_string(str);
		gLcdObj.prevTick = gLcdObj.currTick;
		
	}
}
