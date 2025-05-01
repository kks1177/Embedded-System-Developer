
// ImageProcessingRC2Doc.cpp: CImageProcessingRC2Doc 클래스의 구현
//


#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessingRC2.h"
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "ImageProcessingRC2Doc.h"
#include "CInputDlg_Bright.h"
#include "CInputDlg_Clear.h"
#include "CInputDlg_BW.h"
#include "CInputDlg_BIT.h"
#include "CInputDlg_Gamma.h"
#include "CInputDlg_Range.h"
#include "CInputDlg_Turn.h"
#include "CInputDlg_SizeUp.h"
#include "CInputDlg_Stretched.h"
#include "CInputDlg_SizeDown.h"
#include "CInputDlg_Move.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingRC2Doc

IMPLEMENT_DYNCREATE(CImageProcessingRC2Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingRC2Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingRC2Doc 생성/소멸

CImageProcessingRC2Doc::CImageProcessingRC2Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingRC2Doc::~CImageProcessingRC2Doc()
{
}

BOOL CImageProcessingRC2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingRC2Doc serialization

void CImageProcessingRC2Doc::Serialize(CArchive& ar)
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
void CImageProcessingRC2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessingRC2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingRC2Doc::SetSearchContent(const CString& value)
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

// CImageProcessingRC2Doc 진단

#ifdef _DEBUG
void CImageProcessingRC2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingRC2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingRC2Doc 명령

//// ************************* < 이미지 입출력 함수 정의부 > ************************* ////

// 2차원 배열 생성 함수 (동적 할당)
unsigned char** CImageProcessingRC2Doc::malloc2D(int h, int w)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당.										// C++일 때 new와 delete 연산자를 사용			==> 속도가 훨씬 빠름
	retMemory = new unsigned char* [h];		// C++ 자체 
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;

	/*
	// C와 C++ 둘 다 사용 가능
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
void CImageProcessingRC2Doc::free2D(unsigned char** memory, int h)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가
	if (memory == NULL)
		return;

	// 메모리 해제
	for (int i = 0; i < h; i++)
		delete memory[i];		// == free(memory[i]);

	delete memory;			// == free(memory);
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

// 이미지 파일 열기 (입력)
BOOL CImageProcessingRC2Doc::OnOpenDocument(LPCTSTR lpszPathName)
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
BOOL CImageProcessingRC2Doc::OnSaveDocument(LPCTSTR lpszPathName)
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
void CImageProcessingRC2Doc::OnCloseDocument()
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
void CImageProcessingRC2Doc::OnEqualImage()
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
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 반전 이미지 - Doc.cpp
void CImageProcessingRC2Doc::OnReverseImage()
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
			int pxR = 255 - m_inImageR[i][k];
			int pxG = 255 - m_inImageG[i][k];
			int pxB = 255 - m_inImageB[i][k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 밝기 조절 이미지 (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnBrightControl()
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
	// Dialog 입력값
	CInputDlg_Bright dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력
	
	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] + value;
			int pxG = m_inImageG[i][k] + value;
			int pxB = m_inImageB[i][k] + value;

			// 오버플로우,언더플로우 처리
			if (pxR > 255 || pxG > 255 || pxB > 255)			pxR = pxG = pxB = 255;
			else	if (pxR <= 0 || pxG <= 0 || pxB <= 0)		pxR = pxG = pxB = 0;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 선명도_선명하게 (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnClearUp()
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
	// Dialog 입력값
	CInputDlg_Clear dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] * value;
			int pxG = m_inImageG[i][k] * value;
			int pxB = m_inImageB[i][k] * value;

			// 오버플로우,언더플로우 처리
			if (pxR > 255 || pxG > 255 || pxB > 255)			pxR = pxG = pxB = 255;
			else	if (pxR <= 0 || pxG <= 0 || pxB <= 0)		pxR = pxG = pxB = 0;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 선명도_흐릿하게 (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnClearDown()
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
	// Dialog 입력값
	CInputDlg_Clear dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] / value;
			int pxG = m_inImageG[i][k] / value;
			int pxB = m_inImageB[i][k] / value;

			// 오버플로우,언더플로우 처리
			if (pxR > 255 || pxG > 255 || pxB > 255)			pxR = pxG = pxB = 255;
			else	if (pxR <= 0 || pxG <= 0 || pxB <= 0)		pxR = pxG = pxB = 0;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 흑백 처리 (128 기준) - Doc.cpp
void CImageProcessingRC2Doc::OnBWImage128()
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
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			/*if (pxR > 128)	m_outImageR[i][k] = 255;
			else					m_outImageR[i][k] = 0;

			if (pxG > 128)	m_outImageG[i][k] = 255;
			else					m_outImageG[i][k] = 0;

			if (pxB > 128)	m_outImageB[i][k] = 255;
			else					m_outImageB[i][k] = 0;*/

			// 오버플로우,언더플로우 처리
			if (pxR > 128 || pxG > 128 || pxB > 128)		pxR = pxG = pxB = 255;
			else															pxR = pxG = pxB = 0;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 흑백 처리 (평균값 기준) - Doc.cpp
void CImageProcessingRC2Doc::OnBWImageAvg()
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
	int pixSumR = 0, pixSumG = 0, pixSumB = 0;
	int pixAvgR = 0, pixAvgG = 0, pixAvgB = 0;

	for (int i = 0; i < m_inH; i++) { 
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			pixSumR += pxR;
			pixSumG += pxG;
			pixSumB += pxB;
		}
	}
	pixAvgR = pixSumR / (m_inH * m_inW);
	pixAvgG = pixSumG / (m_inH * m_inW);
	pixAvgB = pixSumB / (m_inH * m_inW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			// 오버플로우,언더플로우 처리
			if (pxR > pixAvgR || pxG > pixAvgG || pxB > pixAvgB)		pxR = pxG = pxB = 255;
			else																				pxR = pxG = pxB = 0;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 흑백 범위 처리 (입력값 기준) (2입력) - Doc.cpp
void CImageProcessingRC2Doc::OnBWImageInput()
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
	// Dialog 입력값
	CInputDlg_BW dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value1 = dlg.m_value1;		// 대화상자로 들어온 value 값을 int value에 저장
	int value2 = dlg.m_value2;		// 대화상자로 들어온 value 값을 int value에 저장


	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			// 오버플로우,언더플로우 처리
			if (pxR <= value1 || pxG <= value1 || pxB <= value1)		pxR = pxG = pxB = 0;
			else if (pxR > value2 || pxG > value2 || pxB > value2)		pxR = pxG = pxB = 255;
			else	{
				m_outImageR[i][k] = pxR;		m_outImageG[i][k] = pxG;		m_outImageB[i][k] = pxB;
			}
			/*m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;*/
		}
	}
}
// 그레이 스케일 - Doc.cpp
void CImageProcessingRC2Doc::OnGreyScale()
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

