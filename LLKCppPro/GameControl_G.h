#pragma once
#include "Graph.h"
#include "global.h"
class CGameControl_G
{
public:
	CGameControl_G();
	~CGameControl_G();
	CGraph m_graph;
	int GetElement(int nRow, int nCol);
	bool PushVex(CGraph &g, Vertex V);

	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
};

