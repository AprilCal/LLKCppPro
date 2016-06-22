// GameDlg.cpp : ʵ���ļ�
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

// CGameDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	//ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGameDlg::OnBnClickedCancel)
	//ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CGameDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_PROMPT, &CGameDlg::OnBnClickedButtonPrompt)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IGameDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {58450D3F-E759-4BE5-9E9B-C60030158F5F}
static const IID IID_IGameDlg =
{ 0x58450D3F, 0xE759, 0x4BE5, { 0x9E, 0x9B, 0xC6, 0x0, 0x30, 0x15, 0x8F, 0x5F } };

BEGIN_INTERFACE_MAP(CGameDlg, CDialogEx)
	INTERFACE_PART(CGameDlg, IID_IGameDlg, Dispatch)
END_INTERFACE_MAP()


// CGameDlg ��Ϣ�������


BOOL CGameDlg::OnInitDialog()
{
	InitDC();
	InitBackground();
	UpdateWindow();

	//���ý������ķ�Χ
	UpdateData(false);
	m_ctrlProgress.SetRange(0, 300);

	//���ý�������ÿһ��������
	m_ctrlProgress.SetStep(-1);

	//���ý������ĵ�ǰλ��
	m_ctrlProgress.SetPos(300);
	
	CDialogEx::OnInitDialog();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CGameDlg::InitBackground()
{
	//if (!bitmap.Attach(hbitmap)) //��λͼ������û�����������ϵ
	//	MessageBox("ATTACH FAIL!");//���Attach����ʧ�ܵ�����Ϣ����ʾ
	CBitmap bmpMain;
	HBITMAP hbitmap =(HBITMAP)::LoadImage(NULL, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpMain.Attach(hbitmap);
	m_dcMem.SelectObject(bmpMain);
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal*nElemH,SRCPAINT);
			//&&
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcElement, 0, nElemVal*nElemH, SRCAND);
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
		if (!m_bPaused&&m_bPlaying && gamecontrol.m_pGameMap[row][col] != BLANK)
		{
			CClientDC dc(this);
			CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
			dc.SelectObject(&penRect);
			dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(TruenLeft + nElemW*col, TruenTop + nElemH*row, TruenLeft + nElemW*col + 40, TruenTop + nElemH*row + 40);
		}
		if (!m_bPaused&&m_bPlaying && gamecontrol.m_pGameMap[row][col] != BLANK)
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
					Path *path=new Path();
					path->next = NULL;
					if (gamelogic.IsSame(gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint) &&
					gamelogic.IsLink(path,gamecontrol.m_pGameMap, m_bFirstPoint, m_bSecPoint))
					{
						CClientDC dc(this);
						CPen penRect(PS_SOLID, 2, RGB(0, 255, 0));
						dc.SelectObject(&penRect);//��pen�ŵ�dc��
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
	if (count >= RowElementNum*ColElementNum && time>=0)
	{
		AfxMessageBox(_T("You Win"));
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1); //IDC_BUTTON2�����ť 
		if (pBtn != NULL)
		{
			pBtn->EnableWindow(TRUE); // True or False 
		}
	}
}


void CGameDlg::OnBnClickedButton1()
{
	m_bPlaying = true;
	m_ctrlProgress.SetPos(300);
	CClientDC dc(this);
	count = 0;
	gamecontrol.m_pGameMap = gamelogic.InitMap();
	UpdateWindow();
	InitElement();
	UpdateMap();
	dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1); //IDC_BUTTON2�����ť 
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(FALSE); // True or False 
	}

	CString tmpStr;
	GetDlgItemText(IDC_PROGRESS1, tmpStr);
	count = _wtoi(tmpStr);//�����ַ�ת��������
	//SetTimer(1, 1000, NULL);//��Ϊһ����ʱ��
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
	UpdateData(FALSE);
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
	dc.SelectObject(&penRect);//��pen�ŵ�dc��
	dc.SelectStockObject(NULL_BRUSH);
	while (path != NULL && path->next != NULL)
	{
		dc.MoveTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
		path = path->next;
		dc.LineTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
		dc.MoveTo(path->v.nCol * 40 + TruenLeft + nElemW/2, path->v.nRow * 40 + TruenTop + nElemH/2);
	}
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
		m_ctrlProgress.StepIt();
		DrawTime();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawTime()
{
	//����CPaintDC����
	CClientDC dc(this);

	//��������
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));

	//������ѡ��DC
	CFont *oldFont;
	oldFont = dc.SelectObject(&font);

	//����������ɫ�ͱ���
	dc.SetTextColor(RGB(22, 22, 2));
	dc.SetBkColor(RGB(228, 221, 222));

	//��ȡ���������λ��
	CRect rect;
	GetDlgItem(IDC_PROGRESS1)->GetWindowRect(&rect);
	ScreenToClient(rect);

	//�����������Ϊ����
	CString time;
	time.Format(_T("%3d"), m_ctrlProgress.GetPos());

	//�ÿո���Ʊ�֤ÿ������ı�����һ��
	if (m_ctrlProgress.GetPos() >= 10 && m_ctrlProgress.GetPos() < 300)
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
	//��Ϸʤ���ж�
	BOOL bGameStatus = gamecontrol.IsWin(m_ctrlProgress.GetPos());
	//�ж��Ƿ������Ϸ
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//��Ϸ��ʶ��Ϊfalse
		m_bPlaying = false;
		//�رն�ʱ��
		KillTimer(PLAY_TIMER_ID);
		//AfxMessageBox(_T("KillTimer"));
		//��ʾ��ʤ
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			for (int i = 0;i < 10;i++)
			{
				if ((300 - m_ctrlProgress.GetPos()) < rank[i].time)
				{
					rank[i].time = (300 - m_ctrlProgress.GetPos());
					//FILE *in2;
					FILE *out;
					errno_t err3 = fopen_s(&out, "score\\score.txt", "wb");
					//errno_t err2 = fopen_s(&in2, "score\\score.txt", "rb");
					for (int j = 0;j < 10;j++)
					{
						fwrite(&rank[j], sizeof(Score), 1, out);
					}
					//fclose(in2);
					fclose(out);
					break;
				}
			}
			MessageBox(_T("��ϲ����ʤ��"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("���ź���ʱ�䵽��"), strTitle);
		}
		//��ԭ��ʼ��Ϸ��ť��ʹ��ʼ��ť���Ե��
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}

void CGameDlg::OnBnClickedButtonPause()
{
	if (m_bPlaying == false)
	{
		return;
	}
	if (m_bPaused == false)
	{
		//������ͣͼ
		CClientDC dc(this);
		InitBackground();
		dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
		this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BUTTON_Pause)->SetWindowTextW(_T("������Ϸ"));
	}
	else
	{
		CClientDC dc(this);
		UpdateMap();
		dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
		this->GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BUTTON_Pause)->SetWindowTextW(_T("��ͣ��Ϸ"));
	}
	m_bPaused = !m_bPaused;
}


void CGameDlg::OnBnClickedButtonPrompt()
{
	if (m_bPlaying && !m_bPaused)
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
		AfxMessageBox(_T("���ӿ���"));
	loop:int i;
	}
}


void CGameDlg::OnBnClickedButtonReset()
{
	if (m_bPlaying && !m_bPaused)
	{
		gamecontrol.ResetMap();
		CClientDC dc(this);
		UpdateMap();
		dc.BitBlt(0, 0, ColElementNum*nElemW + nLeft, RowElementNum*nElemH + nTop, &m_dcMem, 0, 0, SRCCOPY);
		if (count >= 160)
		{
			AfxMessageBox(_T("�����¿�ʼ"));
		}
	}
}
