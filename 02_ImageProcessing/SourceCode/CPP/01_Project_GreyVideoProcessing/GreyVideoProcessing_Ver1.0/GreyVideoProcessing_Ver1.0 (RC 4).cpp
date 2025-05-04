// GreyVideoProcessing_Ver1.0 (RC 4).cpp


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
#include <Windows.h>		// GUI 지원해주는 헤더
#include <string>
using namespace std;	// C++ 추가 기능

#include "Declaration4.h"
#include "Difinition4.h"

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n%60s \n", "프로그램 종료!");
}

