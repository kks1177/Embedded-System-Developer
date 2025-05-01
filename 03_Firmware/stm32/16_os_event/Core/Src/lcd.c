#include "lcd.h"

#define STR_SIZE 10

static MOV_AVG_T m_lcd[2];

void lcd_initial(void){
	lcd_init();
	lcd_disp_on();
	lcd_clear_display();
	lcd_home();
}
static char str_buf[2][STR_SIZE] = { "dist1:", "dist2:" };
static char val_buf[20];

void lcd_print(int pin, float dist){
	static uint32_t prev_tick = 0, curr_tick;
	curr_tick = HAL_GetTick();
	moving_avg(&m_lcd[pin], dist);
	
	if(curr_tick - prev_tick > 500){
		if(m_lcd[0].mean >= 3.0f && m_lcd[0].mean <= 130.0f){
			lcd_clear_display();
			lcd_locate(1,1);
			sprintf(val_buf, "%s%7.2f", str_buf[0], m_lcd[0].mean);
			lcd_print_string(val_buf);
		}
		else{
			lcd_clear_display();
			lcd_locate(1,1);
			sprintf(val_buf, "%s Range Out", str_buf[0]);
			lcd_print_string(val_buf);
		}
		
		if(m_lcd[1].mean >= 3.0f && m_lcd[1].mean <= 130.0f){
			lcd_locate(2,1);
			sprintf(val_buf, "%s%7.2f", str_buf[1], m_lcd[1].mean);
			lcd_print_string(val_buf);
		}
		else{
			lcd_locate(2,1);
			sprintf(val_buf, "%s Range Out", str_buf[1]);
			lcd_print_string(val_buf);
		}
		
		prev_tick = curr_tick;
	}
}

