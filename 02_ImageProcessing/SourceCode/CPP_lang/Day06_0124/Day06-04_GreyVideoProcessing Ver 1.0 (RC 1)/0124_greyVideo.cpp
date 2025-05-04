// 0124_greyVideo.cpp

#define _CRT_SECURE_NO_WARNINGS
using namespace std; // C++ 추가기능												// 0124_14:15 변경해야되는 거 확인
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h> // GUI를 지원하는 기능

// **** 전역 변수부(중요!)
char filename[100];
int inH, inW, outH, outW;		// 입출력 영상의 크기								////////////// 추가
unsigned char **inImage, **outImage;												////////////// **로 변경
HWND hwnd; // 윈도 화면(외부, 물리적)
HDC  hdc;  // 윈도 화면(내부, 논리적)

// **** 함수 선언부(이름만 표현)
unsigned char** melloc2D(int, int);
void free2D(unsigned char**, int);

void printImage(); void openImage();
void equalImage(); void addImage();
void reverseImage();

void printMenu() {
	puts("\n ## 그레이 영상처리 (Beta 1) ##\n");
	puts("0.열기 1.저장 9.종료\n");
	puts("A.동일 B.밝게/어둡게 C.반전 .....\n");
}

int main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		switch (inKey) {
		case '0': openImage(); break;
		case '9': free2D(inImage, inH); free2D(outImage, outH); break;
		case 'A':
		case 'a': equalImage(); break;
		case 'B':
		case 'b': addImage(); break;
		case 'C':
		case 'c': reverseImage(); break;
		}
	}

	printf("안녕히 가세요~");
}

// *** 공통 함수부
void printImage() {
	// 이미지를 화면 출력
	system("cls");
	int px;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}


// 2차원 배열을 만들어주는 함수
unsigned char** malloc2D(int row, int col) {
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당. 
	retMemory = (unsigned char**)malloc(row * sizeof(unsigned char*));					// unsigned char 뒤에 * 잊지 말기!
	for (int i = 0; i < row; i++) {				// 가로 픽셀, 세로 픽셀 바뀔 때 범위 주의!
		retMemory[i] = (unsigned char*)malloc(col * sizeof(unsigned char));
	}
	return retMemory;
}														///////// 2차원 배열

// free 함수
void free2D(unsigned char** memory, int h) {
	for (int i = 0; i < h; i++) {
		free(memory[i]);
	}
	free(memory);
}

void openImage() {
	char fullName[100] = "C:/images/Etc_Raw(squre)/";
	char tmpName[100];
	printf("파일명-->"); // cat01, doc13
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(filename, fullName);

	FILE* rfp = fopen(filename, "rb");
	if (rfp == NULL)																										///////////// 오류 처리
		return;



	// 입력 영상의 크기를 알아내는 코드. --> inH, inW 결정
	fseek(rfp, 0L, SEEK_END);		// 파일의 끝으로 이동
	unsigned long fsize = ftell(rfp);			// 너 어디야?    262144(=512x512)
	fclose(rfp);

	inH = inW = sqrt(fsize);			// if, 512x512
	// 입력영상 (inImage)의 메모리 할당
	inImage = malloc2D(inH, inW);

	// 파일 --> 메모리로 로딩
	rfp = fopen(filename, "rb");
	for (int i = 0; i < inH; i++) {
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	}


	// 파일 닫기
	fclose(rfp);
	equalImage();
}


//***** 영상 처리 함수 모음 ******
void equalImage() {
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//// ** 진짜 영상처리 알고리즘 ** ////
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	// ******************************** //
	printImage();
}

void addImage() {
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//// ** 진짜 영상처리 알고리즘 ** ////
	int value;
	printf("밝게할 값-->");
	scanf("%d", &value);
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int px = inImage[i][k] + value;
			if (px > 255)
				px = 255;
			else if (px < 0)
				px = 0;
			outImage[i][k] = px;
		}
	}
	printImage();
}

void reverseImage() {// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//// ** 진짜 영상처리 알고리즘 ** ////

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}
//******************************