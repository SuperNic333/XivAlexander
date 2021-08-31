#pragma once

#ifndef XIVALEXANDER_DLLEXPORT

#include <minwindef.h>

#ifdef XIVALEXANDER_DLLEXPORT_SET
#define XIVALEXANDER_DLLEXPORT __declspec(dllexport)
#else
#define XIVALEXANDER_DLLEXPORT __declspec(dllimport)
#endif

namespace XivAlexDll {
	struct InjectEntryPointParameters;

	enum class LoaderAction : int {
		Auto,
		Web,
		Ask,
		Load,
		Unload,
		Launcher,
		UpdateCheck,
		Internal_Update_Step2_ReplaceFiles,
		Internal_Update_Step3_CleanupFiles,
		Internal_Inject_HookEntryPoint,
		Internal_Inject_LoadXivAlexanderImmediately,
		Internal_Cleanup_Handle,
		Count_,  // for internal use only
	};

	XIVALEXANDER_DLLEXPORT const char* LoaderActionToString(LoaderAction val);
	
	XIVALEXANDER_DLLEXPORT DWORD LaunchXivAlexLoaderWithTargetHandles(
		const std::vector<Utils::Win32::Process>& hSources, 
		LoaderAction action, 
		bool wait,
		const std::filesystem::path& launcherPath = L"",
		const Utils::Win32::Process& waitFor = nullptr);
	XIVALEXANDER_DLLEXPORT InjectEntryPointParameters* PatchEntryPointForInjection(HANDLE hProcess);

	//
	// Everything declared below must be able to be called from CreateRemoteProcess.
	//
	
	class InjectOnCreateProcessAppFlags {
	public:
		enum : size_t {
			Use = 1 << 0,
			InjectAll = 1 << 1,
			InjectGameOnly = 1 << 2,
		};
	};
	extern "C" XIVALEXANDER_DLLEXPORT size_t __stdcall EnableInjectOnCreateProcess(size_t flags);

	struct InjectEntryPointParameters {
		void* EntryPoint;
		void* EntryPointOriginalBytes;
		size_t EntryPointOriginalLength;
		void* TrampolineAddress;

		struct {
			HANDLE hContinuableEvent;
			HANDLE hWorkerThread;
			HANDLE hMainThread;
		} Internal;
	};

	extern "C" XIVALEXANDER_DLLEXPORT void __stdcall InjectEntryPoint(InjectEntryPointParameters* pParam);
	extern "C" XIVALEXANDER_DLLEXPORT size_t __stdcall EnableXivAlexander(size_t bEnable);
	extern "C" XIVALEXANDER_DLLEXPORT size_t __stdcall ReloadConfiguration(void* lpReserved);
	extern "C" XIVALEXANDER_DLLEXPORT size_t __stdcall DisableAllApps(void* lpReserved);
	extern "C" XIVALEXANDER_DLLEXPORT void __stdcall CallFreeLibrary(void*);
	extern "C" XIVALEXANDER_DLLEXPORT size_t __stdcall DisableUnloading(const char* pszReason);
	extern "C" XIVALEXANDER_DLLEXPORT const char* __stdcall GetUnloadDisabledReason();
}

#endif
