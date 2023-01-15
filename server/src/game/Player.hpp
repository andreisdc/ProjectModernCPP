#pragma once

#include <string>

#include "User.hpp"

struct Player {
	Player(User *user)
		: id(user->id), username(user->username) {}

	int id;
	std::string username;
	int score = 0;
};
