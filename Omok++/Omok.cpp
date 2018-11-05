#include "Omok.h"

const string Omok::Player2String[] = { "Èæ", "¹é" };

Omok::Omok() :
	DirCostY{ -1, 1, 0, 0, -1, -1, 1, 1 },
	DirCostX{ 0, 0, -1, 1, -1, 1, -1, 1 },
	board(std::vector<std::vector<Player>>(SIZE, std::vector<Player>(SIZE, Player::None))),
	autoPlay(false),
	nowPlayer(Player::Black)
{
}

Omok::~Omok()
{
}

bool Omok::put(const Vec2& v)
{
	if (board[v.y][v.x] != Player::None)
	{
		return false;
	}

	board[v.y][v.x] = nowPlayer;
	records.insert({v, nowPlayer});

	nowPlayer = nowPlayer == Player::Black ? Player::White : Player::Black;
	return true;
}
