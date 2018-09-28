#pragma once

#include <Windows.h>
#include <vector>
#include "util.h"

class Object
{
private:
	HWND hWnd;
	HDC hdc;

public:
	Object(HWND hWnd) : hWnd(hWnd) {}
	~Object() = default;

	/*
	inline HDC getHdc()
	{
		return hdc;
	}
	*/
	inline void setHDC(HDC hdc)
	{
		this->hdc = hdc;
	}

	inline HWND getHWND()
	{
		return hWnd;
	}

	/*
	WM_PAINT 贸府
	*/
	virtual void draw(HDC& hdc, PAINTSTRUCT& ps) = 0; 
	inline void line(const Vec2& sv, const Vec2& ev)
	{
		MoveToEx(hdc, sv.x, sv.y, NULL);
		LineTo(hdc, ev.x, ev.y);
	}
	inline void rect(const Vec2& sv, const Vec2& size)
	{
		Rectangle(hdc, sv.x, sv.y, sv.x + size.x, sv.y + size.y);
	}
	inline void square(const Vec2& sv, const int r, const std::pair<float, float>& anc = { 0, 0 })
	{
		Rectangle(hdc,
			sv.x - (anc.first * r),
			sv.y - (anc.second * r),
			sv.x + ((1.0f - anc.first) * r),
			sv.y + ((1.0f - anc.second) * r));
	}

	/*
	付快胶 捞亥飘 贸府
	*/
	virtual void mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam) = 0;
};

class ObjectManager
{
public:
	static ObjectManager* instance;
	static ObjectManager* getInstance();

private:
	std::vector<Object*> obj;

	ObjectManager() = default;
	
public:
	~ObjectManager();
	inline void add(Object* obj)
	{
		this->obj.push_back(obj);
	}
	void draw(HDC hdc, PAINTSTRUCT ps);
	void mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam);
};