#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

class County {
private:
	std::string m_countiesName = " ";
	int m_exp = 0;
	int m_numberNeighbors = 0;
	std::vector<County *> m_listNeighbors;
	json m_questionsTrivia;

public:
	County(const std::string &name, int exp);
	void addCounty(County *County);
	County *getCounty(int number);
	void showCountyName();
	void showNumberNeighbors();
	void showTriviaQuestions();
};
