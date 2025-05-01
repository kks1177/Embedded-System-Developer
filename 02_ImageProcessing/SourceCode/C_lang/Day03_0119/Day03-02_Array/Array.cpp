// Array.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
using namespace std;

int main()
{
	// for 문은 배열을 위해 존재
	const int SIZE = 5;		// const : 상수화시킴
	int ary[5];
	int hap = 0;

	for (int i = 0; i < SIZE; i++) {			// i --> 배열의 첨자 용도
		scanf("%d", &ary[i]);
		hap += ary[i];
	}
	printf("합계 --> %d \n", hap);
}

