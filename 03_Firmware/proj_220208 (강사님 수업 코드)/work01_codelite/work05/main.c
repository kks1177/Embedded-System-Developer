#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

typedef struct { 
    char name[10];// 이름
    char phone[20];// 전화번호
    char address[50];// 주소
    int age;// 나이
    int gender;// 성별
    float height;// 키
    float weight;// 몸무게
} CUSTOMER_T;

CUSTOMER_T gCustObj[3] = {
    { "Donald", "+820134513453",    "Seoul",    20, 1, 170, 60 },
    { "Jade",   "+820134517453",    "Daejon",   21, 0, 165, 55 },
    { "John",   "+820134518453",    "Gongju",   22, 1, 172, 65 },
};

void print_dump(uint8_t *ptr, int len)
{
    int i, j;
        
    if (ptr == NULL || len == 0) return;
    printf("\n");
    for (i=0, j=0; i<len; i+= 16) {
        printf("\n%p : ", ptr+i);
        for (j=0; j<16; j++) {
            printf("%02x ", *(ptr+i+j));
        }
        
        printf("\t");
        for (j=0; j<16; j++) {
            if (isprint(*(ptr+i+j))) {
                printf("%c ", *(ptr+i+j));
            } else {
                printf("  ");
            }
        }
    }    
}
int main(int argc, char **argv)
{

    uint8_t *pData;
    uint8_t temp;
    
    pData = (uint8_t *)&gCustObj[0];
    //pData = (uint8_t *)gCustObj;
    //pData = (uint8_t *)&(gCustObj[0].name[0]);
    //pData = (uint8_t *)(gCustObj[0].name);
    
    print_dump(pData, sizeof(gCustObj)); 
    
    
    pData = (uint8_t *)&(gCustObj[1].phone[1]);
    printf("\n\naddr : %p\n", pData);
    
    temp = pData[1];
    pData[1] = pData[0];
    pData[0] = temp;

    pData = (uint8_t *)gCustObj;

    print_dump(pData, sizeof(gCustObj)); 

	return 0;
}
