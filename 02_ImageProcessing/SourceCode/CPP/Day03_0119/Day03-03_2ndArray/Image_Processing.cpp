// Image_Processing.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <time.h>		// rand
#include <stdlib.h>	
using namespace std;

// 전역 변수
const int ROW = 8, COL = 8;
unsigned char m_image[ROW][COL];

int main()
{
	// 이미지 배열 초기화
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			m_image[i][k] = 0;
		}
	}

	// 이미지 파일 --> 배열 Loading
	unsigned char pixel;	// 한 한 점의 값 (0~255)
	srand(time(NULL));		// 랜덤 초기화
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			pixel = rand() % 256;		// 파일에서 한 점 읽기
			m_image[i][k] = pixel;
		}
	}
	
	// 이미지를 화면 출력
	/*
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf("%3d ", m_image[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
	*/




	////////// 영상 처리 ////////////
	/// (1) 영상을 밝게 처리 --> 값을 증가 (50)
	int value = 50;
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = m_image[i][k] + value;
			if (px > 255) {
				m_image[i][k] = 255;
			}
			else
				m_image[i][k] += value;
		}
	}

	// 이미지를 화면 출력
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf("%3d ", m_image[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
}


