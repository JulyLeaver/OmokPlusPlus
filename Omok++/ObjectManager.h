#pragma once

#include <Windows.h>
#include <vector>
#include "Logger.h"
#include "util.h"

using namespace std;

class Object
{
private:
	const HWND hWnd;
	HDC hdc;

protected:
	Logger* logger;

public:
	Object(const HWND hWnd, Logger* logger) : hWnd(hWnd), logger(logger) {}
	~Object() = default;

//	inline HDC getHdc() { return hdc; }
	inline void setHDC(HDC hdc) { this->hdc = hdc; }
	inline HWND getHWND() { return hWnd; }

	/*
	WM_PAINT 贸府
	*/
	virtual void draw(HDC& hdc, PAINTSTRUCT& ps) = 0; 

	/*
	付快胶 捞亥飘 贸府
	*/
	virtual void mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam) = 0;

	virtual void cmdEvent(WPARAM wParam, LPARAM lParam) = 0;

	inline void line(const Vec2& sv, const Vec2& ev)
	{
		MoveToEx(hdc, sv.x, sv.y, NULL);
		LineTo(hdc, ev.x, ev.y);
	}
	inline void rect(const Vec2& sv, const Vec2& size)
	{
		Rectangle(hdc, sv.x, sv.y, sv.x + size.x, sv.y + size.y);
	}
	inline void square(const Vec2& sv, const int r, const pair<float, float>& anc = { 0.0f, 0.0f })
	{
		Rectangle(hdc,
			sv.x - static_cast<int>(anc.first * r),
			sv.y - static_cast<int>(anc.second * r),
			sv.x + static_cast<int>((1.0f - anc.first) * r),
			sv.y + static_cast<int>((1.0f - anc.second) * r));
	}
	inline void ellipse(const Vec2& sv, const int r, const pair<float, float>& anc = { 0.0f, 0.0f })
	{
		Ellipse(hdc,
			sv.x - static_cast<int>(anc.first * r),
			sv.y - static_cast<int>(anc.second * r),
			sv.x + static_cast<int>((1.0f - anc.first) * r),
			sv.y + static_cast<int>((1.0f - anc.second) * r));
	}
};

class ObjectManager
{
public:
	static ObjectManager* instance;
	static ObjectManager* getInstance();

private:
	vector<Object*> obj;

	ObjectManager() = default;
	
public:
	~ObjectManager();
	inline void add(Object* obj) { this->obj.push_back(obj); }
	void draw(HDC hdc, PAINTSTRUCT ps);
	void mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam);
	void cmdEvent(WPARAM wParam, LPARAM lParam);
};