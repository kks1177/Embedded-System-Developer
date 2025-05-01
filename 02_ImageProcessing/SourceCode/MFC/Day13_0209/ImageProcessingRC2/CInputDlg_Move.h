#pragma once
#include "afxdialogex.h"


// CInputDlg_Move 대화 상자

class CInputDlg_Move : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_Move)

public:
	CInputDlg_Move(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Move();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11_MOVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_value1;
	float m_value2;
};
