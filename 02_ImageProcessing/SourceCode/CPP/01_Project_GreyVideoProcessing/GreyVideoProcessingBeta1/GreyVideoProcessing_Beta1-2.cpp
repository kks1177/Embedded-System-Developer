// GreyVideoProcessing_Beta1-2.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;	// C++ 추가 기능

// **** 전역부 (중요!) **** //
char filename[100];
char tmpName[100] = { 0 };		// 파일명 담을 변수 선언
const int ROW = 512, COL = 512;
unsigned char inImage[ROW][COL];		// input
unsigned char outImage[ROW][COL];		// output
HWND hwnd;		// 윈도우 화면 (외부, 물리적)		// 암기x
HDC  hdc;		// 왼도우 화면 (내부, 논리적)		// 암기x

void openImage();
void printScreen(char res);
//void originImage();			// A.원본
void equalImage();				// A.원본

void brightControlImage();		// B.밝기 조절
void clearControlImage();		// C.선명도 조절
void reverseImage();			// D.반전
void grayScaleImage();			// E.흑백
void L_R_mirroring();			// F.좌우 미러링
void T_B_mirroring();			// G.상하 미러링
void turn90Right();				// H.결과 이미지 오른쪽으로 90도 회전
void turn90Left();				// I.결과 이미지 왼쪽으로 90도 회전

/*
 - 밝기 (밝게/어둡게)
 - 반전
 - 흑백
 - 영상 좌우 미러링

 - 영상 상하 미러링
 - 결과 이미지 90도 회전
 - // 결과 이미지 180도 회전
 - // 평균값으로 흑백처리
 - // 중앙값으로 흑백처리

*/


// 메뉴 설명
void printMenu() {
	puts("\n");
	puts("\t\t\t=========================================================================");
	puts("\t\t\t                 ### 그레이 영상처리 (Alpha 1) ###\n");
	puts("\t\t\t-------------------------------------------------------------------------");
	puts("\t\t\t [ 파일 메뉴 선택 ] \t 1.열기  2.저장  0.종료 \n\n");
	puts("\t\t\t [ 영상처리 메뉴 선택 ] \n");
	puts("\t\t\t    A.원본  B.밝기  C.선명도  D.반전  E.흑백  F.좌우미러링  G.상하미러링");
	puts("\t\t\t=========================================================================\n");
}
// 메뉴 선택
void choiceMenu() {
	char inKey = 0;		// 키보드로 입력 받는 변수

	printMenu();
	printf("\t\t\t 메뉴 선택 : ");

	while (inKey != '0') {
		inKey = _getch();

		switch (inKey) {
		case '0':	break;
		case '1':
			system("cls");
			printMenu();
			openImage();
			break;
		case 'A':	case 'a':
			system("cls");
			printMenu();
			equalImage();
			break;
		case 'B':	case 'b':
			system("cls");
			printMenu();
			brightControlImage();
			break;
		case 'C':	case 'c':
			system("cls");
			printMenu();
			clearControlImage();
			break;
		case 'D':	case 'd':
			system("cls");
			printMenu();
			reverseImage();
			break;
		case 'E':	case 'e':
			system("cls");
			printMenu();
			grayScaleImage();
			break;
		case 'F':	case 'f':
			system("cls");
			printMenu();
			L_R_mirroring();
			break;
		case 'G':	case 'g':
			system("cls");
			printMenu();
			T_B_mirroring();
			break;
		case 'H':	case 'h':
			system("cls");
			printMenu();
			T_B_mirroring();
			break;
		default:
			printf("입력 오류! 재입력 바랍니다! \n");
			Sleep(1000);
			system("cls");
			printMenu();
			printf("\t\t\t 메뉴 선택 : ");
		}
	}
}

int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	choiceMenu();

	printf("\n%60s \n", "프로그램 종료!");
}


// 파일 열기
void openImage() {
	char fullName[100] = "C:/images/Pet_RAW(squre)/Pet_RAW(512x512)/";

	printf("\t\t\t 파일명 --> ");	// cat01, dog13
	scanf("%s", tmpName);

	// 주소(fullname) + 파일명(tmpname) + _512.raw 더해서 --> filename으로
	strcat(fullName, tmpName);		// strcat : 문자열을 이어줌
	strcat(fullName, "_512.raw");
	strcpy(filename, fullName);

	//// 파일 열기 ////
	FILE* rfp = fopen(filename, "rb");		// rb: Read Binary

	// 512x512 번 반복해서 읽거나, 한방에 512,512 읽거나
	fread(inImage, sizeof(unsigned char), ROW * COL, rfp);

	//// 파일 닫기 ////
	fclose(rfp);

	system("cls");
	printMenu();
	printf("\t\t\t선택한 파일명 : %s %s", tmpName, "\n\n\n");
	equalImage();
}

