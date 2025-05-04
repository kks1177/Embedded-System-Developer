// Pointer01.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 정적배열, 동적배열
int main()
{
	// 지금부터 내가 입력하는 숫자들을 저장하고, 합계를 내라.
	// 배열을 준비해야 함.

	// 방법1. 배열을 충분히 크게 준비

	// 방법2. 배열의 크기를 입력받기.
	/*
	int SIZE;
	printf("오늘 몇개 입력? ");
	scanf("%d", &SIZE);
	
	int ary[SIZE] = { 0 };		// error.. 배열에는 변수가 들어올 수 없음. 상수만..
	*/

	/*
	int a = 100;
	int b = 200;

	printf("%ld \n", &a);
	printf("%ld \n", &b);
	*/

	/*
	int aa[3] = { 10, 20, 30 };
	printf("%d, %x \n", aa[0], &aa[0]);		// 배열의 이름(aa)은 변수가 아닌, 포인터 상수
	printf("%d, %x \n", aa[1], &aa[1]);
	printf("%d, %x \n", aa[2], &aa[2]);

	printf("%x \n", aa);
	*/

	// 변수에는 값을 담을 수 있다.
	// 변수 앞에 &를 붙이면, 변수가 아니라 변수의 메모리상의 번지를 의미
	// 즉 1035 같은 주소값.. 
	// &a는 변수가 아니라 포인터 상수다.
	// 배열의 aa[0]은 변수다. &aa[0] ==> 상수 (1039)
	// 배열의 이름 aa는 포인터 상수다. (1039)


	/*
	char ch;		// 문자 담는 변수
	char* p;		// 주소 담는 변수

	ch = 'A';
	p = &ch;

	printf("%c, %x \n", ch, &ch);		// ch에 담긴 문자, ch 주소값
	printf("%x, %x \n", p, &p);			// ch의 주소값, p의 주소값

	printf("%c \n", *p);	// ch에 담긴 문자
	*/

	
	// 두 값을 바꾸기.
	/*
	char ch1 = 'A', ch2 = 'Z';
	char* p;
	char* q;
	char tmp;

	p = &ch1;
	q = &ch2;
	tmp = *p;
	*p = *q;
	*q = tmp;

	printf("%c  %c", ch1, ch2);
	*/


	// 배열과 포인터
	char s[8] = "Basic-C";
	char* p;

	p = s;

	printf("%c \n", *(p + 0));		// s[0] == *(p+0) == *p == p[0]
	printf("%c \n", *(p + 1));		// *(p+1) == *p+1
	*(p + 2) = '$';

	printf("%s \n", s);
	printf("%s \n", p);
}



