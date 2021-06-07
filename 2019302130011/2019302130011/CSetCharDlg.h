#pragma once


// CSetCharDlg 对话框

class CSetCharDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetCharDlg)

public:
	CSetCharDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetCharDlg();

	CFont m_fnt;//保存字体
	COLORREF m_clrText;//保存颜色

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strString;
	int m_nX;
	int m_nY;
	afx_msg void OnClickedButtonFont();
};
