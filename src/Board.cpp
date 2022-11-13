#pragma once

#include <cstdlib>
#include <ctime>
#include "Board.hpp"

void Board::addCounty(County county) {
	m_listCounty.push_back(county);
}

void Board::moveCounty() {
	std::cout << std::endl;
	std::cout << "IN CE JUDET VREI SA TE MUTI?:" << std::endl;
	this->m_county->showNumberNeighbors();

	int number;
	std::cin >> number;

	this->m_county = m_county->getCounty(number - 1);
}

void Board::selectCounty() {
	srand(time(NULL));
	int rnd;
	rnd = rand() % 41 + 0;
	this->m_county = &m_listCounty[rnd];
	m_listCountyV.push_back(&m_listCounty[rnd]);
}

void Board::showCounty() {
	m_county->showCountyName();
}

void Board::showAllCounties() {
	for (auto c: m_listCounty) {
		c.showCountyName();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

