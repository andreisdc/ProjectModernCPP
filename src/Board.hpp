#pragma once

#include <vector>
#include "County.hpp"

class Board {
private:
	std::vector<County> m_listCounty;
	County *m_county;
	std::vector<County *> m_listCountyV;

public:
	void selectCounty();
	void showCounty();
	void addCounty(County county);
	void moveCounty();
	void showAllCounties();
};
