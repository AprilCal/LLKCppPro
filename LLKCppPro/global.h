#pragma once


#define BLANK 100

#define GAME_LOSE -1//游戏失败
#define GAME_SUCCESS 0//游戏获胜
#define GAME_PLAY 1//游戏正在进行

#define PLAY_TIMER_ID 1

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

struct Score
{
	int time;
};