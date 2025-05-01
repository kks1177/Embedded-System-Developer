// led.h

#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void led_onoff(uint32_t no, bool on);

#ifdef __cplusplus
}
#endif

#endif // __LED_H__
