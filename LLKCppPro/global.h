#pragma once


#define BLANK 100
struct Vertex
{
	int nRow;
	int nCol;
};

struct Path
{
	Vertex v;
	Path* next;
};