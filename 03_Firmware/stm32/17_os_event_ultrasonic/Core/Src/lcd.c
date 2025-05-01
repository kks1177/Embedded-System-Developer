#include "lcd.h"

#define STR_SIZE 10

void lcd_initial(void){
	lcd_init();
	lcd_disp_on();
	lcd_clear_display();
	lcd_home();
}

static char str_buf[2][STR_SIZE] = { "dist1:", "dist2:" };
static char val_buf[20];

void lcd_print(float d1, float d2){
	if(d1 >= 3.0f && d1 <= 130.0f){
		lcd_clear_display();
		lcd_locate(1,1);
		sprintf(val_buf, "%s%7.2f", str_buf[0], d1);
		lcd_print_string(val_buf);
	}
	else{
		lcd_clear_display();
		lcd_locate(1,1);
		sprintf(val_buf, "%s Range Out", str_buf[0]);
		lcd_print_string(val_buf);
	}
	
	if(d2 >= 3.0f && d2 <= 130.0f){
		lcd_locate(2,1);
		sprintf(val_buf, "%s%7.2f", str_buf[1], d2);
		lcd_print_string(val_buf);
	}
	else{
		lcd_locate(2,1);
		sprintf(val_buf, "%s Range Out", str_buf[1]);
		lcd_print_string(val_buf);
	}
}

