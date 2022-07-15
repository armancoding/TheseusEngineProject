#include "Theseus.h"
//#include <winrt/Windows.UI.ViewManagement.h>
#include "Window.h" 
#include "Core/PerGameSettings.h"


#define DCX_USESTYLE 0x00010000

namespace Win32 {

	Window::Window( std::wstring Title, HICON icon, WindowType type)
		: Win32::SubObject(Title, Title, icon), m_Size(SIZE{ DEFAULTWIDTH, DEFAULTHEIGHT }), m_Type(type)
	{

	}



	VOID Window::Initialize()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, Size().cx, Size().cy};
		AdjustWindowRect(&R, m_Type, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		m_Handle = CreateWindow(m_Class.c_str(), m_Title.c_str(), m_Type,
			((desktop.right / 2)-(Size().cx / 2)), ((desktop.bottom / 2) - (Size().cy / 2)), Size().cx, Size().cy, 0, 0, HInstance(), (void*)this);
		
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}
	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_NCCREATE:		{	OnNonClientCreate();				  }			return TRUE;
		case WM_NCACTIVATE:		{	Active(LOWORD(wParam) != WA_INACTIVE);}						return TRUE;
		case WM_NCPAINT:		{	OnNonClientPaint((HRGN)wParam, hWnd); }						return FALSE;
		case WM_NCLBUTTONDOWN:	{	OnNonClientLeftMouseButtonDown(); }							break;
		case WM_GETMINMAXINFO:	{	OnGetMinMaxInfo(((MINMAXINFO*)lParam)); }					return 0;
		case WM_PAINT:			{	OnPaint(); }												break;
		case WM_TIMER:			{	RedrawWindow();	}											break;
		}

		return SubObject::MessageHandler(hWnd, message, wParam, lParam);
	}

	VOID Window::OnNonClientCreate()
	{

		SetTimer(GetHandle(), 1, 100, NULL);
		SetWindowTheme(GetHandle(), L"", L"");


		Win32::Utils::ModifyClassStyle(GetHandle(), 0, CS_DROPSHADOW);

		Win32::Caption::AddCaptionButton(new CaptionButton(L"✕", CB_CLOSE)); 
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
		Win32::Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));
	}

	VOID Window::OnNonClientPaint(HRGN region, HWND hWnd)
	{
		//Start Draw
		HDC hdc = GetDCEx(GetHandle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USESTYLE);
		HWND hwnd = hWnd;
		RECT rect;
		GetWindowRect(GetHandle(), &rect);


		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };

		HBITMAP	hbmMem = CreateCompatibleBitmap(hdc, size.cx, size.cy);
		HANDLE hOld = SelectObject(hdc, hbmMem);

		//Draw
		HBRUSH brush = CreateSolidBrush(GetTheme() ? LIGHTFOREGROUND : DARKFOREGROUND);
		HBRUSH framebrush = CreateSolidBrush(GetTheme() ? LIGHTFRAME : DARKFRAME);
		RECT newRect = RECT{ 0, 0, size.cx, size.cy };
		FillRect(hdc, &newRect, brush);
		if (Active() && !Win32::Utils::IsWindowFullscreen(GetHandle())) 
		{
			FrameRect(hdc, &newRect, framebrush);
		}
		
		PaintCaption(hdc);

		DeleteObject(brush);
		DeleteObject(framebrush);
		//End Draw 


		BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);
		ReleaseDC(GetHandle(), hdc);
	}

	VOID Window::RedrawWindow()
	{
		SetWindowPos(GetHandle(), 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED); //reset window
		SendMessage(GetHandle(), WM_PAINT, 0, 0);
	}

	VOID Window::PaintCaption(HDC hdc)
	{
		RECT rect;
		GetWindowRect(GetHandle(), &rect);
		SIZE size = SIZE{ rect.right - rect.left, rect.bottom - rect.top };


		if (ShowTitle())
		{
			rect = RECT{ 0, 0, size.cx, 30 };
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, Active() ? (GetTheme() ? LIGHTTEXT : DARKTEXT) : (GetTheme() ? LIGHTINACTIVE : DARKINACTIVE));
			DrawText(hdc, m_Title.c_str(), wcslen(m_Title.c_str()), &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}

		int spacing = 0;
		int spacingprop = 70;

		POINT pt;
		GetCursorPos(&pt);

		GetWindowRect(GetHandle(), &rect);
		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto& button : Caption::CaptionButtons())
		{
			spacing += button->Width;
			button->Rect = RECT{ size.cx - spacing , 0,size.cx - spacing + button->Width , 30 };
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				HBRUSH brush = CreateSolidBrush(GetTheme() ? LIGHTFRAME : DARKFRAME);
				FillRect(hdc, &button->Rect, brush);
				DeleteObject(brush);
			}


			if (button->Text.compare(L"🗖") == 0 && Win32::Utils::IsWindowFullscreen(GetHandle()))
			{
				button->Text = L"🗗";
			}
			else if (button->Text.compare(L"🗗") == 0 && !Win32::Utils::IsWindowFullscreen(GetHandle()))
			{
				button->Text = L"🗖";
			}

			DrawText(hdc, button->Text.c_str(), wcslen(button->Text.c_str()), &button->Rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		}

	}

	VOID Window::OnNonClientLeftMouseButtonDown()
	{
		POINT pt;
		RECT rect;

		GetCursorPos(&pt);
		GetWindowRect(GetHandle(), &rect);
		pt.x -= rect.left;
		pt.y -= rect.top;

		for (auto& button : Caption::CaptionButtons())
		{
			if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
			{
				switch (button->Command) 
				{
				case CB_CLOSE:			{SendMessage(GetHandle(), WM_CLOSE, 0, 0); }		break;
				case CB_MAXIMIZE:		{Win32::Utils::MaximizeWindow(GetHandle()); }		break;
				case CB_MINIMIZE:		{ShowWindow(GetHandle(), SW_MINIMIZE); }			break;
				}
			}
		}
	}

	VOID Window::OnGetMinMaxInfo(MINMAXINFO* minmax)
	{
		RECT WorkArea; SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
		minmax->ptMaxSize.x = (WorkArea.right - WorkArea.left);
		minmax->ptMaxSize.y = (WorkArea.bottom - WorkArea.top);
		minmax->ptMaxPosition.x = WorkArea.left;
		minmax->ptMaxPosition.y = WorkArea.top;
		minmax->ptMinTrackSize.x = 500;
		minmax->ptMinTrackSize.y = 300;
	}

	VOID Window::OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(GetHandle(), &ps);
		RECT rc;
		GetClientRect(GetHandle(), &rc);
		HBRUSH brush = CreateSolidBrush(GetTheme() ? LIGHTBACKGROUND : DARKBACKGROUND);
		FillRect(hdc, &rc, brush);
		DeleteObject(brush);
		EndPaint(GetHandle(), &ps);


	}
	//IDockProvider::SetDockPosition()

	Window::~Window()
	{
	}
}
 

