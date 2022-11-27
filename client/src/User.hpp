#pragma once

#include <iostream>
#include <string>

class User {
private:
	std::string m_username;
	std::string m_password;
	int m_rank;
	int m_points;

public:
	User();

	void addUser();

	const std::string getUsername();
	const std::string getPassword();
	const int getRank();
	const int getPoints();

	void setUsername(const std::string username);
	void setPassword(const std::string password);
	void setRank(const int rank);
	void setPoints(const int points);

	void addPoints(const int countyPoints);

	friend std::ostream &operator<<(std::ostream &out, User &u);
};
