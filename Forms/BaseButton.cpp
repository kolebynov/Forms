#include "stdafx.h"
#include "BaseButton.h"

namespace Forms
{
	BaseButton::BaseButton(DWORD btnStyle) : BaseControl(L"BUTTON", [this, btnStyle]
	{
		defStyle |= WS_TABSTOP;
		SetInternalStyle(btnStyle);
		SetHeight(35);
		SetWidth(70);
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