#pragma once
#include <QtCore>
#include "User.hpp"

class MyThread : public QThread{
public:
	MyThread();
	void run(User user);

};
