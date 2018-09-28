#include "WindowsEngin.h"
#include "GameBoard.h"

WindowsEngin::WindowsEngin(HINSTANCE hInstance, int nCmdShow) : WindowsCreate(hInstance, nCmdShow)
{
	objManager = ObjectManager::getInstance();
	objManager->add(new GameBoard(hWnd));
}

WindowsEngin::~WindowsEngin()
{
	WindowsCreate::~WindowsCreate();
}

void WindowsEngin::draw(HDC hdc, PAINTSTRUCT ps)
{
	objManager->draw(hdc, ps);
}

void WindowsEngin::mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam)
{
	objManager->mouseEvent(ent, wParam, lParam);
}

void WindowsEngin::init()
{
}

void WindowsEngin::destroy()
{
	delete objManager;
}
