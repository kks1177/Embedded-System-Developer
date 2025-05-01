// GreyVideoProcessing_Alpha1-1.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
using namespace std;	// C++ 추가 기능

char filename[100];
const int ROW = 512, COL = 512;
unsigned char inImage[ROW][COL];		// input
unsigned char outImage[ROW][COL];		// output

void printScreen();
void openImage();
void equalImage();				// 원본

void brightControlImage();		// 밝기 조절
void reverseImage();			// 반전
void grayScaleImage();			// 흑백

// 메뉴 설명		// 자주 수정해야 하므로 상단에 배치
void printMenu() {
	puts("\n ## 그레이 영상처리 (Alpha 1) ##\n");
	puts(" 0.열기  1.저장  9.종료\n");
	puts(" A.동일  B.밝게/어둡게  C.반전  ....\n");
}
// 메뉴 선택
void choiceMenu() {
	char inKey = 0;		// 키보드로 입력 받는 변수

	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		system("cls");

		switch (inKey) {
		case '0':	openImage(); 	break;
		case '9':	break;
		case 'A':
		case 'a':
			equalImage();
			break;
		case 'B':
		case 'b':
			brightControlImage();
			break;
		case 'C':
		case 'c':
			reverseImage();
			break;
		}
	}
}

int main()
{
	choiceMenu();

	printf("안녕히 가세요~");
}

// 이미지를 화면 출력
void printScreen() {
	for (int i = 100; i < 110; i++) {
		for (int k = 100; k < 110; k++) {
			printf("%3d ", outImage[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

// 파일 열기
void openImage() {
	char fullName[100] = "C:\\images\\Pet_RAW(squre)\\Pet_RAW(512x512)\\";		// 끝에 \\ 붙여야함!
	char tmpName[100];

	printf(" 파일명 --> ");	// cat01, dog13
	scanf("%s", tmpName);
	strcat(fullName, tmpName);		// strcat : 문자열을 이어줌
	strcat(fullName, "_512.raw");
	strcpy(filename, fullName);

	//// 파일 열기 ////
	FILE* rfp = fopen(filename, "rb");		// rb: Read Binary

	// 512x512 번 반복해서 읽거나, 한방에 512,512 읽거나
	fread(inImage, sizeof(unsigned char), ROW * COL, rfp);

	//// 파일 닫기 ////
	fclose(rfp);

	equalImage();
}


// ***** 영상 처리 함수 모음 ***** //
// 
void equalImage() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printScreen();
}

// 이미지 밝기 조절
void brightControlImage() {
	int value;
	printf("밝게할 값 --> ");
	scanf("%d", &value);

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
	printScreen();
}

// 이미지 반전 처리
void reverseImage() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printScreen();
}

// 이미지 흑백 처리


// 이미지 좌우 미러링


// 이미지 상하 미러링


// 결과 이미지 90도 회전


// 결과 이미지 180도 회전


// 평균값으로 흑백처리


// 중앙값으로 흑백처리

