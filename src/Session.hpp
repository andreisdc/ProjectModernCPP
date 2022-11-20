#pragma once

#ifndef PROIECT_MODERN_CPP_SESSION_HPP
#define PROIECT_MODERN_CPP_SESSION_HPP

#include "County.hpp"
#include "Board.hpp"
#include "User.hpp"

class Session {
private:
	User m_Player;
	Board m_Board;
	unsigned int m_life = 3;
	int m_points = 0;
	std::vector<County *> m_listCountyV;
	County* selecctCounty;

public:
	Session(User player,Board board);
	void getRank();
	void setRank();
	void getPoint();
	void setPoint();
	void addCountyAtList();

};

#endif//PROIECT_MODERN_CPP_SESSION_HPP
