// Mission2_ImageProcessing.cpp
// 0119_미션

// 미션2. 5x8크기의 2차원 배열 준비, 0~255까지 랜덤 값, 배열 출력
/*
* (미션2-1.) 이미지 50 밝게 처리
* (미션2-2.) 이미지 100 어둡게 처리 
* (미션2-3.) 이미지 완전 흑백 처리
* (미션2-4.) 이미지 반전 처리
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>		// rand
#include <stdlib.h>		// rand
using namespace std;

// 전역 변수
const int ROW = 5, COL = 8;
unsigned char m_image[ROW][COL] = { 0,0 };

void imageAryInit();		// 이미지 배열 초기화
void imageToArray();		// 이미지 파일 --> 배열
void printScreen();			// 이미지 화면 출력

int main()
{
	// 이미지 배열 초기화
	imageAryInit();

	// 이미지 파일 --> 배열
	imageToArray();

	// (원본) 이미지 화면
	printf(" < (원본) 이미지 화면 > \n");
	printScreen();

	
	/////// 영상 처리 ///////
	//// (미션2-1.) 영상을 50 밝게 처리
	/*
	int value = 50;
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = m_image[i][k] + value;
			if (px > 255) {
				m_image[i][k] = 255;
			}
			else if (px < 0) {
				m_image[i][k] = 0;
			}
			else {
				m_image[i][k] += value;
			}
		}
	}
	printf(" < 영상 50 증가 화면 > \n");
	printScreen();
	*/

	//// (미션2-2.) 영상을 100 어둡게 처리
	/*
	int value = 100;
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = m_image[i][k] - value;
			if (px > 255) {
				m_image[i][k] = 255;
			}
			else if (px < 0) {
				m_image[i][k] = 0;
			}
			else {
				m_image[i][k] -= value;
			}
		}
	}
	printf(" < 영상 100 감소 화면 > \n");
	printScreen();
	*/

	//// (미션2-3.) 영상 완전 흑백 처리 
	/*
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = m_image[i][k];
			if (px > 127) {
				m_image[i][k] = 255;
			}
			else {
				m_image[i][k] = 0;
			}
		}
	}
	printf(" < 영상 흑백 처리 화면 > \n");
	printScreen();
	*/

	//// (미션2-4.) 이미지 반전 처리
	/*
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = 255 - m_image[i][k];
			m_image[i][k] = px;
		}
	}
	printf(" < 영상 반전 처리 화면 > \n");
	printScreen();
	*/

}



// 이미지 배열 초기화
void imageAryInit() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			m_image[i][k] = 0;
		}
	}
}

// 이미지 파일 --> 배열 Loading
void imageToArray() {
	unsigned char pixel;	// 한 한 점의 값 (0~255)
	srand(time(NULL));		// 랜덤 초기화
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			pixel = rand() % 256;		// 파일에서 한 점 읽기
			m_image[i][k] = pixel;
		}
	}
}

// 이미지 화면 출력
void printScreen() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %3d ", m_image[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
}



