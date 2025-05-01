
// MFCProcessingDoc.cpp: CMFCProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCProcessing.h"
#endif

#include "MFCProcessingDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCProcessingDoc

IMPLEMENT_DYNCREATE(CMFCProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CMFCProcessingDoc 생성/소멸

CMFCProcessingDoc::CMFCProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCProcessingDoc::~CMFCProcessingDoc()
{
}

BOOL CMFCProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCProcessingDoc serialization

void CMFCProcessingDoc::Serialize(CArchive& ar)
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
void CMFCProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCProcessingDoc::SetSearchContent(const CString& value)
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

// CMFCProcessingDoc 진단

#ifdef _DEBUG
void CMFCProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCProcessingDoc 명령

// 이미지 파일 열기 (입력)
BOOL CMFCProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;

	// 중요!! 입력 영상의 크기 확인
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);			// = rfp.open(filename, "rb");
	// 메모리 누수 방지
	free2D(m_inImage, m_inH);

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

// 이미지 파일 저장
BOOL CMFCProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;

	// 중요!! 입력 영상의 크기 확인
	File.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite);

	// 메모리 --> 파일 Save
	for (int i = 0; i < m_outH; i++)
		File.Write(m_outImage[i], m_outW);

	// 파일 닫기
	File.Close();

	MessageBox(NULL, L"성공했음", L"저장", NULL);

	return TRUE;
	// return 	CDocument::OnSaveDocument(lpszPathName);		// 이름 입력 받기
}

// 입/출력 이미지 메모리 해제
void CMFCProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D1(m_inImage, m_inH);
	free2D1(m_outImage, m_outH);

	CDocument::OnCloseDocument();
}

// 2차원 배열 생성 함수 (동적 할당)
unsigned char** CMFCProcessingDoc::malloc2D(int h, int w)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당.										// C++일 때 new와 delete 연산자를 사용			==> 속도가 훨씬 빠름
	retMemory = new unsigned char* [h];		// C++ 자체 
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;

	// C와 C++ 둘 다 사용 가능
	/*
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당
	retMemory = (unsigned char**)malloc(h * sizeof(unsigned char*));					// unsigned char 뒤에 * 잊지 말기!
	for (int i = 0; i < h; i++) 				// 가로 픽셀, 세로 픽셀 바뀔 때 범위 주의!
		retMemory[i] = (unsigned char*)malloc(w * sizeof(unsigned char));

	return retMemory;
	*/
}

// free 함수 (메모리 할당 해제 함수부)
void CMFCProcessingDoc::free2D1(unsigned char** memory, int h)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가
	if (memory == NULL)
		return;

	// 메모리 해제
	for (int i = 0; i < h; i++)
		delete memory[i];		// == free(memory[i]);

	delete memory;		// == free(memory);
	memory = NULL;

	// C, C++ 둘 다 사용 가능
	/*
	// TODO: 여기에 구현 코드 추가
	if (memory == NULL)
		return;

	// 메모리 해제
	for (int i = 0; i < h; i++)
		free(memory[i]);

	free(memory);
	memory = NULL;
	*/
}

void CMFCProcessingDoc::free2D()
{
	// TODO: 여기에 구현 코드 추가.
}

