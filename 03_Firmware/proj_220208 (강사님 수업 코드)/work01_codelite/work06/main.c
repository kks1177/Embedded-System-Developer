// static 변수 사용 범위와 수명
#include <stdio.h>

void count_test(void);
int count_static(void);
void swap_call_by_value(void);
void swap_value(int a, int b);
void swap_call_by_reference(void);
void swap_reference(int *a, int *b);

int main(int argc, char **argv)
{
    count_test();
    swap_call_by_value();
    swap_call_by_reference();
    
    return 0;
}

void count_test(void)
{
    int i, count;
    
    for (i=0 ; i<5 ; i++) {
        count = count_static();
        printf("Function Count() is called %d times\n", count);
    }
}

int count_static(void)
{
#if 1    
    static int count = 0;
#else
    int count = 0;
#endif

    count++;
    return count;
}

void swap_call_by_value(void)
{
    int a=10, b=20;
    swap_value(a,b);
    printf("a=%d, b=%d\n", a, b);
}

void swap_value(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_call_by_reference(void)
{
    int a=10, b=20;
    swap_reference(&a, &b);
    printf("a=%d, b=%d\n", a, b);
}

void swap_reference(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}