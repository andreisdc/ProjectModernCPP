#pragma once

#include <iostream>
#include <vector>

class County {
private:
	std::string m_countiesName = " ";
	int m_exp = 0;
	int m_numberNeighbors = 0;
	std::vector<County *> m_listNeighbors;

public:
	County(const std::string &name, int exp);
	void addCounty(County *County);
	County *getCounty(int number);
	void showCountyName();
	void showNumberNeighbors();
};
