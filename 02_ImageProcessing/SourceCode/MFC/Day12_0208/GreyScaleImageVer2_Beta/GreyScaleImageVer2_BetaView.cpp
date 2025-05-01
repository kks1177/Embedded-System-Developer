
// GreyScaleImageVer2_BetaView.cpp: CGreyScaleImageVer2BetaView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GreyScaleImageVer2_Beta.h"
#endif

#include "GreyScaleImageVer2_BetaDoc.h"
#include "GreyScaleImageVer2_BetaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGreyScaleImageVer2BetaView

IMPLEMENT_DYNCREATE(CGreyScaleImageVer2BetaView, CView)

BEGIN_MESSAGE_MAP(CGreyScaleImageVer2BetaView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGreyScaleImageVer2BetaView::OnEqualImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CGreyScaleImageVer2BetaView::OnReverseImage)
	ON_COMMAND(IDM_BRIGHT_CONTROL_IMAGE, &CGreyScaleImageVer2BetaView::OnBrightControlImage)
	ON_COMMAND(IDM_B_W_IMAGE, &CGreyScaleImageVer2BetaView::OnBWImage)
	ON_COMMAND(IDM_CLEAR_UP, &CGreyScaleImageVer2BetaView::OnClearUp)
	ON_COMMAND(IDM_CLEAR_DOWN, &CGreyScaleImageVer2BetaView::OnClearDown)
	ON_COMMAND(IDM_GRAY_SCALE_128, &CGreyScaleImageVer2BetaView::OnGrayScale128)
	ON_COMMAND(IDM_GRAY_SCALE_AVG, &CGreyScaleImageVer2BetaView::OnGrayScaleAvg)
	ON_COMMAND(IDM_GRAY_SCALE_INPUT, &CGreyScaleImageVer2BetaView::OnGrayScaleInput)
	ON_COMMAND(IDM_BIT_CALC_AND, &CGreyScaleImageVer2BetaView::OnBitCalcAnd)
	ON_COMMAND(IDM_BIT_CALC_OR, &CGreyScaleImageVer2BetaView::OnBitCalcOr)
	ON_COMMAND(IDM_BIT_CALC_XOR, &CGreyScaleImageVer2BetaView::OnBitCalcXor)
	ON_COMMAND(IDM_BIT_CALC_NOT, &CGreyScaleImageVer2BetaView::OnBitCalcNot)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CGreyScaleImageVer2BetaView::OnGammaImage)
	ON_COMMAND(IDM_RANGE_EMPHASIS_IMAGE, &CGreyScaleImageVer2BetaView::OnRangeEmphasisImage)
	ON_COMMAND(IDM_PARABOLA_CAP, &CGreyScaleImageVer2BetaView::OnParabolaCap)
	ON_COMMAND(IDM_PARABOLA_CUP, &CGreyScaleImageVer2BetaView::OnParabolaCup)
	ON_COMMAND(IDM_STRETCHED_IMAGE, &CGreyScaleImageVer2BetaView::OnStretchedImage)
	ON_COMMAND(IDM_PRINT_HISTO, &CGreyScaleImageVer2BetaView::OnPrintHisto)
	ON_COMMAND(IDM_HISTO_STRETCH_IMAGE, &CGreyScaleImageVer2BetaView::OnHistoStretchImage)
	ON_COMMAND(IDM_HISTO_END_IN_IMAGE, &CGreyScaleImageVer2BetaView::OnHistoEndInImage)
	ON_COMMAND(IDM_HISTO_EQUAL_IMAGE, &CGreyScaleImageVer2BetaView::OnHistoEqualImage)
	ON_COMMAND(IDM_EMBOSSING_IMAGE, &CGreyScaleImageVer2BetaView::OnEmbossingImage)
	ON_COMMAND(IDM_BLURRING33, &CGreyScaleImageVer2BetaView::OnBlurring33)
	ON_COMMAND(IDM_BLURRING55, &CGreyScaleImageVer2BetaView::OnBlurring55)
	ON_COMMAND(IDM_SHARPENING, &CGreyScaleImageVer2BetaView::OnSharpening)
	ON_COMMAND(IDM_H_P_F_SHARP, &CGreyScaleImageVer2BetaView::OnHPFSharp)
	ON_COMMAND(IDM_L_P_F_SHARP, &CGreyScaleImageVer2BetaView::OnLPFSharp)
	ON_COMMAND(IDM_SMOOTHING_IMAGE, &CGreyScaleImageVer2BetaView::OnSmoothingImage)
	ON_COMMAND(IDM_HORIZONTAL_EDGE, &CGreyScaleImageVer2BetaView::OnHorizontalEdge)
	ON_COMMAND(IDM_VERTICAL_EDGE, &CGreyScaleImageVer2BetaView::OnVerticalEdge)
	ON_COMMAND(IDM_HORI_VERTI_EDGE, &CGreyScaleImageVer2BetaView::OnHoriVertiEdge)
	ON_COMMAND(IDM_L_R_MIRRORING, &CGreyScaleImageVer2BetaView::OnLRMirroring)
	ON_COMMAND(IDM_T_B_MIRRORING, &CGreyScaleImageVer2BetaView::OnTBMirroring)
	//ON_COMMAND(IDM_TB_LR_MIRRORING, &CGreyScaleImageVer2BetaView::OnTbLrMirroring)
	ON_COMMAND(IDM_T_B_L_R_MIRRORING, &CGreyScaleImageVer2BetaView::OnTBLRMirroring)
	ON_COMMAND(IDM_TURN_90_RIGHT, &CGreyScaleImageVer2BetaView::OnTurn90Right)
	ON_COMMAND(IDM_TURN_180_RIGHT, &CGreyScaleImageVer2BetaView::OnTurn180Right)
	ON_COMMAND(IDM_TURN_270_RIGHT, &CGreyScaleImageVer2BetaView::OnTurn270Right)
	ON_COMMAND(IDM_TURN_90_LEFT, &CGreyScaleImageVer2BetaView::OnTurn90Left)
