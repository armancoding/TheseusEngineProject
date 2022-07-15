#include "Theseus.h"
#include "MainWindow.h"
#include "Platform/WIN32/FileMenu.h"


namespace MainScreen {

	MainWindow* m_MainWindow;

	VOID THESEUS_API Open()
	{
		if (m_MainWindow != nullptr)
			return;
		m_MainWindow = new MainWindow();
	}



	VOID THESEUS_API Close()
	{
		DestroyWindow(m_MainWindow->GetHandle());
		//exit(EXIT_SUCCESS);
	}

	

}

MainWindow::MainWindow()
	:Win32::Window(PerGameSettings::GameName(), NULL)
{
	Win32::Window::RegisterNewClass();
	Win32::Window::Initialize();
}


VOID MainWindow::OnNonClientCreate()
{

	SetTimer(GetHandle(), 1, 100, NULL);
	SetWindowTheme(GetHandle(), L"", L"");

	Win32::Utils::ModifyClassStyle(GetHandle(), 0, CS_DROPSHADOW);

	Win32::Caption::AddCaptionButton(new CaptionButton(L"✕", CB_CLOSE));
	Win32::Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
	Win32::Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));

	Win32::Caption::AddCaptionButtonProp(new CaptionButton(L"File", CB_FILE));
	Win32::Caption::AddCaptionButtonProp(new CaptionButton(L"Edit", CB_EDIT));
	Win32::Caption::AddCaptionButtonProp(new CaptionButton(L"Window", CB_WINDOW));
	Win32::Caption::AddCaptionButtonProp(new CaptionButton(L"Tools", CB_TOOLS));


}


VOID MainWindow::PaintCaption(HDC hdc)
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

	for (auto& button : Caption::CaptionButtonsProp())
	{
		button->Width = 10*wcslen(button->Text.c_str());
		button->Rect = RECT{ spacingprop , 5,spacingprop + button->Width , 25 };
		if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
		{
			HBRUSH brush = CreateSolidBrush(GetTheme() ? LIGHTFRAME : DARKFRAME);
			FillRect(hdc, &button->Rect, brush);
			DeleteObject(brush);
		}
		spacingprop += button->Width;
		DrawText(hdc, button->Text.c_str(), wcslen(button->Text.c_str()), &button->Rect, DT_SINGLELINE | DT_BOTTOM | DT_CENTER);
	}


	//Win32::Utils::AddBitmap(PerGameSettings::IconURL(), hdc, 0, 0);

}

VOID MainWindow::OnNonClientLeftMouseButtonDown()
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
			case CB_CLOSE: {SendMessage(GetHandle(), WM_CLOSE, 0, 0); MainScreen::Close; }		break;
			case CB_MAXIMIZE:	{Win32::Utils::MaximizeWindow(GetHandle()); }		break;
			case CB_MINIMIZE:	{ShowWindow(GetHandle(), SW_MINIMIZE); }			break;
			}

		}
	}
	for (auto& button : Caption::CaptionButtonsProp())
	{
		if (button->Rect.left < pt.x && button->Rect.right > pt.x && button->Rect.top < pt.y && button->Rect.bottom > pt.y)
		{
			switch (button->Command)
			{
			case CB_FILE:	{FileMenu::Open(button->Rect.left + rect.left, button->Rect.bottom + rect.top);}		break;
			case CB_EDIT:	{FileMenu::Close(); }		break;  //debug use only
			case CB_WINDOW:	{ShowWindow(GetHandle(), SW_MINIMIZE); }			break;
			case CB_TOOLS:	{}													break;
			}
		}
	}

}




MainWindow::~MainWindow()
{
}

