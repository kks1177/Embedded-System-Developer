// work06
// static 변수 사용 범위와 수명
#include <stdio.h>
#include <stdint.h>
#include <conio.h>

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






// 함수 포인터 변수
void (*loop)(void);
// void pointer 를 return 하는 loop 함수의 prototype
//void *loop(void);


void scena_0(void);     // scen ==> scenario
void scena_1(void);

void app_main(void)
{
    loop = scena_1;
    
    while (1) {
        loop();
    }
}


// scen ==> scenario
void scena_0(void)
{
    uint8_t sens_value = 200;
    
    while (1) {
        // 화살표 버튼을 누르면 화면에 해당하는 메시지 출력
        // 엔터 버튼을 누르면 저장, 해당 루프를 탈출
        // 취소 버튼을 누르면 저장 없이 해당 없이 루프 탈출
        // scene_1로 변경
        sens_value++;       // 센서에서 들어오는 값 
        
        int ch = getch();
        
        // ENTER Key
        if (ch == 13) {
            // 
            loop = scena_1;
            break;
        }
        // ESC Key
        if (ch == 27) {
            break;
        }
    }
}

void scena_1(void)
{
    uint8_t sens_value = 100;
    
    while (1) {
        // 측정된 값을 화면에 출력
        // 엔터 버튼을 누르면 scene_0로 변경
        
        sens_value++;       // 센서에서 들어오는 값
 
        int ch = getch();
        
        // ENTER Key
        if (ch == 13) {
            loop = scena_0;
            break;
        }
        // ESC Key
        if (ch == 27) {
            break;
        }
    }
}
