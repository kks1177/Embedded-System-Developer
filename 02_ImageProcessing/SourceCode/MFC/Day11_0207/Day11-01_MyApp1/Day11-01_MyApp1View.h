
// Day11-01_MyApp1View.h: CDay1101MyApp1View 클래스의 인터페이스
//

#pragma once


class CDay1101MyApp1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CDay1101MyApp1View() noexcept;
	DECLARE_DYNCREATE(CDay1101MyApp1View)

// 특성입니다.
public:
	CDay1101MyApp1Doc* GetDocument() const;

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
	virtual ~CDay1101MyApp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Day11-01_MyApp1View.cpp의 디버그 버전
inline CDay1101MyApp1Doc* CDay1101MyApp1View::GetDocument() const
   { return reinterpret_cast<CDay1101MyApp1Doc*>(m_pDocument); }
#endif

