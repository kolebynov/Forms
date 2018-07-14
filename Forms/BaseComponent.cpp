#include "stdafx.h"
#include "BaseComponent.h"
#include "Application.h"

using namespace Forms;
using namespace std;

HWND Forms::BaseComponent::GetHwnd()
{
	return _hwnd;
}

int Forms::BaseComponent::GetWidth()
{
	return _width;
}

void Forms::BaseComponent::SetWidth(int width)
{
	_width = width;
}

int Forms::BaseComponent::GetHeight()
{
	return _height;
}

void Forms::BaseComponent::SetHeight(int height)
{
	_height = height;
}

const wstring& Forms::BaseComponent::GetCaption() const
{
	return _caption;
}

void Forms::BaseComponent::SetCaption(const wstring &caption)
{
	_caption = caption;
	if (GetHwnd())
	{
		SetWindowText(GetHwnd(), _caption.c_str());
	}
}

int Forms::BaseComponent::GetX()
{
	return _x;
}

void Forms::BaseComponent::SetX(int x)
{
	_x = x;
}

int Forms::BaseComponent::GetY()
{
	return _y;
}

void Forms::BaseComponent::SetY(int y)
{
	_y = y;
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

		if (_parent->GetHwnd())
		{
			Show();
		}
	}
}

void Forms::BaseComponent::Show()
{
	InitComponentAndDoAction([this] { ShowWindow(GetHwnd(), SW_SHOWNORMAL); ShowChildComponents(); });
}

LRESULT Forms::BaseComponent::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void Forms::BaseComponent::AddChild(BaseComponent *child)
{
	_childComponents.insert(child);
	if (child->GetParentComponent() != this)
	{
		child->SetParentComponent(this);
	}
}

void Forms::BaseComponent::RemoveChild(BaseComponent *child)
{
	_childComponents.erase(child);
	if (child->GetParentComponent() == this)
	{
		child->SetParentComponent(nullptr);
	}
}

BaseComponent::BaseComponent() : BaseComponent(L"")
{
	
}

Forms::BaseComponent::BaseComponent(const std::wstring &componentClassName)
{
	_hInstance = Application::GetHinstance();
	_hwnd = nullptr;
	_parent = nullptr;
	_childComponents = unordered_set<BaseComponent*>();
	_styles = 0;

	SetWidth(0);
	SetHeight(0);
	SetX(0);
	SetY(0);
	SetCaption(L"");
	SetComponentClassName(componentClassName);	
}

BaseComponent::~BaseComponent()
{
	DestroyComponent();
}

void Forms::BaseComponent::InitComponent()
{
	DestroyComponent();
	_hwnd = CreateWindow(GetComponentClassName().c_str(), GetCaption().c_str(), _styles, GetX(), GetY(), GetWidth(), GetHeight(), GetParentComponent() != nullptr ? GetParentComponent()->GetHwnd() : HWND_DESKTOP, 
		nullptr, _hInstance, nullptr);

	if (_hwnd)
	{
		Application::AddComponent(this);
	}
}

void Forms::BaseComponent::DestroyComponent()
{
	if (GetHwnd())
	{
		DestroyChildComponents();
		Application::RemoveComponent(this);
		DestroyWindow(GetHwnd());
		_hwnd = nullptr;
	}
}

HINSTANCE Forms::BaseComponent::GetHinstance()
{
	return _hInstance;
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
}

void Forms::BaseComponent::InitComponentOrDoAction(std::function<void(void)> action)
{
	if (GetHwnd())
	{
		action();
	}
	else
	{
		InitComponent();
	}
}

void Forms::BaseComponent::InitComponentAndDoAction(std::function<void(void)> action)
{
	if (!GetHwnd())
	{
		InitComponent();
	}

	action();
}

void Forms::BaseComponent::ShowChildComponents()
{
	for (BaseComponent *child : _childComponents)
	{
		child->Show();
	}
}

void Forms::BaseComponent::DestroyChildComponents()
{
	for (BaseComponent *child : _childComponents)
	{
		delete child;
	}
}