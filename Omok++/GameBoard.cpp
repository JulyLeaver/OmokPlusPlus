#include "GameBoard.h"
#include "WindowsCreate.h"

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
	finallyPointColor = RGB(255, 0, 0);

	boardEdgePen = CreatePen(PS_SOLID, 2, boardLineColor);
	boardLinePen = CreatePen(PS_SOLID, 1, boardLineColor);

	boardBackgroungBrush = CreateSolidBrush(boardColor);
	cursorBrush = CreateSolidBrush(cursorColor);
	blackPlayerBrush = CreateSolidBrush(blackPlayerColor);
	whitePlayerBrush = CreateSolidBrush(whitePlayerColor);
	finallyPointBrush = CreateSolidBrush(finallyPointColor);

	CreateWindow(TEXT("button"), TEXT("New"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		boardMargin * 2 + boardSize,
		boardMargin,
		60, 60,
		hWnd, (HMENU)NEW_GAME_BUTTON_ID, WindowsCreate::hInstance, NULL);

	CreateWindow(TEXT("button"), TEXT("Prev"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		boardMargin * 2 + boardSize,
		boardMargin + 60 + 20,
		60, 60,
		hWnd, (HMENU)PREV_BUTTON_ID, WindowsCreate::hInstance, NULL);

	CreateWindow(TEXT("button"), TEXT("AI"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		boardMargin * 2 + boardSize,
		boardMargin + 120 + 40,
		60, 60,
		hWnd, (HMENU)AI_BUTTON_ID, WindowsCreate::hInstance, NULL);

	omokStart();
}

GameBoard::~GameBoard()
{
	DeleteObject(boardEdgePen);
	DeleteObject(boardLinePen);

	DeleteObject(boardBackgroungBrush);
	DeleteObject(cursorBrush);
	DeleteObject(blackPlayerBrush);
	DeleteObject(whitePlayerBrush);
	DeleteObject(finallyPointBrush);
}

void GameBoard::draw(HDC& hdc, PAINTSTRUCT& ps)
{
	setHDC(hdc); // 필수

	// 게임판 생성 및 배경색 지정
	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	SelectObject(hdc, boardBackgroungBrush);
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

	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	const auto& records = omok.getRecords();
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
		ellipse(point, cursorSize * 0.9, { 0.5f, 0.5f });
	}

	SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
	SelectObject(hdc, finallyPointBrush);
	const Vec2 finallyPoint = {
			boardMargin + board1pxSize * records.back().point.x,
			boardMargin + board1pxSize * records.back().point.y
	};
	square(finallyPoint, cursorSize * 0.35, { 0.5f, 0.5f });

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

	// 게임판 범위 넘어가면 모든것을 무효화 처리
	if (!Vec2(X, Y).isInside(cursorRect))
	{
		if (cursorIdx.x != -1) // 움직이는데 게임판 위에 마우스가 존재하지 않는다면
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
		return;
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
			logger->log(pointString + "에 이미 돌이 존재합니다.");
		}
		return;
	}
}

void GameBoard::cmdEvent(WPARAM wParam, LPARAM lParam)
{
	const int ID = LOWORD(wParam);
	if (ID == PREV_BUTTON_ID)
	{
		logger->log("이전으로 돌아갑니다.");
		const auto& records = omok.getRecords();
		omok.delPrevRecord();
		InvalidateRect(getHWND(), NULL, true);
	}
	else if (ID == AI_BUTTON_ID)
	{
		logger->log(Omok::Player2String[static_cast<int>(omok.getNowPlayer())] + "돌을 AI에게 맡깁니다.");
	}
	else if (ID == NEW_GAME_BUTTON_ID)
	{
	//	logger->log("새로운 게임을 시작합니다.");
		omokStart();
	}
}

void GameBoard::omokStart()
{
	omok.reset();
	InvalidateRect(getHWND(), NULL, true);

	system("cls");
	const string startPoint = "(" + to_string(Omok::SIZE / 2) + ", " + to_string(Omok::SIZE / 2) + ")";
	logger->log(startPoint + " 흑");
}
