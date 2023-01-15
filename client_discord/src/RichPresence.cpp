#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>

#include "discord_game_sdk/discord.h"

#include "RichPresence.hpp"

struct DiscordState {
	std::unique_ptr<discord::Core> core;
	discord::Activity activity{};
};

namespace {
	volatile bool interrupted{false};
}

void Init() {
	DiscordState state{};

	discord::Core *core{};
	auto result = discord::Core::Create(1063927540323979334, DiscordCreateFlags_Default, &core);
	state.core.reset(core);
	if (!state.core) {
		std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result) << ")\n";
		std::exit(-1);
	}

	state.core->SetLogHook(
			discord::LogLevel::Debug, [](discord::LogLevel level, const char *message) {
				std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
			});
			
	state.activity.SetDetails("Normal Match");
	state.activity.SetState("In Lobby");
	state.activity.GetAssets().SetLargeImage("harta");
	state.activity.GetAssets().SetLargeText("Romania");
	state.activity.GetParty().GetSize().SetCurrentSize(1);
	state.activity.GetParty().GetSize().SetMaxSize(4);
	state.activity.GetParty().SetId("party id");
	state.activity.GetParty().SetPrivacy(discord::ActivityPartyPrivacy::Public);
	state.activity.SetType(discord::ActivityType::Playing);
	state.core->ActivityManager().UpdateActivity(state.activity, [](discord::Result result) {
		std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
	});

	std::signal(SIGINT, [](int) -> void { interrupted = true; });

	do {
		state.core->RunCallbacks();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (!interrupted);
}
