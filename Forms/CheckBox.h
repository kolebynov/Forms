#pragma once
#include "BaseButton.h"

namespace Forms
{
	enum class CheckBoxType;

	class FORMS_API CheckBox : public BaseButton
	{
	public:
		CheckBox();

		CheckBoxType GetType();
		void SetType(CheckBoxType type);

	private:
		CheckBoxType _type;
	};

	enum class CheckBoxType
	{
		TwoState,
		ThreeState
	};
}