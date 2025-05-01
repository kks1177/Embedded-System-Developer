// Quiz04-02.cpp

#define _CRT_SECURE_NO_WARNINGS
#define LEN 80

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

// c:\windows\win.ini 파일
int main()
{
	char str[LEN];
	FILE* rfp;		// FILE* : 파일입출력 위한 그냥 정해진 약속			// rfp : Read File Pointer (Disk에 있는 파일에 연결)

	//// (1) 파일 열기 ////
	rfp = fopen("c:\\windows\\win.ini", "r");		// 읽기

	//// (2) 파일 읽기 또는 쓰기 등등 ////
	int lineNum = 1;		// 라인 행번호를 위한 변수
	while(1) {
		fgets(str, LEN, rfp);	// str 변수에 넣어라, 최대 80 글자 읽어와라, rfp에서

		// 파일에 내용이 더이상 없으면 종료
		if (feof(rfp))		// feof : File end of File
			break;

		// ASCII 코드표를 보고 소문자 -> 대문자 변환, 숫자 -> # 변환
		for (int i = 0; i < LEN; i++) {
			if (str[i] == '\n')
				break;

			// 소문자 -> 대문자
			if ('a' <= str[i] && str[i]  <= 'z') {
				str[i] -= ('a' - 'A');
			}

			// 숫자 -> #
			else if ('0' <= str[i] && str[i] <= '9') {
				str[i] = '#';
			}
			printf("%c", str[i]);
		}
		printf("%d : %s", lineNum, str);
		lineNum++;
	}

	//// (3) 파일 닫기 ////
	fclose(rfp);

}
