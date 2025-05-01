
// GreyScaleImageVer2_BetaDoc.cpp: CGreyScaleImageVer2BetaDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GreyScaleImageVer2_Beta.h"
#endif

#include "GreyScaleImageVer2_BetaDoc.h"
#include "CInputDlg.h"
#include "CInput2Dlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGreyScaleImageVer2BetaDoc

IMPLEMENT_DYNCREATE(CGreyScaleImageVer2BetaDoc, CDocument)

BEGIN_MESSAGE_MAP(CGreyScaleImageVer2BetaDoc, CDocument)
END_MESSAGE_MAP()


// CGreyScaleImageVer2BetaDoc 생성/소멸

CGreyScaleImageVer2BetaDoc::CGreyScaleImageVer2BetaDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGreyScaleImageVer2BetaDoc::~CGreyScaleImageVer2BetaDoc()
{
}

BOOL  CGreyScaleImageVer2BetaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGreyScaleImageVer2BetaDoc serialization

void CGreyScaleImageVer2BetaDoc::Serialize(CArchive& ar)
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
void CGreyScaleImageVer2BetaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CGreyScaleImageVer2BetaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGreyScaleImageVer2BetaDoc::SetSearchContent(const CString& value)
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

// CGreyScaleImageVer2BetaDoc 진단

#ifdef _DEBUG
void CGreyScaleImageVer2BetaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGreyScaleImageVer2BetaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGreyScaleImageVer2BetaDoc 명령

//// ************************* < 이미지 입출력 함수 정의부 > ************************* ////

// 이미지 파일 열기 (입력)
BOOL CGreyScaleImageVer2BetaDoc::OnOpenDocument(LPCTSTR lpszPathName)
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
BOOL CGreyScaleImageVer2BetaDoc::OnSaveDocument(LPCTSTR lpszPathName)
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
// 입출력 이미지 메모리 해제
void CGreyScaleImageVer2BetaDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	free2D(m_inImage, m_inH);
	free2D(m_outImage, m_outH);

	CDocument::OnCloseDocument();
}

