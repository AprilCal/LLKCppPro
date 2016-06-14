#include "stdafx.h"
#include "GameLogic_G.h"
#include "GameControl_G.h"
#include "global.h"


CGameLogic_G::CGameLogic_G()
{
}


CGameLogic_G::~CGameLogic_G()
{
}

void CGameLogic_G::InitMap(CGraph &g)
{
	int nRows = CGameControl_G::s_nRows;
	int nCols = CGameControl_G::s_nCols;
	for (int i = 0;i < nRows;i++)
	{
		for (int j = 0;j < nCols;j++)
		{
			g.m_Vertices[i*nCols + j] = j;
		}
	}

	srand((int)time(NULL));
	int nVertexNum = nRows*nCols;
	for (int i = 0;i < nVertexNum;i++)
	{
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		int nTmp = g.GetVertex(nIndex1);
		g.SetVertex(nIndex1,g.GetVertex(nIndex2));
		g.SetVertex(nIndex2, nTmp);
	}
	for (int i = 0;i < 100;i++)
	{
		for (int j = 0;j < 100;j++)
		{
			g.m_AdjMatrix[i][j] = 1;
		}
	}

}

bool CGameLogic_G::IsSame(CGraph *g, Vertex v1, Vertex v2)
{
	if (g->GetElement(v1.nRow, v1.nCol) == g->GetElement(v2.nRow, v2.nCol))
	{
		return true;
	}
	else
	{
		return false;
	}
}