#pragma once
#include "afxdialogex.h"


// CInputDlg_Stretched 대화 상자

class CInputDlg_Stretched : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_Stretched)

public:
	CInputDlg_Stretched(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Stretched();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9_STRETCHED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_value;
};
