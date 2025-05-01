#pragma once
#include "afxdialogex.h"


// CInputDlg_Bright 대화 상자

class CInputDlg_Bright : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_Bright)

public:
	CInputDlg_Bright(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Bright();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRIGHT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_value;
	afx_msg void OnBnClickedOk();
};
