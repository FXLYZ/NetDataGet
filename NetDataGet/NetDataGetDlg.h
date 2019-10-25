
// NetDataGetDlg.h: 头文件
//

#pragma once


// CNetDataGetDlg 对话框
class CNetDataGetDlg : public CDialogEx
{
// 构造
public:
	CNetDataGetDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETDATAGET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit DataContent;
	CListBox NetWorkCardBox;
	CEdit NetWorkCardInfo;
	CButton StartCatch;
	CButton StopCatch;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
