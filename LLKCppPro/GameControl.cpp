#include "stdafx.h"
#include "GameControl.h"
#include "global.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

int CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 16;

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];
}

bool CGameControl::PushVex(Vertex V)
{
	if (m_pGameMap[V.nRow][V.nCol] != BLANK)
	{
		m_pGameMap[V.nRow][V.nCol] = BLANK;
		return true;
	}
	return false;
}