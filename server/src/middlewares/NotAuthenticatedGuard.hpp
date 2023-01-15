#pragma once

#include <crow.h>

#include "Session.hpp"

namespace middlewares {

	struct NotAuthenticatedGuard : crow::ILocalMiddleware {
		struct context {};

		template<typename AllContext>
		void before_handle(const crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx) {
			Session::context &session_ctx = all_ctx.template get<Session>();

			if (session_ctx.contains("id")) {
				res.code = crow::status::BAD_REQUEST;
				res.body = "Already logged in!";
				res.end();
			}
		}

		template<typename AllContext>
		void after_handle(const crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx) {}
	};

}// namespace middlewares
