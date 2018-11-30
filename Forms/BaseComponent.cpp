#include "stdafx.h"
#include "BaseComponent.h"
#include "Application.h"

using namespace Forms;
using namespace std;

BaseComponent::BaseComponent() : BaseComponent(L"", nullptr)
{

}

Forms::BaseComponent::BaseComponent(const std::wstring &componentClassName, std::function<void(void)> beforeInitFunc)
{
	_hInstance = Application::GetHinstance();
	_hwnd = nullptr;
	_parent = nullptr;
	_styles = 0;
	showFlags = SW_SHOW;
	_isVisible = true;

	_windowLocalRect = {};
	_clientRect = {};
	SetCaption(L"");
	SetComponentClassName(componentClassName);

	if (beforeInitFunc != nullptr)
	{
		beforeInitFunc();
	}
	InitComponent();
}

HWND Forms::BaseComponent::GetHwnd()
{
	if (!_hwnd)
	{
		throw runtime_error("Component not created");
	}

	return _hwnd;
}

int Forms::BaseComponent::GetWidth()
{
	return _windowLocalRect.right - _windowLocalRect.left;
}

void Forms::BaseComponent::SetWidth(int width)
{
	_windowLocalRect.right = _windowLocalRect.left + width;
	UpdateWindowSize();
}

int Forms::BaseComponent::GetHeight()
{
	return _windowLocalRect.bottom - _windowLocalRect.top;
}

void Forms::BaseComponent::SetHeight(int height)
{
	_windowLocalRect.bottom = _windowLocalRect.top + height;
	UpdateWindowSize();
}

int Forms::BaseComponent::GetClientWidth()
{
	return _clientRect.right - _clientRect.left;
}

int Forms::BaseComponent::GetClientHeight()
{
	return _clientRect.bottom - _clientRect.top;
}

const wstring& Forms::BaseComponent::GetCaption() const
{
	return _caption;
}

void Forms::BaseComponent::SetCaption(const wstring &caption)
{
	_caption = caption;
	if (_hwnd)
	{
		SetWindowText(_hwnd, _caption.c_str());
	}
}

int Forms::BaseComponent::GetX()
{
	return _windowLocalRect.left;
}

void Forms::BaseComponent::SetX(int x)
{
	int width = GetWidth();
	_windowLocalRect.left = x;
	_windowLocalRect.right = x + width;

	UpdateWindowSize();
}

int Forms::BaseComponent::GetY()
{
	return _windowLocalRect.top;
}

void Forms::BaseComponent::SetY(int y)
{
	int height = GetHeight();
	_windowLocalRect.top = y;
	_windowLocalRect.bottom = y + height;

	UpdateWindowSize();
}

bool Forms::BaseComponent::IsVisible()
{
	return _isVisible;
}

void Forms::BaseComponent::SetVisible(bool visible)
{
	_isVisible = visible;
	if (_isVisible && !_hwnd)
	{
		InitComponent();
	}

	SetVisibleInternal(_isVisible);
}

BaseComponent* Forms::BaseComponent::GetParentComponent()
{
	return _parent;
}

void Forms::BaseComponent::SetParentComponent(BaseComponent *parent)
{
	BaseComponent *oldParent = _parent;
	_parent = parent;

	if (oldParent != nullptr)
	{
		oldParent->RemoveChild(this);
	}

	if (_parent != nullptr)
	{
		_parent->AddChild(this);
	}

	if (!_hwnd)
	{
		InitComponent();
	}
	else
	{
		SetParent(_hwnd, GetParentHwnd());
	}
}

const std::pair<std::vector<BaseComponent*>::const_iterator, std::vector<BaseComponent*>::const_iterator> Forms::BaseComponent::GetChildComponents() const
{
	return std::make_pair(_childComponents.cbegin(), _childComponents.cend());
}

void Forms::BaseComponent::AddChild(BaseComponent *child)
{
	_childComponents.push_back(child);
	if (child->GetParentComponent() != this)
	{
		child->SetParentComponent(this);
	}
}

void Forms::BaseComponent::RemoveChild(BaseComponent *child)
{
	_childComponents.erase(find(_childComponents.begin(), _childComponents.end(), child));
	if (child->GetParentComponent() == this)
	{
		child->SetParentComponent(nullptr);
	}
}

BaseComponent::~BaseComponent()
{
	DestroyComponent();
}

void Forms::BaseComponent::OnClick(std::function<void()> handler)
{
	_onClickHandlers.push_back(handler);
}

void Forms::BaseComponent::InitComponent()
{
	DestroyComponent();
	_hwnd = CreateWindow(GetComponentClassName().c_str(), GetCaption().c_str(), _styles, GetX(), GetY(), GetWidth(), GetHeight(), GetParentHwnd(),
		nullptr, _hInstance, nullptr);

	UpdateRects();

	if (IsVisible() && _hwnd)
	{
		ShowInternal();
	}
}

void Forms::BaseComponent::DestroyComponent()
{
	DestroyChildComponents();
	DestroyWindow(_hwnd);
	_hwnd = nullptr;
}

void Forms::BaseComponent::UpdateWindowStyle()
{
	if (_hwnd)
	{
		SetWindowLongPtr(_hwnd, GWL_STYLE, _styles);
		UpdateWindowSize();
	}
}

HINSTANCE Forms::BaseComponent::GetHinstance()
{
	return _hInstance;
}

HWND Forms::BaseComponent::GetParentHwnd()
{
	return GetParentComponent() != nullptr ? GetParentComponent()->GetHwnd() : HWND_DESKTOP;
}

const wstring& Forms::BaseComponent::GetComponentClassName() const
{
	return _componentClassName;
}

void Forms::BaseComponent::SetComponentClassName(const wstring &componentClassName)
{
	_componentClassName = componentClassName;
}

void Forms::BaseComponent::AppendStyle(int style)
{
	_styles |= style;
	UpdateWindowStyle();
}

void Forms::BaseComponent::DestroyChildComponents()
{
	for (BaseComponent *child : _childComponents)
	{
		delete child;
	}
}

void Forms::BaseComponent::UpdateWindowSize()
{
	if (_hwnd)
	{
		SetWindowPos(_hwnd, (HWND)0, GetX(), GetY(), GetWidth(), GetHeight(), 0);
	}
}

void Forms::BaseComponent::UpdateRects()
{
	if (_hwnd)
	{
		GetClientRect(_hwnd, &_clientRect);
		GetWindowRect(_hwnd, &_windowLocalRect);
		MapWindowPoints(HWND_DESKTOP, GetParentHwnd(), (LPPOINT)&_windowLocalRect, 2);
	}
}

void Forms::BaseComponent::ShowInternal()
{
	SetVisibleInternal(true);
}

void Forms::BaseComponent::HideInternal()
{
	SetVisibleInternal(false);
}

void Forms::BaseComponent::RaiseClickEvent()
{
	for_each(_onClickHandlers.begin(), _onClickHandlers.end(), [](std::function<void()> &handler) { handler(); });
}

void Forms::BaseComponent::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
}

void Forms::BaseComponent::SetVisibleInternal(bool visible)
{
	if (_hwnd)
	{
		ShowWindow(_hwnd, visible ? showFlags : SW_HIDE);
	}
}
