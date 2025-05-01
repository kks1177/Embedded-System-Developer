#ifndef __I2C_HD44780__H__
#define __I2C_HD44780__H__

#include "main.h"

#ifdef __cpluspluse
extern "C" {
#endif


void lcd_init (void);   // initialize lcd
//void lcd_send_cmd (char cmd);  // send command to the lcd
//void lcd_send_data (char data);  // send data to the lcd
void lcd_disp_on(void);
void lcd_disp_off(void);
void lcd_home(void);
void lcd_clear_display(void);
void lcd_locate(uint8_t row, uint8_t column);
void lcd_printchar(unsigned char ascode);
void lcd_print_string (char *str);  // print string to the lcd
void lcd_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
