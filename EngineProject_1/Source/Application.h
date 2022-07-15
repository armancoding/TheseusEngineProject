#pragma once
#include "Engine/Simulation.h"

class Application :public Theseus::Simulation
{
public:
	Application();
	~Application();

	VOID SetupPerGameSettings() override;


	VOID Initialize() override;

	VOID Update() override;
	
};