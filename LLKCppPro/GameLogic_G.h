#pragma once
#include "Graph.h"
#include "global.h"
class CGameLogic_G
{
public:
	CGameLogic_G();
	~CGameLogic_G();
	void InitMap(CGraph &g);
	bool IsSame(CGraph *g, Vertex v1, Vertex v2);
};

