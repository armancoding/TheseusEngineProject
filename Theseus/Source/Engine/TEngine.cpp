#include "Theseus.h"

namespace Engine 
{
	TEngine g_TheseusEngine;

	VOID  SetMode(EngineMode mode)
	{
		g_TheseusEngine.SetEngineMode(mode);
	}

	EngineMode  GetMode()
	{
		return g_TheseusEngine.GetEngineMode();
	}

	std::wstring THESEUS_API EngineModeToString()
	{
		switch (Engine::GetMode())
		{
		case EngineMode::DEBUG:		return L"Debug";
		case EngineMode::RELEASE:	return L"Release";
		case EngineMode::SERVER:	return L"Server";
		case EngineMode::EDITOR:	return L"Editor";
		default:					return L"None";
		}
	}
}




TEngine::TEngine()
{
#ifdef _DEBUG
	m_EngineMode = Engine::EngineMode::DEBUG;
#else
	m_EngineMode = Engine::EngineMode::RELEASE;
#endif
}

TEngine::~TEngine()
{
}

Engine::EngineMode TEngine::GetEngineMode()
{
	return m_EngineMode;
}

VOID TEngine::SetEngineMode(Engine::EngineMode mode)
{
	m_EngineMode = mode;
}
