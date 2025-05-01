// CInputDlg_SizeUp.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessingRC2.h"
#include "afxdialogex.h"
#include "CInputDlg_SizeUp.h"


// CInputDlg_SizeUp 대화 상자

IMPLEMENT_DYNAMIC(CInputDlg_SizeUp, CDialog)

CInputDlg_SizeUp::CInputDlg_SizeUp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG8_SIZE_UP, pParent)
	, m_value(0)
{

}

CInputDlg_SizeUp::~CInputDlg_SizeUp()
{
}

void CInputDlg_SizeUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value);
}


BEGIN_MESSAGE_MAP(CInputDlg_SizeUp, CDialog)
END_MESSAGE_MAP()


// CInputDlg_SizeUp 메시지 처리기
