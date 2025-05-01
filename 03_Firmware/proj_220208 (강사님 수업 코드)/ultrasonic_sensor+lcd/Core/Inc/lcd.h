#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void lcd_initialize(void);
void lcd_displaying(float dist);

#ifdef __cplusplus
}
#endif

#endif  // __LCD_H
