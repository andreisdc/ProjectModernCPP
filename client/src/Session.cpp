#include "Session.hpp"

Session::Session(User *player1, User *player2, User *player3, User *player4) {
	this->m_player1 = player1;
	this->m_player2 = player2;
	this->m_player3 = player3;
	this->m_player4 = player4;
}
void Session::getPoint(int nrPlayer) {
	if (nrPlayer == 1) {
		m_player1->setPoints(m_player1->getPoints() + 100);
	} else if (nrPlayer == 2) {
		m_player2->setPoints(m_player2->getPoints() + 100);
	} else if (nrPlayer == 3) {
		m_player3->setPoints(m_player3->getPoints() + 100);
	} else if (nrPlayer == 4) {
		m_player4->setPoints(m_player4->getPoints() + 100);
	}
}
void Session::setPoint() {
	m_player1->setPoints(0);
	m_player2->setPoints(0);
	m_player3->setPoints(0);
	m_player4->setPoints(0);
}
void Session::addPlayer(int nrPlayer) {

	 if (nrPlayer == 2) {
		m_player1 = nullptr;
	} else if (nrPlayer == 3) {
		m_player2 = nullptr;
	} else if (nrPlayer == 4) {
		m_player3 = nullptr;
	}
}

