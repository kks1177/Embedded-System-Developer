// Quiz03-01.cpp

#include <stdio.h>

// 퀴즈 1-1. 1부터 100까지 출력, 단... 줄 안 넘어가고 한칸 띄우기
/*
int main()
{
	for (int i = 1; i < 101; i++) {
		printf("%d ", i);
	}
}
*/


// 퀴즈 1-2. 123부터 456까지 출력. 상동
/*
int main()
{
	for (int i = 123; i < 457; i++) {
		printf("%d ", i);
	}
}
*/


// 퀴즈 1-3. 1부터 100까지 홀수만 출력. 상동
/*
int main()
{
	for (int i = 1; i < 101; i += 2) {
		printf("%d ", i);
	}
}
*/


// 퀴즈 1-4. 12345부터 67890까지 839의 배수만 출력. 상동
/*
int main()
{
	for (int i = 12345; i < 67891; i++) {
		if (i % 839 == 0) {
			printf("%d ", i);
		}
	}
}
*/


// 퀴즈 1-5. 2부터 1000까지의 소수를 출력. 
/*
int main()
{
	for (int i = 2; i < 1001; i++) {
		for (int k = 2; k < i; k++) {
			if (i % k == 0)
				break;
		}
		if (i == k) {
			printf("%d ", i);
		}
	}
}
*/


// 퀴즈 2-1. 구구단 출력하기
/*
int main()
{
	for (int i = 2; i <= 9; i++) {
		for (int k = 1; k <= 9; k++) {
			printf("%d x %d = %d \n", i, k, i * k);
		}
		printf("\n");
	}
}
*/


// 퀴즈 2-2. 구구단 책받침 출력하기
int main()
{
	for (int i = 2; i <= 9; i++) {
		for (int k = 1; k <= 9; k++) {
			printf("%3d x %d = %2d \t", i, k, i * k);
		}
	}
}


// 퀴즈 2-3. 구구단 책받침 거꾸로 출력하기
int main()
{
	for (int k = 1; k <= 9; k++) {
		for (int i = 2; i <= 9; i++) {

		}
	}
}





