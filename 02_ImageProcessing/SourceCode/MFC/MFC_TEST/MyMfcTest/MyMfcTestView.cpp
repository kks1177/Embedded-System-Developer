
// MyMfcTestView.cpp: CMyMfcTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MyMfcTest.h"
#endif

#include "MyMfcTestDoc.h"
#include "MyMfcTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMfcTestView

IMPLEMENT_DYNCREATE(CMyMfcTestView, CView)

BEGIN_MESSAGE_MAP(CMyMfcTestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CMyMfcTestView::OnEqualImage)
	ON_COMMAND(IDM_NEGA_IMAGE, &CMyMfcTestView::OnNegaImage)
END_MESSAGE_MAP()

// CMyMfcTestView 생성/소멸

CMyMfcTestView::CMyMfcTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMyMfcTestView::~CMyMfcTestView()
{
}

BOOL CMyMfcTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyMfcTestView 그리기

void CMyMfcTestView::OnDraw(CDC* pDC)
{
	CMyMfcTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int px;

	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int k = 0; k < pDoc->m_inW; k++) {
			px = pDoc->m_inImage[i][k];
			pDC->SetPixel(k + 5, i + 5, RGB(px, px, px));
		}
	}

	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int k = 0; k < pDoc->m_outW; k++) {
			px = pDoc->m_outImage[i][k];
			pDC->SetPixel(pDoc->m_outH + k + 5 + 5, i + 5, RGB(px, px, px));
		}
	}
}


// CMyMfcTestView 인쇄

BOOL CMyMfcTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMyMfcTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMyMfcTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMyMfcTestView 진단

#ifdef _DEBUG
void CMyMfcTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMfcTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMfcTestDoc* CMyMfcTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMfcTestDoc)));
	return (CMyMfcTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMfcTestView 메시지 처리기


void CMyMfcTestView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMfcTestDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CMyMfcTestView::OnNegaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMyMfcTestDoc* pDoc = GetDocument();			// Document에 접근
	ASSERT_VALID(pDoc);

	pDoc->OnNegaImage();
	Invalidate(TRUE);
}
