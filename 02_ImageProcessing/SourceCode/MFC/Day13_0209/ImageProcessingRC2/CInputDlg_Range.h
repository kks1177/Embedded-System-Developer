#pragma once
#include "afxdialogex.h"


// CInputDlg_Range 대화 상자

class CInputDlg_Range : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_Range)

public:
	CInputDlg_Range(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Range();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6_RANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_value1;
	int m_value2;
};
