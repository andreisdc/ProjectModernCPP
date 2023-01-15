#pragma once

#include <memory>

namespace models {

	struct PastMatch {
		int id;
		std::unique_ptr<int> player1;
		std::unique_ptr<int> player2;
		std::unique_ptr<int> player3;
		std::unique_ptr<int> player4;
	};

}// namespace models
