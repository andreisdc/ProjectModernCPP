#include <Windows.h>

#include "discord_game_sdk/discord.h"

#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>

struct DiscordState {
	discord::User currentUser;

	std::unique_ptr<discord::Core> core;
};

namespace {
	volatile bool interrupted{false};
}

void Init() {
	DiscordState state{};

	discord::Core *core{};
	auto result = discord::Core::Create(310270644849737729, DiscordCreateFlags_Default, &core);
	state.core.reset(core);
	if (!state.core) {
		std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result)
				  << ")\n";
		std::exit(-1);
	}

	state.core->SetLogHook(
			discord::LogLevel::Debug, [](discord::LogLevel level, const char *message) {
				std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
			});

	core->UserManager().OnCurrentUserUpdate.Connect([&state]() {
		state.core->UserManager().GetCurrentUser(&state.currentUser);

		std::cout << "Current user updated: " << state.currentUser.GetUsername() << "#"
				  << state.currentUser.GetDiscriminator() << "\n";
	});

	std::signal(SIGINT, [](int) { interrupted = true; });

	do {
		state.core->RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (!interrupted);
}

void Restore() {
	
}

DWORD APIENTRY InitDllHandling(HINSTANCE hModuleInstance) {
	Init();
	return TRUE;
}

DWORD APIENTRY ShutdownDllHandling(HINSTANCE hModuleInstance) {
	Restore();
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE) InitDllHandling, nullptr, NULL, nullptr);
	} else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		(LPTHREAD_START_ROUTINE) ShutdownDllHandling;
	}

	return TRUE;
}
