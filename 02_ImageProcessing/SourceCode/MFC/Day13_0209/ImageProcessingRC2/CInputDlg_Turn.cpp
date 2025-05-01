// CInputDlg_Turn.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Turn.h"


// CInputDlg_Turn 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Turn, CDialog)

CInputDlg_Turn::CInputDlg_Turn(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG7_TURN, pParent)
	, m_value(0)
{

}

CInputDlg_Turn::~CInputDlg_Turn()
{
}

void CInputDlg_Turn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_Turn, CDialog)
END_MESSAGE_MAP()


// CInputDlg_Turn 메시지 처리기