// 이미지를 화면 출력
void printScreen(char res) {
	int px = 0;

	if (res == 0) {
		printf("\n");
		printf("%40s", " < 원본 이미지 화면 > ");
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				px = outImage[i][k];
				SetPixel(hdc, k + 50, i + 400, RGB(px, px, px));		// hdc가 제공해주는 함수		// i, k -> k+50, i+250
			}
		}
	}
	else {
		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				px = outImage[i][k];
				SetPixel(hdc, k + 600, i + 400, RGB(px, px, px));
			}
		}
	}
}

// 원본 이미지
/*
void originImage() {
	system("cls");

	printf("파일명 : %s \n\n", imgname);
	printf("기존 이미지\n");
	equalImage(1);
}
*/


//// ******* 영상 처리 함수 모음 ******* ////


// 이전 이미지
void equalImage() {		// previousImage()
	system("cls");
	printMenu();
	printf("%40s %s %s", "선택한 파일명 :", tmpName, "\t");

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
//	printf("%40s", " < 원본 이미지 화면 > ");
	printf("\n");
	printScreen(0);
}

// 이미지 밝기 값 조절
void brightControlImage() {
	int value;

	system("cls");
	printMenu();
	printf("%40s %s", "선택한 파일명 :", tmpName);

	printf("\t\t  밝기 조절 값 --> ");
	scanf("%d", &value);
	printf("\n");

	equalImage();

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
		printf("%40s", " < 밝기 ");
		printf("%d 증가 화면 >", value);
		printScreen(1);
	}
	else if (value < 0) {
		printf("%40s", " < 밝기 ");
		printf("%d 감소 화면 >", value); 
		printScreen(1);
	}
	else {
		printf("다시 입력하세요!\n");
	}
}

// 이미지 선명도 조절
void clearControlImage() {
	char choice = 0;
	int value = 0;

	system("cls");
	printMenu();
	printf("%40s %s", "선택한 파일명 :", tmpName);

	printf("\t\t[선명도 조절] 8.선명하게  9.희미하게 ");
	scanf("%c", &choice);

	if (choice == 8) {		// 선명하게
		printf("\t  선명도 조절 값 --> ");
		scanf("%d", &value);
		printf("\n");

		equalImage();

		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				int px = inImage[i][k] * value;		// px : pixel

				if (px > 255)
					px = 255;
				else if (px < 0)
					px = 0;
				else
					outImage[i][k] = px;
			}
		}
		if (value > 0) {
			printf("%40s", " < 선명도 ");
			printf("%d 증가 화면 >", value);
			printScreen(1);
		}
		else {
			printf("다시 입력하세요!\n");
		}
	}
	else if (choice == 9) {		// 희미하게
		printf("\t  선명도 조절 값 --> ");
		scanf("%d", &value);
		printf("\n");

		equalImage();

		for (int i = 0; i < ROW; i++) {
			for (int k = 0; k < COL; k++) {
				int px = inImage[i][k] / (float)value;		// px : pixel

				if (px > 255)
					px = 255;
				else if (px < 0)
					px = 0;
				else
					outImage[i][k] = px;
			}
		}
		if (value < 0) {
			printf("%40s", " < 선명도 ");
			printf("%d 감소 화면 >", value);
			printScreen(1);
		}
		else {
			printf("다시 입력하세요!\n");
		}
	}

}

// 이미지 반전 처리
void reverseImage() {
	equalImage();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printf("\t\t\t\t < 영상 반전 화면 > ");
	printScreen(1);
}

// 이미지 흑백 처리
void grayScaleImage() {
	equalImage();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k];

			if (px >= 128) {
				px = 255;
			}
			else if (px < 128) {
				px = 0;
			}

			outImage[i][k] = px;
		}
	}
	printf("\t\t\t\t < 영상 흑백 처리 화면 > ");
	printScreen(1);
}

// 이미지 좌우 미러링
void L_R_mirroring() {
	equalImage();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[i][COL - 1 - k];	// (최대열 - 1) - 반복자
		}
	}
	printf("\t\t\t\t < 영상 좌우 미러링 화면 > ");
	printScreen(1);
}

// 이미지 상하 미러링
void T_B_mirroring() {
	equalImage();

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[ROW - 1 - i][k];		// (최대행 - 1) - 반복자
		}
	}

	printf("\t\t\t\t < 영상 상하 미러링 화면 > ");
	printScreen(1);
}

// 결과 이미지 오른쪽으로 90도 회전
void turn90Right() {
	equalImage();
	printf("------------------------------------------------\n");
}

// 결과 이미지 왼쪽으로 90도 회전
void turn90Left() {
	equalImage();
	printf("------------------------------------------------\n");
}

// 결과 이미지 180도 회전


// 평균값으로 흑백처리


// 중앙값으로 흑백처리

