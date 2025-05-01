#include "led.h"
#include "app.h"

static void app_init(void);

static void app_drive(void *pArg)
{
	LED_T *pLed = (LED_T *)pArg; 
	
	HAL_GPIO_TogglePin(pLed->port, pLed->pin);	
}

void app_loop(void)
{
	app_init();	
	
  while (1) { 
		led_thread();
//		btn_thread();
  }	
}

static void app_init(void)
{
	led_init();
//	led_reg_cbf(0, app_drive);
	led_reg_cbf(1, app_drive);
	led_reg_cbf(2, app_drive);
	
//	btn_init();
}
