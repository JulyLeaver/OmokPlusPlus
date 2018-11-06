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
	COLORREF finallyPointColor;

	HPEN boardEdgePen;
	HPEN boardLinePen;

	HBRUSH boardBackgroungBrush;
	HBRUSH cursorBrush;
	HBRUSH blackPlayerBrush;
	HBRUSH whitePlayerBrush;
	HBRUSH finallyPointBrush;

private:
	Omok omok;

public:
	const int NEW_GAME_BUTTON_ID = 1000;
	const int PREV_BUTTON_ID = 1001;
	const int AI_BUTTON_ID = 1002;

public:
	GameBoard(const HWND hWnd, Logger* logger);
	~GameBoard();
	virtual void draw(HDC& hdc, PAINTSTRUCT& ps) override;
	virtual void mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam) override;
	virtual void cmdEvent(WPARAM wParam, LPARAM lParam) override;

	void omokStart();
};

