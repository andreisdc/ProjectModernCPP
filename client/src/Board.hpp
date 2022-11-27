#pragma once

#include "County.hpp"
#include <vector>

class Board {
private:
	std::vector<County> m_listCounty;
	County *m_county;

public:
	void selectCounty();
	void showCounty();
	void addCounty(County county);
	void moveCounty();
	void showAllCounties();
};
