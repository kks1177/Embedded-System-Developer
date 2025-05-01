// GreyVideoProcessing_Beta1-4.cpp

/*
 - 밝기 (밝게/어둡게)
 - 선명도 (선명하게/흐릿하게)
 - 반전
 - 흑백
 - 흑백 (평균)

 - 비트 And/Or/Xor/Not
 - // 감마, 범위 강조, 파라볼라 변환, 스트래칭

 - 영상 좌우 미러링
 - 영상 상하 미러링
 - 좌우+상하 미러링
 - 결과 이미지 90도 회전
 - 결과 이미지 180도 회전
 - 결과 이미지 270도 회전
 - // 이동, 자유 각도 회전, 2배 축소, 2배 확대
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;	// C++ 추가 기능


// **** 전역부 (중요!) **** //
char imgName[100] = { 0 };		// 파일명 + .확장자명
char filePath[100] = { 0 };		// 파일 경로 담을 변수
//char fileName[100] = { 0 };

char inKey = 0;				// 키보드로 입력 받는 변수
char pix = 0;				// 이미지 출력 변수
int ROW = 512, COL = 512;
int imgSize = 0;

const int C_ROW = 512, C_COL = 512;

unsigned char inImage[C_ROW][C_COL] = { 0, 0 };		// input
unsigned char outImage[C_ROW][C_COL] = { 0, 0 };	// output

HWND hwnd;		// 윈도우 화면 (외부, 물리적)		// 암기x
HDC  hdc;		// 왼도우 화면 (내부, 논리적)		// 암기x

#include "GreyVideoProcessing_Beta1-4.h"

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n%60s \n", "프로그램 종료!");
}

