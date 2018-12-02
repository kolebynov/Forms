// TestForms.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestForms.h"
#include "../Forms/Application.h"
#include "../Forms/Form.h"
#include "../Forms/Button.h"
#include "../Forms/CheckBox.h"

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
	form->SetCaption(L"Окно");

	Button *button = new Button();
	button->SetCaption(L"Кнопка");
	button->SetX(20);
	button->SetY(50);
	button->SetParentComponent(form);
	button->OnClick([]() 
	{ 
		Form *form = new Form(L"Test");
		form->Show();
	});

	CheckBox *check = new CheckBox();
	check->SetCaption(L"sas");
	form->AddChild(check);
	
	Application::Run(form);
}