#pragma once
#include "GameControl.h"
#include "GameLogic.h"
#include "afxcmn.h"
#include "afxwin.h"

/*************************************************
Copyright:AprilCal
Create on 2016.05.28 by AprilCal in Whut
Description:no
**************************************************/

// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)
private:
	int GAMEWND_WIDTH = 800;
	int GAMEWND_HEIGHT = 600;

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	void InitBackground();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
	void InitDC();
	void DrawLine(Path *path);
	void FreePath(Path *path);
	void DrawTime();
	void JudgeWin();
	void InitRank();

	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;

	int nLeft = 20;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	int RowElementNum = 10;
	int ColElementNum = 16;
	int TruenLeft = -20;
	int TruenTop = 10;
	int count = 0;
	//int time = 0;
	CFont font;

	CRect m_rtGameRect;

	CGameLogic gamelogic;
	CGameControl gamecontrol;

	bool m_bPlaying = false;
	bool m_bPaused = false;

	Score rank[10];

	Vertex m_bFirstPoint = {11,0};
	Vertex m_bSecPoint = {11,0};
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CProgressCtrl m_ctrlProgress;

	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonPrompt();
	afx_msg void OnBnClickedButtonReset();
};
