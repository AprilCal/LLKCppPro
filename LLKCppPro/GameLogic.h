#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();
	void ReleaseMap(int **&pGameMap);
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);
private:
	int nRows;
	int nCols;
};