// 비트연산_AND (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnBitCalcAnd()
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
	// Dialog 입력값
	CInputDlg_BIT dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] & value;
			int pxG = m_inImageG[i][k] & value;
			int pxB = m_inImageB[i][k] & value;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 비트연산_OR (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnBitCalcOr()
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
	// Dialog 입력값
	CInputDlg_BIT dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] | value;
			int pxG = m_inImageG[i][k] | value;
			int pxB = m_inImageB[i][k] | value;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 비트연산_XOR (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnBitCalcXor()
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
	// Dialog 입력값
	CInputDlg_BIT dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k] ^ value;
			int pxG = m_inImageG[i][k] ^ value;
			int pxB = m_inImageB[i][k] ^ value;

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 비트연산_NOT - Doc.cpp
void CImageProcessingRC2Doc::OnBitCalcNot()
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
			int pxR = ~m_inImageR[i][k];
			int pxG = ~m_inImageG[i][k];
			int pxB = ~m_inImageB[i][k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 감마 변환 이미지 (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnGammaImage()
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
	// Dialog 입력값
	CInputDlg_Gamma dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	float value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			float gammaR = pow(float(pxR), 1 / value);
			float gammaG = pow(float(pxG), 1 / value);
			float gammaB = pow(float(pxB), 1 / value);

			// 오버플로우,언더플로우 처리
			if (gammaR > 255 || gammaG > 255 || gammaB > 255)		gammaR = gammaG = gammaB = 255;
			else	if (gammaR < 0 || gammaG < 0 || gammaB < 0)			gammaR = gammaG = gammaB = 0;
			else {
				m_outImageR[i][k] = gammaR;		m_outImageG[i][k] = gammaG;		m_outImageB[i][k] = gammaB;
			}

			m_outImageR[i][k] = gammaR;
			m_outImageG[i][k] = gammaG;
			m_outImageB[i][k] = gammaB;
		}
	}
}

// 범위 강조 이미지 (2입력) - Doc.cpp
void CImageProcessingRC2Doc::OnRangeEmphasis()
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
	// Dialog 입력값
	CInputDlg_Range dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value1 = dlg.m_value1;		// 대화상자로 들어온 value 값을 int value에 저장
	int value2 = dlg.m_value2;		// 대화상자로 들어온 value 값을 int value에 저장


	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			//// 오버플로우,언더플로우 처리
			/*if (((value1 <= pxR) && (pxR <= value2)) || ((value1 <= pxG) && (pxG <= value2)) || ((value1 <= pxB) && (pxB <= value2)))
				pxR = pxG = pxB = 255;
			else {
				m_outImageR[i][k] = pxR;		m_outImageG[i][k] = pxG;		m_outImageB[i][k] = pxB;
			}

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;*/

			if (value1 <= pxR && pxR <= value2)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = pxR;

			if (value1 <= pxG && pxG <= value2)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = pxG;

			if (value1 <= pxB && pxB <= value2)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = pxB;

		}
	}
}

// 파라볼라 CAP 변환 - Doc.cpp
void CImageProcessingRC2Doc::OnParabolaCap()
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
			float pxR = (4 / 255.0) * m_inImageR[i][k] * (255 - m_inImageR[i][k]);
			float pxG = (4 / 255.0) * m_inImageG[i][k] * (255 - m_inImageG[i][k]);
			float pxB = (4 / 255.0) * m_inImageB[i][k] * (255 - m_inImageB[i][k]);

			m_outImageR[i][k] = (unsigned char)pxR;
			m_outImageG[i][k] = (unsigned char)pxG;
			m_outImageB[i][k] = (unsigned char)pxB;
		}
	}
}
// 파라볼라 CUP 변환 - Doc.cpp
void CImageProcessingRC2Doc::OnParabolaCup()
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
			float pxR = (4 / 255.0) * m_inImageR[i][k] * (m_inImageR[i][k] - 255) + 255;
			float pxG = (4 / 255.0) * m_inImageG[i][k] * (m_inImageG[i][k] - 255) + 255;
			float pxB = (4 / 255.0) * m_inImageB[i][k] * (m_inImageB[i][k] - 255) + 255;

			m_outImageR[i][k] = (unsigned char)pxR;
			m_outImageG[i][k] = (unsigned char)pxG;
			m_outImageB[i][k] = (unsigned char)pxB;
		}
	}
}

