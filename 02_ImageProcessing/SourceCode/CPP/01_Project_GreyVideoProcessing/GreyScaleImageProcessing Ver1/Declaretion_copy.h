// Declaretion_copy.h


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>		// GUI 지원해주는 헤더
#include <string>
using namespace std;		// C++ 추가 기능


// ============================== < 전역 변수부 (중요!) > ============================== //
char imgName[100] = { 0 };		// 파일명 + .확장자명
char filePath[100] = { 0 };			// 파일 경로 담을 변수

char inKey = 0;			// 키보드로 입력 받는 변수
char algoPick = 0;		// 키보드로 입력 받는 알고리즘 메뉴 변수
char pix = 0;				// pixel, 이미지 출력 변수
//char morpPix = 0;

int inH, inW, outH, outW;		// 입출력 이미지의 크기 (높이/너비)

unsigned char** inImage = NULL, ** outImage = NULL;		// 입력 이미지(이미지 초기값), 출력이미지
unsigned char** morpImage = NULL;

HWND hwnd;	// 윈도우 화면 (외부, 물리적)		// 암기x
HDC  hdc;			// 왼도우 화면 (내부, 논리적)		// 암기x


// ============================= < 메뉴 관련 함수 선언부 > ============================= //
void mainMenu();									// 기본 메뉴 UI
void printMenu(char functionChoice);	// 전체 메뉴 UI
int choiceMenu();									// 메뉴 선택


// =========================== < 이미지 입출력 함수 선언부 > =========================== //
unsigned char** melloc2D(int, int);		// 2차원 배열 생성 함수
void free2D(unsigned char**, int);		// free 함수
void free2D_out();									// 출력 free 함수

void openImage();									// 이미지 파일 open (입력)
void saveImage();									// 출력 이미지 저장 함수
//void openMorpImage();							// 모핑할 이미지 open (입력)

void originImage(char oriImage);			// 원본 이미지
void resultImage(char oriImage);			// 결과 이미지
void ori_printScreen();							// 원본 이미지 화면 출력
void res_printScreen();							// 결과 이미지 화면 출력


// =========================== < 1.화소점 처리 기능 함수 선언부 > ======================== //
void brightControlImage();			// A.밝기 조절	
void clearControlImage();				// B.선명도 조절
void reverseImage();						// C.반전
void grayScaleImage();					// D.흑백 (128/평균)
void bitCalcImage();						// E.비트 연산 (And/Or/Xor/Not)
void gammaConverseImage();		// F.감마 변환
void rangeEmphasisImage();		// G.범위 강조
void parabolaImage();					// H.파라볼라 변환 
void stretchedImage();					// I.명암대비 스트래칭


// ===================== < 2.화소점(히스토그램) 처리 기능 함수 선언부 > ===================== //
void printHisto();							// A.히스토그램 출력
void histoStretchImage();				// B.히스토그램 스트래칭
void histoEndInImage();				// C.히스토그램 엔드-인 탐색
void histoEqualImage();				// D.히스토그램 평활화


// ========================== < 3.화소영역 처리 기능 함수 선언부 > ======================= //
double** malloc2D_double(int row, int col);
void free2D_double(double** memory, int h);

void embossingImage();				// A.엠보싱 
void blurringImage();					// B.블러링
void sharpeningImage();				// C.샤프닝
void smoothingImage();				// D.스무딩 (가우시안)


// ========================== < 4.화소영역 (엣지 검출) 처리 기능 함수 선언부 > ======================= //
void shiftDifferEdgeImage();			// A.이동과 차분 엣지 검출 (수직, 수평, 수직수평)


// ============================ < 5.기하학 처리 함수 선언부 > =========================== //
void mirroringImage();  				// A.미러링 (좌우/상하/좌우+상하)
void turnImage();							// B.회전 (방향, 90/180/270도/자유-백워딩+중앙)	
void imageSizeUpDown();				// C.이미지 크기(규격) 확대/축소
void moveImage();						// D.이동
void warpingImage();					// E.워핑
//void morphingImage();					// F.모핑



// ============================ < 결과 처리 함수 선언부 > ============================== //
void inImgCheck();		// 입력 이미지 입력 여부 확인

void inImg_128();			// 이미지 파일 입력_128x128
void inImg_256();			// 이미지 파일 입력_256x256
void inImg_512();			// 이미지 파일 입력_512x512
void outImg_128();		// 이미지 파일 출력_128x128
void outImg_256();		// 이미지 파일 출력_256x256
void outImg_512();		// 이미지 파일 출력_512x512
//void morpOutImg();		// 모핑할 이미지 출력

void clearUp(int val);					// 1-B.선명하게
void clearDown(int val);			// 1-B.흐릿하게

void grayScale128();					// 1-D.흑백처리 (128 기준)
void grayScaleAvg();					// 1-D.흑백처리 (평균값 기준)

void bitCalc_And(int val);			// 1-E.비트연산_And
void bitCalc_Or(int val);				// 1-E.비트연산_Or
void bitCalc_Xor(int val);			// 1-E.비트연산_Xor
void bitCalc_Not();					// 1-E.비트연산_Not

void parabolaCap();					// 1-H.파라볼라_CAP 변환
void parabolaCup();					// 1-H.파라볼라_CUP 변환


void blurring33();						// 3-B.3x3 블러링
void blurring55();						// 3-B.5x5 블러링

void sharpening();						// 3-C.샤프닝
void HPF_sharp();						// 3-C.고주파필터 처리 샤프닝
void LPF_sharp();						// 3-C.저주파필터 처리 샤프닝


void horizontalEdge();				// 4-A.수직 엣지
void verticalEdge();					// 4-A.수평 엣지
void horiVertiEdge();					// 4-A.수직 수평 엣지


void L_R_mirroring();				// 5-A.좌우 미러링
void T_B_mirroring();				// 5-A.상하 미러링
void TB_LR_mirroring();			// 5-A.상하/좌우 미러링

void turn90Right();					// 5-B.오른쪽으로 90도 회전
void turn180Right();					// 5-B.오른쪽으로 180도 회전
void turn270Right();					// 5-B.오른쪽으로 270도 회전
void turn90Left();						// 5-B.왼쪽으로 90도 회전
void turn180Left();					// 5-B.왼쪽으로 180도 회전
void turn270Left();					// 5-B.왼쪽으로 270도 회전
void turnFree(int val);				// 5-B.자유회전 (포워딩)
void turnFreeCenter(int val);		// 5-B.자유회전 (백워딩+중앙회전)

void sizeUp(int val);									// 5-C.이미지 크기 확대 (포워딩)
void backwardMappingSizeUp(int val);		// 5-C.이미지 크기 확대 (백워딩, Backward Mapping)
void sizeDown(int val);								// 5-C.이미지 크기 축소 (포워딩)
void backwardMappingSizeDown(int val);	// 5-C.이미지 크기 축소 (백워딩)


