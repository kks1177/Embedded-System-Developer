#include <stdio.h>
#include <stdint.h>

uint8_t     a[5] = { 1,2,3,4,5};
uint16_t    b[5] = { 0x10,0x20,0x30,0x40,0x50};
uint32_t    c[5] = { 0x100,0x200,0x300,0x400,0x500};
float       d[5] = { 1000,2000,3000,4000,5000};
double      e[5] = { 10000,20000,30000,40000,50000};

typedef struct __attribute__((packed)) {
    float sum;
    float avr;
    char name[10];
} ITEM_T;

ITEM_T f[5];

//uint8_t *ptr;

uint32_t *ptr;

int main(int argc, char **argv)
{
    int i;
    
    printf("addr : %p, %p, %p, %p %p\n\n", a, b, c, d, e);
    
    for (i=0; i<5; i++) {
        printf("addr : %p, %p, %p, %p %p\n", &a[i], &b[i], &c[i], &d[i], &e[i]);
    }
    
    printf("\n\naddr : %p:%d\n\n", f, sizeof (ITEM_T));
    
    for (i=0; i<5; i++) {
        printf("addr : %p\n", &f[i]);
    }    
    
    
    printf("\n\naddr of ptr = %p\n", &ptr);
    printf("ptr = %p\n", ptr);
    ptr = a;
    printf("ptr = a; => ptr = %p\n", ptr);
    
    printf("*ptr; => %08x\n", *ptr);
    
//    ptr++;
//    printf("ptr++; => ptr = %p\n", ptr);
//    
//    printf("*ptr; => %08x\n", *ptr);   
//    (*ptr)+= 20;
//    printf("ptr = %p\n", ptr);
//    printf("*ptr++; => %08x\n", *ptr);   
//    
//    for (i=0; i<5; i++) {
//        printf("a[%d] = %d\n", i, a[i]);
//    }    
//    

    for (i=0; i<5; i++) {
        printf("a[%d] = %02x\n", i, a[i]);
    }    
    
    *ptr = 0xff00ff00;
    
    printf("\n");
    
    for (i=0; i<5; i++) {
        printf("a[%d] = %02x\n", i, a[i]);
    }    
    
    int j = 0,k = 0;
    for (j=0; j < 10; j++) {
        printf("%p : ", ptr + j * 4);        
        for (k=0; k<4; k++) {
            printf("%08x ", ptr[k + j * 4]); 
        }
        printf("\n");
    }
    
	return 0;
}

 