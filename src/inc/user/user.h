//
// Created by alexi on 10/11/2022.
//
#include <string>
#include <iostream>
#ifndef PROIECT_MODERN_CPP_USER_H
#define PROIECT_MODERN_CPP_USER_H

class user {
private:
	std::string m_username;
	std::string m_password;
public:
	user();
	void addUser();
	std::string getUsername();
	std::string getPassword();
	void setUsername(std::string username);
	void setPassword(std::string password);

};

#endif//PROIECT_MODERN_CPP_USER_H
