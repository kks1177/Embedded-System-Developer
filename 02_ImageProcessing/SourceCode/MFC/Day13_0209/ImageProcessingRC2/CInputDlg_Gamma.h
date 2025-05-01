#pragma once
#include "afxdialogex.h"


// CInputDlg_Gamma 대화 상자

class CInputDlg_Gamma : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDlg_Gamma)

public:
	CInputDlg_Gamma(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_Gamma();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAAMA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_value;
};
