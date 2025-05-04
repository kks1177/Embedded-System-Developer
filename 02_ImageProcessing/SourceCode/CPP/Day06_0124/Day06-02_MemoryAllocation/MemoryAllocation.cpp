// MemoryAllocation.cpp
// 메모리 할당

// Pointer01.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// 동적 배열 --> 사용자가 입력하는 크기만큼 ...
	int SIZE;
	printf("몇 개 : ");
	scanf("%d", &SIZE);

	int* p;
	p = (int*)malloc(SIZE * sizeof(int));		// malloc : MemoryAllocate(메모리 할당)

	int value = 200;
	for (int i = 0; i < SIZE; i++) {
		p[i] = value++;
	}
	printf("%d \n", p[SIZE-1]);		// SIZE-1 : 마지막 위치의 값
	
	free(p);		// 메모리 할당 해제(반환) -> 운영체제한테

	printf("프로그램 끝! \n");
}


