#pragma once

#include "Macros.h"
#include "BaseComponent.h"

namespace Forms
{
	class FORMS_API Form : public BaseComponent
	{
	public:
		Form(const std::wstring &name);
		virtual ~Form();
		int GetId();

		virtual LRESULT HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void OnPaint(std::function<void()> handler);

	private:
		int _id;
		std::vector<std::function<void()>> _onPaintHandlers;

		void InitForm();
	};
}