// 명암대비 스트래칭 (입력) - Doc.cpp
void CImageProcessingRC2Doc::OnStretchedImage()
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
	// Dialog 입력값
	CInputDlg_Stretched dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			float pxR = m_inImageR[i][k] + (m_outImageR[i][k] - 128) * value;
			float pxG = m_inImageG[i][k] + (m_outImageG[i][k] - 128) * value;
			float pxB = m_inImageB[i][k] + (m_outImageB[i][k] - 128) * value;

			// 오버플로우,언더플로우 처리
			if (pxR > 255 || pxG > 255 || pxB > 255)			pxR = pxG = pxB = 255;
			else	if (pxR <= 0 || pxG <= 0 || pxB <= 0)		pxR = pxG = pxB = 0;
			else	{
				m_outImageR[i][k] = (unsigned char)pxR;		m_outImageG[i][k] = (unsigned char)pxG;		m_outImageB[i][k] = (unsigned char)pxB;
			}

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
//// ********************************************************************************* ////


//// ************************ < 2.화소점(히스토그램) 처리 기능 함수 정의부 > ************************ ////

// 히스토그램 출력 - Doc.cpp
void CImageProcessingRC2Doc::OnPrintHisto()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = 256;
	m_outW = 256;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	// 히스토그램 이미지 크기 (1차원배열화)
	int reSize = m_outH * m_outW;
	int LOW = 0;
	int HIGH = 255;
	// 히스토그램 행렬
	unsigned char histR[256] = { 0 };
	unsigned char histG[256] = { 0 };
	unsigned char histB[256] = { 0 };
	unsigned char valueR = 0;
	unsigned char valueG = 0;
	unsigned char valueB = 0;

	//초기화
	for (int i = 0; i < 256; i++) {
		histR[i] = 0;		histG[i] = 0;		histB[i] = 0;
	}
	//빈도수 조사
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			valueR = m_inImageR[i][k];
			histR[valueR]++;
			valueG = m_inImageG[i][k];
			histG[valueG]++;
			valueB = m_inImageB[i][k];
			histB[valueB]++;
		}
	}
	// 정규화
	// 최소값 초기화
	unsigned char minR = 0;
	unsigned char minG = 0;
	unsigned char minB = 0;
	// 최대값 초기화
	unsigned char maxR = 0;
	unsigned char maxG = 0;
	unsigned char maxB = 0;
	unsigned char difR = 0;
	unsigned char difG = 0;
	unsigned char difB = 0;
	int hNum = 0;

	for (int i = 0; i < 256; i++) {
		if (histR[i] <= minR)		minR = (unsigned char)histR[i];
		if (histR[i] >= maxR)		maxR = (unsigned char)histR[i];
		if (histG[i] <= minG)		minG = (unsigned char)histG[i];
		if (histG[i] >= maxG)		maxG = (unsigned char)histG[i];
		if (histB[i] <= minB)		minB = (unsigned char)histB[i];
		if (histB[i] >= maxB)		maxB = (unsigned char)histB[i];
	}
	difR = maxR - minR; difG = maxG - minG; difB = maxB - minB;

	unsigned char scaleHistR[256] = { 0 };
	unsigned char scaleHistG[256] = { 0 };
	unsigned char scaleHistB[256] = { 0 };

	// 정규화 된 히스토그램
	for (int i = 0; i < 256; i++) {
		scaleHistR[i] = (unsigned char)((histR[i] - minR) * HIGH / difR);
		scaleHistG[i] = (unsigned char)((histG[i] - minG) * HIGH / difG);
		scaleHistB[i] = (unsigned char)((histB[i] - minB) * HIGH / difB);
	}

	// 정규화된 히스토그램 출력
	unsigned char* OutImageR = (unsigned char*)malloc((reSize) * sizeof(unsigned char));
	unsigned char* OutImageG = (unsigned char*)malloc((reSize) * sizeof(unsigned char));
	unsigned char* OutImageB = (unsigned char*)malloc((reSize) * sizeof(unsigned char));

	// 정규화된히스토그램의값은출력배열에검은점(0)으로표현
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < scaleHistR[i]; k++) 
			OutImageR[m_outW * (m_outH - k - 1) + i] = 0;
		
		for (int k = 0; k < scaleHistG[i]; k++) 
			OutImageG[m_outW * (m_outH - k - 1) + i] = 0;
		
		for (int k = 0; k < scaleHistB[i]; k++) 
			OutImageB[m_outW * (m_outH - k - 1) + i] = 0;
	}

	hNum = 0;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = OutImageR[hNum];
			m_outImageG[i][k] = OutImageG[hNum];
			m_outImageB[i][k] = OutImageB[hNum];
			hNum++;
		}
	}
	free(OutImageR); free(OutImageG); free(OutImageB);
}

