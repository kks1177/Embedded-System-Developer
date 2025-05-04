// BinaryFileProcessing.cpp
// 2진파일 처리

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;	// C++ 추가 기능

char filename[100];
const int ROW = 512, COL = 512;
unsigned char inImage[ROW][COL];		// input
unsigned char outImage[ROW][COL];		// output

void printScreen();
void openImage();
void equalImage();
void addImage();

int main()
{
	//// 파일 열기 ////
	openImage();

	//// 영상 처리 ////
	//addImage();


	printf("처리 끝~");
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
	printScreen();
}


// ***** 영상 처리 함수 모음 ***** //
// 
void equalImage() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
}

// 이미지 밝기 조절
void addImage() {
	int value;
	printf("밝게할 값 --> ");
	scanf("%d", &value);

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = inImage[i][k] + value;		// px : pixel,		unsigned int 안하는 이유 확인!!!
		
			if (px > 255)
				px = 255;
			else if (px < 0)
				px = 0;
			outImage[i][k] = px;
		}
	}
	printScreen();
}

