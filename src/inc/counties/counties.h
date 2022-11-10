#include <iostream>

#ifndef PROJECTMODERNCPP_COUNTIES_H
#define PROJECTMODERNCPP_COUNTIES_H

class counties {
private:
	std::string m_countiesName = " ";
	int m_exp = 0;
public:
	counties(std::string Name, int exp);
};

#endif//PROJECTMODERNCPP_COUNTIES_H