// 히스토그램 스트래칭 - Doc.cpp
void CImageProcessingRC2Doc::OnHistoStretch()
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
	/* 공식.
	 out = (in - low) / (high - low) * 255.0;.*/

	int lowR = m_inImageR[0][0], highR = m_inImageR[0][0];
	int lowG = m_inImageG[0][0], highG = m_inImageG[0][0];
	int lowB = m_inImageB[0][0], highB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			if (pxR < lowR)				lowR = pxR;
			else if (pxR > highR)		highR = pxR;
			else								pxR;
			if (pxG < lowG)				lowG = pxG;
			else if (pxG > highG)		highG = pxG;
			else								pxG;
			if (pxB < lowB)				lowB = pxB;
			else if (pxB > highB)		highB = pxB;
			else								pxB;

		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			m_outImageR[i][k] = (double)(m_inImageR[i][k] - lowR) / (highR - lowR) * 255.0;
			m_outImageG[i][k] = (double)(m_inImageG[i][k] - lowG) / (highG - lowG) * 255.0;
			m_outImageB[i][k] = (double)(m_inImageB[i][k] - lowB) / (highB - lowB) * 255.0;
		}
	}
}

// 히스토그램 엔드-인 탐색 - Doc.cpp
void CImageProcessingRC2Doc::OnHistoEndIn()
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
	int lowR = m_inImageR[0][0], highR = m_inImageR[0][0];
	int lowG = m_inImageG[0][0], highG = m_inImageG[0][0];
	int lowB = m_inImageB[0][0], highB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];
			
			if (pxR < lowR)				lowR = pxR;
			else if (pxR > highR)		highR = pxR;
			else								pxR;
			if (pxG < lowG)				lowG = pxG;
			else if (pxG > highG)		highG = pxG;
			else								pxG;
			if (pxB < lowB)				lowB = pxB;
			else if (pxB > highB)		highB = pxB;
			else								pxB;
		}
	}
	
	lowR += 50;		highR += 50;
	lowG += 50;		highG += 50;
	lowB += 50;		highB += 50;

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double pxR = (double)(m_inImageR[i][k] - lowR) / (highR - lowR) * 255.0;
			double pxG = (double)(m_inImageG[i][k] - lowG) / (highG - lowG) * 255.0;
			double pxB = (double)(m_inImageB[i][k] - lowB) / (highB - lowB) * 255.0;

			if (pxR > 255.0)			m_outImageR[i][k] = 255;
			else if (pxR <= 0.0)	m_outImageR[i][k] = 0;
			else							m_outImageR[i][k] = pxR;
			if (pxG > 255.0)			m_outImageG[i][k] = 255;
			else if (pxG <= 0.0)	m_outImageG[i][k] = 0;
			else							m_outImageG[i][k] = pxG;
			if (pxB > 255.0)			m_outImageB[i][k] = 255;
			else if (pxB <= 0.0)	m_outImageB[i][k] = 0;
			else							m_outImageB[i][k] = pxB;
		}
	}
}

// 히스토그램 평활화 - Doc.cpp
void CImageProcessingRC2Doc::OnHistoEqual()
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
	// 1단계 : 히스토그램 생성
	int histoR[256] = { 0, }, histoG[256] = { 0, }, histoB[256] = { 0, };
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			histoR[m_inImageR[i][k]]++;
			histoG[m_inImageG[i][k]]++;
			histoB[m_inImageB[i][k]]++;
		}
	}

	// 2단계 : 누적 히스토그램 생성 (누적합 생성)
	int sumHistoR[256] = { 0, }, sumHistoG[256] = { 0, }, sumHistoB[256] = { 0, };
	sumHistoR[0] = histoR[0], sumHistoG[0] = histoG[0], sumHistoB[0] = histoB[0];
	for (int i = 1; i < 256; i++) {
		sumHistoR[i] += sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] += sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] += sumHistoB[i - 1] + histoB[i];
	}

	// 3 단계 : 정규화된 누적 히스토그램 생성 (정규화된 누적합 생성)
	// n = sum * (1/(inH*inW)) * 255.0
	double normalHistoR[256] = { 0, }, normalHistoG[256] = { 0, }, normalHistoB[256] = { 0, };
	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}

	// 4단계 : 원래값을 정규화 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = normalHistoR[m_inImageR[i][k]];
			m_outImageG[i][k] = normalHistoG[m_inImageG[i][k]];
			m_outImageB[i][k] = normalHistoB[m_inImageB[i][k]];
		}
	}
}
//// ******************************************************************************* ////
  

//// ************************** < 3.화소 영역 처리 기능 함수 정의부 > ************************** ////

// 2차원 배열 (double) 생성 함수 (동적 할당)
double** CImageProcessingRC2Doc::malloc2D_double(int row, int col)
{
	// C++ 일 때만 사용 가능
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;			// retMemory == inImage

	// 입력영상(inImage)의 메모리 할당.										// C++일 때 new와 delete 연산자를 사용			==> 속도가 훨씬 빠름
	retMemory = new double* [row];		// C++ 자체 
	for (int i = 0; i < row; i++)
		retMemory[i] = new double[col];

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
void CImageProcessingRC2Doc::free2D_double(double** memory, int h)
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
void CImageProcessingRC2Doc::OnEmbossing()
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
	const int MSIZE = 3;
	// 엠보싱 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ { -1,  0,  0},
	  {  0,  0,  0},
	  {  0,  0,  1} };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}

