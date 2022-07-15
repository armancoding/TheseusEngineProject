#pragma once

namespace Win32
{
	class THESEUS_API SubObject
	{
	public:
		SubObject(WSTRING className, WSTRING classTitle, HICON icon);
		~SubObject();

		virtual VOID RegisterNewClass();
		virtual VOID Initialize() = 0;

	protected:
		static		LRESULT CALLBACK	SetupMessaegeHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static		LRESULT				AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual		LRESULT				MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

	protected:
		WSTRING			m_Class;
		WSTRING			m_Title;
		HICON					m_hIcon;
		HWND					m_Handle;
		BOOL					m_Theme = FALSE;

	public: //Getters
		HWND					GetHandle()				{ return m_Handle; }
		BOOL					GetTheme()				{ return m_Theme; }

	public: //Setters
		VOID					SetHandle(HWND hwnd)	{ m_Handle = hwnd; }
		VOID					SetTheme(BOOL theme)	{ m_Theme = theme; }
	};


}