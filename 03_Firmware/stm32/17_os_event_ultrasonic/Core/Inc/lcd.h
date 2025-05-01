#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "app.h"
#include "main.h"
#include "i2c_HD44780.h"
#include "moving_average.h"

#ifdef __cplusplus
extern "C" {
#endif

void lcd_initial(void);
void lcd_print(float, float);
//void lcd_print(MOV_AVG_T*, float);
#ifdef __cplusplus
}
#endif

#endif // __LCD_H__
