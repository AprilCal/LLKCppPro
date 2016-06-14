#include "stdafx.h"
#include "GameControl_G.h"

int CGameControl_G::s_nRows = 10;
int CGameControl_G::s_nCols = 16;
int CGameControl_G::s_nPicNum = 16;

CGameControl_G::CGameControl_G()
{
}


CGameControl_G::~CGameControl_G()
{
}

int CGameControl_G::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow*CGameControl_G::s_nCols + nCol);
}

bool CGameControl_G::PushVex(CGraph &g, Vertex V)
{
	if (g.GetElement(V.nRow, V.nCol) != BLANK)
	{
		g.SetElement(V.nRow, V.nCol, BLANK);
		return true;
	}
	else
	{
		return false;
	}
}