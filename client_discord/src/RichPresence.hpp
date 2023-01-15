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
	RichPresence(int64_t clientID);
	~RichPresence();

	void setActivityDetails(
	std::string const &details,
	std::string const &state,
	std::string const &largeIcon,
	std::string const &largeText,
	std::string const &smallIcon,
	std::string const &smallText);

private:
	std::unique_ptr<discord::Core> core;
	discord::Activity activity{};
};
