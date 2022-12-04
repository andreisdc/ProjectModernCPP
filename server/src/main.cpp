#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

struct User {
	int id;
	std::string username;
	std::string password;
};

int main() {
	crow::SimpleApp app;

	using namespace sqlite_orm;

	auto storage = make_storage(
		"db.sqlite",
		make_table(
			"users",
			make_column("id", &User::id, autoincrement(), primary_key()),
			make_column("username", &User::username),
			make_column("password", &User::password)
		)
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

	app.port(8080).run();

	return 0;
}
