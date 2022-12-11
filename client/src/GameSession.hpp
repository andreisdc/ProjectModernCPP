#pragma once
#include "County.hpp"
#include "Board.hpp"
#include "User.hpp"

class GameSession {

private:
	User m_player1;
	User m_player2;
	User m_player3;
	User m_player4;
public:
	GameSession(User player1, User player2, User player3, User player4);
	void battleOne();
	void battleTwo();
};
