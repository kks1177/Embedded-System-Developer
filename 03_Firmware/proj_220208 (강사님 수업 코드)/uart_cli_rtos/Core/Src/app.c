#include "cmsis_os2.h"
#include "cli.h"
#include "uart.h"
#include "app.h"

#define MSG_Q_OBJS_MAX	10



APP_T gAppObj;


void app_task(void *arg)
{
	osStatus_t sts;
	MSG_T rxMsg;
	
	uart_init();
	
	printf("System start....\n");
	
	while (1) {
		sts = osMessageQueueGet(gAppObj.q_id, &rxMsg, NULL, osWaitForever);
		if (sts == osOK) {
			switch (rxMsg.type) {
				case MSG_UART_RX_E : {
					cli_parser((char *)rxMsg.data);
				} break;
				
				case MSG_UART_TX_E : {
					printf("rx[%d]%s\n", rxMsg.len, rxMsg.data);
				} break;
			}
		}
	}
}

const osThreadAttr_t app_task_attributes = {
  .name = "app_Task",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void app_init(void)
{
	osKernelInitialize();

	osThreadNew(app_task, NULL, &app_task_attributes);
	gAppObj.q_id = osMessageQueueNew(MSG_Q_OBJS_MAX, sizeof(MSG_T), NULL);
	
	osKernelStart();
}

void app_main(void)
{
	app_init();
}

