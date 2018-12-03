#include "stdafx.h"
#include "CheckBox.h"

namespace Forms
{
	CheckBox::CheckBox() : BaseButton(BS_AUTOCHECKBOX)
	{
		_type = CheckBoxType::TwoState;
	}

	CheckBoxType CheckBox::GetType()
	{
		return _type;
	}

	void CheckBox::SetType(CheckBoxType type)
	{
		_type = type;

		SetInternalStyle(_type == CheckBoxType::TwoState ? BS_AUTOCHECKBOX : BS_AUTO3STATE);
	}
}