END_MESSAGE_MAP()

// CGreyScaleImageVer2BetaView 생성/소멸

CGreyScaleImageVer2BetaView::CGreyScaleImageVer2BetaView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGreyScaleImageVer2BetaView::~CGreyScaleImageVer2BetaView()
{
}

BOOL CGreyScaleImageVer2BetaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGreyScaleImageVer2BetaView 그리기

// 이미지 화면 출력
void CGreyScaleImageVer2BetaView::OnDraw(CDC* pDC)
{
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int px;

	// 원본 이미지 화면 출력
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			px = pDoc->m_inImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(px, px, px));
		}
	}

	// 결과 이미지 화면 출력
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			px = pDoc->m_outImage[i][k];
			pDC->SetPixel(pDoc->m_outH + k + 5 + 5, i + 5, RGB(px, px, px));
		}
	}
}


// CGreyScaleImageVer2BetaView 인쇄

BOOL CGreyScaleImageVer2BetaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGreyScaleImageVer2BetaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGreyScaleImageVer2BetaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGreyScaleImageVer2BetaView 진단

#ifdef _DEBUG
void CGreyScaleImageVer2BetaView::AssertValid() const
{
	CView::AssertValid();
}

void CGreyScaleImageVer2BetaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGreyScaleImageVer2BetaDoc* CGreyScaleImageVer2BetaView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGreyScaleImageVer2BetaDoc)));
	return (CGreyScaleImageVer2BetaDoc*)m_pDocument;
}
#endif //_DEBUG


// CGreyScaleImageVer2BetaView 메시지 처리기

// =========================== < 1.화소점 처리 기능 함수 선언부 > ======================== //

// 동일 이미지 - View.cpp
void CGreyScaleImageVer2BetaView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}

// 반전 이미지 - View.cpp
void CGreyScaleImageVer2BetaView::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE);
}

// 밝기 조절 이미지 - View.cpp
void CGreyScaleImageVer2BetaView::OnBrightControlImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBrightControlImage();
	Invalidate(TRUE);
}

// 선명도_선명하게 - View.cpp
void CGreyScaleImageVer2BetaView::OnClearUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnClearUp();
	Invalidate(TRUE);
}
// 선명도_흐릿하게 - View.cpp
void CGreyScaleImageVer2BetaView::OnClearDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnClearDown();
	Invalidate(TRUE);
}

// 흑백 이미지 - View.cpp
void CGreyScaleImageVer2BetaView::OnBWImage()
{
	
}
// 흑백 처리 (128 기준) - View.cpp
void CGreyScaleImageVer2BetaView::OnGrayScale128()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale128();
	Invalidate(TRUE);
}
// 흑백 처리 (평균값 기준) - View.cpp
void CGreyScaleImageVer2BetaView::OnGrayScaleAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScaleAvg();
	Invalidate(TRUE);
}
// 흑백 처리 (입력값 기준) - View.cpp
void CGreyScaleImageVer2BetaView::OnGrayScaleInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScaleInput();
	Invalidate(TRUE);
}

// 비트연산_AND - View.cpp
void CGreyScaleImageVer2BetaView::OnBitCalcAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBitCalcAnd();
	Invalidate(TRUE);
}
// 비트연산_OR - View.cpp
void CGreyScaleImageVer2BetaView::OnBitCalcOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBitCalcOr();
	Invalidate(TRUE);
}
// 비트연산_XOR - View.cpp
void CGreyScaleImageVer2BetaView::OnBitCalcXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBitCalcXor();
	Invalidate(TRUE);
}
// 비트연산_NOT - View.cpp
void CGreyScaleImageVer2BetaView::OnBitCalcNot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBitCalcNot();
	Invalidate(TRUE);
}

