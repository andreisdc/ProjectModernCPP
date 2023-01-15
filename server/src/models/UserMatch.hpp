#pragma once

#include <memory>

namespace models {

	struct UserMatch {
		int id;
		std::unique_ptr<int> player_id;
		int score;
	};

}// namespace models
