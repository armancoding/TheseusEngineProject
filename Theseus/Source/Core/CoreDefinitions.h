#pragma once 

#ifdef BUILD_DLL
	#define THESEUS_API __declspec(dllexport)
#else
	#define THESEUS_API __declspec(dllimport)
#endif

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

typedef std::wstring WSTRING;
typedef std::string STRING;
