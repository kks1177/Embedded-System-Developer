// operator.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	int intNum1, intNum2;		// 변수 == 그릇
	float result;

	printf("숫자1 입력 : ");
	scanf("%d", &intNum1);
	printf("숫자2 입력 : ");
	scanf("%d", &intNum2);

	result = intNum1 + intNum2;
	printf("%d + %d = %.1f \n", intNum1, intNum2, result);

	result = intNum1 - intNum2;
	printf("%d - %d = %.1f \n", intNum1, intNum2, result);

	result = intNum1 * intNum2;
	printf("%d * %d = %.1f \n", intNum1, intNum2, result);

	if (intNum2 != 0) {
		result = (float)intNum1 / intNum2;								// 정수와 정수의 연산 --> 정수
		printf("%d / %d = %.1f \n", intNum1, intNum2, result);			// 정수와 실수의 연산 --> 실수
	}
	else
		printf("0으로 나누면 안됩니다. \n");

	if (intNum2 != 0) {
		result = intNum1 % intNum2;
		printf("%d %% %d = %.1f \n", intNum1, intNum2, result);
	}
	else
		printf("0으로 나머지 값은 안됩니다. \n");
}

