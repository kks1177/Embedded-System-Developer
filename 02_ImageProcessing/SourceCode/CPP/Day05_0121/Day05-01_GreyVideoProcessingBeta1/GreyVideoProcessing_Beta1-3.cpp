// GreyVideoProcessing_Beta1-3.cpp

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


void printMenu();				// 메뉴 UI
void choiceMenu();				// 메뉴 선택

void openImage();				// 이미지 파일 open (입력)

void originImage(char oriImage);	// 원본 이미지
void resultImage(char oriImage);	// 결과 이미지
void ori_printScreen();				// 원본 이미지 화면 출력
void res_printScreen();				// 결과 이미지 화면 출력

//void equalImage();				// 이전 이미지 출력
// =========================== < 화소점 처리 기능 함수 선언 > ===========================
void brightControlImage();		// A.밝기 조절
void clearControlImage();		// B.선명도 조절
void reverseImage();			// C.반전
void grayScaleImage();			// D.흑백 (128/평균)
void bitCalcImage();			// E.비트 연산 (And/Or/Xor/Not)
void gammaConverseImage();		// F.감마 변환
void rangeEmphasisImage();		// G.범위 강조
void parabolaImage();			// H.파라볼라 변환
void stretchedImage();			// I.스트래칭
// ============================ < 기하학 처리 함수 선언 > ===============================
void mirroringImage();  		// J.미러링 (좌우/상하/좌우+상하)
void turnImage();				// K.회전 (방향, 90/180/270도/자유)
void doubleUpDownImage();		// L.2배 확대/축소
void moveImage();				// M.이동

// ============================ < 결과 처리 함수 선언 > ===============================
void clearUp();				// B.선명하게
void clearDown();			// B.흐릿하게

void grayScale128();		// D.흑백처리 (128 기준)
void grayScaleAvg();		// D.흑백처리 (평균값 기준)

void bitCalc_And(int val);		// E-1.비트연산_And
void bitCalc_Or(int val);		// E-2.비트연산_Or
void bitCalc_Xor(int val);		// E-3.비트연산_Xor
void bitCalc_Not();				// E-4.비트연산_Not

void L_R_mirroring();		// J.좌우 미러링
void T_B_mirroring();		// J.상하 미러링
void TB_LR_mirroring();		// J.상하/좌우 미러링

void turn90Right();			// K.오른쪽으로 90도 회전
void turn180Right();		// K.오른쪽으로 180도 회전
void turn270Right();		// K.오른쪽으로 270도 회전
void turn90Left();			// K.왼쪽으로 90도 회전
void turn180Left();			// K.왼쪽으로 180도 회전
void turn270Left();			// K.왼쪽으로 270도 회전

void doubleUp();			// L.2배 확대
void doubleDown();			// L.2배 축소



int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n%60s \n", "프로그램 종료!");
}


