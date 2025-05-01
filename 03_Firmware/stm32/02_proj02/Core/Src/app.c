// app.c

#include "led.h"
#include "app.h"

// === �Լ� ����� ===
static void app_init(void);

static void app_drive(void *pArg) {
	LED_T *pLed = (LED_T *)pArg;
	
	HAL_GPIO_TogglePin(pLed->port, pLed->pin);
}

/*
LED_T gLed[D_LED_MAX] = {
	{0, 100, LD1_GPIO_Port, LD1_Pin},
	{0, 500, LD2_GPIO_Port, LD2_Pin},
	{0, 730, LD3_GPIO_Port, LD3_Pin}
};
*/

/*
void thread_Led(LED_T *pLed) { 
	uint32_t tickcurr = HAL_GetTick();
	
	if ((tickcurr - pLed->tickstart) > pLed->wait) {
		pLed->tickstart = tickcurr;
		HAL_GPIO_TogglePin(pLed->port, pLed->pin);
	}
}
*/


/*
void app_Handler(uint32_t type, void* pArg) {
	switch(type) {
		case E_LED: {
			LED_T *pLed = (LED_T *)pArg;
			thread_Led(pLed);
		} break;
		
		case E_XXX: {
		} break;
		
		default: {
		}
	}
}
*/


// === �Լ� ���Ǻ� ===
// ���� ����
void app_loop(void) {
	app_init();
	
	//int i;
	while(1) {
		led_thread();
		//btn_thread();
	//for(i = 0; i < D_LED_MAX; i++) {
	//	app_Handler(E_LED, &gLed[i]);
	//}
	}
}

// app.c ���� �ȿ����� ����
// static Ű���� : ���� �ۿ��� ȣ������ �ʵ��� ���
static void app_init(void) {
	led_init();
	led_reg_cbf(0, app_drive);
	led_reg_cbf(1, app_drive);
	led_reg_cbf(2, app_drive);
	
	//btn_init();
	
	/*
	int i;
	
	// �ʱ�ȭ
	for (i = 0; i < D_LED_MAX; i++) {
		// 1
		//if ((HAL_GetTick() - gLed[i].tickstart) >= gLed[i].wait) {
		//	gLed[i].tickstart = HAL_GetTick();
		//	HAL_GPIO_TogglePin (gLed[i].port, gLed[i].pin);
		//}
		
		// 2
		//thread_Led(&gLed[i]);
		
		// 3
		app_Handler(E_LED, (void*)&gLed[i]);
	} 
	*/
}
