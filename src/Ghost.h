#ifndef GHOST_H_
#define GHOST_H_

#include "movingEntity.h"
#include "Timer.h"

namespace Pac {
	class Ghost : public movingEntity {
	public:
		Ghost(char direction, float speed, float x, float y, int homeTileX, int homeTileY, int startPosX, int startPosY, Timer* t);
		void setGhostDirectionChase(Collision* c,Astar* as, int* pacPosition);
		void setGhostDirectionAmbush(Collision* c,Astar* as, int* pacPosition, char pacDirection);
		void setGhostDirectionHomeTile(Collision* c,Astar* as);
		bool isFrightened();
		void setFrightened(int time);
		void clearFrightened();
		void checkStillFrightened();
		int getTimeFrightened();
		void setFrightenTime(int frightenTime);
		void setStartPos(int x, int y);
		void setHomeTile(int x, int y);
		void moveToStartPos();
		bool isEaten();
		void setEaten();
		void clearEaten();
		virtual ~Ghost();
	protected:
		bool frightened;
		int timeStartFrightened;
		int frightenTime;
		int homeTileX;
		int homeTileY;
		int startPosX;
		int startPosY;
		bool wasAlreadyFrightened;
		bool eaten;
		Timer* t;
	};
}

#endif /* GHOST_H_ */
