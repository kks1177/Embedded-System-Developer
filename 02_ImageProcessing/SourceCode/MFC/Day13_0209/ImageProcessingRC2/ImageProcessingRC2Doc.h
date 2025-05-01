
// ImageProcessingRC2Doc.h: CImageProcessingRC2Doc 클래스의 인터페이스
//


#pragma once


class CImageProcessingRC2Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingRC2Doc() noexcept;
	DECLARE_DYNCREATE(CImageProcessingRC2Doc)

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
	virtual ~CImageProcessingRC2Doc();
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
	// 입력 영상의 크기 변수 (행/열)
	int m_inH = 0;
	int m_inW = 0;
	// 입력 영상 배열
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;

	// 입력 영상의 크기 변수 (행/열)
	int m_outH = 0;
	int m_outW = 0;
	// 출력 영상 배열
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;


	unsigned char** malloc2D(int h, int w);
	void free2D(unsigned char** memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnReverseImage();
	void OnBrightControl();
	void OnClearUp();
	void OnClearDown();
	void OnBWImage128();
	void OnBWImageAvg();
	void OnBWImageInput();
	void OnBitCalcAnd();
	void OnBitCalcOr();
	void OnBitCalcXor();
	void OnBitCalcNot();
	void OnGammaImage();
	void OnRangeEmphasis();
	void OnParabolaCap();
	void OnParabolaCup();
	void OnStretchedImage();
	void OnPrintHisto();
	void OnHistoStretch();
	void OnHistoEndIn();
	void OnHistoEqual();
	double** malloc2D_double(int row, int col);
	void free2D_double(double** memory, int h);
	void OnEmbossing();
	void OnBlurring33();
	void OnBlurring55();
	void OnSharpning();
	void OnHPFSharp();
	void OnlPFSharp();
	void OnSmoothing();
	void OnHorizontalEdge();
	void OnVerticalEdge();
	void OnHoriVertiEdge();
	void OnLRMirroring();
	void OnTBMirroring();
	void OnTBLRMirroring();
	void OnTurn90Right();
	void OnTurn180Right();
	void OnTurn270Right();
	void OnTurn90Left();
	void OnTurn180Left();
	void OnTurn270Left();
	void OnTurnFree();
	void OnTurnFreeCenter();
	void OnSizeUp();
	void OnBackwardMappingSizeUp();
	void OnSizeDown();
	void OnBackwardMappingSizeDown();
	void OnMoveImage();
	void OnWarpingImage();
	void OnGreyScale();
};
