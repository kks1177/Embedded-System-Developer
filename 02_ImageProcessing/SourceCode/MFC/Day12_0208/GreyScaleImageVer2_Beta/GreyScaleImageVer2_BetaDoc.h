
// GreyScaleImageVer2_BetaDoc.h: CGreyScaleImageVer2BetaDoc 클래스의 인터페이스
//


#pragma once


class CGreyScaleImageVer2BetaDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGreyScaleImageVer2BetaDoc() noexcept;
	DECLARE_DYNCREATE(CGreyScaleImageVer2BetaDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGreyScaleImageVer2BetaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	// ============================== < 전역 변수부 (중요!) > ============================== //
	
	// 입력 영상 배열
	unsigned char** m_inImage = NULL;
	// 출력 영상 배열
	unsigned char** m_outImage = NULL;

	 // 입출력 영상의 크기 변수 (행/열)
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;

	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	// 2차원 배열 생성 함수 (동적 할당)
	unsigned char** malloc2D(int h, int w);
	// free 함수 (메모리 할당 해제 함수부)
	void free2D(unsigned char** memory, int h);


	void OnEqualImage();
	void OnReverseImage();
	void OnBrightControlImage();
	void OnBWImage();
	void OnClearUp();
	void OnClearDown();
	void OnGrayScale128();
	void OnGrayScaleAvg();
	void OnGrayScaleInput();
	void OnBitCalcAnd();
	void OnBitCalcOr();
	void OnBitCalcXor();
	void OnBitCalcNot();
	void OnGammaImage();
	void OnRangeEmphasisImage();
	void OnParabolaCap();
	void OnParabolaCup();
	void OnStretchedImage();
	void OnPrintHisto();
	void OnHistoStretchImage();
	void OnHistoEndInImage();
	void OnHistoEqualImage();
	void OnEmbossingImage();
	double** malloc2D_double(int h, int w);
	void free2D_double(double** memory, int h);
	void OnBlurringImage();
	void OnBlurring33();
	void OnBlurring55();
	void OnSharpening();
	void OnHPFSharp();
	void OnLPFSharp();
	void OnSmoothingImage();
	void OnHorizontalEdge();
	void OnVerticalEdge();
	void OnHoriVertiEdge();
	void OnLRMirroring();
	void OnTBMirroring();
	void OnTbLrMirroring();
	void OnTBLRMirroring();
	void OnTurn90Right();
	void OnTurn180Right();
	void OnTurn270Right();
	void OnTurn90Left();
};
