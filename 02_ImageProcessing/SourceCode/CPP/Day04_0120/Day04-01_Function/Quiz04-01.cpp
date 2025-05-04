// Quiz04-01.cpp
// 퀴즈1.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

int plusNumber(int n1, int n2);
int subNumber(int n1, int n2);		// sub : subtract
int mulNumber(int n1, int n2);		// mul : multiply
float divNumber(int n1, int n2);	// div : divide
int remNumber(int n1, int n2);		// rem : remainder 

int main()
{
	int num1 = 100, num2 = 200;
	int result;
	float result2;

	// 더하기
	result = plusNumber(num1, num2);
	printf("%d + %d = %d \n", num1, num2, result);

	// 빼기
	result = subNumber(num1, num2);
	printf("%d - %d = %d \n", num1, num2, result);

	// 곱하기
	result = mulNumber(num1, num2);
	printf("%d * %d = %d \n", num1, num2, result);

	// 나누기
	if (num2 != 0) {
		result2 = divNumber(num1, num2);
		printf("%d / %d = %.1f \n", num1, num2, result2);
	}
	else
		printf("이러지 맙시다.... \n");

	// 나머지
	result = remNumber(num1, num2);
	printf("%d %% %d = %d \n", num1, num2, result);
}


// 두 숫자를 더하는 알고리즘을 구현
int plusNumber(int n1, int n2) {
	int res;		// result -> res
	res = n1 + n2;

	return res;
}
// 두 숫자를 빼는 알고리즘을 구현
int subNumber(int n1, int n2) {
	int res;
	res = n1 - n2;

	return res;
}
// 두 숫자를 곱하는 알고리즘을 구현
int mulNumber(int n1, int n2) {
	int res;
	res = n1 * n2;

	return res;
}
// 두 숫자를 나누는 알고리즘을 구현
float divNumber(int n1, int n2) {
	float res;
	res = (float)n1 / n2;

	return res;
}
// 두 숫자의 나머지 알고리즘을 구현
int remNumber(int n1, int n2) {
	int res;
	res = n1 % n2;

	return res;
}
