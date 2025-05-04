// FileInputOutput.cpp
// 파일 입출력

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

// c:\windows\win.ini 파일
int main()
{
	char str[80];
	FILE* rfp;		// FILE* : 파일입출력 위한 그냥 정해진 약속			// rfp : Read File Pointer

	//// (1) 파일 열기 ////
	rfp = fopen("c:\\windows\\win.ini", "r");		// 읽기

	//// (2) 파일 읽기 또는 쓰기 등등 ////
	while (1) {
		fgets(str, 80, rfp);	// str 변수에 넣어라, 최대 80 글자 읽어와라, rfp에서
		if (feof(rfp))			// => 파일의 내용이 더 이상 없으면 종료		// feof : File end of File
			break;
		printf("%s", str);
	}

	//// (3) 파일 닫기 ////
	fclose(rfp);

}
