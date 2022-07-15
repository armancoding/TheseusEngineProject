#pragma once

#include "CoreDefinitions.h"
#include "Engine/TEngine.h"
#include "Engine/Simulation.h"

#include "Common/Logger.h"
#include "Common/Time.h"
#include "Core/PerGameSettings.h"

#ifdef WIN32
	#include "Platform/WIN32/Win32Utils.h"
	#include "Platform/WIN32/SubObject.h"
	#include "Platform/WIN32/Window.h"
	#include "Platform/WIN32/w32Caption.h"
	#include "Platform/WIN32/iApplication.h"
#endif	