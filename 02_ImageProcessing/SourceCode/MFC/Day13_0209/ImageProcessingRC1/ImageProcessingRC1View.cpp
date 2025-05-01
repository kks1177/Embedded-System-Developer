
// ImageProcessingRC1View.cpp: CImageProcessingRC1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessingRC1.h"
#endif

#include "ImageProcessingRC1Doc.h"
#include "ImageProcessingRC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingRC1View

IMPLEMENT_DYNCREATE(CImageProcessingRC1View, CView)

BEGIN_MESSAGE_MAP(CImageProcessingRC1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImageProcessingRC1View::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CImageProcessingRC1View::OnGrayScale)
END_MESSAGE_MAP()

// CImageProcessingRC1View 생성/소멸

CImageProcessingRC1View::CImageProcessingRC1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingRC1View::~CImageProcessingRC1View()
{
}

BOOL CImageProcessingRC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingRC1View 그리기

// 이미지 화면 출력
void CImageProcessingRC1View::OnDraw(CDC* pDC)
{
	CImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int R, G, B;

	// 원본 이미지 화면 출력
	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			R = pDoc->m_inImageR[i][k];
			G = pDoc->m_inImageG[i][k];
			B = pDoc->m_inImageB[i][k];

			pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
		}
	}

	// 결과 이미지 화면 출력
	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			R = pDoc->m_outImageR[i][k];
			G = pDoc->m_outImageG[i][k];
			B = pDoc->m_outImageB[i][k];
			pDC->SetPixel(pDoc->m_inW + k + 5 + 5, i + 5, RGB(R, G, B));
		}
	}
}

// CImageProcessingRC1View 인쇄

BOOL CImageProcessingRC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingRC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingRC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingRC1View 진단

#ifdef _DEBUG
void CImageProcessingRC1View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingRC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingRC1Doc* CImageProcessingRC1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingRC1Doc)));
	return (CImageProcessingRC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingRC1View 메시지 처리기

// =========================== < 1.화소점 처리 기능 함수 선언부 > ======================== //

// 동일 이미지 - View.cpp
void CImageProcessingRC1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


// ===================== < 2.화소점(히스토그램) 처리 기능 함수 선언부 > ===================== //


// ========================== < 3.화소영역 처리 기능 함수 선언부 > ======================= //


// ========================== < 4.화소영역 (엣지 검출) 처리 기능 함수 선언부 > ======================= //


// ============================ < 5.기하학 처리 함수 선언부 > =========================== //






// =============================================================================== //

// 그레이스케일 - View.cpp
void CImageProcessingRC1View::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingRC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}
