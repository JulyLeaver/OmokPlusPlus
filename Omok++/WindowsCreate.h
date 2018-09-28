#pragma once

#include <Windows.h>
#include <functional>

class WindowsCreate
{
public:
	const int WND_WIDTH = 1000, WND_HEIGHT = 600;
	HWND hWnd; // ���� ������ �ڵ�

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
	static const TCHAR* CLASS_NAME; // Ÿ��Ʋ �̸��� ����
	static HINSTANCE hInstance; // ���α׷� �ڵ�
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lPara);
	
	static std::function<void(HDC, PAINTSTRUCT)> drawFunc;

	// "���콺 L, R ��ư �ٿ�, ������" �� ó��
	static std::function<void(UINT, WPARAM, LPARAM)> mouseEventFunc;
};