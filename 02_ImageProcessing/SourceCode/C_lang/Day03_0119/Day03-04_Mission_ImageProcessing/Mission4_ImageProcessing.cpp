// Mission4_ImageProcessing.cpp

// 미션4. 1000 크기 배열 준비, 1~1000까지의 숫자 중 소수 저장
// 배열에서 소수의 합계를 내고 출력

# define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define SIZE 1000

int main()
{
	int ary[SIZE] = { 0, };
	int cnt = 0;		// 나누어 떨어지는지 확인하기 위한 변수 생성

	// 소수만 이므로 1 제외
	for (int i = 2; i <= SIZE; i++) {
		for (int k = 2; k < i; k++) {
			// 나누어 떨어진[다면 i와 k 사이에 약수가 존재함을 의미
			if (i % k == 0) {
				cnt = 1;
				break;
			}
		}
		// 약수가 없으면 소수
		if (cnt == 0) {
			printf("%3d ", i);
			ary
		}
		cnt = 0;
	}

	for (int i = 0; i < )
	printf("\n\n 1~1000까지 소수의 합계 : %d \n", hap);

	return 0;
}


