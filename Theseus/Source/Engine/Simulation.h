#pragma once
#include "Platform/WIN32/Window.h"
#include "Platform/WIN32/iApplication.h"

namespace Theseus
{
	class THESEUS_API Simulation : public Win32::iApplication, public Win32::Window
	{
	public:
		Simulation();
		~Simulation();
		virtual VOID PreInitialize() override;
		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	private:

	};
}