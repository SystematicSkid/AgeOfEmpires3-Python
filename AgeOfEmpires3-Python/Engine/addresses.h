#pragma once

namespace Engine
{
	namespace Addresses
	{

		namespace Syscall
		{
			namespace Offsets
			{
				DWORD64 CONST callback		= 0x0008;
				DWORD64 CONST description	= 0x0010;
			}
		}

		namespace SyscallModule
		{
			namespace Offsets
			{
				DWORD64 CONST syscalls		= 0x0010;
				DWORD64 CONST num_syscalls	= 0x0008 + syscalls;
				DWORD64 CONST max_syscalls	= 0x0004 + num_syscalls;
			}
		}

		namespace Console
		{
			namespace Offsets
			{
				DWORD64 CONST syscall_module = 0x0090;
			}
			DWORD64 CONST instance = Memory::GetInstanceAddress("48 8B 0D ? ? ? ? 41 B9 ? ? ? ? E8 ? ? ? ? 48 8B CB", "AoE3DE.exe");
		}
	}
}