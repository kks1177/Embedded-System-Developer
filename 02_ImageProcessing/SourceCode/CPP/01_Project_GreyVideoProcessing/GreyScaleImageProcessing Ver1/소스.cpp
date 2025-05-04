#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
/* =======================================================================
   이름 : 미니프로젝트_ImageProcessing
   버전 :1.0
   기능
   -기본기능
     -파일열기, 저장, 종료
   -영상처리기능
    - 화소점처리, 기하학처리, 화소영역처리, 히스토그램처리
   ======================================================================= */

   // 전역변수부
#define UC unsigned char
HWND hwnd;  HDC hdc;
UC** m_InImage = NULL;     // Input_Image : 입력 이미지(이미지초기값)
UC** m_OutImage = NULL;     // Output_Image : 출력 이미지
int m_inH, m_inW, m_outH, m_outW; // 이미지 높이, 너비
int menuInput = 0;
float version = 1.0; // 버전 입력

// 함수 선언부 (공통)
UC** malloc2D(int, int);    void free2D(UC**, int);
void openImage();           void saveImage();
void displayImage();

// 함수 선언부 (영상처리)
void equalImage();
void pmLightImage();        void mdLightImage();
void andCircleImage();      void orCircleImage();
void bwImage();             void bwAvgImage();
void ngtvImage();           void gammaImage();      void paraImage();

void zoomOutImage();        void zoomInImage();
void zoomInBackImage();
void mirrorLRImage();       void mirrorUDImage();
void moveImage();
void rotateImage();         void midRotateImage();  void midRotateFullImage();

void embossImage();
void blur3Image();          void blur5Image();      void blurImage();
void gausBlur3Image();      void sharp1Image();     void sharp2Image();
void hfSharpImage();

void vEdgeImage();          void hEdgeImage();
void  robertsVEdgeImage();  void robertsHEdgeImage();   void robertsEdgeImage();
void prwVEdgeImage();       void prwHEdgeImage();       void prwEdgeImage();
void  sobelVEdgeImage();    void sobelHEdgeImage();     void sobelEdgeImage();
void lapla4EdgeImage();     void laplam8EdgeImage();    void lapla8EdgeImage();
void logEdgeImage();        void dogEdgeImage();

void usaImage();            void minusImage();          void zoomInYSImage();       void rotateYSImage();

void histStretchImage();    void histEqualizeImage();   void histImage();

void printMenu() {
    int endPage = 4;
    if (menuInput > endPage) {
        menuInput = 0;
    }
    else if (menuInput < 0) {
        menuInput = endPage;
    }
    printf(" \n   ImageProcessing(Version %.1f)_박시환\n", version);
    puts("-------------------------------------------------\n");
    puts("   [0.이미지열기] [1.저장] [2.원본] [3.종료]\n");
    printf("---------------------[%d / %d]----------------------\n", menuInput + 1, endPage + 1);
    switch (menuInput) {
    case 0:
        puts("   [화소점처리]\n");
        puts("(A.흑백)\t(B.평균흑백)\n");
        puts("(C.+-밝기)\t(D.*/밝기)\n");
        puts("(E.AND원)\t(F.OR원)\n");
        puts("(G.반전)\t(H.감마)\n");
        puts("(I.파라볼라)\n");
        break;
    case 1:
        puts("   [기하학처리]\n");
        puts("(A.축소)\t(B.확대)\n");
        puts("(C.백워딩확대)\t(D.이동)\n");
        puts("(E.좌우미러링)\t(F.상하미러링)\n");
        puts("(G.회전)\t(H.중앙백워딩회전)\n");
        puts("\n[양선형보간법]\n");
        puts("(I.회전)\t(J.확대)\n");
        break;
    case 2:
        puts("   [화소영역처리]\n");
        puts("(A.엠보싱)\n");
        puts("(B.3x3블러)\t(C.5x5블러)\n");
        puts("(D.입력평균블러)\t(E.가우시안블러)\n");
        puts("(F.고주파통과샤프닝1)\t(G.고주파통과샤프닝2)\n");
        puts("(H.고주파필터샤프닝)\t\n");
        break;
    case 3:
        puts("   [화소영역처리(엣지처리)]\n");
        puts("(A.수평엣지)\t(B.수직엣지)\n");
        puts("\n[1차 미분 회선 마스크]\n");
        puts("[로버츠엣지]\t(C.수평) (D.수직) (E.수직수평)\n");
        puts("[프리윗엣지]\t(F.수평) (G.수직) (H.수직수평)\n");
        puts("[소벨엣지]]\t(I.수평) (J.수직) (K.수직수평)\n");
        puts("\n[2차 미분 회선 마스크]\n");
        puts("[라플라엣지]]\t(L.4)\t(M.-8)\t(N.8)\n");
        puts("(O.LOG연산)\t(V.DoG연산)\n");
        puts("\n[연산자]\n");
        puts("(Q.유사연산자)\t(R.차연산자)\n");
        break;
    case 4:
        puts("   [히스토그램처리]\n");
        puts("(A.히스토그램표시)\n");
        puts("(B.스트레칭)\t(C.평활화)\n");
        break;
    }
    puts("-------------------------------------------------\n");
    puts(" >.다음 메뉴\n");

}

