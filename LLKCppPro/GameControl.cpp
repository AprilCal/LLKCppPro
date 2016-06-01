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

int** CGameControl::ResetMap()
{
	srand((int)time(NULL));
	//exchange two number randomly
	int nVertexNum = 16*10;
	for (int i = 0;i < nVertexNum;i++)
	{
		//get two coordinates
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		//exchange value of two number
		int nTmp = m_pGameMap[nIndex1 / 16][nIndex1 %16];
		m_pGameMap[nIndex1 / 16][nIndex1 % 16] = m_pGameMap[nIndex2 / 16][nIndex2 % 16];
		m_pGameMap[nIndex2 / 16][nIndex2 % 16] = nTmp;
	}

	//how many
	return m_pGameMap;
}