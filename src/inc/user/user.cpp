//
// Created by alexi on 10/11/2022.
//

#include "user.h"
user::user() {
	std::cin>>m_username>>m_password;
	m_rank = 0;
	m_points = 0;
}
void user::addUser() {

}
const std::string user::getUsername() {
	return m_username;
}
const std::string user::getPassword() {
	return m_password;
}
void user::setUsername(std::string username) {
	this->m_username = username;
}
void user::setPassword(std::string password) {
	this->m_password = password;
}
const int user::getRank() {
	return m_rank;
}
void user::setRank(const int rank) {
	this->m_rank = rank;
}
std::ostream &operator<<(std::ostream &out, user& u) {
	out<<"Username: " << u.m_username << "\n";
	out<<"Rank: " << u.m_rank << "\n";
	out<<"Points: " << u.m_points << "\n";
	return out;
}
const int user::getPoints() {
	return m_points;
}
void user::setPoints(const int points) {
	this->m_points = points;
}
void user::addPoints(const int countyPoints) {
	m_points += countyPoints;
}