// 메인함수
int main() {
    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(hwnd);

    char input = 0;
    while (true) {
        printMenu();
        input = _getch();
        if (menuInput == 0) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': bwImage(); break;
            case 'b': case'B': bwAvgImage(); break;
            case 'c': case'C': pmLightImage(); break;
            case 'd': case'D': mdLightImage(); break;
            case 'e': case'E': andCircleImage(); break;
            case 'f': case'F': orCircleImage(); break;
            case 'g': case'G': ngtvImage(); break;
            case 'h': case'H': gammaImage(); break;
            case 'i': case'I': paraImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> 올바른 값을 입력하세요.\n"); break;
            }
        }
        else if (menuInput == 1) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': zoomOutImage();  break;
            case 'b': case'B': zoomInImage(); break;
            case 'c': case'C': zoomInBackImage(); break;
            case 'd': case'D': moveImage(); break;
            case 'e': case'E': mirrorLRImage(); break;
            case 'f': case'F': mirrorUDImage(); break;
            case 'g': case'G': rotateImage(); break;
            case 'h': case'H': midRotateFullImage(); break;
            case 'i': case'I': rotateYSImage(); break;
            case 'j': case'J': zoomInYSImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> 올바른 값을 입력하세요.\n"); break;
            }
        }
        else if (menuInput == 2) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': embossImage(); break;
            case 'b': case'B': blur3Image(); break;
            case 'c': case'C': blur5Image(); break;
            case 'd': case'D': blurImage(); break;
            case 'e': case'E': gausBlur3Image(); break;
            case 'f': case'F': sharp1Image(); break;
            case 'g': case'G': sharp2Image(); break;
            case 'h': case'H': hfSharpImage(); break;

            default:
                if (input != 'x' && input != 'X') printf("-> 올바른 값을 입력하세요.\n"); break;
            }

        }
        else if (menuInput == 3) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': hEdgeImage(); break;
            case 'b': case'B': vEdgeImage(); break;
            case 'c': case'C': robertsVEdgeImage(); break;
            case 'd': case'D': robertsHEdgeImage(); break;
            case 'e': case'E': robertsEdgeImage(); break;
            case 'f': case'F': prwVEdgeImage(); break;
            case 'g': case'G': prwHEdgeImage(); break;
            case 'h': case'H': prwEdgeImage(); break;
            case 'i': case'I': sobelVEdgeImage(); break;
            case 'j': case'J': sobelHEdgeImage(); break;
            case 'k': case'K': sobelEdgeImage(); break;
            case 'l': case'L': lapla4EdgeImage(); break;
            case 'm': case'M': laplam8EdgeImage(); break;
            case 'n': case'N': lapla8EdgeImage(); break;
            case 'o': case'O': logEdgeImage(); break;
            case 'v': case'V': dogEdgeImage(); break;
            case 'q': case'Q': usaImage(); break;
            case 'r': case'R': minusImage(); break;


            default:
                if (input != 'x' && input != 'X') printf("-> 올바른 값을 입력하세요.\n"); break;
            }

        }
        else if (menuInput == 4) {
            switch (input) {
            case '>': menuInput++; system("cls"); break;
            case '<': menuInput--; system("cls"); break;
            case '0': openImage(); break;
            case '1': saveImage(); break;
            case '2':equalImage(); break;
            case '3': free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH); return 0;

            case 'a': case'A': histImage(); break;
            case 'b': case'B': histStretchImage(); break;
            case 'c': case'C': histEqualizeImage(); break;


            default:
                if (input != 'x' && input != 'X') printf("-> 올바른 값을 입력하세요.\n"); break;
            }

        }
    }
    system("cls");
    printf("종료되었습니다.\n");
    free2D(m_InImage, m_inH); free2D(m_OutImage, m_outH);
    return 0;
}

/// 함수 정의부 (공통함수)
// 메모리 관련함수
UC** malloc2D(int  h, int w) {
    UC** mem;
    mem = (UC**)malloc(h * sizeof(UC*));
    for (int i = 0; i < h; i++)
        mem[i] = (UC*)malloc(w * sizeof(UC));

    // 초기화(Clear)
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0;
        }
    }
    return mem;
}
void free2D(UC** memory, int h) {
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]);
        free(memory);
    }
}
// - 이미지 열기
void openImage() {
    char input[50];
    char routeName[100] = "c:/images/meRAW/";
    printf("열어볼 파일 명 -> "); scanf("%s", &input);
    strcat(routeName, input); strcat(routeName, ".raw");
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;

    //기존 입력 메모리 해제
    free2D(m_InImage, m_inH);
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    fclose(file);

    m_inH = m_inW = (int)sqrt(size);
    m_InImage = malloc2D(m_inH, m_inW);
    printf("[%s][%dx%d]경로 파일을 여는 중 ..\n", routeName, m_inH, m_inW);
    file = fopen(routeName, "rb");
    for (int i = 0; i < m_inH; i++)
        fread(m_InImage[i], sizeof(UC), m_inW, file);
    fclose(file);
    equalImage();
}
// - 이미지 저장
void saveImage() {
    char input[50];
    char routeName[100] = "c:/images/meRAW/";
    printf("저장할 파일 명 -> "); scanf("%s", &input);
    strcat(routeName, input); strcat(routeName, ".raw");
    FILE* file = fopen(routeName, "wb");
    for (int i = 0; i < m_outH; i++) {
        fwrite(m_OutImage[i], sizeof(UC), m_outW, file);
    }
    fclose(file);
    MessageBox(hwnd, L"저장완료", L"메세지 창", NULL);
}
// - 이미지 출력 : Output Image를 보여준다.
void displayImage() {
    system("cls");
    int px;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            px = m_OutImage[i][k];
            SetPixel(hdc, k + 630, i + 50, RGB(px, px, px));
        }
    }
}

