
// ImageProcessingRC2View.cpp: CImageProcessingRC2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessingRC2.h"
#endif

#include "ImageProcessingRC2Doc.h"
#include "ImageProcessingRC2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingRC2View

IMPLEMENT_DYNCREATE(CImageProcessingRC2View, CView)

BEGIN_MESSAGE_MAP(CImageProcessingRC2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImageProcessingRC2View::OnEqualImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CImageProcessingRC2View::OnReverseImage)
	ON_COMMAND(IDM_BRIGHT_CONTROL, &CImageProcessingRC2View::OnBrightControl)
	ON_COMMAND(IDM_CLEAR_UP, &CImageProcessingRC2View::OnClearUp)
	ON_COMMAND(IDM_CLEAR_DOWN, &CImageProcessingRC2View::OnClearDown)
	ON_COMMAND(IDM_B_W_IMAGE_128, &CImageProcessingRC2View::OnBWImage128)
	ON_COMMAND(IDM_B_W_IMAGE_AVG, &CImageProcessingRC2View::OnBWImageAvg)
	ON_COMMAND(IDM_B_W_IMAGE_INPUT, &CImageProcessingRC2View::OnBWImageInput)
	ON_COMMAND(IDM_BIT_CALC_AND, &CImageProcessingRC2View::OnBitCalcAnd)
	ON_COMMAND(IDM_BIT_CALC_OR, &CImageProcessingRC2View::OnBitCalcOr)
	ON_COMMAND(IDM_BIT_CALC_XOR, &CImageProcessingRC2View::OnBitCalcXor)
	ON_COMMAND(IDM_BIT_CALC_NOT, &CImageProcessingRC2View::OnBitCalcNot)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CImageProcessingRC2View::OnGammaImage)
	ON_COMMAND(IDM_RANGE_EMPHASIS, &CImageProcessingRC2View::OnRangeEmphasis)
	ON_COMMAND(IDM_PARABOLA_CAP, &CImageProcessingRC2View::OnParabolaCap)
	ON_COMMAND(IDM_PARABOLA_Cup, &CImageProcessingRC2View::OnParabolaCup)
	ON_COMMAND(IDM_STRETCHED_IMAGE, &CImageProcessingRC2View::OnStretchedImage)
	ON_COMMAND(IDM_PRINT_HISTO, &CImageProcessingRC2View::OnPrintHisto)
	ON_COMMAND(IDM_HISTO_STRETCH, &CImageProcessingRC2View::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_END_IN, &CImageProcessingRC2View::OnHistoEndIn)
	ON_COMMAND(IDM_HISTO_EQUAL, &CImageProcessingRC2View::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSSING, &CImageProcessingRC2View::OnEmbossing)
	ON_COMMAND(IDM_BLURRING_33, &CImageProcessingRC2View::OnBlurring33)
	ON_COMMAND(IDM_BLURRING_55, &CImageProcessingRC2View::OnBlurring55)
	ON_COMMAND(IDM_SHARPNING, &CImageProcessingRC2View::OnSharpning)
	ON_COMMAND(IDM_H_P_F_SHARP, &CImageProcessingRC2View::OnHPFSharp)
	ON_COMMAND(IDM_l_P_F_SHARP, &CImageProcessingRC2View::OnlPFSharp)
	ON_COMMAND(IDM_SMOOTHING, &CImageProcessingRC2View::OnSmoothing)
	ON_COMMAND(IDM_HORIZONTAL_EDGE, &CImageProcessingRC2View::OnHorizontalEdge)
	ON_COMMAND(IDM_VERTICAL_EDGE, &CImageProcessingRC2View::OnVerticalEdge)
	ON_COMMAND(IDM_HORI_VERTI_EDGE, &CImageProcessingRC2View::OnHoriVertiEdge)
	ON_COMMAND(IDM_L_R_MIRRORING, &CImageProcessingRC2View::OnLRMirroring)
	ON_COMMAND(IDM_T_B_MIRRORING, &CImageProcessingRC2View::OnTBMirroring)
	ON_COMMAND(IDM_T_B_L_R_MIRRORING, &CImageProcessingRC2View::OnTBLRMirroring)
	ON_COMMAND(IDM_TURN_90_RIGHT, &CImageProcessingRC2View::OnTurn90Right)
	ON_COMMAND(IDM_TURN_180_RIGHT, &CImageProcessingRC2View::OnTurn180Right)
	ON_COMMAND(IDM_TURN_270_RIGHT, &CImageProcessingRC2View::OnTurn270Right)
	ON_COMMAND(IDM_TURN_90_LEFT, &CImageProcessingRC2View::OnTurn90Left)
	ON_COMMAND(IDM_TURN_180_LEFT, &CImageProcessingRC2View::OnTurn180Left)
	ON_COMMAND(IDM_TURN_270_LEFT, &CImageProcessingRC2View::OnTurn270Left)
	ON_COMMAND(IDM_TURN_FREE, &CImageProcessingRC2View::OnTurnFree)
	ON_COMMAND(IDM_TURN_FREE_CENTER, &CImageProcessingRC2View::OnTurnFreeCenter)
	ON_COMMAND(IDM_SIZE_UP, &CImageProcessingRC2View::OnSizeUp)
	ON_COMMAND(IDM_BACKWARD_MAPPING_SIZE_UP, &CImageProcessingRC2View::OnBackwardMappingSizeUp)
	ON_COMMAND(IDM_SIZE_DOWN, &CImageProcessingRC2View::OnSizeDown)
	ON_COMMAND(IDM_BACKWARD_MAPPING_SIZE_DOWN, &CImageProcessingRC2View::OnBackwardMappingSizeDown)
	ON_COMMAND(IDM_MOVE_IMAGE, &CImageProcessingRC2View::OnMoveImage)
	ON_COMMAND(IDM_WARPING_IMAGE, &CImageProcessingRC2View::OnWarpingImage)
	ON_COMMAND(IDM_GREY_SCALE, &CImageProcessingRC2View::OnGreyScale)
