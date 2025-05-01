// CInput2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "GreyScaleImageVer2_Beta.h"
#include "afxdialogex.h"
#include "CInput2Dlg.h"


// CInput2Dlg 대화 상자

IMPLEMENT_DYNAMIC(CInput2Dlg, CDialog)

CInput2Dlg::CInput2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, m_value1(0)
	, m_value2(0)
{

}

CInput2Dlg::~CInput2Dlg()
{
}

void CInput2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VALUE, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
}


BEGIN_MESSAGE_MAP(CInput2Dlg, CDialog)
END_MESSAGE_MAP()


// CInput2Dlg 메시지 처리기
