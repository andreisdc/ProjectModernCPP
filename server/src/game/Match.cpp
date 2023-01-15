#include "Match.hpp"

std::vector<Match *> Match::matches;

Match::Match(Lobby *lobby) {
	static int LAST_ID = 0;

	if (lobby->user2 != nullptr) {
		return;
	}

	this->id = LAST_ID;
	LAST_ID++;

	this->player1 = new Player(lobby->creator);
	this->player2 = new Player(lobby->user2);
	this->player_count = 2;
	if (lobby->user3 != nullptr) {
		this->player3 = new Player(lobby->user3);
		this->player_count = 3;
		if (lobby->user4 != nullptr) {
			this->player4 = new Player(lobby->user4);
			this->player_count = 4;
		}
	}

	this->territories = Territory::generate_territories(this->player_count);

	this->phase = MatchPhases::STARTED;

	this->update();
}

Match *Match::find_by_id(int player_id) {
	const auto result = std::ranges::find_if(
			matches.begin(),
			matches.end(),
			[&player_id](Match *lobby) -> bool { return lobby->id == player_id; });

	if (result == matches.end())
		return nullptr;

	return (*result);
}

Player * Match::find_player_by_id(int player_id) {
	if (this->player1->id == player_id) {
		return this->player1;
	} else if (this->player2->id == player_id) {
		return this->player2;
	} else if (this->player3->id == player_id) {
		return this->player3;
	} else if (this->player4->id == player_id) {
		return this->player4;
	}
	return nullptr;
}

void Match::update() {
	this->phase = PRE_BASE_SELECTION;
}

void Match::submit_pre_base_selection_answer(int player_id, int answer_id) {
	if (this->phase != PRE_BASE_SELECTION)
		return;
}

void Match::submit_base_choice(int player_id, int choice_id) {
	if (this->phase != BASE_SELECTION)
		return;
}

void Match::submit_territory_selection_answer(int player_id, int answer_id) {
	if (this->phase != TERRITORY_CONQUEST)
		return;
}

void Match::submit_territory_choice(int player_id, int choice_id) {
	if (this->phase != TERRITORY_CONQUEST)
		return;
}

void Match::submit_duel_choice(int player_id, int choice_id) {
	if (this->phase != DUEL)
		return;
}

void Match::submit_duel_answer(int player_id, int answer_id) {
	if (this->phase != DUEL)
		return;
}
