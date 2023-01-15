#pragma once

#include "User.hpp"
#include "Lobby.hpp"
class Session {
private:
	User *m_player1 = nullptr;
	User *m_player2 = nullptr;
	User *m_player3 = nullptr;
	User *m_player4 = nullptr;
	int m_nrPlayer = 0;
	int nrMap = 0;
	std::vector<User *> lobby;

public:
	Session(User *player1 = nullptr, User *player2 = nullptr, User *player3 = nullptr, User *player4 =nullptr);

	void getPoint(int nrPlayer);
	void setPoint();
	void kickPlayer(int nrPlayer);
	int getNumberPlayer();
	bool isOnline(int nrPlayer) {
		if (nrPlayer == 2) {
			if (m_player2 == nullptr) {
				return false;
			}
		}else
		if (nrPlayer == 3) {
			if (m_player3 == nullptr) {
				return false;
			}
		}else
		if (nrPlayer == 4) {
			if (m_player4 == nullptr) {
				return false;
			}
		}else
		return true;
	}
	void Verify(int nrPlayer);
	const std::string getUser(int nr);
};