END_MESSAGE_MAP()

// CImageProcessingRC2View 생성/소멸

CImageProcessingRC2View::CImageProcessingRC2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingRC2View::~CImageProcessingRC2View()
{
}

BOOL CImageProcessingRC2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingRC2View 그리기

// 이미지 화면 출력
void CImageProcessingRC2View::OnDraw(CDC* pDC)
{
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 출력 영상크기 자동 조절
	double MAXSIZE = 800;
	int iW = pDoc->m_inW;
	int iH = pDoc->m_inH;
	double hop = 1.0;

	if (iH > MAXSIZE || iW > MAXSIZE)
	{
		if (pDoc->m_inW > pDoc->m_inH)
			hop = (pDoc->m_inW / MAXSIZE);
		else
			hop = (pDoc->m_inH / MAXSIZE);

		iW = (int)(pDoc->m_inW / hop);
		iH = (int)(pDoc->m_inH / hop);
	}
	// 메모리 DC에 그리기
	for (i = 0; i < iH; i++) {
		for (k = 0; k < iW; k++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	int oW = pDoc->m_outW;
	int oH = pDoc->m_outH;
	double hop2 = 1.0;

	if (oH > MAXSIZE || oW > MAXSIZE)
	{
		if (pDoc->m_outW > pDoc->m_outH)
			hop2 = (pDoc->m_outW / MAXSIZE);
		else
			hop2 = (pDoc->m_outH / MAXSIZE);

		oW = (int)(pDoc->m_outW / hop);
		oH = (int)(pDoc->m_outH / hop);
	}
	for (i = 0; i < oH; i++) {
		for (k = 0; k < oW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop2)][(int)(k * hop2)];
			G = pDoc->m_outImageG[(int)(i * hop2)][(int)(k * hop2)];
			B = pDoc->m_outImageB[(int)(i * hop2)][(int)(k * hop2)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(iW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CImageProcessingRC2View 인쇄

BOOL CImageProcessingRC2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingRC2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingRC2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingRC2View 진단

#ifdef _DEBUG
void CImageProcessingRC2View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingRC2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingRC2Doc* CImageProcessingRC2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingRC2Doc)));
	return (CImageProcessingRC2Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingRC2View 메시지 처리기

// =========================== < 1.화소점 처리 기능 함수 선언부 > ======================== //

// 동일 이미지 - View.cpp
void CImageProcessingRC2View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}

// 반전 이미지 - View.cpp
void CImageProcessingRC2View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnReverseImage();
	Invalidate(TRUE);
}

// 밝기 조절 이미지 - View.cpp
void CImageProcessingRC2View::OnBrightControl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBrightControl();
	Invalidate(TRUE);
}

