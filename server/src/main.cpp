#include <iostream>
#include <memory>
#include <vector>

#include <crow.h>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include "Database.hpp"
#include "game/Lobby.hpp"
#include "game/Match.hpp"
#include "game/Player.hpp"
#include "game/Territory.hpp"
#include "game/User.hpp"
#include "middlewares/AuthenticatedGuard.hpp"
#include "middlewares/NotAuthenticatedGuard.hpp"
#include "middlewares/Session.hpp"
#include "models/PastMatch.hpp"
#include "models/User.hpp"
#include "models/UserMatch.hpp"

struct WebSocketUser {
	int id;
	std::string username;
	int lobby_id;
	int match_id;
};

using CustomApp = crow::App<
		crow::CookieParser,
		middlewares::Session>;

std::unique_ptr<Storage> storage;

int main() {
	/*
	 * Application instance
	 */
	CustomApp app;

	/*
	 * Database init
	 */
	using namespace sqlite_orm;

	storage = std::make_unique<Storage>(initStorage("db.sqlite"));

	/*
	 * Questions file
	 */
	std::ifstream json_file("intrebari.json");
	nlohmann::json questions_json = nlohmann::json::parse(json_file);
	json_file.close();
	MultipleChoiceQuestion::load(questions_json.at("Standard questions"));
	NumericQuestion::load(questions_json.at("Numerical questions"));

	/*
	 * WebSockets misc
	 */
	std::mutex websocket_mutex;
	std::unordered_set<crow::websocket::connection *> websocket_users;

	auto broadcast_to_lobby = [&websocket_users](int id, int lobby_id, const std::string &message) -> void {
		for (auto user: websocket_users) {
			auto userdata = reinterpret_cast<WebSocketUser *>(user->userdata());

			if (userdata->id == id)
				continue;

			if (userdata->lobby_id != lobby_id)
				continue;

			user->send_text(message);
		}
	};

	auto broadcast_to_match = [&websocket_users](int id, int match_id, const std::string &message) -> void {
		for (auto user: websocket_users) {
			auto userdata = reinterpret_cast<WebSocketUser *>(user->userdata());

			if (userdata->id == id)
				continue;

			if (userdata->match_id)
				continue;

			user->send_text(message);
		}
	};

	/*
	 * Router
	 */
	CROW_ROUTE(app, "/users/login")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("username") || !json_body.has("password"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Already logged in!");

				const std::string username = json_body["username"].s();
				const std::string password = json_body["password"].s();

				const std::vector<int> selected_ids = storage->select(
						&models::User::id,
						where(is_equal(&models::User::username, username) && is_equal(&models::User::password, password)));

				if (selected_ids.empty())
					return crow::response(crow::status::NOT_FOUND, "User not found.");

				const int selected_id = selected_ids.front();

				session_ctx.set<int>("id", selected_id);

				return crow::response(crow::status::OK, "Logged in!");
			});

	CROW_ROUTE(app, "/users/register")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("username") || !json_body.has("password"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Already logged in!");

				const std::string username = json_body["username"].s();
				const std::string password = json_body["password"].s();

				const std::vector<int> selected_ids = storage->select(
						&models::User::id,
						where(is_equal(&models::User::username, username)));

				if (!selected_ids.empty())
					return crow::response(crow::status::CONFLICT, "User already exists!");

				models::User user{-1, username, password};
				const int new_user_id = storage->insert(user);
				user.id = new_user_id;

				return crow::response(crow::status::CREATED, "Registered!");
			});

	CROW_ROUTE(app, "/users/logout")
			.methods(crow::HTTPMethod::GET)([&app](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (session_ctx.contains("id"))
					session_ctx.remove("id");

				if (session_ctx.contains("lobby_id"))
					session_ctx.remove("lobby_id");

				if (session_ctx.contains("match_id"))
					session_ctx.remove("match_id");

				return crow::response(crow::status::OK, "Logged out!");
			});

	CROW_ROUTE(app, "/users/profile")
			.methods(crow::HTTPMethod::GET)([&app](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				crow::json::wvalue json_body;

				// TODO: populate json_body

				return crow::response(crow::status::OK, json_body);
			});

	CROW_ROUTE(app, "/lobby/create")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (session_ctx.contains("lobby_id"))
					return crow::response(crow::status::FORBIDDEN, "Already in a lobby!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				Lobby *new_lobby = new Lobby(new User(current_user->id, current_user->username));

				Lobby::lobbies.push_back(new_lobby);

				session_ctx.set<int>("lobby_id", new_lobby->get_id());

				crow::json::wvalue json_body;

				json_body["lobbyId"] = new_lobby->get_id();

				return crow::response(crow::status::CREATED, json_body);
			});

	CROW_ROUTE(app, "/lobby/delete")
			.methods(crow::HTTPMethod::POST)([&app, &broadcast_to_lobby](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("lobby_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a lobby!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int lobby_id = session_ctx.get<int>("lobby_id");

				auto current_lobby = Lobby::find_by_id(lobby_id);

				if (!current_lobby) {
					session_ctx.remove("lobby_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid lobby!");
				}

				if (current_lobby->creator->id != current_user->id) {
					return crow::response(crow::status::UNAUTHORIZED, "Not the lobby creator!");
				}

				crow::json::wvalue message = {{"type", "lobby_delete"}};
				broadcast_to_lobby(current_user_id, lobby_id, message.dump());

				Lobby::delete_by_ptr(current_lobby);

				session_ctx.remove("lobby_id");

				return crow::response(crow::status::OK, "Deleted.");
			});

	CROW_ROUTE(app, "/lobby/join")
			.methods(crow::HTTPMethod::POST)([&app, &broadcast_to_lobby](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("lobbyId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (session_ctx.contains("lobby_id"))
					return crow::response(crow::status::FORBIDDEN, "Already in a lobby!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int lobby_id = json_body["lobbyId"].i();

				auto current_lobby = Lobby::find_by_id(lobby_id);

				if (!current_lobby) {
					session_ctx.remove("lobby_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid lobby session!");
				}

				if (!current_lobby->add_player(new User(current_user->id, current_user->username))) {
					return crow::response(crow::status::BAD_REQUEST, "Lobby is full!");
				}

				session_ctx.set<int>("lobby_id", lobby_id);

				crow::json::wvalue message = {
						{"type", "lobby_join"},
						{"id", current_user_id},
						{"username", current_user->username},
				};
				broadcast_to_lobby(current_user_id, lobby_id, message.dump());

				crow::json::wvalue wjson_body;
				wjson_body[0] = {
						{"id", current_lobby->creator->id},
						{"username", current_lobby->creator->username},
				};
				wjson_body[1] = {
						{"id", current_lobby->user2->id},
						{"username", current_lobby->user2->username},
				};
				if (current_lobby->user3 != nullptr) {
					wjson_body[2] = {
							{"id", current_lobby->user3->id},
							{"username", current_lobby->user3->username},
					};
				}
				if (current_lobby->user4 != nullptr) {
					wjson_body[3] = {
							{"id", current_lobby->user4->id},
							{"username", current_lobby->user4->username},
					};
				}

				return crow::response(crow::status::OK, wjson_body);
			});

	CROW_ROUTE(app, "/lobby/leave")
			.methods(crow::HTTPMethod::POST)([&app, &broadcast_to_lobby](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("lobby_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a lobby!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int lobby_id = session_ctx.get<int>("lobby_id");

				auto current_lobby = Lobby::find_by_id(lobby_id);

				if (!current_lobby) {
					session_ctx.remove("lobby_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid lobby session!");
				}

				if (current_lobby->creator->id == current_user->id) {
					return crow::response(crow::status::BAD_REQUEST, "The host may not leave! Delete the lobby instead.");
				}

				if (!current_lobby->remove_player(current_user_id)) {
					return crow::response(crow::status::INTERNAL_SERVER_ERROR);
				}

				session_ctx.remove("lobby_id");

				crow::json::wvalue message = {
						{"type", "lobby_leave"},
						{"id", current_user_id},
				};
				broadcast_to_lobby(current_user_id, lobby_id, message.dump());

				return crow::response(crow::status::OK);
			});

	CROW_ROUTE(app, "/match/start")
			.methods(crow::HTTPMethod::POST)([&app, &websocket_users](const crow::request &req) -> crow::response {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("lobby_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a lobby!");

				if (session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Already in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int lobby_id = session_ctx.get<int>("lobby_id");

				auto current_lobby = Lobby::find_by_id(lobby_id);

				if (!current_lobby) {
					session_ctx.remove("lobby_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid lobby session!");
				}

				if (current_lobby->creator->id != current_user->id) {
					return crow::response(crow::status::UNAUTHORIZED, "Only the host may start the match.");
				}

				auto current_match = new Match(current_lobby);

				Match::matches.push_back(current_match);

				crow::json::wvalue message = {
					{"type", "match_start"}
				};
				
				for (auto user: websocket_users) {
					auto userdata = reinterpret_cast<WebSocketUser *>(user->userdata());

					if (userdata->id == current_user_id)
						continue;

					if (userdata->lobby_id != lobby_id)
						continue;

					userdata->match_id = current_match->id;

					user->send_text(message.dump());
				}

				Lobby::delete_by_ptr(current_lobby);

				session_ctx.remove("lobby_id");

				session_ctx.set<int>("match_id", current_match->id);

				return crow::response(crow::status::CREATED);
			});

	CROW_ROUTE(app, "/match/pre_base_selection_answer")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("answerId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");
					
				if (!session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int current_match_id = session_ctx.get<int>("id");

				auto current_match = Match::find_by_id(current_match_id);

				if (!current_match) {
					session_ctx.remove("match_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid match session!");
				}

				const int answer_id = json_body["answerId"].i();

				current_match->submit_pre_base_selection_answer(current_user_id, answer_id);

				return crow::response(crow::status::OK);
			});

	CROW_ROUTE(app, "/match/base_choice")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("answerId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int current_match_id = session_ctx.get<int>("id");

				auto current_match = Match::find_by_id(current_match_id);

				if (!current_match) {
					session_ctx.remove("match_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid match session!");
				}

				const int answer_id = json_body["answerId"].i();

				current_match->submit_base_choice(current_user_id, answer_id);

				return crow::response(crow::status::OK);
			});

	CROW_ROUTE(app, "/match/territory_selection_answer")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("answerId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int current_match_id = session_ctx.get<int>("id");

				auto current_match = Match::find_by_id(current_match_id);

				if (!current_match) {
					session_ctx.remove("match_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid match session!");
				}

				const int answer_id = json_body["answerId"].i();

				current_match->submit_territory_selection_answer(current_user_id, answer_id);

				return crow::response(crow::status::OK);
			});

	CROW_ROUTE(app, "/match/territory_choice")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("answerId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int current_match_id = session_ctx.get<int>("id");

				auto current_match = Match::find_by_id(current_match_id);

				if (!current_match) {
					session_ctx.remove("match_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid match session!");
				}

				const int answer_id = json_body["answerId"].i();

				current_match->submit_territory_choice(current_user_id, answer_id);

				return crow::response(crow::status::OK);
			});

	CROW_ROUTE(app, "/match/duel_choice")
			.methods(crow::HTTPMethod::POST)([&app](const crow::request &req) -> crow::response {
				auto json_body = crow::json::load(req.body);
				if (!json_body || !json_body.has("answerId"))
					return crow::response(crow::status::BAD_REQUEST, "Incorrect body format.");

				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return crow::response(crow::status::FORBIDDEN, "Not logged in!");

				if (!session_ctx.contains("match_id"))
					return crow::response(crow::status::FORBIDDEN, "Not in a match!");

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid session!");
				}

				const int current_match_id = session_ctx.get<int>("id");

				auto current_match = Match::find_by_id(current_match_id);

				if (!current_match) {
					session_ctx.remove("match_id");
					return crow::response(crow::status::INTERNAL_SERVER_ERROR, "Invalid match session!");
				}

				const int answer_id = json_body["answerId"].i();

				current_match->submit_duel_choice(current_user_id, answer_id);

				return crow::response(crow::status::OK);
			});

	CROW_WEBSOCKET_ROUTE(app, "/game_socket")
			.onaccept([&](const crow::request &req, void **userdata) -> bool {
				auto &session_ctx = app.get_context<middlewares::Session>(req);

				if (!session_ctx.contains("id"))
					return false;

				if (!session_ctx.contains("lobby_id"))
					return false;

				const int current_user_id = session_ctx.get<int>("id");

				auto current_user = storage->get_pointer<models::User>(current_user_id);

				if (!current_user) {
					session_ctx.remove("id");
					return false;
				}

				const int lobby_id = session_ctx.get<int>("lobby_id");

				auto current_lobby = Lobby::find_by_id(lobby_id);

				if (!current_lobby) {
					session_ctx.remove("lobby_id");
					return false;
				}

				*userdata = new WebSocketUser{
						current_user->id,
						current_user->username,
						lobby_id,
				};

				return true;
			})
			.onopen([&](crow::websocket::connection &conn) -> void {
				CROW_LOG_INFO << "WebSocket connection opened!";

				std::lock_guard<std::mutex> mutex_lock(websocket_mutex);

				websocket_users.insert(&conn);
			})
			.onmessage([&](crow::websocket::connection &conn, const std::string &message, bool is_binary) -> void {
				std::lock_guard<std::mutex> mutex_lock(websocket_mutex);

				auto conn_userdata = reinterpret_cast<WebSocketUser *>(conn.userdata());
			})
			.onerror([&](crow::websocket::connection &conn, const std::string &error_message) -> void {
				CROW_LOG_ERROR << "WebSocket connection error! " << error_message;
			})
			.onclose([&](crow::websocket::connection &conn, const std::string &reason) -> void {
				CROW_LOG_INFO << "WebSocket connection closed! " << reason;

				std::lock_guard<std::mutex> mutex_lock(websocket_mutex);

				auto conn_userdata = reinterpret_cast<WebSocketUser *>(conn.userdata());

				crow::json::wvalue message = {
						{"type", "lobby_leave"},
						{"id", conn_userdata->id},
				};

				for (auto user: websocket_users) {
					if (user == &conn)
						continue;

					auto userdata = reinterpret_cast<WebSocketUser *>(user->userdata());

					if (userdata->lobby_id == conn_userdata->lobby_id)
						continue;

					user->send_text(message.dump());
				}

				websocket_users.erase(&conn);
			});

	app.port(8080).multithreaded().run();

	return 0;
}
