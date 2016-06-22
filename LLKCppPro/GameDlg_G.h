#pragma once
#include "GameControl.h"
#include "GameLogic.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "global.h"

// CGameDlg_G 对话框

class CGameDlg_G : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg_G)

public:
	CGameDlg_G(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg_G();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG2 };
#endif

private:
	int GAMEWND_WIDTH = 800;
	int GAMEWND_HEIGHT = 600;
protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void InitBackground();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
	void InitDC();
	void DrawLine(Path *path);
	void FreePath(Path *path);
	void DrawTime();
	void JudgeWin();

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
	int time = 0;
	CFont font;

	CRect m_rtGameRect;

	CGameLogic gamelogic;
	CGameControl gamecontrol;

	bool m_bPlaying = true;
	bool m_bPaused = false;

	Vertex m_bFirstPoint = { 11,0 };
	Vertex m_bSecPoint = { 11,0 };
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonStartgame();
};
