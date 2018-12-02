#pragma once
#include "stdafx.h"
#include "BaseComponent.h"

namespace Forms
{
	class FORMS_API BaseButton : public BaseComponent
	{
	public:
		bool HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		BaseButton(DWORD btnStyle);
	};
}

