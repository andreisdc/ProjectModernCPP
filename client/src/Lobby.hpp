#pragma once
#include "User.hpp"
#include <vector>
class Lobby {
private:
	std::vector<User*> m_lobby;
public:
	Lobby(User *player1 = nullptr, User *player2 = nullptr, User *player3 = nullptr, User *player4 = nullptr);
	void kickPlayer(int nr);
	User *getUser(int nr);
	void Verify(int nrPlayer);
};
