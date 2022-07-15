#pragma once
#include "Theseus.h"
#include "Window.h"

namespace FileMenu
{
	VOID THESEUS_API Open(int x, int y);
	VOID THESEUS_API Close();
	//VOID THESEUS_API AddMessage(CONST WCHAR* message);
}


class THESEUS_API FilePopup :public Win32::Window
{
public:
	FilePopup(int x, int y);
	~FilePopup();
	virtual		VOID				Initialize(int x, int y);

	LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
