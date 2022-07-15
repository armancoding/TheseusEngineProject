#pragma once
#include "Platform/WIN32/Window.h"
namespace SplashScreen {
	VOID THESEUS_API Open();
	VOID THESEUS_API Close();
	VOID THESEUS_API AddMessage(CONST WCHAR* message);
}

class THESEUS_API SplashWindow :public Win32::Window
{
public:
	SplashWindow();
	~SplashWindow();

	LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
public:
	WCHAR m_OutputMessage[MAX_NAME_STRING];
};