// 3x3 블러링 - Doc.cpp
void CImageProcessingRC2Doc::OnBlurring33()
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
	const int MSIZE = 3;
	// 3x3 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  },
	  {  1. / 9,  1. / 9,  1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
// 5x5 블러링 - Doc.cpp
void CImageProcessingRC2Doc::OnBlurring55()
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
	const int MSIZE = 5;
	// 5x5 블러링 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  },
	  {  1. / 25,  1. / 25,  1. / 25,  1. / 25,  1. / 25  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 4, m_inW + 4);
	tmpInG = malloc2D_double(m_inH + 4, m_inW + 4);
	tmpInB = malloc2D_double(m_inH + 4, m_inW + 4);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 4);
	free2D_double(tmpInG, m_inH + 4);
	free2D_double(tmpInB, m_inH + 4);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}

// 샤프닝 - Doc.cpp
void CImageProcessingRC2Doc::OnSharpning()
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
	const int MSIZE = 3;
	// 샤프닝 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  -1, -1, -1  },
	  {  -1,   9, -1  },
	  {  -1, -1, -1  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
// 고주파필터 처리 샤프닝 - Doc.cpp
void CImageProcessingRC2Doc::OnHPFSharp()
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
	const int MSIZE = 3;
	// 고주파필터 처리 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  -1. / 9,  -1. / 9,  -1. / 9  },
	  {  -1. / 9,   8. / 9,  -1. / 9  },
	  {  -1. / 9,  -1. / 9,  -1. / 9  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R * 8;
			tmpOutG[i][k] = S_G * 8;
			tmpOutB[i][k] = S_B * 8;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우 추가
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}
	

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <=0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
// 저주파필터 처리 샤프닝 - Doc.cpp
void CImageProcessingRC2Doc::OnlPFSharp()
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
	const int MSIZE = 3;
	// 저주파필터 처리 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {	 1. / 16,	 2. / 16,	 1. / 16  },
	  {	 2. / 16,	 4. / 16,	 2. / 16  },
	  {	 1. / 16,	 2. / 16,	 1. / 16  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = (m_inImageR[i][k] - S_R) * 8;
			tmpOutG[i][k] = (m_inImageG[i][k] - S_G) * 8;
			tmpOutB[i][k] = (m_inImageB[i][k] - S_B) * 8;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	/*for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;

			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)		vR = vG = vB = 0.0;
			else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}

// 스무딩 (가우시안) - Doc.cpp
void CImageProcessingRC2Doc::OnSmoothing()
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
	const int MSIZE = 3;
	// 스무딩 (가우시안) 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  1. / 16,  1. / 8,  1. / 16},
	  {  1. / 8,    1. / 4,  1. / 8},
	  {  1. / 16,  1. / 8,  1. / 16} };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크의 합이 0이 아니므로 주석 처리
	/*
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}
	*/

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/

			m_outImageR[i][k] = vR;
			m_outImageG[i][k] = vG;
			m_outImageB[i][k] = vB;
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
//// ********************************************************************************* ////


//// ************************** < 4.화소 영역 (엣지 검출) 처리 기능 함수 정의부 > ************************** ////

// 수직 엣지 - Doc.cpp
void CImageProcessingRC2Doc::OnHorizontalEdge()
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
	const int MSIZE = 3;
	// 수직 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  0,  0,  0  },
	  { -1,  1,  0  },
	  {  0,  0,  0  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <=0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
// 수평 엣지 - Doc.cpp
void CImageProcessingRC2Doc::OnVerticalEdge()
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
	const int MSIZE = 3;
	// 수평 엣지 마스크 (각 기능에 대한 마스크는 교재나 구글링)
	double mask[MSIZE][MSIZE] =
	{ {  0, -1,  0  },
	  {  0,  1,  0  },
	  {  0,  0,  0  } };

	// 임시 입출력 메모리 할당
	double** tmpInR, ** tmpInG, ** tmpInB, ** tmpOutR, ** tmpOutG, ** tmpOutB;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOutR = malloc2D_double(m_outH, m_outW);
	tmpOutG = malloc2D_double(m_outH, m_outW);
	tmpOutB = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * mask[m][n];
					S_G += tmpInG[i + m][k + n] * mask[m][n];
					S_B += tmpInB[i + m][k + n] * mask[m][n];
				}
			}
			tmpOutR[i][k] = S_R;
			tmpOutG[i][k] = S_G;
			tmpOutB[i][k] = S_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOutR[i][k] += 127.0;
			tmpOutG[i][k] += 127.0;
			tmpOutB[i][k] += 127.0;
		}
	}

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double vR = tmpOutR[i][k];
			double vG = tmpOutG[i][k];
			double vB = tmpOutB[i][k];

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}
	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOutR, m_outH);
	free2D_double(tmpOutG, m_outH);
	free2D_double(tmpOutB, m_outH);
}
// 수직 수평 엣지 - Doc.cp
void CImageProcessingRC2Doc::OnHoriVertiEdge()
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
	double** tmpInR, ** tmpInG, ** tmpInB;
	double **tmpOut1R, ** tmpOut1G, ** tmpOut1B, ** tmpOut2R, ** tmpOut2G, ** tmpOut2B;
	tmpInR = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInG = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpInB = malloc2D_double(m_inH + 2, m_inW + 2);
	tmpOut1R = malloc2D_double(m_outH, m_outW);
	tmpOut1G = malloc2D_double(m_outH, m_outW);
	tmpOut1B = malloc2D_double(m_outH, m_outW);
	tmpOut2R = malloc2D_double(m_outH, m_outW);
	tmpOut2G = malloc2D_double(m_outH, m_outW);
	tmpOut2B = malloc2D_double(m_outH, m_outW);

	// 임시 입력을 0으로 초기화
	for (int i = 0; i < m_inH + 2; i++) {
		for (int k = 0; k < m_inW + 2; k++) {
			tmpInR[i][k] = 0.0;
			tmpInG[i][k] = 0.0;
			tmpInB[i][k] = 0.0;
		}
	}

	// 입력 영상 --> 임시 입력 영상 (inImage --> tmpInImage)
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInR[i + 1][k + 1] = m_inImageR[i][k];
			tmpInG[i + 1][k + 1] = m_inImageG[i][k];
			tmpInB[i + 1][k + 1] = m_inImageB[i][k];
		}
	}

	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S_R;		// 한점에 대한 입력영상X마스크의 합계
	double S_G;		// 한점에 대한 입력영상X마스크의 합계
	double S_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S_R = 0.0;
			S_G = 0.0;
			S_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S_R += tmpInR[i + m][k + n] * Hmask[m][n];
					S_G += tmpInG[i + m][k + n] * Hmask[m][n];
					S_B += tmpInB[i + m][k + n] * Hmask[m][n];
				}
			}
			tmpOut1R[i][k] = S_R;
			tmpOut1G[i][k] = S_G;
			tmpOut1B[i][k] = S_B;
		}
	}
	// 회선 연산 --> 마스크로 긁어가면서 계산하기
	double S2_R;		// 한점에 대한 입력영상X마스크의 합계
	double S2_G;		// 한점에 대한 입력영상X마스크의 합계
	double S2_B;		// 한점에 대한 입력영상X마스크의 합계
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S2_R = 0.0;
			S2_G = 0.0;
			S2_B = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					S2_R += tmpInR[i + m][k + n] * Vmask[m][n];
					S2_G += tmpInG[i + m][k + n] * Vmask[m][n];
					S2_B += tmpInB[i + m][k + n] * Vmask[m][n];
				}
			}
			tmpOut2R[i][k] = S2_R;
			tmpOut2G[i][k] = S2_G;
			tmpOut2B[i][k] = S2_B;
		}
	}

	// 후처리 (마스크의 합계에 따라서 정제...)
	// 마스크 합계가 0일 경우에만 추가 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			tmpOut1R[i][k] += 127.0;
			tmpOut1G[i][k] += 127.0;
			tmpOut1B[i][k] += 127.0;
			tmpOut2R[i][k] += 127.0;
			tmpOut2G[i][k] += 127.0;
			tmpOut2B[i][k] += 127.0;
		}
	}

	// 임시 출력 --> 출력 메모리
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			double v1R = tmpOut1R[i][k];	double v1G = tmpOut1G[i][k];	double v1B = tmpOut1B[i][k];
			double v2R = tmpOut1R[i][k];	double v2G = tmpOut1G[i][k];	double v2B = tmpOut1B[i][k];
			double vR = v1R + v2R;		double vG = v1G + v2G;		double vB = v1B + v2B;

			if (vR > 255)			m_outImageR[i][k] = 255;
			else if (vR <= 0)		m_outImageR[i][k] = 0;
			else						m_outImageR[i][k] = vR;

			if (vG > 255)			m_outImageG[i][k] = 255;
			else if (vG <= 0)		m_outImageG[i][k] = 0;
			else						m_outImageG[i][k] = vG;

			if (vB > 255)			m_outImageB[i][k] = 255;
			else if (vB <= 0)		m_outImageB[i][k] = 0;
			else						m_outImageB[i][k] = vB;
			/*if ((vR > 255.0 || vG > 255.0 || vB > 255.0))		vR = vG = vB = 255.0;
			else if (vR <= 0.0 || vG <= 0.0 || vB <= 0.0)			vR = vG = vB = 0.0;
			else else {
				m_outImageR[i][k] = vR;		m_outImageG[i][k] = vG;		m_outImageB[i][k] = vB;
			}*/
		}

	free2D_double(tmpInR, m_inH + 2);
	free2D_double(tmpInG, m_inH + 2);
	free2D_double(tmpInB, m_inH + 2);
	free2D_double(tmpOut1R, m_outH);
	free2D_double(tmpOut1G, m_outH);
	free2D_double(tmpOut1B, m_outH);
	free2D_double(tmpOut2R, m_outH);
	free2D_double(tmpOut2G, m_outH);
	free2D_double(tmpOut2B, m_outH);
}
//// ********************************************************************************* ////


