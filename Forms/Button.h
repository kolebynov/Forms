#pragma once

#include "BaseComponent.h";
#include "Macros.h"

namespace Forms
{
	class FORMS_API Button : public BaseComponent
	{
	public:
		Button();
		void HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}