/// 함수 정의부 (영상처리)

//화소점처리
// - 이미지 원본화 : Input Image로 Output Image를 초기화시켜준다.
void equalImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[i][k];
        }
    }
    displayImage();
}
// - 덧셈 뺄셈으로 이미지 밝기 조절 : 밝은, 어두운부분 전부 똑같이 영향을 끼침.
void pmLightImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("원하는 밝기조절량 :"); scanf("%d", &input);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] += input;
            if ((m_InImage[i][k] + input) > 255) m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] + input) <= 0) m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = m_InImage[i][k] + input;
        }
    }
    displayImage();
}
// - 곱셈 나눗셈으로 이미지 밝기 조절 : 밝은, 어두운부분을 적당히 영향을 끼침.
void mdLightImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("(1)곱셈 (2) 나눗셈\n"); input = _getch();
    if (input == '1') {
        printf("원하는 밝기조절량 :"); scanf("%d", &input);
        for (int i = 0; i < m_inH; i++) {
            for (int k = 0; k < m_inW; k++) {
                if ((m_InImage[i][k] * input) > 255) m_OutImage[i][k] = 255;
                else if ((m_InImage[i][k] * input) <= 0) m_OutImage[i][k] = 0;
                else m_OutImage[i][k] = m_InImage[i][k] * input;
            }
        }
    }
    if (input == '2') {
        printf("원하는 밝기조절량 :"); scanf("%d", &input);
        for (int i = 0; i < m_inH; i++) {
            for (int k = 0; k < m_inW; k++) {
                if (input == 0) input = 1;
                if ((m_InImage[i][k] / input) > 255) m_OutImage[i][k] = 255;
                else if ((m_InImage[i][k] / input) <= 0) m_OutImage[i][k] = 0;
                else m_OutImage[i][k] = m_InImage[i][k] / input;
            }
        }
    }

    displayImage();
}
// - 흑백 원과 AND연산을 하는 함수이다. 비트연산으로 처리하면 무슨일이 일어날까 싶어서 만들었다.
// -- 128크기의 원을 해당 이미지 크기와 같은크기로 만든 후 비트연산 처리한다.
void andCircleImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    //128x128사이즈의 흑백원 그림을 가져온다.
    char routeName[100] = "C:/images/meRAW/circle128.raw";
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;
    //원의 본 사이즈를 측정
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    int c_H, c_W;
    c_H = c_W = (int)sqrt(size);
    fclose(file);
    UC** circ = malloc2D(c_H, c_W); // 원그림 원본 메모리
    //128x128 흑백원 그리기
    file = fopen(routeName, "rb");
    for (int i = 0; i < c_H; i++)
        fread(circ[i], sizeof(UC), c_W, file);
    fclose(file);
    //연상용 원 만들기
    UC** circOut = malloc2D(m_outH, m_outW); // 연산할때 사용할 원그림 메모리
    int scale = (int)(m_outH / c_H);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            circOut[i][k] = circ[i / scale][k / scale];
        }
    }
    // AND연산 :: 주의! 비트연산자는 우선순위가 낮기때문에 괄호처리 매우 중요
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if ((m_InImage[i][k] & circOut[i][k]) >= 255)  m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] & circOut[i][k]) < 0)  m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = (m_InImage[i][k] & circOut[i][k]);
        }
    }
    free2D(circ, c_H);
    free2D(circOut, m_outH);
    displayImage();
}
// 흑백 원과 OR연산을 하는 함수이다.
void orCircleImage() { // 흑백 원과 OR연산을 하는 함수이다.
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    //128x128사이즈의 흑백원 그림을 가져온다.
    char routeName[100] = "C:/images/meRAW/circle128.raw";
    FILE* file = fopen(routeName, "rb");
    if (file == NULL) return;
    //원의 본 사이즈를 측정
    fseek(file, 0L, SEEK_END);
    unsigned long size = ftell(file);
    int c_H, c_W;
    c_H = c_W = (int)sqrt(size);
    fclose(file);
    UC** circ = malloc2D(c_H, c_W); // 원그림 원본 메모리
    //128x128 흑백원 그리기
    file = fopen(routeName, "rb");
    for (int i = 0; i < c_H; i++)
        fread(circ[i], sizeof(UC), c_W, file);
    fclose(file);
    //연상용 원 만들기
    UC** circOut = malloc2D(m_outH, m_outW); // 연산할때 사용할 원그림 메모리
    int scale = (int)(m_outH / c_H);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            circOut[i][k] = circ[i / scale][k / scale];
        }
    }
    // OR연산 :: 주의! 비트연산자는 우선순위가 낮기때문에 괄호처리 매우 중요
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if ((m_InImage[i][k] | circOut[i][k]) >= 255)  m_OutImage[i][k] = 255;
            else if ((m_InImage[i][k] | circOut[i][k]) < 0)  m_OutImage[i][k] = 0;
            else m_OutImage[i][k] = (m_InImage[i][k] | circOut[i][k]);
        }
    }
    free2D(circ, c_H);
    free2D(circOut, m_outH);
    displayImage();
}
// - 이미지 완전 흑백
void bwImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] > 127) m_OutImage[i][k] = 255;
            else m_OutImage[i][k] = 0;
        }
    }
    displayImage();
}
// - 이미지 평균값 흑백
void bwAvgImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    unsigned long hap = 0;
    int cnt = 0;
    int avg = 0;

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            hap += m_InImage[i][k];
            cnt++;
        }
    }
    avg = (int)hap / cnt;
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] >= avg) m_OutImage[i][k] = 255;
            else m_OutImage[i][k] = 0;
        }
    }
    displayImage();
}
// - 이미지 반전
void ngtvImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = 255 - m_InImage[i][k];
        }
    }
    displayImage();
}
// - 이미지 감마 조절
void gammaImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);

    float gamma;
    printf("감마값 (0.2~1.8) : "); scanf("%f", &gamma);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            double m = m_InImage[i][k];
            m_OutImage[i][k] = (unsigned int)255.0 * pow(m / 255.0, gamma); // pow(a,b) ; a의 b 제곱
        }
    }
    displayImage();
}
// - 이미지 파라볼라 모드(Cup, Cap)
void paraImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH; m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("(1)CAP (2) CUP\n"); input = _getch();
    double value = 0.0;

    if (input == '1') {
        for (int i = 0; i < m_outH; i++) {
            for (int k = 0; k < m_outW; k++) {
                //pow()// 거듭제곱 : x의 y제곱
                double value = 255.0 - 255.0 * pow((m_InImage[i][k] / 128.0 - 1.0), 2); //밝은 곳 입체형 (CAP)
                if (value > 255.0) value = 255.0;
                else if (value < 0.0) value = 0.0;

                m_OutImage[i][k] = (UC)value;
            }
        }
    }
    else {
        for (int i = 0; i < m_outH; i++) {
            for (int k = 0; k < m_outW; k++) {
                //pow()// 거듭제곱 : x의 y제곱
                double value = 255.0 * pow((m_InImage[i][k] / 128.0 - 1.0), 2); //어두운 곳 입체형 (CUP)
                if (value > 255.0) value = 255.0;
                else if (value < 0.0) value = 0.0;

                m_OutImage[i][k] = (UC)value;
            }
        }
    }
    displayImage();
}

