// Declaration.h


// **** 전역부 (중요!) **** //
char imgName[100] = { 0 };		// 파일명 + .확장자명
char filePath[100] = { 0 };		// 파일 경로 담을 변수
// = char fileName[100] = { 0 };

char inKey = 0;				// 키보드로 입력 받는 변수
char pix = 0;				// 이미지 출력 변수
int imgSize = 0;			// 이미지 사이즈

int inH, inW, outH, outW;		// 입출력 영상의 크기

unsigned char** inImage = NULL, ** outImage = NULL;

HWND hwnd;		// 윈도우 화면 (외부, 물리적)		// 암기x
HDC  hdc;		// 왼도우 화면 (내부, 논리적)		// 암기x


void printMenu();				// 메뉴 UI
void choiceMenu();				// 메뉴 선택

unsigned char** melloc2D(int, int);			// 2차원 배열 생성 함수
void free2D(unsigned char**, int);			// free 함수
void openImage();				// 이미지 파일 open (입력)

void originImage(char oriImage);	// 원본 이미지
void resultImage(char oriImage);	// 결과 이미지
void ori_printScreen();				// 원본 이미지 화면 출력
void res_printScreen();				// 결과 이미지 화면 출력

//void equalImage();				// 이전 이미지 출력
// =========================== < 화소점 처리 기능 함수 선언 > ===========================
void brightControlImage();		// A.밝기 조절
void clearControlImage();		// B.선명도 조절
void reverseImage();			// C.반전
void grayScaleImage();			// D.흑백 (128/평균)
void bitCalcImage();			// E.비트 연산 (And/Or/Xor/Not)
void gammaConverseImage();		// F.감마 변환
void rangeEmphasisImage();		// G.범위 강조
void parabolaImage();			// H.파라볼라 변환
void stretchedImage();			// I.스트래칭
// ============================ < 기하학 처리 함수 선언 > ===============================
void mirroringImage();  		// J.미러링 (좌우/상하/좌우+상하)
void turnImage();				// K.회전 (방향, 90/180/270도/자유)
void doubleUpDownImage();		// L.2배 확대/축소
void moveImage();				// M.이동

// ============================ < 결과 처리 함수 선언 > ===============================
void inImg_128();			// 이미지 파일 입력_128x128
void inImg_256();			// 이미지 파일 입력_256x256
void inImg_512();			// 이미지 파일 입력_512x512
void outImg_128();			// 이미지 파일 출력_128x128
void outImg_256();			// 이미지 파일 출력_256x256
void outImg_512();			// 이미지 파일 출력_512x512

void clearUp();				// B.선명하게
void clearDown();			// B.흐릿하게

void grayScale128();		// D.흑백처리 (128 기준)
void grayScaleAvg();		// D.흑백처리 (평균값 기준)

void bitCalc_And(int val);		// E-1.비트연산_And
void bitCalc_Or(int val);		// E-2.비트연산_Or
void bitCalc_Xor(int val);		// E-3.비트연산_Xor
void bitCalc_Not();				// E-4.비트연산_Not

void L_R_mirroring();		// J.좌우 미러링
void T_B_mirroring();		// J.상하 미러링
void TB_LR_mirroring();		// J.상하/좌우 미러링

void turn90Right();			// K.오른쪽으로 90도 회전
void turn180Right();		// K.오른쪽으로 180도 회전
void turn270Right();		// K.오른쪽으로 270도 회전
void turn90Left();			// K.왼쪽으로 90도 회전
void turn180Left();			// K.왼쪽으로 180도 회전
void turn270Left();			// K.왼쪽으로 270도 회전

void doubleUp();			// L.2배 확대
void doubleDown();			// L.2배 축소

