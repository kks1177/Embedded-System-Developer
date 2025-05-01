#pragma once
#include "afxdialogex.h"


// CInput2Dlg 대화 상자

class CInput2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CInput2Dlg)

public:
	CInput2Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInput2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_value1;
	double m_value2;
};
