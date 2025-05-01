
// MFCProcessingView.cpp: CMFCProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCProcessing.h"
#endif

#include "MFCProcessingDoc.h"
#include "MFCProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCProcessingView

IMPLEMENT_DYNCREATE(CMFCProcessingView, CView)

BEGIN_MESSAGE_MAP(CMFCProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCProcessingView 생성/소멸

CMFCProcessingView::CMFCProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCProcessingView::~CMFCProcessingView()
{
}

BOOL CMFCProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCProcessingView 그리기

// 이미지 화면 출력
void CMFCProcessingView::OnDraw(CDC* pDC)
{
	CMFCProcessingDoc* pDoc = GetDocument();
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


// CMFCProcessingView 인쇄

BOOL CMFCProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCProcessingView 진단

#ifdef _DEBUG
void CMFCProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCProcessingDoc* CMFCProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCProcessingDoc)));
	return (CMFCProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCProcessingView 메시지 처리기
