#include <stdio.h>

// 함수 선언부
void while_test(void);
void do_while_test(plus);
void do_while_test2(void);
void if_else_test(void);
void for_test(void);
void for_test_temperature(void);

// 메인 함수
int main(int argc, char **argv)
{
	printf("System Start \n");
    
    printf("\n < while_test > \n");
    while_test();
    
    printf("\n < do_while_test, loop++ > \n");
    do_while_test(1);
    printf("\n < do_while_test, ++loop > \n");
    do_while_test(2);
    printf("\n < do_while_test2 > \n");
    do_while_test2();
    
    printf("\n < if_else_test > \n");
    if_else_test();
    
    printf("\n < for_test > \n");
    for_test();
    
    printf("\n < for_test_temperature > \n");
    for_test_temperature();
    
    puts(" ");
	return 0;
}

// 함수 정의부
void while_test(void)
{
    int loop = 1;
    while (loop <= 10) {
        printf("%d, little Indian \n", loop);
        loop++;
    }
}

//volatile int deb = 1;

void do_while_test(plus)
{
    int loop = 1;

//#if 0
    if (plus == 1) {
        do {
            printf("%d, little Indian \n", loop);
        } while (loop++ <= 10);
    }
//#else 
    if (plus == 2) {
        do {
            printf("%d, little Indian \n", loop+1);
        } while (++loop < 10);
    }
//#endif
    do {
        printf("test once.. \n");
    } while(0);
}

void do_while_test2(void)
{
    int num, sum = 0;
    
    printf("Input Number (EXIT, if intput 0) \n ");
    
    do {
        scanf("%d", &num);
        sum += num;
    } while (num != 0);
    
    printf("sum = %d \n", sum);
}

#define DEBUG   1

void if_else_test(void) 
{
    int charge = 0;
    int amount = 0;
    
#if (DEBUG == 1)
    printf("[%s][%s] \n", __DATE__, __FILE__);          // __DATE__ : 오늘 날짜, __FILE__ : 파일 현재 위치
    printf("[%s][%d] \n", __FUNCTION__, __LINE__);      // __FUNCTION__ : if_else_test(), __LINE__ : 88번째 줄
#endif
    
    do {
        charge = 13000;
        
        printf("Total used Time (EXIT, if intput 0) : ");
        scanf("%d", &amount);
        
        if (amount == 0) break;
        
        if (amount < 100) {
            charge += amount * 50;
#if (DEBUG == 1)
            printf("[%s][%d] \n", __FUNCTION__, __LINE__);
        }
        else if (amount < 200) {
            charge += 100 * 50;
            charge += (amount - 100) * 30;
        }
        else {
            charge += 100 * 50;
            charge += 100 * 30;
            charge += (amount - 200) * 20;
        }
        printf("Total charge : %d \n", charge);
    } while(1);
}

void for_test(void) 
{
    for (int loop = 1; loop <= 10; loop++) {
        printf("%d, Little Indian \n", loop);
    }
}

void for_test_temperature(void) 
{
    int C, F;
    for (C = 0; C <= 100; C++) {
        F = (9 * C/5) + 32;
        printf("Celsius %3dC : Fahrenheit %3dF \n", C, F);
    }
}