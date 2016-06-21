#pragma once
#include "global.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	int **m_pGameMap;
	int GetElement(int nRow, int nCol);
	bool PushVex(Vertex V);
	int** ResetMap();
	BOOL IsWin(int nTime);

	Vertex m_svSelFst;//first vex selected
	Vertex m_svSelSec;//second vex selected
private:
};

