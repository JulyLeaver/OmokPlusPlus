#pragma once

#include <Windows.h>
#include "WindowsCreate.h"
#include "ObjectManager.h"

class WindowsEngin : public WindowsCreate
{
private:
	ObjectManager* objManager;

public:
	WindowsEngin(HINSTANCE hInstance, int nCmdShow);
	virtual ~WindowsEngin() override;

private:
	virtual void draw(HDC hdc, PAINTSTRUCT ps) override;
	virtual void mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam) override;

	virtual void init() override;
	virtual void destroy() override;
};