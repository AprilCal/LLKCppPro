#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();
	void ReleaseMap(int **&pGameMap);
	bool IsBlank(int **anMap);

	bool IsLink(Path* path,int** pGameMap, Vertex v1, Vertex v2);
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);
	bool IsSame(int** pGameMap, Vertex v1, Vertex v2);
	bool OneCornerLink(Path* path,int** pGameMap, Vertex v1, Vertex v2);
	bool TwoCornerLinkBasedOnX(Path* path,int** pGameMap, Vertex v1, Vertex v2);
	bool TwoCornerLinkBasedOnY(Path* path, int** pGameMap, Vertex v1, Vertex v2);
	
	void FreePathList(Path *path);
private:
	int nRows;
	int nCols;
};

