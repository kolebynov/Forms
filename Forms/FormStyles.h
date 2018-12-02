#pragma once
#include "stdafx.h"

namespace Forms
{
	enum class FormStyles
	{
		Overlapped = WS_OVERLAPPED,
		Border = WS_BORDER,
		MaximizeBox = WS_MAXIMIZEBOX,
		MinimizeBox = WS_MINIMIZEBOX,
		Caption = WS_CAPTION,
		Sizebox = WS_THICKFRAME,
		SysMenu = WS_SYSMENU
	};
}