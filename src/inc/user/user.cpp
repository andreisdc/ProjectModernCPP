//
// Created by alexi on 10/11/2022.
//

#include "user.h"
user::user() {
	std::cin>>username>>password;
}
void user::addUser() {

}
std::string user::getUsername() {
	return m_username;
}
std::string user::getPassword() {
	return m_password;
}
void user::setUsername(std::string username) {
	this->m_username = username;
}
void user::setPassword(std::string password) {
	this->m_password = password;
}
