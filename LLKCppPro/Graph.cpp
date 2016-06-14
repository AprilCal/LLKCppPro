#include "stdafx.h"
#include "Graph.h"
#include "GameControl_G.h"


CGraph::CGraph()
{
}


CGraph::~CGraph()
{
}

void CGraph::InitGraph()
{
	for (int i = 0;i < 16;i++)
	{
		m_Vertices[i] = i;
	}
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

void CGraph::SetVertex(int nIndex,int n)
{
	m_Vertices[nIndex] = n;
}

int CGraph::GetElement(int nRow, int nCol)
{
	return GetVertex(nRow*CGameControl_G::s_nCols + nCol);
}

void CGraph::SetElement(int nRow, int nCol, int n)
{
	SetVertex(nRow*CGameControl_G::s_nCols + nCol, n);
}

void CGraph::AddArc(int v1, int v2)
{
	m_AdjMatrix[v1][v2] = true;
	m_AdjMatrix[v2][v1] = true;
}