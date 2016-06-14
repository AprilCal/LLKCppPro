// GameDlg_G.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "GameDlg_G.h"
#include "afxdialogex.h"
#include "global.h"


// CGameDlg_G �Ի���

IMPLEMENT_DYNAMIC(CGameDlg_G, CDialogEx)

CGameDlg_G::CGameDlg_G(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG2, pParent)
{

}

CGameDlg_G::~CGameDlg_G()
{
}

void CGameDlg_G::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg_G, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg_G ��Ϣ�������


void CGameDlg_G::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}


BOOL CGameDlg_G::OnInitDialog()
{
	UpdateWindow();
	InitDC();
	InitBackground();
	InitElement();
	UpdateMap();
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CGameDlg_G::InitDC()
{
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcElement.CreateCompatibleDC(&dc);
}

void CGameDlg_G::InitBackground()
{
	//if (!bitmap.Attach(hbitmap)) //��λͼ������û�����������ϵ
	//	MessageBox("ATTACH FAIL!");//���Attach����ʧ�ܵ�����Ϣ����ʾ
	CBitmap bmpMain;
	HBITMAP hbitmap = (HBITMAP)::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMain.Attach(hbitmap);
	m_dcMem.SelectObject(bmpMain);
}

void  CGameDlg_G::UpdateWindow()
{
	gamecontrol.m_graph.InitGraph();
	gamelogic.InitMap(gamecontrol.m_graph);
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

void CGameDlg_G::InitElement()
{
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\Elements-mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.SelectObject(hMask);

	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\Elements.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.SelectObject(hBmp);
}

void CGameDlg_G::UpdateMap()
{
	InitBackground();
	/*gamecontrol.m_graph.InitGraph();
	gamelogic.InitMap(gamecontrol.m_graph);*/
	for (int i = 0;i < CGameControl_G::s_nRows;i++)
	{
		for (int j = 0;j < CGameControl_G::s_nCols;j++)
		{
			//get picture num
			int nElemVal = gamecontrol.GetElement(i, j);
			//||
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal*nElemH, SRCPAINT);
			//&&
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal*nElemH, SRCAND);
		}
	}
}

void CGameDlg_G::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_rtGameRect.top = nTop;
	m_rtGameRect.bottom = nTop + nElemH*RowElementNum;
	m_rtGameRect.left = nLeft;
	m_rtGameRect.right = nLeft + nElemW*ColElementNum;

	int row = (point.y - TruenTop) / nElemH - 1;
	int col = (point.x - TruenLeft) / nElemW - 1;
	int TrueRow = (point.y - TruenTop) / nElemH;
	int TrueCol = (point.x - TruenLeft) / nElemW;

	if (point.y<m_rtGameRect.top || point.y>m_rtGameRect.bottom
		|| point.x <m_rtGameRect.left || point.x >m_rtGameRect.right)
	{
		//do nothing
		//return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else
	{
		if (gamecontrol.GetElement(row,col) != BLANK)
		{
			CClientDC dc(this);
			CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
			dc.SelectObject(&penRect);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(TruenLeft + nElemW*TrueCol, TruenTop + nElemH*TrueRow, TruenLeft + nElemW*TrueCol + 40, TruenTop + nElemH*TrueRow + 40);
		}
		if ((gamecontrol.GetElement(row, col) != BLANK))
		{
			if (m_bFirstPoint.nRow == 12)//һ��12��,0-11�������õ�12
			{
				m_bFirstPoint.nRow = row;
				m_bFirstPoint.nCol = col;
			}
			else
			{
				m_bSecPoint.nRow = row;
				m_bSecPoint.nCol = col;
				if (m_bFirstPoint.nRow == m_bSecPoint.nRow&&
					m_bFirstPoint.nCol == m_bSecPoint.nCol)//������ѡ�еĵ���ͬ����ȡ��ѡ�񣬼��ڶ��ε��һ����ȡ��ѡ��
				{
					//do nothing except repaint dc
					CClientDC dc(this);
					UpdateMap();
					dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
					m_bFirstPoint.nRow = 12;
				}
				else
				{
					Path *path = new Path();
					path->next = NULL;
					
					//if (gamelogic.IsSame(gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint) &&
					//	gamelogic.IsLink(path, gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint))
					//{
					//	CClientDC dc(this);
					//	CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
					//	dc.SelectObject(&penRect);//��pen�ŵ�dc��
					//	dc.SelectStockObject(NULL_BRUSH);
					//	DrawLine(path);
					//	Sleep(100);
					//	gamecontrol.PushVex(m_bFirstPoint);
					//	gamecontrol.PushVex(m_bSecPoint);
					//	count += 2;
					//	UpdateMap();
					//	dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft + 22, RowElementNum*nElemH + nTop + 22, &m_dcMem, 0, 0, SRCCOPY);
					//	m_bFirstPoint.nRow = 12;
					//	FreePath(path);
					//}
					if (gamelogic.IsSame(&gamecontrol.m_graph,m_bFirstPoint,m_bSecPoint))
					{
						CClientDC dc(this);
						gamecontrol.PushVex(gamecontrol.m_graph, m_bFirstPoint);
						gamecontrol.PushVex(gamecontrol.m_graph, m_bSecPoint);
						UpdateMap();
						m_bFirstPoint.nRow = 12;
						dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft + 22, RowElementNum*nElemH + nTop + 22, &m_dcMem, 0, 0, SRCCOPY);
					}
					else//���ѡ��ĵ㲻��ͨ����ͬ����ȡ��ѡ��
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
