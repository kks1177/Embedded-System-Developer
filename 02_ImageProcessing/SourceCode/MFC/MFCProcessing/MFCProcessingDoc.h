
// MFCProcessingDoc.h: CMFCProcessingDoc 클래스의 인터페이스
//


#pragma once


class CMFCProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CMFCProcessingDoc)

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
	virtual ~CMFCProcessingDoc();
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
	// 입력 영상 배열
	unsigned char** m_inImage = NULL;
	// 출력 영상 배열
	unsigned char** m_outImage = NULL;

	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	unsigned char** malloc2D(int h, int w);
	void free2D();
	void free2D1(unsigned char** memory, int h);
};
