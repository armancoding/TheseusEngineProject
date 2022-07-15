#pragma once

#define DEFAULTWIDTH 800
#define DEFAULTHEIGHT  600


#define DARKBACKGROUND	RGB(36, 30, 30)
#define DARKFOREGROUND	RGB(46, 40, 40)
#define DARKFRAME		RGB(170, 100, 100)
#define DARKTEXT		RGB(240, 255, 255)
#define DARKINACTIVE	RGB(100, 115, 115)


#define LIGHTBACKGROUND RGB(230, 220, 220)
#define LIGHTFOREGROUND RGB(255, 245, 250)
#define LIGHTFRAME		RGB(200, 100, 100)
#define LIGHTTEXT		RGB(55, 30, 30)
#define LIGHTINACTIVE	RGB(130, 100, 100)



namespace Win32 {

	enum WindowType : DWORD
	{
		STATIC			= WS_OVERLAPPED,
		RESIZABLE		= WS_SIZEBOX,
		POPUP			= WS_POPUP,
		NORMAL			= WS_OVERLAPPEDWINDOW
	};

	namespace Utils {
		BOOL THESEUS_API AddBitmap(const WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);
        BOOL THESEUS_API AddIcon(const WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);

        /// Sets and clears style flags for a particular window.
        inline VOID THESEUS_API ModifyWindowStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        /// Sets and clears extended style flags for a particular window.
        inline VOID THESEUS_API ModifyWindowExStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            SetWindowLong(hWnd, GWL_EXSTYLE, (exStyle & ~flagsToDisable) | flagsToEnable);
        }


        inline BOOL THESEUS_API HasStyle(HWND hwnd, DWORD style) {
            DWORD dwStyle = (DWORD)GetWindowLong(hwnd, GWL_STYLE);
            if ((dwStyle & style) != 0) return TRUE;
            return FALSE;
        }


        /// Sets and clears style flags for a particular window.
        inline VOID THESEUS_API ModifyClassStyle(HWND hWnd, DWORD flagsToDisable, DWORD flagsToEnable)
        {
            DWORD style = GetWindowLong(hWnd, GCL_STYLE);
            SetClassLong(hWnd, GCL_STYLE, (style & ~flagsToDisable) | flagsToEnable);
        }

        inline BOOL THESEUS_API IsWindowFullscreen(HWND hWnd)
        {
            WINDOWPLACEMENT placement;
            GetWindowPlacement(hWnd, &placement);

            if (placement.showCmd == SW_MAXIMIZE)
                return TRUE;
            return FALSE;
        }

        inline VOID THESEUS_API MaximizeWindow(HWND hwnd) {
            WINDOWPLACEMENT wPos;
            GetWindowPlacement(hwnd, &wPos);
            if (wPos.showCmd == SW_MAXIMIZE) ShowWindow(hwnd, SW_NORMAL);
            else  ShowWindow(hwnd, SW_MAXIMIZE);
        }
	}
}