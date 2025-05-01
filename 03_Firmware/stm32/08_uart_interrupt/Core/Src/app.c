// app.c
// uart_interrupt

#include "app.h"
#include "ring.h"
#include "cli.h"
#include "uart.h"

static void app_print(uint8_t *, uint32_t);

static void app_parser(uint8_t *, uint32_t);

void app_init(void)
{
	printf("System start...!!\n");
	
	uart_cbf_reg(0, app_print);
	uart_cbf_reg(1, app_parser);
}

void app_main(void)
{
	app_init();
	
	uart_init();
	
	while (1) {
		uart_loop();
	}
	//ring_g_test();'
}
static void app_print(uint8_t *str, uint32_t len)
{
	printf("%s", (char *)str);
}


static void app_parser(uint8_t *str, uint32_t len)
{
	cli_parser((char *)str);
}

