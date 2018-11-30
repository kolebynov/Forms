#include "stdafx.h"
#include "Form.h"
#include "Application.h";

using namespace Forms;
using namespace std;

Form::Form(const wstring &name) : BaseComponent(name, [this] { InitForm(); })
{
	_id = Application::GetIdForNewForm();
	Application::AddForm(this);
}

Forms::Form::~Form()
{
	Application::RemoveForm(this);
	BaseComponent::~BaseComponent();
}

int Forms::Form::GetId()
{
	return _id;
}

void Forms::Form::Show()
{
	SetVisible(true);
}

void Forms::Form::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		for_each(_onPaintHandlers.begin(), _onPaintHandlers.end(), [](std::function<void()> &handler) { handler(); });
		break;
	case WM_SIZE:
	case WM_MOVE:
		UpdateRects();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		auto childComponents = GetChildComponents();
		auto result = find_if(childComponents.first, childComponents.second,
			[lParam](BaseComponent *component) { return component->GetHwnd() == (HWND)lParam; });
		(*result)->HandleNativeEvent(hwnd, uMsg, wParam, lParam);
		break;
	}
}

void Forms::Form::OnPaint(std::function<void()> handler)
{
	if (handler != nullptr)
	{
		_onPaintHandlers.push_back(handler);
	}
}

void Forms::Form::InitForm()
{
	WNDCLASS wndClass = {};
	wndClass.hInstance = GetHinstance();
	wndClass.lpszClassName = GetComponentClassName().c_str();
	wndClass.lpfnWndProc = Application::GetWndProc();
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpszMenuName = nullptr;
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClass(&wndClass))
	{

	}

	SetWidth(300);
	SetHeight(200);
	AppendStyle(WS_OVERLAPPEDWINDOW);
	SetCaption(GetComponentClassName());

	showFlags = SW_SHOWNORMAL;
}
