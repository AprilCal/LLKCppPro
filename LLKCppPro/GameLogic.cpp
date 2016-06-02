#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"
#include "global.h"


CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::ReleaseMap(int **&pGameMap)
{
	for (int i = 0;i < CGameControl::s_nRows;i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}

int** CGameLogic::InitMap()
{
	//get 
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	//
	int** pGameMap = new int*[nRows];
	if (NULL == pGameMap)
	{
		//TODO:
		//define CGameException
	}
	else
	{
		for (int i = 0;i < nRows;i++)
		{
			pGameMap[i] = new int[nCols];
			if (NULL == pGameMap)
			{
				//TODO:
				//throw CGameException
			}
			memset(pGameMap[i], NULL, sizeof(int)*nCols);
		}
	}

	if ((nRows*nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		//throw new CGameException
	}
	int nRepeatNum = nRows*nCols / nPicNum;

	int nCount = 0;
	for (int i = 0;i < nPicNum;i++)
	{
		for (int j = 0;j < nRepeatNum;j++)
		{
			pGameMap[nCount / nCols][nCount%nCols]=i;
			nCount++;
		}
	}

	//select two position and change each other
	//set random num seed
	srand((int)time(NULL));
	//exchange two number randomly
	int nVertexNum = nRows*nCols;
	for (int i = 0;i < nVertexNum;i++)
	{
		//get two coordinates
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		//exchange value of two number
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 %nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}

	//define true GameMap
	int** TruepGameMap = new int*[nRows + 2];
	if (NULL == TruepGameMap)
	{
		//TODO:
		//define CGameException
	}
	else
	{
		for (int i = 0;i < nRows + 2;i++)
		{
			TruepGameMap[i] = new int[nCols+2];
			if (NULL == TruepGameMap)
			{
				//TODO:
				//throw CGameException
			}
			memset(TruepGameMap[i], NULL, sizeof(int)*(nCols+2));
		}
	}
	for (int i = 0;i < nRows + 2;i++)
	{
		for (int j = 0;j < nCols + 2;j++)
		{
			TruepGameMap[i][j] = BLANK;
		}
	}
	for (int i = 0;i < nRows;i++)
	{
		for (int j = 0;j < nCols;j++)
		{
			TruepGameMap[i + 1][j + 1] = pGameMap[i][j];
		}
	}
	//how many
	return TruepGameMap;
}



bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	if (v1.nRow != v2.nRow)
	{
		return false;
	}
	int left = v1.nCol < v2.nCol ? v1.nCol : v2.nCol;
	int right = v1.nCol > v2.nCol ? v1.nCol : v2.nCol;
	int nRow = v1.nRow;
	//if (left + 1 == right)//如果相邻
	//{
	//	return true;
	//}
	left++;
	for (;left <= right;left++)//不相邻
	{
		if (left == right) return true;
		if (pGameMap[nRow][left]!=BLANK) break;
	}
	return false;
}

bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	if (v1.nCol != v2.nCol)
	{
		return false;
	}
	int top = v1.nRow < v2.nRow ? v1.nRow : v2.nRow;
	int bottom = v1.nRow > v2.nRow ? v1.nRow : v2.nRow;
	int nCol = v1.nCol;
	/*if (top + 1 == bottom)
	{
		return true;
	}*/
	top++;
	for (;top <= bottom;top++)
	{
		if (top == bottom) return true;
		if (pGameMap[top][nCol] != BLANK) break;
	}
	return false;
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	if (v1.nCol == v2.nCol || v1.nRow == v2.nRow)
	{
		return false;
	}
	if (pGameMap[v1.nRow][v2.nCol] == BLANK)
	{
		if (LinkInRow(pGameMap, v1, { v1.nRow,v2.nCol }) && LinkInCol(pGameMap, v2, { v1.nRow,v2.nCol }))
			return true;
	}
	if(pGameMap[v2.nRow][v1.nCol] == BLANK)
	{
		if (LinkInCol(pGameMap, v1, { v2.nRow,v1.nCol }) && LinkInRow(pGameMap, v2, { v2.nRow,v1.nCol }))
		{
			return true;
		}
	}
	return false;
}

bool CGameLogic::TwoCornerLinkBasedOnX(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int i = 0;i <= 11;i++)
	{
		if (i == v1.nRow || i == v2.nRow) continue;
		if (pGameMap[i][v1.nCol] == BLANK&&pGameMap[i][v2.nCol] == BLANK)
		{
			if (LinkInRow(pGameMap, { i,v1.nCol }, { i,v2.nCol }) &&
				LinkInCol(pGameMap, v1, { i,v1.nCol }) &&
				LinkInCol(pGameMap, v2, { i,v2.nCol }))
			{
				return true;
			}
		}
	}
	return false;
}

bool CGameLogic::TwoCornerLinkBasedOnY(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int i = 0;i <= 17;i++)
	{
		if (i == v1.nCol || i == v2.nCol) continue;
		if (pGameMap[v1.nRow][i] == BLANK&&pGameMap[v2.nRow][i] == BLANK)
		{
			if (LinkInCol(pGameMap, { v1.nRow,i }, { v2.nRow,i }) &&
				LinkInRow(pGameMap, v1, { v1.nRow,i }) &&
				LinkInRow(pGameMap, v2, { v2.nRow,i }))
			{
				return true;
			}
		}
	}
	return false;
}

bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	return LinkInRow(pGameMap, v1, v2)|| 
		   LinkInCol(pGameMap, v1, v2)|| 
		   OneCornerLink(pGameMap, v1, v2)||
		   TwoCornerLinkBasedOnX(pGameMap, v1, v2)||
	       TwoCornerLinkBasedOnY(pGameMap, v1, v2);
}

bool CGameLogic::IsSame(int** pGameMap, Vertex v1, Vertex v2)
{
	return pGameMap[v1.nRow][v1.nCol] == pGameMap[v2.nRow][v2.nCol] ? true : false;
}