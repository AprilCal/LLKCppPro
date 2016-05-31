// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameLogic.h"
#include "GameControl.h"
#include "global.h"

/*************************************************
Copyright:AprilCal
Create on 2016.05.28 by AprilCal in Whut
Description:no
**************************************************/

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{

	EnableAutomation();

}

CGameDlg::~CGameDlg()
{
	
}

void CGameDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGameDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IGameDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {58450D3F-E759-4BE5-9E9B-C60030158F5F}
static const IID IID_IGameDlg =
{ 0x58450D3F, 0xE759, 0x4BE5, { 0x9E, 0x9B, 0xC6, 0x0, 0x30, 0x15, 0x8F, 0x5F } };

BEGIN_INTERFACE_MAP(CGameDlg, CDialogEx)
	INTERFACE_PART(CGameDlg, IID_IGameDlg, Dispatch)
END_INTERFACE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	InitDC();
	//InitBackground();
	UpdateWindow();
	InitElement();
	UpdateMap();
	
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::InitBackground()
{

	//if (!bitmap.Attach(hbitmap)) //将位图对象和用户定义类相联系
	//	MessageBox("ATTACH FAIL!");//如果Attach调用失败弹出信息框提示
	CBitmap bmpMain;
	//bmpMain.LoadBitmapW(IDB_BITMAP1);
	HBITMAP hbitmap =(HBITMAP)::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMain.Attach(hbitmap);

	 CClientDC dc(this);
	//m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmpMain);
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitDC()
{
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcElement.CreateCompatibleDC(&dc);
}

void  CGameDlg::UpdateWindow()
{
	//set window size
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	//set size of title bar & outer boder
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
	CenterWindow();
}

void CGameDlg::InitElement()
{
	CClientDC dc(this);
	//m_dcMask.CreateCompatibleDC(&dc);
	//m_dcElement.CreateCompatibleDC(&dc);

	HANDLE hMask=::LoadImageW(NULL, _T("theme\\picture\\Elements-mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.SelectObject(hMask);
	//m_dcMem.BitBlt(400, 290, 40, 400, &m_dcMask, 0, 0, SRCPAINT);

	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\Elements.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.SelectObject(hBmp);
	//m_dcMem.BitBlt(400, 290, 40, 400, &m_dcElement, 0, 0, SRCAND);
}

void CGameDlg::UpdateMap()
{
	InitBackground();
	gamecontrol.m_pGameMap = gamelogic.InitMap();
	for (int i = 0;i < CGameControl::s_nRows;i++)
	{
		for (int j = 0;j < CGameControl::s_nCols;j++)
		{
			//get picture num
			int nElemVal = gamecontrol.GetElement(i, j);
			//m_dcMem.SelectObject();
			//||
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH,SRCPAINT);
			//&&
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
		}
	}
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_rtGameRect.top = 50;
	m_rtGameRect.bottom = 600;
	m_rtGameRect.left = 20;
	m_rtGameRect.right = 800;

	if (point.y<m_rtGameRect.top || point.y>m_rtGameRect.bottom
		|| point.x <m_rtGameRect.left || point.x >m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else
	{
		int row = (point.y - nTop) / nElemH;
		int col = (point.x - nLeft) / nElemH;
		CClientDC dc(this);
		CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
		dc.SelectObject(&penRect);//将pen放到dc上
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(nLeft+nElemW*col, nTop+nElemH*row, nLeft + nElemW*col +40, nTop + nElemH*row + 40);//画一个矩形

		UpdateMap();
		//CDialogEx::OnLButtonUp(nFlags, point);
	}
	/*if (m_bFirstPoint.nCol!=0)
	{
		m_bFirstPoint.nRow = (point.y - nTop) / nElemH;
		m_bFirstPoint.nCol = (point.x - nLeft) / nElemH;
	}
	else
	{
		bool bSuc = false;
		if (bSuc == true)
		{
			UpdateMap();
		}
	}*/
}


void CGameDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
	dc.SelectObject(&penRect);//将pen放到dc上
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(100, 100, 200, 200);//画一个矩形
}


void CGameDlg::OnBnClickedButton4()
{
	CClientDC dc(this); 
	UpdateMap();
	dc.BitBlt( 0, 0, RowElementNum*nElemW+nLeft, ColElementNum*nElemH+nTop, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::OnBnClickedOk()
{
	//CDialog::OnCancel();
}

void CGameDlg::OnBnClickedCancel()
{
	//CDialog::OnCancel();
	CDialogEx::OnCancel();
}
