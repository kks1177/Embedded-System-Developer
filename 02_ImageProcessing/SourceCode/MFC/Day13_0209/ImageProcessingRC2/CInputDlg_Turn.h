#pragma once
#include "afxdialogex.h"


// CInputDlg_Turn 대화 상자

class CInputDlg_Turn : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_Turn)

public:
	CInputDlg_Turn(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Turn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7_TURN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_value;
};
