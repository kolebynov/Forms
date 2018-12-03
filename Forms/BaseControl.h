#pragma once
#include "BaseComponent.h"

namespace Forms
{
	class FORMS_API BaseControl : public BaseComponent
	{
	protected:
		BaseControl(const std::wstring &componentClassName, std::function<void(void)> beforeInitFunc);
	};
}

