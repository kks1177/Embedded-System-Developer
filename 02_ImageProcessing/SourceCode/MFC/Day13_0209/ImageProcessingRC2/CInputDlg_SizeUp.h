#pragma once
#include "afxdialogex.h"


// CInputDlg_SizeUp 대화 상자

class CInputDlg_SizeUp : public CDialog
{
	DECLARE_DYNAMIC(CInputDlg_SizeUp)

public:
	CInputDlg_SizeUp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInputDlg_SizeUp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8_SIZE_UP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_value;
};
