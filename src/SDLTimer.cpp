#include "SDLTimer.h"

namespace SDLPac {

	SDLTimer::SDLTimer() : Pac::Timer() {

	}

	//starts the timer
	void SDLTimer::startTimer() {
		startTime = SDL_GetTicks();
		running = true;
	}

	//returns time in seconds
	int SDLTimer::getTimeInSeconds() {
		if(restarted == false && running == true) {
			timeSeconds = SDL_GetTicks() - startTime;
			timeSeconds = timeSeconds/1000;
			timeSeconds = timeSeconds % 60;
			timeSeconds = floor(timeSeconds);
		}
		else if(restarted == true && running == true) {
			timeSeconds = SDL_GetTicks() - startTime;
			timeSeconds = timeSeconds/1000;
			timeSeconds = timeSeconds % 60;
			timeSeconds = floor(timeSeconds + savedTime[0]);
		}
		else {
			timeSeconds = savedTime[0];
		}
		return timeSeconds;
	}

	//returns time in minutes
	int SDLTimer::getTimeInMinutes() {
		if(restarted == false && running == true) {
			timeMinutes = SDL_GetTicks() - startTime;
			timeMinutes = timeMinutes/1000;
			timeMinutes = timeMinutes/60;
			timeMinutes = floor(timeMinutes);
		}
		else if (restarted == true && running == true) {
			timeMinutes = SDL_GetTicks() - startTime;
			timeMinutes = timeMinutes/1000;
			timeMinutes = timeMinutes/60;
			timeMinutes = floor(timeMinutes + savedTime[1]);
		}
		else {
			timeMinutes = savedTime[1];
		}
		return timeMinutes;
	}

	//stops the timer and saves the current timer
	void SDLTimer::stopTimer() {
		running = false;
		restarted = true;
		savedTime[0] = timeSeconds;
		savedTime[1] = timeMinutes;
	}

    SDLTimer::SDLTimer::~SDLTimer() {
	}

}



