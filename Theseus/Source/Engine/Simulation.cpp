#include "Theseus.h"
#include "Simulation.h"
#include "SplashScreen.h"
#include "MainWindow.h"

Theseus::Simulation::Simulation()
	: Win32::Window(L"Theseus Engine", NULL)
{

}

VOID Theseus::Simulation::PreInitialize()
{
	Logger::PrintDebugSeparator();
	Logger::PrintLog(L"Application Starting...\n");
	Logger::PrintLog(L"Game Name: %s\n", PerGameSettings::GameName());
	Logger::PrintLog(L"Boot Time: % s\n", Time::GetDateTimeString().c_str());
	Logger::PrintLog(L"Engine Mode: % s\n", Engine::EngineModeToString().c_str());
	Logger::PrintDebugSeparator();
	SplashScreen::Open();

	
	Sleep(3000); 	 //debug line
	SplashScreen::Close();

	//Win32::Window::SetTheme(TRUE); //debug line

	//Win32::Window::RegisterNewClass();
	//Win32::Window::Initialize();

	MainScreen::Open();
}

LRESULT Theseus::Simulation::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	}

	return Window::MessageHandler(hWnd, message, wParam, lParam);
}

Theseus::Simulation::~Simulation()
{
}

