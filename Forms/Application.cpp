#include "stdafx.h"
#include "Application.h"

using namespace Forms;
using namespace std;

HINSTANCE Application::_hInstance = nullptr;
unordered_map<int, Form*> Application::_forms = unordered_map<int, Form*>();
int Application::_nextFormId = 0;

void Application::Run(Form *mainForm)
{
	mainForm->Show();

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

WNDPROC Application::GetWndProc()
{
	return Application::WndProc;
}

void Forms::Application::Init(HINSTANCE hInstance)
{
	Application::_hInstance = hInstance;
}

HINSTANCE Forms::Application::GetHinstance()
{
	return Application::_hInstance;
}

void Forms::Application::AddForm(Form *form)
{
	_forms[form->GetId()] = form;
}

void Forms::Application::RemoveForm(Form *form)
{
	_forms.erase(form->GetId());
}

void Forms::Application::EnableVisualStyles()
{
	TCHAR dir[MAX_PATH];
	ULONG_PTR ulpActivationCookie = FALSE;

	UINT cch = GetSystemDirectory(dir, sizeof(dir) / sizeof(*dir));
	if (cch >= sizeof(dir) / sizeof(*dir))
	{
	}

	std::wstring dllPath = std::wstring(dir) + L"\\shell32.dll";
	ACTCTX actCtx = {};
	actCtx.cbSize = sizeof(actCtx);
	actCtx.lpSource = dllPath.c_str();
	actCtx.lpResourceName = (LPCWSTR)124;
	actCtx.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID;
	ActivateActCtx(CreateActCtx(&actCtx), &ulpActivationCookie);
}

int Forms::Application::GetIdForNewForm()
{
	return _nextFormId++;
}

Application::Application()
{
}

LRESULT Application::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto findResult = std::find_if(_forms.begin(), _forms.end(), [hwnd](const std::pair<int, Form*> &pair) { return pair.second->GetHwnd() == hwnd; });
	if (findResult != _forms.end())
	{
		Form *form = findResult->second;
		if (form != nullptr)
		{
			return form->HandleNativeEvent(hwnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}