//// ************************** < 5.기하학 처리 기능 함수 정의부 > ************************** ////

// 좌우 미러링 - Doc.cpp
void CImageProcessingRC2Doc::OnLRMirroring()
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
			int pxR = m_inImageR[i][(m_inW - 1) - k];			// (최대열 - 1) - 반복자
			int pxG = m_inImageG[i][(m_inW - 1) - k];
			int pxB = m_inImageB[i][(m_inW - 1) - k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 상하 미러링 - Doc.cpp
void CImageProcessingRC2Doc::OnTBMirroring()
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
			int pxR = m_inImageR[(m_inH - 1) - i][k];			// (최대행 - 1) - 반복자
			int pxG = m_inImageG[(m_inH - 1) - i][k];
			int pxB = m_inImageB[(m_inH - 1) - i][k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 상하좌우 미러링 - Doc.cpp
void CImageProcessingRC2Doc::OnTBLRMirroring()
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
			int pxR = m_inImageR[(m_inH - 1) - i][(m_inW - 1) - k];			// (최대행 - 1) - 반복자		// (최대열 - 1) - 반복자
			int pxG = m_inImageG[(m_inH - 1) - i][(m_inW - 1) - k];
			int pxB = m_inImageB[(m_inH - 1) - i][(m_inW - 1) - k];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 오른쪽 90도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn90Right()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inW;
	m_outW = m_inH;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++) {
		for (int k = 0; k < m_inH; k++) {
			int pxR = m_inImageR[m_inH - k - 1][i];		// 최대행 - 반복자 - 1
			int pxG = m_inImageG[m_inH - k - 1][i];
			int pxB = m_inImageB[m_inH - k - 1][i];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 오른쪽 180도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn180Right()
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
			int pxR = m_inImageR[m_inH - i - 1][m_inW - k - 1];		// 최대행 - 반복자 - 1			// 최대열 - 반복자 - 1
			int pxG = m_inImageG[m_inH - i - 1][m_inW - k - 1];
			int pxB = m_inImageB[m_inH - i - 1][m_inW - k - 1];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 오른쪽 270도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn270Right()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inW;
	m_outW = m_inH;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++) {
		for (int k = 0; k < m_inH; k++) {
			int pxR = m_inImageR[k][m_inW - i - 1];		// 최대행 - 반복자 - 1
			int pxG = m_inImageG[k][m_inW - i - 1];
			int pxB = m_inImageB[k][m_inW - i - 1];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 왼쪽 90도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn90Left()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inW;
	m_outW = m_inH;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++) {
		for (int k = 0; k < m_inH; k++) {
			int pxR = m_inImageR[k][m_inW - i - 1];		// 최대행 - 반복자 - 1
			int pxG = m_inImageG[k][m_inW - i - 1];
			int pxB = m_inImageB[k][m_inW - i - 1];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 왼쪽 180도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn180Left()
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
			int pxR = m_inImageR[m_inH - i - 1][m_inW - k - 1];		// 최대행 - 반복자 - 1			// 최대열 - 반복자 - 1
			int pxG = m_inImageG[m_inH - i - 1][m_inW - k - 1];
			int pxB = m_inImageB[m_inH - i - 1][m_inW - k - 1];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 왼쪽 270도 회전 - Doc.cpp
void CImageProcessingRC2Doc::OnTurn270Left()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inW;
	m_outW = m_inH;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inW; i++) {
		for (int k = 0; k < m_inH; k++) {
			int pxR = m_inImageR[m_inH - k - 1][i];			// 최대행 - 반복자 - 1
			int pxG = m_inImageG[m_inH - k - 1][i];			// 최대행 - 반복자 - 1
			int pxB = m_inImageB[m_inH - k - 1][i];			// 최대행 - 반복자 - 1

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 자유회전_시계방향 (포워딩) - Doc.cpp
void CImageProcessingRC2Doc::OnTurnFree()
{
	/* 공식
	xd = cos * xs - sin * ys
	yd = sin * xs + cos * ys
	*/
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
	// Dialog 입력값
	CInputDlg_Turn dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	double value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	double radian = value * M_PI / 180.0;

	for (int xs = 0; xs < m_inH; xs++) {
		for (int ys = 0; ys < m_inW; ys++) {
			int xd = cos(radian) * xs - sin(radian) * ys;
			int yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}
// 자유회전_시계방향 (백워딩+중앙회전) - Doc.cpp
void CImageProcessingRC2Doc::OnTurnFreeCenter()
{
	/* 공식
	xs = cos * (xd-cx) + sin * (yd-cy)
	ys = -sin * (xd-cs) + cos * (yd-cy)
	xs += cx;
	ys += cy;
	*/
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);


	// ***** 진짜 영상처리 알고리즘 *****
	// Dialog 입력값
	CInputDlg_Turn dlg;		// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	double value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	double radian = -value * M_PI / 180.0;

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	m_outH = int(fabs(m_inH * cos(radian)) + fabs(m_inW * cos(M_PI / 2 - radian)) + 4.5);
	m_outW = int(fabs(m_inH * cos(M_PI / 2 - radian)) + fabs(m_inW * cos(radian)) + 4.5);
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);

	int cx = m_outH / 2;
	int cy = m_outW / 2;
	int in_cx = m_inH / 2;
	int in_cy = m_inW / 2;
	int xs, ys;

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = 0;
			m_outImageG[i][k] = 0;
			m_outImageB[i][k] = 0;
		}
	}

	for (int xd = 0; xd < m_outH; xd++) {
		for (int yd = 0; yd < m_outW; yd++) {
			xs = int(cos(radian) * (xd - cx + 0.5) + sin(radian) * (yd - cy + 0.5));
			ys = int(-sin(radian) * (xd - cx + 0.5) + cos(radian) * (yd - cy + 0.5));

			xs += in_cx - 1;		ys += in_cy - 1;
			if ((0 <= xs && xs < m_inH) && (0 <= ys && ys < m_inW)) {
				m_outImageR[xd][yd] = m_inImageR[xs][ys];
				m_outImageG[xd][yd] = m_inImageG[xs][ys];
				m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}

// 이미지 크기 확대 (포워딩) - Doc.cpp
void CImageProcessingRC2Doc::OnSizeUp()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// Dialog 입력값
	CInputDlg_SizeUp dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = (int)dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	m_outH = m_inH * value;
	m_outW = m_inW * value;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);


	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			m_outImageR[i * value][k * value] = pxR;
			m_outImageG[i * value][k * value] = pxG;
			m_outImageB[i * value][k * value] = pxB;
		}
	}
}
// 이미지 크기 확대 (백워딩) - Doc.cpp
void CImageProcessingRC2Doc::OnBackwardMappingSizeUp()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// Dialog 입력값
	CInputDlg_SizeUp dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	m_outH = m_inH * value;
	m_outW = m_inW * value;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);


	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i / value][k / value];
			int pxG = m_inImageG[i / value][k / value];
			int pxB = m_inImageB[i / value][k / value];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}
