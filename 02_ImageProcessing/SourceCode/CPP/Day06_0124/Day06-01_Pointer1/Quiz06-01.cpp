// Quiz06-01.cpp

#include <stdio.h>

int main()
{
	char ary1[10] = "Hello";
	char ary2[10] = "World";
	char* p1, * p2;
	char tmp;

	p1 = ary1;
	p2 = ary2;

	for (int i = 0; i < 10; i++) {
		tmp = p1[i];
		p1[i] = p2[i];
		p2[i] = tmp;
		/*
		tmp = *(p1 + i);
		*(p1 + i) = *(p2 + i);
		*(p2 + i) = tmp;
		*/
	}
	printf("%s \n", ary1);
	printf("%s \n", ary2);
}