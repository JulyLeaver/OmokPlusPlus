#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;
ObjectManager * ObjectManager::getInstance()
{
	return instance == nullptr ? instance = new ObjectManager() : instance;
}

ObjectManager::~ObjectManager()
{
	for (auto i : obj)
	{
		delete i;
	}
}

void ObjectManager::draw(HDC hdc, PAINTSTRUCT ps)
{
	for (auto i : obj)
	{
		i->draw(hdc, ps);

		SelectObject(hdc, (HPEN)GetStockObject(NULL_PEN));
		SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
	}
}

void ObjectManager::mouseEvent(UINT ent, WPARAM wParam, LPARAM lParam)
{
	for (auto i : obj)
	{
		i->mouseEvent(ent, wParam, lParam);
	}
}

void ObjectManager::cmdEvent(WPARAM wParam, LPARAM lParam)
{
	for (auto i : obj)
	{
		i->cmdEvent(wParam, lParam);
	}
}
