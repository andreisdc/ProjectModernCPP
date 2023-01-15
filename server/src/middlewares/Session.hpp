#pragma once

#include <crow/middlewares/session.h>

namespace middlewares {

	using Session = crow::SessionMiddleware<crow::InMemoryStore>;

}
