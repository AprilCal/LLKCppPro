#pragma once
#include "afxwin.h"
#include "string"


// CRank �Ի���

class CRank : public CDialogEx
{
	DECLARE_DYNAMIC(CRank)

public:
	CRank(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRank();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
