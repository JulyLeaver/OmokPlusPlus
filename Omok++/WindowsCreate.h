#pragma once

#include <Windows.h>
#include <functional>

class WindowsCreate
{
public:
	const int WND_WIDTH = 1000, WND_HEIGHT = 600;
	HWND hWnd; // 메인 윈도우 핸들

public:
	WindowsCreate(HINSTANCE hInstance, int nCmdShow);
	virtual ~WindowsCreate() = default;

	MSG start();

private:
	virtual void init() = 0;
	virtual void draw(HDC hdc, PAINTSTRUCT ps) = 0;
	virtual void mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam) = 0;
	virtual void destroy() = 0;

public:
	static const TCHAR* CLASS_NAME; // 타이틀 이름과 같음
	static HINSTANCE hInstance; // 프로그램 핸들
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lPara);
	
	static std::function<void(HDC, PAINTSTRUCT)> drawFunc;

	// "마우스 L, R 버튼 다운, 움직임" 만 처리
	static std::function<void(UINT, WPARAM, LPARAM)> mouseEventFunc;
};