// 이미지 크기 축소 (포워딩) - Doc.cpp
void CImageProcessingRC2Doc::OnSizeDown()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// Dialog 입력값
	CInputDlg_SizeDown dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = (int)dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	m_outH = m_inH / value;
	m_outW = m_inW / value;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);


	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i][k];
			int pxG = m_inImageG[i][k];
			int pxB = m_inImageB[i][k];

			m_outImageR[i * value][k * value] = pxR;
			m_outImageG[i * value][k * value] = pxG;
			m_outImageB[i * value][k * value] = pxB;
		}
	}
}
// 이미지 크기 축소 (백워딩) - Doc.cpp
void CImageProcessingRC2Doc::OnBackwardMappingSizeDown()
{
	// TODO: 여기에 구현 코드 추가.
	free2D(m_outImageR, m_outH);
	free2D(m_outImageG, m_outH);
	free2D(m_outImageB, m_outH);

	// (중요!) 출력영상의 크기를 결정 --> 알고리즘에 의존
	// Dialog 입력값
	CInputDlg_SizeDown dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value = (int)dlg.m_value;		// 대화상자로 들어온 value 값을 int value에 저장

	m_outH = m_inH / value;
	m_outW = m_inW / value;
	m_outImageR = malloc2D(m_outH, m_outW);
	m_outImageG = malloc2D(m_outH, m_outW);
	m_outImageB = malloc2D(m_outH, m_outW);


	// ***** 진짜 영상처리 알고리즘 *****
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int pxR = m_inImageR[i * value][k * value];
			int pxG = m_inImageG[i * value][k * value];
			int pxB = m_inImageB[i * value][k * value];

			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 이미지 이동 - Doc.cpp
void CImageProcessingRC2Doc::OnMoveImage()
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
	CInputDlg_Move dlg;	// Dialog 선언			클래스(CInputDlg_Bright) 인스턴스(dlg)로 선언
	dlg.DoModal();				// Dialog 화면에 출력

	int value1 = dlg.m_value1;		// 대화상자로 들어온 m_value 값을 int value에 저장
	int value2 = dlg.m_value2;		// 대화상자로 들어온 m_value 값을 int value에 저장

	// 출력 이미지 0으로 초기화
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 0;
			m_outImageG[i][k] = 0;
			m_outImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH - value2; i++) {
		for (int k = 0; k < m_inW - value1; k++) {
			int pxR = m_inImageR[i + value2][k + value1];
			int pxG = m_inImageG[i + value2][k + value1];
			int pxB = m_inImageB[i + value2][k + value1];
			
			m_outImageR[i][k] = pxR;
			m_outImageG[i][k] = pxG;
			m_outImageB[i][k] = pxB;
		}
	}
}

