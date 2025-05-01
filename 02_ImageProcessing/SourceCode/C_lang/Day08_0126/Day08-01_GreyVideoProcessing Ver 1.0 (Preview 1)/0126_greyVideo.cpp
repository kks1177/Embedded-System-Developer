// 0126_greyVideo


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>		// GUI를 지원하는 기능
#include <string>
using namespace std;


// **** 전역 변수부(중요!)
char filename[100];
int inH, inW, outH, outW; // 입출력 영상의 크기
unsigned char** inImage = NULL, ** outImage = NULL;
HWND hwnd; // 윈도 화면(외부, 물리적)
HDC  hdc;  // 윈도 화면(내부, 논리적)

// ***** 함수 선언부(이름만 표현) ***** //
unsigned char** malloc2D(int, int);
void free2D(unsigned char**, int);
void free2D_out();
void printMenu();
void printImage(); void openImage(); void saveImage();
void equalImage(); void reverseImage();
void zoomOut();	void zoomIn();	void zoomIn2();
void LotateImage();	 void Lotate2Image();
void histoStretch();	void endIn();		void histoEqual();
void embossing();		void blurring();



// ***** 메인 함수 ***** //
int main() {
	hwnd = GetForegroundWindow();		// 윈도우 창 입력 받는 함수
	hdc = GetWindowDC(hwnd);

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		switch (inKey) {
		case '0': openImage(); break;
		case '1': saveImage(); break;														// @@@@@@@추가
		case '9': free2D(inImage, inH); free2D(outImage, outH); break;
		case 'A':	case 'a':	equalImage(); break;
		case 'B':	case 'b':	reverseImage(); break;
		case 'K':	case 'k':	zoomOut(); break;
		case 'L':	case 'l':	zoomIn(); break;
		case 'M':	case 'm':	zoomIn2(); break;
		case 'N':	case 'n':	LotateImage(); break;
		case 'O':	case 'o':	Lotate2Image(); break;
		case 'V':	case 'v':	histoStretch(); break;
		case 'W':	case 'w':	endIn(); break;
		case 'X':	case 'x':	histoEqual(); break;
		case '@':					embossing(); break;
		case '#':					blurring(); break;

		}
	}
	printf("안녕히 가세요~");
}

void printMenu() {
	puts("\n ## 그레이 영상처리 (Beta 1) ##\n");
	puts("0.열기 1.저장 9.종료\n");
	puts("A.동일 B.반전 .....\n");
	puts("K.축소 L.확대 M.확대(백워딩) N.회전 O.회전(백워딩+중앙).....\n");
	puts("V.히스토그램 스트래칭 W.엔드-인 탐색 X.히스토그램 평활화 \n");
	puts("@.엠보싱  #.블러링 \n");
}
// *********************** //


// ***** 공통 함수부 ***** //
unsigned char** malloc2D(int row, int col) {
	unsigned char** retMemory;
	retMemory = (unsigned char**)malloc(row * sizeof(unsigned char*));
	for (int i = 0; i < row; i++)
		retMemory[i] = (unsigned char*)malloc(col * sizeof(unsigned char));
	return retMemory;
}
void free2D(unsigned char** memory, int h) {
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}
void free2D_out() {
	if (outImage == NULL)
		return;

	for (int i = 0; i < outH; i++)
		free(outImage[i]);
	free(outImage);
}

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

void openImage() {
	char fullName[100] = "C:/images/Etc_Raw(squre)/";
	char tmpName[100];

	printf("파일명-->"); // cat01, doc13
	scanf("%s", tmpName);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(filename, fullName);

	FILE* rfp = fopen(filename, "rb");
	if (rfp == NULL)																// 파일 잘못 선택했으면 안하는것
		return;

	// 입력 영상의 크기를 알아내야 함. --> inH, inW를 결정
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	unsigned long fsize = ftell(rfp); // 너 어디야? 262144
	fclose(rfp);

	inH = inW = sqrt(fsize); // 512x512												// (아주 중요!) 픽셀 수 파악하는 함수
	// 입력영상(inImage)의 메모리를 할당.  uc inImage[inH][inW];
	inImage = malloc2D(inH, inW);
	// 파일 --> 메모리로 로딩
	rfp = fopen(filename, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	// 파일 닫기
	fclose(rfp);
	equalImage();
}

void saveImage() {
	char fullName[100] = "C:/images/Etc_Raw(squre)/";
	char tmpName[100];
	printf("(저장) 파일명-->"); // cat01, doc13
	scanf("%s", tmpName);

	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(filename, fullName);

	FILE* wfp = fopen(filename, "wb");												// rfp --> wfp             rb -> wb
	if (wfp == NULL)																// 작업하다가 USB가 갑자기 뽑혔을 때 발생하는 에러 처리
		return;

	// 메모리 --> 파일로 로딩
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);						// inImage[i] --> outImage[i],     intW--->outW, rfp --> wfp
	// 파일 닫기
	fclose(wfp);
	MessageBox(hwnd, L"저장 OK", L"저장 창", NULL);										// 추가, 
}


