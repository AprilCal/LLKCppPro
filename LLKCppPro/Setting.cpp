// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
END_MESSAGE_MAP()


// CSetting 消息处理程序


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString bgm;
	bgm = "背景音乐";
	CString music;
	music = "音效";
	SetDlgItemText(IDC_EDIT_BGM, bgm);
	SetDlgItemText(IDC_EDIT_SOUND_EFFECT, music);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