//// ********** 메뉴 관련 함수 정의  ********** ////
// 메뉴 UI
void printMenu() {
	puts("\n");
	puts("\t\t\t===========================================================================");
	puts("\t\t\t                    ### 그레이 영상처리 (Alpha 1) ###\n");
	puts("\t\t\t---------------------------------------------------------------------------");
	puts("\t\t\t [ 파일 메뉴 선택 ] \t 1.열기  2.저장  0.종료 \n\n");
	puts("\t\t\t [ 영상처리 메뉴 선택 ] \n");
	puts("\t\t\t    A.밝기  B.선명도  C.반전  D.흑백  E.비트연산  F.감마변환  G.범위강조");
	puts("\t\t\t    H.파라볼라 변환  I.스트래칭     J.미러링  K.회전  L.확대/축소  M.이동");
	puts("\t\t\t===========================================================================\n");
}
// 메뉴 선택
void choiceMenu() {
	printMenu();
	printf("\t\t\t 메뉴 선택 : ");

	while (inKey != '0') {
		inKey = _getch();

		switch (inKey) {
		case '0':	break;		// 종료
		case '1':				// 파일 open
			system("cls");	printMenu();	openImage();	break;

		case 'A':	case 'a':	// 밝기 조절
			system("cls");	printMenu();	brightControlImage();	break;
		case 'B':	case 'b':	// 선명도 조절
			system("cls");	printMenu();	clearControlImage();	break;
		case 'C':	case 'c':	// 반전 조절
			system("cls");	printMenu();	reverseImage();	break;
		case 'D':	case 'd':	// 흑백 (128/평균)
			system("cls");	printMenu();	grayScaleImage();	break;
		case 'E':	case 'e':	// 비트 연산 (And/Or/Xor/Not)
			system("cls");	printMenu();	bitCalcImage();	break;
		case 'F':	case 'f':	// 감마 변환
			system("cls");	printMenu();	gammaConverseImage();	break;
		case 'G':	case 'g':	// 범위 강조 
			system("cls");	printMenu();	rangeEmphasisImage();	break;
		case 'H':	case 'h':	// 파라볼라 변환 
			system("cls");	printMenu();	parabolaImage();	break;
		case 'I':	case 'i':	// 스트래칭
			system("cls");	printMenu();	stretchedImage();	break;

		case 'J':	case 'j':	// 미러링 (좌우/상하/좌우+상하)
			system("cls");	printMenu();	mirroringImage();	break;
		case 'K':	case 'k':	// 회전 (방향, 90/180/270도/자유)
			system("cls");	printMenu();	turnImage();	break;
		case 'L':	case 'l':	// 2배 확대/축소
			system("cls");	printMenu();	doubleUpDownImage();	break;
		case 'M':	case 'm':	// 이미지 이동
			system("cls");	printMenu();	moveImage();	break;

		default:				// 예외처리
			printf("입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();	printf("\t\t\t 메뉴 선택 : ");
		}
	}
}
//// ****************************************** ////



//// ********** 이미지 입출력 함수 정의 ********** ////
// 이미지 파일 열기 (입력)
void openImage() {
	char fullName[100] = "C:/images/Gallery/Gallery";			// C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";
	short tmp_row = 0, tmp_col = 0;
	unsigned char tmp_inImage[C_ROW][C_COL] = { 0, 0 };

	printf("\t\t\t 파일명 --> ");	// cat01, dog13
	scanf("%s", imgName);

	while (1) {
		printf("\n\t\t\t[픽셀 선택] \n");
		printf("\t\t\t  1.128  2.256  3.512 ");
		
		inKey = _getch();
		switch (inKey) {
		case '1':		// 128x128
			pix = 1;
			ROW = 128, COL = 128;

			// 주소(fullName) + 파일명(imgName) + _128.raw 더해서 --> filePath로
			strcat(fullName, "(128x128)/");		// strcat : 문자열을 이어줌
			strcat(fullName, imgName);
			strcat(fullName, "_128.raw");
			strcat(imgName, "_128.raw");

			strcpy(filePath, fullName);

			break;
		case '2':		// 256x256
			pix = 2;
			ROW = 256, COL = 256;

			strcat(fullName, "(256x256)/");
			strcat(fullName, imgName);
			strcat(fullName, "_256.raw");
			strcat(imgName, "_256.raw");

			strcpy(filePath, fullName);

			break;
		case '3':		// 512x512
			pix = 3;
			ROW = 512, COL = 512;

			strcat(fullName, "(512x512)/");
			strcat(fullName, imgName);
			strcat(fullName, "_512.raw");
			strcat(imgName, "_512.raw");

			strcpy(filePath, fullName);

			break;
		default:
			printf("\t\t\t입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);	system("cls");
			printMenu();	printf("\t\t\t 파일명 --> ");
		}
		if (pix != 0) break;
	}

	//// 파일 열기 ////
	FILE* rfp = fopen(filePath, "rb");		// rb: Read Binary

	// 512x512 번 반복해서 읽거나, 한방에 512,512 읽거나
	fread(tmp_inImage, sizeof(unsigned char), ROW * COL, rfp);
	
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			inImage[i][k] = tmp_inImage[tmp_row][tmp_col];
			tmp_col++;
			if (tmp_col == C_COL) {
				tmp_col = 0;
				tmp_row++;
			}
		}
	}

	//// 파일 닫기 ////
	fclose(rfp);

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	ori_printScreen();
}

