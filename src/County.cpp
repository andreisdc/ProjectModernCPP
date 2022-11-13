#include "County.hpp"

County::County(const std::string &name, int exp) {
	this->m_countiesName = name;
	this->m_exp = exp;
}

void County::addCounty(County *county) {
	this->m_listNeighbors.push_back(county);
	this->m_numberNeighbors++;
}

County *County::getCounty(int number) {
	return m_listNeighbors[number];
}

void County::showCountyName() {
	std::cout << m_countiesName;
}

void County::showNumberNeighbors() {
	int contor = 1;
	for (auto c: m_listNeighbors) {
		std::cout << "(" << contor << ") ";
		c->showCountyName();
		contor++;
		std::cout << std::endl;
	}
}
