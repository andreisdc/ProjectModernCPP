#pragma once

#ifdef RICHPRESENCE_EXPORTS
#define RICHPRESENCE_API __declspec(dllexport)
#else
#define RICHPRESENCE_API __declspec(dllimport)
#endif

#include <memory>

#include "discord_game_sdk/discord.h"

class RICHPRESENCE_API RichPresence {
public:
	RichPresence(int64_t client_id);
	~RichPresence();

	void set_activity_details(
			const std::string &details,
			const std::string &state,
			const std::string &largeIcon,
			const std::string &largeText,
			const std::string &smallIcon,
			const std::string &smallText,
			int currentSize,
			int maxSize,
			const std::string &partyId);

	void clear_activity();

	void tick();

private:
	std::unique_ptr<discord::Core> core;
	discord::Activity activity{};
};
