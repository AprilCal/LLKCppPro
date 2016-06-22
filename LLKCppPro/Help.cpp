// Help.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "Help.h"
#include "afxdialogex.h"


// CHelp 对话框

IMPLEMENT_DYNAMIC(CHelp, CDialogEx)

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelp, CDialogEx)
END_MESSAGE_MAP()


// CHelp 消息处理程序


BOOL CHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString info1;
	info1 = "基本模式：300s内完成则游戏胜利，否则失败";
	CString info2;
	info2 = "休闲模式：不限时间";
	CString info3;
	info3 = "关卡模式：待开发";
	CString info;
	info += info1;
	info += "\r\n";
	info += info2;
	info += "\r\n";
	info += info3;
	SetDlgItemText(IDC_EDIT_HELP, info);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