// 2차원 배열 생성 함수 (동적 할당)
unsigned char** CGreyScaleImageVer2BetaDoc::malloc2D(int h, int w)
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
void CGreyScaleImageVer2BetaDoc::free2D(unsigned char** memory, int h)
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

	/*
	// C, C++ 둘 다 사용 가능
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


//// ************************* < 1.화소점 처리 기능 함수 정의부 > ********************** ////

// 동일 이미지 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = m_inImage[i][k];
}

// 반전 이미지 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = 255 - m_inImage[i][k];

			m_outImage[i][k] = px;
		}
	}
}

// 밝기 조절 이미지 (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBrightControlImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// Dialog 입력값
	CInputDlg dlg;		// Dialog 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스(Dialog) 인스턴스(dlg)로 선언
	dlg.DoModal();		// Dialog 화면에 출력
	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] + value;

			// 오버플로우,언더플로우 처리
			if (px > 255)			px = 255;
			else	if (px <= 0)	px = 0;

			m_outImage[i][k] = px;
		}
	}
}

// 선명도_선명하게 (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnClearUp()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언

	dlg.DoModal();		// 대화상자 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] * value;

			// 오버플로우,언더플로우 처리
			if (px > 255)			px = 255;
			else	if (px <= 0)	px = 0;

			m_outImage[i][k] = px;
		}
	}
}
// 선명도_흐릿하게 (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnClearDown()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언

	dlg.DoModal();		// 대화상자 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] / value;

			// 오버플로우,언더플로우 처리
			if (px > 255)			px = 255;
			else	if (px <= 0)	px = 0;

			m_outImage[i][k] = px;
		}
	}
}

// 흑백 이미지 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBWImage()
{
}
// 흑백 처리 (128 기준) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnGrayScale128()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if (px > 128)		px = 255;
			else					px = 0;

			m_outImage[i][k] = px;
		}
	}
}
// 흑백 처리 (평균값 기준) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnGrayScaleAvg()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	int pixSum = 0;
	int pixAvg = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			pixSum += px;
		}
	}
	pixAvg = pixSum / (m_inH * m_inW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if (px > pixAvg)		px = 255;
			else						px = 0;

			m_outImage[i][k] = px;
		}
	}
}
// 흑백 처리 (입력값 기준) (2입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnGrayScaleInput()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInput2Dlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언
	
	dlg.DoModal();		// 대화상자 화면에 출력

	int value1 = dlg.m_value1;		// 대화상자로 들어온 value 값을 int value에 저장
	int value2 = dlg.m_value2;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if (px >= value1)			px = 255;
			else if (px <= value2)		px = 0;
			else								m_outImage[i][k] = px;

			m_outImage[i][k] = px;
		}
	}
}

// 비트연산_AND (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBitCalcAnd()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// Dialog 입력값
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언
	dlg.DoModal();		// 대화상자 화면에 출력
	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] & value;

			m_outImage[i][k] = px;
		}
	}
}
// 비트연산_OR (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBitCalcOr()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// Dialog 입력값
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언
	dlg.DoModal();		// 대화상자 화면에 출력
	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] | value;

			m_outImage[i][k] = px;
		}
	}
}
// 비트연산_XOR (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBitCalcXor()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// Dialog 입력값
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언
	dlg.DoModal();		// 대화상자 화면에 출력
	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k] ^ value;

			m_outImage[i][k] = px;
		}
	}
}
// 비트연산_NOT - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBitCalcNot()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = ~m_inImage[i][k];

			m_outImage[i][k] = px;
		}
	}
}

// 감마 변환 이미지 (입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언

	dlg.DoModal();		// 대화상자 화면에 출력

	float value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			float gamma = pow(float(m_inImage[i][k]), 1 / value);

			if (gamma > 255)			gamma = 255;
			else	if (gamma < 0)		gamma = 0;
			else								m_outImage[i][k] = gamma;

			m_outImage[i][k] = gamma;
		}
	}
}

// 범위 강조 이미지 (2입력) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnRangeEmphasisImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInput2Dlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언

	dlg.DoModal();		// 대화상자 화면에 출력

	int value1 = dlg.m_value1;		// 대화상자로 들어온 value 값을 int value에 저장
	int value2 = dlg.m_value2;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if ((value1 <= px) && (px < value2))
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = px;
		}
	}
}

// 파라볼라 CAP 변환 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnParabolaCap()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			float px = (4 / 255.0) * m_inImage[i][k] * (255 - m_inImage[i][k]);

			m_outImage[i][k] = (unsigned char)px;
		}
	}
}
// 파라볼라 CUP 변환 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnParabolaCup()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			float px = (4 / 255.0) * m_inImage[i][k] * (m_inImage[i][k] - 255) + 255;

			m_outImage[i][k] = (unsigned char)px;
		}
	}
}

// 명암대비 스트래칭 (입력) - View.cpp
void CGreyScaleImageVer2BetaDoc::OnStretchedImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	CInputDlg dlg;		// 대화상자 선언					// int 변수명;  char 변수명;  선언하듯  -->  클래스명 인스턴스로 선언

	dlg.DoModal();		// 대화상자 화면에 출력

	float value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			float px = m_inImage[i][k] + (m_outImage[i][k] - 128) * value;

			if (px > 255)		px = 255;
			else if (px < 0)	px = 0;
			else					m_outImage[i][k] = (unsigned char)px;

			m_outImage[i][k] = px;
		}
	}
}
//// ********************************************************************************* ////


//// ************************ < 2.화소점(히스토그램) 처리 기능 함수 정의부 > ************************ ////

// 히스토그램 출력 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnPrintHisto()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	int reSize = m_outH * m_outW;

	// ***** 진짜 영상처리 알고리즘 *****
	unsigned char hist[256] = { 0 };		// 히스토그램 행렬
	int LOW = 0;
	int HIGH = 255;
	unsigned char value = 0;

	// 초기화
	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	// 빈도수 조사
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			value = m_inImage[i][k];
			hist[value]++;
		}
	}

	// 정규화
	unsigned char min = 0;// 최소값 초기화
	unsigned char max = 0; // 최대값 초기화
	unsigned char dif;
	int hNum = 0;

	for (int i = 0; i < 256; i++) {
		if (hist[i] <= min)		min = (unsigned char)hist[i];
		if (hist[i] >= max)		max = (unsigned char)hist[i];
	}
	dif = max - min;
	unsigned char scaleHist[256] = { 0 };

	// 정규화 된 히스토그램
	for (int i = 0; i < 256; i++)
		scaleHist[i] = (unsigned char)((hist[i] - min) * HIGH / dif);

	// 정규화된 히스토그램 출력
	unsigned char* OutImage = (unsigned char*)malloc((reSize) * sizeof(unsigned char));

	// 정규화된히스토그램의 값은 출력배열에 검은점(0)으로 표현
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < scaleHist[i]; k++)
			OutImage[m_outW * (m_outH - k - 1) + i] = 0;

	hNum = 0;
	m_outImage = malloc2D(m_outH, m_outW);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = OutImage[hNum];
			hNum++;
		}
	}
	free(OutImage);
}

// 히스토그램 스트래칭 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnHistoStretchImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	int low = m_inImage[0][0], high = m_inImage[0][0];		// 초기화 가장 안전한 방법

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if (px < low)		low = px;
			if (px > high)		high = px;
		}
	}

	// 공식 
	// out = (in - low) / (high - low) * 255.0;
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = (double)(m_inImage[i][k] - low) / (high - low) * 255.0;
}

// 히스토그램 엔드-인 탐색 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnHistoEndInImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	int low = m_inImage[0][0], high = m_inImage[0][0];		// 초기화 가장 안전한 방법

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][k];

			if (px < low)	low = px;
			if (px > high)	high = px;
		}
	}

	low += 50;
	high -= 50;

	// out = (in - low) / (high - low) * 255.0;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double res = (double)(m_inImage[i][k] - low) / (high - low) * 255.0;

			if (res <= 0.0)
				m_outImage[i][k] = 0;
			else if (res > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = res;
		}
	}
}

// 히스토그램 평활화 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnHistoEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// 1단계 : 히스토그램 생성
	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImage[i][k]]++;

	// 2단계 : 누적 히스토그램 생성 (누적합 생성)
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];

	// 3 단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
	// n = sum * (1/(inH*inW)) * 255.0
	double normalHisto[256] = { 0, };
	for (int i = 0; i < 256; i++)
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;

	// 4단계 : 원래값을 정규화 값으로 치환
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = normalHisto[m_inImage[i][k]];
}
//// ******************************************************************************* ////


//// ************************** < 3.화소 영역 처리 기능 함수 정의부 > ************************** ////

// 2차원 배열 (double) 생성 함수 (동적 할당)
double** CGreyScaleImageVer2BetaDoc::malloc2D_double(int h, int w)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당.										// C++일 때 new와 delete 연산자를 사용			==> 속도가 훨씬 빠름
	retMemory = new double* [h];		// C++ 자체 
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];

	return retMemory;

	// C와 C++ 둘 다 사용 가능
	/*
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;

	// 입력영상(inImage)의 메모리 할당.	
	retMemory = (double**)malloc(h * sizeof(double*));
	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(w * sizeof(double));

	return retMemory;
	*/
}
// free (double) 함수 (메모리 할당 해제 함수부)
void CGreyScaleImageVer2BetaDoc::free2D_double(double** memory, int h)
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

