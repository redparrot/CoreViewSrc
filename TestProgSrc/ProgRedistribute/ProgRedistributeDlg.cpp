// ProgRedistributeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProgRedistribute.h"
#include "ProgRedistributeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CProgRedistributeDlg 对话框




CProgRedistributeDlg::CProgRedistributeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgRedistributeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgRedistributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CProgRedistributeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CProgRedistributeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CProgRedistributeDlg 消息处理程序

BOOL CProgRedistributeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProgRedistributeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProgRedistributeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CProgRedistributeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProgRedistributeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	CStdioFile f;
	CString s, DllName;
	int pos1 = 0, pos2 = 0;
	char buf[1024];
	buf[0] = 0;
	CStringArray FileList, OutList;
	int FileCnt = 0;
	BOOL b = FALSE;
	_finddata32_t fileinfo;
	CString FileName;
	CFileDialog FileDlg(TRUE, "txt", "*.txt", OFN_HIDEREADONLY, "TXT文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||");

	FileDlg.m_ofn.lpstrInitialDir = "C:\\";

	int ret = FileDlg.DoModal();
	if(ret == IDOK)
	{
		FileName = FileDlg.GetFileName();
		b = f.Open(FileName, CFile::modeReadWrite | CFile::typeText);

		while (f.ReadString(buf, 1024))
		{
			s = buf;

			//找DLL标记
			pos2 = s.Find(".dll");
			if (pos2 != -1)
			{
				//中文IDE时
				pos1 = s.Find("已加载“");
				if (pos1 >= 0)
				{
					DllName = s.Mid(pos1 + 8, pos2 - pos1 - 4);
					FileList.Add(DllName);
				}

				//英文IDE时
				pos1 = s.Find("Loaded '");
				if (pos1 >= 0)
				{
					DllName = s.Mid(pos1 + 8, pos2 - pos1 - 4);
					FileList.Add(DllName);
				}
			}

			//找OCX标记
			pos2 = s.Find(".ocx");
			if (pos2 != -1)
			{
				//中文IDE时
				pos1 = s.Find("已加载“");
				if (pos1 >= 0)
				{
					DllName = s.Mid(pos1 + 8, pos2 - pos1 - 4);
					FileList.Add(DllName);
				}

				//英文IDE时
				pos1 = s.Find("Loaded '");
				if (pos1 >= 0)
				{
					DllName = s.Mid(pos1 + 8, pos2 - pos1 - 4);
					FileList.Add(DllName);
				}
			}
		}

		f.Close();

		//判定文件是否存在
		FileCnt = (int)FileList.GetCount();
		s.Format("文件对应的程序需要 %d 个DLL/OCX", FileCnt);
		m_List.AddString(s);
		for (int i = 0; i < FileCnt; i++)
		{
			DllName = FileList.GetAt(i);
			b = IsFileExist(DllName.GetBuffer(), fileinfo);
			DllName.ReleaseBuffer();
			if (!b)
			{
				OutList.Add(DllName);
			}
		}

		//将不存在的文件输出到列表控件中
		FileCnt = (int)OutList.GetCount();
		if (FileCnt > 0)
		{
			s.Format("本机缺少的DLL/OCX个数为%d，列表如下:", FileCnt);
			m_List.AddString(s);
			for (int i = 0; i < FileCnt; i++)
			{
				DllName = OutList.GetAt(i);
				m_List.AddString(DllName);
			}
		}
		else
		{
			s.Format("文本对应程序所需DLL齐备", FileCnt);
			m_List.AddString(s);
		}
	}
}

BOOL CProgRedistributeDlg::IsFileExist(char* ExistingFileName, _finddata32_t &fileinfo)
{
	ASSERT(strlen(ExistingFileName) != 0);

	if (strlen(ExistingFileName) == 0)
	{
		return -1;//参数错误
	}

	intptr_t handle = 0;
	intptr_t ret = 0;
	BOOL Ret = FALSE;
	memset(&fileinfo, 0, sizeof(_finddata32_t));

	handle = _findfirst32(ExistingFileName, &fileinfo);
	if (handle == -1)
	{
		Ret = FALSE;
	}
	else
	{
		Ret = TRUE;
	}

	ret = _findclose(handle);

	return Ret;
}