//***** 영상 처리 함수부 ***** //
void equalImage() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	//*****************************
	printImage();
}

void reverseImage() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();
}

// 영상 축소 알고리즘
void zoomOut() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	int scale;
	printf("축소 배율 --> ");
	scanf("%d", &scale);

	// output의 크기 결정
	outH = inH / scale;					// output이 input 과 달라짐
	outW = inW / scale;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i / scale][k / scale] = inImage[i][k];
		}
	}
	//*****************************
	printImage();
}

// 영상 확대 알고리즘 (포워딩)
void zoomIn() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	int scale;
	printf("확대 배율 --> ");
	scanf("%d", &scale);

	// output의 크기 결정
	outH = inH * scale;					// output이 input 과 달라짐
	outW = inW * scale;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i * scale][k * scale] = inImage[i][k];
		}
	}
	//*****************************
	printImage();
}
// 영상 확대 알고리즘2 (백워딩)		// 비워진 홀을 채우는 알고리즘
void zoomIn2() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	int scale;
	printf("확대 배율 --> ");
	scanf("%d", &scale);

	// output의 크기 결정
	outH = inH * scale;					// output이 input 과 달라짐
	outW = inW * scale;
	outImage = malloc2D(outH, outW);

	//*** 진짜 영상처리 알고리즘 ***//
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[i / scale][k / scale];
		}
	}
	//*****************************
	printImage();
}

void LotateImage() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	int angle;
	printf("회전 각도 --> ");
	scanf("%d", &angle);
	double radian = angle * 3.141592 / 180.0;

	/* 공식
	xd = cos * xs - sin * ys
	yd = sin * xs + cos * ys
	*/
	int xd, yd;
	for (int xs = 0; xs < inH; xs++) {
		for (int ys = 0; ys < inW; ys++) {
			xd = cos(radian) * xs - sin(radian) * ys;
			yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
	//*****************************
	printImage();
}

// 회전 (백워딩 + 중앙회전)				// 백워딩 : 홀이 생기는 것
void Lotate2Image() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	int angle;
	printf("회전 각도 --> ");
	scanf("%d", &angle);
	double radian = angle * 3.141592 / 180.0;

	/* 공식
	xd = cos * xs - sin * ys
	yd = sin * xs + cos * ys
	*/

	int cx = outH / 2;
	int cy = outW / 2;

	int xs, ys;
	for (int xd = 0; xd < outH; xd++) {
		for (int yd = 0; yd < outW; yd++) {
			xs = cos(radian) * (xd - cx) + sin(radian) * (yd - cy);
			ys = -sin(radian) * (xd - cx) + cos(radian) * (yd - cy);
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW)) {
				outImage[xd][yd] = inImage[xs][ys];
			}
		}
	}
	//*****************************
	printImage();
}



// 히스토그램 스트래치
void histoStretch() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	// 공식. (엔드-인 탐색)
	// out = (in - low) / (high - low) * 255.0;.

	int low = inImage[0][0], high = inImage[0][0];		// 초기화 가장 안전한 방법
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (double)(inImage[i][k] - low) / (high - low) * 255.0;
		}
	}
	//*****************************
	printImage();
}

// 히스토그램 엔드-인 탐색
void endIn() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	int low = inImage[0][0], high = inImage[0][0];		// 초기화 가장 안전한 방법
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	low += 50;
	high -= 50;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			double res = (double)(inImage[i][k] - low) / (high - low) * 255.0;
			if (res <= 0.0)
				outImage[i][k] = 0;
			else if (res > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = res;
		}
	}
	//*****************************
	printImage();
}

