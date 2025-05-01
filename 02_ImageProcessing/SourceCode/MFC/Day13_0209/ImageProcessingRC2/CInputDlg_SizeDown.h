#pragma once
#include "afxdialogex.h"


// CInputDlg_SizeDown 대화 상자

class CInputDlg_SizeDown : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_SizeDown)

public:
	CInputDlg_SizeDown(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_SizeDown();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10_SIZE_DOWN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_value;
};
