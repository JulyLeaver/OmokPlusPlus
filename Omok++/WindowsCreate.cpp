#include "WindowsCreate.h"

HINSTANCE WindowsCreate::hInstance;
const TCHAR* WindowsCreate::CLASS_NAME = TEXT("Omok++");

function<void(HDC, PAINTSTRUCT)> WindowsCreate::drawFunc;
function<void(UINT, WPARAM, LPARAM)> WindowsCreate::mouseEventFunc;
function<void(WPARAM, LPARAM)> WindowsCreate::cmdEventFunc;

WindowsCreate::WindowsCreate(HINSTANCE hInstance, int nCmdShow)
{
	WindowsCreate::hInstance = hInstance;

	WindowsCreate::drawFunc = bind(&WindowsCreate::draw, this, placeholders::_1, placeholders::_2);
	WindowsCreate::mouseEventFunc = bind(&WindowsCreate::mouseEvent, this, placeholders::_1, placeholders::_2, placeholders::_3);
	WindowsCreate::cmdEventFunc = bind(&WindowsCreate::cmdEvent, this, placeholders::_1, placeholders::_2);

	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowsCreate::WndProc;
	wndClass.cbClsExtra = wndClass.cbWndExtra = 0; // 예약 영역, 특수 목적, 사용하지 않으면 0
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDC_ARROW);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = WindowsCreate::CLASS_NAME;

	RegisterClass(&wndClass);

	this->hWnd = CreateWindow(
		WindowsCreate::CLASS_NAME, WindowsCreate::CLASS_NAME,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
		WND_WIDTH, WND_HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(this->hWnd, nCmdShow);

//	OutputDebugString("Windows Create End\n");
}

MSG WindowsCreate::start()
{
//	OutputDebugString("START\n");

	init();

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	destroy();

	return msg;
}

LRESULT CALLBACK WindowsCreate::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_CREATE:
		return 0;

	case WM_PAINT:
	//	OutputDebugString("WM_PAINT\n");
		hdc = BeginPaint(hWnd, &ps);

		drawFunc(hdc, ps);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		mouseEventFunc(iMsg, wParam, lParam);
		return 0;

	case WM_COMMAND:
		cmdEventFunc(wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
