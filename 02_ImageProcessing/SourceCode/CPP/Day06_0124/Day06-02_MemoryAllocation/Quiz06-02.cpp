// Quiz06-02.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int SIZE;
	int tmp = 0;

	printf("크기 입력 : ");
	scanf("%d", &SIZE);

	int* p1, * p2;
	p1 = (int*)malloc(SIZE * sizeof(int));
	p2 = (int*)malloc(SIZE * sizeof(int));

	for (int i = 0; i < SIZE; i++) {
		p1[i] += i;
	}
	for (int i = -1; i > -SIZE; i++) {
		p2[i] += i;
	}

	for (int i = 0; i < SIZE; i++) {
		tmp = p1[i];
		p1[i] = p2[i];
		p2[i] = tmp;
	}

	printf("%s \n", p1);
	printf("%s \n", p2);

	free(p1);
	free(p2);
}