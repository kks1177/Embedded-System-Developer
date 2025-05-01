// 질문.cpp 


#include <string>
#include <stdio.h>
using namespace std;

int main()
{
	char str1[10] = "AAA";				// C Style
	printf("%s \n", str1);				// AAA

	string str2 = "BBB";				// C++ Style, cout 사용하지 않기 위해 -> printf("%s \n", 문자열.c_str()) 사용
	printf("%s \n", str2.c_str());		// BBB		// c_str() 함수 : string을 C style의 문자열로 바꿀 때 사용하는 함수 (리턴 : const char*)

	
	//string str3 = "CCC";
	//printf("%s \n", str3);					// garbage value
}


#include <iostream>
#include <string.h>

