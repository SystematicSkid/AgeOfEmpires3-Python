#include <windows.h>
#include <iostream>
#include "./Core/core.h"

HMODULE dll;

VOID Initialize()
{
#ifdef _DEBUG_MODE
	/* Create our debug console */
	FILE* pNewStdout = NULL;
	FILE* pNewStderr = NULL;
	FILE* pNewStdin = NULL;
	AllocConsole();
	SetConsoleTitleA("Age of Empires 3 - DE");
	//// Assign `stdin`, `stout`, `stderr`
	::freopen_s(&pNewStdin, "CONIN$", "r", stdin);
	::freopen_s(&pNewStdout, "CONOUT$", "w", stdout);
	::freopen_s(&pNewStderr, "CONOUT$", "w", stderr); 
#endif

	/* Call the core initialization subroutine */
	Core::Initialize( );

	/* We are done, exit library so we can go for another test! */
	FreeLibraryAndExitThread(dll, 0x1);
}



DWORD WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;
	dll = (HMODULE)hInstance;
	/* Create a thread to handle all of our tasks */
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Initialize, NULL, NULL, NULL);

	return TRUE;
}