///기하학 처리
// 영상 축소 알고리즘
void zoomOutImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("원하는 축소배율 :"); scanf("%d", &scale);
    m_outH = m_inH / scale;
    m_outW = m_inW / scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i / scale][k / scale] = m_InImage[i][k];
        }
    }
    displayImage();
}
// 영상 확대 알고리즘
void zoomInImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("원하는 확대배율 :"); scanf("%d", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i * scale][k * scale] = m_InImage[i][k];
        }
    }
    displayImage();
}
// 영상 확대 백워딩 알고리즘
void zoomInBackImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    int scale = 0;
    printf("원하는 확대배율 :"); scanf("%d", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;

    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = m_InImage[i / scale][k / scale];
        }
    }
    displayImage();
}
// 회전 알고리즘  : 미완성 (1. 중앙으로, 2. 백워딩 3. 각도 안정)
void rotateImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    // 출력 영상 메모리 할당
    m_OutImage = malloc2D(m_outH, m_outW);
    int angle = 0; // 0~360
    printf("원하는 회전각도 :"); scanf("%d", &angle);

    double radian = angle * M_PI / 180.0;
    // 삼각함수 공식 :
    // newX = cos * x - sin * y;
    // newY = sin * x + cos * y;
    // 컴퓨터는 radian밖에 안받음 (degree에서 radian으로 형변환 해줘야한다)

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {

            int newI = cos(radian) * i - sin(radian) * k;
            int newK = sin(radian) * i + cos(radian) * k;
            if (((0 <= newI) && (newI < m_outH)) && ((0 <= newK) && (newK < m_outW)))
                m_OutImage[newI][newK] = m_InImage[i][k];
        }
    }
    displayImage();
}
// 회전알고리즘 중심점 : 중앙회전 + 백워딩
void midRotateImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    // 출력 영상 메모리 할당
    m_OutImage = malloc2D(m_outH, m_outW);
    int angle = 0; // 0~360
    printf("원하는 일반 회전각도 :"); scanf("%d", &angle);
    double radian = angle * M_PI / 180.0;
    // 삼각함수 공식 :
    // newX = cos * x - sin * y;
    // newY = sin * x + cos * y;
    // 컴퓨터는 radian밖에 안받음 (degree에서 radian으로 형변환 해줘야한다)

    // 중앙위치 구하기
    int cx = m_outH / 2;
    int cy = m_outW / 2;

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {

            int oldI = (cos(radian) * (i - cx) + sin(radian) * (k - cy)) + cx;
            int oldK = (-sin(radian) * (i - cx) + cos(radian) * (k - cy)) + cy;
            if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW)))
                m_OutImage[i][k] = m_InImage[oldI][oldK];
        }
    }
    displayImage();
}
// 회전알고리즘 중심점 : 중앙회전 + 백워딩 + 확대 + 시작부터중앙에서회전
void midRotateFullImage() {// 영상 회전 알고리즘. 중앙회전+백워딩+확대
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    // 진짜 영상 처리 알고리즘
    int angle; // 0 ~ 360
    printf("원하는 회전각도 :"); scanf("%d", &angle);
    double tmp_radian = angle % 90 * M_PI / 180.0;
    double tmp_radian90 = (90 - angle % 90) * M_PI / 180.0;

    //(중요!) 출력 영상의 높이와 폭을 결정 --> 알고리즘에 따름
    m_outH = (int)(m_inH * cos(tmp_radian90) + m_inW * cos(tmp_radian));
    m_outW = (int)(m_inW * cos(tmp_radian) + m_inW * cos(tmp_radian90));
    // 출력 영상 메모리 할당
    double radian = angle * M_PI / 180.0;
    m_OutImage = malloc2D(m_outH, m_outW);

    // 임시 입력 영상 ---> 출력과 크기가 같게 하고, 입력 영상을 중앙에 두기.
    UC** tmpInput = malloc2D(m_outH, m_outW);
    int dx = (m_outH - m_inH) / 2;
    int dy = (m_outW - m_inW) / 2;
    for (int i = 0; i < m_inH; i++)
        for (int k = 0; k < m_inW; k++)
            tmpInput[i + dx][k + dy] = m_InImage[i][k];

    // 중앙 위치 구하기
    int cx = m_outH / 2;
    int cy = m_outW / 2;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            int oldI = (cos(radian) * (i - cx) + sin(radian) * (k - cy)) + cx;
            int oldK = (-sin(radian) * (i - cx) + cos(radian) * (k - cy)) + cy;
            if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW)))
                m_OutImage[i][k] = tmpInput[oldI][oldK];
        }
    }
    free2D(tmpInput, m_outH);
    displayImage();
}
void mirrorLRImage() { //좌우 미러링 함수
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[i][m_inW - k - 1];
        }
    }
    displayImage();
}
void mirrorUDImage() { //상하 미러링 함수
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[m_inH - i - 1][k];
        }
    }
    displayImage();
}
void moveImage() { //이동 이미지 함수
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("원하는 이동 정도 : "); scanf("%d", &input);
    if (m_inH < input) input = 0;
    for (int i = input; i < m_inH; i++) {
        for (int k = input; k < m_inW; k++) {

            m_OutImage[i][k] = m_InImage[i - input][k - input];
        }
    }
    displayImage();
}

