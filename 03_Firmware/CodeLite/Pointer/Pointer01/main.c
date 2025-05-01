#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_value(uint8_t *pStr, uint32_t len) {
    uint32_t i;
    
    if (pStr == NULL || len == 0) return;
    
    for (i=0; i<len; i++) {
        printf("%02x ", pStr[i]);
    }
    printf("\n");
}

//typedef struct __attribute__((packed)) {
typedef struct {
    uint32_t tickstart;
    uint16_t pin;
    uint16_t pin2;
} PACKET_T;

uint8_t buf[100];

int main(int argc, char **argv)
{
    uint32_t tickstart = 0x12345678;
    uint16_t pin = 0x9abc;
    
    memset(buf, 0, sizeof(buf));
    
    // 1. 직관적인 방법
    buf[0] = (uint8_t)tickstart;
    buf[1] = (uint8_t)(tickstart >> 8);
    buf[2] = (uint8_t)(tickstart >> 16);
    buf[3] = (uint8_t)(tickstart >> 24);
    buf[4] = (uint8_t)pin;
    buf[5] = (uint8_t)(pin >> 8);
    
    print_value(buf, 6);
    memset(buf, 0, sizeof(buf));

    // 2. 구조체 사용, 포인터 사용x
    uint32_t *p0;
    p0 = (uint32_t *)&buf[0];
    *p0 = tickstart;
    
    uint16_t *p1;
    p1 = (uint16_t*)&buf[4];
    *p1 = pin;
    
    print_value(buf, 6);
    memset(buf, 0, sizeof(buf));

    // 3. 구조체 사용, 포인터 사용                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    PACKET_T *pPkt;
    
    pPkt = (PACKET_T *)&buf[0];
    
    pPkt->tickstart = tickstart;
    pPkt->pin = pin;
    //pPkt->pin2 = pin+1;
    
    print_value(buf, sizeof(PACKET_T));
    
	return 0;
}
