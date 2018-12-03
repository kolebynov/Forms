#include "stdafx.h"
#include "BaseControl.h"

namespace Forms
{
	BaseControl::BaseControl(const std::wstring &componentClassName, std::function<void(void)> beforeInitFunc)
		: BaseComponent(componentClassName, [this, beforeInitFunc]()
	{
		defStyle |= WS_CHILD;

		if (beforeInitFunc != nullptr)
		{
			beforeInitFunc();
		}	
	})
	{
	}
}
