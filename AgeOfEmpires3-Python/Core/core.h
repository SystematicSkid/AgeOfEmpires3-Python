#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define WIN32_LEAN_AND_MEAN
// win
#include <Windows.h>
#include <winternl.h>
#include <Xinput.h>
#include <d3d11.h>
#include <comdef.h>
#include <minwindef.h>
#include <winbase.h>
#include <intrin.h>
#include <cor.h>
#include <cordebug.h>
#include <metahost.h>
#include <mutex>
#include <cassert>
#include <psapi.h>

// stl
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <sstream>
#include <map>
#include <functional>

// Utility
#include "../Utilities/macros.h"
#include "../Utilities/xorstr.h"
#include "../Utilities/memory.h"

// Engine
#include "../Engine/engine.h"

// Python
#include "./Python/communication.h"

namespace Core
{
	BOOL Initialize( VOID )
	{
		DEBUG("[ + ] Initializing Core...\n");
		//...
		DEBUG("[ + ] Initializing Python...\n");
		if (!Core::Python::Initialize())
		{
			DEBUG("[ ! ] Fatal Error! Failed to initialize Python environment!\n");
			return FALSE;
		}

		return TRUE;
	}
}