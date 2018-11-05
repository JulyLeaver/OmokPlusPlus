#pragma once

#include <vector>
#include "util.h"

using namespace std;

using Board = vector<vector<int>>;

enum class Player { Black = 0, White = 1 };

struct Record
{
	Vec2 point;
	Player player;
	Record(const Vec2& point, Player player) : point(point), player(player)
	{}
};

class Omok
{
private:
	enum class MinMax { Max = 0, Min = 1 };
	enum class Direction { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

	const int DirCostY[8];
	const int DirCostX[8];

public:
	const static int SIZE = 15;

private:
	Board board;
	vector<Record> records;

	bool _auto;
	Player player;
public:
	Omok();
	~Omok();

	bool put(const Vec2& v);

	inline void autoPlay(bool _auto) { this->_auto = _auto; }
	inline const Board& getBoard() { return board; }
	inline const vector<Record>& getRecords() { return records; }

//	int minimax(const Board& board, )

	inline bool validPoint(const Vec2& v)
	{
		return (
			0 <= v.y && v.y < SIZE &&
			0 <= v.x && v.x < SIZE
			);
	}

	inline bool ablePoint(const Board& board, const Vec2& v)
	{
		if (!validPoint(v)) return false;
		return board[v.y][v.x] == -1;
	}

	Vec2 playerEndLinePoint(const Board& board, const Vec2& start, const Player player, const Direction dir)
	{
		int r = start.y, c = start.x;
		const int delR = DirCostY[static_cast<int>(dir)], delC = DirCostX[static_cast<int>(dir)];
		while (
			0 <= r + delR && r + delR < SIZE &&
			0 <= c + delC && c + delC < SIZE &&
			board[r + delR][c + delC] == static_cast<int>(player)
			)
		{
			r += delR;
			c += delC;
		}
		return { r, c };
	}

	/*
	5 <= cc : INF
	*/
//	int calcCost(const Board& board, const int player);
};