// 히스토그램 평활화
/*
* 1단계 : 명암 값 j의 빈도수 hist[j]를 계산해 입력 영상이 히스토그램 생성
* 2단계 : 각 명암 값 i에서 0~i까지의 누적 빈도수(누적합)를 계산
* 3단계 : 2단계에서 구한 누적 빈도수를 정규화 (정규화 누적합)
*/
void histoEqual() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	// 1단계 : 히스토그램 생성
	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; k++)
			histo[inImage[i][k]]++;

	// 2단계 : 누적 히스토그램 생성 (누적합 생성)
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3 단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
	// n = sum * (1/(inH*inW)) * 255.0
	double normalHisto[256] = { 0, };
	for (int i = 0; i < 256; i++)
		normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;

	// 4단계 : 원래값을 정규화 값으로 치환
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = normalHisto[inImage[i][k]];
		}
	}	
	//*****************************
	printImage();
}




double** malloc2D_double(int row, int col) {
	double** retMemory;
	retMemory = (double**)malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++)
		retMemory[i] = (double*)malloc(col * sizeof(double));
	return retMemory;
}
void free2D_double(double** memory, int h) {
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

// 화소영역 처리
// 엠보싱
void embossing() {
	free2d_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outh = inh;
	outw = inw;
	outimage = malloc2d(outh, outw);

	//**** 진짜 영상처리 알고리즘 ***//
	const int msize = 3;		// 마스크 크기
	// 엠보싱 마스크 (각 기능에 대한 마스크는 교재나 구글링)
		double mask[msize][msize] = { {-1,0,0},
										{ 0,0, 0},
										{0,0,1} };

	// 임시 입출력 메모리 할당
	double** tmpin, ** tmpout;
	tmpin = malloc2d_double(inh + 2, inw + 2);
	tmpout = malloc2d_double(outh, outw);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inh + 2; i++)
		for (int k = 0; k < inw + 2; k++)
			tmpin[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inimage --> tmpinimage)
	for (int i = 0; i < inh; i++)
		for (int k = 0; k < inw; i++)
			tmpin[i + 1][k + 1] = inimage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double s;		// 한점에 대한 입력 영상 x 마스크의 합계
	for (int i = 0; i < inh; i++) {
		for (int k = 0; k < inw; k++) {
			s = 0.0;
			for (int m = 0; m < msize; m++) {
				for (int n = 0; n < msize; n++) {
					s += tmpin[i + m][k + n] * mask[m][n];
				}
			}
			tmpout[i][k] = s;
		}
	}
	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < outh; i++) {
		for (int k = 0; k < outw; k++) {
			tmpout[i][k] += 127.0;
		}
	}
	//  임시 출력 --> 출력 메모리
	for (int i = 0; i < outh; i++) {
		for (int k = 0; k < outw; k++) {
			double v = tmpout[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;
			outimage[i][k] = v;
		}
	}
	free2d_double(tmpin, inh + 2);
	free2d_double(tmpout, outh);

	printimage();
}

// 블러링
void blurring() {
	free2D_out();
	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	outH = inH;
	outW = inW;
	outImage = malloc2D(outH, outW);

	//**** 진짜 영상처리 알고리즘 ***//
	const int MSIZE = 3;		// 마스크 크기
	// 엠보싱 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] = { {1./9, 1./9, 1./9},
												      {1./9, 1./9, 1./9},
													  {1./9, 1./9, 1./9} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(inH + 2, inW + 2);
	tmpOut = malloc2D_double(outH, outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < inH + 2; i++)
		for (int k = 0; k < inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < inH; i++)
		for (int k = 0; k < inW; i++)
			tmpIn[i + 1][k + 1] = inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S;		// 한점에 대한 입력 영상 x 마스크의 합계
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			S = 0.0;
			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S += tmpIn[i + m][k + n] * mask[m][n];
				}
			}
			tmpOut[i][k] = S;
		}
	}
	// 후처리 (마스크의 합계에 따라서 정제...)
	/*
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			tmpOut[i][k] += 127.0;
		}
	}
	*/

	//  임시 출력 --> 출력 메모리
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			double v = tmpOut[i][k];
			if (v > 255.0)
				v = 255.0;
			else if (v < 0.0)
				v = 0.0;
			outImage[i][k] = v;
		}
	}
	free2D_double(tmpIn, inH + 2);
	free2D_double(tmpOut, outH);

	printImage();
}



