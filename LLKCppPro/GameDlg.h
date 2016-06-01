#pragma once
#include "GameControl.h"
#include "GameLogic.h"

/*************************************************
Copyright:AprilCal
Create on 2016.05.28 by AprilCal in Whut
Description:no
**************************************************/

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)
private:
	int GAMEWND_WIDTH = 800;
	int GAMEWND_HEIGHT = 600;

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	void InitBackground();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
	void InitDC();
	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;

	int nLeft = 20;
	int nTop = 50;
	int nElemW = 40;
	int nElemH = 40;
	int RowElementNum = 16;
	int ColElementNum = 10;

	CRect m_rtGameRect;

	CGameLogic gamelogic;
	CGameControl gamecontrol;

	Vertex m_bFirstPoint = {11,0};
	Vertex m_bSecPoint = {11,0};
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
