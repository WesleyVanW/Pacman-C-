#include "Timer.h"

namespace Pac {

	Timer::Timer() {
		this->startTime = 0;
		this->savedTime = new int[2];
		this->running = false;
		this->restarted = false;
		this->timeSeconds = 0;
		this->timeMinutes = 0;
	}

	//return if time is running
	bool Timer::getRunning() {
		return running;
	}

	//returns if timer is restarted
	bool Timer::getRestarted() {
		return restarted;
	}

	Timer::~Timer() {
		delete savedTime;
	}
}




