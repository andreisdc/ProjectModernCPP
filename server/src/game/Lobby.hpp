#pragma once

#include <optional>
#include <vector>

#include "User.hpp"

struct Lobby {
	Lobby(User *creator);

	int get_id() const {
		return this->id;
	}

	User *get_creator() const {
		return this->creator;
	}

	bool add_player(User *user);

	bool remove_player(int id);

	bool remove_player(User *user);

	static Lobby *find_by_id(int id);

	static bool delete_by_id(int id);

	static bool delete_by_ptr(Lobby *lobby);

	int id;
	User *creator;
	User *user2 = nullptr;
	User *user3 = nullptr;
	User *user4 = nullptr;
	int player_count = 1;

	static std::vector<Lobby *> lobbies;
};
