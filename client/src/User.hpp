#pragma once

#include <iostream>
#include <string>
#include <QPushButton>

class User {
private:
	std::string m_username;
	std::string m_password;
	int m_rank;
	int m_points;
	int nrMoves;
	std::vector<QPushButton> m_myCounty;
	int nrColor;

public:
	User(std::string userName, int point);
	User();
	const std::string getUsername();
	const std::string getPassword();
	void setColor(int nr);
	const int getRank();
	const int getPoints();
	void setMoves(int nr);
	void decreaseMove();
	int getMoves();
	void setUsername(const std::string username);
	void setPassword(const std::string password);
	void setRank(const int rank);
	void setPoints(const int points);
	void addCounty(const QPushButton button);
	void addPoints(const int countyPoints);

	friend std::ostream &operator<<(std::ostream &out, User &u);
};
