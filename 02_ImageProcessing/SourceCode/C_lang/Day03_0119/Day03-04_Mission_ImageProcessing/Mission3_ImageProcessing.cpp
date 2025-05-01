// Mission3_ImageProcessing.cpp

// 미션3. 5x7 크기의 2차원 배열 2개 준비, 0~255 사이의 랜덤 값
//		5x7 크기의 결과 저장할 빈 배열 1개 준비, 출력하여 확인
/*
* (미션3-1.) 두 이미지 중첩, 결과 이미지에 저장
* (미션3-2.) 두 이미지 중, 평균값 높은 이미지 출력
* (미션3-3.) 두 이미지 중, 중앙값 높은 이미지 출력
* (미션3-4.) 결과 이미지 흑백처리
* (미션3-5.) 결과 이미지 평균값으로 흑백처리
* (미션3-6.) 결과 이미지 중앙값으로 흑백처리
* (미션3-7.) 결과 이미지 90도 회전
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

const int ROW = 5, COL = 7;			// 행 : 5, 열 : 7
const int ARY_SIZE = ROW * COL;		// 배열 사이즈 크기
unsigned char m_image1[ROW][COL] = { 0,0 };				// 원본 이미지 배열1 초기화
unsigned char m_image2[ROW][COL] = { 0,0 };				// 원본 이미지 배열2 초기화
unsigned char tempArrayImage[ROW][COL] = { 0,0 };		// 결과 저장용 빈 배열 초기화

void cleanScreen();			// 화면 초기화
void imageAryInit();		// 배열 초기화
void imageToArray();		// 배열 랜덤값
void printScreen1();		// 이미지 화면1 출력
void printScreen2();		// 이미지 화면2 출력
void printResScreen();		// 결과 화면 출력
void full_image();			// 전체 이미지 화면 출력
void overlapImage();		// 두 원본 이미지 배열 중첩
void findHighAvr_image();	// 평균값 높은 이미지 출력
void findHighMid_image();	// 중앙값 높은 이미지 출력
void blackWhite();			// 결과 이미지 출력
void turnRight();			// 결과 이미지 오른쪽으로 90도 회전
void turnLeft();			// 결과 이미지 왼쪽으로 90도 회전

int main()
{
	printf("============< 초기 상태 >============\n");
	imageAryInit();
	imageToArray();
	full_image();

	cleanScreen();

	// 미션3-1. 이미지 중첩
	printf("============< 미션 3-1 >============\n");
	overlapImage();
	full_image();

	cleanScreen();

	// 미션3-2. 평균값 높은 이미지 출력
	printf("============< 미션 3-2 >============\n");
	findHighAvr_image();

	cleanScreen();

	// 미션3-3. 중앙값 높은 이미지 출력
	printf("============< 미션 3-3 >============\n");
	findHighMid_image();

	/*
	cleanScreen();

	// 미션3-4. 결과 이미지 흑백 처리
	printf("============< 미션 3-4 >============\n");
	blackWhite();
	printResScreen();

	cleanScreen();

	// 미션3-5. 결과 이미지 평균값으로 흑백처리
	printf("============< 미션 3-5 >============\n");

	cleanScreen();

	// 미션3-6. 결과 이미지 중앙값으로 흑백처리
	printf("============< 미션 3-6 >============\n");

	cleanScreen();

	// 미션3-7-01 결과 이미지 오른쪽으로 90도 회전
	printf("============< 미션 3-7-01 >============\n");
	turnRight();

	cleanScreen();

	// 미션3-7-02 결과 이미지 왼쪽으로 90도 회전
	printf("============< 미션 3-7-02 >============\n");
	turnLeft();
	*/
}


// 화면 초기화
void cleanScreen() {
	Sleep(3000);		// 2초 딜레이
	system("cls");		// 화면 초기화
}

// 배열 초기화
void imageAryInit() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			m_image1[i][k] = 0;
			m_image2[i][k] = 0;
			tempArrayImage[i][k] = 0;
		}
	}
}

// 배열 랜덤값 
void imageToArray() {
	unsigned char data;
	srand((int)time(NULL));
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			data = rand() % 256;
			m_image1[i][k] = data;
		}
	}
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			data = rand() % 256;
			m_image2[i][k] = data;
		}
	}
}

// 이미지 화면1 출력
void printScreen1() {
	// 원본1 이미지 화면 출력
	printf("\t< 이미지 1 화면 > \n");
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %3d ", m_image1[i][k]);
		}
		printf("\n");
	}
}

