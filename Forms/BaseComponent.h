#pragma once

#include "Macros.h"
#include <string>
#include <vector>
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

		int GetClientWidth();
		int GetClientHeight();

		const std::wstring& GetCaption() const;
		void SetCaption(const std::wstring &caption);

		int GetX();
		void SetX(int x);

		int GetY();
		void SetY(int y);

		BaseComponent* GetParentComponent();
		void SetParentComponent(BaseComponent *parent);

		void Show();

		void AddChild(BaseComponent *child);
		void RemoveChild(BaseComponent *child);

		virtual void InitComponent();

		virtual ~BaseComponent();

	protected:
		BaseComponent();
		BaseComponent(const std::wstring &componentClassName);
	
		HINSTANCE GetHinstance();

		const std::wstring& GetComponentClassName() const;
		void SetComponentClassName(const std::wstring &componentClassName);
		void AppendStyle(int style);
		template <class T>
		T InitComponentOrDoAction(std::function<T(void)> action);
		template <class T>
		T InitComponentAndDoAction(std::function<T(void)> action);
		void UpdateWindowSize();
		void UpdateRects();

	private:
		HWND _hwnd;
		int _styles;
		std::wstring _caption, _componentClassName;
		HINSTANCE _hInstance;
		BaseComponent *_parent;
		std::vector<BaseComponent*> _childComponents;
		RECT _windowLocalRect;
		RECT _clientRect;

		void ShowChildComponents();
		void DestroyChildComponents();
		void DestroyComponent();
	};
}