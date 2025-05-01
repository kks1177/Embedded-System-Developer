// CInputDlg_Gamma.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Gamma.h"


// CInputDlg_Gamma 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Gamma, CDialogEx)

CInputDlg_Gamma::CInputDlg_Gamma(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5_GAMMA, pParent)
	, m_value(0)
{

}

CInputDlg_Gamma::~CInputDlg_Gamma()
{
}

void CInputDlg_Gamma::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_Gamma, CDialogEx)
END_MESSAGE_MAP()


// CInputDlg_Gamma 메시지 처리기
