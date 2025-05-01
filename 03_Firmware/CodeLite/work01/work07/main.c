// work07
// 함수 포인터

///* 
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

// ========== 전역 변수부 ==========
// 함수 포인터 변수
int (*loop)(void);
// void pointer 를 return 하는 loop 함수의 prototype
//void *loop(void);
float setting_value = 0.0f;

// ========== 함수 선언부 ==========
int scena_main(void);     // scen ==> scenario
int scena_menu1(void);
int scena_menu2(void);


// ========== 메인 함수 ==========
int main(int argc, char **argv)
{
    printf("System Start.. \n");
    
    loop = scena_main;
    
    while (1) {
        if (loop() == -1)
            break;
    }
    
    return 0;
}

// ========== 함수 정의부 ==========
// scen ==> scenario
int scena_main(void)
{
    bool exit = false;
    
    system("cls");
    printf(" < Main Menu > \n");
    printf(" If, you want to escape, press 'ESC' \n");
    printf("  >>> '1' : menu1 \n");
    printf("  >>> '2' : menu2 \n");
    
    while (1) {
        // 엔터 버튼을 누르면 --> 저장, 해당 루프를 탈출
        // 취소 버튼을 누르면 --> 저장 없이 해당 루프 탈출
        // 화살표 버튼을 누르면 --> 해당 메시지 화면에 출력
        // scena_menu1 변경
        
        if (kbhit()) {
            int ch = getch();
            printf("%d \n", ch);
        
            // ENTER:13, ESC:27, 상:72, 하:80, 좌:75, 우:77
            switch (ch) {
                case 27: {      // ESC Key
                    return -1;      // program terminate
                } break;
                case 13: {      // ENTER Key
                } break;
                
                case '1': {
                    loop = scena_menu1;
                    exit = true;
                } break;
                case '2': {
                    loop = scena_menu1;
                    exit = true;
                }
            }
            if (exit == true)
                break;
        }
    }
    return 0;
}

int scena_menu1(void)
{
    bool exit = false;
    char buf[50] = {0, };
    volatile uint8_t idx = 0; 
    
    system("cls");
    printf(" Menu 1 \n");
    
    sprintf(buf, "%06.2f", setting_value);
    printf("[%d]%s\n", idx, buf);  
    
    while (1) {
        // 측정된 값을 화면에 출력
        // 엔터 버튼을 누르면 --> scena_main 변경
 
        if (kbhit()) {
            int ch = getch();
            //printf("%d \n", ch);
        
            // ENTER:13, ESC:27, 상:72, 하:80, 좌:75, 우:77
            switch (ch) {
                case 27: {      // ESC Key
                    exit = true;
                } break;
                case 13: {      // ENTER Key
                    setting_value = atof(buf);
                    exit = true;
                } break;
                
                case 72: {      // UP
                    //if (idx != 3) {
                        buf[idx]++;
                        if (buf[idx] > '9') buf[idx] = '0';
                    //}
                    printf("[%d]%s\n", idx, buf);  
                } break;
                case 80: {      // DOWN
                    //if (idx != 3) {
                        buf[idx]--;
                        if (buf[idx] < '0') buf[idx] = '9';
                    //}
                    printf("[%d]%s\n", idx, buf); 
                } break;
                case 75: {      // LEFT
                    if (idx > 0) {
                        idx--;
                        
                        if ( idx == 3)
                            idx--;
                    }
                    printf("[%d]%s\n", idx, buf);    
                } break;
                case 77: {      // RIGHT
                    if (idx < 5) {
                        idx++;
                        
                        if (idx == 3) 
                            idx++;
                    }
                    printf("[%d]%s\n", idx, buf); 
                } break;
            }
            if (exit == true) {
                loop = scena_main;
                break;
            }
        }
    }
    return 0;
}

