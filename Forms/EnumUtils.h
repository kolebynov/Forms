#pragma once
#include "stdafx.h"

namespace Forms
{
	template <class T>
	inline T operator| (T a, T b)
	{
		return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
	}

	template <class T>
	inline T operator& (T a, T b)
	{
		return static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
	}

	template <class T>
	inline T operator^ (T a, T b)
	{
		return static_cast<T>(static_cast<int>(a) ^ static_cast<int>(b));
	}
}