#pragma once

#include <string>

struct User {
	User(int id, const std::string &username)
		: id(id), username(username) {}

	int id;
	std::string username;
};
