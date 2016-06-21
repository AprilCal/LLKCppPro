// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameLogic.h"
#include "GameControl.h"
#include "global.h"
#include <sstream>
using namespace std;

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
	//  DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	//  DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	//  DDX_Control(pDX, IDC_EDIT1, m_Label);
	//  DDX_Control(pDX, IDCANCEL, m_Label);
	//  DDX_Control(pDX, IDC_EDIT2, m_Time);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGameDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CGameDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_PROMPT, &CGameDlg::OnBnClickedButtonPrompt)
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
	InitBackground();
	UpdateWindow();

	//设置进度条的范围
	time = 10;
	UpdateData(false);
	m_ctrlProgress.SetRange(0, 10);

	//设置进度条的每一步的增量
	m_ctrlProgress.SetStep(1);

	//设置进度条的当前位置
	m_ctrlProgress.SetPos(10);
	
	CDialogEx::OnInitDialog();
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
		//do nothing
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
	if (count >= RowElementNum*ColElementNum && time>=0)
	{
		AfxMessageBox(_T("You Win"));
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1); //IDC_BUTTON2这个按钮 
		if (pBtn != NULL)
		{
			pBtn->EnableWindow(TRUE); // True or False 
		}
	}
}


void CGameDlg::OnBnClickedButton1()
{
	CClientDC dc(this);
	count = 0;
	gamecontrol.m_pGameMap = gamelogic.InitMap();
	//InitBackground();
	UpdateWindow();
	InitElement();
	UpdateMap();
	dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1); //IDC_BUTTON2这个按钮 
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(FALSE); // True or False 
	}

	CString tmpStr;
	GetDlgItemText(IDC_PROGRESS1, tmpStr);
	count = _wtoi(tmpStr);//将宽字符转换成整型
	//SetTimer(1, 1000, NULL);//此为一个定时器
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
	UpdateData(FALSE);
}


void CGameDlg::OnBnClickedButton4()
{
	gamecontrol.ResetMap();
	CClientDC dc(this); 
	UpdateMap();
	dc.BitBlt( 0, 0, ColElementNum*nElemW+nLeft, RowElementNum*nElemH+nTop, &m_dcMem, 0, 0, SRCCOPY);
	if (count >= 160)
	{
		AfxMessageBox(_T("请重新开始"));
	}
}

void CGameDlg::OnBnClickedOk()
{
	//CDialog::OnCancel();
}

void CGameDlg::OnBnClickedCancel()
{
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

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	JudgeWin();
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPaused)
	{
		if (time > 0)
		{
			//time--;
		}
		m_ctrlProgress.SetPos(time);
		DrawTime();
		/*if (time == 0)
		{
			AfxMessageBox(_T("时间到!!!"));
		}*/
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawTime()
{
	//创建CPaintDC对象
	CClientDC dc(this);

	//创建字体
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));

	//将字体选进DC
	CFont *oldFont;
	oldFont = dc.SelectObject(&font);

	//设置字体颜色和背景
	dc.SetTextColor(RGB(22, 22, 2));
	dc.SetBkColor(RGB(228, 221, 222));

	//获取进度条组件位置
	CRect rect;
	GetDlgItem(IDC_PROGRESS1)->GetWindowRect(&rect);
	ScreenToClient(rect);

	//设置输出内容为进度
	CString time;
	time.Format(_T("%3d"), m_ctrlProgress.GetPos());

	//设置输出位置为进度条旁
	dc.TextOut(rect.left + rect.Width(), rect.top, time);

	//用空格控制保证每次输出文本长度一致
	if (m_ctrlProgress.GetPos() >= 10 && m_ctrlProgress.GetPos() < 100)
	{
		CString time;
		time.Format(_T("%-3d "), m_ctrlProgress.GetPos());
		dc.TextOut(rect.left + rect.Width(), rect.top, time);
	}
	if (m_ctrlProgress.GetPos() <10)
	{
		CString time;
		time.Format(_T("%-3d "), m_ctrlProgress.GetPos());
		dc.TextOut(rect.left + rect.Width(), rect.top, time);
	}
}


void CGameDlg::JudgeWin()
{
	//游戏胜负判断
	BOOL bGameStatus = gamecontrol.IsWin(m_ctrlProgress.GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//游戏标识改为false
		m_bPlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIMER_ID);
		//AfxMessageBox(_T("KillTimer"));
		//提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("恭喜您获胜！"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到！"), strTitle);
		}
		//还原开始游戏按钮，使开始按钮可以点击
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}

void CGameDlg::OnBnClickedButtonPause()
{
	
	//CClientDC dc(this);
	//dc.BitBlt(30, 30, 700, 700, &m_dcPause, 30, 30, SRCCOPY);
	if (m_bPlaying == false)
	{
		return;
	}
	if (m_bPaused == false)
	{
		//绘制暂停图
		CClientDC dc(this);
		InitBackground();
		dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
		this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BUTTON_Pause)->SetWindowTextW(_T("继续游戏"));
	}
	else
	{
		CClientDC dc(this);
		UpdateMap();
		dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
		this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BUTTON_Pause)->SetWindowTextW(_T("暂停游戏"));
	}
	m_bPaused = !m_bPaused;
}


void CGameDlg::OnBnClickedButtonPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
}