// 선명도_선명하게 - View.cpp
void CImageProcessingRC2View::OnClearUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnClearUp();
	Invalidate(TRUE);
}
// 선명도_흐릿하게 - View.cpp
void CImageProcessingRC2View::OnClearDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnClearDown();
	Invalidate(TRUE);
}

// 흑백 처리 (128 기준) - View.cpp
void CImageProcessingRC2View::OnBWImage128()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBWImage128();
	Invalidate(TRUE);
}
// 흑백 처리 (평균값 기준) - View.cpp
void CImageProcessingRC2View::OnBWImageAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBWImageAvg();
	Invalidate(TRUE);
}
// 흑백 처리 (입력값 기준) - View.cpp
void CImageProcessingRC2View::OnBWImageInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBWImageInput();
	Invalidate(TRUE);
}
// 그레이 스케일 - View.cpp
void CImageProcessingRC2View::OnGreyScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGreyScale();
	Invalidate(TRUE);
}

// 비트연산_AND - View.cpp
void CImageProcessingRC2View::OnBitCalcAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBitCalcAnd();
	Invalidate(TRUE);
}
// 비트연산_OR - View.cpp
void CImageProcessingRC2View::OnBitCalcOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBitCalcOr();
	Invalidate(TRUE);
}
// 비트연산_XOR - View.cpp
void CImageProcessingRC2View::OnBitCalcXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBitCalcXor();
	Invalidate(TRUE);
}
// 비트연산_NOT - View.cpp
void CImageProcessingRC2View::OnBitCalcNot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBitCalcNot();
	Invalidate(TRUE);
}

// 감마 변환 - View.cpp
void CImageProcessingRC2View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGammaImage();
	Invalidate(TRUE);
}

// 범위 강조 - View.cpp
void CImageProcessingRC2View::OnRangeEmphasis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRangeEmphasis();
	Invalidate(TRUE);
}

// 파라볼라 CAP 변환 - View.cpp
void CImageProcessingRC2View::OnParabolaCap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnParabolaCap();
	Invalidate(TRUE);
}
// 파라볼라 CUP 변환 - View.cpp
void CImageProcessingRC2View::OnParabolaCup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnParabolaCup();
	Invalidate(TRUE);
}

// 명암대비 스트래칭 (입력) - View.cpp
void CImageProcessingRC2View::OnStretchedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnStretchedImage();
	Invalidate(TRUE);
}


// ===================== < 2.화소점(히스토그램) 처리 기능 함수 선언부 > ===================== //

// 히스토그램 출력 - View.cpp
void CImageProcessingRC2View::OnPrintHisto()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnPrintHisto();
	Invalidate(TRUE);
}

// 히스토그램 스트래칭 - View.cpp
void CImageProcessingRC2View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}

// 히스토그램 엔드-인 탐색 - View.cpp
void CImageProcessingRC2View::OnHistoEndIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistoEndIn();
	Invalidate(TRUE);
}

// 히스토그램 평활화 - View.cpp
void CImageProcessingRC2View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


// ========================== < 3.화소영역 처리 기능 함수 선언부 > ======================= //

// 엠보싱 - View.cpp
void CImageProcessingRC2View::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEmbossing();
	Invalidate(TRUE);
}

