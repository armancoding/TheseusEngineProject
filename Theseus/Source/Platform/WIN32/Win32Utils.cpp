#include "Theseus.h"
#include "Win32Utils.h"
#include <Gdiplus.h>

BOOL  Win32::Utils::AddBitmap(const WCHAR* szFileName, HDC hWinDC, INT x, INT y)
{
	HBITMAP hBitMap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitMap == NULL)
	{
		MessageBox(NULL, L"LoadImage Failed", L"Error", MB_OK);
		return false;
	}

	HDC hLocalDC = CreateCompatibleDC(hWinDC);
	if (hLocalDC == NULL)
	{
		MessageBox(NULL, L"CreateCompatibleDC Failed", L"Error", MB_OK);
		return false;
	}

	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitMap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn)
	{
		MessageBox(NULL, L"GetObject Failed", L"Error", MB_OK);
		return false;
	}

	::SelectObject(hLocalDC, hBitMap);

	BOOL qRetBlit = ::BitBlt(hWinDC, x, y, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit)
	{
		MessageBox(NULL, L"Blit Failed", L"Error", MB_OK);
		return false;
	}

	::SelectObject(hLocalDC, hBitMap);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitMap);
	return true;
}


