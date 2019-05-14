#ifndef TIMER_H_
#define TIMER_H_

namespace Pac {

	class Timer {
	public :
		Timer();
		bool getRunning();
		bool getRestarted();
		virtual void startTimer() = 0;
		virtual int getTimeInSeconds() = 0;
		virtual int getTimeInMinutes() = 0;
		virtual void stopTimer() = 0;
		virtual ~Timer();
	protected :
		int startTime;
		int* savedTime;
		int timeSeconds;
		int timeMinutes;
		bool running;
		bool restarted;
	};
}




#endif /* TIMER_H_ */
