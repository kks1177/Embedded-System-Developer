// GreyScaleImageProcessing_Ver1.0.cpp
/* 
=======================================================================
  * 프로젝트명 : Image Processing Programming
  * 버전 : 미니프로젝트 Ver 1.0
  * 기능
   - 기본 기능
		: 파일 Open/Save, 종료
   - 영상처리 알고리즘
		: 화소점 처리, 히스토그램 처리, 화소영역 처리, 엣지검출 처리, 기하학 처리

 * 발표자 : 김기성
 * 과정명 : 무인이동체용 지능형 임베디드 시스템 개발자
 * 과목명 : 프로그래밍 (우재남 교수님)
 * 프로젝트 기간 : 2022.01.20 ~ 2022.02.06
======================================================================= 
*/


#include "Declaretion.h"
#include "Difinition.h"

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n %60s \n", "프로그램 종료! \n");
}

