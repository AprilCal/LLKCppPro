// Help.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "Help.h"
#include "afxdialogex.h"


// CHelp �Ի���

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


// CHelp ��Ϣ�������


BOOL CHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString info1;
	info1 = "����ģʽ��300s���������Ϸʤ��������ʧ��";
	CString info2;
	info2 = "����ģʽ������ʱ��";
	CString info3;
	info3 = "�ؿ�ģʽ��������";
	CString info;
	info += info1;
	info += "\r\n";
	info += info2;
	info += "\r\n";
	info += info3;
	SetDlgItemText(IDC_EDIT_HELP, info);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
