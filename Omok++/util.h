#pragma once

#include <Windows.h>
#include <utility>

struct Vec2
{
public:
	int x, y;
	Vec2() {}
	Vec2(int x, int y) : x(x), y(y) {}
	bool operator<(const Vec2& v) const
	{
		return x < v.x || (!(v.x < x) && y < v.y);
	}
	bool operator==(const Vec2& v) const
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const Vec2& v) const
	{
		return !(operator==(v));
	}
	inline bool isInside(const RECT& rect)
	{
		return (
			rect.left <= x && x <= rect.right &&
			rect.top <= y && y <= rect.bottom
			);
	}
public:
};