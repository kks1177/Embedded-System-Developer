// CInputDlg_Bright.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Bright.h"


// CInputDlg_Bright 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Bright, CDialog)

CInputDlg_Bright::CInputDlg_Bright(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_BRIGHT_DIALOG, pParent)
	, m_value(0)
{

}

CInputDlg_Bright::~CInputDlg_Bright()
{
}

void CInputDlg_Bright::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_Bright, CDialog)
	ON_BN_CLICKED(IDOK, &CInputDlg_Bright::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputDlg_Bright 메시지 처리기


void CInputDlg_Bright::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
