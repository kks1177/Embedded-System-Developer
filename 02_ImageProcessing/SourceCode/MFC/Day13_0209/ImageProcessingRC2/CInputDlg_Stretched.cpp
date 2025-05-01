// CInputDlg_Stretched.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Stretched.h"


// CInputDlg_Stretched 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Stretched, CDialog)

CInputDlg_Stretched::CInputDlg_Stretched(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG9_STRETCHED, pParent)
	, m_value(0)
{

}

CInputDlg_Stretched::~CInputDlg_Stretched()
{
}

void CInputDlg_Stretched::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_Stretched, CDialog)
END_MESSAGE_MAP()


// CInputDlg_Stretched 메시지 처리기
