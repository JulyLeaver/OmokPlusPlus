#include "GameBoard.h"

GameBoard::GameBoard(const HWND hWnd, Logger* logger) : Object(hWnd, logger)
{
	RECT t;
	GetClientRect(hWnd, &t);

	clientWndSize = { t.right, t.bottom };
	gameBoardRect.left = gameBoardRect.right = 0;
	gameBoardRect.right = gameBoardRect.bottom = clientWndSize.y;

	boardN = Omok::SIZE;
	boardMargin = 42;
	boardSize = clientWndSize.y - 2 * boardMargin;
	board1pxSize = boardSize / (boardN - 1);

	cursorSize = static_cast<int>(board1pxSize * 1.0);
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
	blackPlayerColor = RGB(0, 0, 0);
	whitePlayerColor = RGB(255, 255, 255);

	boardEdgePen = CreatePen(PS_SOLID, 2, boardLineColor);
	boardLinePen = CreatePen(PS_SOLID, 1, boardLineColor);

	boardBackgroungBrush = CreateSolidBrush(boardColor);
	cursorBrush = CreateSolidBrush(cursorColor);
	blackPlayerBrush = CreateSolidBrush(blackPlayerColor);
	whitePlayerBrush = CreateSolidBrush(whitePlayerColor);
}

GameBoard::~GameBoard()
{
	DeleteObject(boardEdgePen);
	DeleteObject(boardLinePen);

	DeleteObject(boardBackgroungBrush);
	DeleteObject(cursorBrush);
}

void GameBoard::draw(HDC& hdc, PAINTSTRUCT& ps)
{
	setHDC(hdc); // �ʼ�

	// ������ ���� �� ���� ����
	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	SelectObject(hdc, boardBackgroungBrush);
	rect({ boardMargin / 2, boardMargin / 2 }, { boardSize + boardMargin, boardSize + boardMargin });

	// ������ �׵θ�
	SelectObject(hdc, boardEdgePen);
	rect({ boardMargin, boardMargin }, { boardSize, boardSize });

	// ������ ����
	SelectObject(hdc, boardLinePen);
	for (int i = 1; i < boardN - 1; ++i)
	{
		const int d = boardMargin + i * board1pxSize;
		line({ boardMargin, d }, { boardMargin + boardSize, d });
		line({ d,boardMargin }, { d, boardMargin + boardSize });
	}

	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	const set<Record>& records = omok.getRecords();
	for (auto i : records)
	{
		if (i.player == Player::Black)
		{
			SelectObject(hdc, blackPlayerBrush);
		}
		else
		{
			SelectObject(hdc, whitePlayerBrush);
		}
		const Vec2 point = {
			boardMargin + board1pxSize * i.point.x,
			boardMargin + board1pxSize * i.point.y
		};
		ellipse(point, cursorSize, { 0.5f, 0.5f });
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
			{ 0.5f, 0.5f });
	}
}

void GameBoard::mouseEvent(UINT& ent, WPARAM& wParam, LPARAM& lParam)
{
	const int X = LOWORD(lParam), Y = HIWORD(lParam);

	// ������ ���� �Ѿ�� ������ ��ȿȭ ó��
	if (!Vec2(X, Y).isInside(cursorRect))
	{
		if (cursorIdx.x != -1) // �����̴µ� ������ ���� ���콺�� �������� �ʴ´ٸ�
		{
			cursorIdx.x = cursorIdx.y = -1;
			InvalidateRect(getHWND(), NULL, true);
		}
		return;
	}

	if (ent == WM_MOUSEMOVE)
	{
		const Vec2 thisIdx(
			(X - boardMargin + board1pxSize / 2) / board1pxSize,
			(Y - boardMargin + board1pxSize / 2) / board1pxSize);
		if (thisIdx == cursorIdx) return;
		cursorIdx = thisIdx;
		InvalidateRect(getHWND(), NULL, true);
	}
	else if (ent == WM_LBUTTONDOWN)
	{
		const string pointString = "(" + to_string(cursorIdx.x) + ", " + to_string(cursorIdx.y) + ")";
		if (omok.put(cursorIdx))
		{
			logger->log(pointString + " " + Omok::Player2String[static_cast<int>(omok.getPointPlayer(cursorIdx))]);
		//	cursorIdx = { -1,-1 };
			InvalidateRect(getHWND(), NULL, true);
		}
		else
		{
			logger->log(pointString + "�� �̹� ���� �����մϴ�.");
		}
		return;
	}
}
