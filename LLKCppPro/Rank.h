#pragma once
#include "afxwin.h"
#include "string"


// CRank 对话框

class CRank : public CDialogEx
{
	DECLARE_DYNAMIC(CRank)

public:
	CRank(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRank();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void DrawRank();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_RankEdit;
protected:
public:
	virtual BOOL OnInitDialog();
//	CString m_Rank;
	afx_msg void OnBnClickedOk();
};