/// 화소영역처리
double** malloc2D_double(int  h, int w) {
    double** mem;
    mem = (double**)malloc(h * sizeof(double*));
    for (int i = 0; i < h; i++)
        mem[i] = (double*)malloc(w * sizeof(double));

    // 초기화(Clear)
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0;
        }
    }
    return mem;
}
void free2D_double(double** memory, int h) {
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]);
        free(memory);
    }
}
// 엠보싱 알고리즘
void embossImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (엠보싱)
    double mask[3][3] = { {-1.,0.,0.},
                          {0.,0.,0.},
                          {0.,0.,1.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k]; // 임시Input의 중심에 사진을 넣는중.
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S; // 마스크9개 X 입력영상 9개의 합
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    // 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            tmpOutput[i][k] += 127.0;
        }
    }
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 3x3블러링 알고리즘
void blur3Image() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {1 / 9.,1 / 9.,1 / 9.},
                          {1 / 9.,1 / 9.,1 / 9.},
                          {1 / 9.,1 / 9.,1 / 9.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 5x5블러링 알고리즘
void blur5Image() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[5][5] = { {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.},
                          {1 / 25.,1 / 25.,1 / 25.,1 / 25.,1 / 25.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 4, m_inW + 4); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 2][k + 2] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크25개 X 입력영상 25개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 5; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 4);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 입력값대로 블러처리
void blurImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    int input = 0;
    printf("블러 강도 : "); scanf("%d", &input);
    if (input % 2 == 0) {
        input += 1;
    }
    printf("%d x %d 블러 처리 중...\n", input, input);
    double** mask = malloc2D_double(input, input);
    for (int i = 0; i < input; i++) {
        for (int k = 0; k < input; k++) {
            mask[i][k] = (double)(1.0 / ((double)(input * input)));
        }
    }
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + (int)(input / 2) * 2, m_inW + (int)(input / 2) * 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + (int)(input / 2)][k + (int)(input / 2)] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < input; m++) {
                for (int n = 0; n < input; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + (int)(input / 2) * 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 가우시안 블러처리
void gausBlur3Image() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {1 / 16.,1 / 8.,1 / 16.},
                          {1 / 8.,1 / 4.,1 / 8.},
                          {1 / 16.,1 / 8.,1 / 16.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 고주파통과샤프닝1
void sharp1Image() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    int input = 0;
    double mask[3][3] = { {-1.,-1.,-1.},
                          {-1., 9.,-1.},
                          {-1.,-1.,-1.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 고주파통과샤프닝2
void sharp2Image() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {0.,-1.,0},
                          {-1., 5.,-1.},
                          {0,-1.,0.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 고주파 필터 샤프닝
void hfSharpImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {-1. / 9.,1 / 9.,-1. / 9.},
                          {-1. / 9.,8. / 9.,-1. / 8.},
                          {-1. / 9.,1 / 9.,-1. / 9.} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

/// 엣지영역 검출
// 수직엣지 검출
void vEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {0,0,0},
                          {-1,1,0},
                          {0,0,0} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평엣지 검출
void hEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3] = { {0,-1,0},
                          {0,1,0},
                          {0,0,0} };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    //// 마무리 (다듬기) --> 마스크합계가 0 또는 1 이면 127 더하기
    //for (int i = 0; i < m_outH; i++) {
    //    for (int k = 0; k < m_outW; k++) {
    //        tmpOutput[i][k] += 127.0;
    //    }
    //}
    // tmpOutput -> m_OutImage // 오버플로우, 언더플로우 확인 후.
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 유사 연산자 검출 (해야함)
/// 1차 미분검출
// 수평 로버츠 검출
void robertsHEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {-1,0,0} ,
            {0,1,0} ,
            {0,0,0} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수직 로버츠 검출
void robertsVEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {0,0,-1} ,
            {0,1,0} ,
            {0,0,0} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평수직,로버츠 검출
void robertsEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double maskV[3][3]
        = { {-1,0,0} ,
            {0,1,0} ,
            {0,0,0} };
    double maskH[3][3]
        = { {0,0,-1} ,
            {0,1,0} ,
            {0,0,0} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
// 수직 프리윗 검출
void prwVEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {-1,0,1} ,
            {-1,0,1} ,
            {-1,0,1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평 프리웟 검출
void prwHEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {1,1,1} ,
            {0,0,0} ,
            {-1,-1,-1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평수직,프리웟 검출
void prwEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double maskV[3][3]
        = { {-1,0,1} ,
            {-1,0,1} ,
            {-1,0,1} };
    double maskH[3][3]
        = { {1,1,1} ,
            {0,0,0} ,
            {-1,-1,-1} };


    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
// 수직 소벨 검출
void sobelVEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {1,2,1} ,
            {0,0,0} ,
            {-1,-2,-1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평 소벨 검출
void sobelHEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {-1,0,1} ,
            {-2,0,2} ,
            {-1,0,1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 수평수직 소벨 검출
void sobelEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double maskV[3][3]
        = { {1,2,1} ,
            {0,0,0} ,
            {-1,-2,-1} };
    double maskH[3][3]
        = { {-1,0,1} ,
           {-2,0,2} ,
           {-1,0,1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    double** tmpOutput2 = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskH[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }
    S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * maskV[m][n];
                }
            }
            tmpOutput2[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v1 = tmpOutput[i][k];
            double v2 = tmpOutput[i][k];
            double v = v1 + v2;
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    free2D_double(tmpOutput2, m_outH);
    displayImage();
}
/// 2차 미분검출
// 라플라시안(4) 검출
// 라플라시안의 회선마스크 합은 0어야 한다.
void lapla4EdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {0,-1,0} ,
            {-1,4,-1} ,
            {0,-1,0} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 라플라시안(-8) 검출
void laplam8EdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {1,1,1} ,
            {1,-8,1} ,
            {1,1,1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 라플라시안(8)  검출
void lapla8EdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[3][3]
        = { {-1,-1,-1} ,
            {-1,8,-1} ,
            {-1,-1,-1} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

// LoG 엣지검출 : 1.가우시안 2. 라플라시안
// LoG (Laplacian of Gausian)
// 잡음에 민감한 라플라시안의 단점을 고안하고자, 
// 가우시안 스무딩(블러링)을 한후 라플라시안 사용.
void logEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[5][5]
        = { {0,0,-1,0,0} ,
            {0,-1,-2,-1,0} ,
            {-1,-2,16,-2,-1},
            {0,-1,-2,-1,0} ,
            {0,0,-1,0,0} };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 4, m_inW + 4); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 2][k + 2] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 5; m++) {
                for (int n = 0; n < 5; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 4);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// DoG 엣지검출 : LoG의 느린속도를 보완하기위해 나옴.
void dogEdgeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    //(중요!) 화소영역 알고리즘에 해당하는 마스크 (블러링) : 픽셀/마스크 전체크기 
    double mask[9][9]
        = { {0,0,0,-1,-1,-1,0,0,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-3,-1,9,9,9,-1,-3,0},
            {-1,-3,-1,9,19,9,-1,-3,-1},
            {0,-3,-1,9,9,9,-1,-3,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,0,0,-1,-1,-1,0,0,0}
    };

    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 8, m_inW + 8); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 4][k + 4] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 9; m++) {
                for (int n = 0; n < 9; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 8);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}

// 유사연산자
double doubleABS(double x) {
    // 실수의 절대 값 연산 함수
    if (x >= 0) return x;
    else        return -x;
}
void usaImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double max = 0.0; // 블록이 이동할 때 마다 최대값
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            max = 0.0; // 최대값도 초기화
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    if (doubleABS(tmpInput[i + 1][k + 1] -
                        tmpInput[i + m][k + n]) >= max)
                        // 블록의 가운대값 - 블록의 주변 픽셀값의 절대값 중에서
                        // 최대값을 찾는다.
                        max = doubleABS(tmpInput[i + 1][k + 1] - tmpInput[i + m][k + n]);
                }
            }
            tmpOutput[i][k] = max;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 차 연산자
void minusImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    // 임시 입력/출력 메모리 준비
    double** tmpInput = malloc2D_double(m_inH + 2, m_inW + 2); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = malloc2D_double(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tmpInput[i + 1][k + 1] = m_InImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double max = 0.0; // 블록이 이동할 때 마다 최대값
    double mask[4] = { 0, };
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            max = 0.0; // 최대값 초기화
            mask[0] = doubleABS(tmpInput[i][k] - tmpInput[i + 2][k + 2]);
            mask[1] = doubleABS(tmpInput[i][k + 1] - tmpInput[i + 2][k + 1]);
            mask[2] = doubleABS(tmpInput[i][k + 2] - tmpInput[i + 2][k]);
            mask[3] = doubleABS(tmpInput[i + 1][k] - tmpInput[i + 1][k + 2]);
            for (int m = 0; m < 4; m++) {
                if (mask[m] >= max) max = mask[m];
            }
            tmpOutput[i][k] = max;
        }
    }

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            m_OutImage[i][k] = (UC)v;
        }
    }
    free2D_double(tmpInput, m_inH + 2);
    free2D_double(tmpOutput, m_outH);
    displayImage();
}
// 영상 확대, 양선형 보간법
void zoomInYSImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    double scale = 0.0;
    printf("원하는 확대배율 :"); scanf("%lf", &scale);
    m_outH = m_inH * scale;
    m_outW = m_inW * scale;
    double** tempImage = malloc2D_double(m_inH, m_inW);
    m_OutImage = malloc2D(m_outH, m_outW);

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            tempImage[i][k] = (double)m_InImage[i][k];
        }
    }

    double r_H, r_W, s_H, s_W;
    int i_W, i_H;
    double C1, C2, C3, C4;
    int v = 0;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            r_H = i / scale;
            r_W = k / scale;

            i_H = (int)floor(r_H); //  내림. celi = 올림
            i_W = (int)floor(r_W);

            s_H = r_H - i_H;
            s_W = r_W - i_W;

            if (i_H < 0 || i_H >= (m_inH - 1) || i_W < 0 || i_W >= (m_inW - 1)) {
                m_OutImage[i][k] = 255;
            }
            else
            {
                C1 = (double)tempImage[i_H][i_W];           // A
                C2 = (double)tempImage[i_H][i_W + 1];       // B
                C3 = (double)tempImage[i_H + 1][i_W + 1];   // C
                C4 = (double)tempImage[i_H + 1][i_W];       // D
            }
            v = (UC)(C1 * (1 - s_H) * (1 - s_W) + C2 * s_W * (1 - s_H)
                + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
            m_OutImage[i][k] = v;
        }
    }
    free2D_double(tempImage, m_inH);
    displayImage();
}
// 영상 회전 양선형 보간법 : 미완성
void rotateYSImage() {// 영상 회전 알고리즘. 중앙회전+백워딩+확대

    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH); // 해제가 위에 오는 이유는 출력 width,height가 입력과 다를 수 있기 때문에 폭넓이 결정전에 해야한다.


    // 진짜 영상처리 알고리즘

    int angle; // 0~ 360 인데 컴퓨터는 radian으로 인식 따라서 변환해주어야함
    printf("이동 각도 크기 입력:\n  ");
    scanf("%d", &angle);



    double radian = (angle * 3.141592) / 180.0;
    double radian90 = ((90 - angle) * 3.141592) / 180.0;  // 90도 넘는 각을 어떻게 계산할지 생각
    // newX = cos * x - sin * y  영상 회전 공식 x = i , y = k
    // newY = sin * x + cos * y



    //(중요!) 출력 영상의 높이와 폭을 결정해야한다 --> 알고리즘에 따라 달라져야함

    m_outH = (int)(m_inH * fabs(cos(radian90)) + m_inW * fabs(cos(radian)));     // 확대를 위해 입력받은 뒤 상 출력 폭 넓이 정해야 해서 위치를 아래로
    m_outW = (int)(m_inW * fabs(cos(radian)) + m_inW * fabs(cos(radian90)));   // 실수형을 정수로 바꿧다. 실수가 나올 수 있기 때문  
                                                                                 // cos값이 음수될 수 있기 떄문에 fabs로 실수일때 절대값 취해줌
    // 출력 영상 메모리 할당

    m_OutImage = malloc2D(m_outH, m_outW);

    // 임시 입력 영상 -----> 출력과 크기가 같게 하고 , 입력 영상에 두기

    UC** tmpInput = malloc2D(m_outH, m_outW); // 임시 입력 영상 메모리 할당 (출력크기로 할당) 


    int dx = (m_outW - m_inW) / 2;
    int dy = (m_outH - m_inH) / 2;

    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {

            tmpInput[i + dy][k + dx] = m_InImage[i][k]; // 원본영상을 tmpInput에 그대로 저장하는데 tmpInput은 (0,0) 좌표에서 중앙으로 이동시킴(dy,dx)
            m_OutImage[i][k] = 0;
        }
    }


    // 중앙 위치 구하기
    int centerx = m_outW / 2; //회전 사진의 중앙
    int centery = m_outH / 2;

    int x1, x2, y1, y2;
    double rx, ry, p, q, value;


    //for (int i = 0; i < m_outH; i++) { // 백워딩, 역방향 사상 : 출력 기준으로 for문 돌려야함
    //	for (int k = 0; k < m_outW; k++) {

    //		int oldI = (cos(radian) * (i - centerx) + sin(radian) * (k - centery)) + centery;  // 중앙기준 회전을 위해 만든 공식 , 백워딩기준으로 바꿈 부호도
    //		int oldK = (-sin(radian) * (i - centerx) + cos(radian) * (k - centery)) + centerx;

    //		if (((0 <= oldI) && (oldI < m_outH)) && ((0 <= oldK) && (oldK < m_outW))) {


    //			tmpOutput[i][k] = tmpInput[oldI][oldK] ;   // 중앙에 놓은 tmpInput을 돌려준다. 


    //		}
    //		


    //	}
    //}

    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {

            // 실수형 변수 rx, ry는 입력 영상에서 참조할 픽셀 값의 실수 좌표 
            rx = (double)(-sin(radian)) * (i - centerx) + cos(radian) * (k - centery) + centerx;
            ry = (double)(cos(radian)) * (i - centerx) + sin(radian) * (k - centery) + centery;

            if (0 <= rx && rx < m_outW && 0 <= ry && ry < m_outH) {
                // x1, x2, y1, y2는 각각(rx, ry) 좌표를 둘러싼 4개의 픽셀 좌표를 나타낸다.
                x1 = (int)rx;
                y1 = (int)ry;

                x2 = x1 + 1;
                if (x2 == m_outW) {
                    x2 = m_outW - 1;
                }

                y2 = y1 + 1;
                if (y2 == m_outH) {
                    y2 = m_outH - 1;
                }
                // p와 q는 0부터 1 사이의 값을 갖는 실수형 변수 
                p = rx - x1;
                q = ry - y1;

                value = (1. - p) * (1. - q) * tmpInput[y1][x1]
                    + p * (1. - q) * tmpInput[y2][x1]
                    + (1. - p) * q * tmpInput[y1][x2]
                    + p * q * tmpInput[y2][x2];


                if (value > 255) {
                    value = 255;
                }
                else if (value < 0) {
                    value = 0;
                }
                m_OutImage[i][k] = (UC)value;
            }

        }
    }

    free2D(tmpInput, m_outH); // 임시 입력 영상 메모리 해줘야 RAM 누수 안일어남
    displayImage();

}

