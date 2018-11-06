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

	int cursorSize; // 커서가 가르킬 때 표시되는 사각형 크기
	Vec2 cursorIdx; // 마우스가 가르키는 게임판 인덱스, 죄측 상단 (0,0)
	RECT cursorRect; // 마우스 커서가 인식하는 게임판의 범위

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

