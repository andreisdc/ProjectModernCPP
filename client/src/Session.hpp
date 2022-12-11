#pragma once

#include "Board.hpp"
#include "County.hpp"
#include "User.hpp"

class Session {
private:
	User *m_player1 = nullptr;
	User *m_player2 = nullptr;
	User *m_player3 = nullptr;
	User *m_player4 = nullptr;
	int nrPlayer = 0;
public:
	Session(User *player1 = nullptr, User *player2 = nullptr, User *player3 = nullptr, User *player4 =nullptr);
	void getPoint(int nrPlayer);
	void setPoint();
	void addPlayer();
	void kickPlayer();
};
