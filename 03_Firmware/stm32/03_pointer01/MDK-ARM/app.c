// app.c

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "app.h"

static void app_init(void);

uint32_t a[3];

/*
typedef struct {
	uint32_t tickstart, wait;
	GPIO_TypeDef *port;
	uint16_t pin;
	void (*cbf)(void *arg);
} LED_T;
*/

typedef __packed struct {
	uint32_t tickstart, wait;
	GPIO_TypeDef *port;
	uint16_t pin;
	void (*cbf)(void *arg);
} LED_T;

LED_T gLed[3];

void app_loop(void) {
	app_init();
	
	a[0] = 0x12345678;
	a[1] = 0xff00ff00;
	a[2] = 0x00aa00aa;
	
	uint8_t *ptr;			// uint8  : unsigned char
	uint16_t *ptr1;		// uint16 : unsigned short int
	uint32_t *ptr2;		// uint32 : unsigned int
	LED_T *pLed;
	
	printf("size : %d, %d, %d, %d \n", sizeof(ptr), sizeof(ptr1), sizeof(ptr2), sizeof(pLed));
	printf("size : %d, %d, %d, %d, %d, %d \n", sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t), sizeof(float), sizeof(double), sizeof(LED_T));
	
//	// �迭 a�� �̸��� �迭 a�� ��ġ�ϴ� ���� ���� �ּ��̴�.
//	printf("%08x\n", a);
//	// �迭 a�� ù��° �������� �ּҿ� ��
//	printf("[%08x]:0x%08x\n", &a[0], a[0]);
//	// �迭 a�� �ι�° �������� �ּҿ� ��
//	printf("[%08x]:0x%08x\n", &a[0], a[0]);
//	// �迭 a�� ����° �������� �ּҿ� ��
//	printf("[%08x]:0x%08x\n", &a[0], a[0]);
//	
//	// ������ ���� ����, 
//	// ptr �����Ͱ� ����Ű�� ���� ���� ũ�Ⱑ ����Ʈ ����
//	uint8_t *ptr;
//	
//	// ptr ���� �迭 a�� ���� �ּҸ� ����
//	ptr = (uint8_t *)a;
//	// ptr ���� �ڽ��� ��ġ : ptr�� �ּ�
//	printf("addr[ptr] : %08x\n", &ptr);
//	// ptr ������ ��� �ִ� ��
//	printf("ptr : %08x\n", ptr);
//	// ptr ������ ��� �ִ� ���� ����Ű�� ���� ��
//	printf("*ptr : %08x\n", *ptr);
//	
//	*ptr = 0xffffff87;
//	printf("0x%08x:0x%08x:0x%08x\n", a, &a[0], a[0]);
//	*ptr++;
//	ptr++;
//	printf("0x%08x:0x%08x:0x%08x\n", a, &a[0], a[0]);

//	// ptr�� ��ġ : �ڱ� �ڽ��� ��ġ�� �ּ�
//  printf("addr of ptr : %08x\n", &ptr);
//	// ptr�� ��� �ִ� �� : �ٸ� �������� ���� �ּ�
//	printf("value of ptr : %08x\n", ptr);
//	// ptr�� ��� �ִ� ���� ����Ű�� ���� ��
//	printf("*ptr : %08x\n", *ptr);

	for(;;) {
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}

static void app_init(void) {
	printf("System Start...\n");
}

extern UART_HandleTypeDef huart3;
int fputc(int ch, FILE *f) {
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 10);
  return ch;
}
