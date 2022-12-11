#pragma once

#include "Board.hpp"
#include "County.hpp"
#include "User.hpp"

class Session {
private:
	User m_player1;
	User m_player2;
	User m_player3;
	User m_player4;
	int nrPlayer = 0;
public:
	Session(User player1, User player2, User player3, User player4);
	void getPoint(int nrPlayer);
	void setPoint();
	void addPlayer();
	void kickPlayer();
};
