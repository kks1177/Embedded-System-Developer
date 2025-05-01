// led.h

#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define D_LED_MAX 3

typedef void (*CBF_T)(void *arg);		// 포인터를 typedef

typedef struct {
	uint32_t tickstart;
	uint32_t wait;
	GPIO_TypeDef *port;
	uint16_t pin;
	CBF_T cbf;
} LED_T;

void led_init(void);
bool led_reg_cbf(uint32_t idx, CBF_T cbf);
void led_set_wait(LED_T *p, uint32_t wait);
void led_thread(void);

#ifdef __cplusplus
}
#endif

#endif // __LED_H__
