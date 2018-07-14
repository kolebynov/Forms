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
		static void AddComponent(BaseComponent *component);
		static void RemoveComponent(BaseComponent *component);
		static void EnableVisualStyles();

	private:
		Application();

		static HINSTANCE _hInstance;
		static std::unordered_map<HWND, BaseComponent*> _components;

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}