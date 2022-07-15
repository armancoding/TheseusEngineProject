#pragma once


class THESEUS_API TEngine;
namespace Engine
{
	enum EngineMode : INT
	{
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};
	extern TEngine g_TheseusEngine;

	VOID THESEUS_API SetMode(EngineMode mode);
	EngineMode THESEUS_API GetMode();

	WSTRING THESEUS_API EngineModeToString();

}

class THESEUS_API TEngine
{
public:
	TEngine();
	~TEngine();
private:
	Engine::EngineMode m_EngineMode;
public:
	Engine::EngineMode GetEngineMode();
	VOID SetEngineMode(Engine::EngineMode mode);
};