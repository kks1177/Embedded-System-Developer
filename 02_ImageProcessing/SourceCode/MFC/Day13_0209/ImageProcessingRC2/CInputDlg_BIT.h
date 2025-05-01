#pragma once
#include "afxdialogex.h"


// CInputDlg_BIT 대화 상자

class CInputDlg_BIT : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_BIT)

public:
	CInputDlg_BIT(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_BIT();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_value;
};
