// app.c
// 14_character_lcd

#include <string.h>
#include "i2c_HD44780.h"
#include "app.h"

void app_main(void) 
{
	char buf[17];
	uint8_t i = 0;
	
	lcd_init();
	lcd_disp_on();
	lcd_clear_display();
	lcd_home();
	//lcd_print_string("Hello");
	
	while(1){
		sprintf(buf, "%6d", i++);
		lcd_locate(1,1);
		lcd_print_string(buf);
		i %= 101;
		
		HAL_Delay(500);
	}
}
