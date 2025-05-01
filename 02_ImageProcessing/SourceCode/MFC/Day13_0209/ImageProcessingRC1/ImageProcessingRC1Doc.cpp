
// ImageProcessingRC1Doc.cpp: CImageProcessingRC1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessingRC1.h"
#endif

#include "ImageProcessingRC1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingRC1Doc

IMPLEMENT_DYNCREATE(CImageProcessingRC1Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingRC1Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingRC1Doc 생성/소멸

CImageProcessingRC1Doc::CImageProcessingRC1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingRC1Doc::~CImageProcessingRC1Doc()
{
}

BOOL CImageProcessingRC1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingRC1Doc serialization

void CImageProcessingRC1Doc::Serialize(CArchive& ar)
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
void CImageProcessingRC1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessingRC1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingRC1Doc::SetSearchContent(const CString& value)
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

// CImageProcessingRC1Doc 진단

#ifdef _DEBUG
void CImageProcessingRC1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingRC1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingRC1Doc 명령

// 2차원 배열 생성 함수 (동적 할당)
unsigned char** CImageProcessingRC1Doc::malloc2D(int h, int w)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당.										// C++일 때 new와 delete 연산자를 사용			==> 속도가 훨씬 빠름
	retMemory = new unsigned char* [h];		// C++ 자체 
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;
}
// free 함수 (메모리 할당 해제 함수부)
void CImageProcessingRC1Doc::free2D(unsigned char** memory, int h)
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
}

// 이미지 파일 열기 (입력)
BOOL CImageProcessingRC1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// 파일 열기를 누르고 취소를 눌렀을 때 종료시킴
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage img;
	img.Load(lpszPathName);

	// 중요! 영상 크기 알아내기
	m_inH = img.GetHeight();
	m_inW = img.GetWidth();

	// 입력영상 메모리 할당
	m_inImageR = malloc2D(m_inH, m_inW);
	m_inImageG = malloc2D(m_inH, m_inW);
	m_inImageB = malloc2D(m_inH, m_inW);

	// CImage를 입력메모리에 가져오기.
	COLORREF px;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			px = img.GetPixel(k, i);
			m_inImageR[i][k] = GetRValue(px);
			m_inImageG[i][k] = GetGValue(px);
			m_inImageB[i][k] = GetBValue(px);
		}
	}
	return TRUE;
}
// 이미지 파일 저장
BOOL CImageProcessingRC1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CImage img;
	img.Create(m_outW, m_outH, 32);		// 저장이 거꾸로 되는 것을 방지하기 위해 W, H 순으로.. , 32bit
	COLORREF px;
	unsigned char R, G, B;
	
	for (int i = 0; i < m_outW; i++) {
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];

			px = RGB(R, G, B);			// 3개를 섞어서 픽셀 하나에 값을 넣음
			img.SetPixel(i, k, px);
		}
	}
	img.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"성공했음", L"저장", NULL);

	return TRUE;
}
// 입출력 이미지 메모리 해제
void CImageProcessingRC1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_inImageR, m_inH);
	free2D(m_inImageG, m_inH);
	free2D(m_inImageB, m_inH);
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	CDocument::OnCloseDocument();
}

//// ************************* < 1.화소점 처리 기능 함수 정의부 > ********************** ////

// 동일 이미지 - Doc.cpp
void CImageProcessingRC1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}


//// ********************************************************************************* ////


//// ************************ < 2.화소점(히스토그램) 처리 기능 함수 정의부 > ************************ ////

//// ******************************************************************************* ////


//// ************************** < 3.화소 영역 처리 기능 함수 정의부 > ************************** ////

//// ********************************************************************************* ////


//// ************************** < 4.화소 영역 (엣지 검출) 처리 기능 함수 정의부 > ************************** ////

//// ********************************************************************************* ////


//// ************************** < 5.기하학 처리 기능 함수 정의부 > ************************** ////

//// ******************************************************************************* ////



// 그레이 스케일 - Doc.cpp
void CImageProcessingRC1Doc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int hap = m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k];
			
			m_outImageR[i][k] = hap / 3.0;
			m_outImageG[i][k] = hap / 3.0;
			m_outImageB[i][k] = hap / 3.0;
		}
	}
}