// 엠보싱 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnEmbossingImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 엠보싱 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ { -1,  0,  0},
	  {  0,  0,  0},
	  {  0,  0,  1} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}

// 3x3 블러링 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBlurring33()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 3x3 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
// 5x5 블러링 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnBlurring55()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 5;
	// 5x5 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 4, m_inW + 4);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 4);
	free2D_double(tmpOut, m_outH);
}

// 샤프닝 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnSharpening()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 샤프닝 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  -1, -1, -1  },
	  {  -1,   9, -1  },
	  {  -1, -1, -1  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
// 고주파필터 처리 샤프닝 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnHPFSharp()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 고주파필터 처리 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  -1. / 9,  -1. / 9,  -1. / 9  },
	  {  -1. / 9,   8. / 9,  -1. / 9  },
	  {  -1. / 9,  -1. / 9,  -1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
// 저주파필터 처리 샤프닝 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnLPFSharp()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 저주파필터 처리 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {	 1. / 16,	 2. / 16,	 1. / 16  },
	  {	 2. / 16,	 4. / 16,	 2. / 16  },
	  {	 1. / 16,	 2. / 16,	 1. / 16  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}

// 스무딩 (가우시안) - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnSmoothingImage()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 스무딩 (가우시안) 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 16,  1. / 8,  1. / 16},
	  {  1. / 8,    1. / 4,  1. / 8},
	  {  1. / 16,  1. / 8,  1. / 16} };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
//// ********************************************************************************* ////


//// ************************** < 4.화소 영역 (엣지 검출) 처리 기능 함수 정의부 > ************************** ////

// 수직 엣지 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnHorizontalEdge()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 수직 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  0,  0,  0  },
	  { -1,  1,  0  },
	  {  0,  0,  0  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
// 수평 엣지 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnVerticalEdge()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 수평 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  0, -1,  0  },
	  {  0,  1,  0  },
	  {  0,  0,  0  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpIn[i + m][k + n] * mask[m][n];

			tmpOut[i][k] = S;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v = tmpOut[i][k];

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut, m_outH);
}
// 수직 수평 엣지 - Doc.cp
void CGreyScaleImageVer2BetaDoc::OnHoriVertiEdge()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	const int MSIZE = 3;
	// 수직 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Hmask[MSIZE][MSIZE] =
	{ {  0,  0,  0  },
	  { -1,  1,  0  },
	  {  0,  0,  0  } };
	// 수평 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double Vmask[MSIZE][MSIZE] =
	{ {  0, -1,  0  },
	  {  0,  1,  0  },
	  {  0,  0,  0  } };

	// 임시 입출력 메모리 할당
	double** tmpIn, ** tmpOut1, ** tmpOut2;
	tmpIn = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut1 = malloc2D_double(m_outH, m_outW);
	tmpOut2 = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpIn[i][k] = 0.0;

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpIn[i + 1][k + 1] = m_inImage[i][k];

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S1; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S1 = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S1 += tmpIn[i + m][k + n] * Hmask[m][n];

			tmpOut1[i][k] = S1;
		}
	}
	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S2; // 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S2 = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S2 += tmpIn[i + m][k + n] * Vmask[m][n];

			tmpOut1[i][k] = S2;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOut2[i][k] += 127.0;

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v1 = tmpOut1[i][k];
			double v2 = tmpOut2[i][k];
			double v = v1 + v2;

			if (v > 255.0)		v = 255.0;
			else if (v < 0.0)	v = 0.0;

			m_outImage[i][k] = v;
		}
	free2D_double(tmpIn, m_inH + 2);
	free2D_double(tmpOut1, m_outH);
	free2D_double(tmpOut2, m_outH);
}
//// ********************************************************************************* ////


