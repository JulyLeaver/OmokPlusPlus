#pragma once

#include <vector>
#include "util.h"

using namespace std;

enum class Player { Black = 0, White = 1, None };

using Board = vector<vector<Player>>;

struct Record
{
	Vec2 point;
	Player player;
	Record(const Vec2& point, Player player) : point(point), player(player)
	{
	}
	bool operator<(const Record& a) const
	{
		return point < a.point;
	}
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
	const static string Player2String[2];

private:
	Board board;
	vector<Record> records;

	bool autoPlay;
	Player nowPlayer;
public:
	Omok();
	~Omok();

	bool put(const Vec2& v);
	inline void reset()
	{
		board = vector<vector<Player>>(SIZE, vector<Player>(SIZE, Player::None));
		records.clear();

		autoPlay = false;
		nowPlayer = Player::Black;
		put({ SIZE / 2, SIZE / 2 });
	}

	inline void setAutoPlay(bool _auto) { this->autoPlay = _auto; }
	inline const Board& getBoard() { return board; }
	inline const vector<Record>& getRecords() { return records; }
	inline void delPrevRecord()
	{
		if (1 < records.size())
		{
			board[records.back().point.y][records.back().point.x] = Player::None;
			records.pop_back();
			nowPlayer = nowPlayer == Player::Black ? Player::White : Player::Black;
		}
	}
	inline Player getPointPlayer(const Vec2& p) { return board[p.y][p.x]; }
	inline Player getNowPlayer() { return nowPlayer; }

private:
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
		return board[v.y][v.x] == Player::None;
	}

	Vec2 playerEndLinePoint(const Board& board, const Vec2& start, const Player player, const Direction dir)
	{
		int r = start.y, c = start.x;
		const int delR = DirCostY[static_cast<int>(dir)], delC = DirCostX[static_cast<int>(dir)];
		while (
			0 <= r + delR && r + delR < SIZE &&
			0 <= c + delC && c + delC < SIZE &&
			board[r + delR][c + delC] == player
			)
		{
			r += delR;
			c += delC;
		}
		return { r, c };
	}

	int calcCost(const Board& board)
	{

	}
};

