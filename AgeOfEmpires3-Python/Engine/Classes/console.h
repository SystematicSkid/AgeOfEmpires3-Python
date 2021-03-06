#pragma once
#include "../engine.h"

namespace Engine
{
	class Console
	{
	public:
		static Console*& Instance;
	public:
		#define DEFINE_MEMBER_CLASS Engine::Addresses::Console::Offsets
		union
		{
			DEFINE_MEMBER_B(Engine::SyscallModule*, syscall_module);
		};
		#undef DEFINE_MEMBER_CLASS
	};
	Engine::Console*& Engine::Console::Instance = *(Engine::Console**)(Engine::Addresses::Console::instance);

}