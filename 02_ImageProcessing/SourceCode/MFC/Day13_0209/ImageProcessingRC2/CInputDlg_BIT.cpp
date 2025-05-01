// CInputDlg_BIT.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_BIT.h"


// CInputDlg_BIT 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_BIT, CDialog)

CInputDlg_BIT::CInputDlg_BIT(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG4_BIT, pParent)
	, m_value(0)
{

}

CInputDlg_BIT::~CInputDlg_BIT()
{
}

void CInputDlg_BIT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_BIT, CDialog)
END_MESSAGE_MAP()


// CInputDlg_BIT 메시지 처리기