// 이미지 화면2 출력
void printScreen2() {
	printf("\n");
	// 원본2 이미지 화면 출력
	printf("\t< 이미지 2 화면 > \n");
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %3d ", m_image2[i][k]);
		}
		printf("\n");
	}
}

// 결과 이미지 화면 출력
void printResScreen() {
	printf("\n -----------------------------------");

	// 결과 저장용 배열 출력
	printf("\n\n <  결과 저장용 이미지 화면 > \n");
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			printf(" %3d ", tempArrayImage[i][k]);
		}
		printf("\n");
	}
	printf("\n\n");
}

// 전체 이미지 화면 출력 
void full_image() {
	printScreen1();
	printScreen2();
	printResScreen();
}

// 미션3-1
// 두 원본 이미지 중첩
void overlapImage() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			tempArrayImage[i][k] = m_image1[i][k] + m_image2[i][k];
		}
	}
}

// 미션3-2
// 평균값 높은 이미지 출력
void findHighAvr_image() {
	int hap1 = 0, hap2 = 0;
	float avr1 = 0, avr2 = 0;

	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			hap1 += m_image1[i][k];
			hap2 += m_image2[i][k];
		}
	}
	avr1 = (float)(hap1 / ARY_SIZE);
	avr2 = (float)(hap2 / ARY_SIZE);

	//// 평균값 비교 및 이미지 출력 ////
	if (avr1 > avr2) {
		printScreen1();
	}
	else if (avr1 < avr2) {
		printScreen2();
	}
	else
		printf("평균값 같음 \n");

	printf("\n\n --- 평균값 ---");
	printf("\n이미지1 : %.2f, 이미지2 : %.2f\n", avr1, avr2);
}

// 미션3-3
// 중앙값 높은 이미지 출력
void findHighMid_image() {
	int mid1 = 0, mid2 = 0;		// 중앙값1, 2
	int temp = 0;
	int count = 0;
	int image1_sort[ARY_SIZE] = {0, 0};
	int image2_sort[ARY_SIZE] = {0, 0};

	/// 2차원 배열 -> 1차원 배열 변환 ////
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			image1_sort[count] = m_image1[i - 1][k - 1];
			image2_sort[count] = m_image2[i - 1][k - 1];
			count += 1;
		}
	}

	//// 배열 정렬 ////
	for (int i = 0; i < ARY_SIZE-1; i++) {
		for (int k = i+1; k < ARY_SIZE; k++) {
			if (image1_sort[i] > image1_sort[k]) {
				temp = image1_sort[i];
				image1_sort[i] = image1_sort[k];
				image1_sort[k] = temp;
			}
		}
	}
	for (int i = 0; i < ARY_SIZE - 1; i++) {
		for (int k = i + 1; k < ARY_SIZE; k++) {
			if (image2_sort[i] > image2_sort[k]) {
				temp = image2_sort[i];
				image2_sort[i] = image2_sort[k];
				image2_sort[k] = temp;
			}
		}
	}
	//// 변수에 중앙값 저장 ////
	mid1 = image1_sort[(ARY_SIZE - 1) / 2];
	mid2 = image2_sort[(ARY_SIZE - 1) / 2];

	//// 중앙값 비교 및 이미지 출력 ////
	if (mid1 >= mid2) {
		printScreen1();
	}
	else if (mid1 < mid2) {
		printScreen2();
	}
	else
		printf("중앙값 같음 \n");

	printf("\n\n --- 중앙값 ---");
	printf("\n이미지1 : %d, 이미지2 : %d\n", mid1, mid2);
}

// 미션3-4
// 결과 이미지 흑백 처리
void blackWhite() {
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (tempArrayImage[i][k] <= 127) {
				tempArrayImage[i][k] = 0;
			}
			else
				tempArrayImage[i][k] = 255;
		}
		printf("\n");
	}
	printf("\n");
}

// 미션3-5
// 결과 이미지 평균값으로 흑백처리
//void avrBlackWhite() {
//	
//}

// 미션 3-6
// 결과 이미지 중앙값으로 흑백처리

// 미션 3-7-01
// 결과 이미지 오른쪽으로 90도 회전
void turnRight() {
	for (int i = 0; i < COL; i++) {
		for (int k = (ROW - 1); k >= 0; k--) {
			printf("%3d ", tempArrayImage[k][i]);
		}
		printf("\n");
	}
	printf("\n");
}

// 미션 3-7-02
// 결과 이미지 왼쪽으로 90도 회전
void turnLeft() {
	for (int i = 0; i < COL; i++) {
		for (int k = (ROW - 1); k >= 0; k--) {
			printf("%3d ", tempArrayImage[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

