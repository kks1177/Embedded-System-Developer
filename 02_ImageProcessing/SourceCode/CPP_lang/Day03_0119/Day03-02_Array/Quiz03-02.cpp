// Quiz03-02.cpp

#include <stdio.h>

// 퀴즈 3-1.
/*
100개짜리 1차원 배열을 준비
100부터 1까지 대입
합계 출력
*/
/*
int main()
{
	const int ARY_SIZE = 100;
	int ary[ARY_SIZE];
	int value = 100;
	int hap = 0;		// hap 은 long 타입 권장

	for (int i = 0; i < 100; i++) {		// **적극 권장사항** for문의 i를 배열의 첨자(ary[i]) 용도로만 사용
		ary[i] = value;
		value--;

		hap += ary[i];
	}
	printf("합계 : %d \n", hap);
}
*/

// 퀴즈 3-2.
/*
20개짜리 배열 2개 준비
앞 배열에는 3의 배수 대입
뒤 배열에는 앞 배열의 순서를 거꾸로 대입
두 배열을 출력
*/

///*
int main()
{
	const int ARY_SIZE = 20;
	int ary1[ARY_SIZE], ary2[ARY_SIZE];
	int value = 3;

	for (int i = 0; i < ARY_SIZE; i++) {
		ary1[i] = value;
		value += 3;
		printf("%d ", ary1[i]);
	}
	printf("\n\n");
	for (int i = 0; i < ARY_SIZE; i++) {
		ary2[i] = ary1[(ARY_SIZE - 1) - i];
		printf("%d ", ary2[i]);
	}
	printf("\n");
}
//*/

