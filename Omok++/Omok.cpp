#include "Omok.h"

Omok::Omok() :
	DirCostY{ -1, 1, 0, 0, -1, -1, 1, 1 },
	DirCostX{ 0, 0, -1, 1, -1, 1, -1, 1 },
	board(std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE))),
	_auto(false),
	player(Player::Black)
{
}

Omok::~Omok()
{
}

bool Omok::put(const Vec2& v)
{
	int& p = board[v.y][v.x];
//	if (p != -1) return false;

	records.push_back(Record(v, player));

	player = player == Player::Black ? Player::White : Player::Black;

	return true;
}
