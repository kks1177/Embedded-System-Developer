// function.cpp
// 함수

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

int plusNumber(int n1, int n2);

int main()
{
	int num1 = 100, num2 = 200;
	int result;

	// 두 숫자를 더하는 알고리즘을 구현
	result = plusNumber(num1, num2);

	// 출력
	printf("%d + %d = %d \n", num1, num2, result);
}


// 두 숫자를 더하는 알고리즘을 구현
int plusNumber(int n1, int n2) {
	int res;		// result -> res
	res = n1 + n2;

	return res;
}

