#include "stdafx.h"
#include "Button.h"

using namespace Forms;

Button::Button() : BaseComponent(L"BUTTON", nullptr)
{
	AppendStyle(WS_CHILD | BS_NULL);
	SetHeight(50);
	SetWidth(100);
}

LRESULT Forms::Button::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