//// ************************** < 5.기하학 처리 기능 함수 정의부 > ************************** ////

// 좌우 미러링 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnLRMirroring()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[i][m_inW - 1 - k];		// (최대열 - 1) - 반복자

			m_outImage[i][k] = px;
		}
	}
}
// 상하 미러링 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTBMirroring()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int px = m_inImage[m_inH - 1 - i][k];		// (최대행 - 1) - 반복자

			m_outImage[i][k] = px;
		}
	}
}
// 상하좌우 미러링 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTBLRMirroring()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++) {
		for (int k = 0; k < m_inH; k++) {
			int mirror_i = m_inH - 1 - i;			// (최대행 - 1) - 반복자
			int mirror_k = m_inW - 1 - k;		// (최대열 - 1) - 반복자

			m_outImage[i][k] = m_inImage[mirror_i][mirror_k];
		}
	}
}

// 오른쪽 90도 회전 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTurn90Right()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++)
		for (int k = 0; k < m_inH; k++)
			m_outImage[i][k] = m_inImage[m_inH - k - 1][i];			// 최대행 - 반복자 - 1
}
// 오른쪽 180도 회전 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTurn180Right()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++)
		for (int k = 0; k < m_inH; k++)
			m_outImage[i][k] = m_inImage[m_inH - i - 1][m_inW - k - 1];		// 최대행 - 반복자 - 1			// 최대열 - 반복자 - 1
}
// 오른쪽 270도 회전 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTurn270Right()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++)
		for (int k = 0; k < m_inH; k++)
			m_outImage[i][k] = m_inImage[k][m_inH - i - 1];			// 최대행 - 반복자 - 1
}
// 왼쪽 90도 회전 - Doc.cpp
void CGreyScaleImageVer2BetaDoc::OnTurn90Left()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImage, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImage = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			m_outImage[i][k] = m_inImage[k][m_inH - 1 - i];		// 최대행 - 1 - 반복자
}

//// ******************************************************************************* ////



















