#include "Session.hpp"

Session::Session(User player, Board board) {
	this->m_Board = board;
	this->m_Player = player;
}

void Session::addCountyAtList() {
	m_listCountyV.push_back(selecctCounty);
}