// 원본 이미지
void originImage(char oriImage) {
	short px = 0;

	// Original 128x128
	if (oriImage == 1) {
		printf("\n\t\t\t < 원본 이미지 화면(128) > ");
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				px = inImage[i][k];
				SetPixel(hdc, k + 300, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
			}
		}
	}
	// Original 256x256
	else if (oriImage == 2) {
		printf("\n\t\t\t < 원본 이미지 화면(256) > ");
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				px = inImage[i][k];
				SetPixel(hdc, k + 250, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
			}
		}
	}
	// Original 512x512
	else if (oriImage == 3) {
		printf("\n\t\t < 원본 이미지 화면(512) > ");
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				px = inImage[i][k];
				SetPixel(hdc, k + 50, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
			}
		}
	}
	else
		printf("파일 업로드 오류! \n");
}
// 결과 이미지
void resultImage(char oriImage) {
	short px = 0;

	// 원본 사이즈로 출력
	if (imgSize == 0) {
		// Result 128x128
		if (oriImage == 1) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 800, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 256x256
		else if (oriImage == 2) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 720, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 512x512
		else if (oriImage == 3) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 600, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		else
			printf("파일 업로드 오류!");
	}
	// 2배 확대 출력
	else if (imgSize == 1) {
		// Result 128x128
		if (oriImage == 1) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 800, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 256x256
		else if (oriImage == 2) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 720, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 512x512
		else if (oriImage == 3) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 600, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		else
			printf("파일 업로드 오류!");
	}
	// 2배 축소 출력
	else if (imgSize == 2) {
		// Result 128x128
		if (oriImage == 1) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 800, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 256x256
		else if (oriImage == 2) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 720, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		// Result 512x512
		else if (oriImage == 3) {
			for (int i = 0; i < ROW; i++) {
				for (int k = 0; k < COL; k++) {
					px = outImage[i][k];
					SetPixel(hdc, k + 600, i + 420, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
				}
			}
		}
		else
			printf("파일 업로드 오류!");
	}
	else
		printf("파일 입력 오류!");
}
// 원본 이미지 화면 출력
void ori_printScreen() {
	if		(pix == 1)	originImage(1);		// 128x128
	else if (pix == 2)	originImage(2);		// 256x256
	else if (pix == 3)	originImage(3);		// 512x512
}
// 결과 이미지 화면 출력
void res_printScreen() {
	if		(pix == 1)	resultImage(1);		// 128x128
	else if (pix == 2)	resultImage(2);		// 256x256
	else if (pix == 3)	resultImage(3);		// 512x512
}
//// ********************************************* ////



//// ********** 화소점 처리 기능 함수 정의 ********** ////
// 이전 이미지 출력
/*
void equalImage() {		// previousImage()
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];

			outImage[i][k] = px;
		}
	}
	printf("\n");
	res_printScreen();
}
*/

// A.이미지 밝기 값 조절
void brightControlImage() {
	int value;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t  밝기 조절 값 --> ");
	scanf("%d", &value);
	printf("\n");

	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k] + value;		// px : pixel

			if (px > 255)
				px = 255;
			else if (px < 0)
				px = 0;

			outImage[i][k] = px;
		}
	}
	if (value > 0) {
		printf("\t\t\t < 밝기 %d 증가 화면 >", value);
		res_printScreen();
	}
	else if (value < 0) {
		printf("\t\t\t < 밝기 %d 감소 화면 >", value);
		res_printScreen();
	}
	else {
		printf("다시 입력하세요!\n");
	}
}

// B.이미지 선명도 조절
void clearControlImage() {
	int choice = 0;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");
	
	printf("\n\t\t\t[선명도 조절] \n");
	printf("\t\t\t  1.선명하게  2.희미하게");

	inKey = _getch();
	switch (inKey) {
	case '1':		// 선명하게
		clearUp();
		break;
	case '2':		// 희미하게
		clearDown();
		break;
	default:
		printf("입력 오류! 재입력 바랍니다! \n");
		Sleep(1000);	system("cls");
		printMenu();	printf("\t\t\t 파일명 --> ");
		break;
	}
}

// C.이미지 반전 처리
void reverseImage() {
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];

			outImage[i][k] = 255 - px;
		}
	}
	printf("\t\t\t < 영상 반전 화면 > ");
	res_printScreen();
}

// D.이미지 흑백 처리
void grayScaleImage() {
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t  1.128 기준  2.평균값 기준 \n");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':		// 128 기준
		grayScale128();
		break;
	case '2':		// 평균값 기준
		grayScaleAvg();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
}

// E.비트연산 (And/Or/Xor/Not)
void bitCalcImage() {
	int value = 0;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\n\n\t\t 1.And  2.Or  3.Xor  4.Not ");

	inKey = _getch();
	if (inKey == '1' || inKey == '2' || inKey == '3') {
		while (1) {
			printf("\t\t 연산할 값 (0~255) : ");
			scanf("%d", &value);

			if (value >= 0 && value <= 255) {
				break;
			}
			else
				printf("\t\t 입력오류! 값(0~255)을 다시 입력하세요! \n");
		}
	}
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	ori_printScreen();

	switch (inKey) {
	case '1':
		bitCalc_And(value);
		break;
	case '2':
		bitCalc_Or(value);
		break;
	case '3':
		bitCalc_Xor(value);
		break;
	case '4':
		bitCalc_Not();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}


}

