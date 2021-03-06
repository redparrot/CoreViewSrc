// MultiStartTestDlg.h : 头文件
//

#pragma once


// CMultiStartTestDlg 对话框
class CMultiStartTestDlg : public CDialog
{
// 构造
public:
	CMultiStartTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MULTISTARTTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	int Time;//周期间隔
	int ProcessNums;//进程实例的个数
	CString ExePathName;//可执行程序的名称及路径
	CString CmdLine;//可执行程序的命令行参数

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedCancel2();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk2();
};
