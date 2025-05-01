// CInputDlg_BW.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_BW.h"


// CInputDlg_BW 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_BW, CDialog)

CInputDlg_BW::CInputDlg_BW(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG3_BW, pParent)
	, m_value1(0)
	, m_value2(0)
{

}

CInputDlg_BW::~CInputDlg_BW()
{
}

void CInputDlg_BW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
}


BEGIN_MESSAGE_MAP(CInputDlg_BW, CDialog)
END_MESSAGE_MAP()


// CInputDlg_BW 메시지 처리기
