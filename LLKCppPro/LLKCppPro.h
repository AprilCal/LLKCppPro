
// LLKCppPro.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLLKCppProApp: 
// �йش����ʵ�֣������ LLKCppPro.cpp
//

class CLLKCppProApp : public CWinApp
{
public:
	CLLKCppProApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLLKCppProApp theApp;