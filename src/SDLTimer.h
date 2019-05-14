#ifndef SDLTIMER_H_
#define SDLTIMER_H_

#include "Timer.h"
#include <SDL.h>
#include <math.h>

namespace SDLPac {
	class SDLTimer : public Pac::Timer {
	public :
		SDLTimer();
		void startTimer();
		int getTimeInSeconds();
		int getTimeInMinutes();
		void stopTimer();
		virtual ~SDLTimer();
	};
}




#endif /* SDLTIMER_H_ */
