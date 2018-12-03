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

		const std::wstring& GetText() const;
		void SetText(const std::wstring &text);

		int GetX();
		void SetX(int x);

		int GetY();
		void SetY(int y);

		bool IsVisible();
		void SetVisible(bool visible);

		BaseComponent* GetParentComponent();
		void SetParentComponent(BaseComponent *parent);

		const std::pair<std::vector<BaseComponent*>::const_iterator, std::vector<BaseComponent*>::const_iterator> GetChildComponents() const;

		void AddChild(BaseComponent *child);
		void RemoveChild(BaseComponent *child);

		virtual bool HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual ~BaseComponent();
		
		void OnClick(std::function<void()> handler);

	protected:
		int showFlags;
		DWORD defStyle;

		BaseComponent();
		BaseComponent(const std::wstring &componentClassName, std::function<void(void)> beforeInitFunc);
	
		HINSTANCE GetHinstance();
		HWND GetParentHwnd();

		const std::wstring& GetComponentClassName() const;
		void SetComponentClassName(const std::wstring &componentClassName);

		void SetInternalStyle(DWORD style);
		DWORD GetInternalStyle();

		void UpdateWindowSize();
		void SetVisibleInternal(bool visible);
		void UpdateRects();
		void ShowInternal();
		void HideInternal();
		
		void RaiseClickEvent();

	private:
		HWND _hwnd;
		DWORD _styles;
		std::wstring _text, _componentClassName;
		HINSTANCE _hInstance;
		BaseComponent *_parent;
		std::vector<BaseComponent*> _childComponents;
		RECT _windowLocalRect;
		RECT _clientRect;
		bool _isVisible;

		std::vector<std::function<void()>> _onClickHandlers;

		void DestroyChildComponents();
		void InitComponent();
		void DestroyComponent();
		void UpdateWindowStyle();
	};
}