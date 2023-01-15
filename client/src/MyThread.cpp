#include "MyThread.hpp"

MyThread::MyThread() {
}

void MyThread::run(User user) {
	while (user.getMoves() > 0) {
		wait();
	}
}
