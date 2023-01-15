#pragma once

#include "Lobby.hpp"
#include "Player.hpp"
#include "Question.hpp"
#include "Territory.hpp"

enum MatchPhases {
	INVALID = -1,

	STARTED = 0,

	PRE_BASE_SELECTION = 1,

	BASE_SELECTION = 2,

	/*
	 * Pana la epuizarea teritoriilor.
	 */
	TERRITORY_CONQUEST = 3,

	/*
	 * 2 jucatori = 4 runde
	 * 3 jucatori = 6 runde
	 * 4 jucatori = 8 runde
	 */
	DUEL = 4,

	ENDED = 5,
};

struct Match {
	Match(Lobby *lobby);

	static Match *find_by_id(int player_id);

	Player *find_player_by_id(int player_id);

	void update();

	void submit_pre_base_selection_answer(int player_id, int answer_id);

	void submit_base_choice(int player_id, int choice_id);

	void submit_territory_selection_answer(int player_id, int answer_id);

	void submit_territory_choice(int player_id, int choice_id);

	void submit_duel_choice(int player_id, int choice_id);

	void submit_duel_answer(int player_id, int answer_id);

	int id;

	Player *player1;
	Player *player2;
	Player *player3;
	Player *player4;
	int player_count;

	std::vector<Territory *> territories;

	MatchPhases phase = MatchPhases::INVALID;

	MultipleChoiceQuestion::QuestionManager multiple_choice_question_manager;
	NumericQuestion::QuestionManager numeric_question_manager;

	static std::vector<Match *> matches;
};
