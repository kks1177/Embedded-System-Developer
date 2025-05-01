// CInputDlg_Range.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_Range.h"


// CInputDlg_Range 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_Range, CDialog)

CInputDlg_Range::CInputDlg_Range(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG6_RANGE, pParent)
	, m_value1(0)
	, m_value2(0)
{

}

CInputDlg_Range::~CInputDlg_Range()
{
}

void CInputDlg_Range::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
}


BEGIN_MESSAGE_MAP(CInputDlg_Range, CDialog)
END_MESSAGE_MAP()


// CInputDlg_Range 메시지 처리기
