#ifndef __LED_H__
#define __LED_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void led_onoff(uint8_t idx, bool onoff);

#ifdef __cplusplus
}
#endif

#endif // __LED_H__

