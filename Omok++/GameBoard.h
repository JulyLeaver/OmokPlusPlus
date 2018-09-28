#pragma once

#include <Windows.h>
#include "util.h"
#include "ObjectManager.h"
#include "Omok.h"

class GameBoard : public Object
{
private:
	Vec2 clientWndSize; // ������ �۾� ���� ũ��
	RECT gameBoardRect; // �����쿡�� �������� �뷫 ����

	int boardN; // ������ ���� ����
	int boardMargin; // ������ ����
	int boardSize; // ������ ũ��
	int board1pxSize; // ������ 1���� ���簢�� ũ��

	int cursorSize;
	Vec2 cursorIdx; // ���콺�� ����Ű�� ������ �ε���
	RECT cursorRect; // ���콺 Ŀ���� �ν��ϴ� ������ ����

	COLORREF boardColor;
	COLORREF boardLineColor;
	COLORREF cursorColor;

	HPEN boardEdgePen;
	HPEN boardLinePen;

	HBRUSH boardBackBrush;
	HBRUSH cursorBrush;

private:
	Board board;

public:
	GameBoard(HWND hWnd);
	~GameBoard();
	virtual void draw(HDC& hdc, PAINTSTRUCT& ps) override;
	virtual void mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam) override;
};

