// Quiz03-03.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <time.h>		// rand
#include <stdlib.h>	
using namespace std;

// **** 전역 변수부 (중요!) **** //
const int ROW = 8, COL = 8;
unsigned char m_image[ROW][COL];

// **** 사용자 정의 함수 **** //
//void cleanScreen();		// 화면 초기화
void image_arr_init();		// 배열 초기화
void imageToArray();		// 배열 랜덤값
void print_screen();		// 이미지 화면 출력

void addImage();			// (1) 영상을 밝게 처리 --> 값을 증가 (50)
void subImage();			// (퀴즈3-1.) 영상을 어둡게 처리 --> 값을 감소 (100)
void reverseImage();		// (퀴즈3-2.) 영상 반전 --> if, value:50 => value:205
void grayScaleImage();		// (퀴즈 3-3.) 영상 흑백처리 --> 0 or 255로만
void L_R_mirroring();		// (퀴즈 3-4.) 영상 좌우 미러링  -->  2장의 이미지가 필요
void T_B_mirroring();		// (퀴즈 3-5.) 영상 상하 미러링
void turnRight();			// (심화 퀴즈 3-6.)결과 이미지 오른쪽으로 90도 회전
void turnLeft();			// (심화 퀴즈 3-6-2.)결과 이미지 왼쪽으로 90도 회전

int main()
{
	image_arr_init();
	imageToArray();
	
	// (원본)이미지 화면
	printf(" < 원본 이미지 화면 > \n");
	print_screen();


	////////// 영상 처리 ////////////
	//// (1) 영상을 밝게 처리 --> 값을 증가 (50)
//	addImage();

	//// (퀴즈3-1.) 영상을 어둡게 처리 --> 값을 감소 (100)
//	subImage();

	//// (퀴즈3-2.) 영상 반전 --> if, value:50 => value:205
//	reverseImage();

	//// (퀴즈 3-3.) 영상 흑백처리 --> 0 or 255로만
//	grayScaleImage();

	//// (퀴즈 3-4.) 영상 좌우 미러링  -->  2장의 이미지가 필요
//	L_R_mirroring();

	//// (퀴즈 3-5.) 영상 상하 미러링
//	T_B_mirroring();

	//// (심화 퀴즈 3-6.)  오른쪽으로 90도 회전
	turnRight();

	//// (심화 퀴즈 3-6-2.)  왼쪽으로 90도 회전
	turnLeft();
}

// 화면 초기화
/*
void cleanScreen() {
	Sleep(3000);		// 2초 딜레이
	system("cls");		// 화면 초기화
}
*/

// 배열 초기화
void image_arr_init() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			m_image[i][k] = 0;
		}
	}
}

// 배열 랜덤값
void imageToArray() {
	// 이미지 파일 --> 배열 Loading
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
void print_screen() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf("%3d ", m_image[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
}

// (1) 영상을 밝게 처리 --> 값을 증가 (50)
void addImage() {
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
}

// (퀴즈3-1.) 영상을 어둡게 처리 --> 값을 감소 (100)
void subImage() {
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
			else
				m_image[i][k] -= value;
		}
	}
	printf(" < 영상 100 감소 화면 > \n");
	print_screen(); 
}

// (퀴즈3-2.) 영상 반전 --> if, value:50 => value:205
void reverseImage() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = 255 - m_image[i][k];
			m_image[i][k] = px;
		}
	}
	printf(" < 영상 반전 화면 > \n");
	print_screen();
}

// (퀴즈 3-3.) 영상 흑백처리 --> 0 or 255로만
void grayScaleImage() {
	int value = 127;
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int px = m_image[i][k];
			if (px > value) {
				m_image[i][k] = 255;
			}
			else if (px <= value) {
				m_image[i][k] = 0;
			}
		}
	}
	printf(" < 영상 흑백 처리 화면 > \n");
	print_screen();
}

// (퀴즈 3-4.) 영상 좌우 미러링  -->  2장의 이미지가 필요
void L_R_mirroring() {
	unsigned char temp[ROW][COL] = { 0,0 };

	for (int i = 0; i < ROW; i++) 
		for (int k = 0; k < COL; k++) 
			temp[i][k] = m_image[i][k];

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int lr_mirror = (COL - 1) - k;

			m_image[i][k] = temp[i][lr_mirror];
		}
	}
	printf(" < 영상 좌우 미러링 화면 > \n");
	print_screen();
}

// (퀴즈 3 - 5.) 영상 상하 미러링
void T_B_mirroring() {
	unsigned char temp[ROW][COL] = { 0,0 };

	for (int i = 0; i < ROW; i++)
		for (int k = 0; k < COL; k++)
			temp[i][k] = m_image[i][k];

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			int tb_mirror = (ROW - 1) - i;

			m_image[i][k] = temp[tb_mirror][k];
		}
	}

	printf(" < 영상 상하 미러링 화면 > \n");
	print_screen();
}

// (심화 퀴즈 3-6.)결과 이미지 오른쪽으로 90도 회전
void turnRight() {
	printf(" < 영상 90도 오른쪽으로 회전 화면 > \n");
	print_screen();
}

// (심화 퀴즈 3-6-2.)결과 이미지 왼쪽으로 90도 회전
void turnLeft() {
	printf(" < 영상 90도 왼쪽으로 회전 화면 > \n");
	print_screen();
}


