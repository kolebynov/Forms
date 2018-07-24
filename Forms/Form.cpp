#include "stdafx.h"
#include "Form.h"
#include "Application.h";

using namespace Forms;
using namespace std;

Form::Form(const wstring &name) : BaseComponent(name)
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

	SetCaption(L"ala");
	SetWidth(300);
	SetHeight(200);
	AppendStyle(WS_OVERLAPPEDWINDOW);
}

LRESULT Forms::Form::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

void Forms::Form::InitComponent()
{
	BaseComponent::InitComponent();

	if (GetHwnd())
	{
		Application::AddForm(this);
	}
}

void Forms::Form::DestroyComponent()
{
	Application::RemoveForm(this);
	BaseComponent::DestroyComponent();
}
