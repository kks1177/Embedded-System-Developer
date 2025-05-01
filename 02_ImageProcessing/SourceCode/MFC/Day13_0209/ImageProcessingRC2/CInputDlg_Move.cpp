// CInputDlg_Move.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Move.h"


// CInputDlg_Move 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Move, CDialog)

CInputDlg_Move::CInputDlg_Move(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG11_MOVE, pParent)
	, m_value1(0)
	, m_value2(0)
{

}

CInputDlg_Move::~CInputDlg_Move()
{
}

void CInputDlg_Move::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
}


BEGIN_MESSAGE_MAP(CInputDlg_Move, CDialog)
END_MESSAGE_MAP()


// CInputDlg_Move 메시지 처리기
