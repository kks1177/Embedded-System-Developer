// for_while.cpp

#include <stdio.h>

int main()
{
	// 1부터 10까지 출력해라.
	/*
	 //Ctrl + k + c : 선택영역 주석
	 //Ctrl + k + u : 선택영역 주석 해제
	for (int i = 1; i < 11; i++) {
		printf("%d\n", i);
	}
	*/

	/*
	printf("%d\n", 1);
	printf("%d\n", 2);
	printf("%d\n", 3);
	*/

	// 100부터 1까지의 합계는?
	/*
	int hap = 0;
	for (int i = 100; i >= 1; i--) {
		hap += i;
	}
	printf("%d ", hap);
	*/

	// 1,1 --> 1,2 --> 1,3 --> 2,1 --> 2,2 --> 2,3, .... --> 4,3 출력
	for (int i = 1; i <= 4; i++) {
		for (int k = 1; k <= 3; k++) {
			printf("%d,%d \n", i, k);
		}
	}
}


