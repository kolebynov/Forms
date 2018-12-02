#pragma once

#include "Macros.h"
#include "BaseComponent.h"
#include "FormStyles.h"
#include "EnumUtils.h"

namespace Forms
{
	class FORMS_API Form : public BaseComponent
	{
	public:
		Form(const std::wstring &name);
		virtual ~Form();
		int GetId();

		void Show();

		void SetStyle(FormStyles style);
		FormStyles GetStyle();

		bool HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void OnPaint(std::function<void()> handler);

	private:
		int _id;
		FormStyles _styles;
		std::vector<std::function<void()>> _onPaintHandlers;

		void InitForm();
	};
}