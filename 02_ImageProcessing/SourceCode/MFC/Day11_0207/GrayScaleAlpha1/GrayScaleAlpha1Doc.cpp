
// GrayScaleAlpha1Doc.cpp: CGrayScaleAlpha1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleAlpha1.h"
#endif

#include "GrayScaleAlpha1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleAlpha1Doc

IMPLEMENT_DYNCREATE(CGrayScaleAlpha1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleAlpha1Doc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleAlpha1Doc 생성/소멸

CGrayScaleAlpha1Doc::CGrayScaleAlpha1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleAlpha1Doc::~CGrayScaleAlpha1Doc()
{
}

BOOL CGrayScaleAlpha1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleAlpha1Doc serialization

void CGrayScaleAlpha1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleAlpha1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleAlpha1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleAlpha1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleAlpha1Doc 진단

#ifdef _DEBUG
void CGrayScaleAlpha1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleAlpha1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleAlpha1Doc 명령


// 1.이미지 파일 열기 (입력)
BOOL CGrayScaleAlpha1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;

	// 중요!! 입력 영상의 크기 확인
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);			// = rfp.open(filename, "rb");
	long fLength = File.GetLength();			// 512*512, = 262144
	m_inH = m_inW = (int)sqrt((double)fLength);

	// 입력 영상 메모리 동적 할당
	m_inImage = malloc2D(m_inH, m_inW);

	// 파일 --> 메모리 Loading
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);

	// 파일 닫기
	File.Close();

	return TRUE;
}

// 입/출력 이미지 메모리 해제
void CGrayScaleAlpha1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_inImage, m_inH);
	free2D(m_outImage, m_outH);

	CDocument::OnCloseDocument();
}

// 2차원 배열 생성 함수 (동적할당)
unsigned char** CGrayScaleAlpha1Doc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당. 
	retMemory = (unsigned char**)malloc(h * sizeof(unsigned char*));					// unsigned char 뒤에 * 잊지 말기!
	for (int i = 0; i < h; i++) 				// 가로 픽셀, 세로 픽셀 바뀔 때 범위 주의!
		retMemory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));

	return retMemory;
}

// free 함수 (메모리 할당 해제 함수부)
void CGrayScaleAlpha1Doc::free2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가
	if (memory == NULL)
		return;

	// 메모리 해제
	for (int i = 0; i < h; i++)
		free(memory[i]);

	free(memory);
	memory = NULL;
}



// 동일 이미지 - Doc.cpp
void CGrayScaleAlpha1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ** //
	for (int i = 0; i < m_inH; i++) 
		for (int k = 0; k < m_inW; k++) 
			m_outImage[i][k] = m_inImage[i][k];
}

// 반전 이미지 - Doc.cpp
void CGrayScaleAlpha1Doc::OnNegaImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// *** 진짜 영상처리 알고리즘 ** //
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = 255 - m_inImage[i][k];
}
