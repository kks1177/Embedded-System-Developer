#include "led.h"

#define D_WAIT_MIN		10

static LED_T gLed[D_LED_MAX] = {
   { 0, 10, LD1_GPIO_Port, LD1_Pin, NULL },
   { 0, 50, LD2_GPIO_Port, LD2_Pin, NULL },
   { 0, 73, LD3_GPIO_Port, LD3_Pin, NULL },
};

static void led_drive(LED_T *pLed); 

void led_thread(void)
{
	int i;
	
	for (i=0; i<D_LED_MAX; i++) {
		led_drive(&gLed[i]);
	}
}

//bool led_reg_cbf(uint32_t idx, void (*cbf)(void *arg))


bool led_reg_cbf(uint32_t idx, CBF_T cbf)
{
	if (idx < D_LED_MAX) {
		gLed[idx].cbf = cbf;
		return true;
	}
	
	return false;
}

void led_set_wait(LED_T *p, uint32_t wait)
{
	if (p != NULL && wait > D_WAIT_MIN) {
		p->wait = wait;
	}
}

void led_init(void)
{
	int i;

	for (i=0; i<D_LED_MAX; i++) {
		gLed[i].tickstart = HAL_GetTick();
	}
}

static void led_drive(LED_T *pLed) 
{
	uint32_t tickcurr = HAL_GetTick();
	
	if (tickcurr - pLed->tickstart > pLed->wait) {
		pLed->tickstart = tickcurr;
		//HAL_GPIO_TogglePin(pLed->port, pLed->pin);
		if (pLed->cbf != NULL) pLed->cbf((void *)pLed);
	}
}	
