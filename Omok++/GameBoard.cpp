#include "GameBoard.h"

#include <iostream>

GameBoard::GameBoard(HWND hWnd) : Object(hWnd)
{
	RECT t;
	GetClientRect(hWnd, &t);

	clientWndSize = { t.right, t.bottom };
	gameBoardRect.left = gameBoardRect.right = 0;
	gameBoardRect.right = gameBoardRect.bottom = clientWndSize.y;

	boardN = 15;
	boardMargin = 42;
	boardSize = clientWndSize.y - 2 * boardMargin;
	board1pxSize = boardSize / (boardN - 1);

	cursorSize = static_cast<int>(board1pxSize * 0.85);
	cursorIdx = { -1,-1 };
	cursorRect =
	{
		boardMargin - board1pxSize / 2, 
		boardMargin - board1pxSize / 2,

		boardMargin + boardSize + board1pxSize / 2,
		boardMargin + boardSize + board1pxSize / 2
	};

	boardColor = RGB(220, 179, 92);
	boardLineColor = RGB(0, 0, 0);
	cursorColor = RGB(255, 255, 0);

	boardEdgePen = CreatePen(PS_SOLID, 2, boardLineColor);
	boardLinePen = CreatePen(PS_SOLID, 1, boardLineColor);

	boardBackBrush = CreateSolidBrush(boardColor);
	cursorBrush = CreateSolidBrush(cursorColor);
}

GameBoard::~GameBoard()
{
	DeleteObject(boardEdgePen);
	DeleteObject(boardLinePen);

	DeleteObject(boardBackBrush);
	DeleteObject(cursorBrush);
}

void GameBoard::draw(HDC& hdc, PAINTSTRUCT& ps)
{
	setHDC(hdc); // 필수

	// 게임판 생성 및 배경색 지정
	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	SelectObject(hdc, boardBackBrush);
	rect({ boardMargin / 2, boardMargin / 2 }, { boardSize + boardMargin, boardSize + boardMargin });

	// 게임판 테두리
	SelectObject(hdc, boardEdgePen);
	rect({ boardMargin, boardMargin }, { boardSize, boardSize });

	// 게임판 라인
	SelectObject(hdc, boardLinePen);
	for (int i = 1; i < boardN - 1; ++i)
	{
		const int d = boardMargin + i * board1pxSize;
		line({ boardMargin, d }, { boardMargin + boardSize, d });
		line({ d,boardMargin }, { d, boardMargin + boardSize });
	}

	if (cursorIdx.x != -1)
	{
		SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
		SelectObject(hdc, cursorBrush);
		square(
			{ 
				boardMargin + board1pxSize * cursorIdx.x, 
				boardMargin + board1pxSize * cursorIdx.y 
			},
			cursorSize, 
			{ 0.5, 0.5 });

	}
}

void GameBoard::mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam)
{
	const int X = LOWORD(lParam), Y = HIWORD(lParam);
	if (ent == WM_MOUSEMOVE)
	{
		if (!Vec2(X, Y).isInside(cursorRect))
		{
			cursorIdx.x = cursorIdx.y = -1;
		}
		else
		{ 
			cursorIdx.x = (X - boardMargin + board1pxSize / 2) / board1pxSize;
			cursorIdx.y = (Y - boardMargin + board1pxSize / 2) / board1pxSize;
		}
		InvalidateRect(getHWND(), NULL, true);
	}
}
