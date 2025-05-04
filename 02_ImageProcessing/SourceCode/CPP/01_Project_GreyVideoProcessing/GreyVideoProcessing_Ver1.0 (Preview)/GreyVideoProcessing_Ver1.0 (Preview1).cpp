// GreyVideoProcessing_Ver1.0 (Preview1).cpp
// 22.01.26		히스토그램 스트래칭, 엔드-인 탐색, 히스토그램 평활화 추가


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>		// GUI 지원해주는 헤더
#include <string>
using namespace std;	// C++ 추가 기능

#include "FunctionDeclaretion.h"
#include "FunctionDifinition.h"

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n%60s \n", "프로그램 종료!");
}

