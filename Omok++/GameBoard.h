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

	int cursorSize; // Ŀ���� ����ų �� ǥ�õǴ� �簢�� ũ��
	Vec2 cursorIdx; // ���콺�� ����Ű�� ������ �ε���, ���� ��� (0,0)
	RECT cursorRect; // ���콺 Ŀ���� �ν��ϴ� �������� ����

	COLORREF boardColor;
	COLORREF boardLineColor;
	COLORREF cursorColor;
	COLORREF blackPlayerColor;
	COLORREF whitePlayerColor;

	HPEN boardEdgePen;
	HPEN boardLinePen;

	HBRUSH boardBackgroungBrush;
	HBRUSH cursorBrush;
	HBRUSH blackPlayerBrush;
	HBRUSH whitePlayerBrush;

private:
	Omok omok;

public:
	GameBoard(const HWND hWnd, Logger* logger);
	~GameBoard();
	virtual void draw(HDC& hdc, PAINTSTRUCT& ps) override;
	virtual void mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam) override;
};

