#include "Lobby.hpp"

std::vector<Lobby *> Lobby::lobbies = {};

Lobby::Lobby(User *creator) {
	static int LAST_ID = 0;
	this->id = LAST_ID;
	LAST_ID++;

	this->creator = creator;
}

bool Lobby::add_player(User *user) {
	if (!this->user2) {
		this->user2 = user;
		player_count = 2;
	} else if (!this->user3) {
		this->user3 = user;
		player_count = 3;
	} else if (!this->user4) {
		this->user4 = user;
		player_count = 4;
	} else {
		return false;
	}
	return true;
}

bool Lobby::remove_player(int id) {
	if (this->user2->id == id) {
		this->user2 = this->user3;
		this->user3 = this->user4;
		this->user4 = nullptr;
		player_count = 1;
	} else if (this->user3->id == id) {
		this->user3 = this->user4;
		this->user4 = nullptr;
		player_count = 2;
	} else if (this->user4->id == id) {
		this->user4 = nullptr;
		player_count = 3;
	} else {
		return false;
	}
	return true;
}

bool Lobby::remove_player(User *user) {
	return this->remove_player(user->id);
}

Lobby *Lobby::find_by_id(int id) {
	const auto result = std::ranges::find_if(
			lobbies.begin(),
			lobbies.end(),
			[&id](Lobby *lobby) -> bool { return lobby->id == id; });

	if (result == lobbies.end())
		return nullptr;

	return (*result);
}

bool Lobby::delete_by_id(int id) {
	return delete_by_ptr(find_by_id(id));
}

bool Lobby::delete_by_ptr(Lobby *lobby) {
	lobbies.erase(std::remove(lobbies.begin(), lobbies.end(), lobby), lobbies.end());
	delete lobby;
	return true;
}
