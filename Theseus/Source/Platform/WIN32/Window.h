#pragma once
#include "SubObject.h"
#include "Win32Utils.h"
#include "w32Caption.h"
#include "Uxtheme.h"
#pragma comment(lib, "uxtheme.lib")

//WSTRING Text = L"🗕";


namespace Win32
{
	class THESEUS_API Window : public Win32::SubObject, public Win32::Caption
	{
	public:
		Window(WSTRING Title, HICON icon, WindowType type = NORMAL);
		~Window();

		virtual		VOID				Initialize() override;

		virtual		LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

		virtual		VOID				OnNonClientPaint(HRGN region, HWND hWnd);
		virtual		VOID				OnNonClientCreate();
		virtual		VOID				RedrawWindow();
		virtual		VOID				PaintCaption(HDC hdc);
		virtual		VOID				OnNonClientLeftMouseButtonDown();
		virtual		VOID				OnGetMinMaxInfo(MINMAXINFO* minmax);
		virtual		VOID				OnPaint();



	protected:
		SIZE				m_Size;
		WindowType			m_Type;
		BOOL				m_IsActive;
	

	public:
		SIZE				Size() { return m_Size; }
		BOOL				Active() { return m_IsActive; }

	public:
		VOID				Size(SIZE size) { m_Size = size; }
		VOID				Size(INT cx, INT cy) { m_Size.cx = cx; m_Size.cy = cy; }
		VOID				Active(BOOL active) { m_IsActive = active; }
	};

}
