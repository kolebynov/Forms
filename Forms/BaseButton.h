#pragma once
#include "stdafx.h"
#include "BaseControl.h"

namespace Forms
{
	class FORMS_API BaseButton : public BaseControl
	{
	public:
		bool HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		BaseButton(DWORD btnStyle);
	};
}

