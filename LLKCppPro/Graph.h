#pragma once
class CGraph
{
public:
	CGraph();
	~CGraph();
public:
	int m_Vertices[160];
	bool m_AdjMatrix[160][160];
	int m_nVexnum;//number of vex
	int m_nArcnum;//number of edge

	void InitGraph();
	int GetVertex(int nIndex);
	void SetVertex(int nIndex, int n);
	int GetElement(int nRow, int nCol);
	void SetElement(int nRow, int nCol, int n);
	void AddArc(int v1, int v2);
	bool GetArc(int v1, int v2);
};