int scena_menu2(void)
{
    bool exit = false;
    char buf[50] = {0, };
    volatile uint8_t idx = 0; 
    
    system("cls");
    printf(" Menu 2 \n");
    
    sprintf(buf, "%06.2f", setting_value);
    printf("[%d]%s\n", idx, buf);  
    
    while (1) {
        // 측정된 값을 화면에 출력
        // 엔터 버튼을 누르면 --> scena_main 변경
 
        if (kbhit()) {
            int ch = getch();
            //printf("%d \n", ch);
        
            // ENTER:13, ESC:27, 상:72, 하:80, 좌:75, 우:77
            switch (ch) {
                case 27: {      // ESC Key
                    exit = true;
                } break;
                case 13: {      // ENTER Key
                    setting_value = atof(buf);
                    exit = true;
                } break;
                
                case 72: {      // UP
                    //if (idx != 3) {
                        buf[idx]++;
                        
                        if (buf[idx] > '9') buf[idx] = '0';
                    //}
                    printf("[%d]%s\n", idx, buf);
                } break;
                case 80: {      // DOWN
                    //if (idx != 3) {
                        buf[idx]--;
                        if (buf[idx] < '0') buf[idx] = '9';
                    //}
                    printf("[%d]%s\n", idx, buf);
                } break;
                case 75: {      // LEFT
                    if (idx > 0) {
                        idx--;
                        
                        if ( idx == 3) 
                            idx--;
                    }
                    printf("[%d]%s\n", idx, buf);    
                } break;
                case 77: {      // RIGHT
                    if (idx < 5) {
                        idx++;
                        
                        if (idx == 3) 
                            idx++;
                    }
                    printf("[%d]%s\n", idx, buf);
                } break;
            }
            if (exit == true) {
                loop = scena_main;
                break;
            }
        }
    }
    return 0;
}
//*/

char arr[10];       // 1차 배열
char arr2[2][2];    // 2차원 배열




// 웅식이형 코드
/*
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <math.h>

void (*loop)(char);

typedef struct{
    uint8_t idx;
    char num[7];
} NUM_T;

void print(uint8_t);
void scene_1(char);

NUM_T gNumObj = {
  0, "000.00\0"  
};
float buf[20] = { 0.0, };
uint8_t buf_idx = 0;

int main(int argc, char **argv)
{
   system("cls");
    while(1){
        char ch = getch();
        system("cls");
        if (ch == '1'){
            loop = scene_1;
            
            print(0);
            while(1){
                char menu = getch();
                system("cls");
                
                loop(menu);
            }
        }
    }
    return 0;
}

void scene_1(char m){
    NUM_T *n = &gNumObj;
    uint8_t idx = n->idx;
    
    if(m == 72){
        n->num[idx]++;
        if (n->num[idx] > '9')
            n->num[idx] = '0';
    }
    else if (m == 80){
        n->num[idx]--;
        if (n->num[idx] < '0')
            n->num[idx] = '9';
    }
    else if (m == 75){
        n->idx--;
        if (n->idx == 3) n->idx--;
        else if (n->idx < 0) n->idx = 5;
    }
    else if (m == 77){
        n->idx++;
        if (n->idx == 3) n->idx++;
        else if (n->idx > 5) n->idx = 0;
    }
    else if (m == 13){
        float tmp;
        tmp = atof(n->num);
        if(tmp != 0.0){
            buf[buf_idx] = tmp;
            buf_idx++;
        }
        n->idx = 0;
        strcpy(n->num, "000.00\0");
    }
    else if (m == 27){
        n->idx = 0;
        strcpy(n->num, "000.00\0");
    }
    
    print(n->idx);
}

void print(uint8_t loc){
    NUM_T *n = &gNumObj;
    char underbar[8] = "       \0";
    underbar[loc] = '-';
    
    printf("%s\n", n->num);
    printf("%s\n", underbar);
    printf("------------------------------\n");
    for (int i=0; i<buf_idx; i++){
        printf("buf[%d] = %3.2f\n", i, buf[i]);
    }
}
*/
