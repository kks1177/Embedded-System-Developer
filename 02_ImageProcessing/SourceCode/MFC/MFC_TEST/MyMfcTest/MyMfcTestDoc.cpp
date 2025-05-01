
// MyMfcTestDoc.cpp: CMyMfcTestDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MyMfcTest.h"
#endif

#include "MyMfcTestDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMfcTestDoc

IMPLEMENT_DYNCREATE(CMyMfcTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyMfcTestDoc, CDocument)
END_MESSAGE_MAP()


// CMyMfcTestDoc 생성/소멸

CMyMfcTestDoc::CMyMfcTestDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMyMfcTestDoc::~CMyMfcTestDoc()
{
}

BOOL CMyMfcTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMyMfcTestDoc serialization

void CMyMfcTestDoc::Serialize(CArchive& ar)
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
void CMyMfcTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMyMfcTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyMfcTestDoc::SetSearchContent(const CString& value)
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

// CMyMfcTestDoc 진단

#ifdef _DEBUG
void CMyMfcTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyMfcTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyMfcTestDoc 명령


BOOL CMyMfcTestDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;

	// 중요!! 입력 영상의 크기 확인
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);			// = rfp.open(filename, "rb");
	long fLength = File.GetLength();			// 512*512, = 262144
	m_inH = m_inW = (int)sqrt((double)fLength);

	// 입력 영상 메모리 할당
	m_inImage = malloc2D(m_inH, m_inW);

	// 파일 --> 메모리 Loading
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);

	File.Close();

	return TRUE;
}


void CMyMfcTestDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_inImage, m_inH);
	free2D(m_outImage, m_outH);

	CDocument::OnCloseDocument();
}


unsigned char** CMyMfcTestDoc::malloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당. 
	retMemory = (unsigned char**)malloc(h * sizeof(unsigned char*));					// unsigned char 뒤에 * 잊지 말기!
	for (int i = 0; i < h; i++) 				// 가로 픽셀, 세로 픽셀 바뀔 때 범위 주의!
		retMemory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));

	return retMemory;
}


void CMyMfcTestDoc::free2D(unsigned char** memory, int h)
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


// 동일 이미지
void CMyMfcTestDoc::OnEqualImage()
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


// 반전 이미지
void CMyMfcTestDoc::OnNegaImage()
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
