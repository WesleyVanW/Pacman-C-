#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include <math.h>
#include <iostream>
#include "Collision.h"
#include "Astar.h"

namespace Pac {
	class movingEntity {
	public:
		movingEntity(char direction, float speed, float x, float y);
		movingEntity();
		int* getPosition();
		float *getFloatPosition();
		bool checkPosition(int mapWidth, int mapHeight);
		void changeDirection();
		char getDirection();
		char getReversedDirection();
		void move(Collision* c, int mapWidth, int mapHeight, bool frightened);
		void moveDirection(bool frightened);
		void checkOutOfBounds(int mapWidth, int mapHeight);
		void setDirection(char direction);
		void setLocation(int x, int y);
		void setStartTile(int x, int y);
		void moveToStartTile();
		void setSpeed(float speed);
		virtual ~movingEntity();
		virtual void setGhostDirectionChase(Collision* c, Astar* as, int* pacPosition);
		virtual void setGhostDirectionAmbush(Collision* c,Astar* as, int* pacPosition, char pacDirection);
		virtual void setGhostDirectionHomeTile(Collision* c,Astar* as);
		virtual bool isFrightened();
		virtual void setFrightened(int time);
		virtual void clearFrightened();
		virtual void checkStillFrightened();
		virtual void setFrightenTime(int frightenTime);
		virtual int getTimeFrightened();
		virtual void setStartPos(int x, int y);
		virtual void setHomeTile(int x, int y);
		virtual void moveToStartPos();
		virtual void moveToHomeTile();
		virtual bool isMoving();
		virtual void setMoving();
		virtual void clearMoving();
		virtual bool alive();
		virtual void setDimensions(int w, int h) = 0;
		virtual int getLives();
		virtual void setLives(int lives);
		virtual void death();
		virtual bool isEaten();
		virtual void setEaten();
		virtual void clearEaten();
		virtual void visualize() = 0;
	protected:
		float speed;
		float initSpeed;
		char direction;
		char savedDirection;
		float positionX;
		float positionY;
		int startX;
		int startY;
		int* positionCoord;
		float* floatPosition;
	};
}



#endif /* MOVINGENTITY_H_ */