// 3x3 블러링 - View.cpp
void CImageProcessingRC2View::OnBlurring33()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlurring33();
	Invalidate(TRUE);
}
// 5x5 블러링 - View.cpp
void CImageProcessingRC2View::OnBlurring55()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlurring55();
	Invalidate(TRUE);
}

// 샤프닝 - View.cpp
void CImageProcessingRC2View::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSharpning();
	Invalidate(TRUE);
}
// HPF 샤프닝 - View.cpp
void CImageProcessingRC2View::OnHPFSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHPFSharp();
	Invalidate(TRUE);
}
// LPF 샤프닝 - View.cpp
void CImageProcessingRC2View::OnlPFSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnlPFSharp();
	Invalidate(TRUE);
}

// 스무딩 (가우시안) - View.cpp
void CImageProcessingRC2View::OnSmoothing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSmoothing();
	Invalidate(TRUE);
}


// ========================== < 4.화소영역 (엣지 검출) 처리 기능 함수 선언부 > ======================= //

// 수직 엣지 - View.cpp
void CImageProcessingRC2View::OnHorizontalEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHorizontalEdge();
	Invalidate(TRUE);
}
// 수평 엣지 - View.cpp
void CImageProcessingRC2View::OnVerticalEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnVerticalEdge();
	Invalidate(TRUE);
}
// 수직 수평 엣지 - View.cpp
void CImageProcessingRC2View::OnHoriVertiEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHoriVertiEdge();
	Invalidate(TRUE);
}


// ============================ < 5.기하학 처리 함수 선언부 > =========================== //

// 좌우 미러링 - View.cpp
void CImageProcessingRC2View::OnLRMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLRMirroring();
	Invalidate(TRUE);
}
// 상하 미러링 - View.cpp
void CImageProcessingRC2View::OnTBMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTBMirroring();
	Invalidate(TRUE);
}
// 상하좌우 미러링 - View.cpp
void CImageProcessingRC2View::OnTBLRMirroring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTBLRMirroring();
	Invalidate(TRUE);
}

// 오른쪽 90도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn90Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn90Right();
	Invalidate(TRUE);
}
// 오른쪽 180도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn180Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn180Right();
	Invalidate(TRUE);
}
// 오른쪽 270도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn270Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn270Right();
	Invalidate(TRUE);
}

// 왼쪽 90도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn90Left()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn90Left();
	Invalidate(TRUE);
}
// 왼쪽 180도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn180Left()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn180Left();
	Invalidate(TRUE);
}
// 왼쪽 270도 회전 - View.cpp
void CImageProcessingRC2View::OnTurn270Left()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurn270Left();
	Invalidate(TRUE);
}

// 자유회전_시계방향 (포워딩) - View.cpp
void CImageProcessingRC2View::OnTurnFree()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurnFree();
	Invalidate(TRUE);
}
// 자유회전_시계방향 (백워딩+중앙회전) - View.cpp
void CImageProcessingRC2View::OnTurnFreeCenter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnTurnFreeCenter();
	Invalidate(TRUE);
}

// 이미지 크기 확대 (포워딩) - View.cpp
void CImageProcessingRC2View::OnSizeUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSizeUp();
	Invalidate(TRUE);
}
// 이미지 크기 확대 (백워딩) - View.cpp
void CImageProcessingRC2View::OnBackwardMappingSizeUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBackwardMappingSizeUp();
	Invalidate(TRUE);
}
// 이미지 크기 축소 (포워딩) - View.cpp
void CImageProcessingRC2View::OnSizeDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSizeDown();
	Invalidate(TRUE);
}
// 이미지 크기 축소 (백워딩) - View.cpp
void CImageProcessingRC2View::OnBackwardMappingSizeDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBackwardMappingSizeDown();
	Invalidate(TRUE);
}

// 이미지 이동 - View.cpp
void CImageProcessingRC2View::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMoveImage();
	Invalidate(TRUE);
}

// 워핑 - View.cpp
void CImageProcessingRC2View::OnWarpingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnWarpingImage();
	Invalidate(TRUE);
}

