#pragma once

#include "Macros.h"
#include "Form.h"
#include <unordered_map>

namespace Forms
{
	class FORMS_API Application
	{
	public:
		static void Run(Form *mainForm);
		static WNDPROC GetWndProc();
		static void Init(HINSTANCE hInstance);
		static HINSTANCE GetHinstance();
		static void AddForm(Form *form);
		static void RemoveForm(Form *form);
		static void EnableVisualStyles();
		static int GetIdForNewForm();

	private:
		Application();

		static HINSTANCE _hInstance;
		static std::unordered_map<int, Form*> _forms;
		static int _nextFormId;

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}