// Rank.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKCppPro.h"
#include "Rank.h"
#include "afxdialogex.h"
#include "global.h"


// CRank 对话框

IMPLEMENT_DYNAMIC(CRank, CDialogEx)

CRank::CRank(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
{
}

CRank::~CRank()
{
}

void CRank::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RANK, m_RankEdit);
}


BEGIN_MESSAGE_MAP(CRank, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRank::OnBnClickedOk)
END_MESSAGE_MAP()


// CRank 消息处理程序

void CRank::DrawRank()
{
	CString rank;
	rank ="\t";
	rank += "基本模式排名";
	rank += "\r\n";
	

	//read file head
	Score score;
	FILE *_in;
	errno_t _err = fopen_s(&_in, "score\\score.txt", "rb");
	
	for (int i = 0;i < 10;i++)
	{
		fread(&score, sizeof(score), 1, _in);
		CString temp;
		temp.Format(_T("%3d"), score.time);
		
		CString num;
		num.Format(_T("%3d"), i+1);

		CString word;
		word = "第";
		word += "\t";
		word += num;
		word += "\t";
		word += "名";
		rank += word;
		rank += "\t";
		rank += temp;
		rank += "s";
		rank += "\r\n";
	}
	SetDlgItemText(IDC_EDIT_RANK, rank);
	fclose(_in);
}


BOOL CRank::OnInitDialog()
{
	DrawRank();
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRank::OnBnClickedOk()
{
	Score rank[10];
	for (int i = 0;i < 10;i++)
	{
		rank[i].time=300;
	}

	FILE *out;
	errno_t err3 = fopen_s(&out, "score\\score.txt", "wb");
	for (int j = 0;j < 10;j++)
	{
		fwrite(&rank[j], sizeof(Score), 1, out);
	}
	fclose(out);
	DrawRank();
}
