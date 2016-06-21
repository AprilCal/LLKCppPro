#include "stdafx.h"
#include "GameControl.h"
#include "global.h"
#include "GameLogic.h"


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
	int nVertexNum = 17*11;
	for (int i = 0;i < nVertexNum;i++)
	{
		//get two coordinates
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		if (nIndex1/17 == 0 || nIndex1%17 == 0 || nIndex2/17 == 0 || nIndex2%17 == 0) continue;
		//exchange value of two number
		int nTmp = m_pGameMap[nIndex1 / 17][nIndex1 %17];
		m_pGameMap[nIndex1 / 17][nIndex1 % 17] = m_pGameMap[nIndex2 / 17][nIndex2 % 17];
		m_pGameMap[nIndex2 / 17][nIndex2 % 17] = nTmp;
	}

	//how many
	return m_pGameMap;
}

BOOL CGameControl::IsWin(int nTime)
{
	CGameLogic logic;

	//ÅÐ¶ÏÓÎÏ·Ê±¼ä
	if (nTime <= 0)
	{
		return GAME_LOSE;
	}
	if (logic.IsBlank(m_pGameMap) == true)
	{
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}
