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
		int nTmp = pGameMap[nIndex1 / nCols][nIndex2 %nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
	}

	//how many
	return pGameMap;
}

void CGameLogic::ReleaseMap(int **&pGameMap)
{
	for (int i = 0;i < CGameControl::s_nRows;i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}

bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	int left = v1.nCol < v2.nCol ? v1.nCol : v2.nCol;
	int right = v1.nCol > v2.nCol ? v1.nCol : v2.nCol;
	int nRow = v1.nRow;

	left++;
	for (;left < right;left++)
	{
		if (left == right) return true;
		if (pGameMap[nRow][left]!=100) break;
	}
	return false;
}