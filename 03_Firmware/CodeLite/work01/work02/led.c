// led.c

#include "led.h"

#define D_LED_MAX   3

//#define D_REAL_BOARD

#if defined(D_REAL_BOARD)
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} LED_T;

const LED_T gLed[D_LED_MAX] = {
    {LD1_GPIO_Port, LD1_Pin },
    {LD2_GPIO_Port, LD2_Pin },
    {LD3_GPIO_Port, LD3_Pin },
};

void led_onoff(uint8_t idx, bool onoff)
{
    LED_T *p;
    if (idx < D_LED_MAX) {
        p = &gLedObj[i];
        if (onoff == true) {
            HAL_GPIO_WritePin(p->port, p->pin, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(p->port, p->pin, GPIO_PIN_RESET);
        }
    }
}
#else // D_REAL_BOARD
void led_onoff(uint8_t idx, bool onoff)
{
   if (idx < D_LED_MAX) {
       if (onoff == true) {
            printf("LD%d on\n", idx);
       } else {
            printf("LD%d off\n", idx);
       } 
   } else {
        printf("Invalid parameter...\n");
   }
}

#endif 
