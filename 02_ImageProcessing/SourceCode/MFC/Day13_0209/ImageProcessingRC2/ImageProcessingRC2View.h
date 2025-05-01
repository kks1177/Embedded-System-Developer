
// ImageProcessingRC2View.h: CImageProcessingRC2View 클래스의 인터페이스
//

#pragma once


class CImageProcessingRC2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingRC2View() noexcept;
	DECLARE_DYNCREATE(CImageProcessingRC2View)

// 특성입니다.
public:
	CImageProcessingRC2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProcessingRC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnReverseImage();
	afx_msg void OnBrightControl();
	afx_msg void OnClearUp();
	afx_msg void OnClearDown();
	afx_msg void OnBWImage128();
	afx_msg void OnBWImageAvg();
	afx_msg void OnBWImageInput();
	afx_msg void OnBitCalcAnd();
	afx_msg void OnBitCalcOr();
	afx_msg void OnBitCalcXor();
	afx_msg void OnBitCalcNot();
	afx_msg void OnGammaImage();
	afx_msg void OnRangeEmphasis();
	afx_msg void OnParabolaCap();
	afx_msg void OnParabolaCup();
	afx_msg void OnStretchedImage();
	afx_msg void OnPrintHisto();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEndIn();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurring33();
	afx_msg void OnBlurring55();
	afx_msg void OnSharpning();
	afx_msg void OnHPFSharp();
	afx_msg void OnlPFSharp();
	afx_msg void OnSmoothing();
	afx_msg void OnHorizontalEdge();
	afx_msg void OnVerticalEdge();
	afx_msg void OnHoriVertiEdge();
	afx_msg void OnLRMirroring();
	afx_msg void OnTBMirroring();
	afx_msg void OnTBLRMirroring();
	afx_msg void OnTurn90Right();
	afx_msg void OnTurn180Right();
	afx_msg void OnTurn270Right();
	afx_msg void OnTurn90Left();
	afx_msg void OnTurn180Left();
	afx_msg void OnTurn270Left();
	afx_msg void OnTurnFree();
	afx_msg void OnTurnFreeCenter();
	afx_msg void OnSizeUp();
	afx_msg void OnBackwardMappingSizeUp();
	afx_msg void OnSizeDown();
	afx_msg void OnBackwardMappingSizeDown();
	afx_msg void OnMoveImage();
	afx_msg void OnWarpingImage();
	afx_msg void OnGreyScale();
};

#ifndef _DEBUG  // ImageProcessingRC2View.cpp의 디버그 버전
inline CImageProcessingRC2Doc* CImageProcessingRC2View::GetDocument() const
   { return reinterpret_cast<CImageProcessingRC2Doc*>(m_pDocument); }
#endif

