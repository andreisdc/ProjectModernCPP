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
	int m_rank;
public:
	user();
	void addUser();
	const std::string getUsername();
	const std::string getPassword();
	const int getRank();
	void setUsername(const std::string username);
	void setPassword(const std::string password);
	void setRank(const int rank);
	friend std::ostream& operator<<(std::ostream& out, const user& u);

};

#endif//PROIECT_MODERN_CPP_USER_H
