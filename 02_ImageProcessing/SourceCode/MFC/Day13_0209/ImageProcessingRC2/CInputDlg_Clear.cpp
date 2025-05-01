// CInputDlg_Clear.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Clear.h"


// CInputDlg_Clear 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Clear, CDialog)

CInputDlg_Clear::CInputDlg_Clear(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CLEAR_DIALOG, pParent)
	, m_value(0)
{

}

CInputDlg_Clear::~CInputDlg_Clear()
{
}

void CInputDlg_Clear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_Clear, CDialog)
END_MESSAGE_MAP()


// CInputDlg_Clear 메시지 처리기
