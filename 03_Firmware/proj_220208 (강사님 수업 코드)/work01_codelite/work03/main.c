#include <stdio.h>

void while_test(void)
{
    int loop = 1;
    while (loop <= 10) {
        printf("%d Little Indian\n", loop);
        loop++;
    }
 }
 
 void do_while_test(void)
 {
     int loop = 0;
     
#if 0     
     do {
        printf("%d Little Indian\n", loop);
     } while (loop++ <= 10);
#else
     do {
        printf("%d Little Indian\n", loop+1);
     } while (++loop < 10);
#endif     

     do {
         printf("test once..\n");
     } while (0);
 }

void for_test(void)
{
    int loop;
    for (loop=1 ; loop<=10 ; loop++) {
        printf("%d Little Indian\n", loop);
    }
}

void for_test_temperature(void)
{
    int F, C;
    
    for (C=0; C<=100; C++) {
        F = (9*C/5) + 32;
        printf("Celsius %3dC : Fahrenheit %3dF\n ", C, F);
    }
}

void do_while_test2(void)
{
    int num, sum = 0;
    
    printf("Input Number(Exit, if 0)\n");
    do {
        scanf("%d", &num);
        sum += num;
    } while (num != 0);
    
    printf("sum = %d\n", sum);
}

#define DEBUG       1

void if_else_test(void)
{
    int charge;
    int amount;
    
#if (DEBUG == 1)
    printf("[%s][%s]\n", __DATE__, __FILE__);
    printf("[%s][%d]\n", __FUNCTION__, __LINE__);    
#endif
    
    do {
        charge = 13000;
        
        printf("Total used time(Exit, if 0) : ");
        
        scanf("%d", &amount);
        
        if (amount == 0) break;
        
        if (amount < 100) {
            charge += amount*50;
#if (DEBUG == 1)
            printf("[%s][%d]\n", __FUNCTION__, __LINE__);                
#endif
        } else if (amount < 200) {
            charge += 100*50;
            charge += (amount-100)*30;
#if (DEBUG == 1)
            printf("[%s][%d]\n", __FUNCTION__, __LINE__);                
#endif
        } else {
            charge += 100*50;
            charge += 100*30;
            charge += (amount-200)*20;
#if (DEBUG == 1)
            printf("[%s][%d]\n", __FUNCTION__, __LINE__);                
#endif
        }
    
        printf("Total charge : %d\n", charge);
    } while (1);
    

}

int main(int argc, char **argv)
{
	printf("System Start..\n");
    //while_test();
    //do_while_test();
    //for_test();
    //for_test_temperature();
    //do_while_test2();
    if_else_test();
	return 0;
}
