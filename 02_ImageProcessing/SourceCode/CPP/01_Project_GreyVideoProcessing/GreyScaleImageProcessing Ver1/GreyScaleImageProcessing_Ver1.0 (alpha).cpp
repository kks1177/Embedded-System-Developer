// GreyScaleImageProcessing_Ver1.0 (alpha).cpp
// 2022.01.17 ~ 2022.02.06
/*
=======================================================================
  * 프로젝트명 : GreyScaleImageProcessing (미니프로젝트)
  * 버전 : Ver 1.0
  * 기능
   - 기본 기능
		: 파일 Open/Save, 종료
   - 영상처리 알고리즘
		: 화소점 처리, 히스토그램 처리, 화소영역 처리, 엣지검출 처리, 기하학 처리

 * 발표자 : 김기성
 * 작성일자 : 2022/01/08
 * 과정명 : 임베디드 전문가 과정
 * 과목명 : 프로그래밍 (우재남 교수님)
 * 프로젝트 명 : Grey Scale Image Processing (Ver.1.0)
=======================================================================
*/


#include "FunctionDeclaretion.h"
#include "FunctionDifinition.h"

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n %60s \n", "프로그램 종료! \n");
}

