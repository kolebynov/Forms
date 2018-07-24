#pragma once

#include "Macros.h"
#include "BaseComponent.h"

namespace Forms
{
	class FORMS_API Form : public BaseComponent
	{
	public:
		Form(const std::wstring &name);

		virtual LRESULT HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		void InitComponent();
		void DestroyComponent();
	};
}