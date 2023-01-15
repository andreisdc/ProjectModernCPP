#pragma once

#include <memory>
#include <string>

#include <sqlite_orm/sqlite_orm.h>

#include "models/PastMatch.hpp"
#include "models/User.hpp"
#include "models/UserMatch.hpp"

inline auto initStorage(const std::string &path) {
	using namespace sqlite_orm;
	return make_storage(path,
						make_table(
								"users",
								make_column("id", &models::User::id, autoincrement(), primary_key()),
								make_column("username", &models::User::username),
								make_column("password", &models::User::password)),
						make_table(
								"user_matches",
								make_column("id", &models::UserMatch::id, autoincrement(), primary_key()),
								make_column("player_id", &models::UserMatch::player_id),
								make_column("score", &models::UserMatch::score),
								foreign_key(&models::UserMatch::player_id).references(&models::User::id).on_delete.cascade()),
						make_table(
								"past_matches",
								make_column("id", &models::PastMatch::id, autoincrement(), primary_key()),
								make_column("player1", &models::UserMatch::player_id),
								make_column("player2", &models::UserMatch::player_id),
								make_column("player3", &models::UserMatch::player_id),
								make_column("player4", &models::UserMatch::player_id),
								foreign_key(&models::PastMatch::player1).references(&models::UserMatch::id).on_delete.cascade(),
								foreign_key(&models::PastMatch::player2).references(&models::UserMatch::id).on_delete.cascade(),
								foreign_key(&models::PastMatch::player3).references(&models::UserMatch::id).on_delete.cascade(),
								foreign_key(&models::PastMatch::player4).references(&models::UserMatch::id).on_delete.cascade()));
}

using Storage = decltype(initStorage(""));

extern std::unique_ptr<Storage> storage;
