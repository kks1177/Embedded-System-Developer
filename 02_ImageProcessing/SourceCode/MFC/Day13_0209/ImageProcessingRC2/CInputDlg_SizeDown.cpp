// CInputDlg_SizeDown.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_SizeDown.h"


// CInputDlg_SizeDown 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_SizeDown, CDialog)

CInputDlg_SizeDown::CInputDlg_SizeDown(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG10_SIZE_DOWN, pParent)
	, m_value(0)
{

}

CInputDlg_SizeDown::~CInputDlg_SizeDown()
{
}

void CInputDlg_SizeDown::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_SizeDown, CDialog)
END_MESSAGE_MAP()


// CInputDlg_SizeDown 메시지 처리기
