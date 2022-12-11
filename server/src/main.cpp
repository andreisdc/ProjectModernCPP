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

	CROW_ROUTE(app, "/users/login").methods(crow::HTTPMethod::POST)
		([&app, &storage](const crow::request &req) {
			auto jsonBody = crow::json::load(req.body);
			if (!jsonBody || !jsonBody.has("username") || !jsonBody.has("password"))
				return crow::response(crow::status::BAD_REQUEST);

			if (app.get_context<SessionMiddleware>(req).contains("id"))
				return crow::response(crow::status::BAD_REQUEST, "Already logged in!");

			std::string username = jsonBody["username"].s();
			std::string password = jsonBody["password"].s();

			auto selectedIds = storage.select(
				&User::id,
				where(is_equal(&User::username, username) and is_equal(&User::password, password)));

			if (selectedIds.empty())
				return crow::response(crow::status::NOT_FOUND);

			auto selectedId = selectedIds.front();

			app.get_context<SessionMiddleware>(req).set("id", selectedId);

			return crow::response(crow::status::OK);
		});

	CROW_ROUTE(app, "/users/register").methods(crow::HTTPMethod::POST)
		([&app, &storage](const crow::request &req) {
			auto jsonBody = crow::json::load(req.body);
			if (!jsonBody || !jsonBody.has("username") || !jsonBody.has("password"))
				return crow::response(crow::status::BAD_REQUEST);

			if (app.get_context<SessionMiddleware>(req).contains("id"))
				return crow::response(crow::status::BAD_REQUEST, "Already logged in!");

			std::string username = jsonBody["username"].s();
			std::string password = jsonBody["password"].s();

			auto selectedIds = storage.select(
				&User::id,
				where(is_equal(&User::username, username)));

			if (!selectedIds.empty())
				return crow::response(crow::status::BAD_REQUEST, "User already exists!");

			User user{-1, username, password};
			auto newUserId = storage.insert(user);
			user.id = newUserId;

			return crow::response(crow::status::CREATED);
		});

	CROW_ROUTE(app, "/users/logout").methods(crow::HTTPMethod::GET)
		([&app](const crow::request &req) {
			app.get_context<SessionMiddleware>(req).remove("id");

			return crow::response(crow::status::OK);
		});

	CROW_WEBSOCKET_ROUTE(app, "/ws")
		.onaccept([&](const crow::request &req, void **userdata) -> bool {
			std::cout << "New WebSocket connection!" << std::endl;
			return true;
		})
		.onopen([&](crow::websocket::connection &conn) {
			std::cout << "WebSocket connection opened!" << std::endl;
		})
		.onmessage([&](crow::websocket::connection &conn, const std::string &message, bool is_binary) {
			std::cout << "New WebSocket message: " << message << std::endl;
		})
		.onerror([&](crow::websocket::connection &conn, const std::string &error_message) {
			std::cout << "WebSocket connection error! " << error_message << std::endl;
		})
		.onclose([&](crow::websocket::connection &conn, const std::string &reason) {
			std::cout << "WebSocket connection closed." << std::endl;
		});

	/*
	 * GET /
	 *
	 * POST /users/login {username, password}
	 * POST /users/register {username, password}
	 *
	 * POST /lobby/create
	 * POST /lobby/send_invite {username} -> invite_id
	 * POST /lobby/cancel_invite {invite_id}
	 * POST /lobby/accept_invite {invite_id}
	 * POST /lobby/deny_invite {invite_id}
	 * POST /lobby/kick {username}
	 * POST /lobby/start
	 *
	 * POST /match/leave
	 */

	app.port(8080)
		.multithreaded()
		.run();

	return 0;
}
