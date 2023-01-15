#pragma once

#include <string>
#include <array>
#include <vector>

#include <nlohmann/json_fwd.hpp>

struct MultipleChoiceQuestion {
	int id;
	std::string question;
	std::array<std::string, 4> possible_answers;
	std::string correct_answer;

	struct QuestionManager {
		QuestionManager();

		MultipleChoiceQuestion *get_random();

	private:
		void shuffle();

		std::size_t last_index = 0;
		std::vector<MultipleChoiceQuestion *> shuffled_questions;
	};

	static void load(nlohmann::json j);

	static std::vector<MultipleChoiceQuestion *> questions;
};

struct NumericQuestion {
	int id;
	std::string question;
	int answer;

	struct QuestionManager {
		QuestionManager();

		NumericQuestion *get_random();

	private:
		void shuffle();

		std::size_t last_index = 0;
		std::vector<NumericQuestion *> shuffled_questions;
	};

	static void load(nlohmann::json j);

	static std::vector<NumericQuestion *> questions;
};
