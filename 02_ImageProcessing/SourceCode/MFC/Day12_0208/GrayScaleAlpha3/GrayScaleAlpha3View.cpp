
// GrayScaleAlpha3View.cpp: CGrayScaleAlpha3View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleAlpha3.h"
#endif

#include "GrayScaleAlpha3Doc.h"
#include "GrayScaleAlpha3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleAlpha3View

IMPLEMENT_DYNCREATE(CGrayScaleAlpha3View, CView)

BEGIN_MESSAGE_MAP(CGrayScaleAlpha3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleAlpha3View::OnEqualImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CGrayScaleAlpha3View::OnReverseImage)
	ON_COMMAND(IDM_BRIGHT_CONTROL_IMAGE, &CGrayScaleAlpha3View::OnBrightControlImage)
	ON_COMMAND(IDM_B_W_INPUT, &CGrayScaleAlpha3View::OnBWInput)
END_MESSAGE_MAP()

// CGrayScaleAlpha3View 생성/소멸

CGrayScaleAlpha3View::CGrayScaleAlpha3View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleAlpha3View::~CGrayScaleAlpha3View()
{
}

BOOL CGrayScaleAlpha3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleAlpha3View 그리기

// 이미지 화면 출력
void CGrayScaleAlpha3View::OnDraw(CDC* pDC)
{
	CGrayScaleAlpha3Doc* pDoc = GetDocument();
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


// CGrayScaleAlpha3View 인쇄

BOOL CGrayScaleAlpha3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleAlpha3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleAlpha3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleAlpha3View 진단

#ifdef _DEBUG
void CGrayScaleAlpha3View::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleAlpha3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleAlpha3Doc* CGrayScaleAlpha3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleAlpha3Doc)));
	return (CGrayScaleAlpha3Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleAlpha3View 메시지 처리기


// 동일 이미지 - View.cpp
void CGrayScaleAlpha3View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleAlpha3Doc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}

// 반전 이미지 - View.cpp
void CGrayScaleAlpha3View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleAlpha3Doc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE);
}

// 밝기 조절 이미지 - View.cpp
void CGrayScaleAlpha3View::OnBrightControlImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleAlpha3Doc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBrightControlImage();
	Invalidate(TRUE);
}

// 흑백 이미지 - View.cpp
void CGrayScaleAlpha3View::OnBWInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleAlpha3Doc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnBWInput();
	Invalidate(TRUE);
}