// 감마 변환 - View.cpp
void CGreyScaleImageVer2BetaView::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE);
}

// 범위 강조 - View.cpp
void CGreyScaleImageVer2BetaView::OnRangeEmphasisImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnRangeEmphasisImage();
	Invalidate(TRUE);
}

// 파라볼라 CAP 변환 - View.cpp
void CGreyScaleImageVer2BetaView::OnParabolaCap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCap();
	Invalidate(TRUE);
}
// 파라볼라 CUP 변환 - View.cpp
void CGreyScaleImageVer2BetaView::OnParabolaCup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCup();
	Invalidate(TRUE);
}

// 명암대비 스트래칭 - View.cpp
void CGreyScaleImageVer2BetaView::OnStretchedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnStretchedImage();
	Invalidate(TRUE);
}


// ===================== < 2.화소점(히스토그램) 처리 기능 함수 선언부 > ===================== //

// 히스토그램 출력 - View.cpp
void CGreyScaleImageVer2BetaView::OnPrintHisto()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnPrintHisto();
	Invalidate(TRUE);
}

// 히스토그램 스트래칭 - View.cpp
void CGreyScaleImageVer2BetaView::OnHistoStretchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretchImage();
	Invalidate(TRUE);
}

// 히스토그램 엔드-인 탐색 - View.cpp
void CGreyScaleImageVer2BetaView::OnHistoEndInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEndInImage();
	Invalidate(TRUE);
}

// 히스토그램 평활화 - View.cpp
void CGreyScaleImageVer2BetaView::OnHistoEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqualImage();
	Invalidate(TRUE);
}


// ========================== < 3.화소영역 처리 기능 함수 선언부 > ======================= //

// 엠보싱 - View.cpp
void CGreyScaleImageVer2BetaView::OnEmbossingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossingImage();
	Invalidate(TRUE);
}

// 3x3 블러링 - View.cpp
void CGreyScaleImageVer2BetaView::OnBlurring33()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBlurring33();
	Invalidate(TRUE);
}
// 5x5 블러링 - View.cpp
void CGreyScaleImageVer2BetaView::OnBlurring55()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBlurring55();
	Invalidate(TRUE);
}

// 샤프닝 - View.cpp
void CGreyScaleImageVer2BetaView::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();
	Invalidate(TRUE);
}
// HPF 샤프닝 - View.cpp
void CGreyScaleImageVer2BetaView::OnHPFSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHPFSharp();
	Invalidate(TRUE);
}
// LPF 샤프닝 - View.cpp
void CGreyScaleImageVer2BetaView::OnLPFSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnLPFSharp();
	Invalidate(TRUE);
}

// 스무딩 (가우시안) - View.cpp
void CGreyScaleImageVer2BetaView::OnSmoothingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnSmoothingImage();
	Invalidate(TRUE);
}


// ========================== < 4.화소영역 (엣지 검출) 처리 기능 함수 선언부 > ======================= //

// 수직 엣지 - View.cpp
void CGreyScaleImageVer2BetaView::OnHorizontalEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHorizontalEdge();
	Invalidate(TRUE);
}
// 수평 엣지 - View.cpp
void CGreyScaleImageVer2BetaView::OnVerticalEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnVerticalEdge();
	Invalidate(TRUE);
}
// 수직 수평 엣지 - View.cpp
void CGreyScaleImageVer2BetaView::OnHoriVertiEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnHoriVertiEdge();
	Invalidate(TRUE);
}


// ============================ < 5.기하학 처리 함수 선언부 > =========================== //

// 좌우 미러링 - View.cpp
void CGreyScaleImageVer2BetaView::OnLRMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnLRMirroring();
	Invalidate(TRUE);
}
// 상하 미러링 - View.cpp
void CGreyScaleImageVer2BetaView::OnTBMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTBMirroring();
	Invalidate(TRUE);
}
// 상하좌우 미러링 - View.cpp
void CGreyScaleImageVer2BetaView::OnTBLRMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTBLRMirroring();
	Invalidate(TRUE);
}

// 오른쪽 90도 회전 - View.cpp
void CGreyScaleImageVer2BetaView::OnTurn90Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTurn90Right();
	Invalidate(TRUE);
}
// 오른쪽 180도 회전 - View.cpp
void CGreyScaleImageVer2BetaView::OnTurn180Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTurn180Right();
	Invalidate(TRUE);
}
// 오른쪽 270도 회전 - View.cpp
void CGreyScaleImageVer2BetaView::OnTurn270Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTurn270Right();
	Invalidate(TRUE);
}
// 왼쪽 90도 회전 - View.cpp
void CGreyScaleImageVer2BetaView::OnTurn90Left()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGreyScaleImageVer2BetaDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnTurn90Left();
	Invalidate(TRUE);
}
