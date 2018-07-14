#pragma once

#ifdef FORMS_EXPORTS
#define FORMS_API __declspec(dllexport)
#else
#define FORMS_API __declspec(dllimport)
#endif