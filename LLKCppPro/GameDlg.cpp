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
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
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
	count = 0;
	gamecontrol.m_pGameMap = gamelogic.InitMap();
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
	HBITMAP hbitmap =(HBITMAP)::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMain.Attach(hbitmap);
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

	HANDLE hMask=::LoadImageW(NULL, _T("theme\\picture\\Elements-mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.SelectObject(hMask);

	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\Elements.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.SelectObject(hBmp);
}

void CGameDlg::UpdateMap()
{
	InitBackground();
	for (int i = 0;i < CGameControl::s_nRows;i++)
	{
		for (int j = 0;j < CGameControl::s_nCols;j++)
		{
			//get picture num
			int nElemVal = gamecontrol.GetElement(i+1, j+1);
			//||
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH,SRCPAINT);
			//&&
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
		}
	}
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rtGameRect.top = nTop;
	m_rtGameRect.bottom = nTop + nElemH*RowElementNum;
	m_rtGameRect.left = nLeft;
	m_rtGameRect.right = nLeft + nElemW*ColElementNum;

	int row = (point.y - TruenTop) / nElemH;
	int col = (point.x - TruenLeft) / nElemW;

	if (point.y<m_rtGameRect.top || point.y>m_rtGameRect.bottom
		|| point.x <m_rtGameRect.left || point.x >m_rtGameRect.right)
	{
		//return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else
	{
		if (gamecontrol.m_pGameMap[row][col] != BLANK)
		{
			CClientDC dc(this);
			CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
			dc.SelectObject(&penRect);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(TruenLeft + nElemW*col, TruenTop + nElemH*row, TruenLeft + nElemW*col + 40, TruenTop + nElemH*row + 40);
		}
		if ((gamecontrol.m_pGameMap[row][col] != BLANK))
		{
			if (m_bFirstPoint.nRow == 12)//一共12行,0-11，不会用到12
			{
				m_bFirstPoint.nRow = row;
				m_bFirstPoint.nCol = col;
			}
			else
			{
				m_bSecPoint.nRow = row;
				m_bSecPoint.nCol = col;
				if (m_bFirstPoint.nRow == m_bSecPoint.nRow&&
				m_bFirstPoint.nCol == m_bSecPoint.nCol)//若两次选中的点相同，则取消选择，即第二次点击一个点取消选择
				{
					//do nothing except repaint dc
					CClientDC dc(this);
					UpdateMap();
					dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
					m_bFirstPoint.nRow = 12;
				}
				else
				{
					Path *path=new Path();
					path->next = NULL;
					if (gamelogic.IsSame(gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint) &&
					gamelogic.IsLink(path,gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint))
					{
						CClientDC dc(this);
						CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
						dc.SelectObject(&penRect);//将pen放到dc上
						dc.SelectStockObject(NULL_BRUSH);
						DrawLine(path);
						//for (int i = 0;i < 60000000;i++);
						Sleep(100);
						gamecontrol.PushVex(m_bFirstPoint);
						gamecontrol.PushVex(m_bSecPoint);
						count += 2;
						UpdateMap();
						dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft+22, RowElementNum*nElemH + nTop+22, &m_dcMem, 0, 0, SRCCOPY);
						m_bFirstPoint.nRow = 12;
						FreePath(path);
					}
					else//如果选择的点不连通或不相同，则取消选择
					{
						CClientDC dc(this);
						UpdateMap();
						dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
						m_bFirstPoint.nRow = 12;
					}//else
				}//else
			}//else
		}
	}
	if (count >= RowElementNum*ColElementNum)
	{
		AfxMessageBox(_T("You Win"));
	}
}


void CGameDlg::OnBnClickedButton1()
{

}


void CGameDlg::OnBnClickedButton4()
{
	gamecontrol.ResetMap();
	//gamecontrol.m_pGameMap = gamelogic.InitMap();
	CClientDC dc(this); 
	UpdateMap();
	dc.BitBlt( 0, 0, ColElementNum*nElemW+nLeft, RowElementNum*nElemH+nTop, &m_dcMem, 0, 0, SRCCOPY);
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

void CGameDlg::DrawLine(Path *path)
{
	CClientDC dc(this);
	CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
	dc.SelectObject(&penRect);//将pen放到dc上
	dc.SelectStockObject(NULL_BRUSH);
	while (path != NULL && path->next != NULL)
	{
		dc.MoveTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
		path = path->next;
		dc.LineTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
		dc.MoveTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
	}
}


void CGameDlg::OnBnClickedButton3()
{
	Path *path = new Path();
	for (int i = 1;i < RowElementNum + 1;i++)
	{
		for (int j = 1;j < ColElementNum + 1;j++)
		{
			if (gamecontrol.m_pGameMap[i][j] != BLANK)
			{
				for (int m = 1;m < RowElementNum;m++)
				{
					for (int n = 1;n < ColElementNum;n++)
					{
						if (i == m&&j == n)
						{
							continue;
						}
						else
						{
							if (gamelogic.IsSame(gamecontrol.m_pGameMap, { i,j }, { m,n }) &&
								gamelogic.IsLink(path, gamecontrol.m_pGameMap, { i,j }, { m,n }))
							{
								DrawLine(path);
								goto loop;
							}
						}
					}
				}
			}
		}
	}
	AfxMessageBox(_T("无子可消"));
	loop:int i;
}


void CGameDlg::FreePath(Path* path)
{
	Path *p = path;
	while (p)
	{
		Path* next = p->next;
		free(p);
		p = next;
	}
}