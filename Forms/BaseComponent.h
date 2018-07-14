#pragma once

#include "Macros.h"
#include <string>
#include <unordered_set>
#include <functional>

namespace Forms
{
	class FORMS_API BaseComponent
	{
	public:
		HWND GetHwnd();
		int GetWidth();
		void SetWidth(int width);

		int GetHeight();
		void SetHeight(int height);

		const std::wstring& GetCaption() const;
		void SetCaption(const std::wstring &caption);

		int GetX();
		void SetX(int x);

		int GetY();
		void SetY(int y);

		BaseComponent* GetParentComponent();
		void SetParentComponent(BaseComponent *parent);

		void Show();
		virtual LRESULT HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void AddChild(BaseComponent *child);
		void RemoveChild(BaseComponent *child);

	protected:
		BaseComponent();
		BaseComponent(const std::wstring &componentClassName);
		~BaseComponent();

		void InitComponent();
		void DestroyComponent();
		HINSTANCE GetHinstance();

		const std::wstring& GetComponentClassName() const;
		void SetComponentClassName(const std::wstring &componentClassName);
		void AppendStyle(int style);
		void InitComponentOrDoAction(std::function<void(void)> action);
		void InitComponentAndDoAction(std::function<void(void)> action);

	private:
		HWND _hwnd;
		int _width, _height;
		int _styles;
		int _x, _y;
		std::wstring _caption, _componentClassName;
		HINSTANCE _hInstance;
		BaseComponent *_parent;
		std::unordered_set<BaseComponent*> _childComponents;

		void ShowChildComponents();
		void DestroyChildComponents();
	};
}