// MemoryAllocation.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int row = 5, col = 9;	// 가변적 숫자
	// 최종 int ary[row][col];

	int** p;
	//malloc(row * sizeof(int));		// 심각한 오류.. 당장은 돌아가지만 char형으로 할 경우 블루스크린이 뜸
	
	p = (int**)malloc(row * sizeof(int*));
	for (int i = 0; i < row; i++) {
		p[i] = (int*)malloc(col * sizeof(int));
	}

	// p[3][4] 등등을 활용..

	// 메모리 해제
	for (int i = 0; i < row; i++) {
		free(*p[i]);
	}
	free(p);
}