// F.감마 변환
void gammaConverseImage() {
	int value = 0;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t   감마 값 입력 : ");
	scanf("%d", &value);

	ori_printScreen();

	if (value != 0) {
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				outImage[i][k] = pow(inImage[i][k] / 255., value) * 255 + 0.5;
			}
		}
	}
	else
		printf("다시 입력하세요! \n");
	printf("\t\t\t < 감마 변환 화면 > ");
	res_printScreen();
}

// G.범위 강조
void rangeEmphasisImage() {

}

// H.파라볼라 변환
void parabolaImage() {

}

// I.스트래칭
void stretchedImage() {

}
//// ************************************************ ////



//// ********** 기하학 처리 함수 정의  ********** ////
// J.미러링 (좌우/상하/좌우+상하) 
void mirroringImage() {
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t 1.좌우  2.상하  3.좌우+상하 \n");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':
		L_R_mirroring();
		break;
	case '2':
		T_B_mirroring();
		break;
	case '3':
		TB_LR_mirroring();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
}

// K.회전(오른쪽,왼쪽 90/180/270/자유)
void turnImage() {
	int direct = 0;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t [방향] 1.오른쪽  2.왼쪽 ");
	scanf("%d", &direct);
	printf("\n\t\t\t\t\t\t\t    [각도] A.90  B.180  C.270  D.자유 ");

	// 오른쪽으로 회전
	if (direct == 1) {
		inKey = _getch();
		switch (inKey) {
		case 'A':	case 'a':		// 90도 회전
			system("cls");	printMenu();	turn90Right();	break;
		case 'B':	case 'b':		// 180도 회전
			system("cls");	printMenu();	turn180Right();	break;
		case 'C':	case 'c':		// 270도 회전
			system("cls");	printMenu();	turn270Right();	break;
		case 'D':	case 'd':		// 자유 회전
			break;
		default:
			break;
		}
	}
	// 왼쪽으로 회전
	else if (direct == 2) {
		inKey = _getch();
		switch (inKey) {
		case 'A':	case 'a':		// 90도 회전
			system("cls");	printMenu();	turn90Left();	break;
		case 'B':	case 'b':		// 180도 회전 
			system("cls");	printMenu();	turn180Left();	break;
		case 'C':	case 'c':		// 270도 회전
			system("cls");	printMenu();	turn270Left();	break;
		case 'D':	case 'd':		// 자유 회전
			break;
		default:
			break;
		}
	}
	else {
		printf("다시 입력해주세요! \n");
		return;
	}
	res_printScreen();
}

// L.2배 확대/축소
void doubleUpDownImage() {
	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t 1.2배 확대  2.2배 축소 ");

	ori_printScreen();

	inKey = _getch();
	switch (inKey) {
	case '1':
		doubleUp();
		break;
	case '2':
		doubleDown();
		break;
	default:
		printf("다시 입력하세요! \n");
		break;
	}
}

// M.이동
void moveImage() {
	int value = 0;

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);

	printf("\t\t  이동할 값 : ");
	scanf("%d", &value);

	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = 0;
		}
	}
	for (int i = 0; i < ROW - value; i++) {
		for (int k = 0; k < COL - value; k++) {
			outImage[i][k] = inImage[i + value][k + value]; // = inImage[i][k];
		}
	}
	res_printScreen();
}




// B.선명하게
void clearUp() {
	float value = 0;

	printf("   선명도 조절 값(양수) --> ");
	scanf("%f", &value);

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	ori_printScreen();

	if (value > 0) {
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				float px = inImage[i][k] * value;		// px : pixel

				if (px > 255)
					outImage[i][k] = 255;
				else if (px < 0)
					outImage[i][k] = 0;
				outImage[i][k] = (int)px;
			}
		}
		printf("\t\t\t< 선명도 %.1f 증가 화면 >", value);
		res_printScreen();
	}
	else
		printf("\t\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}
// B.흐릿하게
void clearDown() {
	float value = 0;

	printf("\t   선명도 조절 값(양수) --> ");
	scanf("%f", &value);

	system("cls");
	printMenu();
	printf("\t\t\t  선택한 파일명 : %s", imgName);
	printf("\n\n");

	ori_printScreen();

	if (value > 0) {
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				float px = inImage[i][k] / value;		// px : pixel

				if (px > 255)
					outImage[i][k] = 255;
				else if (px < 0)
					outImage[i][k] = 0;
				outImage[i][k] = float(px);
			}
		}
		printf("\t\t\t< 선명도 %.1f 감소 화면 >", value);
		res_printScreen();
	}
	else
		printf("\t\t\t음수 또는 0 입력.. 양수를 입력해주세요.");
}

