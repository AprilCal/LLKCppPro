// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

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


// CSetting ��Ϣ�������


BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString bgm;
	bgm = "��������";
	CString music;
	music = "��Ч";
	SetDlgItemText(IDC_EDIT_BGM, bgm);
	SetDlgItemText(IDC_EDIT_SOUND_EFFECT, music);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
