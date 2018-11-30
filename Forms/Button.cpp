#include "stdafx.h"
#include "Button.h"

using namespace Forms;

Button::Button() : BaseComponent(L"BUTTON", [this] 
{
	AppendStyle(WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);
	SetHeight(50);
	SetWidth(100); 
})
{
	
}

void Forms::Button::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_COMMAND)
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			RaiseClickEvent();
		}
	}
}