// 워핑 - Doc.cpp
void CImageProcessingRC2Doc::OnWarpingImage()
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
	// 출력 이미지 0으로 초기화
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImageR[i][k] = 0;
			m_outImageG[i][k] = 0;
			m_outImageB[i][k] = 0;
		}
	}

	for (int k = 0; k < m_outW; k++) {
		double f_px = (4.0 / pow(m_outW, 2.0)) * k * (m_outW - k) * m_outH;
		double b_px = (4.0 / pow(m_outW, 2.0)) * (k + 1) * (m_outW - k - 1) * m_outH;
		int px = int((f_px + b_px) / 2);
		double rate = double(m_outH) / px;

		for (int i = 0; i < px; i++) {
			unsigned long sumR = 0;
			unsigned long sumG = 0;
			unsigned long sumB = 0;

			for (int j = int(i * rate); j < int((i + 1) * rate); j++) {
				sumR += m_inImageR[j][k];
				sumG += m_inImageG[j][k];
				sumB += m_inImageB[j][k];
			}

			if ((int((i + 1) * rate) - int(i * rate)) != 0) {
				m_outImageR[i][k] = sumR / (int((i + 1) * rate) - int(i * rate));
				m_outImageG[i][k] = sumG / (int((i + 1) * rate) - int(i * rate));
				m_outImageB[i][k] = sumB / (int((i + 1) * rate) - int(i * rate));
			}
			else {
				m_outImageR[i][k] = m_inImageR[int(i * rate)][k];
				m_outImageG[i][k] = m_inImageG[int(i * rate)][k];
				m_outImageB[i][k] = m_inImageB[int(i * rate)][k];
			}
		}
	}
}
//// ********************************************************************************* ////


