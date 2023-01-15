#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>

#include "discord_game_sdk/discord.h"

#include "RichPresence.hpp"

RichPresence::RichPresence(int64_t client_id) {
	discord::Core *core{};
	auto result = discord::Core::Create(client_id, DiscordCreateFlags_Default, &core);

	this->core.reset(core);

	if (!this->core) {
		std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result) << ")\n";
		std::exit(-1);
	}

	this->core->SetLogHook(
			discord::LogLevel::Debug, [](discord::LogLevel level, const char *message) {
				std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
			});

	this->activity = discord::Activity{};
}

RichPresence::~RichPresence() {}

void RichPresence::set_activity_details(const std::string &details, const std::string &state, const std::string &largeIcon, const std::string &largeText, const std::string &smallIcon, const std::string &smallText, int currentSize, int maxSize, const std::string &partyId) {
	this->activity.SetDetails(details.c_str());
	this->activity.SetState(state.c_str());
	this->activity.GetAssets().SetLargeImage(largeIcon.c_str());
	this->activity.GetAssets().SetLargeText(largeText.c_str());
	this->activity.GetAssets().SetSmallImage(smallIcon.c_str());
	this->activity.GetAssets().SetSmallText(smallText.c_str());
	this->activity.GetParty().GetSize().SetCurrentSize(currentSize);
	this->activity.GetParty().GetSize().SetMaxSize(maxSize);
	this->activity.GetParty().SetId(partyId.c_str());
	this->activity.GetParty().SetPrivacy(discord::ActivityPartyPrivacy::Public);
	this->activity.SetType(discord::ActivityType::Playing);
	this->core->ActivityManager().UpdateActivity(this->activity, [](discord::Result result) {
		std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
	});
}

void RichPresence::clear_activity() {
	this->core->ActivityManager().ClearActivity([](discord::Result result) {
		if (result != discord::Result::Ok && result != discord::Result::TransactionAborted) {
			std::cout << "Failed clearing activity!\n";
		}
	});
}

void RichPresence::tick() {
	this->core->RunCallbacks();
}
