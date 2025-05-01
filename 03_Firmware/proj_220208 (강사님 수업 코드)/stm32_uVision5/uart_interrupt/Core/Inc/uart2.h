#ifndef __UART_H
#define __UART_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define D_UART_MAX			2
#define D_UART_BUF_MAX	50

typedef void (*CBF_T)(uint8_t *, uint32_t);

typedef struct {
	volatile uint8_t data;

	volatile uint8_t buf[D_UART_BUF_MAX];
	volatile uint8_t idx;
	volatile bool flag;
	CBF_T cbf;
} RX_BUF_T;

void uart_init(void);
void uart_loop(void);
void uart_2_test(uint8_t *str, uint32_t len);
bool uart_cbf_reg(uint8_t idx, CBF_T cbf);
	
#ifdef __cplusplus
}
#endif

#endif //__UART_H
