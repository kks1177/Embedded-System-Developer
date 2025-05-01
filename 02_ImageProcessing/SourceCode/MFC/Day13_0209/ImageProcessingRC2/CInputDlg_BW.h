#pragma once
#include "afxdialogex.h"


// CInputDlg_BW 대화 상자

class CInputDlg_BW : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_BW)

public:
	CInputDlg_BW(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_BW();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_B_W_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_value1;
	int m_value2;
};
