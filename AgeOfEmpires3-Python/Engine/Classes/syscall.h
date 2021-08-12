#pragma once
#include "../Engine.h"

namespace Engine
{
	
	class Syscall
	{

	public:
		#define DEFINE_MEMBER_CLASS Engine::Addresses::Syscall::Offsets
		union
		{
			DEFINE_MEMBER(INT, id);
			DEFINE_MEMBER_B(PVOID, callback);
			DEFINE_MEMBER_B(PCHAR, description);
		};
		#undef DEFINE_MEMBER_CLASS
	public:
		std::string GetName()
		{
			std::string desc(description);
			if (memcmp(description, "void", 0x4) == 0 || memcmp(description, "int", 0x3) == 0)
				desc = desc.substr(desc.find_first_of(' ') + 2);

			INT first_non_alpha_idx = -1;
			for (int i = 0; i < desc.length() - 1; i++)
			{
				if (!isalpha(desc.c_str()[i]))
				{
					first_non_alpha_idx = i;
					break;
				}
			}

			return desc.substr(0, first_non_alpha_idx);
		}
	};
	

	class SyscallModule
	{

	public:
		#define DEFINE_MEMBER_CLASS Engine::Addresses::SyscallModule::Offsets
		union
		{
			DEFINE_MEMBER_B(Engine::Syscall**, syscalls);
			DEFINE_MEMBER_B(INT, num_syscalls);
			DEFINE_MEMBER_B(INT, max_syscalls);
		};
		#undef DEFINE_MEMBER_CLASS
	};
}