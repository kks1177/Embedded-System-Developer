// Mission1_ImageProcessing.cpp
// 0119_미션	

// 미션1. 20 크기 배열 준비, 각 배열에 1~99까지 랜덤 값, 배열 출력
/*	
* (미션1-1.) 배열에서 가장 큰 값과 그 위치 출력
* (미션1-2.) 배열에서 가장 작은 값과 그 위치 출력
* (미션1-3.) 배열의 평균값 출력
* (<심화>미션1-4.) 배열의 중앙값 출력
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>		// rand
#include <stdlib.h>		// rand
using namespace std;

const int SIZE = 20;
int ary[SIZE];
int temp = 0;

void aryInit();		// 배열 초기화
void arrayRand();	// 배열 랜덤값
void printArray();	// 배열 출력

void findMaxValue();	// 배열 속 가장 큰 값과 해당 위치 찾기
void findMinValue();	// 배열 속 가장 작은 값과 해당 위치 찾기
void aryAvr();			// 배열 평균값
void aryMid();			// 배열 중앙값


int main()
{
	// 배열 초기화
	aryInit();

	// 배열 랜덤 값
	arrayRand();

	// 배열 출력
	printArray();
	printf("\n\n");

	// 배열 속 가장 큰 값과 해당 위치 찾기
	findMaxValue();
	// 배열 속 가장 작은 값과 해당 위치 찾기
	findMinValue();
	
	// 배열 평균값
	aryAvr();

	// 배열 중앙값
	aryMid();
}


// 배열 초기화
void aryInit() {
	for (int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

// 배열 랜덤값
void arrayRand() {
	unsigned char data;
	srand((int)time(NULL));		// 랜덤 초기화
	for (int i = 0; i < SIZE; i++) {
		data = rand() % 100;		// 파일에서 한 점 읽기
		ary[i] = data;
	}
}

// 배열 출력
void printArray() {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", ary[i]);
	}
}

// 배열 속 가장 큰 값과 해당 위치 찾기
void findMaxValue() {
	int maxValue = ary[0];
	for (int i = 0; i < SIZE; i++) {
		if (ary[i] > maxValue) {
			maxValue = ary[i];
			temp = i;
		}
	}
	printf(" 가장   큰 값 : %d, 위치 : %d\n", maxValue, temp);
}

// 배열 속 가장 작은 값과 해당 위치 찾기
void findMinValue() {
	int minValue = ary[0];
	for (int i = 0; i < SIZE; i++) {
		if (ary[i] < minValue) {
			minValue = ary[i];
			temp = i;
		}
	}
	printf(" 가장 작은 값 : %d, 위치 : %d\n", minValue, temp);
}

// 배열 평균값
void aryAvr() {
	int hap = 0;
	int avr = 0;

	for (int i = 0; i < SIZE; i++) {
		hap += ary[i];
	}
	avr = hap / SIZE;
	printf("\n 평균 값 : %d \n", avr);
}

// 배열 중앙값
void aryMid() {
	int mid = 0;
	int temp = 0;
	int arySort1[SIZE] = {0, 0};

	//// 배열 정렬 ////
	for (int i = 0; i < SIZE-1; i++) {
		for (int k = i+1; k < SIZE; k++) {
			if (ary[i] > ary[k]) {
				temp = ary[i];
				ary[i] = ary[k];
				ary[k] = temp;
			}
		}
	}
	printf("\n 중앙값 : %d\n", ary[(SIZE - 1) / 2]);
}
