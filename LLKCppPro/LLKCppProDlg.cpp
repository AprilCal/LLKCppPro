

// LLKCppProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "LLKCppProDlg.h"
#include "afxdialogex.h"
#include "GameDlg.h"
#include "GameDlg_G.h"
#include "Rank.h"
#include "Help.h"
#include "Setting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*************************************************
Copyright:AprilCal
Create on 2016.05.28 by AprilCal in Whut
Description:no
**************************************************/

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKCppProDlg 对话框



CLLKCppProDlg::CLLKCppProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LLKCPPPRO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKCppProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKCppProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLLKCppProDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLLKCppProDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &CLLKCppProDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLLKCppProDlg::OnBnClickedButtonRank)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKCppProDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLLKCppProDlg::OnBnClickedButtonSetting)
END_MESSAGE_MAP()


// CLLKCppProDlg 消息处理程序

BOOL CLLKCppProDlg::OnInitDialog()
{
	InitBackground();
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKCppProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKCppProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CPaintDC dc(this);
		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKCppProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKCppProDlg::InitBackground()
{
	MoveWindow(0, 0, 800, 600);
	CenterWindow();

	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_BITMAP1);

	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmpMain);
}



void CLLKCppProDlg::OnBnClickedOk()
{
	ShowWindow(SW_HIDE);
	CGameDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CLLKCppProDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CLLKCppProDlg::OnBnClickedButton5()
{
	ShowWindow(SW_HIDE);
	CGameDlg_G dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CLLKCppProDlg::OnBnClickedButtonRank()
{
	CRank rank;
	rank.DoModal();
	ShowWindow(SW_SHOW);
}


void CLLKCppProDlg::OnBnClickedButtonHelp()
{
	CHelp help;
	help.DoModal();
	ShowWindow(SW_SHOW);
}


void CLLKCppProDlg::OnBnClickedButtonSetting()
{
	CSetting setting;
	setting.DoModal();
	ShowWindow(SW_SHOW);
}
