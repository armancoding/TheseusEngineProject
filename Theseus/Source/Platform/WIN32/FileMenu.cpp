#include "Theseus.h"
#include "FileMenu.h"

namespace FileMenu
{
	FilePopup* m_FilePopup;

	VOID  Open(int x, int y)
	{
		if (m_FilePopup != nullptr)
			return;
		m_FilePopup = new FilePopup( x, y);
	}

	VOID  Close()
	{
		DestroyWindow(m_FilePopup->GetHandle());
	}

}

FilePopup::FilePopup(int x, int y)
	:Win32::Window(L"File", NULL, Win32::WindowType::POPUP)
{
	Win32::Window::RegisterNewClass();
	Size(150, 200);
	Initialize(x, y);
}

LRESULT FilePopup::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
	//	HBITMAP hbitmap;
		HDC hdc, hmemdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		//Win32::Utils::AddBitmap(PerGameSettings::GameSplashURL(), hdc, 0, 0);
		SetBkMode(hdc, 0);
		SetTextColor(hdc, DARKTEXT);

	}
	}

	return Window::MessageHandler(hWnd, message, wParam, lParam);
}

VOID FilePopup::Initialize(int x, int y)
{
	//POINT pt;
	//pt.x = x;
	//pt.y = y;
	RECT R = { 0, 0, Size().cx, Size().cy };
	
	AdjustWindowRect(&R, m_Type, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_Handle = CreateWindow(m_Class.c_str(), m_Title.c_str(), m_Type,
		x, y, Size().cx, Size().cy, Win32::Window::GetHandle(), 0, HInstance(), (void*)this);


	ShowWindow(m_Handle, SW_SHOW);
	UpdateWindow(m_Handle);
}