#include "Lobby.hpp"

Lobby::Lobby(User *player1, User *player2, User *player3, User *player4) {
	if (player1 != nullptr)
		m_lobby.push_back(player1);
	if (player2 != nullptr)
		m_lobby.push_back(player2);
	if (player3 != nullptr)
		m_lobby.push_back(player3);
	if (player4 != nullptr)
		m_lobby.push_back(player4);
	
}
void Lobby::kickPlayer(int nr) {
	m_lobby[nr - 1] = nullptr;
}

User * Lobby::getUser(int nr) {
	return m_lobby[nr];
}

void Lobby::Verify(int nrPlayer) {
	for (int i = 0; i < nrPlayer; i++) {
		if (m_lobby[i] == nullptr) {
			m_lobby.erase(m_lobby.begin() + i);
			nrPlayer--;
			i--;
		}
	}
}



