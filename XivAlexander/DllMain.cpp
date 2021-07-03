#include "pch.h"
#include "XivAlexander/XivAlexander.h"

HINSTANCE g_hInstance;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved) {
	g_hInstance = hInstance;
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			MH_Initialize();
			break;

		case DLL_PROCESS_DETACH:
			MH_Uninitialize();
			break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) int __stdcall XivAlexDll::DisableAllApps(void*) {
	EnableXivAlexander(0);
	EnableInjectOnCreateProcess(0);
	return 0;
}

extern "C" __declspec(dllexport) int __stdcall XivAlexDll::CallFreeLibrary(void*) {
	FreeLibraryAndExitThread(g_hInstance, 0);
}
