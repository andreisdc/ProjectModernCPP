#pragma once

#include <string>
#include <vector>

#include "Player.hpp"

struct Territory {
	int id;
	std::string name;

	/*
	 * Baza = 300
	 * Cucerit = 100
	 *
	 * In momentul apararii la duel, creste cu 100.
	 * In momentul pierderii la duel, teritoriul decrementeaza cu 100.
	 */
	int score = 0;

	Player *conquered_by = nullptr;

	static std::vector<Territory*> generate_territories(int player_count);
};
