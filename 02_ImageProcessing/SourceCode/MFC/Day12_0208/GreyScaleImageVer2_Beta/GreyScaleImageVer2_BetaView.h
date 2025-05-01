
// GreyScaleImageVer2_BetaView.h: CGreyScaleImageVer2BetaView 클래스의 인터페이스
//

#pragma once


class CGreyScaleImageVer2BetaView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGreyScaleImageVer2BetaView() noexcept;
	DECLARE_DYNCREATE(CGreyScaleImageVer2BetaView)

// 특성입니다.
public:
	CGreyScaleImageVer2BetaDoc* GetDocument() const;

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
	virtual ~CGreyScaleImageVer2BetaView();
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
	afx_msg void OnBrightControlImage();
	afx_msg void OnBWImage();
	afx_msg void OnClearControlImage();
	afx_msg void OnClearUp();
	afx_msg void OnClearDown();
	afx_msg void OnGrayScale128();
	afx_msg void OnGrayScaleAvg();
	afx_msg void OnGrayScaleInput();
	afx_msg void OnBitCalcAnd();
	afx_msg void OnBitCalcOr();
	afx_msg void OnBitCalcXor();
	afx_msg void OnBitCalcNot();
	afx_msg void OnGammaImage();
	afx_msg void OnRangeEmphasisImage();
	afx_msg void OnParabolaCap();
	afx_msg void OnParabolaCup();
	afx_msg void OnStretchedImage();
	afx_msg void OnPrintHisto();
	afx_msg void OnHistoStretchImage();
	afx_msg void OnHistoEndInImage();
	afx_msg void OnHistoEqualImage();
	afx_msg void OnEmbossingImage();
	afx_msg void OnBlurring33();
	afx_msg void OnBlurring55();
	afx_msg void OnSharpening();
	afx_msg void OnHPFSharp();
	afx_msg void OnLPFSharp();
	afx_msg void OnSmoothingImage();
	afx_msg void OnHorizontalEdge();
	afx_msg void OnVerticalEdge();
	afx_msg void OnHoriVertiEdge();
	afx_msg void OnLRMirroring();
	afx_msg void OnTBMirroring();
	afx_msg void OnTbLrMirroring();
	afx_msg void OnTBLRMirroring();
	afx_msg void OnTurn90Right();
	afx_msg void OnTurn180Right();
	afx_msg void OnTurn270Right();
	afx_msg void OnTurn90Left();
};

#ifndef _DEBUG  // GreyScaleImageVer2_BetaView.cpp의 디버그 버전
inline CGreyScaleImageVer2BetaDoc* CGreyScaleImageVer2BetaView::GetDocument() const
   { return reinterpret_cast<CGreyScaleImageVer2BetaDoc*>(m_pDocument); }
#endif

