#include "User.hpp"

User::User() {
	std::cin >> m_username >> m_password;
	m_rank = 0;
	m_points = 0;
}

void User::addUser() {
}

const std::string User::getUsername() {
	return m_username;
}

const std::string User::getPassword() {
	return m_password;
}

void User::setUsername(std::string username) {
	this->m_username = username;
}

void User::setPassword(std::string password) {
	this->m_password = password;
}

const int User::getRank() {
	return m_rank;
}

void User::setRank(const int rank) {
	this->m_rank = rank;
}

std::ostream &operator<<(std::ostream &out, User &u) {
	out << "Username: " << u.m_username << "\n";
	out << "Rank: " << u.m_rank << "\n";
	out << "Points: " << u.m_points << "\n";
	return out;
}

const int User::getPoints() {
	return m_points;
}

void User::setPoints(const int points) {
	this->m_points = points;
}

void User::addPoints(const int countyPoints) {
	m_points += countyPoints;
}
