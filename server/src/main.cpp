#include <nlohmann/json.hpp>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

int main() {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")
		([]() {
			return "Hello world";
		});

	app.port(8080)
		.multithreaded()
		.run();

	return 0;
}
