#include "stdafx.h"
#include "BaseButton.h"

namespace Forms
{
	BaseButton::BaseButton(DWORD btnStyle) : BaseComponent(L"BUTTON", [this, btnStyle]
	{
		SetInternalStyle(WS_TABSTOP | WS_VISIBLE | WS_CHILD | btnStyle);
		SetHeight(50);
		SetWidth(100);
	})
	{
	}

	bool BaseButton::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_COMMAND)
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				RaiseClickEvent();
			}
		}

		return true;
	}
}