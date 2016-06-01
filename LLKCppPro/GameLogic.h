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
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);
	bool IsSame(int** pGameMap, Vertex v1, Vertex v2);
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);
	bool TwoCornerLinkBasedOnX(int** pGameMap, Vertex v1, Vertex v2);
	bool TwoCornerLinkBasedOnY(int** pGameMap, Vertex v1, Vertex v2);
private:
	int nRows;
	int nCols;
};

