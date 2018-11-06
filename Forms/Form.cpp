#include "stdafx.h"
#include "Form.h"
#include "Application.h";

using namespace Forms;
using namespace std;

Form::Form(const wstring &name) : BaseComponent(L"Form")
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
	SetCaption(name);

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

LRESULT Forms::Form::HandleNativeEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
	case WM_MOVE:
		UpdateRects();
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}