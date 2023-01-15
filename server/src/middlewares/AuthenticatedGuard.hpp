#pragma once

#include <memory>

#include <crow.h>

#include "../Database.hpp"
#include "../models/User.hpp"
#include "Session.hpp"

namespace middlewares {

	struct AuthenticatedGuard : crow::ILocalMiddleware {
		struct context {
			std::unique_ptr<models::User> current_user;
		};

		template<typename AllContext>
		void before_handle(const crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx) {
			Session::context &session_ctx = all_ctx.template get<Session>();

			if (!session_ctx.contains("id")) {
				res.code = crow::status::FORBIDDEN;
				res.body = "Not logged in!";
				res.end();
				return;
			}

			const int current_user_id = session_ctx.get<int>("id");

			std::unique_ptr<models::User> current_user = storage->get_pointer<models::User>(current_user_id);

			if (!current_user) {
				session_ctx.remove("id");

				res.code = crow::status::INTERNAL_SERVER_ERROR;
				res.end();
				return;
			}

			ctx.current_user = std::move(current_user);
		}

		template<typename AllContext>
		void after_handle(const crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx) {}
	};

}// namespace middlewares
