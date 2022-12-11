#include <crow.h>
#include <crow/middlewares/session.h>
#include <sqlite_orm/sqlite_orm.h>
#include <memory>

struct User {
	int id;
	std::string username;
	std::string password;
};

struct UserMatch {
	int id;
	std::unique_ptr<int> player_id;
	int score;
};

struct PastMatch {
	int id;
	std::unique_ptr<int> player1;
	std::unique_ptr<int> player2;
	std::unique_ptr<int> player3;
	std::unique_ptr<int> player4;
};

int main() {
	using SessionMiddleware = crow::SessionMiddleware<crow::InMemoryStore>;
	using CustomApp = crow::App<crow::CookieParser, SessionMiddleware>;

	CustomApp app;

	using namespace sqlite_orm;

	auto storage = make_storage(
		"db.sqlite",
		make_table(
			"users",
			make_column("id", &User::id, autoincrement(), primary_key()),
			make_column("username", &User::username),
			make_column("password", &User::password)),
		make_table(
			"user_matches",
			make_column("id", &UserMatch::id, autoincrement(), primary_key()),
			make_column("player_id", &UserMatch::player_id),
			make_column("score", &UserMatch::score),
			foreign_key(&UserMatch::player_id).references(&User::id).on_delete.cascade()),
		make_table(
			"past_matches",
			make_column("id", &PastMatch::id, autoincrement(), primary_key()),
			make_column("player1", &UserMatch::player_id),
			make_column("player2", &UserMatch::player_id),
			make_column("player3", &UserMatch::player_id),
			make_column("player4", &UserMatch::player_id),
			foreign_key(&PastMatch::player1).references(&UserMatch::id).on_delete.cascade(),
			foreign_key(&PastMatch::player2).references(&UserMatch::id).on_delete.cascade(),
			foreign_key(&PastMatch::player3).references(&UserMatch::id).on_delete.cascade(),
			foreign_key(&PastMatch::player4).references(&UserMatch::id).on_delete.cascade())
	);

	CROW_ROUTE(app, "/")
		([]() {
			return "Hello world";
		});

	CROW_ROUTE(app, "/users/login")
		.methods(crow::HTTPMethod::POST)
			([&storage](const crow::request &req) {
				auto x = crow::json::load(req.body);
				if (!x)
					return crow::response(400);

				std::string username = x["username"].s();
				std::string password = x["password"].s();

				return crow::response(200);
			});

	CROW_ROUTE(app, "/users/register")
		.methods(crow::HTTPMethod::POST)
			([&storage](const crow::request &req) {
				auto x = crow::json::load(req.body);
				if (!x)
					return crow::response(400);

				std::string username = x["username"].s();
				std::string password = x["password"].s();

				User user{-1, username, password};
				auto newUserId = storage.insert(user);
				user.id = newUserId;

				return crow::response(201);
			});

	app.port(8080)
		.multithreaded()
		.run();

	return 0;
}
