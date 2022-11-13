//
// Created by alexi on 10/11/2022.
//

#include "user.h"
user::user() {
	std::cin>>m_username>>m_password;
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
std::ostream &operator<<(std::ostream &out, const user&) {
	out<<"Username: " << user.m_username << "\n";
	out<<"Rank: " << user.m_rank << "\n";
	return out;
}
