#pragma once
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
private:
};

