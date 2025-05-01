// app.h

#ifndef __APP_H__
#define __APP_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
enum {
	E_LED = 0x100,
	E_LED_1,
	E_LED_2,
	E_LED_3,
	
	E_XXX = 0x200,
};
*/

/*
#define D_LED_MAX 3

typedef struct {
	uint32_t tickstart;
	uint32_t wait;
	GPIO_TypeDef *port;
	uint16_t pin;
	//void (*cbf)(void * );
} LED_T;
*/

void app_loop(void);

#ifdef __cplusplus
}

#endif

#endif // __APP_H__

