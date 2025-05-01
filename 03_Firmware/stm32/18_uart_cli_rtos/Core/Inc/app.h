#ifndef __APP_H
#define __APP_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cmsis_os2.h"
#include "main.h"

enum {
	MSG_UART_TX_E,
	MSG_UART_RX_E,
};

typedef struct {
	uint8_t type;
	uint8_t len;
	uint8_t data[50];
} MSG_T;

typedef struct {
	osMessageQueueId_t q_id;
} APP_T;

extern APP_T gAppObj;
#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);

#ifdef __cplusplus
}
#endif

#endif  // __APP_H
