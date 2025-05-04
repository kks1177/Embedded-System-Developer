// 2nd_Array.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
using namespace std;

int main()
{
	const int ROW = 3, COL = 4;
	int ary2[ROW][COL];
	int initValue = 0;
	
	// 배열의 값을 모두 0으로 초기화하라.
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			ary2[i][k] = initValue;
		}
	}
}


