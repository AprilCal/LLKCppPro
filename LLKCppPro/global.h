#pragma once


#define BLANK 100

#define GAME_LOSE -1//��Ϸʧ��
#define GAME_SUCCESS 0//��Ϸ��ʤ
#define GAME_PLAY 1//��Ϸ���ڽ���

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