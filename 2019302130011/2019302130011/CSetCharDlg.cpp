// CSetCharDlg.cpp: 实现文件
//

#include "pch.h"
#include "2019302130011.h"
#include "CSetCharDlg.h"
#include "afxdialogex.h"


// CSetCharDlg 对话框

IMPLEMENT_DYNAMIC(CSetCharDlg, CDialogEx)

CSetCharDlg::CSetCharDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARBOX, pParent)
	, m_strString(_T(""))
	, m_nX(0)
	, m_nY(0)
{
	m_clrText = RGB(0, 0, 0);
}

CSetCharDlg::~CSetCharDlg()
{
}

void CSetCharDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHAR, m_strString);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
}


BEGIN_MESSAGE_MAP(CSetCharDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CSetCharDlg::OnClickedButtonFont)
END_MESSAGE_MAP()


// CSetCharDlg 消息处理程序


void CSetCharDlg::OnClickedButtonFont()
{
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_fnt.DeleteObject();
		LOGFONT LogFnt;
		dlg.GetCurrentFont(&LogFnt);//保存所选字体
		m_fnt.CreateFontIndirect(&LogFnt);//创建所选字体
		m_clrText = dlg.GetColor();//获得所选颜色
	}
}
