#pragma once

#include "Macros.h"
#include "BaseComponent.h"

namespace Forms
{
	class FORMS_API Form : public BaseComponent
	{
	public:
		Form(const std::wstring &name);
	};
}