// D.흑백처리 (128 기준)
void grayScale128() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];

			if (px > 128) {
				px = 255;
			}
			else if (px <= 128) {
				px = 0;
			}
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 흑백 처리(128 기준) 화면 > ");
	res_printScreen();
}
// D.흑백처리 (평균값 기준)
void grayScaleAvg() {
	int pixelSum = 0;
	int pixelAvg = 0;

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];
			pixelSum += px;
		}
	}
	pixelAvg = pixelSum / (ROW * COL);

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];
			if (px > pixelAvg) {
				px = 255;
			}
			else {
				px = 0;
			}
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 흑백 처리(평균값 %d 기준) 화면 > ", pixelAvg);
	res_printScreen();
}

// E-1.비트연산_And
void bitCalc_And(int val) {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			unsigned char px = inImage[i][k] & val;

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < AND 비트 연산 화면 > ");
	res_printScreen();
}
// E-2.비트연산_Or
void bitCalc_Or(int val) {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			unsigned char px = inImage[i][k] | val;
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < OR 비트 연산 화면 > ");
	res_printScreen();
}
// E-3.비트연산_Xor
void bitCalc_Xor(int val) {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			unsigned char px = inImage[i][k] ^ val;
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < XOR 비트 연산 화면 > ");
	res_printScreen();
}
// E-4.비트연산_Not
void bitCalc_Not() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			unsigned char px = ~inImage[i][k];
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < NOT 비트 연산 화면 > ");
	res_printScreen();
}

// J.이미지 좌우 미러링
void L_R_mirroring() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][COL - 1 - k];	// (최대열 - 1) - 반복자
			
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 좌우 미러링 화면 > ");
	res_printScreen();
}
// J.이미지 상하 미러링
void T_B_mirroring() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[ROW - 1 - i][k];		// (최대행 - 1) - 반복자
			
			outImage[i][k] = px;
		}
	}
	printf("\t\t\t < 영상 상하 미러링 화면 > ");
	res_printScreen();
}
// J.이미지 상하+좌우 미러링
void TB_LR_mirroring() {
	for (int i = 0; i < COL; i++) {
		for (int k = 0; k < ROW; k++) {
			unsigned char mirror_i = ROW - 1 - i;
			unsigned char mirror_k = COL - 1 - k;

			outImage[i][k] = inImage[mirror_i][mirror_k];
		}
	}
	printf("\t\t\t < 영상 상하/좌우 미러링 화면 > ");
	res_printScreen();
}

// K.결과 이미지 시계방향으로 90도 회전
void turn90Right() {
	ori_printScreen();

	for (int i = 0; i < COL; i++) {
		for (int k = 0; k < ROW; k++) {
			outImage[i][k] = inImage[ROW - k - 1][i];
		}
	}
	printf("\t\t\t < 시계방향 90도 회전 화면 > ");
}
// K.결과 이미지 시계방향으로 180도 회전
void turn180Right() {
	ori_printScreen();

	for (int i = 0; i < COL; i++) {
		for (int k = 0; k < ROW; k++) {
			outImage[i][k] = inImage[ROW - i - 1][COL - k - 1];
		}
	}
	printf("\t\t\t < 시계방향 180도 회전 화면 > ");
}
// K.결과 이미지 시계방향으로 270도 회전
void turn270Right() {
	ori_printScreen();

	for (int i = 0; i < COL; i++) {
		for (int k = 0; k < ROW; k++) {
			outImage[i][k] = inImage[k][ROW - i - 1];
		}
	}
	printf("\t\t\t < 시계방향 270도 회전 화면 > ");
}

// K.결과 이미지 반시계방향으로 90도 회전
void turn90Left() {
	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[k][ROW - 1 - i];
		}
	}
	printf("\t\t\t < 반시계방향 90도 회전 화면 > ");
}
// K.결과 이미지 반시계방향으로 180도 회전
void turn180Left() {
	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[ROW - 1 - i][COL - k - 1];
		}
	}
	printf("\t\t\t < 반시계방향 180도 회전 화면 > ");
}
// K.결과 이미지 반시계방향으로 270도 회전
void turn270Left() {
	ori_printScreen();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[ROW - k - 1][i];
		}
	}
	printf("\t\t\t < 반시계방향 270도 회전 화면 > ");
}

// L.2배 확대
void doubleUp() {
	imgSize = 1;

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[i / 2][k / 2];
		}
	}
	res_printScreen();
}
// L.2배 축소
void doubleDown() {
	imgSize = 2;

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = 0;
		}
	}
	for (int i = 0; i < ROW / 2; i++) {
		for (int k = 0; k < COL / 2; k++) {
			outImage[i][k] = inImage[i * 2][k * 2];
		}
	}
	res_printScreen();
}
//// ******************************************** ////


