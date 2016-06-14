#pragma once
#include "GameLogic_G.h"
#include "GameControl_G.h"
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	int GAMEWND_WIDTH = 800;
	int GAMEWND_HEIGHT = 600;

	int nLeft = 20;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	int RowElementNum = 10;
	int ColElementNum = 16;
	int TruenLeft = -20;
	int TruenTop = 10;
	int count = 0;

	CRect m_rtGameRect;

	CDC m_dcMem;
	CDC m_dcMask;
	CDC m_dcElement;

	CGameLogic_G gamelogic;
	CGameControl_G gamecontrol;

	Vertex m_bFirstPoint = { 11,0 };
	Vertex m_bSecPoint = { 11,0 };

	void InitDC();
	void InitBackground();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
