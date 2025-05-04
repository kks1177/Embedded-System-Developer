// Quiz04-03.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;	// C++ 추가 기능

// 전역 변수부 (중요!)
const char filename[100] = "C:\\images\\Etc_Raw(squre)\\flower512.raw";
const int ROW = 512, COL = 512;
unsigned char image[ROW][COL];

void printScreen();
void plusScreen();
void subScreen();
void GrayScaleScreen();

int main()
{
	//// 파일 열기 ////
	FILE* rfp = fopen(filename, "rb");		// rb: Read Binary

	// 512x512 번 반복해서 읽거나, 한방에 512,512 읽거나
	fread(image, sizeof(unsigned char), ROW * COL, rfp);

	//// 파일 닫기 ////
	fclose(rfp);

	printf("\n\t < 원본 영상 > \n");
	printScreen();
	printf("======================================");

	plusScreen();
	subScreen();
	GrayScaleScreen();

	printf("\n처리 끝~\n");
}

// 이미지를 화면 출력
void printScreen() {
	for (int i = 100; i < 110; i++) {
		for (int k = 100; k < 110; k++) {
			printf("%3d ", image[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

// 영상 50 밝게 하기
void plusScreen() {
	int value = 50;
	for (int i = 100; i < 110; i++) {
		for (int k = 100; k < 110; k++) {
			int px = image[i][k] + value;
			if (px > 255) {
				image[i][k] = 255;
			}
			else {
				image[i][k] += value;
			}
		}
	}
}

// 영상 100 어둡게 하기
void subScreen() {
	int value = 100;
	for (int i = 100; i < 110; i++) {
		for (int k = 100; k < 110; k++) {
			int px = image[i][k] - value;
			if (px > 255) {
				image[i][k] = 255;
			}
			else {
				image[i][k] -= value;
			}
		}
	}
}

// 영상 흑백 처리
void GrayScaleScreen() {
	int value = 127;
	for (int i = 0; i < 110; i++) {
		for (int k = 0; k < 110; k++) {
			int px = image[i][k];
			if (px > value) {
				image[i][k] = 255;
			}
			else {
				image[i][k] = 0;
			}
		}
	}
}


