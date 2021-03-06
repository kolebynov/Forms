// TestForms.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestForms.h"
#include "../Forms/Application.h"
#include "../Forms/Form.h"
#include "../Forms/Button.h"
#include "../Forms/CheckBox.h"
#include "../Forms/RadioButton.h"

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
	Form *form = new Form();
	form->SetText(L"Окно");

	Button *button = new Button();
	button->SetText(L"Кнопка");
	button->SetX(20);
	button->SetY(50);
	button->SetParentComponent(form);
	button->OnClick([]() 
	{ 
		Form *form = new Form();
		form->SetText(L"Test");
		form->Show();
	});

	CheckBox *check = new CheckBox();
	check->SetText(L"sas");
	check->SetType(CheckBoxType::ThreeState);
	form->AddChild(check);
	
	RadioButton *radio = new RadioButton();
	radio->SetText(L"123");
	radio->SetX(100);
	form->AddChild(radio);

	RadioButton *radio2 = new RadioButton();
	radio2->SetText(L"1234");
	radio2->SetX(180);
	form->AddChild(radio2);

	Application::Run(form);
}