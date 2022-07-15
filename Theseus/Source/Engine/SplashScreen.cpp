#include "Theseus.h"
#include "SplashScreen.h"
#include "Platform/WIN32/Win32Utils.h"

namespace SplashScreen {
#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	VOID Open()
	{
		if (m_SplashWindow != nullptr)
			return;
		m_SplashWindow = new SplashWindow();
	}

	VOID Close()
	{
		DestroyWindow(m_SplashWindow->GetHandle());
	}

	VOID AddMessage(const WCHAR* message)
	{
		PostMessage(m_SplashWindow->GetHandle(), WM_OUTPUTMESSAGE, (WPARAM)message, 0);
	}
}

SplashWindow::SplashWindow()
	: Win32::Window(L"SplashScreen", NULL, Win32::WindowType::POPUP) // 480, 510 
{
	wcscpy_s(m_OutputMessage, L"SplashScreen Starting...");
	Win32::Window::RegisterNewClass();
	Size(480, 510);
	Win32::Window::Initialize();
}

LRESULT SplashWindow::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		HBITMAP hbitmap;
		HDC hdc, hmemdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		Win32::Utils::AddBitmap(PerGameSettings::GameSplashURL(), hdc, 0, 0);
		SetBkMode(hdc, 0);
		SetTextColor(hdc, DARKTEXT);
		if (Engine::GetMode() != Engine::EngineMode::RELEASE)
		{
			std::wstring engineModeText = Engine::EngineModeToString() + L" Mode";
			SetTextAlign(hdc, TA_RIGHT);
			TextOut(hdc, Size().cx - 15, 15, engineModeText.c_str(), wcslen(engineModeText.c_str()));
		}
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, Size().cx / 2, Size().cy - 30, m_OutputMessage, wcslen(m_OutputMessage));
	}
	break;
	case WM_OUTPUTMESSAGE:
	{
		WCHAR* msg = (WCHAR*)wParam;
		wcscpy_s(m_OutputMessage, msg);
		RedrawWindow();
		return 0;
	}
	}

	return Window::MessageHandler(hWnd, message, wParam, lParam);
}

SplashWindow::~SplashWindow()
{
}


