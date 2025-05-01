#include "uart.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

RX_BUF_T rxBuf[D_UART_MAX] = {
	{ .idx = 0,  .flag = false },
	{ .idx = 0,  .flag = false }
};

void uart_init(void)
{
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&(rxBuf[0].data), 1);	
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&(rxBuf[1].data), 1);	
}

void uart_loop(void)
{
	if (rxBuf[0].flag == true) {
		if (rxBuf[0].cbf != NULL) rxBuf[0].cbf((uint8_t *)rxBuf[0].buf, strlen((const char *)rxBuf[0].buf));
		rxBuf[0].flag = false;
	}
	
	if (rxBuf[1].flag == true) {
		if (rxBuf[1].cbf != NULL) rxBuf[1].cbf((uint8_t *)rxBuf[1].buf, strlen((const char *)rxBuf[1].buf));
		rxBuf[1].flag = false;
	}
}

bool uart_cbf_reg(uint8_t idx, CBF_T cbf)
{
	if (idx > D_UART_MAX) return false;
	rxBuf[idx].cbf = cbf;
	return true;
}

void uart_2_test(uint8_t *str, uint32_t len)
{
	char buf[50];
	sprintf(buf, "%s:%d\n", str, len);
	HAL_UART_Transmit(&huart2, (uint8_t *)buf, strlen(buf), 100);
}
	

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart2) {
		if (rxBuf[0].flag == false) {
			rxBuf[0].buf[rxBuf[0].idx++] = rxBuf[0].data;
			rxBuf[0].idx %= 50;
		
			if (rxBuf[0].data == '\r' || rxBuf[0].data == '\n') {
				rxBuf[0].buf[rxBuf[0].idx++] = 0; // null 문자 추가
				rxBuf[0].idx = 0;
				rxBuf[0].flag = true;
			}
		}

		HAL_UART_Receive_IT(&huart2, (uint8_t *)&(rxBuf[0].data), 1);
	
	} else 	if (huart == & huart3) {
		if (rxBuf[1].flag == false) {
			rxBuf[1].buf[rxBuf[1].idx++] = rxBuf[1].data;
			rxBuf[1].idx %= 50;
		
			if (rxBuf[1].data == '\r' || rxBuf[1].data == '\n') {
				rxBuf[1].buf[rxBuf[1].idx++] = 0; // null 문자 추가
				rxBuf[1].idx = 0;
				rxBuf[1].flag = true;
			}
		}
		
		HAL_UART_Receive_IT(&huart3, (uint8_t *)&(rxBuf[1].data), 1);		
	}
}


int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);

//	while (txcplt_flag != true);
//	txcplt_flag = false;
//	
	return ch;
}
