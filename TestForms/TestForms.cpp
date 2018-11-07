// TestForms.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestForms.h"
#include "../Forms/Application.h"
#include "../Forms/Form.h"
#include "../Forms/Button.h"

using namespace Forms;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application::Init(hInstance);
	Application::EnableVisualStyles();
	Form *form = new Form(L"Form");
	Button *button = new Button();
	button->SetParentComponent(form);
	button->SetCaption(L"Кнопка");
	button->GetClientWidth();
	button->SetX(20);
	form->SetCaption(L"Окно");
	Application::Run(form);
}