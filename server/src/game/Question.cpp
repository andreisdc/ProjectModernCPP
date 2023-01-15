#include <algorithm>
#include <random>

#include <nlohmann/json.hpp>

#include "Question.hpp"

std::vector<MultipleChoiceQuestion *> MultipleChoiceQuestion::questions;

MultipleChoiceQuestion::QuestionManager::QuestionManager() {
	this->shuffled_questions = MultipleChoiceQuestion::questions;
	this->shuffle();
}

MultipleChoiceQuestion *MultipleChoiceQuestion::QuestionManager::get_random() {
	auto q = this->shuffled_questions.at(last_index);

	this->last_index++;
	if (this->last_index > this->shuffled_questions.size() - 1) {
		this->last_index = 0;
		this->shuffle();
	}

	return q;
}

void MultipleChoiceQuestion::QuestionManager::shuffle() {
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::ranges::shuffle(this->shuffled_questions, gen);
}

void MultipleChoiceQuestion::load(nlohmann::json j) {
	int i = 0;
	for (auto &item: j.items()) {
		auto q = new MultipleChoiceQuestion;
		q->id = i;

		q->question = item.value().at("intrebare").get<std::string>();

		nlohmann::basic_json answers = item.value().at("raspunsuri");
		q->correct_answer = answers.at(0).get<std::string>();
		q->possible_answers = std::array<std::string, 4>({
				answers.at(0).get<std::string>(),
				answers.at(1).get<std::string>(),
				answers.at(2).get<std::string>(),
				answers.at(3).get<std::string>(),
		});

		questions.push_back(q);
		i++;
	}
}

std::vector<NumericQuestion *> NumericQuestion::questions;

NumericQuestion::QuestionManager::QuestionManager() {
	this->shuffled_questions = NumericQuestion::questions;
	this->shuffle();
}

NumericQuestion *NumericQuestion::QuestionManager::get_random() {
	auto q = this->shuffled_questions.at(last_index);

	this->last_index++;
	if (this->last_index > this->shuffled_questions.size() - 1) {
		this->last_index = 0;
		this->shuffle();
	}

	return q;
}

void NumericQuestion::QuestionManager::shuffle() {
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::ranges::shuffle(this->shuffled_questions, gen);
}

void NumericQuestion::load(nlohmann::json j) {
	int i = 0;
	for (auto &item: j.items()) {
		auto q = new NumericQuestion;
		q->id = i;

		q->question = item.value().at("intrebare").get<std::string>();

		q->answer = item.value().at("raspuns").get<int>();

		questions.push_back(q);
		i++;
	}
}
