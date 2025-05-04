#define _CRT_SECURE_NO_WARNINGS
using namespace std; // C++ 추가기능
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h> // GUI를 지원하는 기능
#include <math.h>

//======================================================================================================
//*****************************프로젝트명 : 2022 GrayScale Image Processing 
//*****************************버      전 : ver 1 preview
//======================================================================================================

//전역 변수부//
char filename[100];
int inH, inW, outH, outW; // 입출력 영상의 크기, 즉 입출력 영상의 이미지높이, 너비 
const double pi = 3.145926535897932; //이미지 회전시 필요한 값
int inKey = 0; // 이미지 처리 4가지 대 분류


short x_mov = 0; // printImage 디스플레이 좌표
short y_mov = 0;

unsigned char** inImage = NULL, ** outImage = NULL; // 입력이미지, 출력이미지
unsigned char** tmpIn1 = NULL; unsigned char** tmpOut1 = NULL; // 임시 입출력 이미지 변수

HWND hwnd; // 윈도 화면(외부, 물리적)
HDC  hdc;  // 윈도 화면(내부, 논리적)

////////////////////// **** 함수 선언부 ******/////////////////////////////////////////////
// 
//********공통함수**********//
unsigned char** malloc2D(int, int);// 2차원 배열 메모리 할당 및 해제
void free2D(unsigned char**, int);
void free2D_out();

void openImage(); void originalImage(); void print_ori_Image();
void printImage();

//********이미지 처리 함수**********//

void equalImage();
void reverseImage(); void timesImage();
void divideImage(); void blackWhiteImage();
void mean(); void bitImage(); void GammaCorrection();
void rangeFocus(); void parabola(); void stretch();
void mirrorImage1(); void mirrorImage2(); void mirrorImage3();
void rot90(); void rot180(); void rot270();
void moving(); void rotate();
void enlarge();  void zoomInbiImage();  void backwarding();
void microprint(); void histostretch(); void endin();
void saveImage(); void histoEqual(); void blurring();
void embossing();

void printMenu() {
    char input = 0;

    puts("\n ## GrayScale Image Processing ver 1.0 RC5 ##\n");
    puts(" 0. 열기 \t 1. 저장 \t 2. 종료\n");
    input = _getch();

    system("CLS"); // 프린트메뉴 직후 선택할때 화면을 깨끗하게 함 

    printf("0. 화소점처리 \n");
    printf("1. 기하학처리\n");
    printf("2. 화소영역처리 \n");
    printf("3. 화소영역처리(엣지) \n");
    printf("4. 히스토그램처리 \n");

    while (input != 2)
    {
        char inKey = 0;

        inKey = _getch();
        switch (inKey) {
        case '0':
            puts(" ##################### 1. 화소점 처리 ####################### \n");
            puts("A.밝기 \t B.곱셈 \t C.나눗셈 \t D.반전\n");
            puts("E.흑백(128) \t F.흑백(평균) \t G. 비트연산\n");
            puts("H. 감마보정 \t I.범위강조 \t J.파라볼라 \t K.스트레칭\n");
            break;
        case '1':
            puts(" ##################### 2. 기하학 처리 ###################### \n");
            break;
        case '2':
            puts(" ##################### 3. 화소영역처리 ##################### \n");
            break;
        case '3':
            puts(" ##################### 4. 화소영역처리(엣지) ############### \n");
            break;
        case '4':
            puts(" ##################### 5. 히스토그램 처리 ################## \n");
            break;
        default: printf("\n 잘못 입력하셨습니다. 다시 선택하세요 \n\n\n\n\n");
        }
        printf(" GrayScale Image Processing(ver 1.0) RC5 구입해 주셔서 감사합니다.\n\n\n\n");
        printf("염유경 미디어\n\n\n\n");
    }
}

// 메인함수 //

int main() {
    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);

    char button = 0;

    printMenu();
    button = _getch();
    if (inKey == 0) {
        switch (button) {
        case 'A':case 'a': openImage(); break;
        case 'B':case 'b': equalImage(); break;
        }
    }
    printf(" GrayScale Image Processing(ver 1.0) RC5 구입해 주셔서 감사합니다.\n\n\n\n");
    printf("염유경 미디어\n\n\n\n");
}