///히스토그램
// 히스토그램 출력
void histImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = 256;
    m_outW = 256;
    int reSize = m_outH * m_outW;
    UC hist[256]; // 히스토그램 행렬
    int LOW = 0;
    int HIGH = 255;
    UC value = 0;

    //초기화
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }
    //빈도수 조사
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            value = m_InImage[i][k];
            hist[value]++;
        }
    }
    // 정규화
    UC min = 0;// 최소값 초기화
    UC max = 0; // 최대값 초기화
    UC dif;
    int hNum = 0;
    for (int i = 0; i < 256; i++) {
        if (hist[i] <= min) min = (UC)hist[i];
        if (hist[i] >= max) max = (UC)hist[i];
    }
    dif = max - min;
    UC scaleHist[256];
    // 정규화 된 히스토그램
    for (int i = 0; i < 256; i++) {
        scaleHist[i] = (UC)((hist[i] - min) * HIGH / dif);
    }
    // 정규화된 히스토그램 출력
    UC* OutImage = (UC*)malloc((reSize) * sizeof(UC));
    // 정규화된히스토그램의값은출력배열에검은점(0)으로표현
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < scaleHist[i]; k++) {
            OutImage[m_outW * (m_outH - k - 1) + i] = 0;
        }
    }
    hNum = 0;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = OutImage[hNum];
            hNum++;
        }
    }
    free(OutImage);
    displayImage();
}
//스트레칭 : 콘스트라트가 낮은 이미지를 선명하게 해준다.
void histStretchImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    int LOW = 0;
    int HIGH = 255;
    UC min = (UC)HIGH;// 최소값 초기화
    UC max = (UC)LOW; // 최대값 초기화

    //입력 영상의 최소값 찾기
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] <= min)
                min = m_InImage[i][k];
        }
    }
    //입력 영상의 최대값 찾기
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            if (m_InImage[i][k] >= max)
                max = m_InImage[i][k];
        }
    }
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            m_OutImage[i][k] = (UC)(m_InImage[i][k] - min) * HIGH / (max - min);
        }
    }
    displayImage();
}
//평활화 : 콘스트라트의 밸런스가 맞아진다.
// 평활화는 히스토그램 막대의 높이를 균일하게하는것.
// != 스트레칭은 히스토그림 막대의 높이는 동일하며 넓게 펼치는것.
void histEqualizeImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;

    int i, j, vmax, vmin;
    double m_HIST[256];
    double m_Sum_of_HIST[256];
    int value;
    unsigned char LOW, HIGH, Temp;
    double SUM = 0.0;

    int size = m_inH * m_inW;
    LOW = 0;
    HIGH = 255;

    // 초기화
    for (int i = 0; i < 256; i++)
        m_HIST[i] = LOW;
    // 빈도수조사
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            value = m_InImage[i][k];
            m_HIST[value]++;
        }
    }
    // 누적히스토그램생성
    for (int i = 0; i < 256; i++) {
        SUM += m_HIST[i];
        m_Sum_of_HIST[i] = SUM;
    }

    m_OutImage = malloc2D(m_outH, m_outW);
    // 입력영상을평활화된영상으로출력
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            Temp = m_InImage[i][k];
            m_OutImage[i][k] = (UC)(m_Sum_of_HIST[Temp] * HIGH / size);
        }
    }

    displayImage();
}