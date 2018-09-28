#pragma once

#include <Windows.h>
#include "util.h"
#include "ObjectManager.h"
#include "Omok.h"

class GameBoard : public Object
{
private:
	Vec2 clientWndSize; // 윈도우 작업 영역 크기
	RECT gameBoardRect; // 윈도우에서 게임판의 대략 범위

	int boardN; // 게임판 라인 갯수
	int boardMargin; // 게임판 여백
	int boardSize; // 게임판 크기
	int board1pxSize; // 게임판 1개의 정사각형 크기

	int cursorSize;
	Vec2 cursorIdx; // 마우스가 가르키는 게임판 인덱스
	RECT cursorRect; // 마우스 커서가 인식하는 게임판 범위

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

